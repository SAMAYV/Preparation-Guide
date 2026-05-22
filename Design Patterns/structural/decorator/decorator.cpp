class WebPage {
    public:
    virtual void display() = 0;
};

class BasicWebPage : public WebPage {
    string html, css, js;
    public:
    BasicWebPage(string html, string css, string js) {
        this->html = html;
        this->css = css;
        this->js = js;
    }
    void display() {
        cout << "Displaying basic web page" << endl;
    }
};

class WebPageDecorator : public WebPage {
    WebPage* page;
    public:
    WebPageDecorator(WebPage* page) {
        this->page = page;
    }
    void display() {
        this->page->display();
    }
};

class AuthorizationDecorator : public WebPageDecorator {
    public:
    AuthorizationDecorator(WebPage* page) : WebPageDecorator(page) {}
    void authorizeUser() {
        cout << "Checking authorization" << endl;
    }
    void display() {
        this->page->display();
        this->authorizeUser();
    }
};

class AuthenticationDecorator : public WebPageDecorator {
    public:
    AuthenticationDecorator(WebPage* page) : WebPageDecorator(page) {}
    void authenticateUser() {
        cout << "Checking authentication" << endl;
    }
    void display() {
        // Display the other decorators
        this->page->display();
        this->authenticateUser();
    }
};

int main() {
    WebPage* page = new BasicWebPage("html", "css", "js");
    page = new AuthenticationDecorator(page);
    page = new AuthorizationDecorator(page);
    page->display();
    return 0;
}
