#include "../exercise.h"
#include <algorithm> // 用于 std::copy，或者手动循环也可以

// READ: 复制构造函数 <https://zh.cppreference.com/w/cpp/language/copy_constructor>
// READ: 函数定义（显式弃置）<https://zh.cppreference.com/w/cpp/language/function>

class DynFibonacci {
    size_t *cache;
    int cached;

public:
    // TODO: 实现动态设置容量的构造器
    // 1. 根据 capacity 分配堆内存
    // 2. 初始化 cached 为 2 (对应 0 和 1)
    // 3. 填充斐波那契数列的基准值
    DynFibonacci(int capacity): cache(new size_t[capacity]), cached(2) {
        cache[0] = 0;
        cache[1] = 1;
    }

    // TODO: 实现复制构造器
    // 1. 这里必须进行【深拷贝】：申请新的内存，并将数据搬运过来
    // 注意：由于类中没有存储 capacity，我们这里暂且按照 source.cached 的大小来分配
    //      这在当前 const 场景下是安全的（shrink-to-fit）。
    DynFibonacci(DynFibonacci const &other) 
        : cache(new size_t[other.cached]), cached(other.cached) {
        // 将原对象的数据复制到新对象的内存中
        for (int i = 0; i < cached; ++i) {
            cache[i] = other.cache[i];
        }
    }

    // TODO: 实现析构器，释放缓存空间
    ~DynFibonacci() {
        delete[] cache;
    }

    // TODO: 实现正确的缓存优化斐波那契计算
    size_t get(int i) {
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    size_t get(int i) const {
        if (i <= cached) {
            return cache[i];
        }
        ASSERT(false, "i out of range");
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    
    // 这里会调用复制构造函数
    DynFibonacci const fib_ = fib;
    ASSERT(fib_.get(10) == fib.get(10), "Object cloned");
    return 0;
}