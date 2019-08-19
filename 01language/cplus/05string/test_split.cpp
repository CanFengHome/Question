#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> split(const string& src, const string& delimiter)
{
    vector<string> ret;

    string str(src);
    str.erase(std::unique(str.begin(), str.end(), [&delimiter](const char& lh, const char& rh) {
        return lh == rh && delimiter.find(lh) != string::npos;
    }), str.end());

    string::size_type pos1 = 0;
    string::size_type pos2 = str.find(delimiter);
    while (pos2 != string::npos)
    {
        ret.push_back(str.substr(pos1, pos2-pos1));
        pos1 = pos2 + delimiter.size();
        pos2 = str.find(delimiter, pos1);
    }

    if (pos1 != str.size())
    {
        ret.push_back(str.substr(pos1));
    }

    return ret;
}

void test_case1()
{
    string msg = "a#b##c";
    vector<string> ret = split(msg, "#");
    for (auto& item : ret)
    {
        cout << item << " ";
    }
    std::cout << endl;
}

void test_case2()
{
    string msg = "a#b##c##d##";
    vector<string> ret = split(msg, "#");
    for (auto& item : ret)
    {
        cout << item << " ";
    }
    std::cout << endl;
}

int main()
{
    test_case1();
    test_case2();

    return 0;
}