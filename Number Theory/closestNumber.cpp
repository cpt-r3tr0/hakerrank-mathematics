#include<stdio.h>
#include<math.h>

int main()
{
    int t;
    long a,b,x,temp;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%ld%ld%ld",&a,&b,&x);
        if(a==1 && x==1)
            printf("1\n");
        else if(a==1 || b<0)
            printf("0\n");
        else
        {
            temp = pow(a,b);
            if(x<(2*(temp%x)))
                printf("%ld\n",temp-temp%x+x);
            else
                printf("%ld\n",temp-temp%x);
        }

    }
    return 0;
}
