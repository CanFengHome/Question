#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "format: ./cmd [filename]" << endl;
        exit(EXIT_FAILURE);
    }

    struct stat st;
    if (stat(argv[1], &st) < 0)
    {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    cout << argv[1] << " size: " << st.st_size << endl;

    return 0;
}