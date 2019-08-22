#include <iostream>
#include <string>

template<typename T, typename U>
decltype(auto) fun(T lh, U rh)
{
    return lh + rh;
}

int main()
{
    std::string msg = fun(std::string("hello"), std::string(" world"));
    std::cout << msg << std::endl;

    double ret = fun(3, 5.0);
    std::cout << ret << std::endl;

    return 0;
}