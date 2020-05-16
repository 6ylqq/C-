#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#define INF 32767				//�����
#define	MAXV 100
typedef char InfoType;
typedef struct
{	int no;						            //������
	InfoType info[MAXV]={'\0'};				//����������Ϣ
} VertexType;					            //��������
typedef struct
{	int edges[MAXV][MAXV];		//�ڽӾ�������
	int n,e;					//������������
	VertexType vexs[MAXV];		//��Ŷ�����Ϣ
} MatGraph;						//������ͼ�ڽӾ�������
int read_line(char str[], int n);
void InitGarden(MatGraph &g);
void Dispath1(MatGraph g,int A[][MAXV],int path[][MAXV]);
void save_garden_to_file(MatGraph g);
void Dispath(MatGraph g,int dist[],int path[],int S[],int v,int a);
void Dijkstra(MatGraph g,int v,int i);
void find_way(MatGraph g);
int main ()
{
    int n;
    MatGraph g;
    InitGarden(g);

    save_garden_to_file(g);
    find_way(g);
    return 0;
}

void InitGarden(MatGraph &g)
{
    int i,j;
    printf("�����빫԰�ľ��������");
    scanf("%d",&g.n);
    for(i=0;i<g.n;i++)
    {
        printf("�������%d�����������: ",i+1);
        read_line(g.vexs[i].info,MAXV);
        g.vexs[i].no=i;
    }
    for(j=0;j<g.n;j++)     //��
        for(i=0;i<g.n;i++) //��
        {
            printf("������%s��%s������ľ���: ",g.vexs[i].info,g.vexs[j].info);
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

void Dispath1(MatGraph g,int A[][MAXV],int path[][MAXV])
{
    int i,j,k,s;
	int apath[MAXV],d;		//���һ�����·���м䶥��(����)���䶥�����
	for (i=0;i<g.n;i++)
		for (j=0;j<g.n;j++)
		{	if (A[i][j]!=INF && i!=j)			//������i��j֮�����·��
			{	printf("  ��%s��%s��·��Ϊ:",g.vexs[i].info,g.vexs[j].info);
				k=path[i][j];
				d=0; apath[d]=j;				//·��������յ�
				while (k!=-1 && k!=i)			//·��������м��
				{	d++; apath[d]=k;
					k=path[i][k];
				}
				d++; apath[d]=i;				//·����������
				printf("%s",g.vexs[apath[d]].info);			//������
				for (s=d-1;s>=0;s--)			//���·���ϵ��м䶥��
					printf(",%s",g.vexs[apath[s]].info);
				printf("\t·������Ϊ:%d\n",A[i][j]);
			}
		}
}

void Floyd(MatGraph g)							//Floyd�㷨
{
    int A[MAXV][MAXV],path[MAXV][MAXV];
	int i,j,k;
	for (i=0;i<g.n;i++)
		for (j=0;j<g.n;j++)
		{	A[i][j]=g.edges[i][j];
			if (i!=j && g.edges[i][j]<INF)
				path[i][j]=i;					//����i��j�б�ʱ
			else
				path[i][j]=-1;				//����i��jû�б�ʱ
		}
	for (k=0;k<g.n;k++)						//���ο������ж���
	{	for (i=0;i<g.n;i++)
			for (j=0;j<g.n;j++)
				if (A[i][j]>A[i][k]+A[k][j])
				{	A[i][j]=A[i][k]+A[k][j];	//�޸����·������
					path[i][j]=path[k][j];		//�޸����·��
				}
	}
	Dispath1(g,A,path);							//������·��
}

void save_garden_to_file(MatGraph g)
{
	int i,j;
	FILE* fp;
	fp = fopen("garden.dat", "w");
	/*if ((fp = fopen("garden.dat", "w")) == NULL)
	{
		printf("TIPS��can not open goods file database!\n");
		return;
	}*/
	for(i=0;j<g.n;i++)
        for(j=0;j<g.n;j++)
        {
            if((fprintf(fp, "%s��%s֮��ľ���Ϊ: ", g.vexs[i].info,g.vexs[j].info))==0)
            {
                printf("erro!\n");
                return;
            }
            else{
            if(g.edges[i][j]!=INF)
                fprintf(fp, "%d\n", g.edges[i][j]);
            else
                fprintf(fp, "����������֮��û��ֱ��·��\n");
       } }
	fclose(fp);
	printf("Save successfully.\n");
}

void Dispath(MatGraph g,int dist[],int path[],int S[],int v,int i)//����Ӷ���v�������������·��
{
    int j,k;
	int apath[MAXV],d;					//���һ�����·��(����)���䶥�����
	//for (i=0;i<g.n;i++)					//ѭ������Ӷ���v��i��·��
		if (S[i]==1 && i!=v)
		{	printf("  �Ӷ���%d������%d��·������Ϊ:%d\t·��Ϊ:",v,i,dist[i]);
			d=0; apath[d]=i;			//���·���ϵ��յ�
			k=path[i];
			if (k==-1)					//û��·�������
				printf("��·��\n");
			else						//����·��ʱ�����·��
			{	while (k!=v)
				{	d++; apath[d]=k;
					k=path[k];
				}
				d++; apath[d]=v;		//���·���ϵ����
				printf("%d",apath[d]);	//��������
				for (j=d-1;j>=0;j--)	//�������������
					printf(",%d",apath[j]);
				printf("\n");
			}
		}
}

void Dijkstra(MatGraph g,int v,int a)	//Dijkstra�㷨
{
    int dist[MAXV],path[MAXV];
	int S[MAXV];				//S[i]=1��ʾ����i��S��, S[i]=0��ʾ����i��U��
	int Mindis,i,j,u;
	for (i=0;i<g.n;i++)
	{	dist[i]=g.edges[v][i];	//�����ʼ��
		S[i]=0;					//S[]�ÿ�
		if (g.edges[v][i]<INF)	//·����ʼ��
			path[i]=v;			//����v������i�б�ʱ���ö���i��ǰһ������Ϊv
		else
			path[i]=-1;			//����v������iû��ʱ���ö���i��ǰһ������Ϊ-1
	}
	S[v]=1;path[v]=0;			//Դ����v����S��
	for (i=0;i<g.n-1;i++)		//ѭ��ֱ�����ж�������·�������
	{	Mindis=INF;				//Mindis����󳤶ȳ�ֵ
		for (j=0;j<g.n;j++)		//ѡȡ����S�У���U�У��Ҿ�����С���·�����ȵĶ���u
			if (S[j]==0 && dist[j]<Mindis)
			{	u=j;
				Mindis=dist[j];
			}
		S[u]=1;					//����u����S��
		for (j=0;j<g.n;j++)		//�޸Ĳ���S�У���U�У��Ķ�������·��
			if (S[j]==0)
				if (g.edges[u][j]<INF && dist[u]+g.edges[u][j]<dist[j])
				{	dist[j]=dist[u]+g.edges[u][j];
					path[j]=u;
				}
	}
	Dispath(g,dist,path,S,v,a);	//������·��
}

void find_way(MatGraph g)
{
    int i,v,a;
    char n[MAXV]={'\0'},m[MAXV]={'\0'};
    printf("�����������յ㣺\n");
    printf("��㣺");
    read_line(n,MAXV);
    printf("�յ㣺");
    read_line(m,MAXV);
    for(v=0;v<g.n;v++)
    {
        if(strcpy(g.vexs[v].info,n)==0)
            break;
    }
    if(v==g.n)
    {
        printf("��㲻����\n");
        return;
    }
    for(a=0;a<g.n;a++)
    {
        if(strcpy(g.vexs[a].info,m)==0)
            break;
    }
    if(v==g.n)
    {
        printf("�յ㲻����\n");
        return;
    }
    Dijkstra(g,v,a);
}
