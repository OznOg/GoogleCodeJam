#include <iostream>
#include <string>
#include <vector>

using panCake = bool;

size_t f(const std::vector<bool> &v) {
    size_t count = 0;
    auto last = v.front();
    for (const auto &b : v) {
        if (b != last) {
            last = b;
            count++;
        }
    }
    if (!last) 
        count++;
    return count;
}

int main(int argc, char **argv)
{
    size_t test_cases_count; 
    std::cin >> test_cases_count;

    for (size_t count = 1; count <= test_cases_count; count++) {
        std::string asciiStack;
        std::cin >> asciiStack;
        std::vector<bool> pancakesStack;
        for (const auto &c : asciiStack)
            pancakesStack.push_back(c == '+');
        std::cout << "Case #" << count << ": " << f(pancakesStack) << std::endl;
    }
    return 0;
}
