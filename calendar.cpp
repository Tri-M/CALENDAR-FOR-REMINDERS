#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include<conio.h>
#include<cstdlib>

#include<stdio.h>
#include"windows.h"
using namespace std;

void showAppName();
void getInput(BOOL);
BOOL checkLeap();
BOOL printCalendar(int);
void printAppointments();
void pause();
int getNumber();
#define CONSO GetConsoleScreenBufferInfo
#define GREEN   10
#define CYAN    11
#define RED     12
#define MAGENTA 13
#define YELLOW  14
#define WHITE   15
void* h = ::GetStdHandle((DWORD)-11);
CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

int attr = CONSO(h, &csbiInfo);
void setTextColor(int color)
{
  SetConsoleTextAttribute(h, color);
}
void setCursor(int row, int col)
{
  COORD coord = {col, row};
  SetConsoleCursorPosition(h, coord);
}
void display_app();
BOOL check_leap();
void pause();
int checkDate();
int day, month, year, appointmentDay;


class Account
{
        
        protected:
            char username[50];
            char password[50];
            unsigned int role;
            
        public:
            
            void Register()
            {               
                ofstream fs("logindata.txt",ios::app);   
               std::cout<<"\nEnter username: ";
                cin>>username;
               std::cout<<"\nEnter password: ";
                cin>>password;
               std::cout<<"Press \n 1. Student \n 2. Faculty \n 3. Admin"<<endl;
                cin>>role;
                fs<<username<<" "<<password<<" "<<role<<" ";  
                ofstream oeam;
                oeam.open("logging.txt",ios::app);
                oeam<<"User registered.\n";
           time_t nowtime=time(0);
           char* deat=ctime(&nowtime);
           oeam<<deat<<endl;
           oeam.close();
                fs.close();
            }
            int login(char  un[],char pw[])
            { 
              int flag=1;
                ifstream fs("logindata.txt",ios::in);
                ofstream t("time.txt",ios::app);
                  while(!fs.eof())
                  {
                 fs>>username>>password>>role;                                  
                if(strcmp(un,username)==0 && strcmp(pw,password)==0)
                {
                    if(role==1)
                    {
                        std::cout<<"\nstudent  : "<<username;
                        return 1;
                    }
                    else if(role==2)
                    {
                       std::cout<<"\nfaculty : "<<username;
                       return 1;
                    }
                    else if(role==3)
                    {
                       std::cout<<"\nAdmin : "<<username; 
                       return 1;                       
                    }
                    flag=0;
                                      
                }                                         
              }                
                fs.close();
                if(flag==1)
    {     
        t<<"Tried to login at\n";
        time_t now=time(0);
        char* dt=ctime(&now);
        t<<dt<<endl;
        t.close();
       std::cout<<"Username or Password does not match. Try again later";
        return 0;
    }
    return 1;                           
            }
};

string appointmentText;
class Calendar:public Account
{
public:
int calendarfunc();
};

int Calendar::calendarfunc()
{
    setTextColor(WHITE);
  menu:
showAppName();
  setCursor(3, 20);  
 std::cout << "\nPick a menu";
  setCursor(5, 20);
 std::cout << "\n1. CHECK LEAP YEAR";
  setCursor(7, 20);
 std::cout << "\n2. PRINT CALENDAR";
  setCursor(9, 20);
 std::cout << "\n3. ADD REMINDERS / APPOINTMENTS"; 
   setCursor(11, 20);
 std::cout << "\n4. Quit";
  setCursor(13, 20);
 std::cout << "\nEnter a choice : ( 1 or 2 or 3 or 4) :  ";
  int choice = getNumber();
  ofstream o;
  o.open("logging.txt",ios::app);
  o<<"Choice for calendar entered.\n";
           time_t now=time(0);
           char* dt=ctime(&now);
           o<<dt<<endl;
           o.close();
  switch (choice)
  {   
  case 1:
    {      
      getInput(0);
      setCursor(5, 20);
     std::cout << "\nResult is: ";
      if(checkLeap())
      {
       std::cout << "\nLeap year";
      }
      else 
      {
       std::cout << "\nNot a Leap year";
      }
      setCursor(7, 20);
      ofstream o;
  o.open("logging.txt",ios::app);
  o<<"Leap year condition checked.\n";
           time_t now=time(0);
           char* dt=ctime(&now);
           o<<dt<<endl;
           o.close();
     std::cout << "\nDone.Press on any key.";
      pause();
      goto menu;
    }    
  case 2:
    {
    getmon:      
      getInput(1);  
      ofstream o;
  o.open("logging.txt",ios::app);
  o<<"Input for printing the calendar of a particular month entered.\n";
           time_t now=time(0);
           char* dt=ctime(&now);
           o<<dt<<endl;    
           o.close();
      appointmentDay = -1;
      if(!printCalendar(8))
      {
        setCursor(23, 20);
        setTextColor(RED);
       std::cout << "\nCalendar dates not appropriate :(  ";
       ofstream o;
       o.open("logging.txt",ios::app);
       o<<"Inappropriate dates entered. User made to enter the data again.\n";
           time_t now=time(0);
           char* dt=ctime(&now);
           o<<dt<<endl;
           o.close();
       std::cout << "Enter again.";
          pause();

        setTextColor(WHITE);
        goto getmon;
      }
      else 
      {
       setCursor(23, 20);
       std::cout<<"Done. Press any key.";        
       ofstream o;
       o.open("logging.txt",ios::app);
       o<<"Calendar printed.\n";
           time_t now=time(0);
           char* dt=ctime(&now);
           o<<dt<<endl;
           o.close();
        pause();
        goto menu;
      }
    }
  case 3:
    {
    getday:
      getInput(1);
      setCursor(7, 20);
     std::cout << "Enter day: ";  
      appointmentDay = getNumber();  
      ofstream ofs;
  ofs.open("logging.txt",ios::app);
  ofs<<"Input for adding the reminder entered.\n";
           time_t pres=time(0);
           char* d=ctime(&pres);
           ofs<<d<<endl;  
           ofs.close(); 
      setCursor(9, 20);      
     std::cout << "Enter text (maximum of 25 characters):";
      ofstream fp("entries.txt",ios::app);         
      getline(cin, appointmentText); 
      fp<<appointmentDay<<'-'<<appointmentText<<endl;    
      fp<<endl; 
      ofstream of;
      of.open("logging.txt",ios::app);
      of<<"Reminder added.\n";
           time_t curr=time(0);
           char* dat=ctime(&curr);
           of<<dat<<endl;
           of.close();
      fp.close();
      if(appointmentText.size() > 25)
      {
        appointmentText.erase(25);
      }
      showAppName();      
      if(printCalendar(4))
      {
       printAppointments();
        setCursor(23, 20);
       std::cout <<"Done. Press any key.";
       ofstream o;
      o.open("logging.txt",ios::app);
      o<<"Reminders displayed.\n";
           time_t now=time(0);
           char* dt=ctime(&now);
           o<<dt<<endl;
           o.close();
        pause();
      }
      else 
      {      
        setCursor(23, 20);
        setTextColor(RED);
       std::cout << "Calendar dates not appropriate. ";
       std::cout << "Enter again...";
       ofstream o;
      o.open("logging.txt",ios::app);
      o<<"Inappropriate dates. User made to enter again.\n";
           time_t now=time(0);
           char* dt=ctime(&now);
           o<<dt<<endl;
           o.close();
        pause();
        setTextColor(WHITE);
        goto getday;
      }
      goto menu;
      fp.close();
    }
  case 0:
    {
      goto menu;
    }
  default:
   break;
  }
  SetConsoleTextAttribute(h, csbiInfo.wAttributes);  //console goes back to the reset state
  return 0;
}
void showAppName()
{
  system("cls");
  setCursor(1, 25);
 std::cout << "CALENDAR BY 20PW19 AND 20PW39";
 ofstream o;
      o.open("logging.txt",ios::app);
      o<<"Title displayed .\n";
           time_t now=time(0);
           char* dt=ctime(&now);
           o<<dt<<endl;
           o.close();
  setCursor(10, 3);
  setTextColor(GREEN);
  for(int x =0; x < 5; x++)
  {
    setCursor(2 + x, 3 + x);
   std::cout << "";
    setCursor(2 + x, 12 - x);
   std::cout << "";
  }
  setCursor(6, 6);
 std::cout << " ";
  setTextColor(WHITE);
}
void getInput(BOOL monthAlso)
{
  showAppName();
  setCursor(3, 20);
  if(monthAlso)
  {
   std::cout << "\nEnter a month number [from 1 to 12] : ";
    month = getNumber();
    ofstream o;
      o.open("logging.txt",ios::app);
      o<<"User made to enter the month .\n";
           time_t now=time(0);
           char* dt=ctime(&now);
           o<<dt<<endl;
           o.close();
    month -= 1;
    setCursor(5, 20);
  }
 std::cout << "\nEnter a year between 1970 to 3000 : ";
  year = getNumber();
  ofstream o;
      o.open("logging.txt",ios::app);
      o<<"User made to enter the year.\n";
           time_t t=time(0);
           char* date=ctime(&t);
           o<<date<<endl;
           o.close();
  year -= 1900;
}
int checkDate()
{
  tm t = {0, 0, 0, day, month, year};
  if(mktime(&t) < 0)
  {
    return -1;
  }
  if(day != t.tm_mday)
  {
    return -1;
  }
  if(month != t.tm_mon)
  {
    return -1;
  }
  if(year != t.tm_year)
  {
    return -1;
  }
   return t.tm_wday;
}
BOOL checkLeap()
{
  day = 29;
  month = 1;
  return checkDate() >= 0;
}
BOOL printCalendar(int fromRow)
{
  day = 1;  
  if(-1 == checkDate())
  {
    return false;
  }
  int row = fromRow;
  setCursor(row, 24);
 std::cout << "CALENDAR for ";
 std::cout << month + 1 << "-";
 std::cout << year + 1900;
  row += 2;
  setCursor(row, 20);
 std::cout << "Mo  Tu  We  Th  Fr  Sa  Su";
  row += 2;
  setCursor(row, 20);
 std::cout << "==========================";
  row += 1;
  while(true)
  {
    switch(checkDate())
    {      
    case 1: //monday
    {
      setCursor(row, 20);
    }
    break;
    case 2: //tuesday
      {
        setCursor(row, 24);
      }
      break;
      case 3:
      {
        setCursor(row, 28);
      }
      break;
     case 4:
      {
        setCursor(row, 32);
      }
      break;
    case 5: //friday
      {
        setCursor(row, 36);
      }
      break;
      case 6:
      {
        setTextColor(CYAN);
        setCursor(row, 40);
      }
      break;
    case 0:
      {
      setTextColor(CYAN);
      setCursor(row, 44);  
        row += 2;
      }
      break;
    default:
      {
        return true;
      }

    }
        if(appointmentDay >= 1)
    {
      if(appointmentDay == day)
      {
        setTextColor(YELLOW); //yellow colour for appointments
      }      
   }
    printf("%2d", day++);
    setTextColor(WHITE);
  }
}
void printAppointments()
{
  setTextColor(GREEN);  
  for(int x = 2; x < 24; x++)
  {
    setCursor(x, 48);
   std::cout << "||";
  }
  setTextColor(MAGENTA);
  setCursor(2, 56); 
 std::cout << "\n";
  setCursor(4, 52);
  ifstream f("entries.txt",ios::in);
  int i=5;
  while(f)
     {  setCursor(i, 58);
      string apptext;
      getline(f,apptext,'\n');
     std::cout<<apptext<<endl;
      i++; 
     }       
  f.close();
  ofstream om;
      om.open("logging.txt",ios::app);
      om<<"Reminders printed.\n";
           time_t nw=time(0);
           char* det=ctime(&nw);
           om<<det<<endl;
           om.close();
  setCursor(i, 52);
  setTextColor(WHITE);
}
int getNumber()
{
  string s;
  getline(cin, s);
  return atoi(s.c_str());
}
void pause()
{
  string s;
  getline(cin, s);
}
 
//main function 
//execution begins from here

int main()
{
    
    Account a;
    Calendar c;
    
    while(1)
    {
    system("cls");
    char username[50],password[50];
    int ch;
   std::cout<<" ======PROJECT BY 20PW19 AND 20PW39======";
   std::cout<<"\n 1. Login \n 2. Signup \n 3. Exit"<<endl;
   std::cout<<"\n Enter choice: ";
    cin>>ch;
    switch(ch)
    {
        case 1:
        {  l1:       
          std::cout<<" \nUsername : "; cin>>username;
          std::cout<<" \nPassword : "; cin>>password;
          if(a.login(username,password)==0)
           goto l1;          
           c.calendarfunc();
           break;
        }
        case 2:
        {
        a.Register();
        break;
        }
        case 3:
        {
        exit(0);
        }
    }
}
}