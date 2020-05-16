#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

typedef struct student  //定义数据结点类型
{
    char sno[12]={'\0'};   //学号
    char sname[10]={'\0'};
    char sex[4]={'\0'};
    char major[20]={'\0'};
    struct student * next;      //指向后续数据节点
}StudentList;

typedef struct stable   //定义学生表
{
    int rows;   //学生表记录数
    int cols;   //学生信息列数
    StudentList * snode;    //学生信息结点
}Stable;

typedef struct course
{
    char cno[10]={'\0'};
    char cname[20]={'\0'};
    int classHours;
    struct  course * next;
}CourseList;

typedef struct ctable
{
    int rows;
    int cols;
    CourseList * cnode;
}Ctable;

typedef struct grade    //定义数据节点类型
{
    char sno[12]={'\0'};
    char cno[10]={'\0'};
    int score;
    struct grade * next;
}GradeList;

typedef struct gtable
{
    int rows;
    int cols;
    GradeList * gnode;
}Gtable;

typedef struct studentgrade
{
    char sno[12]={'\0'};
    char sname[10]={'\0'};
    char major[20]={'\0'};
    char cno[10]={'\0'};
    char cname[20]={'\0'};
    int score;
    struct studentgrade * next;
}StudentGradeList;

typedef struct sgtable
{
    int rows;
    int cols;
    StudentGradeList * sgnode;
}SGtable;

typedef struct
{
    StudentGradeList * front;   //头节点
    StudentGradeList * rear;    //尾结点
}LinkQuNode;

//保存学生数据
void insert_student(void);
void save_to_file_student(StudentList * new_student);
void info_flush_student(char * filename,StudentList * new_student);

//保存课程数据
void insert_course(void);
void save_to_file_course(CourseList * new_course);
void info_flush_course(char * filename,CourseList * new_course);

//保存学生考试成绩
void insert_grade(void);
void save_to_file_grade(GradeList * new_grade);
void info_flush_grade(char * filename,GradeList * new_grade);

//读出学生信息
void StudentList_init(StudentList  *& student);
void readfile_student(char * filename , StudentList * & student);
void print_student(StudentList  *& student);

//读出课程信息
void CourseList_init(CourseList *& course);
void readfile_course(char * filename , CourseList *& course);
void print_course(CourseList *& course);

//读出成绩信息
void GradeList_init(GradeList *& grade);
void readfile_grade(char * filename , GradeList *& grade);
void print_grade(GradeList *& grade);

//连接链表
void connect_lists(StudentGradeList *& sghead ,StudentList * shead , GradeList * ghead , CourseList * chead);
void bubblesort_StudentGrade(StudentGradeList *& sghead);
void info_flush_studentgrade(StudentGradeList * sghead);
void print_StudentGrade(StudentGradeList * sghead);

//查询指定课程号学生成绩信息
void select_from_StudentGradeList_cno(SGtable *& SG_one , StudentGradeList * sghead);
void print_StudentGradeList_one_course(StudentGradeList *sghead_one);

//查询不及格的学生成绩信息
void select_from_StudentGradeList_fail(SGtable *& SG_fail , StudentGradeList * sghead);

//逆序
void resort(StudentList *& shead);

//队列操作
void save_to_queue(LinkQuNode *& q , StudentList * shead , GradeList * ghead , CourseList * chead);
void InitQueue(LinkQuNode *& q);
void enQueue(LinkQuNode *& q , StudentList * shead , GradeList * ghead , CourseList * chead);
void printQueue(LinkQuNode * q);
void save_to_file_Queue(LinkQuNode * q);

int read_line(char str[], int n);
bool check_nullfile(char* filename);

int main()
{
    int choice;
    Stable s;
    Ctable c;
    Gtable g;
    SGtable sg;
    SGtable sg_cno;
    SGtable sg_fail;
    Stable * S;
    Ctable * C;
    Gtable * G;
    SGtable * SG;
    SGtable * SG_cno;
    SGtable * SG_fail;
    LinkQuNode * q;
    S = &s;
    C = &c;
    G = &g;
    SG= &sg;
    SG_cno=&sg_cno;
    SG_fail=&sg_fail;
    S->snode=NULL; S->cols=4; S->rows=10;
    C->cnode=NULL; C->cols=3; C->rows=3;
    G->gnode=NULL; G->cols=3; G->rows=30;
    SG->sgnode=NULL;SG->cols=6;SG->rows=10;
    SG_cno->sgnode=NULL;SG_cno->cols=6;
    SG_fail->sgnode=NULL;SG_fail->cols=6;
    for (;choice!=12;) {
        printf("学生课程成绩查询程序\n");
        printf("********************************************\n");
        printf("1. 输入学生信息\n");
        printf("2. 输入课程信息\n");
        printf("3. 输入成绩信息\n");
        printf("4. 读出学生信息\n");
        printf("5. 读出课程信息\n");
        printf("6. 读出成绩信息\n");
        printf("7. 整合信息\n");
        printf("8. 查询指定课程考生信息\n");
        printf("9. 查询不及格学生信息\n");
        printf("10. 逆序输出学生信息\n");
        printf("11. 用队列实现7的功能\n");
        printf("12. 退出系统\n");
        printf("********************************************\n");
        printf("enter your choice: ");
    scanf("%d", &choice);
    while (getchar() != '\n')   //吃掉空格以及回车字符，避免产生错误
      ;
    switch (choice)
    {
        case 1 : insert_student();                                              break;
        case 2 : insert_course();                                               break;
        case 3 : insert_grade();                                                break;
        case 4 : StudentList_init(S->snode);                                    break;
        case 5 : CourseList_init(C->cnode);                                     break;
        case 6 : GradeList_init(G->gnode);                                      break;
        case 7 : connect_lists(SG->sgnode , S->snode , G->gnode , C->cnode);    break;
        case 8 : select_from_StudentGradeList_cno(SG_cno,SG->sgnode);           break;
        case 9 : select_from_StudentGradeList_fail(SG_fail,SG->sgnode);         break;
        case 10: resort(S->snode);                                              break;
        case 11: save_to_queue(q , S->snode , G->gnode , C->cnode);             break;
        case 12:                                                                break;
        default: printf("Error ! Illegal number !\n");
    }
    printf("\n");
  }
    return 0;
}

void insert_student(void)
{
    StudentList * new_student;
    int i ;
    for(i=0;i<10;i++)
    {
        new_student = (StudentList *)malloc(sizeof(StudentList));
        printf("Please enter the information of the student: \n");
        printf("sno: ");
        read_line(new_student->sno,12);
        printf("sname: ");
        read_line(new_student->sname,10);
        printf("sex: ");
        read_line(new_student->sex,4);
        printf("major: ");
        read_line(new_student->major,20);
        save_to_file_student(new_student);
        free(new_student);
    }
}

void save_to_file_student(StudentList * new_student)
{
    char * filename = (char *)"student.dat";
    info_flush_student(filename,new_student);
    return;
}

void info_flush_student(char * filename,StudentList * new_student)
{
    FILE *fp;
    if ((fp = fopen("student.dat", "a")) == NULL)
    {
        printf("TIPS：can not open goods file database!\n");
        return;
    }
    fprintf(fp, "%s", new_student->sno);
    fprintf(fp, "   %s", new_student->sname);
    fprintf(fp, "   %s", new_student->major);
    fprintf(fp, "   %s", new_student->sex);
    fprintf(fp, "\n");
    fclose(fp);
    printf("Save successfully.\n");
}

void insert_course(void)
{
    CourseList * new_course;
    int i,j;
    for(i=0;i<3;i++)
    {
        new_course = (CourseList*)malloc(sizeof(CourseList));
        printf("Please enter the information of the course: \n");
        printf("cno: ");
        read_line(new_course->cno,10);
        printf("cname: ");
        read_line(new_course->cname,20);
        printf("classHours: ");
        scanf("%d",&new_course->classHours);
        new_course->next=NULL;
        save_to_file_course(new_course);
        free(new_course);
    }
}

void save_to_file_course(CourseList * new_course)
{
    char * filename = (char*)"course.dat";
    info_flush_course(filename,new_course);
    return;
}

void info_flush_course(char * filename, CourseList * new_course)
{
    FILE *fp;
    if ((fp = fopen("course.dat", "a")) == NULL)
    {
        printf("TIPS：can not open goods file database!\n");
        return;
    }
    fprintf(fp, "%s", new_course->cno);
    fprintf(fp, "   %s", new_course->cname);
    fprintf(fp, "   %d", new_course->classHours);
    fprintf(fp, "\n");
    fclose(fp);
    printf("Save successfully.\n");
}

void insert_grade(void)
{
    GradeList * new_grade;
    int i;
    for(i=0;i<30;i++)
    {
        new_grade=(GradeList*)malloc(sizeof(GradeList));
        printf("Please enter the grades of each student: ");
        printf("sno: ");
        read_line(new_grade->sno,12);
        printf("cno: ");
        read_line(new_grade->cno,10);
        printf("score: ");
        scanf("%d",new_grade->score);
        save_to_file_grade(new_grade);
        free(new_grade);
    }
}

void save_to_file_grade(GradeList * new_grade)
{
    char * filename = (char*)"courseGrade.dat";
    info_flush_grade(filename,new_grade);
    return;
}

void info_flush_grade(char * filename,GradeList * new_grade)
{
    FILE *fp;
    if ((fp = fopen("courseGrade.dat", "a")) == NULL)
    {
        printf("TIPS：can not open goods file database!\n");
        return;
    }
    fprintf(fp, "%s", new_grade->sno);
    fprintf(fp, "   %s", new_grade->cno);
    fprintf(fp, "   %d", new_grade->score);
    fprintf(fp, "\n");
    fclose(fp);
    printf("Save successfully.\n");
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

void StudentList_init(StudentList  *& student)
{
    char * filename = (char*)"student.dat";
    readfile_student(filename,student);
    print_student(student);
    return;
}

void readfile_student(char * filename , StudentList * & student)
{
    FILE *fp;
    StudentList  *cur, *prev, *new_student;
    student=NULL;
    bool res = check_nullfile(filename);
    if(!res)
    {
        printf("无法正常打开学生信息文件，请确认您已经输入学生信息\n");
        return;
    }
    if ((fp = fopen(filename, "r")) == NULL)        //打开文件用于读
    {
        if ((fp = fopen(filename, "w")) == NULL)
            printf("TIPS：CAN NOT CREAT STUDENTS DATABASE FILE \n");        //如果不能读不能写
    }
    else {
        while (res && !feof(fp))
        {
        	new_student = (StudentList *)malloc(sizeof(StudentList));
            if (new_student == NULL) {
            printf("Database is full; can't add more students.\n");
            return;
            }
            fscanf(fp, "%s", new_student->sno);
            fscanf(fp, "   %s", new_student->sname);
            fscanf(fp, "   %s", new_student->major);
            fscanf(fp, "   %s\n", new_student->sex);
             for (cur = student, prev = NULL;
                 cur != NULL && strcmp(new_student->sno,cur->sno)>0;
                 prev = cur, cur = cur->next)
             ;
            new_student->next = cur;
            if (prev == NULL)
               student = new_student;
            else
               prev->next = new_student;
         }
    }
    fclose(fp);
}

void print_student(StudentList  *& student)
{
    StudentList * p;
    printf("********************************************\n");
    printf(" Sno        Sname      Sex       major   \n");
    for (p = student; p != NULL; p = p->next)
        printf(" %s     %s       %s       %s\n", p->sno, p->sname,p->sex,p->major);
    printf("********************************************\n");
    return;
}

void CourseList_init(CourseList *& course)
{
    char * filename = (char*)"course.dat";
    readfile_course(filename,course);
    print_course(course);
    return;
}

void readfile_course(char * filename , CourseList * & course)
{
    FILE *fp;
    CourseList  *cur, *prev, *new_course;
    bool res = check_nullfile(filename);
    course=NULL;
    if(!res)
    {
        printf("无法正常打开课程信息文件，请确认您已经输入课程信息\n");
        return;
    }
    if ((fp = fopen(filename, "r")) == NULL)        //打开文件用于读
    {
        if ((fp = fopen(filename, "w")) == NULL)
            printf("TIPS：CAN NOT CREAT COURSE DATABASE FILE \n");        //如果不能读不能写
    }
    else
    {
        while (res && !feof(fp))
        {
        	new_course = (CourseList *)malloc(sizeof(CourseList));
            if (new_course == NULL)
            {
                printf("Database is full; can't add more courses.\n");
                return;
            }
            fscanf(fp, "%s %s %d\n", new_course->cno,new_course->cname,&new_course->classHours);
            for (cur = course, prev = NULL;
                 cur != NULL && strcmp(new_course->cno,cur->cno)>0;
                 prev = cur, cur = cur->next)
            ;

            new_course->next = cur;
            if (prev == NULL)
               course = new_course;
            else
               prev->next = new_course;
         }
    }
    fclose(fp);
}

void print_course(CourseList *& course)
{
    CourseList * p;
    printf("********************************************\n");
    printf("    Cno     Cname       ClassHour   \n");
    for (p = course; p != NULL; p = p->next)
        printf("    %s     %-8s       %d\n", p->cno, p->cname,p->classHours);
    printf("********************************************\n");
    return;
}

void GradeList_init(GradeList *& grade)
{
    char * filename = (char*)"courseGrade.dat";
    readfile_grade(filename,grade);
    print_grade(grade);
    return;
}

void readfile_grade(char * filename,GradeList * & grade)
{
    FILE *fp;
    GradeList  *cur, *prev, *new_grade;
    bool res = check_nullfile(filename);
    grade=NULL;
    if(!res)
    {
        printf("无法正常打开成绩信息文件，请确认您已经输入成绩信息\n");
        return;
    }
    if ((fp = fopen(filename, "r")) == NULL)        //打开文件用于读
    {
        if ((fp = fopen(filename, "w")) == NULL)
            printf("TIPS：CAN NOT CREAT GRADE DATABASE FILE \n");        //如果不能读不能写
    }
    else {

        while (res && !feof(fp))
        {
        	new_grade = (GradeList *)malloc(sizeof(GradeList));
            if (new_grade == NULL) {
            printf("Database is full; can't add more courses.\n");
            return;
            }
            fscanf(fp, "%s %s %d\n", &new_grade->sno,&new_grade->cno,&new_grade->score);

            for (cur = grade, prev = NULL;
                 cur != NULL && strcmp(new_grade->sno,cur->sno)>=0;
                 prev = cur, cur = cur->next)
            ;
            new_grade->next = cur;
            if (prev == NULL)
               grade = new_grade;
            else
               prev->next = new_grade;
         }
    }
    fclose(fp);
}

void print_grade(GradeList  *& grade)
{
    GradeList * p;
    printf("********************************************\n");
    printf(" Sno     cno    Score   \n");
    for (p = grade; p != NULL; p = p->next)
        printf(" %s	 %s 	%2d\n", p->sno, p->cno,p->score);
    printf("********************************************\n");
    return;
}

bool check_nullfile(char* filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
        return false;
    else
            return true;
}

void connect_lists(StudentGradeList *& sghead ,StudentList * shead , GradeList * ghead , CourseList * chead)
{
    StudentGradeList * sg_new , *sg_cur, *prev;
    StudentList * s_cur;
    CourseList * c_cur;
    GradeList * g_cur;
    if(shead==NULL || ghead==NULL || chead==NULL)
    {
        printf("请先将基本信息、课程信息和成绩信息从文件中读出再进行此步骤。\n");
        return;
    }
    for(g_cur=ghead , sg_cur=sghead ; g_cur!=NULL ; g_cur=g_cur->next)
    {
        sg_new=(StudentGradeList*)malloc(sizeof(StudentGradeList));
        strcpy(sg_new->sno,g_cur->sno);
        strcpy(sg_new->cno,g_cur->cno);
        sg_new->score=g_cur->score;
        for (sg_cur = sghead, prev = NULL;
                 sg_cur != NULL ;
                 prev = sg_cur, sg_cur = sg_cur->next)
        ;
        sg_new->next = sg_cur;
        if (prev == NULL)
            sghead = sg_new;
        else
            prev->next = sg_new;
    }
    for(sg_cur=sghead ; sg_cur!=NULL ; sg_cur=sg_cur->next)
    {
        for(c_cur=chead ; strcmp(c_cur->cno,sg_cur->cno)!=0 && c_cur!=NULL ; c_cur=c_cur->next)
        ;
        strcpy(sg_cur->cname,c_cur->cname);
    }
    for(sg_cur=sghead ; sg_cur!=NULL ; sg_cur=sg_cur->next)
    {
        for(s_cur=shead ; strcmp(s_cur->sno,sg_cur->sno)!=0 && s_cur!=NULL ; s_cur=s_cur->next)
        ;
        strcpy(sg_cur->sname,s_cur->sname);
        strcpy(sg_cur->major,s_cur->major);
    }
    bubblesort_StudentGrade(sghead);
    info_flush_studentgrade(sghead);
    print_StudentGrade(sghead);
}

void bubblesort_StudentGrade(StudentGradeList *& sghead)
{
    char sno_tmp[12];
    char sname_tmp[10];
    char major_tmp[20];
    char cno_tmp[10];
    char cname_tmp[20];
    int score_tmp;
    StudentGradeList *p , *q;
    for(p=sghead ; p!=NULL ; p=p->next)
        for(q=p->next ; q!=NULL ; q=q->next)
            if(p->score < q->score)
            {
                strcpy(cname_tmp,q->cname) , strcpy(q->cname,p->cname) , strcpy(p->cname,cname_tmp);
                strcpy(cno_tmp,q->cno) , strcpy(q->cno,p->cno) , strcpy(p->cno , cno_tmp);
                strcpy(major_tmp,q->major) , strcpy(q->major,p->major) , strcpy(p->major,major_tmp);
                score_tmp=q->score , q->score=p->score , p->score=score_tmp;
                strcpy(sname_tmp,q->sname) , strcpy(q->sname,p->sname) , strcpy(p->sname,sname_tmp);
                strcpy(sno_tmp,q->sno) , strcpy(q->sno,p->sno) , strcpy(p->sno,sno_tmp);
            }
}

void print_StudentGrade(StudentGradeList * sghead)
{
    StudentGradeList * p;
    printf("*******************************************************************************\n");
    printf("    Sno        Sname       Major         Cno       Cname          Score\n");
    for (p = sghead;p != NULL;p = p->next)
        printf("    %s     %s       %s       %s       %-8s       %4d\n", p->sno, p->sname,p->major,p->cno,p->cname,p->score);
    printf("*******************************************************************************\n");
    return;
}

void info_flush_studentgrade(StudentGradeList * sghead)
{
    StudentGradeList *cur, *prev;
    FILE *fp;
    if ((fp = fopen("studentGrade.dat", "a")) == NULL)
    {
        printf("TIPS：can not open goods file database!\n");
        return;
    }
    for (cur = sghead, prev = NULL;
                 cur != NULL;
                 prev = cur, cur = cur->next)
    {
        fprintf(fp, "%s", cur->sno);
        fprintf(fp, "      %s", cur->sname);
        fprintf(fp, "      %s", cur->major);
        fprintf(fp, "      %s", cur->cno);
        fprintf(fp, "      %s", cur->cname);
        fprintf(fp, "      %d\n", cur->score);
    }
    fclose(fp);
}

void select_from_StudentGradeList_cno(SGtable *& SG_one , StudentGradeList * sghead)
{

    StudentGradeList * new_node;
    StudentGradeList * cur , * prev;
    StudentGradeList * cur_search;
    StudentGradeList * sghead_one;
    sghead_one=SG_one->sgnode;
    int i=0;
    char cno[10];
    if(sghead==NULL)
    {
        printf("请先完成学生信息的整合。\n");
        return;
    }
    printf("Please enter the number of the course you want to search: ");
    read_line(cno,10);
    for(cur_search=sghead;cur_search!=NULL;cur_search=cur_search->next)
        if(strcmp(cno,cur_search->cno)==0)
        {
            new_node=(StudentGradeList*)malloc(sizeof(StudentGradeList));
            strcpy(new_node->cname,cur_search->cname);
            strcpy(new_node->cno,cur_search->cno);
            strcpy(new_node->major,cur_search->major);
            strcpy(new_node->sname,cur_search->sname);
            strcpy(new_node->sno,cur_search->sno);
            new_node->score=cur_search->score;
            for (cur = sghead_one, prev = NULL;
                 cur != NULL ;
                 prev = cur, cur = cur->next)
            ;
            new_node->next = cur;
            if (prev == NULL)
                sghead_one = new_node;
            else
                prev->next = new_node;
            i++;
        }
    SG_one->rows=i;
    print_StudentGrade(sghead_one);
}

void select_from_StudentGradeList_fail(SGtable *& SG_one , StudentGradeList * sghead)
{
    StudentGradeList * new_node;
    StudentGradeList * cur , * prev;
    StudentGradeList * cur_search;
    StudentGradeList * sghead_one;
    sghead_one=SG_one->sgnode;
    int i=0;
    for(cur_search=sghead,cur=sghead_one;cur_search!=NULL;cur_search=cur_search->next)
        if(cur_search->score<60)
        {
            new_node=(StudentGradeList*)malloc(sizeof(StudentGradeList));
            strcpy(new_node->cname,cur_search->cname);
            strcpy(new_node->cno,cur_search->cno);
            strcpy(new_node->major,cur_search->major);
            strcpy(new_node->sname,cur_search->sname);
            strcpy(new_node->sno,cur_search->sno);
            new_node->score=cur_search->score;
            for (cur = sghead_one, prev = NULL;
                 cur != NULL ;
                 prev = cur, cur = cur->next)
            ;
            new_node->next = cur;
            if (prev == NULL)
                sghead_one = new_node;
            else
                prev->next = new_node;
            i++;
        }
    SG_one->rows=i;
    if(i==0)
    {
        printf("There is no student fails in the exam.\n");
        return;
    }
    print_StudentGrade(sghead_one);
}

void resort(StudentList *& shead)
{
    StudentList save[10];
    StudentList *cur , *prev , *new_node;
    int i,j;
    for(i=0,cur=shead;cur!=NULL;cur=cur->next)
    {
        strcpy(save[i].major,cur->major);
        strcpy(save[i].sex,cur->sex);
        strcpy(save[i].sname,cur->sname);
        strcpy(save[i].sno,cur->sno);
        save[i].next=NULL;
        i++;
    }
    shead=NULL;
    for(i=9;i>=0;i--)
    {
        new_node=&save[i];
        for(cur = shead, prev = NULL;
            cur != NULL ;
            prev = cur, cur = cur->next)
            ;
            new_node->next = cur;
            if (prev == NULL)
                shead = new_node;
            else
                prev->next = new_node;
    }
    print_student(shead);
}

void save_to_queue(LinkQuNode *& q , StudentList * shead , GradeList * ghead , CourseList * chead)
{
    InitQueue(q);
    enQueue(q ,shead ,ghead ,chead);
    printQueue(q);
    save_to_file_Queue(q);
}

void InitQueue(LinkQuNode *& q)
{
    q=(LinkQuNode*)malloc(sizeof(LinkQuNode));
    q->front=q->rear=NULL;
}

void enQueue(LinkQuNode *& q , StudentList * shead , GradeList * ghead , CourseList * chead)
{
    StudentGradeList * sg_new , * sg_cur ;
    StudentList * s_cur;
    CourseList * c_cur;
    GradeList * g_cur;
    if(shead==NULL || ghead==NULL || chead==NULL)
    {
        printf("请先将基本信息、课程信息和成绩信息从文件中读出再进行此步骤。\n");
        return;
    }
    for(g_cur=ghead; g_cur!=NULL ; g_cur=g_cur->next)
    {
        sg_new=(StudentGradeList*)malloc(sizeof(StudentGradeList));
        strcpy(sg_new->sno,g_cur->sno);
        strcpy(sg_new->cno,g_cur->cno);
        sg_new->score=g_cur->score;
        sg_new->next=NULL;
        if(q->rear==NULL)
            q->front=q->rear=sg_new;
        else
        {
            q->rear->next=sg_new;
            q->rear=sg_new;
        }
        sg_new=NULL;
        free(sg_new);
    }
    for(q->rear=q->front ; q->rear!=NULL ; q->rear=q->rear->next)
    {
        for(s_cur=shead ; strcmp(s_cur->sno,q->rear->sno)!=0 && s_cur!=NULL ; s_cur=s_cur->next)
        ;
        strcpy(q->rear->sname,s_cur->sname);
        strcpy(q->rear->major,s_cur->sname);
    }
    for(q->rear=q->front ; q->rear!=NULL ; q->rear=q->rear->next)
    {
        for(c_cur=chead ; strcmp(c_cur->cno,q->rear->cno)!=0 && c_cur!=NULL ; c_cur=c_cur->next)
        ;
        strcpy(q->rear->cname,c_cur->cname);
    }
}

void printQueue(LinkQuNode * q)
{
    q->rear=q->front;
    printf("*******************************************************************************\n");
    printf("     Sno       Sname      Major      Cno       Cname          Score\n");
    for (;q->rear != NULL;q->rear = q->rear->next)
        printf("    %s     %s       %s       %s       %-8s       %2d\n", q->rear->sno, q->rear->sname,q->rear->major,q->rear->cno,q->rear->cname,q->rear->score);
    printf("*******************************************************************************\n");
}

void save_to_file_Queue(LinkQuNode * q)
{
    FILE *fp;
    if ((fp = fopen("studentGrade.dat", "a")) == NULL)
    {
        printf("TIPS：can not open goods file database!\n");
        return;
    }
    for(q->rear=q->front;q->rear!=NULL;q->rear=q->rear->next)
    {
        fprintf(fp, "%s", q->rear->sno);
        fprintf(fp, "      %s", q->rear->sname);
        fprintf(fp, "      %s", q->rear->major);
        fprintf(fp, "      %s", q->rear->cno);
        fprintf(fp, "      %s", q->rear->cname);
        fprintf(fp, "      %d\n", q->rear->score);
    }
    fclose(fp);
}
