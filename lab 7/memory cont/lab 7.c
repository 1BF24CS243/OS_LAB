#include<stdio.h>

int main()
{
    int b[5],p[5],temp[5];
    int i,j,nb,np,best,worst;

    printf("Enter number of memory blocks: ");
    scanf("%d",&nb);

    printf("Enter sizes of memory blocks:\n");
    for(i=0;i<nb;i++)
        scanf("%d",&b[i]);

    printf("Enter number of processes: ");
    scanf("%d",&np);

    printf("Enter sizes of processes:\n");
    for(i=0;i<np;i++)
        scanf("%d",&p[i]);

    // First Fit
    for(i=0;i<nb;i++) temp[i]=b[i];

    printf("\n--- First Fit ---\n");
    for(i=0;i<np;i++)
    {
        for(j=0;j<nb;j++)
        {
            if(temp[j]>=p[i])
            {
                printf("%d -> %d\n",p[i],j+1);
                temp[j]-=p[i];
                break;
            }
        }
    }

    // Best Fit
    for(i=0;i<nb;i++) temp[i]=b[i];

    printf("\n--- Best Fit ---\n");
    for(i=0;i<np;i++)
    {
        best=-1;

        for(j=0;j<nb;j++)
        {
            if(temp[j]>=p[i])
            {
                if(best==-1 || temp[j]<temp[best])
                    best=j;
            }
        }

        if(best!=-1)
        {
            printf("%d -> %d\n",p[i],best+1);
            temp[best]-=p[i];
        }
    }

    // Worst Fit
    for(i=0;i<nb;i++) temp[i]=b[i];

    printf("\n--- Worst Fit ---\n");
    for(i=0;i<np;i++)
    {
        worst=-1;

        for(j=0;j<nb;j++)
        {
            if(temp[j]>=p[i])
            {
                if(worst==-1 || temp[j]>temp[worst])
                    worst=j;
            }
        }

        if(worst!=-1)
        {
            printf("%d -> %d\n",p[i],worst+1);
            temp[worst]-=p[i];
        }
    }

    return 0;
}
