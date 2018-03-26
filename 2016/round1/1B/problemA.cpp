#include <functional>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <set>
#include <map>

#include <experimental/optional>

namespace std {
    /* XXX keep this as long as optional is experimental */
    template <class T>
    using optional = experimental::optional<T>;
    #define make_optional experimental::make_optional
};


std::vector<std::pair<std::string, uint8_t>> numbers = {
    { "ZERO", '0' }, {"ONE", '1'}, { "TWO", '2' } , {"THREE",  '3' }, {"FOUR", '4' }, { "FIVE", '5' }, { "SIX", '6' }, { "SEVEN", '7' }, { "EIGHT", '8' }, { "NINE", '9' }
};


// I use a map to pick entries depending on the letter the contain:
// for example Z is only present in "ZERO".
std::map<uint8_t, std::set<std::pair<std::string, uint8_t>>> map;


bool eraseAllOf(std::string &str, const std::string &entry) {

    for (const auto &c : entry) {
        auto pos = str.find(c);
        if (pos == std::string::npos)
            return false;
        str.erase(pos, 1);
    }
    return true;
}

std::optional<std::string> getPhoneNumber(const std::string &str, const std::string &phone = "") {
    if (str.empty()) { //nothing to be done left; phone must be correct
        auto sorted_phone = phone;
        std::sort(sorted_phone.begin(), sorted_phone.end());
        return std::move(sorted_phone); // the phone is said to be sorted in the problem definition
    }

    for (const auto &entry : map[str[0]]) { //Loop over entries that can have the fist letter
        auto s = str;
        bool res = eraseAllOf(s, entry.first);
        if (res) {
            auto success = getPhoneNumber(s, std::string(phone).append(1, entry.second));
            if (success)
                return std::move(success);
        }
    }

    return {};
}

int main(int argc, char **argv)
{
    size_t test_cases_count; 
    std::cin >> test_cases_count;

    for (auto &e : numbers) {
        for (auto &c : e.first)
            map[c].insert(e);
    }

    for (size_t count = 1; count <= test_cases_count; count++) {
        std::string s;
        std::cin >> s;
        std::sort(s.begin(), s.end(), [](const int a, const int b) { 
                return map[a].size() < map[b].size();
                }); // I sort the input lettrers with respect to the number of
                    // entries they may refer to; letters with feer entries first.
                    // This really make the search faster by removing fastly letters
                    // that have a direct correspondance with the number
        const auto &l = getPhoneNumber(s);
        std::cout << "Case #" << count << ": " << l.value() << std::endl;
    }
    return 0;
}

