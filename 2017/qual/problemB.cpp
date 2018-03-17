#include <array>
#include <iostream>
#include <cstdlib>
#include <cmath>

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

std::string lastClean(const std::string &N) {
    std::string s = N;

    bool clean = true;
    size_t where = 0;
    for (size_t i = 1; i < N.size(); i++) {
        uint8_t next = s[i] - '0';
        uint8_t curr = s[where] - '0';
        if (curr < next) {
            // OK
            where = i;
        } else if (curr == next) {
            // don't move where
        } else {
            clean = false;
            break;
        }
    }

    if (clean)
        return s; // string was already OK

    s[where] -= 1;

    for (size_t i = where + 1; i < N.size(); i++)
        s[i] = '9';

    if (s[0] == '0') {
        return s.substr(1);
    }

    return s;
}


int main(int argc, char **argv)
{
    size_t test_cases_count; 
    std::cin >> test_cases_count;

    for (size_t count = 1; count <= test_cases_count; count++) {
        std::string value;
        std::cin >> value;

        std::cout << "Case #" << count << ": " << lastClean(value) << std::endl;
    }
    return 0;
}
