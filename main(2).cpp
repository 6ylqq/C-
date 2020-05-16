#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#define INF 32767				//定义∞
#define	MAXV 50
typedef char InfoType;

int A[MAXV][MAXV],path[MAXV][MAXV];

typedef struct
{	int no;						            //顶点编号
	InfoType info[MAXV]={'\0'};				//顶点其他信息
} VertexType;					            //顶点类型
typedef struct
{	int edges[MAXV][MAXV];		//邻接矩阵数组
	int n,e;					//顶点数，边数
	VertexType vexs[MAXV];		//存放顶点信息
} MatGraph;						//完整的图邻接矩阵类型
int read_line(char str[], int n);
void InitGarden(MatGraph &g);
void Dispath1(MatGraph g);
void save_garden_to_file(MatGraph g);
void Dispath(MatGraph g,int dist[],int path[],int S[],int v,int a);
void Dijkstra(MatGraph g,int v,int i);
void find_way(MatGraph g);
void Floyd(MatGraph g);
int main ()
{
    int n;
    int choice;
    MatGraph g;
	while (choice!=6)
	{
		printf("下面请选择您要进行的操作:\n");
        printf("********************************************\n");
        printf("1. 输入直接相邻的两个旅游景点的名字以及它们之间的距离并将其存入文件；\n");
        printf("2. 计算给定的两个旅游景点间的最短路径\n");
        printf("3. 对公园的所有旅游景点，设计算法实现计算所有的景点对之间的最短路径，并将最短路径上的各旅游景点及每段路径长度写入磁盘文件AllPath.dat中。（提醒：若文件已存在，便会重新覆盖）\n");
        printf("4.  编写程序从文件AllPath.dat中读出所有旅游景点间的最短路径信息，到内存链表中管理\n");
        printf("5.将每对直接相连的景点间的距离存到磁盘文件中（若未使用功能1则不会重新创建文件）\n");
        printf("6.退出程序\n");
        printf("********************************************\n");
		printf("enter your choice: ");
        scanf("%d", &choice);
		switch(choice)
		{
			case 1: InitGarden(g);save_garden_to_file(g);           break;
			case 2: find_way(g);                                    break;
			case 3: Floyd(g);                                       break;
			case 4:
			break;
			case 5:
			break;
			case 6:                                                 break;
			default: printf("Error: you have entered a wrong number! ");
		}
		printf("\n");
	}
    return 0;
}

void InitGarden(MatGraph &g)
{
    int i,j;
    printf("请输入公园的景点个数：");
    scanf("%d",&g.n);
    for(i=0;i<g.n;i++)
    {
        printf("请输入第%d个景点的名字: ",i+1);
        read_line(g.vexs[i].info,MAXV);
        g.vexs[i].no=i;
    }
    for(j=0;j<g.n;j++)     //行
        for(i=0;i<g.n;i++) //列
        {
            printf("请输入%s和%s两结点间的距离: ",g.vexs[i].info,g.vexs[j].info);
            scanf("%d",&g.edges[i][j]);
        }

}

int read_line(char str[], int n)
{

	int ch, i = 0;

	while (isspace(ch = getchar()))
		;
	while (ch != '\n' && ch != EOF) {
		if (i < n)
			str[i++] = ch;
		ch = getchar();
	}
	str[i] = '\0';
	return i;
}

void Dispath1(MatGraph g)
{
    int i,j,k,s;
    FILE *fp1;
    fp1 = fopen("AllPath.dat", "w");
	int apath[MAXV],d;		//存放一条最短路径中间顶点(反向)及其顶点个数
	for (i=0;i<g.n;i++)
		for (j=0;j<g.n;j++)
		{	if (A[i][j]!=INF && i!=j)			//若顶点i和j之间存在路径
			{	fprintf(fp1,"从%s到%s的路径为:",g.vexs[i].info,g.vexs[j].info);
				k=path[i][j];
				d=0; apath[d]=j;				//路径上添加终点
				while (k!=-1 && k!=i)			//路径上添加中间点
				{	d++; apath[d]=k;
					k=path[i][k];
				}
				d++; apath[d]=i;				//路径上添加起点
				fprintf(fp1,"%s",g.vexs[apath[d]].info);			//输出起点
				for (s=d-1;s>=0;s--)			//输出路径上的中间顶点
					fprintf(fp1,",%s",g.vexs[apath[s]].info);
				fprintf(fp1,"\t路径长度为:%d\n",A[i][j]);
			}
		}
}

void Floyd(MatGraph g)							//Floyd算法
{
	int i,j,k;
	for (i=0;i<g.n;i++)
		for (j=0;j<g.n;j++)
		{	A[i][j]=g.edges[i][j];
			if (i!=j && g.edges[i][j]<INF)
				path[i][j]=i;					//顶点i到j有边时
			else
				path[i][j]=-1;				//顶点i到j没有边时
		}
	for (k=0;k<g.n;k++)						//依次考察所有顶点
	{	for (i=0;i<g.n;i++)
			for (j=0;j<g.n;j++)
				if (A[i][j]>A[i][k]+A[k][j])
				{	A[i][j]=A[i][k]+A[k][j];	//修改最短路径长度
					path[i][j]=path[k][j];		//修改最短路径
				}
	}
	Dispath1(g);							//输出最短路径
}

void save_garden_to_file(MatGraph g)
{
	int i,j;
	FILE* fp;
	fp = fopen("garden.dat", "w");
	/*if ((fp = fopen("garden.dat", "w")) == NULL)
	{
		printf("TIPS：can not open goods file database!\n");
		return;
	}*/
	for(i=0;i<g.n;i++)
        for(j=0;j<g.n;j++)
        {
            if((fprintf(fp, "%s与%s之间的距离为: ", g.vexs[i].info,g.vexs[j].info))==0)
            {
                printf("erro!\n");
                return;
            }
            else{
            if(g.edges[i][j]!=INF)
                fprintf(fp, "%d\n", g.edges[i][j]);
            else
                fprintf(fp, "错误：两景点之间没有直接路径\n");
       } }
	fclose(fp);
	printf("Save successfully.\n");
}

void Dispath(MatGraph g,int dist[],int path[],int S[],int v,int i)//输出从顶点v出发的所有最短路径
{
    int j,k;
	int apath[MAXV],d;					//存放一条最短路径(逆向)及其顶点个数
	//for (i=0;i<g.n;i++)					//循环输出从顶点v到i的路径
		if (S[i]==1 && i!=v)
		{	printf("从顶点%d到顶点%d的路径长度为:%d\t路径为:",v,i,dist[i]);
			d=0; apath[d]=i;			//添加路径上的终点
			k=path[i];
			if (k==-1)					//没有路径的情况
				printf("无路径\n");
			else						//存在路径时输出该路径
			{	while (k!=v)
				{	d++; apath[d]=k;
					k=path[k];
				}
				d++; apath[d]=v;		//添加路径上的起点
				printf("%d",apath[d]);	//先输出起点
				for (j=d-1;j>=0;j--)	//再输出其他顶点
					printf(",%d",apath[j]);
				printf("\n");
			}
		}
}

void Dijkstra(MatGraph g,int v,int a)	//Dijkstra算法
{
    int dist[MAXV],path[MAXV];
	int S[MAXV];				//S[i]=1表示顶点i在S中, S[i]=0表示顶点i在U中
	int Mindis,i,j,u;
	for (i=0;i<g.n;i++)
	{	dist[i]=g.edges[v][i];	//距离初始化
		S[i]=0;					//S[]置空
		if (g.edges[v][i]<INF)	//路径初始化
			path[i]=v;			//顶点v到顶点i有边时，置顶点i的前一个顶点为v
		else
			path[i]=-1;			//顶点v到顶点i没边时，置顶点i的前一个顶点为-1
	}
	S[v]=1;path[v]=0;			//源点编号v放入S中
	for (i=0;i<g.n-1;i++)		//循环直到所有顶点的最短路径都求出
	{	Mindis=INF;				//Mindis置最大长度初值
		for (j=0;j<g.n;j++)		//选取不在S中（即U中）且具有最小最短路径长度的顶点u
			if (S[j]==0 && dist[j]<Mindis)
			{	u=j;
				Mindis=dist[j];
			}
		S[u]=1;					//顶点u加入S中
		for (j=0;j<g.n;j++)		//修改不在S中（即U中）的顶点的最短路径
			if (S[j]==0)
				if (g.edges[u][j]<INF && dist[u]+g.edges[u][j]<dist[j])
				{	dist[j]=dist[u]+g.edges[u][j];
					path[j]=u;
				}
	}
	Dispath(g,dist,path,S,v,a);	//输出最短路径
}

void find_way(MatGraph g)
{
    int i,v,a;
    char n[MAXV]={'\0'},m[MAXV]={'\0'};
    printf("请输入起点和终点：\n");
    printf("起点：");
    read_line(n,MAXV);
    printf("终点：");
    read_line(m,MAXV);
    for(v=0;v<g.n;v++)
    {
        if(strcmp(g.vexs[v].info,n)==0)
            break;
    }
    if(v==g.n)
    {
        printf("起点不存在\n");
        return;
    }
    for(a=0;a<g.n;a++)
    {
        if(strcmp(g.vexs[a].info,m)==0)
            break;
    }
    if(v==g.n)
    {
        printf("终点不存在\n");
        return;
    }
    Dijkstra(g,v,a);
}
