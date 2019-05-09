#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int j, max, vCount=0, len=0, maxInd, mudou=0;
    int p[1000000];
    char c;
    while((c = getchar()) != 'f')
    {
        if (c == 'c')
        {
            scanf("%d", &p[len]);
            ++len;
        }
        else if (c == 'v')
        {
          if(vCount == len){
            printf("0\n");
            continue;
          }
            max = p[0];
            maxInd = 0;
            for(j=1; j<len; j++)
                if (p[j] > max)
                {
                    max = p[j];
                    maxInd = j;
                    mudou = 1;
                }
            if(mudou)
            {
                printf("%d\n", maxInd+1);
                p[maxInd] = 0;
                mudou = 0;
            } 
            else
            {
                printf("1\n");
                p[0] = 0;
            }
            vCount++;
        }
    }
    return 0;
}
