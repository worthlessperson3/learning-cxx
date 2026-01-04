#include "../exercise.h"
#include <cmath> // 需要引入 abs 函数

// READ: 函数模板 <https://zh.cppreference.com/w/cpp/language/function_template>
// TODO: 将这个函数模板化
template <typename T>
T plus(T a, T b) {
    return a + b;
}

int main(int argc, char **argv) {
    ASSERT(plus(1, 2) == 3, "Plus two int");
    ASSERT(plus(1u, 2u) == 3u, "Plus two unsigned int");

    // THINK: 浮点数何时可以判断 ==？何时必须判断差值？
    // 1.25 (1 + 1/4) 和 2.5 (2 + 1/2) 都是 2 的幂次组合，二进制可以精确表示，所以能相等。
    ASSERT(plus(1.25f, 2.5f) == 3.75f, "Plus two float");
    ASSERT(plus(1.25, 2.5) == 3.75, "Plus two double");
    
    // TODO: 修改判断条件使测试通过
    // 0.1 和 0.2 在二进制中是无限循环小数，无法精确存储。
    // 它们相加的结果 0.30000000000000004... 并不等于精确的 0.3
    // 正确的做法是判断它们的差值是否小于一个极小值 (epsilon)
    ASSERT(std::abs(plus(0.1, 0.2) - 0.3) < 1e-9, "How to make this pass?");

    return 0;
}