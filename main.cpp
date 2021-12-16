#include<fstream.h>
#include<iomanip.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>
class student
{
  int rollno;
  char name[50],password,kvmeg;
  int p_marks,c_marks,m_marks,e_marks,cs_marks;
  float per;
  char grade;
  void calculate();
  public:
  void getdata();
  void showdata();
  void show_tabular();
  int retrollno();
  int roll()
  {
    return(rollno);
  }
};

void student::calculate()
{
  per=(p_marks+c_marks+m_marks+e_marks+cs_marks)/5;
  if(per>=60)
   grade='A';
  else if(per>=50)
   grade='B';
  else if(per>=33)
   grade='C';
  else
   grade='F';
}
void student::getdata()
{
 int r;
 student s;
 cout<<"\nENTER THE ROLL NO OF THE STUDENT:";
 cin>>r;
 fstream sid("student.dat",ios::binary|ios::in);
     while(!sid.eof())
     {
      sid.read((char*)&s,sizeof(student));
      if(s.roll()==r)
      {
       cout<<"THIS ROLL NO ALREADY EXISTS";
       goto last;
       }
      }
 rollno=r;
 sid.close();

 cout<<"\nENTER THE NAME OF STUDENT:";
 gets(name);
 cout<<"\nEnter the marks obtained in Physics out of 100:";
 cin>>p_marks;
 cout<<"\nEnter the marks obtained in Chemistry out of 100:";
 cin>>c_marks;
 cout<<"\nEnter the marks obtained in English out of 100:";
 cin>>e_marks;
 cout<<"\nEnter the marks obtained in Maths out of 100:";
 cin>>m_marks;
 cout<<"\nEnter the marks obtained in Computer Science out of 100:";
 cin>>cs_marks;
 calculate();
 cout<<"Record Created";
 last:
 }
void student::showdata()
 {
    cout<<"\nRoll no. of student:"<<rollno;
    cout<<"\nName of student:"<<name;
    cout<<"\nMarks in physics:"<<p_marks;
    cout<<"\nMarks in chemistry:"<<c_marks;
    cout<<"\nMarks in english:"<<e_marks;
    cout<<"\nMarks in maths:"<<m_marks;
    cout<<"\nMarks in computer science:"<<cs_marks;
    cout<<"\nPercentage of student is:"<<per;
    cout<<"\nGrade of student is:"<<grade;
    getch();
  }

void student::show_tabular()
{
 cout<<rollno<<"\t";
 for(int sd=0;sd<strlen(name)&&sd<15;sd++)
 cout<<name[sd];
 if(strlen(name)<=6)
 cout<<"\t";
 cout<<"\t"<<p_marks<<"\t"<<c_marks<<"\t"<<e_marks<<"\t"<<m_marks<<"\t"<<cs_marks<<"\t"<<per<<"\t"<<grade<<endl;
}

int student::retrollno()
{
 return rollno;
}
void write_student();
void display_all();
void display_sp(int);
void modify_student(int);
void delete_student(int);
void class_result();
void result();
void intro();
void entry_menu();

int main()
{
  s:
  char ch;
  cout.setf(ios::fixed|ios::showpoint);
  cout<<setprecision(2);
  clrscr();
  intro();
  do
  {
    clrscr();
    cout<<"\n\n\n\t         MAIN MENU";
    cout<<"\n\n\t01.RESULT MENU";
    cout<<"\n\n\t02.ENTRY/EDIT MENU";
    cout<<"\n\n\t03.CLEAR ALL RECORDS\n\n\t04.Exit";
    cout<<"\n\n\tPLEASE SELECT YOUR OPTION(1-3)";
    cin>>ch;
    clrscr();
    switch(ch)
    {
      case '1': result();
		break;
      case '2': entry_menu();
		break;
      case '3': remove("student.dat");
		cout<<"\n\n\tALL RECORDS DELETED...";
		getch();
		break;
      case '4':
		break;
      default:cout<<"\a";
     }
     }while(ch!='4');
     return 0;
     }

void write_student()
{
  student st;
  ofstream outfile;
  outfile.open("student.dat",ios::binary|ios::app);
  st.getdata();
  outfile.write((char*)&st,sizeof(student));
  cin.ignore();
  getch();
}

void display_all()
{
  student st;
  ifstream infile;
  infile.open("student.dat",ios::binary);
  if(!infile)
  {
   cout<<"FILE COULD NOT BE OPEN !! PRESS ANY KEY...";
   getch();
   return;
  }
 cout<<"\n\n\n\tDISPLAY ALL RECORD\n\n";
 while(!infile.eof())
 {
  infile.read((char*)&st,sizeof(student));
  if(infile.eof()||!infile)
  break;
  st.showdata();
cout<<"\n\n===============================\n\n";
   }
 }

void display_sp(int n)
{
   student st;
   ifstream infile;
   infile.open("student.dat",ios::binary);
   if(!infile)
   {
    cout<<"FILE COULD NOT BE OPEN !! PRESS ANY KEY...";
    getch();
    return;
   }
   int flag=0;
   while(infile.read((char*)&st,sizeof(student)))
   {
    if(st.retrollno()==n)
     {
      st.showdata();
      flag=1;
      }
     }
    infile.close();
    if(flag==0)
    cout<<"\n\nRECORD DOES NOT EXIST...";
    getch();
}

void modify_student(int n)
{
 int found=0;
 student st;
 fstream file;
 file.open("student.dat",ios::binary|ios::in|ios::out);
 if(!file)
 {
  cout<<"FILE COULD NOT BE OPEN !! PRESS ANY KEY...";
  getch();
 }
 while(file.read((char*)&st,sizeof(student))&&found==0)
 {
  if(st.retrollno()==n)
  {
   st.showdata();
   cout<<"\n\nPLEASE ENTER THE NEW DETAILS OF STUDENT"<<endl;
   st.getdata();
   int pos=(-1)*sizeof(st);
   file.seekp(pos,ios::cur);
   file.write((char*)&st,sizeof(student));
   cout<<"\n\n\t RECORD UPDATES";
   found=-1;
    }
   }
   file.close();
   if(found==0)
   cout<<"\n\n RECORD NOT FOUND";
   getch();
}

void delete_student(int n)
{
 int flag=0;
 student st;
 ifstream infile;
 infile.open("student.dat",ios::binary);
 if(!infile)
 {
  cout<<"FILE COULD NOT BE OPEN !! PRESS ANY KEY...";
  getch();
  return;
 }
 ofstream outfile;
 outfile.open("temp.dat",ios::out|ios::binary);
 infile.seekg(0,ios::beg);
 while(!infile.eof())
 {
  infile.read((char*)&st,sizeof(student));
  if(infile.eof())
  break;
  if(st.retrollno()!=n)
  {
     outfile.write((char*)&st,sizeof(student));
  }
  else if(st.retrollno()==n)
  {
   flag=1;
  }
 }
 outfile.close();
 infile.close();
 remove("student.dat");
 rename("temp.dat","student.dat");
  if(flag==1)
  cout<<"\n\n\tRECORD DELETED...";
  else
  cout<<"\n\nNO RECORD FOUND";
  getch();
}

void class_result()
{
  student st;
  ifstream infile;
  infile.open("student.dat",ios::binary);
  if(!infile)
  {
   cout<<"FILE COULD NOT BE OPEN !! PRESS ANY KEY...";
   getch();
   return;
  }
  cout<<"\n\n\tALL STUDENTS RESULT \n\n";
  cout<<"==============================================================\n";
  cout<<"|R.No\t|Name\t\t|Phy\t|Che\t|Mat\t|Eng\t|CS\t|%age\t|Grade"<<endl;
  cout<<"================================================================";
  while(infile.read((char*)&st,sizeof(student)))
  {
   st.show_tabular();
  }
  cout<<"==============================================================\n";
  getch();
  infile.close();
 }

void result()
{
 char ch;
 int rno;
 cout<<"\n\n\tRESULT MENU";
 cout<<"\n\n\t1.CLASS RESULT";
 cout<<"\n\n\t2.STUDENT REPORT CARD";
 cout<<"\n\n\t3.BACK TO MAIN MENU";
 cout<<"\n\n\tENTER YOUR CHOICE(1-3)..";
 cin>>ch;
 switch(ch)
 {
   case '1': class_result();
	     break;
   case '2': cout<<"\n\n\tENTER ROLL NO OF STUDENT:";
	     cin>>rno;
	     display_sp(rno);
	     break;
   case '3': break;
   default:cout<<"\a";
   }
  }

void intro()
{
 cout<<"\n\n\t             COMPUTER SCIENCE INVESTIGATORY PROJECT";
 cout<<"\n\n\t                       STUDENT REPORT CARD";
 cout<<"\n\n\t       MADE BY : MD.DILSHAD, ZIAUR RAHMAN, OF STD. XII 'A4'";
 cout<<"\n\n\t               UNDER THE GUIDANCE OF MR. TANMOY PAUL";
 getch();
}

void entry_menu()
{
 char ch;
 int num;
 clrscr();
 cout<<"\n\n\t ENTRY MENU";
 cout<<"\n\n\t1. CREATE STUDENT RECORD";
 cout<<"\n\n\t2. DISPLAY ALL STUDENT RECORDS";
 cout<<"\n\n\t3. SEARCH STUDENT RECORD";
 cout<<"\n\n\t4. MODIFY STUDENT RECORD";
 cout<<"\n\n\t5. DELETE STUDENT RECORD";
 cout<<"\n\n\t6. BACK TO MAIN MENU";
 cout<<"\n\n\tPLEASE ENTER YOUR CHOICE";
 cin>>ch;
 switch(ch)
 {
  case '1': write_student();
	    break;
  case '2': display_all();
	    break;
  case '3': cout<<"\n\n\tPLEASE ENTER THE ROLL NO.";
	    cin>>num;
	    display_sp(num);
	    break;
  case '4': cout<<"\n\n\tPLEASE ENTER THE ROLL NO.";
	    cin>>num;
	    modify_student(num);
	    break;
  case '5': cout<<"\n\n\tPLEASE ENTER THE ROLL NO.";
	    cin>>num;
	    delete_student(num);
	    break;
  case '6': break;
  default:cout<<"\a";
  entry_menu();
  }
 }
