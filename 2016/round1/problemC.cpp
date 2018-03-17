#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>

struct Student {
    Student *bff;
    size_t id;
    bool visited;
};
using Friends = std::vector<Student *>;

struct Chain {
    explicit Chain(const std::vector<size_t> &v) : length(v.size()) {
            const auto &last = *(v.end() - 1);
            const auto &lastprev = *(v.end() - 2);
            bottom = std::make_pair(std::min(lastprev, last), std::max(lastprev, last));
            goofy = last < lastprev;
    }

    bool match(const Chain &anotherChain) const {
        return bottom == anotherChain.bottom && goofy == !anotherChain.goofy;
    }
    size_t length;
    std::pair<size_t, size_t> bottom;
    bool goofy;
};

size_t circleLength(Friends &f) {

    size_t round_max = 0;
    std::vector<Chain> chains;
    for (auto s : f) {
        std::vector<size_t> path;
        auto *p = s;
        do {
            path.push_back(p->id);
            p->visited = true;
            p = p->bff;
        } while (!p->visited);

        if (p == s) { /* chain is actually a circle (last points on first) */
            round_max = std::max(path.size(), round_max);
        }
        if (p->bff->bff == p && path.size() > 1) { // peer is pointing at us => valid chain
            chains.push_back(Chain(path));
        }
        /* clear */
        p = s;
        while (p->visited) {
            p->visited = false;
            p = p->bff;
        }
    }

    size_t chain_max_lenght = 0;
    for (const auto &c : chains) // simple chain sizes
        chain_max_lenght = std::max(chain_max_lenght, c.length);

    if (chains.size() > 1) {
        for (size_t idx = 0; idx < chains.size() - 1; idx++) { // chains combinations
            for (size_t rem = idx + 1; rem < chains.size(); rem++) {
                const auto &chainA = chains[idx], &chainB = chains[rem];
                if (chainA.match(chainB)) {
                    size_t sum = chainA.length + chainB.length - 2 /* do not count bottom twice */;
                    chain_max_lenght = std::max(sum, chain_max_lenght);
                }
            }
        }
    }
    return std::max(round_max, chain_max_lenght);
}

int main() {
    size_t T;
    std::cin >> T;

    for (size_t count = 1; count <= T; count++) {
        size_t kid_count;
        std::cin >> kid_count;
        Friends friends(kid_count);
        for (auto &s : friends)
            s = new Student();
        for (size_t i = 0; i < kid_count; i++) {
            size_t bff;
            std::cin >> bff;
            bff--;
            friends[i]->bff = friends[bff];
            friends[i]->id = i + 1;
            friends[i]->visited = false;
        }

        std::cout << "Case #" << count << ": " << circleLength(friends) << std::endl;
    }

    return 0;
}
