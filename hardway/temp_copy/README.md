**Problem**

We want to test if we assign map to local variable - deep copy constructor will be called.

    void doSomething(std::map<int, int> var) {
        std::map<int, int> local;
        local = var;
    }
