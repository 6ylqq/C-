#include <stdio.h>
int main()
{int a,b,c;
    printf("Enter a 24-hour time: ");
    scanf("%d:%d",&a,&b);
    if(b<60&&b>=0)
    {
	if(a>12&&a<24)
    {c=a-12;
    printf("Equivalent 12-hour time: %d:%02d PM\n",c,b);}
    else if(a<12&&a>0)
	printf("Equivalent 12-hour time: %d:%02d AM\n",a,b);
	else if (a==12)
	printf("Equivalent 12-hour time: %d:%02d PM\n",a,b);
	else if(a==0||a==24)
	printf("Equivalent 12-hour time: 12:%02d AM\n",b);
	else
	printf("wrong!\n");
    }
    else printf("wrong!\n");
    return 0;
}
