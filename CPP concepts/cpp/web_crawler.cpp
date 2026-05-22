// This is the HtmlParser's API interface.
// You should not implement it, or speculate about its implementation
class HtmlParser {
    public:
    vector<string> getUrls(string url);
};

// Time:  O(|V| + |E|)
// Space: O(|V|)
class Solution {
public:
    vector<string> crawl(string startUrl, HtmlParser htmlParser) {
        unseen_urls.emplace(startUrl);
        unordered_set<string> already_seen_urls = {startUrl};
        vector<thread> workers;
        // Create workers
        for (int i = 0; i < NUMBER_OF_WORKERS; ++i) {
            workers.emplace_back(bind(&Solution::worker, this, &htmlParser, &already_seen_urls));
        }
        // Condition to terminate workers
        {
            unique_lock<mutex> lock{m_};
            cv_.wait(lock, [this]() { return unseen_urls.empty() && !processing_url_count; });
            // Push empty strings to stop workers (poison pill pattern)
            for (const auto& t : workers) {
                unseen_urls.emplace();
            }
            cv_.notify_all();
        }
        for (auto& t : workers) {
            t.join();
        }
        return vector<string>(already_seen_urls.cbegin(), already_seen_urls.cend());
    }

private:
    static const int NUMBER_OF_WORKERS = 4;
    queue<string> unseen_urls;
    int processing_url_count = 0;
    mutex m_;
    condition_variable cv_;
    
    void worker(HtmlParser *htmlParser, unordered_set<string> *already_seen_urls) {
        while (true) {
            string from_url;
            // Worker fetches a URL from the queue
            {
                unique_lock<mutex> lock{m_};
                cv_.wait(lock, [this]() { return !unseen_urls.empty(); });
                from_url = unseen_urls.front(); 
                unseen_urls.pop();
                if (from_url.empty()) {
                    break;
                }
                ++processing_url_count;
            }
            const auto& name = hostname(from_url);
            // Worker fetches all neighbor URLs and pushes new ones to the queue
            for (const auto& to_url: htmlParser->getUrls(from_url)) {
                if (name != hostname(to_url)) {
                    continue;
                }
                unique_lock<mutex> lock{m_};
                if (!already_seen_urls->count(to_url)) {
                    already_seen_urls->emplace(to_url);
                    unseen_urls.emplace(to_url);
                    cv_.notify_all();
                }
            }
            // Worker has parsed the URL
            {
                unique_lock<mutex> lock{m_};
                --processing_url_count;
                // All all URLs have been processed
                if (unseen_urls.empty() && !processing_url_count) {
                    cv_.notify_all();
                }
            }
        }
    }
    
    string hostname(const string& url) {
        static const string scheme = "http://";
        return url.substr(0, url.find('/', scheme.length()));
    }
};