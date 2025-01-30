#include<stdio.h>    //Use for getchar(),cprintf() etc.
#include<conio.h>   //Use for getche(),getch(),clrscr(),gotoxy(), textcolor()
#include<string.h>  //gets(),
#include<stdlib.h>     //Use for exit(0) etc.
#include<dos.h>        //Use for delay() etc.
#include"data.h"       //Use for structur
#include"search.h"     //Use for search function

/*struct contact
{
int sno;
char category[20];
char name[20];
char gender;
int age;
char address[50];
char phone[15];
char email[50];
}cont;*/
void main()
{
void add_contact(); //prototype
void list_contact();
void delete_contact();
void edit_contact();
void search_contact();
char pass[30],original[30],ch,choice;
int i;
FILE *fp;  //perform basic file oprn-fopen(),fclose(),fseek(),ftell() etc.
window(1,1,80,25);
textbackground(YELLOW);
clrscr();
window(20,10,60,15);
textbackground(BLACK);
clrscr();
gotoxy(4,3);
textcolor(RED+BLINK);
cprintf("Enter the password:");
i=0;
while(1)  //known zero value is true that means condition is true-infinit loop
{
ch=getch();//To input a single character without display and without return(enter)
if(ch==13) //ASCII code ENTER key
{
pass[i]='\0';
break;
}
pass[i++]=ch;
printf("*");
}
 //Reading data from the file
fp=fopen("password.c","r");
fgets(original,30,fp); //fgets gets a string from a stream
fclose(fp);
if(!strcmp(original,pass)==0) /*string comarision*/
{
gotoxy(4,4);   /* Replace coursr*/
textcolor(WHITE+BLINK);
cprintf("Incurrect password, Press any key...");
getch();
exit(0);  /* To terminate the programe permanently*/
}
else
{
window(1,1,80,25);
textbackground(11);
clrscr();
gotoxy(32,3);
textcolor(RED);
cprintf("CONTACT MANAGER");
gotoxy(31,5);
textcolor(BLUE);
cprintf("Version no.:1.0");
gotoxy(22,8);
textcolor(YELLOW);
cprintf("Developed by: Love Kumar and Harsh Prakash");
gotoxy(5,15);
textcolor(RED);
cprintf("Please wait");
for(i=1;i<=50;i++)
{
cprintf("%c",220); // ASCII Code:220
delay(70); //To pause the execution of program for a fixed period
}
while(1)
{
textbackground(YELLOW);
clrscr();
window(18,5,60,22);
textbackground(BLACK);
clrscr();
textcolor(11);
gotoxy(18,2);
cprintf("MAIN MENU");
gotoxy(16,3);
printf("---------------");
textcolor(WHITE);
gotoxy(12,5);
cprintf("1 Add new contact");
gotoxy(12,6);
cprintf("2 Delete contact");
gotoxy(12,7);
cprintf("3 Editing");
gotoxy(12,8);
cprintf("4 Search contact");
gotoxy(12,9);
cprintf("5 List of contact");
gotoxy(12,10);
cprintf("6 Exit");
gotoxy(5,11);
cprintf("----------------------------------");
gotoxy(12,13);
textcolor(YELLOW+BLINK);
cprintf("Enter your choice(1-6)?");
choice=getche(); // To input a single character with echo but without return
switch(choice)
{
case '1':
add_contact();
break;
case '2':
delete_contact();
break;
case '3':
edit_contact();
break;
case '4':
search_contact();
case '5':
list_contact();
break;
case '6':
exit(0);
}
getch();
}
}
 }
// Function for Add Contact
void add_contact()
{
      FILE *fp;
      window(1,1,80,25);
      textbackground(YELLOW);
      textcolor(11);     //Color code 11--LIGHTCYAN
      clrscr();
      printf("Add new contact\n");
      printf("------------------------------------------");
      fflush(stdin);
      printf("\nEnter serial no : ");
      scanf("%d",&cont.sno);
      fflush(stdin); // to clear input buffer
      printf("Enter category (Friend/PG/Salesman/Customer/Student) : ");
      gets(cont.category);
      fflush(stdin);
      printf("Enter name : ");
      gets(cont.name);
      printf("Enter gender m/f: ");
      scanf("%c",&cont.gender);
      fflush(stdin);
      printf("Enter age : ");
      scanf("%d",&cont.age);
      fflush(stdin);
      printf("enter address : ");
      gets(cont.address );
      fflush(stdin);
      printf("Enter phone no : ");
      gets(cont.phone);
      fflush(stdin);
      printf("Enter email id : ");
      gets(cont.email);
      fflush(stdin);
      fp=fopen("info.dat","ab" );      //append mode binary format
      fwrite(&cont,sizeof(cont),1,fp); /*this function is used to write data
      into a binary data file (in the form of binary symbol) */
      fclose(fp);
      textcolor(WHITE+BLINK);
      cprintf("\nSuccessfully saved ,Press any key...");
      getch();
}
/*function for delete contact*/

void delete_contact()
{
      char choice;
      int n, found;
      FILE *fp1,*fp2;
      window(1,1,80,25);
      textbackground(BLACK);
      textcolor(YELLOW);
      clrscr();
      printf("Delete Contact");
      printf("\n-------------------------------------------------------------------");
      printf("\nEnter serial no to be deleted : ");
      scanf("%d",&n);
      fp1=fopen("info.dat","rb");  //read mode binary format
      found=0;
      while(fread(&cont,sizeof(cont),1,fp1)!=NULL);
      {
        if(cont.sno==n)
        {
          printf("\nCategory : %s",cont.category);
          printf("\nName     : %s",cont.name);
          printf("\nGender   : %s",cont.gender);
          printf("\nAge      : %d",cont.age);
          printf("\nAddress  : %s",cont.address);
          printf("\nPhone no : %s",cont.phone);
          printf("\nEmail Id : %s",cont.email);
          printf("\n------------------------------------------------------------------");
          found=1;
        }
      }
      if(found==0)
      {
         textcolor(RED+BLINK);
         printf("\n");
         cprintf("Not found, Press any key.....");
         getch();
         fclose(fp1);
         return;
      }
      printf("\nDelete it y/n : ");
      choice=getche();
      if(choice=='y'||choice=='Y')
      {
        rewind(fp1);
        fp2=fopen("temp.dat","wb");
        while(fread(&cont,sizeof(cont),1,fp1)!=NULL)
        {
          if(cont.sno!=n)
          fwrite(&cont,sizeof(cont),1,fp2);
        }
          fclose(fp1);
          fclose(fp2);
          remove("info.dat");
          rename("temp.dat","info.dat");
          textcolor(GREEN+BLINK);
          printf("\n");
          cprintf("Successfully deleted, Press any key...");
          getch();
      }
      }
/*function for edit contact*/

void edit_contact()
{
      FILE *fp;
      int n,pos,found;
      window(1,1,80,25);
      textcolor(YELLOW);
      textbackground(BLACK);
      clrscr();
      printf("Edit contact\n");
      printf("------------------------------------------------------------------");
      printf("\nEnter the serial no to be edited : ");
      scanf("%d",&n);
      fp=fopen("info.dat","r+b");
      found=0;
      while(fread(&cont,sizeof(cont),1,fp)!=NULL)
      {
       if(cont.sno==n)
      {
        found=1;
        printf("\nCategory : %s",cont.category);
        printf("\nName     : %s",cont.name);
        printf("\nGender   : %c",cont.gender);
        printf("\nAge      : %d",cont.age);
        printf("\nAddress  : %s",cont.address);
        printf("\nPhone no : %s",cont.phone);
        printf("\nEmail Id : %s",cont.email);
        break;
      }
      }
      if(found==0)
      {
        printf("\n");
        textcolor(RED+BLINK);
        cprintf("Not found, Press any key....");
        fclose(fp);
        getch();
        return;
      }
        printf("\nENTER NEW DATA\n");
        pos=ftell(fp);
        fseek(fp,pos-sizeof(cont),SEEK_SET);
        fflush(stdin); // to clear input buffer
        printf("Enter category (Friend/PG/Salesman/Customer/Student) : ");
        gets(cont.category);
        fflush(stdin);
        printf("Enter name : ");
        gets(cont.name);
        printf("Enter gender m/f: ");
        scanf("%c",&cont.gender);
        fflush(stdin);
        printf("Enter age : ");
        scanf("%d",&cont.age);
        fflush(stdin);
        printf("enter address : ");
        gets(cont.address );
        fflush(stdin);
        printf("Enter phone no : ");
        gets(cont.phone);
        fflush(stdin);
        printf("Enter email id : ");
        gets(cont.email);
        fflush(stdin);
        fwrite(&cont,sizeof(cont),1,fp);
        fclose(fp);
        printf("\n");
        textcolor(RED+BLINK);
        cprintf("Successfully updated, Press any key....");
        getch();
     }

/*function for list contact*/

void list_contact()
{
     int i;
     FILE *fp;
     window(1,1,80,25);
     textbackground(WHITE);
     textcolor(BLUE);
     clrscr();
     gotoxy(34,1);
     printf("LIST OF CONTACTS");
     printf("\n");
     for(i=1;i<=80;i++)
     printf("-");
     gotoxy(1,3);
     printf("SNO");
     gotoxy(8,3);
     printf("CATEGORY");
     gotoxy(20,3);
     printf("NAME");
     gotoxy(36,3);
     printf("GENDER");
     gotoxy(46,3);
     printf("AGE");
     gotoxy(55,3);
     printf("ADDRESS");
     gotoxy(70,3);
     printf("PHONE");
     printf("\n");
     for(i=1;i<=80;i++)
     printf("-");
     fp=fopen("info.dat","rb");
     i=5;
     while(fread(&cont,sizeof(cont),1,fp)!=NULL) /*fread()- This function is
     used to read data from the binary data file and store in variable (in
     the form of character)*/
     {
        gotoxy(1,i);
        printf("%d",cont.sno);
        gotoxy(8,i);
        printf("%s",cont.category);
        gotoxy(20,i);
        printf("%s",cont.name);
        gotoxy(36,i);
        printf("%c",cont.gender);
        gotoxy(46,i);
        printf("%d",cont.age);
        gotoxy(55,i);
        printf("%s",cont.address);
        gotoxy(70,i);
        printf("%s",cont.phone);
        i++;
     }
        fclose(fp);
        textcolor(RED+BLINK);
        printf("\n");
        cprintf("Press any key....");
        getch();
     }
//Search contact
 void search_contact()
 {
     char ch;
     window(1,1,80,25);
     textbackground(BLACK);
     textcolor(11);
     clrscr();
     textcolor(WHITE);
     cprintf("SEARCH OPTION");
     printf("\n");
     printf("---------------------------------------------------------");
     printf("\n1  Search by serial no ");
     printf("\n2  Search by category ");
     printf("\n3  Search by name ");
     printf("\n4  Search by phone no ");
     printf("\n5  Back to back menu ");
     printf("\n-------------------------------------------------------");
     textcolor(YELLOW+BLINK);
     printf("\n");
     cprintf("Enter your choice(1-5) ?");
     ch=getche();
     switch(ch)
     {
        case '1':
        search_sno();
        break;
	case '2':
        search_category();
        break;
	case '3':
	search_name();
        break;
	case '4':
        search_phone();
	break;
        case '5':
        return;
	}
	getch();
     }


