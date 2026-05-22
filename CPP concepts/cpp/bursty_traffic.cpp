#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <string>
#include <stdexcept>

/*
wait_for() with a timeout returns false if the condition isn't met in time. This prevents the producer 
from blocking forever when the queue is full. The timeout approach works well for request handlers that 
need to fail fast under overload.
*/

struct PurchaseRequest {
    std::string userId;
    std::string eventId;
    int quantity;
};

class TicketService {
    // Sized for 10-second burst at 10,000 req/s
    std::queue<PurchaseRequest> purchaseQueue_;
    std::mutex mutex_;
    std::condition_variable not_empty_;
    std::condition_variable not_full_;
    static constexpr size_t MAX_SIZE = 100000;

public:
    // API handler (producer) - handles bursts
    void purchaseTicket(const std::string& userId, const std::string& eventId, int quantity) {
        PurchaseRequest request{userId, eventId, quantity};

        // Enqueue request - returns immediately even during spike
        std::unique_lock<std::mutex> lock(mutex_);
        if (!not_full_.wait_for(lock, std::chrono::milliseconds(100), [this] { return purchaseQueue_.size() < MAX_SIZE; })) {
            throw std::runtime_error("Too many requests, try again");
        }
        purchaseQueue_.push(std::move(request));
        not_empty_.notify_one();
    }

    // Worker pool sized for normal load (100 workers)
    void purchaseWorker() {
        while (true) {
            PurchaseRequest request;
            {
                std::unique_lock<std::mutex> lock(mutex_);
                not_empty_.wait(lock, [this] { return !purchaseQueue_.empty(); });
                request = std::move(purchaseQueue_.front());
                purchaseQueue_.pop();
                not_full_.notify_one();
            }
            // Process at normal rate - database, payment, inventory
            processPurchase(request);
        }
    }
};

/*
Bursty traffic shows up whenever load is unpredictable or event-driven.
News Site: Most hours see 1,000 page views per minute. Breaking news hits and you get 100,000 page views in one minute. 
The web servers enqueue page view events. Analytics workers process them at a steady rate. The queue absorbs the spike. 
Without it, your analytics database gets crushed and the whole site slows down.

Email Campaign: A company sends a marketing email to 1 million subscribers. Within minutes, 200,000 users click the link. 
Each click triggers backend work—logging the event, personalizing content, tracking conversions. The API enqueues click events.
Workers process them steadily. The queue prevents the spike from bringing down the tracking system.

Batch Job Completion: A nightly ETL job finishes processing 10 million records. It needs to send a completion notification 
for each one. Sending 10 million notifications at once would overwhelm your notification service. Instead, enqueue all 10 million. 
Workers send notifications at a controlled rate. The external service never sees the spike.

Webhooks: You receive webhook events from a payment provider. Normally you get 100 per minute. During a flash sale, you get 
10,000 in one minute. Your webhook handler enqueues events. Workers process them—update orders, send receipts, trigger fulfillment. 
The queue prevents the burst from causing database connection exhaustion.
*/