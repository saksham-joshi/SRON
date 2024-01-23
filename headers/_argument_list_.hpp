#include "_datatypes_.hpp"

class Argument_List {
private:
    Any** array;
    size_t size;

public:
    Argument_List() : array(nullptr), size(0) {
        array = reinterpret_cast<Any**>(calloc(1, sizeof(Any*)));
        if(!array){
            DISPLAY_EXCEPTION("allocating a memory to call a function.",SystemOutofMemoryException);
        }
    }

    ~Argument_List() {
        free(array);
    }

    Any* operator[](size_t index) const {
        if (index < size) {
            return array[index];
        } else {
            DISPLAY_EXCEPTION("extracting the passed arguments.",IndexNotWithinRange);
            return nullptr;
        }
    }

    inline void PUT(Any* arg) {
        try{
            size++;
            array = reinterpret_cast<Any**>(realloc(array, size * sizeof(Any*)));
            array[size - 1] = arg;
        }
        catch(const std::exception&){
            DISPLAY_EXCEPTION("calling a function.",SystemOutofMemoryException);
        }
    }

    inline void CLEAR(){
        array = NULL;
        size = 0;
    }

    inline size_t LEN(){
        return size;
    }
};