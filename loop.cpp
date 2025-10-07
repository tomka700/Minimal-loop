// g++ -std=c++23 -O3 -march=native -flto -Wall loop.cpp -o loop
// g++ -std=c++23 -O3 -march=native -flto -Wall -fprofile-generate loop.cpp -o loop
// g++ -std=c++23 -O3 -march=native -flto -Wall -fprofile-use loop.cpp -o loop
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdint>
#include <thread>
#include <atomic>
#include <mutex>
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>

constexpr int n = 8;
constexpr int MAX_LEN = 40;

static_assert(n > 3, "n must be at least 4!");

constexpr int TOTAL_BITS = n * n;

struct Dir {
    int dx;
    int dy;
    int max_added;
    int length;
};

constexpr Dir DIRS[16] = {
    {-1, 1, 3, 1},
    {-1, -1, 3, 1},
    {1, -1, 3, 1},
    {1, 1, 3, 1},
    {0, -1, 2, 1},
    {1, 0, 2, 1},
    {0, 1, 2, 1},
    {-1, 0, 2, 1},
    {2, 1, 4, 2}, // only used for n == 7, see MAX_I
    {2, -1, 4, 2},
    {-2, 1, 4, 2},
    {-2, -1, 4, 2},
    {1, 2, 4, 2},
    {1, -2, 4, 2},
    {-1, 2, 4, 2},
    {-1, -2, 4, 2}
};

using MaskMatrix = std::array<std::array<std::bitset<TOTAL_BITS>, n+1>, n+1>;

constexpr MaskMatrix create_vertex_masks() {
    MaskMatrix masks;
    for (int x = 0; x <= n; ++x) {
        for (int y = 0; y <= n; ++y) {
            if (x > 0 && y > 0) masks[x][y].set((x-1) * n + (y-1));
            if (x > 0 && y < n) masks[x][y].set((x-1) * n + y);
            if (x < n && y > 0) masks[x][y].set(x * n + (y-1));
            if (x < n && y < n) masks[x][y].set(x * n + y);
        }
    }
    return masks;
}
constexpr auto VERTEX_MASKS = create_vertex_masks();

constexpr std::array<std::array<bool, n+1>, n+1> create_is_outer() {
    std::array<std::array<bool, n+1>, n+1> is_outer;
    for (int i = 0; i <= n; ++i) {
        is_outer[i][0] = true;
        is_outer[i][n] = true;
        is_outer[0][i] = true;
        is_outer[n][i] = true;
    }
    return is_outer;
}
constexpr auto IS_OUTER = create_is_outer();

int best_len = MAX_LEN;
bool found = false;

void dfs(std::bitset<TOTAL_BITS>& mask, std::array<std::pair<int, int>, MAX_LEN+1>& path, int idx, int len) {
    int count = mask.count();
    if (len + (TOTAL_BITS - count + 2) / 3 > best_len) return;

    auto [x, y] = path[idx];
    if (count == TOTAL_BITS && x == 1 && y == 2) {
        if (len <= best_len) {
            found = true;
            best_len = len;
            std::cout << "New best: " << len << ", Path: ";
            for (int i = 0; i <= idx; ++i) {
                std::cout << "(" << path[i].first << "," << path[i].second << ")";
            }
            std::cout << "\n";
        }
        return;
    }

    auto invmask = ~mask;
    constexpr int MAX_I = n == 7 ? 16 : 8;
    for (int i = 0; i < MAX_I; ++i) {
        const Dir dir = DIRS[i];
        int nx = x + dir.dx;
        int ny = y + dir.dy;
        if (IS_OUTER[nx][ny]) continue;

        auto added = VERTEX_MASKS[nx][ny] & invmask;
        if (n != 5 && static_cast<int>(added.count()) < dir.max_added) continue;
        if (n == 5 && static_cast<int>(added.count()) < 2) continue;

        path[idx+1] = {nx, ny};
        mask |= added;
        dfs(mask, path, idx + 1, len + dir.length);
        mask &= ~added;
    }
}

int main() {
    // init with forced corner turn
    std::array<std::pair<int, int>, MAX_LEN+1> path;
    path[0] = {1, 2};
    path[1] = {1, 1};
    path[2] = {2, 1};
    path[3] = {3, 1};
    std::bitset<TOTAL_BITS> mask;
    mask.set(0);
    mask.set(n);
    mask |= VERTEX_MASKS[3][1];

    dfs(mask, path, 3, 3);
}