#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
    printf("Bonjour\n");
    fork(); 
    printf("Au revoir\n"); /* On aura deux fois le message à cause du fork */
    
    return 0;
}
