#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include <ctype.h>

#define N 10



typedef struct student {
	char sno[12];
	char sname[10];
	char sex[4];
	char major[20];
	struct student *next;
}StudentList;

StudentList *student;

typedef struct stable //定义学生表
{ int rows; //学生表记录数
int cols; //学生信息列数
StudentList *snode; //学生信息结点
} Stable;

typedef struct course //定义数据结点类型
{ char cno[10];
char cname[20];
int classHours ;
struct course *next; //指向后继数据结点
} CourseList;

typedef struct ctable //定义课程表
{ int rows; //课程表记录数
int cols; //课程信息列数
CourseList *cnode; //课程信息结点
} Ctable;

typedef struct grade //定义数据结点类型
{ char sno[12];
char cno[10];
int score ;
struct grade *next; //指向后继数据结点
} GradeList;

typedef struct gtable //定义成绩表
{ int rows; //成绩表记录数
int cols; //成绩信息列数
GradeList *gnode; //成绩信息结点
} Gtable;

void studentslist_init(void);
void readfile(char * filename);
void save_to_file_exit1(void);
void info_flush(char * filename);
void Destroystudents(struct student* student);
bool check_nullfile(char* filename);

void insert(void);
void print(void);
void bubblesort(void);

int read_line(char str[], int n);

int main(void)
{ 
  int choice; 
  int i;
  scanf("%d", &choice);
  switch(choice){
  	case 1:  studentslist_init();
             for(i=0;i<2;i++){
  	             insert(); 
             }
			 save_to_file_exit1();
             break;
    case 4:  studentslist_init();
             bubblesort();
             print();
             break;
  }
}

void studentslist_init(void)
{
    readfile("student.dat");   
}

void readfile(char * filename)
{
    FILE *fp;
    struct student *cur, *prev, *new_node;
    bool res = check_nullfile(filename);
    if ((fp = fopen(filename, "rb")) == NULL)
    {
        if ((fp = fopen(filename, "wb")) == NULL)
            printf("TIPS：CAN NOT CREAT GOODS DATABASE FILE \n");
    }
    else {

        while (res && !feof(fp))
        {       	
        	new_node = malloc(sizeof(struct student));
            if (new_node == NULL) {
            printf("Database is full; can't add more goods.\n");
            return;
            }       	
            fprintf(fp, "%s", cur->sno);
            fprintf(fp, "      %s", cur->sname);
            fprintf(fp, "      %s", cur->sex);
            fprintf(fp, "      %d\n", cur->major);
            new_node->next = cur;
            if (prev == NULL)
               student = new_node;
            else
               prev->next = new_node;  
         }  
    }
    
    fclose(fp);
}


void save_to_file_exit1(void)
{
 info_flush("student.dat");
 Destroystudents(student);    
 exit(EXIT_SUCCESS);
}

void info_flush(char * filename){
    struct student *cur, *prev;
    FILE *fp;
    if ((fp = fopen("student.dat", "wb")) == NULL)
    {
        printf("TIPS：can not open file database!\n");
        return;
    }
    for (cur = student, prev = NULL;
                 cur != NULL;
                 prev = cur, cur = cur->next)            
    {

        fprintf(fp, "%s", cur->sno);
        fprintf(fp, "      %s", cur->sname);
        fprintf(fp, "      %s", cur->sex);
        fprintf(fp, "      %d\n", cur->major);
    }
    fclose(fp);
    Destroystudents(student);
}

void Destroystudents(struct student* student) {
    if (!student) return; 
    struct student *cur,*prev;
    for (cur = student, prev = NULL;
                 cur != NULL;
                 prev = cur, cur = cur->next,free(cur))  
                 ;
}

bool check_nullfile(char* filename)
{
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        printf("TIPS: FILE NOT EXIST, CREAT ONE FOR YOU.\n");
        FILE *fp = fopen(filename, "wb");
        fclose(fp);

        return false; 
    }
    else {
        int temp;
        int res = fscanf(fp, "%d", &temp);
        fclose(fp);
        if (res <= 0)
            return false;
        else
            return true;
    }
}

  void insert(void)
{
       struct student *cur, *prev, *new_node;

  new_node = malloc(sizeof(struct student));
  if (new_node == NULL) {
    printf("Database is full; can't add more parts.\n");
    return;
  }
  
  printf("Enter student number: ");  
  read_line(new_node->sno,12);
  printf("Enter student name: ");
  read_line(new_node->sname,10);
  printf("Enter student sex: ");
  read_line(new_node->sex,4);
  printf("Enter student major: ");
  read_line(new_node->major,20);

  new_node->next = cur;
  if (prev == NULL)
    student = new_node;
  else
    prev->next = new_node;
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

void print(void)
{
  struct student *p;
  printf("Student Number   Student Name                   Student sex   Student major   \n");
  for (p = student; p != NULL; p = p->next)
    printf("%12s       %-10s   %4s      %20s      \n", p->sno, p->sname,p->sex,p->major);
}
    

 void bubblesort(void)
{
   	struct student *cur, *prev,*change ;
   	change=student;
   	prev=student;
   	cur=student;
      while(change!=NULL)
      {
      	change=change->next;
      }
      while(prev->next!=change){
      	cur=student;
     while(cur->next!=change){     
        if(strcmp(cur->sno,cur->next->sno))
        {
        char ch1[12];
        char ch2[10];
        char ch3[4];
        char ch4[20];
        strcpy(ch1,cur->sno);
        strcpy(cur->sno,cur->next->sno);
        strcpy(cur->next->sno,ch1);
        strcpy(ch2,cur->sname);
        strcpy(cur->sname,cur->next->sname);
        strcpy(cur->next->sname,ch2);
        strcpy(ch3,cur->sex);
        strcpy(cur->sex,cur->next->sex);
        strcpy(cur->next->sex,ch3);
        strcpy(ch4,cur->major);
        strcpy(cur->major,cur->next->major);
        strcpy(cur->next->major,ch4);
        }
		cur=cur->next;			
        }
     	change=cur;        	
      }
   }
