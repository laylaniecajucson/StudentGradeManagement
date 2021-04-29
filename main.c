/*   Written by: Cajucson, Laylanie C.
                  BSCS 1B- M

     Date: April 23, 2021   */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Struct declaration
typedef struct Student{  //Student Information in struct
    int rno;
    char name[30];
        struct subject{ // Struct for subject
        char subjectName[20];
        int grade;
            }sub[3];
    int total;
    float average;

    }Student;

//FUNCTION DECLARATIONS

void addStudent(){ //SUBPROGRAM FOR ADDING STUDENTS IN THE LIST
//Variable declaration
    char askAdd;
    Student *s;     // pointer
    FILE *fp;       //Binary file
    int num, i,j;

    cls(); // clears the screen
    do{
     cls();
     // Printing the screen layout
    printf("\n\n\t\t\t\t***************************************************************");
    printf("\n\t\t\t\t\t\tA D D  S T U D E N T / S");
    printf("\n\t\t\t\t***************************************************************");
    printf("\n\t\t\t\tHow many students you want to record? \t");
    scanf("%d", &num);

    //allocates the requested memory and returns a pointer to it
    s = (Student*)calloc(num, sizeof(Student));

    // opens the file in append format
    fp= fopen("records.txt", "a");

    if(fp == NULL)
        {fp = fopen("Services.txt", "w"); }   // opens the file in write format

        //for loop
        for (i=0; i<num; i++){
        s[i].total = 0;     //set sum of grades in three subjects to zero
        s[i].average = 0;   //set average to zero

        printf("\n\t\t\t\tEnter ID number : \t");
        scanf("%d", &s[i]);
        fflush(stdin);      //flush the output buffer of the stream

        printf("\n\t\t\t\tEnter name :\t ");
        scanf("%[^\n]s",s[i].name);

        if  (isdigit(&s[i].name))
        {
            printf("error");
        }
        else{
            printf("\n\n\t\t\t\t***************************************************************");
            printf("\n\t\t\t\tSubject1 = Filipino\tSubject2= Science\tSubject3=English");
            printf("\n\t\t\t\t***************************************************************");

        //for loop
        for(j=0;j<3;j++){
            printf("\n\t\t\t\tEnter grade in Subject%d : \t", j+1);
            scanf("%d", &s[i].sub[j].grade);
            s[i].total+= s[i].sub[j].grade;
            }

            s[i].average=s[i].total/3.0; // loop for computing the average

            fwrite (&s[i], sizeof(Student),1,fp); //writes bytes
            }}

            do{
                printf("\n\n\n\t\t\t\tAdd another stududent/s? (Y/N)? : \t");
                scanf(" %c", &askAdd);
                cls();
                askAdd=toupper(askAdd);           //capitalize inputs
                if(askAdd!='Y'&&askAdd!='N')
                    printf("\n\n\n\t\t\t\t***************************************************************");
                    printf("\n\t\t\t\t\t\tI n v a l i d   r e s p o n s e!");
                    printf("\n\t\t\t\t***************************************************************");



        }while(askAdd!='Y'&&askAdd!='N');     //loop if input is invalid
        }while(askAdd=='Y');


    fclose(fp);  // closed file


    }

void openRecords(){ ////SUBPROGRAM TO DISPLAY THE LIST
    //Variable declaration
    Student s1;     //struct
    FILE *fp;
    int j;
    cls();          //clears the screen
  fp=fopen("records.txt", "r");     // opens the file in read format

    //Printing screen layout
    printf("\n\t\t\t\t***************************************************************");
    printf("\n\t\t\t\t\tL I S T   O F   S T U D E N T ' S   R E C O R D S");
    printf("\n\t\t\t\t***************************************************************");
    printf("\n\t\t\t\tID NO.\tNAME\t\tFILIPINO   SCIENCE   ENGLISH\t AVERAGE");
    printf("\n\t\t\t\t================================================================");


    //while loop
    while (fread(&s1, sizeof(Student),1,fp))//reads data from the given stream
    {
    printf("\n\t\t\t\t%-5d\t%-20s",s1.rno,s1.name ); //print data

        for (j=0; j<3; j++){
        printf("%4d\t", s1.sub[j].grade);}      //grades
        printf("%7.2f",s1.average);            //average
    }

    printf("\n\n\n\t\t\t\t\t\t      Press any key to go back to Mainmenu.......");
    getch(); // hold the output screen until the user presses on the keyboard

    fclose(fp);  //closes file

}
void editRecords(){

    //variable Declaration
    Student s1;
    FILE *fp,*fp1;      //binary files
    int j, rno, found=0;
    char askEdit;

    do{
    fp=fopen("records.txt","r");        // opens the file in read format
    fp1=fopen("newrecords.txt","w");    // opens the file in write format


    cls();

    //Printing the screen layout
    printf("\n\n\n\t\t\t\t***************************************************************");
    printf("\n\t\t\t\t  E D I T   L I S T   O F   S T U D E N T ' S   R E C O R D S");
    printf("\n\t\t\t\t***************************************************************");

    printf("\n\n\n\t\t\t\tEnter ID number to edit:  ");
    scanf("%d", &rno);

    while(fread(&s1, sizeof (Student),1,fp))
    {
    if (s1.rno==rno){   // condition if the ID number given by the user is the same for the ID number recorder in struct
    s1.total =0;        //set sum of grades in three subjects to zero
    s1.average=0;       //set average to zero
    found=1;
    fflush(stdin);
    printf("\n\n\n\t\t\t\tEnter NEW name : ");  //allowing the user to input new name
    scanf("%[^\n]s",s1.name);
     for(j=0;j<3;j++)       //loop getting grades
        {
        printf("\n\n\n\t\t\t\tEnter NEW grade in Subject%d : ", j+1);   //allowing the user to input new grade in subjects
        scanf("%d", &s1.sub[j].grade);
        s1.total+= s1.sub[j].grade;
        }
        s1.average=s1.total/3.0;    //computing average
    }
        fwrite(&s1,sizeof (Student),1,fp1);     //write the upadated version in fp
    }
    fclose(fp); //closes files
    fclose(fp1);
    if (found){
        fp1= fopen("newrecords.txt","r");
        fp = fopen("records.txt","w");

        while(fread(&s1,sizeof(Student),1,fp1)){
            fwrite(&s1,sizeof(Student),1,fp);}

        fclose(fp);
        fclose(fp1);
        cls();
        printf("\n\n\n\t\t\t\t***************************************************************");
       printf("\n\t\t\t\t\t\tRecord successfully updated!");
       printf("\n\t\t\t\t***************************************************************");
       getch();
    }
    else //(s1.rno!=rno);
        cls();
    cls();
       printf("\n\n\n\t\t\t\t***************************************************************");
       printf("\n\t\t\t\t\t\tCheck your ID number....");
       printf("\n\t\t\t\t***************************************************************");
       //getch();


        do{
            printf("\n\n\n\t\t\t\tEdit stududent's record? (Y/N)? : \t");
            scanf(" %c", &askEdit);
            cls();
            askEdit=toupper(askEdit);           //capitalize inputs
            if(askEdit!='Y'&&askEdit!='N')
                printf("\n\n\n\t\t\t\t***************************************************************");
                printf("\n\t\t\t\t\t\tI n v a l i d   r e s p o n s e!");
                printf("\n\t\t\t\t***************************************************************");




        }while(askEdit!='Y'&&askEdit!='N');     //loop if input is invalid
        }while(askEdit=='Y');





         }





/*//do{

  //fp=fopen("records.txt", "r");

    cls();
    printf("\n\t\t\t\t***************************************************************");
    printf("\n\t\t\t\t  E D I T   L I S T   O F   S T U D E N T ' S   R E C O R D S");
    printf("\n\t\t\t\t***************************************************************");
    printf("\n\t\t\t\tID NO.\tNAME\t\tFILIPINO   SCIENCE   ENGLISH\t AVERAGE");
    printf("\n\t\t\t\t================================================================");


    while (fread(&s1, sizeof(Student),1,fp))
    {
    printf("\n\t\t\t\t%-5d\t%-20s",s1.rno,s1.name );
        for (j=0; j<3; j++){
        printf("%4d\t", s1.sub[j].grade);}
        printf("%7.2f",s1.average);
        }
    fclose(fp);

    fp=fopen("records.txt","r");
    fp1=fopen("newrecords.txt","w");
    printf("\n\n\t\t\t\t================================================================");
    printf("\n\t\t\t\tEnter ID number to edit:  ");
    scanf("%d", &rno);
    while(fread(&s1, sizeof (Student),1,fp))
    {
    if (s1.rno==rno){
    s1.total =0;
    s1.average=0;
    found=1;
    fflush(stdin);
    printf("\n\t\t\t\tEnter NEW name : ");
    scanf("%[^\n]s",s1.name);
    printf("\n\t\t\t\t================================================================");
    printf("\n\t\t\t\tSubject1 = Filipino\tSubject2= Science\tSubject3=English");
    printf("\n\t\t\t\t================================================================");

    for(j=0;j<3;j++){


        printf("\n\t\t\t\tEnter NEW grade in Subject%d : ", j+1);
        scanf("%d", &s1.sub[j].grade);
        s1.total+= s1.sub[j].grade;
    }
    s1.average=s1.total/3.0;

    fwrite(&s1,sizeof (Student),1,fp1);
}   fclose(fp);
    fclose(fp1);
    if (found){
        fp1= fopen("newrecords.txt","r");
        fp = fopen("records.txt","w");

        while(fread(&s1,sizeof(Student),1,fp1)){
            fwrite(&s1,sizeof(Student),1,fp);
        }

        fclose(fp);
        fclose(fp1);
    }
    else
        //cls();
        printf("\n\n\n\t\t\t\t***************************************************************");
        printf("\n\t\t\t\t\t\tR e c o r d   n o t  f o u n d!");
        printf("\n\t\t\t\t***************************************************************"); } }

/*
        do{

            printf("\n\n\n\t\t\t\tEdit another record? (Y/N)?: ");
            scanf(" %c", &askRecord);
            cls();
            askRecord=toupper(askRecord);           //capitalize inputs
            if(askRecord!='Y'&&askRecord!='N')
                 printf("\n\n\n\t\t\t\t***************************************************************");
        printf("\n\t\t\t\t\t\tI n v a l i d   r e s p o n s e!");
        printf("\n\t\t\t\t***************************************************************");

        }while(askRecord!='Y'&&askRecord!='N');     //loop if input is invalid
    }while(askRecord=='Y'); */
/*

Student s1;
FILE *fp,*fp1;
int j, rno, found=0;
fp=fopen("records.txt","r");
fp1=fopen("newrecords.txt","w");
printf("Enter ID number to edit:  ");
scanf("%d", &rno);
while(fread(&s1, sizeof (Student),1,fp))
{
    if (s1.rno==rno){
    s1.total =0;
    s1.average=0;
    found=1;
    fflush(stdin);
    printf("Enter NEW name : ");
    scanf("%[^\n]s",s1.name);
    for(j=0;j<3;j++){
        printf("Enter NEW grade in Subject%d : ", j+1);
        scanf("%d", &s1.sub[j].grade);
        s1.total+= s1.sub[j].grade;
    }
    s1.average=s1.total/3.0;
    }
    fwrite(&s1,sizeof (Student),1,fp1);
}   fclose(fp);
    fclose(fp1);
    if (found){
        fp1= fopen("newrecords.txt","r");
        fp = fopen("records.txt","w");

        while(fread(&s1,sizeof(Student),1,fp1)){
            fwrite(&s1,sizeof(Student),1,fp);
        }

        fclose(fp);
        fclose(fp1);
    }
    else
        printf("Record Not Found\n"); */







void deleteRecord(){
Student s1;
FILE *fp,*fp1;
int j, rno, found=0;
char askDelete;
do{
    fp=fopen("records.txt","r");
    fp1=fopen("newrecords.txt","w");


    cls();

    //Printing the screen layout
    printf("\n\n\n\t\t\t\t***************************************************************");
    printf("\n\t\t\t\t  D E L E T E   L I S T   O F   S T U D E N T ' S   R E C O R D S");
    printf("\n\t\t\t\t***************************************************************");

    printf("\n\n\n\t\t\t\tEnter ID number to delete:  ");
    scanf("%d", &rno);


    while(fread(&s1, sizeof (Student),1,fp))
    {
    if (s1.rno==rno){

    found=1;
    }
    else
        fwrite(&s1,sizeof (Student),1,fp1);
    }
    fclose(fp);
    fclose(fp1);
    if (found){
        fp1= fopen("newrecords.txt","r");
        fp = fopen("records.txt","w");

        while(fread(&s1,sizeof(Student),1,fp1)){
            fwrite(&s1,sizeof(Student),1,fp);}

        fclose(fp);
        fclose(fp1);


        cls();
        printf("\n\n\n\t\t\t\t***************************************************************");
       printf("\n\t\t\t\t\t\tRecord successfully deleted!");
       printf("\n\t\t\t\t***************************************************************");
       getch();
       cls();
    }
    else //(s1.rno!=rno);
        cls();
       printf("\n\n\n\n\t\t\t\t***************************************************************");
        printf("\n\t\t\t\t\t\tCheck your ID number....");
       printf("\n\t\t\t\t***************************************************************");



  do{
            printf("\n\n\n\t\t\t\tDelete stududent's record? (Y/N)? : \t");
            scanf(" %c", &askDelete);
            cls();
            askDelete=toupper(askDelete);           //capitalize inputs
            if(askDelete!='Y'&&askDelete!='N')
                printf("\n\n\n\t\t\t\t***************************************************************");
                printf("\n\t\t\t\t\t\tI n v a l i d   r e s p o n s e!");
                printf("\n\t\t\t\t***************************************************************");




        }while(askDelete!='Y'&&askDelete!='N');     //loop if input is invalid
        }while(askDelete=='Y');


         }

void fileRecord(){
Student *s, s1;
FILE *fp, *fp2;
int i,j;

cls();
fp= fopen("records.txt", "r");
fseek(fp,0,SEEK_END);
int n= ftell(fp)/sizeof(Student);
s=(Student*)calloc(n,sizeof(Student));

rewind(fp);
for(i=0;i<n;i++)
    fread(&s[i], sizeof(Student),1,fp);
fclose(fp);
    for (i=0;i<n; i++){
        for(j=i+1;j<n; j++){
            if(s[i].total<s[j].total){
                s1=s[i];
                s[i]=s[j];
                s[j]=s1;
        }
    }
}
fp2=fopen("finalrecords.txt","w");
fp=fopen("records.txt","w+");

    printf("\n\t\t\t\t***************************************************************");
    printf("\n\t\t\t\tL I S T   O F   S T U D E N T ' S   R E C O R D S   I N   F I L E ");
    printf("\n\t\t\t\t***************************************************************");
    printf("\n\t\t\t\tID NO.\tNAME\t\tFILIPINO   SCIENCE   ENGLISH\t AVERAGE");
    printf("\n\t\t\t\t================================================================");


    fprintf(fp2,"\n\t\t***************************************************************");
    fprintf(fp2,"\n\t\tL I S T   O F   S T U D E N T ' S   R E C O R D S   I N   F I L E ");
    fprintf(fp2,"\n\t\t***************************************************************");
    fprintf(fp2,"\n\t\tID NO.\tNAME\t\tFILIPINO   SCIENCE   ENGLISH\t AVERAGE");
    fprintf(fp2,"\n\t\t================================================================");





    for (i=0; i<n;i++){
    printf("\n\t\t\t\t%-5d\t%-20s",s[i].rno,s[i].name);

    fprintf(fp2, "\n\t\t%-5d\t%s\t\t", s[i].rno,s[i].name);

        for (j=0;j<3;j++){
           printf("%4d\t",s[i].sub[j].grade);
     fprintf(fp2, " %d\t ",s[i].sub[j].grade);

           }
        printf("%7.2f",s[i].average);
    fprintf(fp2, "\t%7.2f", s[i].average);
    fprintf(fp2, "\n");

         fwrite(&s[i],sizeof(Student),1,fp);
        //fprintf_s(fp2,"%n%-5d%-20s %4d %7.2f", s[i].rno,s[i].name, s[i].sub[j].grade,s[i].average);





        /*if (fp == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }

        fwrite(&s[i],sizeof(Student),1,fp);
        if(fwrite != 0)
        printf("contents to file written successfully !\n");
        else
        printf("error writing file !\n"); */




        //fprintf(&s[i],sizeof(Student),1,fp);
       // fprintf(fp, "\n%-5d %-20s %4d %.2f", s[i].rno,s[i].name, s[i].sub[j].grade,s[i].average);

    /*char cBuffer[1024]="";
        snprintf(cBuffer, sizeof(cBuffer),"%n%-5d%-20s %4d %7.2f", s[i].rno,s[i].name, s[i].sub[j].grade,s[i].average);
        fwrite(cBuffer,strlen(cBuffer),1,fp);

    */
        }
    fclose(fp);

        //fscanf(fp,"%n%-5d%-20s %4d %7.2f", s[i].rno,s[i].name, s[i].sub[j].grade,s[i].average);
         //fprintf(fp2,"%n%-5d%-20s %4d %7.2f", s[i].rno,s[i].name, s[i].sub[j].grade,s[i].average);


        fclose(fp2);
        printf("\n\n\n\n\t\t\t\tPress any key to go back to Mainmenu.......");
 getch();

}
void cls(){     //clears the output screen of the program
    system("cls");
}

int main()
{   system("COLOR F2");
    cls();
    int mainmenu;


    printf("\n\n\t\t\t\t*************************************************************");
        printf("\n\t\t\t\t*************************************************************");
        printf("\n\n\t\t\t\t\t\t\tWELCOME TO");
        printf("\n\n\t\t\t\t\t\t""PAGOD NA"" National High School");
        printf("\n\n\t\t\t\t\t\t---Student Grade Management--- ");

        printf("\n\n\t\t\t\t*************************************************************");
        printf("\n\t\t\t\t*************************************************************\n");
        printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\tPress any key........");
        getch();

cls();

    do{ cls();

        //SCREEN LAYOUT 1
        printf("\n\n\t\t\t\t*************************************************************");
        printf("\n\t\t\t\t*************************************************************");
        printf("\n\n\t\t\t\t\t\t\tM A I N M E N U\n");
        printf("\n\t\t\t\t*************************************************************");
        printf("\n\t\t\t\t*************************************************************");
        printf("\n\t\t\t\t1.) \tADD STUDENT\n");
        printf("\n\t\t\t\t2.) \tOPEN RECORDS\n");
        printf("\n\t\t\t\t3.) \tEDIT RECORDS\n");
        printf("\n\t\t\t\t4.) \tDELETE RECORDS\n");
        printf("\n\t\t\t\t5.) \tFILE RECORD\n");
        printf("\n\t\t\t\t6.) \tEXIT \n");
        printf("\n\n\t\t\t\tEnter a number: \t");
        scanf("%d", &mainmenu);

        switch(mainmenu){                           //A switch statement allows a variable to be tested for equality against a list of values.
            case 1: //File Mangement of Service
                addStudent();                //subprogram
                break;
            case 2: //Transaction
                openRecords();
                break;
            case 3: //Manage Advance Request
                //openRecords();
                editRecords();
                break;
            case 4: //Generate Report
                deleteRecord();
                break;
            case 5: //Exit Mainmenu
                fileRecord();
                break;
            case 6: //Exit Mainmenu
                exit(1);
            default:
                printf("\n\t\t\t\tInput must be from 1-6 only!");
                getch();
                break;                         // The default case can be used for performing a task when none of the cases is true.
        }
    }while(mainmenu !=0);

}
