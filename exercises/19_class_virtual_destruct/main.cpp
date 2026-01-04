#include "../exercise.h"

// READ: 静态字段 <https://zh.cppreference.com/w/cpp/language/static>
// READ: 虚析构函数 <https://zh.cppreference.com/w/cpp/language/destructor>

struct A {
    // 1. 静态成员在类内只能声明，不能赋值（除非是 const 或 inline）
    static int num_a;

    A() {
        ++num_a;
    }
    
    // 2. 关键点：基类的析构函数必须是 virtual 的！
    // 否则 delete ab (A类型指针) 时，不会调用子类 B 的析构函数
    virtual ~A() {
        --num_a;
    }

    virtual char name() const {
        return 'A';
    }
};

struct B final : public A {
    static int num_b;

    B() {
        ++num_b;
    }
    ~B() {
        --num_b;
    }

    char name() const final {
        return 'B';
    }
};

// 3. 在类外定义并初始化静态成员变量
int A::num_a = 0;
int B::num_b = 0;

int main(int argc, char **argv) {
    auto a = new A;
    auto b = new B;
    
    // 逻辑解析：
    // a 是 A 对象 -> A::num_a + 1
    // b 是 B 对象 -> B 继承 A，先构造 A (num_a + 1)，再构造 B (num_b + 1)
    // 此时 num_a = 2, num_b = 1
    ASSERT(A::num_a == 2, "Fill in the correct value for A::num_a");
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    ASSERT(a->name() == 'A', "Fill in the correct value for a->name()");
    ASSERT(b->name() == 'B', "Fill in the correct value for b->name()");

    delete a;
    delete b;
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    A *ab = new B; // 派生类指针可以随意转换为基类指针
    // new B -> 构造 A (num_a=1) -> 构造 B (num_b=1)
    ASSERT(A::num_a == 1, "Fill in the correct value for A::num_a");
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    // 多态生效：实际对象是 B，所以调用 B::name()
    ASSERT(ab->name() == 'B', "Fill in the correct value for ab->name()");

    // TODO: 基类指针无法随意转换为派生类指针，补全正确的转换语句
    // 4. 使用 dynamic_cast 进行安全的向下转型 (Downcasting)
    // 这里 ab 是指针，我们要转换成 B& 引用，需要解引用 *ab
    B &bb = dynamic_cast<B&>(*ab); 
    ASSERT(bb.name() == 'B', "Fill in the correct value for bb->name()");

    // TODO: ---- 以下代码不要修改，通过改正类定义解决编译问题 ----
    // 这里的 delete ab 能够让 ASSERT 通过，全靠 ~A() 加上了 virtual
    delete ab; // 通过指针可以删除指向的对象，即使是多态对象
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    return 0;
}