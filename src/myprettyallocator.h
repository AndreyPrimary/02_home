#pragma once

#include <iostream>
#include <memory>

template <typename T, int S = 10>
struct MyPrettyAllocator {
    using value_type = T;
    std::size_t allocated_size;
    std::size_t reserv_size = S;
    char* pMemory = nullptr;

    MyPrettyAllocator() noexcept;

    ~MyPrettyAllocator();

    template <typename U> MyPrettyAllocator (const MyPrettyAllocator<U>&) noexcept;

    std::size_t max_size() const noexcept;

    T* allocate (std::size_t n);

    void deallocate (T* p, std::size_t n);

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args);

    void destroy(T *p);

    template<class U>
    struct rebind {
        using other = MyPrettyAllocator<U, S>;
    };
};

template <class T, class U>
constexpr bool operator== (const MyPrettyAllocator<T>&, const MyPrettyAllocator<U>&) noexcept;

template <class T, class U>
constexpr bool operator!= (const MyPrettyAllocator<T>&, const MyPrettyAllocator<U>&) noexcept;

// ----------------------

template <typename T, int S>
MyPrettyAllocator<T,S>::MyPrettyAllocator() noexcept 
    : allocated_size(0), reserv_size(S) {
}

template <typename T, int S>
MyPrettyAllocator<T,S>::~MyPrettyAllocator() {
    if (pMemory != nullptr) {
        std::free(pMemory);
        pMemory = nullptr;
    }    
}

template <typename T, int S>
template <typename U>
MyPrettyAllocator<T,S>::MyPrettyAllocator(const MyPrettyAllocator<U>& ) noexcept 
    : allocated_size(0) {
}

template <typename T, int S>
std::size_t MyPrettyAllocator<T,S>::max_size() const noexcept {
    return reserv_size;
}

template <typename T, int S>
T* MyPrettyAllocator<T,S>::allocate (std::size_t n) {
#ifdef LOG_ALLOC    
    #ifndef USE_PRETTY
            std::cout << "allocate: [n = " << n << "]" << std::endl;
    #else
            std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
    #endif
#endif

    if (allocated_size == 0) {
#ifdef LOG_ALLOC    
    #ifndef USE_PRETTY
            std::cout << "malloc memory element: [" << reserv_size << "]" << std::endl;
    #else
            std::cout << __PRETTY_FUNCTION__ << "malloc memory element: [" << reserv_size << "]"  std::endl;
    #endif
#endif
        pMemory = reinterpret_cast<char*> (std::malloc(reserv_size * sizeof(T))); 

        if (!pMemory)
            throw std::bad_alloc();
    }

    auto p = pMemory + allocated_size * sizeof(T);
    allocated_size += n;

    if (allocated_size > reserv_size) {
        throw std::bad_alloc();        
    }

	// auto p = std::malloc(n * sizeof(T));
	// if (!p)
	// 	throw std::bad_alloc();

	return reinterpret_cast<T *>(p);
}

template <typename T, int S>
void MyPrettyAllocator<T,S>::deallocate ([[maybe_unused]] T* p, [[maybe_unused]] std::size_t n) {
#ifdef LOG_ALLOC
    #ifndef USE_PRETTY
            std::cout << "deallocate: [n  = " << n << "] " << std::endl;
    #else
            std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
    #endif
#endif   
    allocated_size -= n;

    if (allocated_size <= 0) {
#ifdef LOG_ALLOC    
    #ifndef USE_PRETTY
            std::cout << "free memory element: [" << reserv_size << "]" << std::endl;
    #else
            std::cout << __PRETTY_FUNCTION__ << "free memory element: [" << reserv_size << "]"  std::endl;
    #endif
#endif
        std::free(pMemory);
        pMemory = nullptr;
    }
}

template <typename T, int S>
template<typename U, typename ...Args>
void MyPrettyAllocator<T,S>::construct(U *p, Args &&...args) {
#ifdef LOG_ALLOC
    #ifndef USE_PRETTY
        std::cout << "construct" << std::endl;
    #else
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    #endif
#endif
    new(p) U(std::forward<Args>(args)...);
}

template <typename T, int S>
void MyPrettyAllocator<T,S>::destroy(T *p) {
#ifdef LOG_ALLOC
    #ifndef USE_PRETTY
        std::cout << "destroy" << std::endl;
    #else
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    #endif
#endif
    p->~T();
}

// template <typename T, typename U>
// struct MyPrettyAllocator<U>::rebind {
//     typedef MyPrettyAllocator<U> other;
// };  

template <class T, class U>
constexpr bool operator== (const MyPrettyAllocator<T>&, const MyPrettyAllocator<U>&) noexcept {
	return false;
}

template <class T, class U>
constexpr bool operator!= (const MyPrettyAllocator<T>&, const MyPrettyAllocator<U>&) noexcept {
	return false;
}


// template <typename T>
// struct MyPrettyAllocator<T, 10>;

