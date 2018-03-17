#include <iostream>
#include <sstream>
#include <string>
#include <set>


using Rawlist = std::multiset<size_t>;

std::string doIt(const Rawlist &list) {
    std::set<size_t> res;
    for (auto &v : list) {
        if (list.count(v) % 2 != 0)
            res.insert(v);
    }

    std::stringstream ss;
    for (auto &v : res)
        ss << v << " ";

    auto s = ss.str();
    s.resize(s.size() - 1);
    return s;
}

int main(int argc, char **argv)
{
    size_t test_cases_count; 
    std::cin >> test_cases_count;

    for (size_t count = 1; count <= test_cases_count; count++) {
        size_t N;
        std::cin >> N;
        Rawlist v;
        for (size_t e = 0; e < 2 * N - 1; e++) {
            for (size_t i = 0; i < N; i++) {
                size_t val;
                std::cin >> val;
                v.insert(val);
            }
        }

        auto s = doIt(v);

        std::cout << "Case #" << count << ": " << s << std::endl;
    }
    return 0;
}

