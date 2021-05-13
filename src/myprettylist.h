#pragma once

#include <iostream>
#include <memory>

template <typename T>
struct node {
//   T data;
  T* data;
  node *next;
};

template <typename T,typename Allocator = std::allocator<T>>
class MyPrettyList {

public:    
    using value_type = T;
    using size_type = size_t;
    using allocator_type = Allocator;

    MyPrettyList() : head(nullptr)//, tail(nullptr) 
    {
#ifdef LOG_LIST
        std::cout << "constructor MyPrettyList" << std::endl;
#endif 
    };

    ~MyPrettyList()
    {
#ifdef LOG_LIST
        std::cout << "destructor MyPrettyList" << std::endl;
#endif 
        node<T>* tmp;

        while(head) {
            tmp = head;
            head = head->next;
            alloc.destroy(tmp->data);
            alloc.deallocate (tmp->data, 1);
            delete tmp;
        }
    }

    // Modifier
    void push_back(T const& item)
    {
        node<T> *n = new node<T>();   
        n->data = alloc.allocate(1);
        alloc.construct(n->data, item);

        // n->data = item;
        n->next = nullptr;

        // tail = n;

        node<T>* last = head;

        if (last == nullptr) {
            head = n;
        } else {
            while(last->next) {
                last = last->next;
            }
            last->next = n;
        }
    }

    // iterator
    
    template < bool CONST > struct iterator_impl ;

    using iterator = iterator_impl<false>;
    iterator begin() { return iterator{head} ; }
    iterator end() { return iterator{nullptr} ; }

    using const_iterator = iterator_impl<true> ;
    const_iterator begin() const { return const_iterator{head} ; }
    const_iterator end() const { return const_iterator{nullptr} ; }
    const_iterator cbegin() const { return begin() ; }
    const_iterator cend() const { return end() ; }

    node<T> *head = nullptr;
    // node<T> *tail = nullptr;

    //Memory management
    allocator_type alloc;

public:

    template < bool IS_CONST > struct iterator_impl
        {
            using value_type = typename std::conditional< IS_CONST, const T, T >::type ;

            explicit iterator_impl( node<T>* n ) : curr(n) {}

            value_type& operator* () { return /*curr->value*/ *curr->data ; }
            value_type& operator-> () { return std::addressof(**this) ; }

            iterator_impl& operator++ () { curr = curr->next ; return *this ; }
            iterator_impl operator++ (int) { const auto pv = *this ; ++*this ; return pv ; }

            bool operator== ( const_iterator that ) const { return curr == that.curr ; }
            bool operator!= ( const_iterator that ) const { return !( *this == that ) ; }

            // provide for implicit conversion from iterator to const_iterator
            operator const_iterator () const { return const_iterator{curr} ; }

            private: node<T>* curr ;

            friend iterator ; // give iterator access to const_iterator::curr
        };
      
};

// ---------------------------

    



