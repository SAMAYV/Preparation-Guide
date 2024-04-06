class MemoryPool {
private:
    void * pos[10];
    int itr = 9; // Stack top

public:
    void * allocate(size_t size) {
        if (pos[itr] == NULL, 0)
            pos[itr] = malloc(size);
        return pos[itr--]; 
    }

    MemoryPool(){
        for (int i = 0; i < 10; i++)
            pos[i] = NULL;
    }

    void deallocate(void* ptr) {
        pos[++itr] = ptr; 
    }
};

MemoryPool pool;
class A{
public:
    void* operator new(size_t size){
        return pool.allocate(size);
    }

    void operator delete(void * p) {
        pool.deallocate(p);
    }
};