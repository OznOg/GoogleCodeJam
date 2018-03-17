#include <functional>
#include <iostream>
#include <set>
#include <string>

std::string lastWord(const std::string &s) {
    std::string res;
    for (auto &c : s) {
        if (res.empty() || c < res[0])
            res.append(1, c);
        else
            res = std::string(1, c) + res;
    }

    return res;
}

int main(int argc, char **argv)
{
    size_t test_cases_count; 
    std::cin >> test_cases_count;

    for (size_t count = 1; count <= test_cases_count; count++) {
        std::string s;
        std::cin >> s;
        const auto &l = lastWord(s);
        std::cout << "Case #" << count << ": " << l << std::endl;
    }
    return 0;
}

