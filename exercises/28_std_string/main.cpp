#include "../exercise.h"
#include <string>

// READ: 字符串 <https://zh.cppreference.com/w/cpp/string/basic_string>

int main(int argc, char **argv) {
    // READ: 字符串字面量 <https://zh.cppreference.com/w/cpp/string/basic_string/operator%22%22s>
    using namespace std::string_literals;
    
    // 1. "Hello"s 使用了 's' 后缀，这是一个用户定义字面量，直接生成 std::string 对象
    auto hello = "Hello"s; 
    
    // 2. "world" 是传统的 C 风格字符串字面量。
    // auto 推导时，数组类型会“退化”(decay) 为指针类型，即 const char*
    auto world = "world";
    
    // READ: `decltype` 表达式 <https://zh.cppreference.com/w/cpp/language/decltype>
    // READ: `std::is_same_v` 元编程判别 <https://zh.cppreference.com/w/cpp/types/is_same>
    ASSERT((std::is_same_v<decltype(hello), std::string>), "Fill in the missing type.");
    ASSERT((std::is_same_v<decltype(world), const char*>), "Fill in the missing type.");
    
    // TODO: 将 `?` 替换为正确的字符串
    // std::string 重载了 + 运算符，支持混合拼接
    // "Hello" (string) + ", " (const char*) -> "Hello, " (string)
    // "Hello, " (string) + "world" (const char*) -> "Hello, world" (string)
    // "Hello, world" (string) + '!' (char) -> "Hello, world!" (string)
    ASSERT(hello + ", " + world + '!' == "Hello, world!", "Fill in the missing string.");
    
    return 0;
}