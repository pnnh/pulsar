module;
#include <iostream>

export module foo;

export class foo
{
public:
    foo();
    void helloworld();
};

foo::foo() = default;
void foo::helloworld() { std::cout << "hello world\n"; }