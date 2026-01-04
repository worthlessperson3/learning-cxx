#include "../exercise.h"

// 数组定义在全局，初始化为 {0, 1, 0, 0, ...}
unsigned long long arr[90]{0, 1};

unsigned long long fibonacci(int i) {
    switch (i) {
        case 0:
            return 0;
        case 1:
            return 1;
        default:
            // 如果 arr[i] 不为 0，说明已经计算过，直接返回；否则计算并存入 arr[i]
            return arr[i] != 0 ? arr[i] : (arr[i] = fibonacci(i - 1) + fibonacci(i - 2));
    }
}

int main(int argc, char **argv) {
    // 90 个 unsigned long long，每个 8 字节，共 720 字节
    ASSERT(sizeof(arr) == 720, "sizeof array is size of all its elements");
    
    // ---- 不要修改以下代码 ----
    ASSERT(fibonacci(2) == 1, "fibonacci(2) should be 1");
    ASSERT(fibonacci(20) == 6765, "fibonacci(20) should be 6765");
    ASSERT(fibonacci(80) == 23416728348467685, "fibonacci(80) should be 23416728348467685");
    return 0;
}