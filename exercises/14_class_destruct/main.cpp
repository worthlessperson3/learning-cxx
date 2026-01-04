#include "../exercise.h"
#include <iostream>

// READ: 析构函数 <https://zh.cppreference.com/w/cpp/language/destructor>
// READ: RAII <https://learn.microsoft.com/zh-cn/cpp/cpp/object-lifetime-and-resource-management-modern-cpp?view=msvc-170>

/// @brief 任意缓存容量的斐波那契类型。
/// @details 可以在构造时传入缓存容量，因此需要动态分配缓存空间。
class DynFibonacci {
    size_t *cache;
    int cached;

public:
    // TODO: 实现动态设置容量的构造器
    // 1. 使用初始化列表分配数组内存：new size_t[capacity]
    // 2. 初始化 cached 为 2（因为我们要预填前两个数）
    DynFibonacci(int capacity) : cache(new size_t[capacity]), cached(2) {
        cache[0] = 0;
        cache[1] = 1;
    }

    // TODO: 实现析构器，释放缓存空间
    // 当对象生命周期结束时，自动调用析构函数释放内存
    ~DynFibonacci() {
        delete[] cache; // 注意：释放数组必须用 delete[]，不能用 delete
    }

    // TODO: 实现正确的缓存优化斐波那契计算
    size_t get(int i) {
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}