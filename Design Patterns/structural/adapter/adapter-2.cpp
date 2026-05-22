class WebRequestor {
    public:
    // Accepts object
    virtual int request(Object object) = 0;
};

class Adapter : public WebRequestor {
    WebService webService;
    public:
    void connect(WebService webService) {
        this->webService = webService;
    }
    int request(Object object) {
        Json json = this->convertToJSON(object);
        Json response = webService->request(json);
        if (response != NULL) return 200;
        else return 500;
    }
    Json convertToJSON(Object object) {
        // convert to JSON
    }
};

// Adaptee (accepts JSON)
class WebService {
    public:
    WebService(String webHost) {
        this->webHost = webHost;
    }
    int request(Json json) {
        // send request
        // return response
        return 200;
    }
};

class WebClient {
    WebRequestor* webRequestor;
    public:
    WebClient(WebRequestor* webRequestor) {
        this->webRequestor = webRequestor;
    }
    void doWork() {
        int status = webRequestor->request(makeObject());
        if (status == 200)  cout << "Request successful" << endl;
        else cout << "Request failed" << endl;
    }
    Object makeObject() {
        // make object
    }
};

void main() {
    // Adaptee
    String webHost = "Host: https://google.com";
    WebService* webService = new WebService(webHost);

    // Adapter
    WebRequestor* adapter = new Adapter();
    adapter->connect(webService);

    // Client
    WebClient* webClient = new WebClient(adapter);
    webClient->doWork();

    return 0;
}