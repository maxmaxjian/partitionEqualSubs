#include <iostream>
#include <vector>
#include <numeric>
#include <functional>
#include <utility>
#include <algorithm>
#include <iterator>

using std::vector;
using std::pair;

class solution {
  public:
    bool canPartition(const vector<int> & nums) {
        auto partitions = balance(nums, vector<int>());
        for (auto partition : partitions) {
            std::cout << "[";
            std::copy(partition.first.begin(), partition.first.end(), std::ostream_iterator<int>(std::cout," "));
            std::cout << "] ";
            std::cout << "[";
            std::copy(partition.second.begin(), partition.second.end(), std::ostream_iterator<int>(std::cout," "));
            std::cout << "] ";
            std::cout << std::endl;
        }
        return !partitions.empty();
    }

  private:
    vector<pair<vector<int>, vector<int>>> balance(const vector<int> v1, const vector<int> v2) {
        vector<pair<vector<int>,vector<int>>> result;
        int sum1 = std::accumulate(v1.begin(), v1.end(), 0);
        int sum2 = std::accumulate(v2.begin(), v2.end(), 0);
        if (sum1 == sum2) {
            result.push_back(std::make_pair(v1,v2));
        }
        else if (sum1 > sum2){
            int diff = sum1-sum2;
            auto it = std::find(v1.begin(), v1.end(), diff);
            if (it != v1.end()) {
                auto first = v1;
                auto second = v2;
                second.push_back(*it);
                first.erase(first.begin()+std::distance(v1.begin(), it));
            }
            else {
                vector<int> next;
                for (auto & v : v1) {
                    if (v < diff)
                        next.push_back(v);
                }
                std::sort(next.begin(), next.end());
                for (auto nx : next) {
                    auto first = v1;
                    first.erase(std::find(first.begin(), first.end(), nx));
                    auto second = v2;
                    second.push_back(nx);
                    auto temp = balance(first, second);
                    for (auto tmp : temp)
                        result.push_back(tmp);
                }
            }
        }
        return result;
    }
};

int main() {
    // vector<int> nums{1,5,11,5};
    vector<int> nums{1,2,3,5};
    
    solution soln;
    bool result = soln.canPartition(nums);
    std::cout << std::boolalpha
              << result << std::endl;
}
