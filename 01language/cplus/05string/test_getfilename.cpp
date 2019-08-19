#include <iostream>
#include <string>

using namespace std;

string getFileName(const string& dir)
{
    string::size_type pos = dir.find_last_of("/");
    if (pos != string::npos && pos < dir.size())
    {
        return dir.substr(pos+1);
    }
    else
    {
        return "";
    }
    
}

int main()
{
    const string strMsg1 = "/home/dir/file.txt";
    cout << strMsg1 << " file: " << getFileName(strMsg1) << endl;

    const string strMsg2 = "/";
    cout << strMsg2 << " file: " << getFileName(strMsg2) << endl;

    const string strMsg3 = "/home";
    cout << strMsg3 << " file: " << getFileName(strMsg3) << endl;

    return 0;
}