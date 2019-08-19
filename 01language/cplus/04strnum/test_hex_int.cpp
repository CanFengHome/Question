#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int strHex2int(const string& str)
{
    stringstream stream;
    stream << std::hex << str;
    int ret = 0;
    stream >> ret;
    return ret;
}

string int2strHex(char num)
{
    char buf[16];
    sprintf(buf, "0x%02x", num);
    return buf;
}

int main()
{
    string strHex = "0x41";
    int ch = strHex2int(strHex);
    printf("use stringstream %s is char: %c\n", strHex.c_str(), ch);

    int ch1 = std::stoi(strHex, 0, 16);
    printf("use sstoi %s is char: %c\n", strHex.c_str(), ch1);

    string str = int2strHex('A');
    printf("%s hex is %s\n", "A", str.c_str());

    return 0;
}