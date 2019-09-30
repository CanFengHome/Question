#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main()
{
    int (*func)(int a, int b);
    int a = 5;
    int b = 3;

    const char* file = "../lib/libmycal.so";
    void* handle = dlopen(file, RTLD_LAZY);
    if(handle == NULL) {
        printf("Open library %s error: %s\n", file, dlerror());
        return -1;
    }

    func = dlsym(handle, "add");
    char* error = NULL;
    if((error = dlerror()) != NULL) {
        printf("Symbol add not found: %s\n", error);
        dlclose(handle);
        return -1;
    }

    printf("%d + %d = %d\n", a, b, func(a, b));

    dlclose(handle);

    return 0;
}