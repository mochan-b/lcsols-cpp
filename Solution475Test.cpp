
#include <iostream>

#include "catch.hpp"

#include <vector>
#include <algorithm>

using namespace std;

class Solution475 {
public:
    int findRadius(vector<int> &houses, vector<int> &heaters) {
        auto findHeater = [&heaters](int house) {
            int left = 0, right = heaters.size() - 1;
            while (left <= right) {
                auto mid = left + ((right - left) >> 1);
                if (heaters[mid] == house)
                    return mid;
                if (heaters[mid] < house)
                    left = mid + 1;
                else
                    right = mid - 1;
            }
            return left;
        };

        std::sort(heaters.begin(), heaters.end());
        int radius = 0;
        for (auto house : houses) {
            auto heaterIndex = findHeater(house);
            auto leftDistFn = [house, &heaters, heaterIndex]() { return house - heaters[heaterIndex - 1]; };
            auto rightDistFn = [house, &heaters, heaterIndex]() { return heaters[heaterIndex] - house; };
            auto heaterDist =
                    heaterIndex == 0 ? rightDistFn() : heaterIndex == heaters.size() ? leftDistFn() : std::min(
                            leftDistFn(), rightDistFn());
            radius = std::max(radius, heaterDist);
        }
        return radius;
    }
};

TEST_CASE("[1,2,3], [2] = 1", "[475]") {
    vector<int> houses = {1, 2, 3};
    vector<int> heaters = {2};
    Solution475 solution;
    auto result = solution.findRadius(houses, heaters);
    REQUIRE(result == 1);
}

TEST_CASE("[1,3,2], [2] = 1", "[475]") {
    vector<int> houses = {1, 3, 2};
    vector<int> heaters = {2};
    Solution475 solution;
    auto result = solution.findRadius(houses, heaters);
    REQUIRE(result == 1);
}

TEST_CASE("[1,2,3,4], [1,4] = 1", "[475]") {
    vector<int> houses = {1, 2, 3, 4};
    vector<int> heaters = {1, 4};
    Solution475 solution;
    auto result = solution.findRadius(houses, heaters);
    REQUIRE(result == 1);
}

TEST_CASE("[1,5], [2] = 3", "[475]") {
    vector<int> houses = {1, 5};
    vector<int> heaters = {2};
    Solution475 solution;
    auto result = solution.findRadius(houses, heaters);
    REQUIRE(result == 3);
}

TEST_CASE("[1,5], [10] = 9", "[475]") {
    vector<int> houses = {1, 5};
    vector<int> heaters = {10};
    Solution475 solution;
    auto result = solution.findRadius(houses, heaters);
    REQUIRE(result == 9);
}

TEST_CASE("unsorted heaters", "[475]") {
    vector<int> houses = {282475249, 622650073, 984943658, 144108930, 470211272, 101027544, 457850878, 458777923};
    vector<int> heaters = {823564440, 115438165, 784484492, 74243042, 114807987, 137522503, 441282327, 16531729,
                           823378840,
                           143542612};
    Solution475 solution;
    auto result = solution.findRadius(houses, heaters);
    REQUIRE(result == 161834419);
}

TEST_CASE("large distances", "[475]") {
    vector<int> houses = {474833169, 264817709, 998097157, 817129560};
    vector<int> heaters = {197493099, 404280278, 893351816, 505795335};
    Solution475 solution;
    auto result = solution.findRadius(houses, heaters);
    REQUIRE(result == 104745341);
}