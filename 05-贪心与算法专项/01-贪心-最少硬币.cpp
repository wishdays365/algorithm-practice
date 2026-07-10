#include <iostream>
#include <vector>

// 定义结构体，用于存储具体的硬币分配信息
struct CoinChoice {
    long long denomination; // 硬币面值
    long long count;        // 该面值使用的硬币个数
};

// 定义结构体，用于返回算法结果
struct Result {
    long long total_coins;                 // 最少硬币总数
    std::vector<CoinChoice> distribution;  // 分配详情
};

/**
 * 计算在币值为 {1, p, p^2, ..., p^n} 的系统中，凑齐金额 y 所需的最少硬币数
 * * @param y 目标总金额
 * @param p 币值系统的基数 (p > 1)
 * @param n 币值的最大幂次
 * @return Result 包含总硬币数和具体分配方案的结构体
 */
Result minCoins(long long y, long long p, int n) {
    Result res;
    res.total_coins = 0;

    // 1. 先计算最大面值 p^n
    long long denomination = 1;
    for (int i = 0; i < n; ++i) {
        denomination *= p;
    }

    // 2. 从最大面值 p^n 开始，一直向下遍历到 p^0 (即 1)
    for (int i = n; i >= 0; --i) {
        long long count = y / denomination; // 当前面值需要的硬币个数

        if (count > 0) {
            res.distribution.push_back({denomination, count});
            res.total_coins += count;
            y = y % denomination; // 更新剩余需要凑齐的金额
        }

        // 如果剩余金额已经为 0，提前结束计算
        if (y == 0) {
            break;
        }

        // 3. 面值降级为 p^(i-1)
        if (i > 0) {
            denomination /= p;
        }
    }

    return res;
}

int main() {
    // 设置测试参数，与 Python 示例保持一致
    long long y = 50;
    long long p = 3;
    int n = 3;

    // 运行算法
    Result res = minCoins(y, p, n);

    // 打印输出结果
    std::cout << "目标金额: " << y << std::endl;
    std::cout << "最少硬币总数: " << res.total_coins << std::endl;
    std::cout << "硬币分配详情:" << std::endl;
    for (const auto& coin : res.distribution) {
        std::cout << "  - 面值 " << coin.denomination << " : " << coin.count << " 个\n";
    }

    return 0;
}