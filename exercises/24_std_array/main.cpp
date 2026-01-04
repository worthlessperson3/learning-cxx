#include "../exercise.h"
#include <array>
#include <cstring>

// READ: std::array <https://zh.cppreference.com/w/cpp/container/array>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    {
        std::array<int, 5> arr{{1, 2, 3, 4, 5}};
        // size() 返回元素个数
        ASSERT(arr.size() == 5, "Fill in the correct value.");
        // sizeof() 返回整个对象占用的字节数。int 通常为 4 字节，5 * 4 = 20
        ASSERT(sizeof(arr) == 20, "Fill in the correct value.");
        int ans[]{1, 2, 3, 4, 5};
        // arr.data() 返回指向底层数组首元素的指针 (int*)
        // memcmp 比较内存字节，长度应该是字节数 (sizeof(ans) 或 20)
        ASSERT(std::memcmp(arr.data(), ans, sizeof(ans)) == 0, "Fill in the correct values.");
    }
    {
        std::array<double, 8> arr;
        // size() 始终等于模板参数 N
        ASSERT(arr.size() == 8, "Fill in the correct value.");
        // double 通常为 8 字节，8 * 8 = 64
        ASSERT(sizeof(arr) == 64, "Fill in the correct value.");
    }
    {
        std::array<char, 21> arr{"Hello, InfiniTensor!"};
        // 注意：这里 size 是 21，不是字符串长度。std::array 的 size 是固定的容量。
        ASSERT(arr.size() == 21, "Fill in the correct value.");
        // char 为 1 字节，21 * 1 = 21
        ASSERT(sizeof(arr) == 21, "Fill in the correct value.");
        // strcmp 需要 const char*，使用 .data() 获取
        ASSERT(std::strcmp(arr.data(), "Hello, InfiniTensor!") == 0, "Fill in the correct value.");
    }
    return 0;
}