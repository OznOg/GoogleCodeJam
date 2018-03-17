#include <array>
#include <iostream>
#include <cstdlib>


bool seenAll(const std::array<bool, 10> &seen) {
    for (const auto &b : seen)
        if (!b) return false;
    return true;
}

bool isClean(size_t N) {
    size_t last = 9;
    while (N > 0) {
        auto div = std::div(N, 10);
        if (div.rem > last)
            return false;
        else
            last = div.rem;
        N = div.quot;
    }
    return true;
}

size_t lastClean(size_t N) {
    while (!isClean(N))
        N--;

   return N;
}


int main(int argc, char **argv)
{
    size_t test_cases_count; 
    std::cin >> test_cases_count;

    for (size_t count = 1; count <= test_cases_count; count++) {
        size_t value;
        std::cin >> value;
        std::cout << "Case #" << count << ": " << lastClean(value) << std::endl;
    }
    return 0;
}
