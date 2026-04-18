#include <iostream>
#include <vector>
using namespace std;

// report[i][j] = 晶片 i 對晶片 j 的判斷
// true  表示 i 說 j 是好晶片
// false 表示 i 說 j 是壞晶片

class ChipTester {
private:
    vector<vector<bool>> report;

public:
    ChipTester(const vector<vector<bool>>& r) : report(r) {}

    // 回傳一顆好晶片的索引；若無法找到則回傳 -1
     int findGoodChip(vector<int> chips) {
    // Phase 1: 配對淘汰
        while (chips.size() > 1) {
            vector<int> next;

            for (int i = 0; i + 1 < chips.size(); i += 2) {
                int A = chips[i];
                int B = chips[i + 1];

                if (report[A][B] && report[B][A]) {
                // 兩個互說好 → 留一個
                    next.push_back(A);
                }
            // 否則兩個都丟掉
            }

        // 如果是奇數個，最後一個直接留下
            if (chips.size() % 2 == 1) {
                next.push_back(chips.back());
            }

            chips = next;
        }

        if (chips.empty()) return -1;

        int candidate = chips[0];

        // Phase 2: 驗證（避免全壞的極端情況）
        int count = 0;
        for (int i = 0; i < report.size(); i++) {
            if (report[candidate][i]) {
                count++;
            }
        }

        if (count >= report.size() / 2) {
            return candidate;
        }
        return -1;
        }
};

int main() {
    // 範例：6 顆晶片，編號 0~5
    // 假設好晶片多於壞晶片
    // 好晶片會誠實回答，壞晶片可任意回答

    vector<vector<bool>> report = {
        // 0    1    2    3    4    5
        {true, true, true, false, true, false},
        {true, true, true, false, true, false},
        {true, true, true, false, true, false},
        {true, false, true, true, false, true},
        {true, true, true, false, true, false},
        {false, true, false, true, true, true}
    };

    ChipTester tester(report);

    vector<int> chips = {0, 1, 2, 3, 4, 5};

    int goodChip = tester.findGoodChip(chips);

    if (goodChip != -1) {
        cout << "Found a good chip: chip " << goodChip << endl;
    } else {
        cout << "No good chip found." << endl;
    }

    return 0;
}
