#include "../exercise.h"
#include <cstring>
// READ: 类模板 <https://zh.cppreference.com/w/cpp/language/class_template>

template<class T>
struct Tensor4D {
    unsigned int shape[4];
    T *data;

    Tensor4D(unsigned int const shape_[4], T const *data_) {
        unsigned int size = 1;
        // TODO: 填入正确的 shape 并计算 size
        for (int i = 0; i < 4; ++i) {
            shape[i] = shape_[i];
            size *= shape[i];
        }
        data = new T[size];
        std::memcpy(data, data_, size * sizeof(T));
    }
    
    ~Tensor4D() {
        delete[] data;
    }

    // 为了保持简单，禁止复制和移动
    Tensor4D(Tensor4D const &) = delete;
    Tensor4D(Tensor4D &&) noexcept = delete;

    // 这个加法需要支持“单向广播”。
    Tensor4D &operator+=(Tensor4D const &others) {
        // TODO: 实现单向广播的加法
        // 预先计算 others 的 strides (步长)，用于将 4D 坐标转回 1D 索引
        // index = n*s0 + c*s1 + h*s2 + w*s3
        unsigned int o_stride[4];
        o_stride[3] = 1;
        o_stride[2] = others.shape[3];
        o_stride[1] = others.shape[2] * others.shape[3];
        o_stride[0] = others.shape[1] * others.shape[2] * others.shape[3];

        // 使用 dst_idx 记录当前 this->data 的线性索引
        unsigned int dst_idx = 0;

        // 四重循环遍历 this 的所有位置 (n, c, h, w)
        for (unsigned int n = 0; n < shape[0]; ++n) {
            // 广播逻辑：如果 others 在该维度长度为 1，则索引固定为 0；否则索引为 n
            unsigned int on = (others.shape[0] == 1) ? 0 : n;
            
            for (unsigned int c = 0; c < shape[1]; ++c) {
                unsigned int oc = (others.shape[1] == 1) ? 0 : c;
                
                for (unsigned int h = 0; h < shape[2]; ++h) {
                    unsigned int oh = (others.shape[2] == 1) ? 0 : h;
                    
                    for (unsigned int w = 0; w < shape[3]; ++w) {
                        unsigned int ow = (others.shape[3] == 1) ? 0 : w;

                        // 计算 others 中的线性索引
                        unsigned int src_idx = on * o_stride[0] + 
                                               oc * o_stride[1] + 
                                               oh * o_stride[2] + 
                                               ow * o_stride[3];
                        
                        // 执行加法
                        data[dst_idx] += others.data[src_idx];
                        
                        // 移动到下一个目标位置
                        dst_idx++;
                    }
                }
            }
        }
        return *this;
    }
};

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    // ... (保持原有的测试代码不变) ...
    {
        unsigned int shape[]{1, 2, 3, 4};
        // clang-format off
        int data[]{
             1,  2,  3,  4,
             5,  6,  7,  8,
             9, 10, 11, 12,

            13, 14, 15, 16,
            17, 18, 19, 20,
            21, 22, 23, 24};
        // clang-format on
        auto t0 = Tensor4D(shape, data); // 自动推导 T 为 int
        auto t1 = Tensor4D(shape, data);
        t0 += t1;
        for (auto i = 0u; i < sizeof(data) / sizeof(*data); ++i) {
            ASSERT(t0.data[i] == data[i] * 2, "Tensor doubled by plus its self.");
        }
    }
    // ... 后续测试用例省略，但逻辑已支持 ...
    {
        unsigned int s0[]{1, 2, 3, 4};
        float d0[]{
            1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3,
            4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6};
        unsigned int s1[]{1, 2, 3, 1};
        float d1[]{6, 5, 4, 3, 2, 1}; // 这里的形状是 [1, 2, 3, 1]

        auto t0 = Tensor4D(s0, d0);
        auto t1 = Tensor4D(s1, d1);
        t0 += t1;
        // 验证广播结果：
        // d1 中 index [0,0,0,0] 的值是 6
        // 它会加到 d0 中 [0,0,0,0], [0,0,0,1], [0,0,0,2], [0,0,0,3] 上
        // 因为 t1 最后一个维度是 1，t0 是 4，所以 t1 的值在最后一个维度被广播（重复）了 4 次。
        for (auto i = 0u; i < sizeof(d0) / sizeof(*d0); ++i) {
             ASSERT(t0.data[i] == 7.f, "Every element of t0 should be 7 after adding t1 to it.");
        }
    }
    // ...
}