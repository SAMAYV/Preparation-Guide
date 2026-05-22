#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <functional>
#include <atomic>
using namespace std;

/*
The C++ implementation shows the underlying machinery: a queue protected by a mutex, a condition variable for efficient waiting, 
and a dedicated thread running the message loop. This is exactly what blocking queues do internally, exposed here to show the mechanics.

Multiple threads can send messages to the same actor, hence need synchronization during send calls.
*/

template<typename T>
class Actor {
private:
    queue<T> mailbox_;
    mutex mutex_;
    condition_variable cv_;
    atomic<bool> running_{true};
    thread thread_;

public:
    // Actor() : thread_([this] { run(); }) {}
    Actor() {
        this->thread_ = thread([this] { this->run(); });
    }

    void send(T message) {
        lock_guard<mutex> lock(mutex_);
        mailbox_.push(move(message));
        cv_.notify_one();
    }

    void stop() {
        running_ = false;
        cv_.notify_one();
        thread_.join();
    }

protected:
    virtual void onReceive(T message) = 0;

private:
    void run() {
        while (running_) {
            unique_lock<mutex> lock(mutex_);
            cv_.wait(lock, [this] { return !mailbox_.empty() || !running_; });
            if (!running_ && mailbox_.empty()) break;
            T message = move(mailbox_.front());
            mailbox_.pop();
            lock.unlock();
            onReceive(move(message));
        }
    }
};

struct EmailRequest {
    string to;
    string subject;
    string body;
};

class EmailActor : public Actor<EmailRequest> {
private:
    EmailClient client_;
protected:
    void onReceive(EmailRequest request) override {
        client_.send(request.to, request.subject, request.body);
    }
};

// Usage: no shared state, no locks needed
class SignupHandler {
private:
    EmailActor emailActor_;
    UserRepository& userRepository_;
public:
    void handleSignup(const SignupRequest& request) {
        User user = userRepository_.save(User{request.email});
        // Send message to actor - returns immediately
        emailActor_.send(EmailRequest{
            user.email,
            "Welcome!",
            "Thanks for signing up..."
        });
    }
};
