#pragma once

#include <iostream>
#include <memory>

template <typename T>
struct node {
  T data;
  node *next;
};

template <typename T,typename Allocator = std::allocator<T>>
class MyPrettyList {

public:    
    using value_type = T;
    using size_type = size_t;

    MyPrettyList() : head(nullptr), tail(nullptr) 
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
            delete tmp;
        }
    }

    // Modifier
    void push_back(T const& item)
    {
        node<T> *n = new node<T>();   
        n->data = item;
        n->next = nullptr;

        tail = n;

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
    
    // using iterator = node<T>*;
    // using const_iterator = const node<T>*;

    template < bool CONST > struct iterator_impl ;

    using iterator = iterator_impl<false>;
    iterator begin() { return iterator{head} ; }
    iterator end() { return iterator{nullptr} ; }

    using const_iterator = iterator_impl<true> ;
    const_iterator begin() const { return const_iterator{head} ; }
    const_iterator end() const { return const_iterator{nullptr} ; }
    const_iterator cbegin() const { return begin() ; }
    const_iterator cend() const { return end() ; }

    /*
    iterator begin() 
    {
#ifdef LOG_LIST
        std::string st = "nullptr";
        if (head) {
            st = std::to_string(head->data);
        }
        std::cout << "iterator begin() data = " << st << std::endl;
#endif 
        return head;
    }
    const_iterator begin() const 
    {
#ifdef LOG_LIST
        std::string st = "nullptr";
        if (head) {
            st = std::to_string(head->data);
        }
        std::cout << "const iterator begin() data = " << st << std::endl;
#endif 
        return head;
    }

    iterator end() 
    {
#ifdef LOG_LIST
        std::string st = "nullptr";
        if (tail) {
            st = std::to_string(tail->data);
        }
        std::cout << "iterator end() data = " << st << std::endl;
#endif 
        return tail->next;
    }
    const_iterator end() const 
    {
#ifdef LOG_LIST
        std::string st = "nullptr";
        if (tail) {
            st = std::to_string(tail->data);
        }
        std::cout << "const iterator end() data = " << st << std::endl;
#endif 
        return tail->next;
    }
    */
private:
    /*
    struct node {
        value_type val;
        node *next;

        node(T const& val, node* next) : val(val), next(next) {}

        node(T&& val, node* next) : val(val), next(next) {}
    };
    */
    node<T> *head = nullptr;
    node<T> *tail = nullptr;

    //Memory management
    // std::allocator<T> alloc;

public:

    template < bool IS_CONST > struct iterator_impl
        {
            using value_type = typename std::conditional< IS_CONST, const T, T >::type ;

            explicit iterator_impl( node<T>* n ) : curr(n) {}

            value_type& operator* () { return /*curr->value*/ curr->data ; }
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

    

// void push_back(T const& item);

/*
template <typename T,typename Allocator>
MyPrettyList<T>::MyPrettyList() {
}

template <typename T,typename Allocator>
MyPrettyList<T>::~MyPrettyList() {
    node* tmp;
    while(head* != nullptr) {
        tmp = head;
        head = head->next;
        delete tmp;
    }
}
*/
/*
template <typename T>
MyPrettyList <T>::~MyPrettyList() {
    node* tmp;
    while(head) {
        tmp = head;
        head = head->next;
        delete tmp;
    }
}
*/