#include <stdio.h>

int main(int argc, char const *argv[])
{
    int a, b;

    /* On s'assure qu'il n'y aura pas de problème de bufferisation */
    setvbuf(stdout, NULL, _IONBF, 0);

    while (1) {
        scanf("%d %d", &a, &b);
        printf("%d\n", a - b);
    }

    return 0;
}