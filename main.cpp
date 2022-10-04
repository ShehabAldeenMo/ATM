#include <iostream>
#include <cstring>
#include<limits>
using namespace std;

class ATM{
    private:
        char Account_name[100];     // 100 letter at max "no symbols or digits"
        char Card_number[19];        // the card num should be 10 digits exactly
        float Amount;                 //the amount of money in the account
    public:
        void create_new_acc();   // create a new account and the card number
        void Deposit();          // deposited amount of money + 1% of the deposited amount added
        void Withdrawal();       //withdraw money in account - 3% deduced from it
        void Transfer();         //transfers money from one to another + deducing 1.5% from both accounts
        void Print_acc_data( int account_index );   // prints the account name, card number, and amount of money
        int Search(char *numOfcard,int index);            // search with card number
            };
 // global ATM account to use in class code and if call main function not declare it again
 ATM Account[100];    // represent max number of accounts
 int iter=0 ;         // represent max number of accounts
 int account_iter_1; int account_iter_2;
void ATM::create_new_acc(){
    C_again:
    fflush(stdin);
   cout<<"please enter the account name: ";
   cin.getline(Account_name,100);
        for(int i=0;Account_name[i];i++) // wanted case : if symbols or digits (Ask again)
     // to test the input name
   /* (name[i]>=65&&name[i]<=90) for small characters
   *  (name[i]>=97&&name[i]<=122)for capital characters
   *  (name[i]==32) for spaces
   */
    if ( !( ( Account_name[i]>='A'&& Account_name[i]<='Z')||( Account_name[i]>='a'&& Account_name[i]<='z'||Account_name[i]==32 ) ) )
    {   cout<<"wrong entrie name\n";
    fflush(stdin);
        goto C_again;
    }
     int time=0;
   for(int i=0;Account_name[i];i++) //loop to count spaces in the name
{
    if(Account_name[i]==32)
        time++;
}
   if(strlen(Account_name)-time<3 ) //check if the name without spaces is less than 3
    {
         cout<<"error the name is too short\n ";
         goto C_again;
       }
 int n_spaces=0,n_char=0,sum=0;
 /* n_spaces,n_char to check the right flow of card number
    sum to check that the card num don't have one digit
 */
  numCard:
    n_spaces=0;n_char=0;sum=0;
   cout<<"Please enter the account number(10 numbers each separated by space): ";
   gets(Card_number);
   for(int i=0;Card_number[i];i++){
     if (Card_number[i]==32)//count spaces
       n_spaces++;
     if(Card_number[i]!=32)//count digits
       n_char++;
   }
   for(int i=0;i<19;i++){// to check that the card num don't have symbols or characters
    if ( !(Card_number[i]>=48&&Card_number[i]<=57||Card_number[i]==32) ){
     cout<<"wrong entrie card num\n";
     goto numCard ;
           }
     }
  for(int i=0;Card_number[i];i++)//to sum all of the digits
    if(Card_number[i]!=32)
       sum+=(Card_number[i]-48);
  if (sum==10*(Card_number[0]-48) ){
        cout<<"weak password\n";
        goto  numCard;
    }
    // to check the right flow of card number
   if ( !((n_spaces==10||n_spaces==9)&& n_char==10) ){
    cout<<"Need only one space between each number,need 10 numbers,Don't begin with space \n";
    goto numCard;
          }
    int check=Search(Card_number,iter-1); // to check that the card number not founded before
    if (check!=-1){
        cout<<"this card number founded before\n";
        goto numCard;
    }
     Amount=0;
    Print_acc_data(iter);//to display data
   return ;
}
void ATM::Deposit(){D_again:
    char _Card_number[19];
    // n_spaces,n_char to check the right flow of card number
   int n_spaces=0,n_char=0;
  _numCard:
    n_spaces=0;n_char=0;
   cout<<"Please enter the account number(10 numbers each separated by space): ";
   gets(_Card_number);
   for(int i=0;_Card_number[i];i++){
     if (_Card_number[i]==32)//count digits
       n_spaces++;
     if(_Card_number[i]!=32)//count spaces
       n_char++;
   }
   // to check that the card num don't have symbols or characters
   for(int i=0;i<19;i++){
    if ( !(_Card_number[i]>=48&&_Card_number[i]<=57||_Card_number[i]==32) ){
     cout<<"wrong entrie card num\n";
     goto _numCard ;
           }
     }
   if ( !((n_spaces==10||n_spaces==9)&& n_char==10) ){ // to check the right flow of card number
    cout<<"Need only one space between each number,need 10 numbers,Don't begin with space  \n";
    goto _numCard;
    }
    // to check that the card number is founded
    account_iter_1=Search(_Card_number,iter);
    if(account_iter_1==-1)
    {cout<<"card number not found\n";
    goto D_again;
    }
    TDA:
    cout<<"Please enter the amount to be deposited: ";
    float _Amount;
    cin>>_Amount;
    if((!cin)||(cin.peek()!='\n'))
             {
              cout<<"invalid letters and symbols\n";
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(), '\n');
      goto TDA;}
    if(_Amount<0)
        {cout<<"it has to be positive number\n";
    goto TDA;}
    Account[account_iter_1].Amount+=_Amount*(1.01);
     //to display data
    Print_acc_data(account_iter_1);
}
void ATM::Withdrawal(){
    char _Card_number[19];
   int n_spaces=0,n_char=0;
  W_again:
    n_spaces=0;n_char=0;
   cout<<"Please enter the account number(10 numbers each separated by space): ";
   gets(_Card_number);
   for(int i=0;_Card_number[i];i++){
     if (_Card_number[i]==32)//count spaces
       n_spaces++;
     if(_Card_number[i]!=32)//count digits
       n_char++;
   }
   for(int i=0;i<19;i++){ // to check that the card num don't have symbols or characters
    if ( !(_Card_number[i]>=48&&_Card_number[i]<=57||_Card_number[i]==32) ){
     cout<<"wrong entrie card num\n";
     goto W_again ;
           }
     }// to check the right flow of card number
   if ( !((n_spaces==10||n_spaces==9)&& n_char==10) ){
    cout<<"Need only one space between each number,need 10 numbers,Don't begin with space  \n";
    goto W_again;
    }    // to check that the card number founded before
    account_iter_1=Search(_Card_number,iter);
     if(account_iter_1==-1)
    {cout<<"card number not found\n";
    goto W_again;
    }
    W2_again:
        TWA:
        fflush(stdin);
        if(Account[account_iter_1].Amount==0)
        {
            cout<<"there is no money in this account\n  ";
            return;
        }
    cout<<"Please enter the amount to be withdrawn: ";
    float _Amount;
    cin>>_Amount;
      if((!cin)||(cin.peek()!='\n'))
             {
              cout<<"invalid letters and symbols\n";
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(), '\n');
      goto TWA;}
    if(_Amount<0)
        {cout<<"it has to be positive number\n";
    goto TWA;}
    Account[account_iter_1].Amount-=_Amount*(1.03);
    if( Account[account_iter_1].Amount<0)
    {Account[account_iter_1].Amount+=_Amount*(1.03);
        cout<<"error Rejected operation \n there is no enough money\n";
        goto W2_again;
    }
    Print_acc_data(account_iter_1);//to display data
}
void ATM::Transfer(){char _Card_number1[19];
TF :
 int n_spaces=0,n_char=0;
    n_spaces=0;n_char=0;
   cout<<"Please enter the sending account number(10 numbers each separated by space): ";
   gets(_Card_number1);
   for(int i=0;_Card_number1[i];i++){
     if (_Card_number1[i]==32)//count spaces
       n_spaces++;
     if(_Card_number1[i]!=32)//count digits
       n_char++;
   }// to check that the card num don't have symbols or characters
   for(int i=0;i<19;i++){
    if ( !(_Card_number1[i]>=48&&_Card_number1[i]<=57||_Card_number1[i]==32) ){
     cout<<"wrong entrie card num\n";
     goto TF ;
           }
     }// to check the right flow of card number
   if ( !((n_spaces==10||n_spaces==9)&& n_char==10) ){
    cout<<"Need only one space between each number,need 10 numbers,Don't begin with space  \n";
    goto TF;
    }
    account_iter_1=Search(_Card_number1,iter);
   if(account_iter_1==-1)  //if search function return -1 then the card number doesn't exist
    {cout<<"card number not found\n"; //error massage and enter the transfer function again
     goto TF;
    }
    if(Account[account_iter_1].Amount==0)
        {
            cout<<"there is no money in this account\n  ";
             goto TF;
        }
    TS:
        char _Card_number2[19];
    n_spaces=0;n_char=0;
   cout<<"Please enter the reseving account number(10 numbers each separated by space): ";
   gets(_Card_number2);
   for(int i=0;_Card_number2[i];i++){
     if (_Card_number2[i]==32)// to count spaces
       n_spaces++;
     if(_Card_number2[i]!=32)//to count digits
       n_char++;
   }// to check that the card num don't have symbols or characters
   for(int i=0;i<19;i++){
    if ( !(_Card_number2[i]>=48&&_Card_number2[i]<=57||_Card_number2[i]==32) ){
     cout<<"wrong entrie card num\n";
     goto TS ;
           }
     }// to check the right flow of card number
   if ( !((n_spaces==10||n_spaces==9)&& n_char==10) ){
    cout<<"Need only one space between each number,need 10 numbers,Don't begin with space  \n";
    goto TS;
    }// to check that the card number founded before
   account_iter_2=Search(_Card_number2,iter);
   if(account_iter_2==-1)  //if search function return -1 then the card number doesn't exist
    {cout<<"card number not found\n"; //error massage and enter the transfer function again
    goto TS;
    }
    //check that the  receiving account is not the sending account
    if(Search(_Card_number2,iter)==Search(_Card_number1,iter))
     {cout<<"error the receiving account canot be the sending account\n";
       goto TS;
     }
    TAM:
    fflush(stdin);
   cout<<"please enter the amount to be transferred: ";
    float _Amount;
    cin>>_Amount;
      if((!cin)||(cin.peek()!='\n'))
             {
              cout<<"invalid letters and symbols\n";
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(), '\n');
      goto TAM;}
    if(_Amount<0)
      {cout<<"it has to be positive number\n";
    goto TAM;}

    if(Account[account_iter_1].Amount-_Amount*(1.015)<0)  //check if there is enough money in the sending account
    {
        cout<<"error Rejected operation \n there is no enough money\n";
        goto TAM;
    }
    Account[account_iter_1].Amount-=_Amount*(1.015);
    Account[account_iter_2].Amount+=_Amount*(0.985);
    cout<<"sending account\n";
    Print_acc_data(account_iter_1);//to display data
    cout<<"receiving account\n";
   Print_acc_data(account_iter_2);//to display data
}
void ATM::Print_acc_data( int account_index ){
   cout<<"name: "<<Account[account_index].Account_name<<endl;
   cout<<"Card number: ";
   cout<<Account[account_index].Card_number;
   cout<<endl;
   cout<<"amount: "<<Account[account_index].Amount<<endl;
      return ;
}
int ATM::Search (char *numOfcard,int index){
  int time;// to count the equaled numbers
  int indexOfaccount=0;
  while(indexOfaccount<=index){
    time=0;
   for(int i=0;i<19;i++){
    if ( Account[indexOfaccount].Card_number[i]== *(numOfcard+i) )
        time++;
   }
   if (time==19){ return indexOfaccount;} // return the founded index
   indexOfaccount++;
  }
   return -1;// return -1 if is not founded
}
int main(){
char option[10];// enter wanted option
 int j=0;// to begin from first at every iteration
 bool f_char =0,ne_char=0;
 /* to check that 1st number between 1:5
    and their's next 2nd number or character
 */
 short flag1=0 ;// lift flag1 if user wanted to exit from code
 while(1){ask:
           fflush(stdin);
    f_char =0,ne_char=0;
/* cout the options for user */
   cout<< "1----Create new account\n";
   cout<<"2----Deposit\n";
   cout<< "3----transfer to another account\n";
   cout<<"4----withdrawal\n";
   cout<<"5----exit\n";
   cout<<"Please enter the number of operation: ";
   cin.getline(option,10);
   if (option[j]>=49&& option[j]<=53)//to check that 1st number between 1:5
      f_char=1;
   for (int i=1;option[i];i++)//their's no next number or character
       {if (option[i]!=32)
         ne_char=1;}
   if ( !(f_char&&!ne_char) ){
       cout<<"wrong option\n";
       j=0;// to begin from first at every iteration
   fflush(stdin);
       goto ask;
   }
   switch (option[j]) {
    case '1' : Account[iter].create_new_acc();
             iter++;
             break ;
    case '2' : Account[iter].Deposit();
             break;
    case '3' : Account[iter].Transfer();
             break ;
    case '4' : Account[iter].Withdrawal();
             break;
    case '5' : flag1=1;
             break;
    default :cout<<"wrong option\n";
  }
   if (flag1==1 || iter==100) break;
 }
  return 0;
}
