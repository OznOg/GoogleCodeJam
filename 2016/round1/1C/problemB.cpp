#include <iostream>
#include <string>

static inline constexpr uint64_t exp2(const uint64_t B) {
    uint64_t res = 1;
    for (uint64_t i = 0; i < B; i++)
         res *= 2;
    return res;
}

std::string slide(uint64_t B, uint64_t M) {
    std::string str = "POSSIBLE\n";

    B -= 2;
    if (M > exp2(B))
        return "IMPOSSIBLE";

    str.append(1, '0');
    if (M == exp2(B)) {
        str.append(B + 1, '1');
    } else {
        for (uint64_t i = 0; i < B; i++)
            str.append(1, (M & ((uint64_t)1 << i)) ? '1' : '0');
        str.append(1, M == exp2(B) ? '1': '0');
    }

    for (uint64_t i = 2; i <= B + 1; i++) {
        str.append(1, '\n');
        str.append(1, '0');
        for (uint64_t j = 2; j <= B + 1; j++)
            str.append(1, j < i ? '1' : '0');
 
        str.append(1, '1');
    }
    
    str.append(1, '\n');

    str.append(B + 2, '0');
    return str;
}

int main(int argc, char **argv)
{
    size_t test_cases_count; 
    std::cin >> test_cases_count;

    for (size_t count = 1; count <= test_cases_count; count++) {
        uint64_t B, M;
        std::cin >> B >> M;
        const auto &s = slide(B, M);
        std::cout << "Case #" << count << ": " << s << std::endl;
    }
    return 0;
}

