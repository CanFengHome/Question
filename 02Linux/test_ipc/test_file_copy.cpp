#include <iostream>
#include <string>

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

void err_exit(const char* err);
int getFileSize(const char* file);
int createFile(const char* file, off_t length);

typedef struct _Data
{
    std::string srcFile;
    std::string destFile;
    int offset;
    int len;
} Data;

void child_work(const Data& data);

int main(int argc, char* argv[])
{
    if (argc != 3) {
        std::cout << "format: ./cmd srcfile destfile" << std::endl;
        exit(EXIT_FAILURE);
    }

    int size = getFileSize(argv[1]);

    const int process_num = 10;
    const int process_step = process_num / size;

    for (int i=0; i<process_num; ++i)
    {
        pid_t pid = fork();
        if (pid < 0)
            err_exit("fork");

        if (pid == 0)
        {
            Data data;
            data.srcFile = argv[1];
            data.destFile = argv[2];
            data.offset = (i * process_step);
            data.len = process_step;
            if (i == (process_num - 1))
            {
                data.len = size - (process_num-1) * process_step;
            }

            child_work(data);
            exit(EXIT_SUCCESS);
        }
    }

    for (int i=0; i<process_num; ++i)
    {
        wait(NULL);
    }

    return 0;
}

void err_exit(const char* err)
{
    perror(err);
    exit(EXIT_FAILURE);
}

int getFileSize(const char* file)
{
    struct stat statbuf;
    if (stat(file, &statbuf) < 0) {
        err_exit("stat");
    }

    return (int)statbuf.st_size;
}

int createFile(const char* file, off_t length)
{
    int ret = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (ret < 0) {
        err_exit("open write");
    }

    if (ftruncate(ret, length) < 0)
    {
        err_exit("ftruncate");
    }

    return ret;
}

FILE* openFile(const std::string& file, const char *mode)
{
    FILE* pFile = fopen(file.c_str(), mode);
    if (pFile == NULL)
    {
        err_exit("fopen");
    }
    return pFile;
}

void child_work(const Data& data)
{
    FILE* pSrcFile = openFile(data.srcFile, "r");
    FILE* pDestFile = openFile(data.destFile, "w+");
    int len = data.len;

    if (fseek(pSrcFile, (off_t)data.offset, SEEK_SET) < 0)
    {
        err_exit("lseek src");
    }
    
    if (fseek(pDestFile, (off_t)data.offset, SEEK_SET) < 0)
    {
        err_exit("lseek dest");
    }
    
    while (len > 0)
    {
        fputc(fgetc(pSrcFile), pDestFile);
        --len;
    }
    
    fclose(pDestFile);
    fclose(pSrcFile);
}
