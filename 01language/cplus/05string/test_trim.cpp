#include <iostream>
#include <string>

using namespace std;

string trim(const string& str, const string& token)
{
    string result = str;
    result.erase(0, result.find_first_not_of(token));
    string::size_type endpos = result.find_last_not_of(token);
    if (endpos != string::npos)
    {
        result.erase(endpos + 1);
    }
    
    return result;
}

int main()
{
    string str = "###abc";
    str = trim(str, "#");
    cout << str << endl;

    str = "abc###";
    str = trim(str, "#");
    cout << str << endl;

    str = "##abc##";
    str = trim(str, "#");
    cout << str << endl;

    return 0;
}