#include "../exercise.h"
#include <map>

// READ: `std::map` <https://zh.cppreference.com/w/cpp/container/map>
// READ: `std::unordered_map` <https://zh.cppreference.com/w/cpp/container/unordered_map>

template<class k, class v>
bool key_exists(std::map<k, v> const &map, k const &key) {
    // TODO: 实现函数
    // 方法 1: 使用 find()。如果返回的迭代器不等于 end()，说明找到了。
    return map.find(key) != map.end();
    
    // 方法 2: 使用 count()。对于 std::map，count 返回 1 (存在) 或 0 (不存在)。
    // return map.count(key) > 0;
    
    // 方法 3 (C++20): map.contains(key);
}

template<class k, class v>
void set(std::map<k, v> &map, k key, v value) {
    // TODO: 实现函数
    // 使用下标操作符 [] 是最简单的方法。
    // 1. 如果 key 不存在，它会创建一个默认值并插入，然后返回引用，我们再赋值。
    // 2. 如果 key 已存在，它直接返回现有 value 的引用，我们覆盖它。
    map[key] = value;
    
    // 另外一种写法是 map.insert_or_assign(key, value) (C++17)
}

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    using namespace std::string_literals;

    std::map<std::string, std::string> secrets;

    set(secrets, "hello"s, "world"s);
    ASSERT(key_exists(secrets, "hello"s), "\"hello\" shoud be in `secrets`");
    ASSERT(!key_exists(secrets, "foo"s), "\"foo\" shoud not be in `secrets`");

    set(secrets, "foo"s, "bar"s);
    set(secrets, "Infini"s, "Tensor"s);
    ASSERT(secrets["hello"] == "world", "hello -> world");
    ASSERT(secrets["foo"] == "bar", "foo -> bar");
    ASSERT(secrets["Infini"] == "Tensor", "Infini -> Tensor");

    set(secrets, "hello"s, "developer"s);
    ASSERT(secrets["hello"] == "developer", "hello -> developer");

    return 0;
}