#include "../exercise.h"
#include <cmath>

enum class DataType {
    Float,
    Double,
};

/// @brief Tagged union 即标签化联合体，是联合体的一种常见应用。
///        Rust enum 在实现上就是标签化联合体。
struct TaggedUnion {
    DataType type;
    // NOTICE: struct/union 可以相互任意嵌套。
    union {
        float f;
        double d;
    };
};

// TODO: 将这个函数模板化用于 sigmoid_dyn
// 只需要把具体的 float 类型替换为模板参数 T 即可
template <typename T>
T sigmoid(T x) {
    return 1 / (1 + std::exp(-x));
}

TaggedUnion sigmoid_dyn(TaggedUnion x) {
    TaggedUnion ans{x.type};
    
    // TODO: 根据 type 调用 sigmoid
    // 这里的 switch 就是“手动分发”，根据运行时标签决定访问 union 的哪个字段
    switch (x.type) {
        case DataType::Float:
            ans.f = sigmoid(x.f); // 自动推导 T 为 float
            break;
        case DataType::Double:
            ans.d = sigmoid(x.d); // 自动推导 T 为 double
            break;
    }
    
    return ans;
}

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    TaggedUnion xf{DataType::Float};
    xf.f = 5.f;
    auto yf = sigmoid_dyn(xf);
    ASSERT(yf.type == DataType::Float, "type mismatch");
    ASSERT(yf.f == 1 / (1 + std::exp(-5.f)), "sigmoid float");

    TaggedUnion xd{DataType::Double};
    xd.d = 5.0;
    auto yd = sigmoid_dyn(xd);
    ASSERT(yd.type == DataType::Double, "type mismatch");
    ASSERT(yd.d == 1 / (1 + std::exp(-5.0)), "sigmoid double");
    return 0;
}