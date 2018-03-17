#include <array>
#include <iostream>
#include <cstdlib>


bool seenAll(const std::array<bool, 10> &seen) {
    for (const auto &b : seen)
        if (!b) return false;
    return true;
}

void update(std::array<bool, 10> &seen, size_t N) {
    while (N > 0) {
        auto div = std::div(N, 10);
        seen[div.rem] = true;
        N = div.quot;
    }
}

size_t last(size_t N) {
    if (N == 0) return 0;

    size_t sum = N;   
    std::array<bool, 10> seen = { false, false, false, false, false, false, false, false, false, false };

    update(seen, sum);
    while (!seenAll(seen)) {
        sum += N;
        update(seen, sum);
    }

   return sum;
}


int main(int argc, char **argv)
{
    size_t test_cases_count; 
    std::cin >> test_cases_count;

    for (size_t count = 1; count <= test_cases_count; count++) {
        size_t value;
        std::cin >> value;
        const auto &l = last(value);
        if (l)
            std::cout << "Case #" << count << ": " << l << std::endl;
        else
            std::cout << "Case #" << count << ": " << "INSOMNIA" << std::endl;
    }
    return 0;
}
