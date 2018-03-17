#include <functional>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <set>

using Entries = std::vector<std::string>;

size_t doIt(const std::vector<std::pair<std::string, std::string>> &v, const Entries &e1, const Entries &e2) {

    size_t count = 0;
    for (size_t idx = 0; idx < v.size(); idx++) {
        const auto &p = v[idx];
        auto it1 = std::find(std::begin(e1), std::end(e1), p.first);
        if (&*it1 == &e1[idx])
           it1 = std::find(it1 + 1, std::end(e1), p.first);

        auto it2 = std::find(std::begin(e2), std::end(e2), p.second);
        if (&*it2 == &e2[idx])
            it2 = std::find(it2 + 1, std::end(e2), p.second);

        if (it1 != e1.end() && it2 != e2.end())
            count++;
    }
    return count;
}

int main(int argc, char **argv)
{
    size_t test_cases_count; 
    std::cin >> test_cases_count;

    for (size_t count = 1; count <= test_cases_count; count++) {
        size_t size;
        std::cin >> size;

        Entries e1, e2;
        std::vector<std::pair<std::string, std::string>> v;
        for (size_t idx = 0; idx < size; idx++) {
            std::string s1, s2;
            std::cin >> s1 >> s2;
            e1.push_back(s1);
            e2.push_back(s2);
            v.push_back(std::make_pair(s1, s2));
        }


        const auto &l = doIt(v, e1, e2);
        std::cout << "Case #" << count << ": " << l << std::endl;
    }
    return 0;
}

