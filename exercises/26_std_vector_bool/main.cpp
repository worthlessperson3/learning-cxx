#include "../exercise.h"
#include <vector>
#include <iostream>

// READ: std::vector <https://zh.cppreference.com/w/cpp/container/vector_bool>
// READ: 模板特化 <https://zh.cppreference.com/w/cpp/language/template_specialization>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    // 1. 构造函数：需要初始化为 true 才能通过 vec[0] 和 vec[99] 的检查
    std::vector<bool> vec(100, true);
    
    ASSERT(vec[0], "Make this assertion pass.");
    ASSERT(vec[99], "Make this assertion pass.");
    ASSERT(vec.size() == 100, "Make this assertion pass.");
    
    // NOTICE: 平台相关！注意 CI:Ubuntu 上的值。
    // 在 64 位 Linux (GCC/libstdc++) 上，vector<bool> 通常占用 40 字节
    // (两个迭代器 16*2 + 一个指针 8 = 40)
    std::cout << "sizeof(std::vector<bool>) = " << sizeof(std::vector<bool>) << std::endl;
    ASSERT(sizeof(vec) == 40, "Fill in the correct value.");
    
    {
        vec[20] = false;
        ASSERT(!vec[20], "Fill in `vec[20]` or `!vec[20]`.");
    }
    {
        vec.push_back(false);
        ASSERT(vec.size() == 101, "Fill in the correct value.");
        ASSERT(!vec[100], "Fill in `vec[100]` or `!vec[100]`.");
    }
    {
        // 关键点：这里的 ref 不是 bool 类型，而是一个“代理对象”
        auto ref = vec[30]; 
        ASSERT(ref, "Fill in `ref` or `!ref`"); // 此时 vec[30] 还是 true
        
        ref = false; // 修改代理对象，实际上会修改 vec[30] 对应的那个 bit
        ASSERT(!ref, "Fill in `ref` or `!ref`");
        
        // THINK: WHAT and WHY?
        // 因为 ref 是 vec[30] 的引用代理，修改 ref 就是修改 vec[30]
        ASSERT(!vec[30], "Fill in `vec[30]` or `!vec[30]`.");
    }
    return 0;
}