#include "../exercise.h"
#include <vector>

// 张量即多维数组。连续存储张量即逻辑结构与存储结构一致的张量。
// 张量的步长或跨度指的是张量每个维度上坐标 +1 时，数据指针跨过的范围。

// READ: 类型别名 <https://zh.cppreference.com/w/cpp/language/type_alias>
using udim = unsigned int;

/// @brief 计算连续存储张量的步长
/// @param shape 张量的形状
/// @return 张量每维度的访问步长
std::vector<udim> strides(std::vector<udim> const &shape) {
    std::vector<udim> strides(shape.size());
    // TODO: 完成函数体，根据张量形状计算张量连续存储时的步长。
    
    // 初始化累乘变量为 1 (因为最后一个维度的步长总是 1)
    udim product = 1;

    // 从后往前遍历 shape
    // 比如 shape = [2, 3, 4]
    // i = 2: strides[2] = 1, product = 1 * 4 = 4
    // i = 1: strides[1] = 4, product = 4 * 3 = 12
    // i = 0: strides[0] = 12, product = 12 * 2 = 24
    for (int i = shape.size() - 1; i >= 0; --i) {
        strides[i] = product;
        product *= shape[i];
    }

    return strides;
}

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    ASSERT((strides({2, 3, 4}) == std::vector<udim>{12, 4, 1}), "Make this assertion pass.");
    ASSERT((strides({3, 4, 5}) == std::vector<udim>{20, 5, 1}), "Make this assertion pass.");
    // 典型的图像数据：Batch=1, RGB=3, H=224, W=224
    ASSERT((strides({1, 3, 224, 224}) == std::vector<udim>{150528, 50176, 224, 1}), "Make this assertion pass.");
    // 广播机制中的特例
    ASSERT((strides({7, 1, 1, 1, 5}) == std::vector<udim>{5, 5, 5, 5, 1}), "Make this assertion pass.");
    return 0;
}