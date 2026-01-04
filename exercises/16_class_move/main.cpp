#include "../exercise.h"
#include <utility> // for std::move, though implied usually

// READ: 左值右值（概念）
// READ: 关于移动语义

class DynFibonacci {
    size_t *cache;
    int cached;

public:
    // TODO: 实现动态设置容量的构造器
    DynFibonacci(int capacity) : cache(new size_t[capacity]), cached(2) {
        cache[0] = 0;
        cache[1] = 1;
    }

    // TODO: 实现移动构造器
    // 逻辑：直接接管 other 的资源，并将 other 置为空指针（防止析构时重复释放）
    DynFibonacci(DynFibonacci &&other) noexcept 
        : cache(other.cache), cached(other.cached) {
        other.cache = nullptr;
        other.cached = 0;
    }

    // TODO: 实现移动赋值
    // NOTICE: ⚠ 注意移动到自身问题 ⚠
    DynFibonacci &operator=(DynFibonacci &&other) noexcept {
        // 1. 检测自赋值 (例如 fib = std::move(fib))
        if (this != &other) {
            // 2. 释放当前对象持有的旧资源
            delete[] cache;

            // 3. 窃取 other 的资源
            cache = other.cache;
            cached = other.cached;

            // 4. 将 other 置于安全的可析构状态
            other.cache = nullptr;
            other.cached = 0;
        }
        return *this;
    }

    // TODO: 实现析构器，释放缓存空间
    ~DynFibonacci() {
        // delete nullptr 是安全的，不需要额外判断
        delete[] cache;
    }

    // TODO: 实现正确的缓存优化斐波那契计算
    // 这里我们将 get 改为了 operator[] 重载，用法变为了 fib[10]
    size_t operator[](int i) {
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    size_t operator[](int i) const {
        ASSERT(i <= cached, "i out of range");
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    bool is_alive() const {
        return cache;
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib[10] == 55, "fibonacci(10) should be 55");

    // 移动构造：fib 的资源被转移给了 fib_
    DynFibonacci const fib_ = std::move(fib);
    // 因为 fib 的 cache 被置为了 nullptr，所以 is_alive() 返回 false
    ASSERT(!fib.is_alive(), "Object moved");
    ASSERT(fib_[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci fib0(6);
    DynFibonacci fib1(12);

    // 移动赋值：fib1 的资源给 fib0，fib0 原有的资源被释放
    fib0 = std::move(fib1);
    // 自赋值检测
    fib0 = std::move(fib0);
    ASSERT(fib0[10] == 55, "fibonacci(10) should be 55");

    return 0;
}