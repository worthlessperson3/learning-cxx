#include "../exercise.h"
#include <iostream>

// C++ 中，`class` 和 `struct` 之间的**唯一区别**是
// `class` 默认访问控制符是 `private`，
// `struct` 默认访问控制符是 `public`。
class Fibonacci {
    size_t cache[16];
    int cached;

public:
    // TODO: 实现构造器
    Fibonacci() {
        cache[0] = 0;
        cache[1] = 1;
        cached = 2; // 标记前两个索引（0和1）已经是有效数据
    }

    // TODO: 实现正确的缓存优化斐波那契计算
    size_t get(int i) {
        // 逻辑同之前的 struct 练习：
        // 如果请求的 i >= cached，说明还没计算过，需要继续计算并填充缓存
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }
};

int main(int argc, char **argv) {
    // 现在类型拥有无参构造器，声明时会自动调用构造函数初始化私有成员。
    Fibonacci fib;
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}