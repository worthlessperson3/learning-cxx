#include "../exercise.h"
#include <iostream>

struct Fibonacci {
    unsigned long long cache[128];
    int cached;

    // TODO: 实现正确的缓存优化斐波那契计算
    unsigned long long get(int i) {
        // 如果请求的索引 i 还没有被计算（即 cached <= i），则继续计算
        // 循环从当前的 cached 位置开始，一直计算到 i 为止
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }
};

int main(int argc, char **argv) {
    // TODO: 初始化缓存结构体，使计算正确
    // 初始化策略：
    // 1. cache[0] = 0, cache[1] = 1 (斐波那契数列的基准)
    // 2. 其余数组元素默认为 0
    // 3. cached = 2 (表示索引 0 和 1 已经是有效数据)
    Fibonacci fib = { {0, 1}, 2 };

    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}