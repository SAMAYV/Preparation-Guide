#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>

/*
Consider an email service. When a user signs up, you need to send them a welcome email. 
Connecting to the email server and sending the message takes 500ms. If you do this inline, 
every signup request takes half a second to respond. Users see a loading spinner and wonder 
if something broke. Instead, you hand off the email task and respond immediately. 
Background processing handles sending.
*/

struct EmailTask {
    std::string recipient;
    std::string templateName;
    std::string data;
};

class EmailService {
    std::queue<EmailTask> emailQueue_;
    std::mutex mutex_;
    std::condition_variable not_empty_;
    std::condition_variable not_full_;
    static constexpr size_t MAX_SIZE = 10000;

public:
    // API handler (producer)
    void signup(const std::string& email, const std::string& name) {
        // Fast: Save user to database
        userRepository.save(email, name);

        // Fast: Enqueue background work
        {
            std::unique_lock<std::mutex> lock(mutex_);
            not_full_.wait(lock, [this] { return emailQueue_.size() < MAX_SIZE; });
            emailQueue_.push({email, "welcome", name});
            not_empty_.notify_one();
        }

        // Return immediately - user sees instant response
    }

    // Worker thread (consumer)
    void emailWorker() {
        while (true) {
            EmailTask task;
            {
                std::unique_lock<std::mutex> lock(mutex_);
                not_empty_.wait(lock, [this] { return !emailQueue_.empty(); });
                task = std::move(emailQueue_.front());
                emailQueue_.pop();
                not_full_.notify_one();
            }
            // Slow: Connect to email server and send
            emailClient.send(task.recipient, task.templateName, task.data);
        }
    }
};

/*
Image Upload Service: Users upload profile photos. The photo needs resizing, compression, and upload to S3. 
This takes seconds. The upload API saves the original to a temp location, enqueues a processing task, and 
returns success immediately. Workers pull tasks, resize images, upload to S3, and update the database with the new URLs.

Payment Processing: A user completes checkout. You need to charge their card, send a receipt email, update 
inventory, and create a shipping label. These operations involve external services that are slow or can fail. 
Save the order, enqueue a fulfillment task, respond to the user. Workers handle the multi-step process. 
One failure doesn't block the whole flow.

Report Generation: An admin requests a monthly report with millions of rows. Generating it takes 10 minutes. 
The HTTP request times out after 30 seconds. Save a "pending" report record, enqueue a generation task, and 
return "Your report is being generated." Workers pull tasks, run the query, generate the CSV, upload to S3, 
and mark the report complete. The admin polls or gets notified when ready.
*/