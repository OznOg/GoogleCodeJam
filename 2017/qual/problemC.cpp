#include <cstdlib>
#include <iostream>
#include <set>
#include <utility>

struct Compare {
    bool operator()(const size_t &lhs, const size_t &rhs) const 
    {
        return lhs > rhs;
    }
};

using Zones = std::multiset<size_t, Compare>;

std::pair<size_t, size_t> f(const Zones &zones, size_t personCount/* kinda depth?*/) {

    if (zones.size() < personCount) {
        Zones sub_zones;
        for (const auto &z : zones) {
                auto div = std::div(z, 2);
                sub_zones.insert(div.rem == 0 && div.quot != 0 ? div.quot - 1 : div.quot);
                sub_zones.insert(div.quot); 
                personCount--;
        }
        return f(sub_zones, personCount);
    }

    size_t max, min;
    for (const auto &z : zones) {
        auto div = std::div(z, 2);
        max = div.quot;
        min = (div.rem == 0 && div.quot != 0 ? div.quot - 1 : div.quot);
        personCount--;
        if (personCount == 0)
            break;
    }
    return std::make_pair(max, min);
}

int main(int argc, char **argv)
{
    size_t test_cases_count; 
    std::cin >> test_cases_count;

    for (size_t count = 1; count <= test_cases_count; count++) {
        size_t size, personCount;
        std::cin >> size >> personCount;
        Zones v = { size };
        auto r = f(v, personCount);
        std::cout << "Case #" << count << ": " << r.first << " " << r.second << std::endl;
    }
    return 0;
}
