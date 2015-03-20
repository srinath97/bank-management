//OM VINAYAKAYA NAMAHA
#include<iostream>
#include<conio.h>
#include<fstream>
#include<time.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
time_t t = time(0);
struct tm * now = localtime( & t );
const int N=50;
class passbook
{
      public:
      int dat,mont,yea;
      char part[N];
      int acn;
      double wmon,dmon,tot;
}; 
void next(int &d,int &m,int &y) // TO RETURN THE DUE DATE BEFORE WHICH LOAN HAS TO BE PAID
{
     switch (m)
     {
            case 1:
            case 3:
            case 5:
            case 7:                                 
            case 8:                                                  
            case 10:
                if(d==31)
                {
                    if(m==1)
                       d=28;
                    else     
                        d=30;
                }
                m++;
            break;
            case 12:
                 m=1;
                 y++;
            break;
            default:
                m++;    
     }
}
class bank
{
      public:
      char name[N];
      int number,type,ag,top,fy;
      char key[N];
      char pass[5]; 
      double days;
      long double money,income,bal,inte,loan;
      passbook entry[N];
      time_t sec;
      int da,mo,ye;
      char ph[15],address[N];
      void newaccount(int f,int g=0) // TO CREATE A NEW ACCOUNT
      {
	   cin.get();
	   cout<<"\nAccount number:\t\t "<<f+1000<<endl;
	   cout<<"\nEnter the account name:  ";
	   cin.getline(name,100);
	   number=f+1000;
       cout<<"\nEnter password:		 ";
	   char c=' ';
	   int i=0;
       while(c!=13)
       {
           c=getch();
           if(c!=13&&c!=8)
           {
               pass[i]=c;
	       cout<<"*";
               i++;
           }
           else if(c==8&&i>0)
	   {
                cout<<'\b';
                i=i-1;
           }
       }
       pass[i]='\0';
       cout<<endl<<endl;
       cout<<"Enter any keywords:      ";
       cin>>key;
       if(g)
       {
          type=4;
	  do
		  {
		       cout<<"\nEnter your age type\n"
			       <<"1-Adult \n"
				   <<"2-Senior citizen: 	";
		       cin>>ag;
		  }while(ag!=1 && ag!=2);
		  if(ag==1)
    		  inte=1.00;
	      else
	          inte=0.75;
		  cout<<"\nEnter your annual income:	";
		  cin>>income;
		  do
		  {
              cout<<"\nEnter the number of years:	";
              cin>>fy;
          }while(fy<=0);
		  do
		  {
                cout<<"\nEnter Loan amount	";
                cin>>money;
				if(money+inte*money>income*fy)
                   cout<<"Loan amount is high!!!\a\n	";
          }while(money+inte*money>income*fy);
          loan=money;
          money=money+inte*money;
          da = now->tm_mday;
          mo= now->tm_mon+1;
          ye = now->tm_year+1900;   
          next(da,mo,ye);  
          bal=money/(12*fy); 
	  cout<<"\nDeposit "<<bal<<"Rs before "<<da<<"/"<<mo<<"/"<<ye<<endl;
       }
       else
       {
    	   do
    	   { 
               cout<<"\nEnter the type  \n1-Savings account \n2-Current account \n3-Fixed deposit: 	";
    	       cin>>type;
    	   }while(type!=1 && type!=2 && type!=3);
    	   if(type==1 || type==3)
	   {
    		  do
    		  {
    		       cout<<"\nEnter your age type\n 1-Adult\n 2-Senior citizen: 	";
    		       cin>>ag;
    		  }while(ag!=1 && ag!=2);
    		  if(ag==1)
    		      inte=0.75;
		      else
		          inte=1.00;
    	   }
		   //INTEREST FOR ADULTS 9 % PER ANNUM
    	   //INTEREST FOR SENIOR CITIZENS 12 % PER ANNUM
    	   else 
    	       ag=0;
           if (type==3)
           {
                 cout<<"\nEnter the number of years:	";
                 cin>>fy;
                 fy=fy*365;
           }          
    	   do
	   {
    	      cout<<"\nEnter money deposited:   ";
    	      cin>>money;
    	   }while(money<0);
        }
        cin.get();
        cout<<"\nEnter your phone number: ";
        cin.getline(ph,15);
        cout<<"\nEnter your Address:    ";
        cin.getline(address,50);
       days=0;
       top=0;
       time(&sec);
      }
};
int check(int no) // TO CHECK WETHER THE THE GIVEN ACCOUNT NUMBER EXISTS
{
     bank b;
     ifstream fin("bankmanage.dat",ios::binary);
     if(fin)
     {
            fin.read((char*)&b,sizeof(b));     
            while(!fin.eof())
            {
                if(b.number==no)
                {
                     fin.close();            
                     return 1;
                }
                else
                    fin.read((char*)&b,sizeof(b));
            }
     }
     fin.close();
     return 0;
}
void writef(bank &b,int &acc) // TO WRITE THE OBJECT INTO THE BINARY FILE
{
         ifstream fin("bankmanage.dat",ios::binary);
         bank ban;
	 ofstream fout("temp.dat",ios::binary);
         if(fin)
         {
                fin.read((char*)&ban,sizeof(ban));
                while(!fin.eof())
                {
                      if(ban.number!=acc)
                          fout.write((char*)&ban,sizeof(ban));
                      else
                          fout.write((char*)&b,sizeof(b));
                      fin.read((char*)&ban,sizeof(ban));
                }
                
         }
         else
             fout.write((char*)&b,sizeof(b));
         fin.close();
         fout.close();
	 remove("bankmanage.dat");
	 rename("temp.dat","bankmanage.dat");

}
void retcust(bank &b,int acc) // TO RETREIVE A CUSTOMER'S DETAILS AND TO RETURN IT 
{
    bank x;
    int found=0;
    ifstream fin("bankmanage.dat",ios::binary);
    if(fin)
    {
         fin.read((char *)&x,sizeof(x));
         while(!fin.eof()&&found==0)
         {
             if(x.number==acc)
             {
                   b=x;
                   found=1;
             }
             else
                 fin.read((char*)&x,sizeof(x));
         }
	 fin.close();
    }
}
void disp1(int no) // TO DIPLAY THE ACCOUNT DETAILS OF THE CUSTOMER
{
      cout<<"\nYOUR ACCOUNT DETAILS\n\n";
      bank ba;
      retcust(ba,no);
      cout<<"Account name:   "<<ba.name<<endl;
      cout<<"Account number: "<<ba.number<<endl ;
      if(ba.type==1)
	      cout<<"Type:		Savings"<<endl;
      else if(ba.type==2)
	      cout<<"Type:		Current"<<endl;
      else if(ba.type==3)
	      cout<<"Type:		Fixed deposit"<<endl;
      else if(ba.type==4)
           cout<<"Type:	Loan\n";
      if(ba.ag==1)
	      cout<<"Age Type:	Adult"<<endl;
      else if(ba.ag==2)
	      cout<<"Age Type:	Senior citizen"<<endl;
      else
          cout<<"Age Type:	NILL"<<endl;
      cout<<"Phone number:	"<<ba.ph<<endl;
      cout<<"Address:        "<<ba.address<<endl;
      if( ba.type==3)
          cout<<"Remaining days:	"<<ba.fy-ba.days<<endl;                    
      if( ba.type==4)
      {
          cout<<"Total Due money: 	"<<ba.money;
          cout<<"\nMoney to be paid:	 "<<ba.bal; 
          cout<<"\nDue date:	 "<<ba.da<<"/"<<ba.mo<<"/"<<ba.ye;    
      }
      else
      cout<<"Balane money:   "<<ba.money;
}
int loanunp(int d1,int m1,int y1,int d2,int m2,int y2) // TO CHECK WETHER DUE HAS BEEN PAID
{
   if(y2>y1)
      return 1;
   else if(m2>m1&&y1==y2)
	return 1;
   else if(d2>d1&&m1==m2)
	return 1;
   else
       return 0;
}
void dispall() // TO DISPLAY THE DETAILS OF ALL THE CUSTOMERS
{
     cout<<"\n*******************************************************************************"<<endl;
     cout<<"A/C NAME       A/C NO           TYPE            Age type                BALANCE"<<endl;
     cout<<"*******************************************************************************"<<endl;
     ifstream fin("bankmanage.dat",ios::binary);
     bank ba;
     if(fin)
     {
	    fin.read((char*)&ba,sizeof(ba));
	    while(!fin.eof())
	    {
		      cout<<ba.name;
		      if(strlen(ba.name)>7)
			    cout<<"\t";
		      else
			    cout<<"\t\t";
		      cout<<ba.number<<"\t\t";
		      if(ba.type==1)
			  cout<<"Savings\t\t";
		      else if(ba.type==2)
			   cout<<"Current\t\t";
		      else if(ba.type==3)
			       cout<<"Fixed deposit\t";
		      else if(ba.type==4)
			   cout<<"Loan\t\t";
		      if( ba.ag==1)
			   cout<<"Adult\t\t";
		      else if( ba.ag==2)
			   cout<<"Senior citizen\t";
		      else
			  cout<<"Nill\t\t";
		      cout<<"\t"<<ba.money<<endl;
		      fin.read((char*)&ba,sizeof(ba));
	      }
	      cout<<endl<<endl<<endl;
	      fin.close();
	      ifstream fin("bankmanage.dat",ios::binary);
	      cout<<"LIST OF CUSTOMERS WHO HAS NOT PAID DUE MONEY\n\n";
	       cout<<"*******************************************************************************"<<endl;
	       cout<<"A/C NAME\tA/C NO\tBALANCE\t ADDRESS"<<endl;
	       cout<<"*******************************************************************************"<<endl;
	       fin.read((char*)&ba,sizeof(ba));
	      while(!fin.eof())
	      {
             if(ba.type==4&&loanunp(ba.da,ba.mo,ba.ye,now->tm_mday,now->tm_mon+1,now->tm_year+1900)==1)
		     {
                 cout<<ba.name;
		         if(strlen(ba.name)>7)
			         cout<<"\t";
                 else
			         cout<<"\t\t";
                 cout<<ba.number<<"\t"<<ba.bal<<"\t "<<ba.address<<"\n";
            }
            fin.read((char*)&ba,sizeof(ba));
	      }
    }
}
void passen(int acc,char pa[],int ac,double with,double dep,double tot)
// TO ADD DETAILS TO THE PASSBOOK
{
     bank ba;
     retcust(ba,acc);
     int &x=ba.top;
     ba.entry[x].dat = now->tm_mday;
     ba.entry[x].mont= now->tm_mon+1;
     ba.entry[x].yea = now->tm_year+1900;
     strcpy(ba.entry[x].part,pa);
     ba.entry[x].acn = ac;
     ba.entry[x].wmon= with;
     ba.entry[x].dmon= dep;
     ba.entry[x].tot = tot;
     x++;
     writef(ba,acc);
}
void create(bank b,int x=0) // TO CREATE AN ACCOUNT
{
         ofstream fout("bankmanage.dat",ios::app|ios::binary);
	 fout.write((char*)&b,sizeof(b));
         cout<<"Account created!!!"<<endl;
         fout.close();
	 if(!x)
             passen(b.number,"A/C CREATED",0,0,b.money,b.money);
         else
             passen(b.number,"Loan Taken",0,b.loan,0,b.money);
}
void del(int acc) // TO DELETE AN ACCOUNT
{
         bank bak;
         retcust(bak,acc);
         bank ba;
         ifstream fin("bankmanage.dat",ios::binary);
         ofstream fout("temp.dat",ios::binary);
         fin.read((char*)&ba,sizeof(ba));
	 while(!fin.eof())
         {
               if( ba.number!=bak.number)
                     fout.write((char*)&ba,sizeof(ba));
	       else
                   cout<<"\nAccount Deleted!!";
	       fin.read((char*)&ba,sizeof(ba));
	 }
	 fout.close();
	 fin.close();
	 remove("bankmanage.dat");
	 rename("temp.dat","bankmanage.dat");
}
void withdraw(int acc) // TO WITHDRAW MONEY FROM AN ACCOUNT
{
     double amm;
     bank ba;
     retcust(ba,acc);
     if(ba.type!=4)
     {
	 if( ba.type==3)
	 {
	     ba.money=0;
	     cout<<"Balance money Rs "<<ba.money<<" withdrawn"<<endl;
	     cout<<"Fixed  deposit account closed";
	     del(acc);
	 }
	 else
	 {
	     cout<<"Enter amount to be withdrawn:";
	     cin>>amm;
	     if( ba.money>=amm && amm>0)
	     {
			 ba.money-=amm;
			 writef(ba,acc);
			 cout<<"Money withdrawn!!! Your account balance is "<<ba.money<<endl;
			 passen(ba.number,"WITHDRAWN",0,amm,0,ba.money);
	     }
	     else
		 cout<<"\aMoney Not Withdrawn!!!"<<endl;
	 }
     }
     else
	 cout<<"You cannot withdraw money";
}
void deposit(int acc)  // TO DEPOSIT MONEY INTO AN ACCOUNT
{
     double amm;

     bank ba;
     retcust(ba,acc);
     if(ba.type!=4)
     {
         cout<<"Enter amount to be deposited:";
         cin>>amm;
         if(amm>0)
         {
                ba.money+=amm;
                writef(ba,acc);
                cout<<"Money deposited!!! \nYour account balance is "<<ba.money<<endl;
				passen(ba.number,"DEPOSITED",0,0,amm,ba.money);
	 	}
         else
             cout<<"\aMoney not Deposited!!"<<endl;
     }
     else
     {
         do
         {
             cout<<"Enter amount to be deposited:";
             cin>>amm;
             if(amm<=ba.bal)
                cout<<"You should pay Rs"<<ba.bal<<"\n";
         }while(amm<=ba.bal);
	 ba.money-=ba.bal;
         cout<<"Money deposited!!! Your Loan balance is "<<ba.money<<endl;
         if(ba.money==0)
         {
             del(acc);
             cout<<"Loan Ammount over. Account deletd!!";
	 }
         else
         {
             next(ba.da,ba.mo,ba.ye);  
             cout<<"Deposit "<<ba.bal<<"Rs before "<<ba.da<<"/"<<ba.mo<<"/"<<ba.ye;  
         }
         writef(ba,acc);  
	 passen(ba.number,"DEPOSITED",0,0,amm,ba.money);
     }   
}
void accset(int acc) // TO MODIFY THE DETAILS OF AN EXISTING CUSTOMER
{
        int z;
	    bank ba;
        retcust(ba,acc);
	    disp1(acc);
	    cout<<endl<<endl;
	    cout<<"1 - Account Name"<<endl;
	    cout<<"2 - Password"<<endl;
	    cout<<"3 - Type"<<endl;
	    cout<<"4 - Age type"<<endl;
	    cout<<"5 - Phone number"<<endl;
	    cout<<"6 - Address"<<endl;
	    cout<<"Enter detail to be changed"<<endl;
	    cout<<"Enter 7 to go back"<<endl;
	    cin>>z;
	    cin.get();
	    if(z==1)
	    {
			cout<<"Enter your new account name :";
			cin.getline(ba.name,N);
			cout<<"Account name changed!!"<<endl;
	    }
	    else if(z==2)
	    {
		     cout<<"Enter your new account Password :";
		     char c=' ';
		     int i=0;
		     while(c!=13)
	     {
		  c=getch();
		  if(c!=13&&c!=8)
		  {
		      ba.pass[i]=c;
		      cout<<"*";
		      i++;
		  }
		  else if(c==8&&i>0)
		  {
		      cout<<'\b';
		      i--;
		  }
	     }
	     ba.pass[i]=0;
		     cout<<endl;
		     cout<<"Account password changed!!"<<endl;
	    }
	    else if(z==3&&ba.type!=4)
	    {
		     do
		     {
			 cout<<"Enter your new account Type 1-Savings 2-Current 3-Fixed deposit :";
			 cin>>ba.type;
	      }while(ba.type==1&&ba.type==2&&ba.type!=3);
	      if(ba.type==3)
	      {
		      cout<<"Enter the number of years";
		      cin>>ba.fy;
	      }
		      cout<<"Account Type changed!!"<<endl;
	    }
	    else if(z==4)
	    {
		    if(ba.ag!=0)
			{
				do
				{
				      cout<<"Enter your age type 1-Adult 2-Senior citizen :";
				      cin>>ba.ag;
			 	}while(ba.ag!=1 && ba.ag!=2);
				 if(ba.ag==1)
				 {
				 	if(ba.type==4)
				       ba.inte=1;
					else
				     ba.inte=0.75;
			 	}
				else
			    {
			    	if(ba.type==4)
				       ba.inte=0.75;
					else
				     ba.inte=1;
				}				
		    cout<<"Account age type changed!!"<<endl;
		    cin.get();
	     }
         else
              cout<<"\aAccount age type cannot be changed";
     }
	 else if( z==5)
	 {
	     cout<<"Enter your Phone Number :";
	     cin.getline(ba.ph,15);
	     cout<<"Phone Number changed!!!\n";
	 }
	 else if( z==6)
	 {
	      cout<<"Enter your Address :";
	      cin.getline(ba.address,50);
	      cout<<"Account address changed!!!\n";
	 }
         else if(z!=7)
             cout<<"Invalid Number\a";
         if(ba.type==4&&z==3)
	       cout<<"\aType cannot be changed";
         writef(ba,acc);
}
void interest(int acc) // TO CALCULATE THE INTEREST AMOUNT
{
     bank ba;
     retcust( ba,acc);
     if(ba.type!=4&&ba.type!=3)
     {
         double &d=ba.days;
         double mon;
         double inter;
         if(d>=30)
         {
    	  mon=d/30;
    	  d=int(d)%30;
          inter=mon*(ba.inte)*ba.money/100;
	  ba.money+=inter;
          writef(ba,acc);
          passen(ba.number,"INTEREST",0,0,inter,ba.money);
         }
     }
}
void dispass(int acc) // TO VIEW THE PASSBOOK ENTRIES
{
     bank ba;
     retcust(ba,acc);
     interest(acc);
     cout<<"*******************************************************************************"<<endl;
     cout<<"DATE         PARTICULARS     AC/NO       WITHDRAW       DEPOSIT     BALANCE   *"<<endl;
     cout<<"*******************************************************************************"<<endl;
     for(int i=0;i<ba.top;i++)
     {
             if(ba.entry[i].dat<10)
		cout<<"0";
	     cout<<ba.entry[i].dat<<"/";
	     if(ba.entry[i].mont<10)
		      cout<<"0";
	    cout<<ba.entry[i].mont<<"/"<<ba.entry[i].yea<<"   ";
            if( strcmp(ba.entry[i].part,"A/C CREATED")==0)
                cout<<ba.entry[i].part<<"      ";
	    else
                cout<<ba.entry[i].part<<"\t      ";
            if( ba.entry[i].acn!=0)
                cout<<ba.entry[i].acn<<"\t ";
            else
                cout<<"NILL\t ";
            if( ba.entry[i].wmon!=0)
                cout<<ba.entry[i].wmon<<"\t\t";
            else 
                 cout<<"NILL\t\t";
            if( ba.entry[i].dmon!=0)
                cout<<ba.entry[i].dmon<<"\t    ";
            else 
                 cout<<"NILL\t    ";
            cout<<ba.entry[i].tot<<endl;
     }
}
void trans(int acc) // TO TRANSFER MONEY 
{
     int am,c,amt;
     bank ba;
     retcust( ba,acc);
     if(ba.type!=4)
     {
         cout<<"Enter the account number where money is to be transfored: ";
         cin>>am;
         bank to;
         retcust(to,am);  
         int nu=check(am);   
         if(am!=acc)
         {
              if(nu)
    	      {
                   do
                   {
                         cout<<"Enter money to be transfored: ";
                         cin>>amt;
                   }while(amt<=0);
                   if(ba.money>=amt)
                   {
		       cout<<"Confirm-1 Cancel-2. Enter 1 or 2: ";
                       cin>>c;
                       if(c==1)
                       {
                              ba.money-=amt;   
                              to.money+=amt;
                              cout<<"MONEY TRANSFERED!!!"<<endl;
                              writef(ba,acc);
                              passen(ba.number,"TRANSFERED",am,amt,0,ba.money);
                              writef(to,am);
                              passen(to.number,"TRANSFERED",am,0,amt,to.money);
                       }
                   }
                   else
                       cout<<"\aNot Enough Balance"<<endl;
             }
             else
                cout<<"\aInvalid account number"<<endl;
         }
         else
	     cout<<"\aMoney cannot be transfored to your own account";
     }
     else
         cout<<"\aYou cannot transfer money";
}
int free() // TO GET AN ACCOUNT NUMBER
{
     ifstream fin("bankmanage.dat",ios::binary);
     bank b;
     int i;
     if(fin)
     {
            fin.read((char*)&b,sizeof(b));
	    if(!fin.eof())
		i=0;
	    while(!fin.eof())
            {
                 i=b.number;
                 fin.read((char*)&b,sizeof(b));
            }
            fin.close();
            if(i!=0)
	       return i-999;
            else
                return 0;
     }
     else 
          return 0;
}
int noday(time_t t1,time_t t2) // TO CALCULATE THE PERIOD
{
    int dar;
    dar=(t1-t2)/(3600*24);
    return dar;
}
int main()
{
    bank newcust;
    int A=1;
    char c,no;
    int numb,month,y;
    char nam[N],ph[N],k[N];
    cout<<"";
    do
    {
        char pas[5]="\0";
	    system("cls");
	    cout<<endl<<"\a\t\t\t\tBANK MANAGEMENT SYSTEM";
	    cout<<endl<<"\t\t\t\t______________________"<<endl<<endl<<endl;
	    cout<<"\t1 - Create a new account"<<endl;
	    cout<<"\t2 - Withdraw money"<<endl;
	    cout<<"\t3 - Deposit money"<<endl;
	    cout<<"\t4 - Account settings"<<endl;
	    cout<<"\t5 - Delete account"<<endl;
	    cout<<"\t6 - Money transfer"<<endl;
	    cout<<"\t7 - View your account details"<<endl;
	    cout<<"\t8 - View all account details"<<endl;
	    cout<<"\t9 - Pass Book Entery"<<endl;
	    cout<<"\t10- Apply for Loan"<<endl;
	    cout<<"\t11- Forgot Password"<<endl;
	    cout<<"\t12- Exit"<<endl<<endl<<endl;
        cout<<"\tEnter a number from 1 to 11 :";
        cin>>A;
        if(A==1)
		{
		        system("cls");
                cout<<"CREATE NEW ACCOUNT"<<endl;
		        newcust.newaccount(free());
                int i=0;
                cout<<"\nConfirm-1 Cancel-2:";
                cin>>i;
                if(i==1)
                     create(newcust);
                else
                    cout<<"\aAccount not created!!";
        }
        else if(A==2)
        {
             bank b;
	         system("cls");
	         cout<<"WITHDRAWAL"<<endl<<endl;
             cout<<"Enter your account number: ";
	         cin>>numb;
	         cout<<"Enter your password:	   ";
		 char c=' ';
	         int i=0;
             while(c!=13)
             {
                  c=getch();
                  if(c!=13&&c!=8)
                  {
                      pas[i]=c;
                      cout<<"*";
                      i++;
                  }
                  else if(c==8&&i>0)
                  {
                      cout<<'\b';
                      i=i-1;
                  }
             }
             pas[i]=0;
             cout<<endl;
	         retcust(b,numb);
		 if(check(numb) && strcmp(b.pass,pas)==0)
	         {
		         if(b.type!=2)
		         {
                      time_t ti;
                      time(&ti);
                      b.days+=noday(ti,b.sec);
                      b.sec=ti;
                      writef(b,numb);
                 }
		         if(b.type!=3 ||b.type==3 && b.days>=b.fy) 
                 {
                     interest(numb);
		             disp1(numb);
		             cout<<endl<<endl;
		             if(b.type==3)
		             {
                        cout<<"1-Increase the number of years"<<endl;
		                cout<<"2-Continue "<<endl;
		                int co;
						do
                        {
                            cout<<"Press 1 or 2				:";
                            cin>>co;
                        }while(co!=1 && co!=2);
                        if(co==1)
                        {
                           cout<<"Enter the number of years		";
                           cin>>y;
                           b.fy=y;
                           writef(b,numb);
                        }
                     }
                     else
                         withdraw(numb);
                 }
                 else
                     cout<<"\aMoney cannot be withdrawn due to incompletion of years of fixed deposit."<<endl;
             }
             else
		 cout<<"\aInvalid account!!";
        }
        else if(A==3)
        {
	         system("cls");
	     cout<<"DEPOSIT"<<endl<<endl;
             cout<<"Enter your account number: ";
             cin>>numb;
             cout<<"Enter your password:	   ";
	         char c=' ';
	         int i=0;
             while(c!=13)
             {
                  c=getch();
                  if(c!=13&&c!=8)
                  {
                      pas[i]=c;
                      cout<<"*";
                      i++;
                  }
		  else if(c==8&&i>0)
                  {
                      cout<<'\b';
                      i=i-1;
                  }
	     }
             pas[i]=0;
             cout<<endl;
             bank b;
             retcust(b,numb);
	         if(check(numb))
	         {
                 if(b.type==3)
                     cout<<"\aMoney cannot be deposited in a fixed deposit account.";                    
                 else
                 {
                     if( strcmp(b.pass,pas)==0)
                     {
        	             if(b.type!=2)
        	             {
			     time_t ti;
                             time(&ti);
                             b.days+=noday(ti,b.sec);
                             b.sec=ti;
                             writef(b,numb);
			  }
        	             interest(numb);
        	             disp1(numb);
        	             cout<<endl<<endl;
        	             deposit(numb);
                      }
                      else
        	              cout<<"\aInvalid account password!!";
                 }
              }
              else
                  cout<<"\aInvalid account!!";
          }
	      else if(A==4)
	      {
		   system("cls");
               cout<<"ACCOUNT SETTING"<<endl<<endl;
	           cout<<"Enter your account number:";
	           cin>>numb;
	           cout<<"Enter your password:      ";
		   bank b;
               retcust(b,numb);
               char c=' ';
               int i=0;
               while(c!=13)
               {
                  c=getch();
                  if(c!=13&&c!=8)
                  {
                      pas[i]=c;
                      cout<<"*";
                      i++;
                  }
                  else if(c==8&&i>0)
                  {
		      cout<<'\b';
                      i=i-1;
                  }
               }
               pas[i]=0;
	       		cout<<endl;
	           if( check(numb) && strcmp(b.pass,pas)==0)
	           {
		           if(b.type!=2)
		           {
                         time_t ti;
                         time(&ti);
                         b.days+=noday(ti,b.sec);
                         b.sec=ti;
                         writef(b,numb);
                   }
		           interest(numb);
		           accset(numb);
                 }
	             else
			     cout<<"\aInvalid account!!";
            }
	        else if(A==5)
	        {
	             system("cls");
		 cout<<"DELETE ACCOUNT\n\n";
	             cout<<"Enter your account number:";
	             cin>>numb;
	             cout<<"Enter your password:      ";
	             char c=' ';
	             int i=0;
                 while(c!=13)
                 {
                      c=getch();
                      if(c!=13&&c!=8)
                      {
                          pas[i]=c;
                          cout<<"*";
                          i++;
                      }
		      else if(c==8&&i>0)
                      {
                          cout<<'\b';
                          i=i-1;
                      }
		  }
                 pas[i]=0;
                 cout<<endl;
                 bank b;
	             retcust(b,numb);
	             if( check(numb)&& strcmp(b.pass,pas)==0&&b.type!=4)
	             {
		             if(b.type!=2)
		             {
                         time_t ti;
                         time(&ti);
                         b.days+=noday(ti,b.sec);
                         b.sec=ti;
                         writef(b,numb);
                     }
			     interest(numb);
	                 if( b.type!=3||b.type==3&&b.days>=b.fy)
		             {
                         disp1(numb);
		                 cout<<endl<<endl;
				 cout<<"Do You surely want to delete your account Y/N";
		                 cin>>c;
		                 if(c=='y'||c=='Y')
		                 {
                               cout<<"Balance money Rs "<<b.money<<" withdrawn";
                               del(numb);
                         }
                         else
                             cout<<"\aAccount not deleted!!!";
                     }
                     else
                         cout<<"\aAccount cannot be deleted due incompletion of finishing date!!!"; 
	             }
	             else
		             cout<<"\aInvalid account!!";
	     }
             else if(A==6)
             {
                  system("cls");
                  cout<<"MONEY TRANSFER\n\n";
		      cout<<"Enter your account number:";
	              cin>>numb;
	              cout<<"Enter your password:      ";
	              char c=' ';
	              int i=0;
                  while(c!=13)
                  {
                      c=getch();
                      if(c!=13&&c!=8)
                      {
                          pas[i]=c;
                          cout<<"*";
                          i++;
                      }
                      else if(c==8&&i>0)
		      {
                          cout<<'\b';
                          i=i-1;
                      }
                  }
		  pas[i]=0;
                  cout<<endl;
	              bank b;
	              retcust(b,numb);
	              if( check(numb) && strcmp(b.pass,pas)==0&&b.type!=4)
	              {
		              if(b.type!=2)
		              {
                         time_t ti;
                         time(&ti);
                         b.days+=noday(ti,b.sec);
                         b.sec=ti;
                      }
                      if(b.type!=3)
		              {
				  interest(numb);
		                  disp1(numb);
		                  cout<<endl<<endl;
		                  trans(numb);
		                  cout<<endl;
				  disp1(numb);
                      }
                      else
                          cout<<"\aMoney cannot be transfered from fixed deposit";
                  }
                  else
                      cout<<"\aInvalid account!!";
             }
	         else if(A==7)
	         {
	              system("cls");
                  cout<<"VIEW YOUR ACCOUNT\n\n";
	              cout<<"Enter your account number:";
	              cin>>numb;
	              cout<<"Enter your password:";
		      char c=' ';
	              int i=0;
                  while(c!=13)
                  {
                      c=getch();
		      if(c!=13&&c!=8)
                      {
                          pas[i]=c;
                          cout<<"*";
                          i++;
                      }
                      else if(c==8&&i>0)
                      {
                          cout<<'\b';
                          i=i-1;
                      }
                  }
                  pas[i]=0;
                  cout<<endl;
	              bank b;
		      retcust(b,numb);
	              if( check(numb) && strcmp(b.pass,pas)==0)
	              {
		              if(b.type!=2)
		              {
			 time_t ti;
                         time(&ti);
                         b.days+=noday(ti,b.sec);
                         b.sec=ti;
                         writef(b,numb);
                      }
		              interest(numb);
		              disp1(numb);
                  }
                  else
                     cout<<"\aInvalid account!!";
             }    
             else if(A==8)
             {
	              system("cls");
		  cout<<"Enter Bank Password:";
		  char c=' ';
		      int i=0;
		  while(c!=13)
		  {
		       c=getch();
		       if(c!=13&&c!=8)
		       {
			   pas[i]=c;
			   cout<<"*";
			   i++;
		       }
		       else if(c==8&&i>0)
		       {
			    cout<<'\b';
			    i=i-1;
		       }
		  }
		  pas[i]=0;
		  if(strcmp(pas,"111")==0)
		      dispall();
		  else
		      cout<<"\n\aWrong bank password"<<endl;
	     }
	     else if(A==9)
	     {
		  system("cls");
		  cout<<"PASSBOOK ENTRY\n\n";
		      cout<<"Enter your account number:";
	              cin>>numb;
	              cout<<"Enter your password:";
	              char c=' ';
	              int i=0;
                  while(c!=13)
                  {
                      c=getch();
                      if(c!=13&&c!=8)
                      {
                          pas[i]=c;
                          cout<<"*";
                          i++;
                      }
                      else if(c==8&&i>0)
                      {
                          cout<<'\b';
                          i=i-1;
                      }
                  }
                  pas[i]=0;
                  cout<<endl;
	              bank b;
	              retcust( b,numb);
	              if( check(numb) && strcmp(b.pass,pas)==0)
	              {
		              if(b.type!=2)
		              {
                         time_t ti;
                         time(&ti);
                         b.days+=noday(ti,b.sec);
                         b.sec=ti;
                      }
		              interest(numb);
		              dispass(numb);
		              writef(b,numb);
                  }
                  else
                     cout<<"\aInvalid account!!";
             } 
             else if(A==10)
             {
                system("cls");
                cout<<"LOAN\n\n";
                cout<<"CREATE ACCOUNT\n";
                newcust.newaccount(free(),1);
                int i=0;
                cout<<"\nConfirm-1 Cancel-2:";
                cin>>i;
                if(i==1)
                    create(newcust,1);
                else
                    cout<<"\aAccount not created!!";
             }
             else if(A==11)
             {
             	system("cls");
             	cout<<"FORGOT PASSWORD\n\n";
             	cout<<"Enter your account number: ";
             	cin>>numb;
             	cin.get();
             	cout<<"Enter your name:           ";
             	cin.getline(nam,N);
             	cout<<"Enter your phone number :  ";
             	cin>>ph;
		cout<<"Enter your keywords :	  ";
		cin>>k;
             	bank b;
	            retcust( b,numb);
	            if(check(numb)&&!strcmp(b.name,nam)&&!strcmp(b.ph,ph)&&!strcmp(b.key,k))
	            	cout<<"Your password is "<<b.pass;
	            else
	            	cout<<"Invalid account!!\a";
	            cin.get();
	            	
             }
             else if(A==12)
             {
	              system("cls");
	              cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
		  		  cout<<"\t\t\t\a\aDONE BY:-"<<endl<<endl;
                  cout<<"\t\t\t\tP.SRINATH"<<endl;
	    }
        else
            cout<<"\aEnter a valid number";
        cin.get();
        cin.get();   
	}while(A!=12);
    getch();
    return 0;
}
