#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{   
    char var[6] = "RUN_0", *pt = NULL;

    while (NULL != (pt = getenv(var))) {
        var[4]++;
        printf("%s\n", pt);
    }

    return 0;
}
