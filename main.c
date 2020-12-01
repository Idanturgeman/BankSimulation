#ifndef WRONG_INDX
#define WRONG_INDX -1
#endif

#include "myBank.h"

#include <stdio.h>

void printMenu()
{
  printf("\t-Help menu- \n\nO: Open new account \nB: Print balance \nD: Deposite  \nW: Withrawal \nC: Close account \n");
  printf("I: Add interest to all accounts \nP: Print all open accounts and balance \nE: Close all accounts and exit \nH: Help\n\n");

}

void putInt(int *x)
{ // make sure that user insert an int
  while(!scanf(" %d", x))
{
    getchar();
    printf("Pleas enter an integer number\n");
  }
}
void putDouble(double *x)
{ // make sure that user insert a double
  while(!scanf(" %lf", x))
{
      getchar();
      printf("Pleas enter a real number\n");
  }
}
 int main() 
{
  printf("Welcome to my online bank \nfor help in any time press H\n\n");
  bool exit = false;
  while (!exit) 
    {
    printMenu();
    printf("Transaction type?\n");
    char act;
    scanf(" %c", &act);
    switch (act) 
    {
      case 'O':
    {
        printf("Initial deposite?\n");
        double amount;
        putDouble(&amount);
        amount = round2Digits(amount);
        int ans = openAcc(amount);
        if(ans != WRONG_INDX)
         {
          printf("Your account number is %d and your balance is %g\n", ans, getBalance(ans));
         }
        else
        {
          printf("I'm sorry but we don't have a place for you. try later.\n");
        }
        break;
      }
      case 'B':
       {
	int account;      
        printf("Account number?\n");
        putInt(&account);
	if(!(isActive(account)))
       {
                        printf("%d account number does'nt exist\n",account);
                        break;
                        }

        double ans = getBalance(account);
        if(ans != WRONG_INDX)
         {
          printf("The balance for %d account is %g\n", account, ans);
        }
        else
         {
          printf("Account dosn't exist\n");
        }
         break;
      }
      case 'D':
       {
        int account;
        printf("Account number?\n");
        putInt(&account);
	if(!(isActive(account)))
        {
			printf("%d account number does'nt exist\n",account);
			break;
			}
        double amount;
        printf("Amount?\n");
        putDouble(&amount);
        amount = round2Digits(amount);
        double ans = deposite(account, amount);
        if(ans != WRONG_INDX)
         {
          printf("%g was deposite. the balance for %d account is %g\n", amount, account, ans);
        }
        else
        {
          printf("Account dosn't exist OR you entered a negativ amount\n");
        }
       break;
      }
      case 'W':
       {
        int account;
        printf("Account number?\n");
        putInt(&account);
	if(!(isActive(account)))
        {
                        printf("%d account number does'nt exist\n",account);
                        break;
                        }

        double amount;
        printf("Amount?\n");
        putDouble(&amount);
        amount = round2Digits(amount);
        double ans = withrawal(account, amount);
        if(ans != WRONG_INDX)
         {
          printf("%g was withrawaled. the balance for %d account is %g\n", amount, account, ans);
        }
        else
        {
          printf("Account dosn't exist OR you don'e have enough money OR you entered a negativ amount\n");
        }
        break;
      }
      case 'C':
       {
        int account;
        printf("Account number?\n");
        putInt(&account);
	if(!(isActive(account)))
        {
                        printf("%d account number does'nt exist\n",account);
                        break;
                        }

        bool ans = closeAcc(account);
        if(ans)
         {
          printf("Account %d is close succsesfuly\n", account);
        }
        else
        {
          printf("Wrong account number\n");
        }
       break;
      }
      case 'I':
       {
        double inter;
        printf("Interest rate?\n");
        putDouble(&inter);
        interest(inter);
        printf("Interest was add with rate of %g\n", inter);
        break;
      }
      case 'P':
      {
        printAll();
        break;
      }
      case 'E':{
      
        closeAll();
        exit = true;
        printf("The bank is close. Goodbye!");
        break;
      }
      case 'H':
      {
        printMenu();
        break;
      }
      default:
      {
        printf("'%c' is wrong input. try again (H for help).\n", act);
      }
    }
    printf("\n");
  }
}

