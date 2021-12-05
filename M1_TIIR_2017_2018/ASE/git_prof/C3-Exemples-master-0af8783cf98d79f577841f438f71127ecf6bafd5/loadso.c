#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
int main(int argc, char **argv) {
    void *handle;
    void (*hellofct)();
    char *error;
    handle = dlopen ("libhello.so", RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        return 1;
    }
    dlerror();    /* Clear any existing error */
    hellofct = dlsym(handle, "hello");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        return 1;
    }
    (*hellofct)();
    dlclose(handle);
    return 0;
}
