#include "../exercise.h"

void func(int);

int main(int argc, char **argv) {
    auto arg = 99;
    ASSERT(arg == 99, "arg should be 99"); // 初始值是 99
    std::cout << "befor func call: " << arg << std::endl;
    func(arg);
    // 因为是值传递，func 里的修改不影响这里
    ASSERT(arg == 99, "arg should be 99"); 
    std::cout << "after func call: " << arg << std::endl;
    return 0;
}

void func(int param) {
    ASSERT(param == 99, "param should be 99"); // 传入的副本初始值也是 99
    std::cout << "befor add: " << param << std::endl;
    param += 1; // 副本自增变为 100
    ASSERT(param == 100, "param should be 100"); 
    std::cout << "after add: " << param << std::endl;
}