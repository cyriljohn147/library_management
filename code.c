#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct libdata
{
  int bkid;
  char avalibility[5],bknm[30],author[30],isudt[15],retdt[15],lstnm[30];
};
struct student
{
  char nm[30];
  int no_bks,id;
};
typedef struct libdata libdata;
typedef struct student student;
void NEWBOOK();
void NEWSTU();
void DISPLAY();
void ISSUE();
void RETURN();
void DELETESTU();
void DELETEBK();
void main()
{

  int ch,k;
  L1:
    printf("==========LIBRARY MANAGEMENT==========");
    printf("\n1.NEW BOOK\n2.NEW STUDENT\n3.DISPLAY\n4.ISSUE\n5.RETURN\n6.DELETE STUDENT\n7.DELETE BOOK\n");
    printf("Enter option:");
    scanf("%d",&ch);
    switch(ch)
    {
      case 1: NEWBOOK();
              break;
      case 2: NEWSTU();
              break;
      case 3: DISPLAY();
              break;
      case 4: ISSUE();
              break;
      case 5: RETURN();
              break;
      case 6: DELETESTU();
              break;
      case 7: DELETEBK();
              break;
      default : printf("Invalid Case\n");
                break;
    }
    printf("Do you want to continue  : 0/1");
    scanf("%d",&k);
    if(k==1)
      goto L1;
    else
      exit(0);
}

void NEWBOOK()
{
   FILE *fp;
    int c,k,i,j;
    student buff;
    libdata buffer;
    printf("Enter no of books to be added in library:");
    scanf("%d",&i);
    //printf("no of students");
    //scanf("%d",&j);
    printf("\n ----------ENTER BOOK DETAILS----------\n\n");
    fp = fopen("LIBRARY RECORD.dat","a+");
    for(c=0;c<i;c++)
     {   fseek(fp,0,SEEK_CUR);
        printf("Enter book name:");
        scanf("%s",buffer.bknm);
        printf("Enter book id:");
        scanf("%d",&buffer.bkid);
        printf("Enter book author:");
        scanf("%s",buffer.author);
        strcpy(buffer.avalibility,"yes");
        strcpy(buffer.isudt,"not issued");
        strcpy(buffer.retdt,"not returned");
        strcpy(buffer.lstnm,"not issued");
        fwrite(&buffer,sizeof(libdata),1,fp);
    }
  fclose(fp);
  /* printf("\n  ENTER STUDENT DETAILS\n\n");
   fp=fopen("STUDENT RECORD.dat","a+");
    for(c=0;c<j;c++)
     {  fseek(fp,0,SEEK_CUR);
      printf("enter id number\n");
      scanf("%d",&buff.id);
      printf("enter name of student\n");
      scanf("%s",buff.nm);
      printf("enter no of books taken by student \n");
      scanf("%d",&buff.no_bks);
      fwrite(&buff,sizeof(student),1,fp);
     }
     fclose(fp);*/
}

void NEWSTU()
{ 
  FILE *fp;
  student buff;
  int j,c;
  printf("\n\nEnter no of students:");
  scanf("%d",&j);
  printf("\n----------ENTER STUDENT DETAILS----------\n");
   fp=fopen("STUDENT RECORD.dat","a+");
    for(c=0;c<j;c++)
     {  fseek(fp,0,SEEK_CUR);
      printf("enter id number:");
      scanf("%d",&buff.id);
      printf("enter name of student:");
      scanf("%s",buff.nm);
      buff.no_bks=0;
      fwrite(&buff,sizeof(student),1,fp);
     }
     fclose(fp);
}

void DISPLAY()
{
  FILE *fp;
  libdata buffer;
  student buff;
   fp = fopen("LIBRARY RECORD.dat","r");

    if (fp == NULL)
    {
        printf("error openin the file");
        exit(1);
    }
    else
    { printf("\t\t    ----------LIBRARY  RECORD----------    \t\t\n");
      printf("\n\t|  BOOK ID  |  BOOK NAME  |  AUTHOR  |  AVALIABILITY  |  ISSUE DATE  |  RETURN DATE  |  LAST ISSUED BY  |\t\n");
       fseek(fp, 0, SEEK_CUR);
      while (!feof(fp))
      {
        fread(&buffer, sizeof(libdata), 1, fp);
        if (feof(fp))
        {
            break;
        }
        printf("\n\t     %d\t\t%s\t\t%s\t \t%s \t %s\t   %s\t   %s\t\n", buffer.bkid, buffer.bknm,buffer.author,buffer.avalibility,buffer.isudt,buffer.retdt,buffer.lstnm);
      }
    }
    fclose(fp);
    fp=fopen("STUDENT RECORD.dat","r");
    if (fp == NULL)
    {
        printf("error openin the file");
        exit(1);
    }
    else
    {  printf("\n\t\t----------STUDENT  RECORD----------\t\t\n");
       printf("\n\t\t|  ID  |  NAME\t  |  NO OF BOOKS  |\t\n");
        fseek(fp, 0, SEEK_CUR);
      while (!feof(fp))
      {
        fread(&buff, sizeof(student),1,fp);
        if (feof(fp))
        {
            break;
        }
        printf("\n\t\t %d\t  %s      \t%d\t\n",buff.id,buff.nm,buff.no_bks);
      }
    }
  fclose(fp);  
}
void ISSUE()
{ 
  FILE *f,*fp,*b,*bb;
  int c,j;
  libdata buffer;
  student buff;
  int bidd,stid;
  char dt[15];
  printf("==========ISSUE OF BOOK==========\n");
  printf("Enter book id:");
  scanf("%d",&bidd);
  fp=fopen("LIBRARY RECORD.dat","r"); 
  if(fp == NULL)
  {
    printf("error openin the file");
    exit(1);
  }
  else
  {  bb=fopen("buffer.dat","w");
      fseek(bb, 0, SEEK_SET);
      fseek(fp, 0, SEEK_SET);
      while (fread(&buffer, sizeof(libdata), 1, fp))
      { 
        if(feof(fp))
        {  exit(0);
        }
        else
        {
        if(buffer.bkid==bidd)
        {
          if(strcmp(buffer.avalibility,"yes")==0)
          { 
            f=fopen("STUDENT RECORD.dat","r");
            if (f == NULL)
            {
                 printf("error openingthe file");
                  exit(0);
            }
            else
            {  printf("enter student id\n");
               scanf("%d",&stid);
              fseek(f, 0, SEEK_SET);
              b=fopen("buff.dat","w");
              fseek(b, 0, SEEK_SET);
              while (fread(&buff, sizeof(student), 1, f))
              {  if(feof(f))
                 { break;
                 }
                    if(buff.id==stid)
                    {
                      if(buff.no_bks<4)
                      { 
                         printf("enter today's date (dd/mm/yyyy) \n");
                        scanf("%s",dt);
                        printf("ISSUED SUCCESSFULLY\n");
                        strcpy(buffer.avalibility,"no");
                        ++buff.no_bks;
                        strcpy(buffer.retdt,"not returned");
                        strcpy(buffer.lstnm,buff.nm);
                        strcpy(buffer.isudt,dt);
                      }
                      else
                        printf("books limit over\n");
                    } //if 
                fwrite(&buff,sizeof(student),1,b);
              }//while
            }//else
          }//if
        }//if
      fwrite(&buffer,sizeof(libdata),1,bb);
      }
     }//while
     fclose(fp);
      fclose(f);
     fclose(bb);
     fclose(b); 
    if(b != NULL)
    {
        // printf("test\n");
      f = fopen("STUDENT RECORD.dat", "w");
      b = fopen("buff.dat", "r");
        fseek(b, 0, SEEK_SET);
       fseek(f, 0, SEEK_SET); 
     while (fread(&buff, sizeof(student), 1, b))
     {  if (feof(b))
        {
          break;
        }
        else
         fwrite(&buff, sizeof(student), 1, f);
     }
     fclose(f);
    fclose(b);
    }
    if(bb != NULL)
    { fp = fopen("LIBRARY RECORD.dat", "w");
      bb = fopen("buffer.dat", "r");
     fseek(bb, 0, SEEK_SET); 
     fseek(fp, 0, SEEK_SET);
      while (fread(&buffer, sizeof(libdata), 1, bb))
      {  if (feof(bb))
        {
           break;
        }
        else
        fwrite(&buffer, sizeof(libdata), 1, fp);
      }
      fclose(fp);
    fclose(bb);
    }
  }//else
}
void RETURN()
{
  FILE *f,*fp,*b,*bb;
  libdata buffer;
  student buff;
  int stid,bid;
  char dt[15];
  printf("enter student id\n");
  scanf("%d",&stid);
  f=fopen("STUDENT RECORD.dat","r");
  if(f == NULL)
  {
        printf("error openin the file");
        exit(1);
  }
  else
 {//e1
   fseek(f, 0, SEEK_SET);
   b=fopen("buff.dat","w");
   fseek(b, 0, SEEK_SET);
   while ( fread(&buff, sizeof(student), 1, f))
   {//w1
     if (feof(f))
     {
       break;
     }
     else
     {//e2
      if(buff.id==stid)
       { //i1
            printf("enter book id\n");
            scanf("%d",&bid);
            fp=fopen("LIBRARY RECORD.dat","r");
            if(fp == NULL)
            {
              printf("error openin the file");
              exit(1);
            }
            else
            {//e3
              bb=fopen("buffer.dat","w");
              fseek(bb, 0, SEEK_SET);
              fseek(fp, 0, SEEK_SET);
              while ( fread(&buffer, sizeof(libdata), 1, fp))
              { if(feof(fp))
                {break;
                }
                if(buffer.bkid==bid)
                {  if(buff.no_bks>0)
                    {
                      printf("enter today's date (dd/mm/yyyy)\n");
                      scanf("%s",dt);
                      printf("BOOK SUCESSFULLY RETURNED\n");
                   // buffer.avalibility="yes"
                      --buff.no_bks;
                    strcpy(buffer.avalibility,"yes");
                    strcpy(buffer.avalibility,"yes");
                    strcpy(buffer.retdt,dt);
                   }
                   else
                     printf("no books due to return\n");
                }
                fwrite(&buffer,sizeof(libdata),1,bb);
              }
            }//e3
           
        } //i1 
       fwrite(&buff,sizeof(student),1,b);
     } //e2
   }//w1
    fclose(fp);
      fclose(f);
     fclose(bb);
     fclose(b); 
    if(b != NULL)
    {
        // printf("test\n");
      f = fopen("STUDENT RECORD.dat", "w");
      b = fopen("buff.dat", "r");
        fseek(b, 0, SEEK_SET);
       fseek(f, 0, SEEK_SET); 
     while (fread(&buff, sizeof(student), 1, b))
     {   if(feof(b))
         {
            break;
         }
         else
         fwrite(&buff, sizeof(student), 1, f);
     }
     fclose(f);
    fclose(b);
    }
    if(bb != NULL)
    { fp = fopen("LIBRARY RECORD.dat", "w");
      bb = fopen("buffer.dat", "r");
     fseek(bb, 0, SEEK_SET); 
     fseek(fp, 0, SEEK_SET);
      while (fread(&buffer, sizeof(libdata), 1, bb))
      {  if(feof(bb))
         {break;
         }
        else
        fwrite(&buffer, sizeof(libdata), 1, fp);
      }
      fclose(fp);
      fclose(bb);
    }
  }
}
void DELETESTU()
{
  FILE *f,*b;
  student buff;
  int stid;
  printf("enter id of student u want to delete\n");
  scanf("%d",&stid);
   f = fopen("STUDENT RECORD.dat", "r");
   b = fopen("buff.dat", "w");
   fseek(b, 0, SEEK_SET);
   fseek(f, 0, SEEK_SET); 
  while ( fread(&buff, sizeof(student), 1, f))  
  { 
    if(feof(f))
    { // printf("hi  ");
       break;   
    }
    else
    { if(stid==buff.id)
       { continue; }
      else
        { fwrite(&buff, sizeof(student), 1, b);
         //printf("ll  ");
        }
    }
  }
  fclose(f);
  fclose(b);
  f = fopen("STUDENT RECORD.dat", "w");
   b = fopen("buff.dat", "r");
   fseek(b, 0, SEEK_SET);
   fseek(f, 0, SEEK_SET); 
  if( b != NULL)
  {
   while ( fread(&buff, sizeof(student), 1, b))  
  { if(feof(b))
    { //printf("test");
       break;   
    }
    else
    {
       fwrite(&buff, sizeof(student), 1, f);
      // printf("hh  ");
    }
  }
  }
  fclose(f);
  fclose(b);
}
void DELETEBK()
{
  FILE *fp,*bb;
  libdata buffer;
  int bid;
  printf("enter id of book u want to delete\n");
  scanf("%d",&bid);
   fp = fopen("LIBRARY RECORD.dat", "r");
   bb = fopen("buffer.dat", "w");
   fseek(bb, 0, SEEK_SET);
   fseek(fp, 0, SEEK_SET); 
  while ( fread(&buffer, sizeof(libdata), 1, fp))  
  { 
    if(feof(fp))
    {  //printf("hi  ");
       break;   
    }
    else
    { if(bid==buffer.bkid)
       { continue; }
      else
        { fwrite(&buffer, sizeof(libdata), 1, bb);
         //printf("ll  ");
        }
    }
  }
  fclose(fp);
  fclose(bb);
  fp = fopen("LIBRARY RECORD.dat", "w");
   bb = fopen("buffer.dat", "r");
   fseek(bb, 0, SEEK_SET);
   fseek(fp, 0, SEEK_SET); 
  if( bb != NULL)
  {
   while ( fread(&buffer, sizeof(libdata), 1, bb))  
  { if(feof(bb))
    {// printf("test");
       break;   
    }
    else
    {
       fwrite(&buffer, sizeof(libdata), 1, fp);
       //printf("hh  ");
    }
  }
  }
  fclose(fp);
  fclose(bb);
}