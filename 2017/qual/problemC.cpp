#include <cstdlib>
#include <iostream>
#include <set>
#include <utility>

std::pair<size_t, size_t> f(size_t size, size_t personCount) {

    size_t zones = 1;

    while (zones <= personCount) {
        zones *= 2;
    }

    if (zones > 1)
        zones /= 2;

    size_t rem = personCount - (zones - 1);

    auto div = std::div((long long)(size - (zones - 1)), zones);

    if (div.rem >= rem) {

        auto dist = std::div((size_t)div.quot, 2);
        return std::make_pair(dist.rem ? dist.quot + 1 : dist.quot, dist.quot);
    } else {
    
        auto dist = std::div((size_t)div.quot - 1, 2);
        return std::make_pair(dist.rem ? dist.quot + 1 : dist.quot, dist.quot);
    }
}

int main(int argc, char **argv)
{
    size_t test_cases_count; 
    std::cin >> test_cases_count;

    for (size_t count = 1; count <= test_cases_count; count++) {
        size_t size, personCount;
        std::cin >> size >> personCount;
        auto r = f(size, personCount);
        std::cout << "Case #" << count << ": " << r.first << " " << r.second << std::endl;
    }
    return 0;
}
