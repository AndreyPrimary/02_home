#pragma once

#include <iostream>
#include <memory>

template <typename T>
struct MyPrettyAllocator {
  using value_type = T;
  std::size_t allocated_size;
  std::size_t reserv_size;
  char* pMemory = nullptr;

  MyPrettyAllocator(std::size_t reserv_size = 10) noexcept;

  ~MyPrettyAllocator();

  template <typename U> MyPrettyAllocator (const MyPrettyAllocator<U>&) noexcept;

  std::size_t max_size() const noexcept;

  T* allocate (std::size_t n);
  
  void deallocate (T* p, std::size_t n);

  template<typename U, typename ...Args>
    void construct(U *p, Args &&...args);

  void destroy(T *p);
};

template <class T, class U>
constexpr bool operator== (const MyPrettyAllocator<T>&, const MyPrettyAllocator<U>&) noexcept;

template <class T, class U>
constexpr bool operator!= (const MyPrettyAllocator<T>&, const MyPrettyAllocator<U>&) noexcept;

// ----------------------

template <typename T>
MyPrettyAllocator<T>::MyPrettyAllocator(std::size_t reserv_size) noexcept 
    : allocated_size(0), reserv_size(reserv_size) {
}

template <typename T>
MyPrettyAllocator<T>::~MyPrettyAllocator() {
    if (pMemory != nullptr) {
        std::free(pMemory);
        pMemory = nullptr;
    }    
}

template <typename T>
template <typename U>
MyPrettyAllocator<T>::MyPrettyAllocator(const MyPrettyAllocator<U>& ) noexcept 
    : allocated_size(0) {
}

template <typename T>
std::size_t MyPrettyAllocator<T>::max_size() const noexcept {
    return reserv_size;
}

template <typename T>
T* MyPrettyAllocator<T>::allocate (std::size_t n) {
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

template <typename T>
void MyPrettyAllocator<T>::deallocate ([[maybe_unused]] T* p, [[maybe_unused]] std::size_t n) {
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

template <typename T>
template<typename U, typename ...Args>
void MyPrettyAllocator<T>::construct(U *p, Args &&...args) {
#ifdef LOG_ALLOC
    #ifndef USE_PRETTY
        std::cout << "construct" << std::endl;
    #else
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    #endif
#endif
    new(p) U(std::forward<Args>(args)...);
}

template <typename T>
void MyPrettyAllocator<T>::destroy(T *p) {
#ifdef LOG_ALLOC
    #ifndef USE_PRETTY
        std::cout << "destroy" << std::endl;
    #else
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    #endif
#endif
    p->~T();
}

template <class T, class U>
constexpr bool operator== (const MyPrettyAllocator<T>&, const MyPrettyAllocator<U>&) noexcept {
	return false;
}

template <class T, class U>
constexpr bool operator!= (const MyPrettyAllocator<T>&, const MyPrettyAllocator<U>&) noexcept {
	return false;
}


