#include <iostream>
#include <memory>
using namespace std;

struct Sample {
    Sample() {
        cout << "CONSTRUCTOR\n";
    }
    ~Sample() {
        cout << "DESTRUCTOR\n";
    }
};

// function that calls the delete [] on received pointer
void deleter(Sample* x) {
    cout << "DELETER FUNCTION CALLED\n";
    delete[] x;
}

class Deleter {
public:
    void operator()(Sample* x) {
        cout << "DELETER FUNCTION CALLED\n";
        delete[] x;
    }
};

int main()
{
    // Creating a shared+ptr with custom deleter
    shared_ptr<Sample> p3(new Sample[12], deleter);

    // Function Object as deleter
    shared_ptr<Sample> p3(new Sample[12], Deleter());
    
    // Lambda function as deleter
    shared_ptr<Sample> p4(new Sample[12], [](Sample* x){
        cout << "DELETER FUNCTION CALLED\n";
        delete[] x;
    });
    return 0;
}