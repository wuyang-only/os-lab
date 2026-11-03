#include <stdio.h>

int main(int argc, char *argv[])
{
    const char *name = (argc > 1) ? argv[1] : "Operating Systems Lab";
    printf("Hello, %s!\n", name);
    printf("This file is used to practise Git version control.\n");
    return 0;
}
