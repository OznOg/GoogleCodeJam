#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <utility>
#include <iomanip>


struct Ret {
    uint64_t diff;
    uint64_t v1; 
    uint64_t v2; 
};

Ret doIt(std::vector<std::vector<uint8_t>> &v1, std::vector<std::vector<uint8_t>> &v2) {
    Ret best{0xFFFFFFFFFFFFFFFF, 0, 0};

    for (uint8_t i = 0; i < v1.size(); i++) {
        if (v1[i].size() != 1) {
            auto clone = v1;
            clone[i].resize(1);
            for (auto &val : v1[i]) {
                clone[i][0] = val;
                auto r = doIt(clone, v2);
                if (r.diff < best.diff || r.diff == best.diff && (best.v1 > r.v1 || best.v2 > r.v2))
                    best = r;
            }
            return best;
        } else if (v2[i].size() != 1) {
            auto clone = v2;
            clone[i].resize(1);
            for (auto &val : v2[i]) {
                clone[i][0] = val;
                auto r = doIt(v1, clone);
                if (r.diff < best.diff || r.diff == best.diff && (best.v1 > r.v1 || best.v2 > r.v2))
                    best = r;
            }
            return best;
        }
    }

    uint64_t val1 = 0, val2 = 0;
    for (uint8_t i = 0; i < v1.size(); i++) {
        val1 = val1 * 10 + v1[i][0];
        val2 = val2 * 10 + v2[i][0];
    }

    best.v1 = val1;
    best.v2 = val2;
    best.diff = val1 > val2 ? val1 - val2 : val2 -val1;
     
    return best;
}


static const std::vector<uint8_t> allval = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 } ;

int main(int argc, char **argv)
{
    size_t test_cases_count; 
    std::cin >> test_cases_count;


    for (size_t count = 1; count <= test_cases_count; count++) {

        std::string s1, s2;
        std::cin >> s1 >> s2;

        std::vector<std::vector<uint8_t>> v1(s1.size());
        std::vector<std::vector<uint8_t>> v2(s2.size());
        for (int i = 0; i < s1.size(); i++) {
            if (s1[i] != '?' && s2[i] != '?') {
                v1[i].push_back(s1[i] - '0');
                v2[i].push_back(s2[i] - '0');
            } else if (s1[i] == '?' && s2[i] == '?') {
                v1[i].push_back(0);
                v2[i].push_back(0);
                v1[i].push_back(1);
                v2[i].push_back(1);
                v1[i].push_back(9);
                v2[i].push_back(9);
            } else if (s1[i] == '?') {
                auto val = s2[i] - '0';
                v1[i].push_back(0);
                v1[i].push_back(9);
                v1[i].push_back(val);
                if (val > 2) v1[i].push_back(val - 1);
                if (val < 8) v1[i].push_back(val + 1);
                v2[i] = std::vector<uint8_t>(1, val);
            } else {
                auto val = s1[i] - '0';
                v2[i].push_back(0);
                v2[i].push_back(9);
                v2[i].push_back(val);
                if (val > 2) v2[i].push_back(val - 1);
                if (val < 8) v2[i].push_back(val + 1);
                v1[i] = std::vector<uint8_t>(1, val);
            }
        }
        const auto &scores = doIt(v1, v2);

        std::cout << "Case #" << count << ": " << std::setw(v2.size()) << std::setfill('0') << scores.v1 << " " 
                                               << std::setw(v2.size()) << std::setfill('0') << scores.v2 << std::endl;
    }
    return 0;
}

