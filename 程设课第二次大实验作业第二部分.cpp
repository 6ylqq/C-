#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<iostream>

#define MaxSize 100
#define MAXV 10
#define INF 32767				//�����

typedef char ElemType;
typedef int InfoType;
typedef struct{
	char search[MaxSize];
}Search;

typedef struct {
	int no;						//����ı��
	char name[MaxSize];				//�����������Ϣ
}VertexType;					//���������

typedef struct {
	int edges[MAXV][MAXV];		//�ڽӾ�������
	int n, e;					//������������
	VertexType vexs[MAXV];		//��Ŷ�����Ϣ
}MatGraph;						//������ͼ�ڽӾ�������

int read_line(char str[], int n);//��ΪΪ�����ַ�����д��С���� 
void Dijkstra1(MatGraph g, int v, int v2);//dijkstra�㷨��һ�����㵽�������������·�����˴�Ϊ��ʽ�������������㣬�õ�����̾��룩 
void Dispath(MatGraph g, int dist[], int path[], int S[], int v, int v2);//������·��(Ӧ�õ�dijkstra�㷨�У�
void Floyd(MatGraph g,FILE *fp);										//Floyd�㷨��ÿ�Զ��������·�� 
void Dispath(MatGraph g, int A[][MAXV], int path[][MAXV],FILE* fp);		//������·����Ӧ�õ�Floyed�㷨�У� 

int main(void) {
	int choice;
	choice = 1;
	while (choice != 6)
	{
		printf("������ѡ����Ҫ���еĲ���:\n");
		printf("********************************************\n");
		printf("1.����ֱ�����ڵ��������ξ���������Լ�����֮��ľ��벢��������ļ���\n");
		printf("2.����������������ξ��������·��\n");
		printf("3.�������еľ����֮������·������д���ļ�\n");
		printf("4.���ļ��ж����������ξ��������·����Ϣ�����ڴ������й���\n");
		printf("5.���ٲ�ѯ\n");
		printf("6.�˳�����\n");
		printf("********************************************\n");
		printf("enter your choice: ");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			FILE* fpWrite1 = fopen((char *)"���������Ϣ.txt", "w");//���ļ� 
			if (fpWrite1 == NULL)//�ж��ļ��Ƿ���ڣ�����case2,3,7�����Ʋ���ͬ��
			{
				return 0;
			}
			int n, e;
			char name[MaxSize];
			printf("�����뾰������");
			scanf("%d", &n);
			printf("�����뾰�����ܱ�����");
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
				printf("���������Ϊ%d�ľ�������:", i);
				read_line(name, MaxSize);
				g.vexs[i].no = i;
				strcpy(g.vexs[i].name, name);
			}
			for (i = 0; i < e; i++) {
				printf("�����������ھ�����ţ�");
				scanf("  %d  %d", &j, &k);
				printf("������˶������ľ��룺");
				scanf("%d", &d);
				g.edges[j][k] = d;
				fprintf(fpWrite1, "�Ӿ���%s������%s�ľ���Ϊ%d\n", g.vexs[j].name, g.vexs[k].name, d);
			}
			printf("�ѳɹ������ݴ�������С�");
			fclose((fpWrite1));
			break;
		case 2:
			int name1,name2;
			printf("���������ѯ�ľ������ţ�");
			scanf(" %d  %d", &name1,&name2);
			Dijkstra1(g, name1,name2);                                 
			break;
		case 3:    
		FILE* fpWrite2 = fopen((char *)"AllPath.dat", "w");//���ļ� 
			if (fpWrite2 == NULL)//�ж��ļ��Ƿ���ڣ�����case2,3,7�����Ʋ���ͬ��
			{
				return 0;
			}
			Floyd(g,fpWrite2);
			fclose((fpWrite2));//�ر��ļ�������case2,3,4,5��6,7ͬ�� 
			break;                                   
		case 4: 
			FILE* fpRead1 = fopen((char *)"AllPath.dat", "r");//���ļ� 
            if (fpRead1 == NULL)//�ж��ļ��Ƿ���� 
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
            printf("��ȡ���");
            break;
		case 5: 
			char num1,num2; 
		    printf("��������Ҫ��ѯ�ľ�����ţ�");
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

int read_line(char str[], int n)//��ΪΪ�����ַ�����д��С���� 
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

void Dijkstra1(MatGraph g, int v, int v2) {					//dijkstra�㷨��һ�����㵽�������������·��
	int dist[MAXV], path[MAXV];
	int S[MAXV];											//S[i]=1��ʾ����i��S�У�S[i]=0��ʾ����i��U��
	int MINdis, i, j, u;
	for (i = 0; i < g.n; i++) {
		dist[i] = g.edges[v][i];							//�����ʼ��
		S[i] = 0;											//S[]�ÿ�
		if (g.edges[v][i] < INF)							//·����ʼ��
			path[i] = v;									//����v������i�б�ʱ���ö���i��ǰһ������Ϊv
		else
			path[i] = -1;									//����v������iû��ʱ���ö���i��ǰһ������Ϊ-1
	}
	S[v] = 1; path[v] = 0;									//Դ����v����S��
	for (i = 0; i < g.n - 1; i++) {							//ѭ��֪�����ж�������·�������
		MINdis = INF;										//MINdis����󳤶ȳ�ֵ
		for (j = 0; j < g.n; j++)							//ѡȡ����S�У���U�У��Ҿ�����С���·�����ȵĶ���u
			if (S[j] == 0 && dist[j] < MINdis) {
				u = j;
				MINdis = dist[j];
			}
		S[u] = 1;											//����u����S��
		for (j = 0; j < g.n; j++)							//�޸Ĳ���S�У���U�У��Ķ�������·��
			if (S[j] == 0)
				if (g.edges[u][j] < INF&&dist[u] + g.edges[u][j] < dist[j]) {
					dist[j] = dist[u] + g.edges[u][j];
					path[j] = u;
				}
	}
	Dispath(g, dist, path, S, v, v2);							//������·��
}

void Dispath(MatGraph g, int dist[], int path[], int S[], int v, int v2) {
	int i, j, k;
	int apath[MAXV], d;										//���һ�����·�������򣩼��䶥�����
	for (i = 0; i < g.n; i++)										//ѭ������Ӷ���v��i��·��
		if (S[i] == 1 && i != v &&i == v2) {
			printf("�Ӷ���%d������%d��·������Ϊ��%d\t·��Ϊ��", v, i, dist[i]);
			d = 0; apath[d] = i;								//���·���ϵ��յ�
			k = path[i];
			if (k == -1)									//û��·�������
				printf("��·��\n");
			else											//����·��ʱ�����·��
			{
				while (k != v) {
					d++; apath[d] = k;
					k = path[k];
				}
				d++; apath[d] = v;							//���·���ϵ����
				printf("%d", apath[d]);						//��������
				for (j = d - 1; j >= 0; j--)				//�������������
					printf(",%d", apath[j]);
				printf("\n");
			}
		}
}


void Floyd(MatGraph g,FILE *fp) {										//Floyd�㷨��ÿ�Զ��������·��
	int A[MAXV][MAXV], path[MAXV][MAXV];
	int i, j, k;
	for(i=0;i<g.n;i++)
		for (j = 0; j < g.n; j++) {
			A[i][j] = g.edges[i][j];
			if (i != j && g.edges[i][j] < INF)
				path[i][j] = i;									//����i��j�б�ʱ
			else
				path[i][j] = -1;								//����i��jû�б�ʱ
		}
	for (k = 0; k < g.n; k++) {									//���ο������ж���
		for(i=0;i<g.n;i++)
			for (j = 0; j < g.n; j++) 
				if (A[i][j] > A[i][k] + A[k][j]) {
					A[i][j] = A[i][k] + A[k][j];				//�޸����·������
					path[i][j] = path[k][j];					//�޸����·��
				}
	}
	Dispath(g, A, path,fp);										//������·��
}

void Dispath(MatGraph g, int A[][MAXV], int path[][MAXV],FILE* fp) {
	int i, j, k, s;
	int apath[MAXV], d;											//���һ�����·���м䶥�㣨����)���䶥�����
	for(i=0;i<g.n;i++)
		for (j = 0; j < g.n; j++) {
			if (A[i][j] != INF && i != j) {						//������i��j֮�����·��
				printf("��%d��%d��·��Ϊ��", i, j);
				fprintf(fp, "��%d��%d�����·��Ϊ��", i,j);
				k = path[i][j];
				d = 0; apath[d] = j;							//·��������յ�
				while (k != -1 && k != i) {						//·��������м��
					d++; apath[d] = k;
					k = path[i][k];
				}
				d++; apath[d] = i;								//·����������
				printf("%d", apath[d]);
				fprintf(fp,"%d",apath[d]);						//������
				for (s = d - 1; s >= 0; s--){					//���·���ϵ��м䶥��
					printf(",%d", apath[s]);
					fprintf(fp,",%d",apath[s]);
				}
				printf("\t·������Ϊ��%d\n", A[i][j]);
				fprintf(fp,"\t·������Ϊ��%d", A[i][j]);
				fprintf(fp, "%c\n", '\0');
			}
		}
}