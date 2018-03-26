
#include <functional>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <list>
#include <sstream>

struct Party {
    uint8_t name;
    size_t size;
};

struct Comp {
    static constexpr bool anticomp(const Party &p1, const Party &p2) {
        if (p1.size == p2.size)
            return p1.name < p2.name;

        return p1.size < p2.size;
    }
    static constexpr bool comp(const Party &p1, const Party &p2) {
        return !anticomp(p1, p2);
    }
};

using Senate = std::list<Party>;


auto overallsize(const Senate &senate) {
    size_t size = 0;
    for (auto & p : senate)
        size += p.size;
    return size;
}

std::string evacuate(Senate senate){
    std::stringstream ss;
    senate.sort(Comp::comp);
    while (!senate.empty()) {

        for (auto &p :senate)
            if ((p.size * 100) / overallsize(senate) > 50) {
                std::cout << ss.str() << std::endl << p.name << " " << p.size << " " << overallsize(senate) << std::endl;
                abort();
            }
 
        if (overallsize(senate) == 3) {
            ss << senate.front().name;
            senate.front().size--;
            if (senate.front().size == 0)
                senate.pop_front();
            senate.sort(Comp::comp);
            ss << " ";
            continue;
        }

        senate.front().size--;
        ss << senate.front().name;
        if (senate.front().size == 0)
            senate.pop_front();
        senate.sort(Comp::comp);

        senate.front().size--;
        ss << senate.front().name;
        if (senate.front().size == 0)
            senate.pop_front();
        senate.sort(Comp::comp);

        ss << " ";
    }
    auto str = std::move(ss.str());
    if (str[str.size() - 1] == ' ')
        str.resize(str.size() - 1);
    return str;
}

void show(const Party &p) {
    std::cout << p.name << " " << p.size << std::endl;
}

int main(int argc, char **argv)
{
    size_t test_cases_count; 
    std::cin >> test_cases_count;

    for (size_t count = 1; count <= test_cases_count; count++) {
        size_t party_count;
        std::cin >> party_count;

        Senate senate;
        for (size_t i = 0; i < party_count; i++) {
            Party p;
            std::cin >> p.size;
            p.name = 'A' + i;
            senate.push_back(p);
        }


        senate.sort(Comp::comp);
        auto r = evacuate(senate);

        std::cout << "Case #" << count << ": " << r << std::endl;
    }
    return 0;
}

