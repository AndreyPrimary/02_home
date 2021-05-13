#include "lib.h"

#define LOG_ALLOC
#define LOG_LIST

#include <iostream>
// #include <fstream>
// #include <sstream>
#include <map>
#include <vector>
// #include <iterator>
// #include <algorithm>

#include "myprettyallocator.h"
#include "myprettylist.h"


template <int N>
struct Factorial 
{
    enum { value = N * Factorial<N - 1>::value };
};

template <>
struct Factorial<0> 
{
    enum { value = 1 };
};


class A1 
{
public:

    struct some_struct
    {
        int i;
        char ch[3];
    };
};


void testCommon()
{
    std::vector<A1::some_struct, std::allocator<A1::some_struct>> v1;

    v1.reserve(100);

    std::vector<int, MyPrettyAllocator<int>> myAllocVector;

    myAllocVector.push_back(1);

    for (const auto val : myAllocVector) {
        std::cout << val << std::endl;
    }

    std::map<int, std::string, std::less<int>, MyPrettyAllocator<std::pair<const int, std::string>> > myAllocMap;

    for (int n = 0; n < 10; n++) {
        myAllocMap[n] = std::string("Line") + std::to_string(n);
    }

    for (const auto &val : myAllocMap) {
        std::cout << val.first << "|" << val.second << std::endl;
    }

}

void testCommonList()
{
    MyPrettyList<int> myList;

    myList.push_back(1);
    myList.push_back(2);
    myList.push_back(3);

    for (const auto val : myList) {
        std::cout << val << std::endl;
    }
}


void testAllocOutOfMaxSize()
{
    std::cout << "std::vector<int, MyPrettyAllocator<int> > out of max size" << std::endl;

    std::vector<int, MyPrettyAllocator<int> > myAllocVector;
    int                 fact = 1;

    myAllocVector.reserve(10);

    for (int n = 0; n < 11; n++) {
        fact = fact * (n + 1);
        myAllocVector.push_back(fact);
    }

    for (const auto &val : myAllocVector) {
        std::cout << val << std::endl;
    }
}

// -создание экземпляра std::map<int, int>
// -заполнение 10 элементами, где ключ-это число от 0 до 9, а значение -факториал ключа
void testStdMap()
{
    std::cout << "std::map<int, int>" << std::endl;

    std::map<int, int>  stdMap;
    int                 fact = 1;

    for (int n = 0; n < 10; n++) {
        fact = fact * (n + 1);
        stdMap[n] = fact;
    }

    for (const auto &val : stdMap) {
        std::cout << val.first << " " << val.second << std::endl;
    }
}

// -создание  экземпляра std::map<int,  int>с  новым  аллокатором,ограниченным10 элементами
// -заполнение 10 элементами, где ключ-это число от 0 до 9, а значение -факториал ключа
// -вывод на экран всех значений (ключ и значение разделены пробелом) хранящихся в контейнере
void testAllocMap()
{
    std::cout << "std::map<int, int, std::less<int>, MyPrettyAllocator<std::pair<const int, int>> >" << std::endl;

    std::map<int, int, std::less<int>, MyPrettyAllocator<std::pair<const int, int>> > myAllocMap;
    int                 fact = 1;

    for (int n = 0; n < 10; n++) {
        fact = fact * (n + 1);
        myAllocMap[n] = fact;
    }

    for (const auto &val : myAllocMap) {
        std::cout << val.first << " " << val.second << std::endl;
    }
}

void testAllocVectorWithReserv()
{
    std::cout << "std::vector<int, MyPrettyAllocator<int> > with reserve" << std::endl;

    std::vector<int, MyPrettyAllocator<int> > myAllocVector;
    int                 fact = 1;

    myAllocVector.reserve(10);

    for (int n = 0; n < 10; n++) {
        fact = fact * (n + 1);
        myAllocVector.push_back(fact);
    }

    for (const auto &val : myAllocVector) {
        std::cout << val << std::endl;
    }
}

// -создание экземпляра своего контейнера для хранения значений типа int
// -заполнение 10 элементами от 0 до 9
void testPrettyList()
{
    std::cout << "MyPrettyList<int>" << std::endl;

    MyPrettyList<int> myAllocList;
    int                 fact = 1;

    for (int n = 0; n < 10; n++) {
        fact = fact * (n + 1);
        myAllocList.push_back(fact);
    }

    for (const auto &val : myAllocList) {
        std::cout << val << std::endl;
    }
}

// -создание экземпляра своего контейнера для хранения значений типа int с новым аллокатором,ограниченным 10 элементами
// -заполнение 10 элементами от 0 до 9
// -вывод на экран всех значений,хранящихся в контейнере
void testAllocPrettyList()
{
    std::cout << "MyPrettyList<int, MyPrettyAllocator<int> >" << std::endl;

    MyPrettyList<int, MyPrettyAllocator<int> > myAllocMap;
    int                 fact = 1;

    for (int n = 0; n < 10; n++) {
        fact = fact * (n + 1);
        myAllocMap.push_back(fact);
    }

    for (const auto &val : myAllocMap) {
        std::cout << val << std::endl;
    }
}

int main (int, char **)
{
    
    std::cout << "Allocator Version: " << version() << std::endl;

    // testCommon();
    // testCommonList();
    // testAllocOutOfMaxSize(); // должна быть ошибка

    testStdMap();
    testAllocMap();
    testAllocVectorWithReserv();
    testPrettyList();
    testAllocPrettyList();

    return 0;
}
