#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<iostream>

#define MaxSize 100
#define MAXV 10
#define INF 32767				//定义∞

typedef char ElemType;
typedef int InfoType;
typedef struct{
	char search[MaxSize];
}Search;

typedef struct {
	int no;						//顶点的编号
	char name[MaxSize];				//顶点的其他信息
}VertexType;					//顶点的类型

typedef struct {
	int edges[MAXV][MAXV];		//邻接矩阵数组
	int n, e;					//顶点数，边数
	VertexType vexs[MAXV];		//存放顶点信息
}MatGraph;						//完整的图邻接矩阵类型

int read_line(char str[], int n);//此为为输入字符串而写的小函数 
void Dijkstra1(MatGraph g, int v, int v2);//dijkstra算法：一个顶点到其余各顶点的最短路径（此处为变式，输入任意两点，得到其最短距离） 
void Dispath(MatGraph g, int dist[], int path[], int S[], int v, int v2);//输出最短路径(应用到dijkstra算法中）
void Floyd(MatGraph g,FILE *fp);										//Floyd算法：每对顶点间的最短路径 
void Dispath(MatGraph g, int A[][MAXV], int path[][MAXV],FILE* fp);		//输出最短路径（应用到Floyed算法中） 

int main(void) {
	int choice;
	choice = 1;
	while (choice != 6)
	{
		printf("下面请选择您要进行的操作:\n");
		printf("********************************************\n");
		printf("1.输入直接相邻的两个旅游景点的名字以及它们之间的距离并将其存入文件；\n");
		printf("2.计算给定的两个旅游景点间的最短路径\n");
		printf("3.计算所有的景点对之间的最短路径，并写入文件\n");
		printf("4.从文件中读出所有旅游景点间的最短路径信息，到内存链表中管理\n");
		printf("5.快速查询\n");
		printf("6.退出程序\n");
		printf("********************************************\n");
		printf("enter your choice: ");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			FILE* fpWrite1 = fopen((char *)"景点基本信息.txt", "w");//建文件 
			if (fpWrite1 == NULL)//判定文件是否存在（以下case2,3,7中类似操作同理）
			{
				return 0;
			}
			int n, e;
			char name[MaxSize];
			printf("请输入景点数：");
			scanf("%d", &n);
			printf("请输入景点间的总边数：");
			scanf("%d", &e);
			MatGraph g;
			g.n = n;
			g.e = e;
			int i;
			int j, k, d;
			for (i = 0; i < MAXV; i++) {
				for (j = 0; j < MAXV; j++) {
					if (i == j) {
						g.edges[i][j] = 0;
					}
					else { g.edges[i][j] = INF; }
				}
			}
			for (i = 0; i < n ; i++) {
				printf("请输入序号为%d的景点名称:", i);
				read_line(name, MaxSize);
				g.vexs[i].no = i;
				strcpy(g.vexs[i].name, name);
			}
			for (i = 0; i < e; i++) {
				printf("请输入两相邻景点序号：");
				scanf("  %d  %d", &j, &k);
				printf("请输入此二景点间的距离：");
				scanf("%d", &d);
				g.edges[j][k] = d;
				fprintf(fpWrite1, "从景点%s到景点%s的距离为%d\n", g.vexs[j].name, g.vexs[k].name, d);
			}
			printf("已成功将数据存入磁盘中。");
			fclose((fpWrite1));
			break;
		case 2:
			int name1,name2;
			printf("请输入想查询的景点的序号：");
			scanf(" %d  %d", &name1,&name2);
			Dijkstra1(g, name1,name2);                                 
			break;
		case 3:    
		FILE* fpWrite2 = fopen((char *)"AllPath.dat", "w");//建文件 
			if (fpWrite2 == NULL)//判定文件是否存在（以下case2,3,7中类似操作同理）
			{
				return 0;
			}
			Floyd(g,fpWrite2);
			fclose((fpWrite2));//关闭文件，以下case2,3,4,5，6,7同理 
			break;                                   
		case 4: 
			FILE* fpRead1 = fopen((char *)"AllPath.dat", "r");//读文件 
            if (fpRead1 == NULL)//判定文件是否存在 
            {
                return 0;
            }
            Search information[e];
            int i4,j4;
            for(i4=0;i4<e;i4++){
            	char ch4;
	            fscanf(fpRead1,"%c",&ch4);
	            j4=0; 
	            information[i4].search[j4]=ch4;
	            while(ch4!='\0'){
            		fscanf(fpRead1,"%c",&ch4);
            		j4++;
            		information[i4].search[j4]=ch4;
            	}
            }
            printf("读取完毕");
            break;
		case 5: 
			char num1,num2; 
		    printf("请输入想要查询的景点序号：");
		    scanf(" %c %c",&num1,&num2);
		    int i5;
		    for(i5=0;i5<e;i5++){
		    	char s1,s2;
		    	s1=information[i5].search[1];
		    	s2=information[i5].search[3];
    			if(num1==s1&&num2==s2){
			    	printf("%s",information[i5].search);
			    }
    		}
      		break;
		case 6:                               break;
		default: printf("Error: you have entered a wrong number! ");
		}
		printf("\n");
	}







}

int read_line(char str[], int n)//此为为输入字符串而写的小函数 
{
	int ch, i = 0;

	while (isspace(ch = getchar()))
		;
	while (ch != '\n' && ch != EOF)
	{
		if (i < n)
			str[i++] = ch;
		ch = getchar();
	}
	str[i] = '\0';
	return i;
}

void Dijkstra1(MatGraph g, int v, int v2) {					//dijkstra算法：一个顶点到其余各顶点的最短路径
	int dist[MAXV], path[MAXV];
	int S[MAXV];											//S[i]=1表示顶点i在S中，S[i]=0表示顶点i在U中
	int MINdis, i, j, u;
	for (i = 0; i < g.n; i++) {
		dist[i] = g.edges[v][i];							//距离初始化
		S[i] = 0;											//S[]置空
		if (g.edges[v][i] < INF)							//路径初始化
			path[i] = v;									//顶点v到顶点i有边时，置顶点i的前一个顶点为v
		else
			path[i] = -1;									//顶点v到顶点i没边时，置顶点i的前一个顶点为-1
	}
	S[v] = 1; path[v] = 0;									//源点编号v放入S中
	for (i = 0; i < g.n - 1; i++) {							//循环知道所有顶点的最短路径都求出
		MINdis = INF;										//MINdis置最大长度初值
		for (j = 0; j < g.n; j++)							//选取不在S中（即U中）且具有最小最短路径长度的顶点u
			if (S[j] == 0 && dist[j] < MINdis) {
				u = j;
				MINdis = dist[j];
			}
		S[u] = 1;											//顶点u加入S中
		for (j = 0; j < g.n; j++)							//修改不在S中（即U中）的顶点的最短路径
			if (S[j] == 0)
				if (g.edges[u][j] < INF&&dist[u] + g.edges[u][j] < dist[j]) {
					dist[j] = dist[u] + g.edges[u][j];
					path[j] = u;
				}
	}
	Dispath(g, dist, path, S, v, v2);							//输出最短路径
}

void Dispath(MatGraph g, int dist[], int path[], int S[], int v, int v2) {
	int i, j, k;
	int apath[MAXV], d;										//存放一条最短路径（逆向）及其顶点个数
	for (i = 0; i < g.n; i++)										//循环输出从顶点v到i的路径
		if (S[i] == 1 && i != v &&i == v2) {
			printf("从顶点%d到顶点%d的路径长度为：%d\t路径为：", v, i, dist[i]);
			d = 0; apath[d] = i;								//添加路径上的终点
			k = path[i];
			if (k == -1)									//没有路径的情况
				printf("无路径\n");
			else											//存在路径时输出该路径
			{
				while (k != v) {
					d++; apath[d] = k;
					k = path[k];
				}
				d++; apath[d] = v;							//添加路径上的起点
				printf("%d", apath[d]);						//先输出起点
				for (j = d - 1; j >= 0; j--)				//再输出其他顶点
					printf(",%d", apath[j]);
				printf("\n");
			}
		}
}


void Floyd(MatGraph g,FILE *fp) {										//Floyd算法：每对顶点间的最短路径
	int A[MAXV][MAXV], path[MAXV][MAXV];
	int i, j, k;
	for(i=0;i<g.n;i++)
		for (j = 0; j < g.n; j++) {
			A[i][j] = g.edges[i][j];
			if (i != j && g.edges[i][j] < INF)
				path[i][j] = i;									//顶点i到j有边时
			else
				path[i][j] = -1;								//顶点i到j没有边时
		}
	for (k = 0; k < g.n; k++) {									//依次考查所有顶点
		for(i=0;i<g.n;i++)
			for (j = 0; j < g.n; j++) 
				if (A[i][j] > A[i][k] + A[k][j]) {
					A[i][j] = A[i][k] + A[k][j];				//修改最短路径长度
					path[i][j] = path[k][j];					//修改最短路径
				}
	}
	Dispath(g, A, path,fp);										//输出最短路径
}

void Dispath(MatGraph g, int A[][MAXV], int path[][MAXV],FILE* fp) {
	int i, j, k, s;
	int apath[MAXV], d;											//存放一条最短路径中间顶点（反向)及其顶点个数
	for(i=0;i<g.n;i++)
		for (j = 0; j < g.n; j++) {
			if (A[i][j] != INF && i != j) {						//若顶点i和j之间存在路径
				printf("从%d到%d的路径为：", i, j);
				fprintf(fp, "从%d到%d的最短路径为：", i,j);
				k = path[i][j];
				d = 0; apath[d] = j;							//路径上添加终点
				while (k != -1 && k != i) {						//路径上添加中间点
					d++; apath[d] = k;
					k = path[i][k];
				}
				d++; apath[d] = i;								//路径上添加起点
				printf("%d", apath[d]);
				fprintf(fp,"%d",apath[d]);						//输出起点
				for (s = d - 1; s >= 0; s--){					//输出路径上的中间顶点
					printf(",%d", apath[s]);
					fprintf(fp,",%d",apath[s]);
				}
				printf("\t路径长度为：%d\n", A[i][j]);
				fprintf(fp,"\t路径长度为：%d", A[i][j]);
				fprintf(fp, "%c\n", '\0');
			}
		}
}