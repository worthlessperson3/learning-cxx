#include "../exercise.h"
#include <cstring>
#include <vector>

// READ: std::vector <https://zh.cppreference.com/w/cpp/container/vector>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    {
        std::vector<int> vec{1, 2, 3, 4, 5};
        ASSERT(vec.size() == 5, "Fill in the correct value.");
        // THINK: `std::vector` 的大小是什么意思？与什么有关？
        // vector 对象本身通常包含 3 个指针 (begin, end, end_of_storage)。
        // 在 64 位系统中，指针大小为 8 字节，所以 sizeof(vec) = 3 * 8 = 24。
        ASSERT(sizeof(vec) == 24, "Fill in the correct value.");
        int ans[]{1, 2, 3, 4, 5};
        // 使用 .data() 获取底层数组指针
        ASSERT(std::memcmp(vec.data(), ans, sizeof(ans)) == 0, "Fill in the correct values.");
    }
    {
        std::vector<double> vec{1, 2, 3, 4, 5};
        {
            ASSERT(vec.size() == 5, "Fill in the correct value.");
            ASSERT(sizeof(vec) == 24, "Fill in the correct value.");
            double ans[]{1, 2, 3, 4, 5};
            ASSERT(std::memcmp(vec.data(), ans, sizeof(ans)) == 0, "Fill in the correct values.");
        }
        {
            vec.push_back(6);
            ASSERT(vec.size() == 6, "Fill in the correct value.");
            // 无论堆上分配了多少内存，栈上的 vector 对象本身大小不变
            ASSERT(sizeof(vec) == 24, "Fill in the correct value.");
            vec.pop_back();
            ASSERT(vec.size() == 5, "Fill in the correct value.");
            ASSERT(sizeof(vec) == 24, "Fill in the correct value.");
        }
        {
            vec[4] = 6;
            ASSERT(vec[0] == 1, "Fill in the correct value.");
            ASSERT(vec[1] == 2, "Fill in the correct value.");
            ASSERT(vec[2] == 3, "Fill in the correct value.");
            ASSERT(vec[3] == 4, "Fill in the correct value.");
            ASSERT(vec[4] == 6, "Fill in the correct value.");
        }
        {
            // THINK: `std::vector` 插入删除的时间复杂度是什么？
            // 目标：{1, 1.5, 2, 3, 4, 6}。在 index 1 的位置插入 1.5
            // insert 接受迭代器：vec.begin() + 1
            vec.insert(vec.begin() + 1, 1.5);
            ASSERT((vec == std::vector<double>{1, 1.5, 2, 3, 4, 6}), "Make this assertion pass.");
            
            // 目标：{1, 1.5, 2, 4, 6}。删除了 index 3 的位置 (值为 3)
            // erase 接受迭代器：vec.begin() + 3
            vec.erase(vec.begin() + 3);
            ASSERT((vec == std::vector<double>{1, 1.5, 2, 4, 6}), "Make this assertion pass.");
        }
        {
            vec.shrink_to_fit();
            // 当前有 5 个元素，shrink_to_fit 后 capacity 变为 5
            ASSERT(vec.capacity() == 5, "Fill in the correct value.");
            vec.clear();
            ASSERT(vec.empty(), "`vec` is empty now.");
            ASSERT(vec.size() == 0, "Fill in the correct value.");
            // clear() 通常不释放内存，只重置 size，所以 capacity 还是 5
            ASSERT(vec.capacity() == 5, "Fill in the correct value.");
        }
    }
    {
        // 构造 48 个 'z'
        std::vector<char> vec(48, 'z'); 
        ASSERT(vec[0] == 'z', "Make this assertion pass.");
        ASSERT(vec[47] == 'z', "Make this assertion pass.");
        ASSERT(vec.size() == 48, "Make this assertion pass.");
        ASSERT(sizeof(vec) == 24, "Fill in the correct value.");
        {
            auto capacity = vec.capacity(); // 此时 capacity 至少是 48
            vec.resize(16);
            ASSERT(vec.size() == 16, "Fill in the correct value.");
            // resize 变小不会自动减小 capacity
            ASSERT(vec.capacity() == capacity, "Fill in a correct identifier.");
        }
        {
            vec.reserve(256);
            ASSERT(vec.size() == 16, "Fill in the correct value.");
            ASSERT(vec.capacity() == 256, "Fill in the correct value.");
        }
        {
            vec.push_back('a');
            vec.push_back('b');
            vec.push_back('c');
            vec.push_back('d');
            // 原来 16 个 + 新增 4 个 = 20
            ASSERT(vec.size() == 20, "Fill in the correct value.");
            ASSERT(vec.capacity() == 256, "Fill in the correct value.");
            ASSERT(vec[15] == 'z', "Fill in the correct value.");
            ASSERT(vec[16] == 'a', "Fill in the correct value.");
            ASSERT(vec[17] == 'b', "Fill in the correct value.");
            ASSERT(vec[18] == 'c', "Fill in the correct value.");
            ASSERT(vec[19] == 'd', "Fill in the correct value.");
        }
    }

    return 0;
}