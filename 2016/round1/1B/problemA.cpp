#include <functional>
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <set>

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


bool eraseAllOf(std::string &str, const std::string &entry) {

    for (auto &c : entry) {
        auto pos = str.find(c);
        if (pos == std::string::npos)
            return false;
        str.erase(pos, 1);
    }
    return true;
}

std::optional<std::string> getPhoneNumber(const std::string &str, const std::string &phone = "") {
    if (str.empty()) //nothing to be done left; phone must be correct
        return phone;

    for (auto &entry : numbers) {
        auto s = str;
        bool res = eraseAllOf(s, entry.first);
        if (res) {
            auto &&new_phone = std::string(phone).append(1, entry.second);
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

    for (size_t count = 1; count <= test_cases_count; count++) {
        std::string s;
        std::cin >> s;
        const auto &l = getPhoneNumber(s);
        std::cout << "Case #" << count << ": " << l.value() << std::endl;
    }
    return 0;
}

