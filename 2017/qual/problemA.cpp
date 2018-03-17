#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>


#include <experimental/optional>

namespace std {
    /* XXX keep this as long as optional is experimental */
    template <class T>
    using optional = experimental::optional<T>;
    #define make_optional experimental::make_optional
};


bool allHappy(const std::vector<bool> &v) {
    for (auto b : v)
        if (!b)
            return false;
    return true;
}


std::vector<bool> flip(std::vector<bool> &v, size_t size, size_t idx) {
    for (size_t i = 0; i < size; i++)
        v[idx + i] = !v[idx + i];

    return v;
}

std::optional<size_t> find(std::vector<bool> &v, size_t size, size_t first_idx = 0, size_t flip_count = 0) {

    size_t min = 0;
    for (size_t i = 0; i < v.size() - size + 1; i++) {
        if (v[i])
            continue;
        flip(v, size, i);
        min++;
        if (allHappy(v))
            return min;
    }
    if (allHappy(v))
        return min;
    else
        return {};
}

int main(int argc, char **argv)
{
    size_t test_cases_count; 
    std::cin >> test_cases_count;

    for (size_t count = 1; count <= test_cases_count; count++) {
        std::string panCakes;
        size_t size;
        std::cin >> panCakes >> size;
        std::vector<bool> p;
        for (auto c : panCakes)
            p.push_back(c == '+');

        auto r = find(p, size);

        if (r)
            std::cout << "Case #" << count << ": " <<  r.value() << std::endl;
        else
            std::cout << "Case #" << count << ": IMPOSSIBLE" << std::endl;
    }
    return 0;
}
