#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) 
{
    if (argc < 3) 
    {
        fprintf(stderr, "Usage: %s <number1> <number2>\n", argv[0]);
        return 1;
    }
    
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    printf("%s + %s = %d\n", argv[1], argv[2], a + b);
    
    return 0;
}
