class FileHandle {
private:
    FILE* file;
    
public:
    // ACQUIRE resource in constructor
    FileHandle(const char* filename) {
        file = fopen(filename, "r");
        if (!file) throw std::runtime_error("Failed to open file");
    }
    
    // RELEASE resource in destructor (ALWAYS called)
    ~FileHandle() {
        if (file) {
            fclose(file);  // Automatic cleanup!
        }
    }
    
    FILE* get() { return file; }
};

// Usage
void processFile() {
    FileHandle fh("data.txt");  // File opened
    // Use file...
    fh.get()->read(...);
    
    // File AUTOMATICALLY closed when fh goes out of scope
    // Even if an exception is thrown!
}