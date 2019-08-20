#include <iostream>

#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <dirent.h>

using namespace std;

int getFileNum(const string& root)
{
    DIR* dir = opendir(root.c_str());
    if(dir == NULL)
    {
        return 0;
    }

    int num = 0;
    struct dirent* ptr = NULL;
    while ((ptr = readdir(dir)) != NULL)
    {
        if (strcmp(ptr->d_name, ".") == 0 ||
            strcmp(ptr->d_name, "..") == 0)
        {
            continue;
        }

        if (ptr->d_type == DT_DIR)
        {
            string next=root;
            next.append("/");
            next.append(ptr->d_name);
            num += getFileNum(next);
        }
        else if (ptr->d_type == DT_REG)
        {
            ++num;
        }
    }
    closedir(dir);
    return num;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "format: ./cmd [dir]" << endl;
        exit(EXIT_FAILURE);
    }

    int num = getFileNum(argv[1]);
    cout << argv[1] << " file num: " << num << endl;

    return 0;
}