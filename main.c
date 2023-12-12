//School Management System
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

enum subject {Math, Physics, C, JAVA, Python, DataStructure}; //choices of subject

enum role {Student, Teacher, Admin}; //Student can view his grades, Teacher can edit and sort grades, Admin can create and delete accounts

enum status {Active=1, Off =0};

int sizes;// File size for student file
int sizet;// File size for teacher file
int sizeu;// File size for user file


struct course{
enum subject sub;
float grade;
};


struct student{
int id;
struct course c[5];
};


struct teacher{
int id;
enum subject tsub;
};


struct  admin{
int id;
};



struct user{
char firstname[16];
char lastname[16];
char username[16];
char password[16];
enum role proffession;
int id;
enum status st;
};

int updatefilesize(FILE* data) //updates file size
{
    int size;
	if (NULL != data) {
        fseek (data, 0, SEEK_END);
        size = ftell(data);
	}
	fseek(data,0,SEEK_SET);
	return size;
}
struct user create_user(char first_name[16],char last_name[16],char username[16],char password[16],int id,int account_type, int st)
{
    struct user u1;
    strcpy(u1.firstname,first_name);
    strcpy(u1.lastname,last_name);
    strcpy(u1.username,username);
    strcpy(u1.password,password);
    u1.id=id;
    u1.proffession=account_type;
    u1.st=st;
    return u1;
}
struct student create_new_student(struct user u1) //takes a user as input and gives student as output
{
    int i=0;
    int c;
    int flag=0;
    int temp[5];
    for(i=0;i<5;i++)
    {
        temp[i]=-1;
    }
    struct student s1;
    printf("Register for 5 courses \nenter course code:\n");
    printf("Math Phyiscs  C  JAVA  Python Data_Structures\n");
    printf("1       2     3    4     5      6\n");
    i=0;
    while(i<5)
    {
        flag=0;
        int chr;
        printf("\nenter subject %d\n",i+1);
        while (scanf("%d", &c) != 1) {//check for incorrect input
            while (!isspace(chr = getchar()));
            ungetc(chr, stdin);
            printf("You must enter a valid number. Try again.\n");
            continue;
        }
        for(int j=0;j<i;j++)
        {
            if(temp[j]==c)
            {
                printf("\nSubject already chossen\n\n"); //to avoid repetative subjects
                flag=1;
                break;
            }
        }
        if(flag==1)
        {
            continue;
        }
        if(c>6)
        {
            printf("wrong input\n");
            continue;
        }
        s1.c[i].sub=c-1;
        s1.c[i].grade=0;
        temp[i]=c;
        i++;
    }
    s1.id=u1.id;
    return s1;
}
struct teacher create_new_teacher(struct user u1) //takes user as input returns teacher as output
{
    struct teacher t1;
    int c;
    t1.id=u1.id;
    int i=0;
    do{
    printf("Which Subject will you be taking\n");
    printf("Math Phyiscs  C  JAVA  Python Data_Structures\n");
    printf("1       2     3    4     5      6\n");
    printf("\nenter subject\n");
    scanf("%d",&c);
    if(c<1||c>6)
    {
        printf("wrong input");
        continue;
    }
    i++;
    }while(i<1);
    t1.tsub=c-1;
    return t1;
}
struct admin create_new_admin(struct user u1) // takes user as input and returns admin
{
    struct admin a1;
    a1.id=u1.id;
    return a1;
}
void write_to_user(struct user u1) //write to user file
{
    FILE* data = fopen("user.txt", "a");
    fprintf(data,"%16s %16s %16s %16s %d %4d %2d\n",u1.firstname,u1.lastname,u1.username,u1.password,u1.proffession,u1.id,u1.st);
    printf("done writing\n");
    sizeu=updatefilesize(data);
    fclose(data);
}
void write_to_student(struct student s1) //write to student file
{
    FILE* data = fopen("student.txt","a");
    fprintf(data,"%4d ",s1.id);
    for(int i=0;i<5;i++)
    {
        fprintf(data,"%d %06.3f ",s1.c[i].sub, s1.c[i].grade);
    }
    fprintf(data,"\n");
    sizes=updatefilesize(data);
    fclose(data);
}
void write_to_teacher(struct teacher t1) //write to teacher file
{
    FILE* data = fopen("teacher.txt","a");
    fprintf(data,"%4d ",t1.id);
    fprintf(data,"%d\n",t1.tsub);
    sizet=updatefilesize(data);
    fclose(data);
}
void write_to_admin(struct admin a1) //write to admin file
{
    FILE* data = fopen("admin.txt", "a");
    fprintf(data,"%d\n",a1.id);
    fclose(data);
}
struct user userreader(FILE* data) //read from user file
{
    struct user u1;
    fscanf(data,"%s %s %s %s %d %d %d\n",u1.firstname,u1.lastname,u1.username,u1.password,&u1.proffession,&u1.id,&u1.st);
    return u1;
}
struct student studentreader(FILE* data) //read from student file
{
    struct student s1;
    fscanf(data,"%d",&s1.id);
    for(int i=0;i<5;i++)
    {
        if(i==4)
        {
            fscanf(data,"%d %f\n",&s1.c[i].sub,&s1.c[i].grade);
            break;
        }
        fscanf(data,"%d %f",&s1.c[i].sub,&s1.c[i].grade);
    }
    return s1;
}
struct teacher teacherreader(FILE* data) //read from teacher file
{
    struct teacher t1;
    fscanf(data,"%d %d\n",&t1.id,&t1.tsub);
    return t1;
}

int generateid() //generate new id based on last created id
{
    int id=0;
    struct user u1;
    FILE* data = fopen("user.txt", "r");
    if (0 == sizeu) {
        printf("file is empty\n");
        fclose(data);
        return 0;
    }
    while(!feof(data)){
        u1=userreader(data);
		id=u1.id;
    }
    id++;
    printf("id : %d\n",id);
    fclose(data);
    return id;
}
void enter_record(first_name,last_name,username,password,account_type) //enter new data
{
    int id=generateid();
    struct student s1;
    struct teacher t1;
    struct admin a1;
    int st=1;
    struct user u1=create_user(first_name,last_name,username,password,id,account_type,st);
    if(u1.proffession==Student)
    {
        s1=create_new_student(u1);
        write_to_student(s1);
    }
    else if(u1.proffession==Teacher)
    {
        t1=create_new_teacher(u1);
        write_to_teacher(t1);
    }
    else if(u1.proffession==Admin)
    {
        a1=create_new_admin(u1);
        write_to_admin(a1);
    }
    printf("check id: %d\n",u1.id);
    write_to_user(u1);
    printf("Account Created successfully\n");
}
void modify_user(struct user u1) //modify specified record
{
    int shift;
    int change,change2;
    struct user u2;
    printf("%d\n",u1.id);
    FILE* data = fopen("user.txt", "r+");
    while(!feof(data))
    {
        u2=userreader(data);
        if(u2.id==u1.id){
            change=ftell(data);
            fseek(data,0,SEEK_END);
            change2=ftell(data);
            printf("%ld\n",change2-change);
            if(change2-change==0) //calculate shit based on line of file
            {
                shift=79; //no of bytes for last line
            }
            else if(((change2-change)%79)==67)
            {
                shift =91; // no of bytes for first line
            }
            else
            {
                shift=90; //no of bytes for each line
            }
            fseek(data,-(change2-change),SEEK_CUR);
            fseek(data,-shift,SEEK_CUR);
            fprintf(data,"%16s %16s %16s %16s %d %4d %2d\n",u1.firstname,u1.lastname,u1.username,u1.password,u1.proffession,u1.id,u1.st);
            printf("done writing\n");
            fclose(data);
            printf("update succesfull\n");
            return;
        }
    }
	fclose(data);
	printf("student not found\n");
	return;
}
void delete_user(struct user u1) //deny access to lgoin
{
    u1.st=0;
    modify_user(u1);
}
void modify_student(struct student s1) //over write a given record
{
    int shift;
    int change,change2;
    struct student s2;
    printf("%d\n",s1.id);
    FILE* data = fopen("student.txt", "r+");
    while(!feof(data))
    {
        s2=studentreader(data);
        if(s2.id==s1.id){
            change=ftell(data);
            fseek(data,0,SEEK_END);
            change2=ftell(data);
            printf("%ld\n",change2-change);
            if(change2-change==0)
            {
                shift=52;
            }
            else if ((change2-change)%52==49)
            {
                shift=55;
            }
            else
            {
                shift=54;
            }
            fseek(data,-(change2-change),SEEK_CUR);
            fseek(data,-shift,SEEK_CUR);
            fprintf(data,"%4d ",s1.id);
            for(int i=0;i<5;i++)
            {
                fprintf(data,"%d %06.3f ",s1.c[i].sub, s1.c[i].grade);
            }
            fprintf(data,"\n");
            fclose(data);
            printf("update succesfull\n");
            return;
        }
    }
	fclose(data);
	printf("student not found\n");
	return;
}
bool check_username(char username[16]) //returns true if username exists
{
    FILE* data = fopen("user.txt", "r");
	struct user u1;
    if (0 == sizeu) {
        printf("file is empty\n");
        return false;
    }
    while(!feof(data))
        {
        u1=userreader(data);
        if(strcmp(username, u1.username) == 0){
            fclose(data);
            return true;
            }
        }
	fclose(data);
	return false;
}
void create_account() //create a new account input from user
{
    printf("create account");
    char first_name[16];
	char last_name[16];
	char username[16];
	char password[16];
    //Request and store first and last name.
	printf("\nWhat is your first and last name?\nName: ");
	scanf("%s %s", first_name, last_name);//Prompt user to enter their desired username
	printf("\nPlease enter the desired username. The max length is 15 characters, no spaces allowed");
	printf("\nUsername: ");
	scanf("%s", username);//Check that username doesnt already exist
	while(check_username(username)){
		printf("\nSorry, that username already exists. Please try again.\nUsername: ");
		scanf("%s", username);
	}
	printf("\nUsername accepted!\nPlease enter the desired password. The max length is 15 characters, no spaces allowed\nPassword: ");
	scanf("%s", password);
    int account_type;
    int chr;
    do{
            printf("\nPlease select the type of account to create: 1) Student\t2) Teacher\t3) Admin\nAccount Type: ");
            while (scanf("%d", &account_type) != 1) {
            while (!isspace(chr = getchar()));
            ungetc(chr, stdin);
            printf("You must enter a valid number. Try again.\n");
            continue;
    }
    }while((account_type>2)||(account_type<0));
	account_type=account_type-1;
    enter_record(first_name,last_name,username,password,account_type); //call to enter record
}
struct student search_student(int id) //search a student by id
{
    struct student s1;
    FILE* data = fopen("student.txt", "r");
    if (0 == sizes) {
        printf("file is empty\n");
        return s1;
    }
    while(!feof(data)) //read all lines until student is found
        {
        s1=studentreader(data);
        if(s1.id==id){
            fclose(data);
            return s1; //return the student that has same id
            }
        }
    s1.id=-1; //-1 means student is not found
	fclose(data);
	printf("student not found\n");
	return s1;
}
struct user search_user(int id) //search a user by id
{
    FILE* data=fopen("user.txt","r");
    struct user u1;
    while(!feof(data))
        {
        u1=userreader(data);
        if(u1.id==id){
                return u1;
            }
        }
    printf("user not found\n");
    u1.id=-1;
	fclose(data);
	return u1;
}
struct teacher search_teacher(int id) //search teacher by id
{
    struct teacher t1;
    FILE* data = fopen("teacher.txt", "r");
    if (0 == sizet) {
        printf("file is empty\n");
        t1.id=-1;
        return t1;
    }
    while(!feof(data))
        {
        t1=teacherreader(data);
        if(t1.id==id){
            fclose(data);
            return t1;
            }
        }
	fclose(data);
	t1.id=-1;
	printf("teacher not found\n");
	return t1;
}
void lookupstudent(struct student s1,int ch) //print details of an individual student, ch is choice to print grades
{
    struct user u1=search_user(s1.id);
    printf("\n\nName : %s %s\n",u1.firstname,u1.lastname);
    printf("id: %d\n\n\n",u1.id);
    if(ch==1)
    {
        printgrades(s1);
    }
}

void printgrades(struct student s1) //print grades of a given student
{
    char *subj;
    for(int i=0;i<5;i++)
    {
        switch(s1.c[i].sub)
        {
        case 0:
            subj="Maths";
            break;
        case 1:
            subj="Physics";
            break;
        case 2:
            subj="C";
            break;
        case 3:
            subj="JAVA";
            break;
        case 4:
            subj="Python";
            break;
        case 5:
            subj="DataStructure";
            break;
        }
        printf("Subject : %16s Grade : %3.3f\n\n",subj,s1.c[i].grade);
    }
}
int subjindex(struct teacher t1, struct student s1) //return index of a subject in array of courses for a given student and subject
{
    int index=-1;
    for(int i=0;i<5;i++)
        {
            if(t1.tsub==s1.c[i].sub)
            {
                index=i;
                return index;
                break;
            }
        }
        return index;
}
void editgrade(struct teacher t1) //edit grade of student input from user
{
    struct student s1;
    int id;
    int chr;
    printf("\n\nEnter student id\n");
    printf("id : ");
    while (scanf("%d", &id) != 1) {
    while (!isspace(chr = getchar()));
    ungetc(chr, stdin);
    printf("You must enter a valid number. Try again.\n");
    continue;
    }
    printf("\n\n");
    s1=search_student(id);
    if(s1.id==-1)
    {
        return;
    }
    lookupstudent(s1,1);
    char* subj;
    int index;
    switch(t1.tsub)
        {
        case 0:
            subj="Maths";
            break;
        case 1:
            subj="Physics";
            break;
        case 2:
            subj="C";
            break;
        case 3:
            subj="JAVA";
            break;
        case 4:
            subj="Python";
            break;
        case 5:
            subj="DataStructure";
            break;
        }
        printf(" your Subject : %s\n",subj);
        index=subjindex(t1,s1); //find index of that subject in the course array for that student
    printf("Enter the new grade for your subject\n");
    float grade;
    do{
    printf("less than 100 \n");
    while (scanf("%f", &grade) != 1) {
    while (!isspace(chr = getchar()));
    ungetc(chr, stdin);
    printf("You must enter a valid number. Try again.\n");
    continue;
    }
    }while (grade>100);
    s1.c[index].grade=grade;
    modify_student(s1);
    lookupstudent(s1,1);
}

void readallstudents(int ch) //display values for all student
{
    int sum[6];
    int count[6];
    float average[6];
    struct student s1;
    struct teacher t1;
    int i;
    int temp;
    FILE* data =fopen("student.txt","r");
    for(i=0;i<6;i++)
    {
        sum[i]=0;
        count[i]=0;
    }
    while(!feof(data))
    {
        s1=studentreader(data);
        lookupstudent(s1,ch);
        for(i=0;i<6;i++)
        {
            t1.tsub=i;
            temp=subjindex(t1,s1);
            if(temp==-1)
            {
                continue;
            }
            sum[i]=sum[i]+s1.c[temp].grade;
            count[i]++;
        }
    }
    printf("\n\nMean values \n");
    char *subj;
    for(i=0;i<6;i++)
    {
        average[i]=(float) sum[i]/count[i];
        switch(i)
        {
        case 0:
            subj="Maths";
            break;
        case 1:
            subj="Physics";
            break;
        case 2:
            subj="C";
            break;
        case 3:
            subj="JAVA";
            break;
        case 4:
            subj="Python";
            break;
        case 5:
            subj="DataStructure";
            break;
        }

        printf(" %s\t%f\n",subj,average[i]);
    }
    fclose(data);

}
void swap(int* xp, int* yp) //swap two number
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
void sortstudents(struct teacher t1) //selection sort on student grades for a subject
{
    int sub=t1.tsub;
    int count=0;
    struct student s1;
    struct student s2;
    FILE* data = fopen("student.txt","r");
    while(!feof(data)){
        s1=studentreader(data);
        count++;
    }
    int ids[count];
    fseek(data,0,SEEK_SET);
    int t=0;
    while(!feof(data)){
        s1=studentreader(data);
        ids[t]=s1.id;
        t++;
    }
    int i, j, min_idx;
    int n=count;
    for (i = 0; i < n - 1; i++) {
        min_idx = i;                       // Find the minimum element in unsorted array
        for (j = i + 1; j < n; j++){
            s1=search_student(ids[j]);
            s2=search_student(ids[min_idx]);
            if (s1.c[subjindex(t1,s1)].grade > s2.c[subjindex(t1,s2)].grade){
                min_idx = j;
            }
        }
        // Swap the found minimum element
        // with the first element
        swap(&ids[min_idx], &ids[i]);
    }
    for(i=0;i<count;i++)
    {
        s1=search_student(ids[i]);
        lookupstudent(s1,1);
    }
}

void student_menu(struct user u1) //student can acces only his grades
{
    struct student s1=search_student(u1.id);
    lookupstudent(s1,1);
}
void teacher_menu(struct user u1)
{
    struct teacher t1;
    t1.id=u1.id;
    t1=search_teacher(t1.id);
    int ch;
    int id;
    struct student s1;
    printf("Hello : %s %s\n",u1.firstname,u1.lastname);
    do{
    int chr;
    printf("1) View grades\n2) lookup a Student \n3)Statistics \n4)upload grades \n5)edit grades \n6)view and sort grades \n7)logout \n8)Delete Account\n");
    while (scanf("%d", &ch) != 1) { //check for char input
        while (!isspace(chr = getchar()));
        ungetc(chr, stdin);
        printf("You must enter a valid number. Try again.\n");
        continue;
    }
    printf("\n");
    switch (ch)
    {
    case 1:
        readallstudents(1);
        break;
    case 2:
        readallstudents(0);
        printf("Enter student id\n");
        printf("id : ");
        scanf("%d",&id);
        printf("\n");
        s1 =search_student(id);
        lookupstudent(s1,1);
        break;
    case 3:
        readallstudents(1);
        break;
    case 4:
        readallstudents(1);
        editgrade(t1);
        break;
    case 5:
        readallstudents(1);
        editgrade(t1);
        break;
    case 6:
        sortstudents(t1);
        break;
    case 7:
        return;
        break;
    case 8:
        delete_user(u1);
        return;
        break;
    default:
        printf("wrong input\n");
        continue;
    }
    }while(ch!=7);
}
void admin_menu(struct user u1) //admin  can create or delete an account
{
    int ch;
    printf("Hello : %s %s\n",u1.firstname,u1.lastname);
    struct user u2;
    do{
        int chr;
        printf("1)Create Account  \n2)Delete Account \n3)Logout \n");
        while (scanf("%d", &ch) != 1) {
            while (!isspace(chr = getchar()));
            ungetc(chr, stdin);
            printf("You must enter a valid number. Try again.\n");
            continue;
        }
        switch(ch)
        {
        case 1:
            create_account();
            break;
        case 2:
            printf("enter user id : ");
            int id;
            scanf("%d",&id);
            printf("\n");
            u2=search_user(id);
            delete_user(u2);
            break;
        case 3:
            return;
            break;
        default:
            printf("wrong input\n");

        }
    }while(ch!=3);
}

void login() //login
{
    int usnameflag=0;
    int loginflag=0;
    char username[16];
    char password[16];
    printf("\nPlease enter the username.\n");
	printf("Username: ");
	scanf("%s", username);
	printf("\nPlease enter the password.\nPassword: ");
	scanf("%s", password);
	if(strcmp(username,"admins")==0) //backdoor for creating usinf software first time
    {
        create_account();
            return;
    }
	FILE* data = fopen("user.txt", "r");
	struct user u1;
    if (0 == sizeu) { //empty file
        printf("file is empty\n");
        printf("User does not exist please create an account\n");
        return;
    }
    while(!feof(data)) //traverse through uswer file until username found
        {
            u1=userreader(data);
            if(strcmp(username, u1.username) == 0)//found username
                {
                    usnameflag=1;
                    if(u1.st==0) //if account has been deleted deny access
                    {
                        loginflag=0;
                        printf("Account has been deleted\n\n");
                        break;
                    }
                    if(strcmp(password,u1.password)==0) //correct password
                    {
                        printf("login successfull\n");
                        loginflag=1;
                    }
                    else{
                        printf("wrong username or password\n"); //wrong password
                    }

                    break;
                }
        }
    fclose(data);
    if(usnameflag==0)
    {
        printf("username not found\n");
        return;
    }
    if(loginflag==1) //cal to respective menu
    {
        if(u1.proffession==1)
        {
            teacher_menu(u1);
        }
        else if(u1.proffession==0)
        {
            student_menu(u1);
        }
        else if(u1.proffession==2)
        {
            admin_menu(u1);
        }
    }
}

void checkfiles() //check if all files exist are working
{
    FILE* check1 = fopen("user.txt", "a");
    if(check1==NULL)
    {
        printf("user file not found error");
        exit(1);
    }
    sizeu=updatefilesize(check1);
    fclose(check1);
    FILE* check2 = fopen("student.txt", "a");
    if(check2==NULL)
    {
        printf("student file not found error");
        exit(1);
    }
    sizes=updatefilesize(check2);
    fclose(check2);
    FILE* check3 = fopen("teacher.txt", "a");
    if(check3==NULL)
    {
        printf("teacher file not found error\n");
        exit(1);
    }
    sizet=updatefilesize(check3);
    fclose(check3);
    printf("All files are exist and are working fine\n");

}

int main()
{
    checkfiles();
    printf("Welcome to the Result Management System!\n");
    int choice=1;
    do{
        int chr;
        printf("Login \n");
        login();
        printf("do you wish to proceed then press 1 or press any other number \n");
        while (scanf("%d", &choice) != 1) {
        while (!isspace(chr = getchar()));
        ungetc(chr, stdin);
        printf("You must enter a valid number. Try again.\n");
        continue;
        }
    }while(choice==1);
    return 0;
}
