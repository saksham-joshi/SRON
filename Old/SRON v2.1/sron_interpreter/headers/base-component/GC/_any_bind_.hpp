

#include "_garbage_collector_.hpp"

inline AnyBind::AnyBind(AnyBind &__binder)
{

    if (this != &__binder)
    {

        this->ptr_ = __binder.ptr_;
        this->layer_ = __binder.layer_;

        __binder.ptr_ = nullptr;
        
    }
}

inline AnyBind::AnyBind(AnyPtr __ptr, GcSize_t __layer)
{
    this->ptr_ = __ptr;
    this->layer_ = __layer;

}

inline AnyBind& AnyBind::operator=(AnyBind& __other)
{
    if(this != &__other){

        this->ptr_ = __other.ptr_;
        this->layer_ = __other.layer_;

        __other.ptr_ = nullptr;

    }
    return *this;
}

inline AnyBind::AnyBind(AnyBind &&__rhs)
{

    if (this != &__rhs)
    {
        this->ptr_ = __rhs.ptr_;
        this->layer_ = __rhs.layer_;

        __rhs.ptr_ = nullptr;
        
    }
}

inline Any &AnyBind::operator*() { if(this->ptr_ == nullptr){ throw NullPointerException(); } return *ptr_; }

inline AnyPtr AnyBind::operator->() { if(this->ptr_ == nullptr){ throw NullPointerException(); }  return this->ptr_; }

inline AnyBind::~AnyBind() noexcept { delete this->ptr_; }



struct ExceptionThrowByUser {

    private :
        StringPtr ptr;

    public :
        inline ExceptionThrowByUser(StringPtr __ptr) : ptr(__ptr) { }

        inline void DISPLAY_EXCEPTION() const{
            ptr->PRINT();
            std::cout << " caught:\n    ";
            LOAD_FILE_AND_PRINT((**ptr).c_str());
        }

};
