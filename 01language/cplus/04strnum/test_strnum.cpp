#include <iostream>
#include <string>
#include <sstream>

using namespace std;

template<typename T>
T str2num(const string& str)
{
    istringstream in(str);
    T ret = (T)0;
    in >> ret;
    return ret;
}

template<typename T>
string num2str(T val)
{
    ostringstream out;
    out << val;
    return out.str();
}

int main()
{
    string strnum="3.15";
    float num = str2num<float>(strnum);
    cout << "float: " << num << endl;

    string strNum = num2str("30");
    cout << "string num " << strNum << endl;

    return 0;
}