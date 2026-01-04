#include "../exercise.h"

// READ: 虚函数 <https://zh.cppreference.com/w/cpp/language/virtual>

struct A {
    virtual char virtual_name() const {
        return 'A';
    }
    char direct_name() const {
        return 'A';
    }
};
struct B : public A {
    // READ: override <https://zh.cppreference.com/w/cpp/language/override>
    char virtual_name() const override {
        return 'B';
    }
    char direct_name() const {
        return 'B';
    }
};
struct C : public B {
    // READ: final <https://zh.cppreference.com/w/cpp/language/final>
    // final 表示之后的子类（比如 D）不能再重写这个函数了
    char virtual_name() const final {
        return 'C';
    }
    char direct_name() const {
        return 'C';
    }
};
struct D : public C {
    // D 无法重写 virtual_name，因为它在 C 中被标记为 final
    // 所以 D 的 virtual_name 就是 C 的版本
    char direct_name() const {
        return 'D';
    }
};

int main(int argc, char **argv) {
    constexpr auto MSG = "Replace '?' with its correct name.";

    A a;
    B b;
    C c;
    D d;

    // 第一组：直接对象调用
    // 没有指针/引用干扰，对象是谁就调谁的
    ASSERT(a.virtual_name() == 'A', MSG);
    ASSERT(b.virtual_name() == 'B', MSG);
    ASSERT(c.virtual_name() == 'C', MSG);
    ASSERT(d.virtual_name() == 'C', MSG); // D 继承自 C，且 C 为 final，D 没有自己的重写
    ASSERT(a.direct_name() == 'A', MSG);
    ASSERT(b.direct_name() == 'B', MSG);
    ASSERT(c.direct_name() == 'C', MSG);
    ASSERT(d.direct_name() == 'D', MSG);

    // 第二组：父类引用指向子类对象
    // rab 是 A 类型的引用，实际指向 B
    A &rab = b;
    B &rbc = c;
    C &rcd = d;

    // virtual_name 是虚函数 -> 看实际对象 -> 实际是 B -> 'B'
    ASSERT(rab.virtual_name() == 'B', MSG);
    ASSERT(rbc.virtual_name() == 'C', MSG);
    ASSERT(rcd.virtual_name() == 'C', MSG); // D 实际上用的是 C 的实现

    // direct_name 是非虚函数 -> 看引用类型 -> 引用是 A -> 'A'
    ASSERT(rab.direct_name() == 'A', MSG); // 静态绑定：编译器只看到 rab 是 A
    ASSERT(rbc.direct_name() == 'B', MSG); // 静态绑定：编译器只看到 rbc 是 B
    ASSERT(rcd.direct_name() == 'C', MSG); // 静态绑定：编译器只看到 rcd 是 C

    // 第三组：跨级引用
    A &rac = c; // A 引用指向 C 对象
    B &rbd = d; // B 引用指向 D 对象

    ASSERT(rac.virtual_name() == 'C', MSG); // 动态绑定：实际是 C
    ASSERT(rbd.virtual_name() == 'C', MSG); // 动态绑定：实际是 D (D 使用 C 的实现)
    
    ASSERT(rac.direct_name() == 'A', MSG); // 静态绑定：引用类型是 A
    ASSERT(rbd.direct_name() == 'B', MSG); // 静态绑定：引用类型是 B

    // 第四组：基类引用指向最底层对象
    A &rad = d;

    ASSERT(rad.virtual_name() == 'C', MSG); // 实际是 D (继承自 C) -> 'C'
    ASSERT(rad.direct_name() == 'A', MSG);  // 引用类型是 A -> 'A'

    return 0;
}