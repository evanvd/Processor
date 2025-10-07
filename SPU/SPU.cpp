#include <stdio.h>

int main()
{
    FILE* np = fopen("native_code.txt", "r");
    int hui [4] = {0, 0, 0, 0};
    for (size_t testNum = 0; testNum < 4; testNum++)
    {
        fscanf(np, "%d",&hui[testNum]);
        printf("%d ",hui[testNum]);
    }
    
}