#include "lib.h"

#include <iostream>
// #include <fstream>
// #include <sstream>
// #include <map>
// #include <vector>
// #include <iterator>
// #include <algorithm>


// using file_text = std::vector<std::string>;
// using ip_address = std::string;
// using ip_key = uint64_t;
// using ip_vector = std::vector<uint8_t>;
// using ip_list = std::multimap<ip_key, ip_address>;

/*
template<char delimiter>
class StringDelimiter : public std::string
{};

std::vector<std::string> splitLine(const std::string& text)
{
    std::istringstream iss(text);

    std::vector<std::string> results((std::istream_iterator<StringDelimiter<'\t'>>(iss)),
        std::istream_iterator<StringDelimiter<'\t'>>());

    return results;
}

std::vector<std::string> splitIp(const ip_address& ip)
{
    std::string ip_val;
    std::istringstream iss(ip);

    std::vector<std::string> result;

    while (std::getline(iss, ip_val, '.')) {
        result.push_back(ip_val);
    }

    return result;
}
*/

int main (int, char **)
{
    std::cout << "Allocator Version: " << version() << std::endl;

    return 0;
}
