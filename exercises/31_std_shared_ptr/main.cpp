#include "../exercise.h"
#include <memory>
#include <tuple> // std::ignore needed for some compilers/standards

int main(int argc, char **argv) {
    auto shared = std::make_shared<int>(10);
    std::shared_ptr<int> ptrs[]{shared, shared, shared};

    std::weak_ptr<int> observer = shared;
    // 1. shared(1) + ptrs[0](1) + ptrs[1](1) + ptrs[2](1) = 4
    ASSERT(observer.use_count() == 4, "");

    ptrs[0].reset();
    // 2. ptrs[0] 释放。剩余: shared, ptrs[1], ptrs[2] = 3
    ASSERT(observer.use_count() == 3, "");

    ptrs[1] = nullptr;
    // 3. ptrs[1] 释放。剩余: shared, ptrs[2] = 2
    ASSERT(observer.use_count() == 2, "");

    ptrs[2] = std::make_shared<int>(*shared);
    // 4. ptrs[2] 指向了一个堆上的新 int(10)，放弃了对旧对象的引用。
    // 旧对象剩余: shared = 1
    ASSERT(observer.use_count() == 1, "");

    ptrs[0] = shared;
    ptrs[1] = shared;
    ptrs[2] = std::move(shared);
    // 5. shared 被 move 给 ptrs[2]，shared 变为空。
    // 引用者: ptrs[0], ptrs[1], ptrs[2] = 3
    ASSERT(observer.use_count() == 3, "");

    std::ignore = std::move(ptrs[0]);
    ptrs[1] = std::move(ptrs[1]);
    ptrs[1] = std::move(ptrs[2]);
    // 6. 详解见下方。最终引用者: ptrs[0], ptrs[1] = 2
    ASSERT(observer.use_count() == 2, "");

    shared = observer.lock();
    // 7. observer 观测的对象被 shared 重新获取。引用者: ptrs[0], ptrs[1], shared = 3
    ASSERT(observer.use_count() == 3, "");

    shared = nullptr;
    for (auto &ptr : ptrs) ptr = nullptr;
    // 8. 所有 shared_ptr 都置空或重置，引用计数归零，对象析构。
    ASSERT(observer.use_count() == 0, "");

    shared = observer.lock();
    // 9. 对象已销毁，lock() 返回空指针，引用计数仍为 0。
    ASSERT(observer.use_count() == 0, "");

    return 0;
}