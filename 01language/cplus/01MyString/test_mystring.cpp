#include <iostream>

#include "MyString.hpp"

int main()
{
    MyString str("hello world");
    str.print();
    std::cout << "=============" << std::endl;

    MyString strCopy(str);
    strCopy.print();
    std::cout << "=============" << std::endl;

    MyString strAssign("assign");
    strAssign.print();
    strAssign = str;
    std::cout << "after assign: ";
    strAssign.print();
    std::cout << "=============" << std::endl;


    return 0;
}