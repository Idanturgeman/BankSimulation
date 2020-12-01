

#ifndef ACCOUNTS
#define ACCOUNTS 50
#endif

#ifndef OPEN_ACCOUNT
#define OPEN_ACCOUNT 1
#endif

#ifndef CLOSE_ACCOUNT
#define CLOSE_ACCOUNT 0
#endif


#ifndef ACCOUNT_STATUS
#define ACCOUNT_STATUS 0
#endif


#ifndef ACCOUNT_BALANCE
#define ACCOUNT_BALANCE 1
#endif

#ifndef FIRST_ACCOUNT
#define FIRST_ACCOUNT 901
#endif


#ifndef WRONG_INDX
#define WRONG_INDX -1
#endif


#include <stdbool.h>
#include <stdio.h>
#include "myBank.h"



double acc[2][ACCOUNTS] = {0};


// Helper for deposite() and withrawal(). return new balance or -1 not allowd
double dep_withr(int account, double amount)
{
  if(isActive(account) && acc[ACCOUNT_BALANCE][account-FIRST_ACCOUNT] + amount >= 0)
{
    account -= FIRST_ACCOUNT;
    acc[ACCOUNT_BALANCE][account] += amount;
    return acc[ACCOUNT_BALANCE][account];
  }
  return WRONG_INDX;
}
double deposite(int account, double amount)
{
  if(amount >= 0)
  {
    return dep_withr(account, amount);
  }
 return WRONG_INDX;
}

// open an account and return the account number or -1 if no space
int openAcc(double amount)
{

  int account = findPlace();
  if(account != WRONG_INDX)
   {
    acc[ACCOUNT_STATUS][account - FIRST_ACCOUNT] = OPEN_ACCOUNT;
    double ans = deposite(account, amount);
    if(ans == WRONG_INDX)
    {
      printf("I'm sorry. you can't deposite a negative ammpunt.\n");
    }
  }
  return account;
}

// return the current balance for the spesific account or -1 if account inactive
double getBalance(int account)
  {
  if(isActive(account))
   {
    return acc[ACCOUNT_BALANCE][account-FIRST_ACCOUNT];
  }
 return WRONG_INDX;
}



// set the balance to 0 and the status to close
bool closeAcc(int account)
  {
  if(isActive(account))
   {
    account -= FIRST_ACCOUNT;
    acc[ACCOUNT_STATUS][account] = CLOSE_ACCOUNT;
    acc[ACCOUNT_BALANCE][account] = 0;
    return true;
  }
  return false;
}

// increas the balance of all accounts by 'inter' percent
void interest(double inter)
  {
  double rate = (100 + inter)/100;
  for(int i = 0; i < ACCOUNTS; i++)
    {
    if(acc[ACCOUNT_STATUS][i] == OPEN_ACCOUNT)
     {
      acc[ACCOUNT_BALANCE][i] = round2Digits(acc[ACCOUNT_BALANCE][i]*rate);
     }
  }
}
// print all active accounts - number and balance
void printAll()
{
  for(int i = 0; i < ACCOUNTS; i++)
    {
    if(acc[ACCOUNT_STATUS][i] == OPEN_ACCOUNT)
     {
      printf("Account number: %d. Balance: %g\n", i + FIRST_ACCOUNT, acc[ACCOUNT_BALANCE][i]);
     }
  }
}

// close all acounts
void closeAll()
{
  for(int i = 0; i < ACCOUNTS; i++)
    {
    closeAcc(i);
    }
}

// return the first empty place or -1 if no space
int findPlace(){
  for(int i = 0; i < ACCOUNTS; i++)
{
    if(acc[ACCOUNT_STATUS][i] == CLOSE_ACCOUNT)
     {
      return i + FIRST_ACCOUNT;
     }
  }
  return WRONG_INDX;
}

// Removeing all non zero digits after 2 places from decimal point
double round2Digits(double x)
{
  x = (int)(x*100);
  return x/100.0;
}

// true iff 'account' is in the allowd range (901-950) AND active
bool isActive(int account)
{
  account -= FIRST_ACCOUNT;
  return account >= 0 && account < ACCOUNTS && acc[ACCOUNT_STATUS][account] == OPEN_ACCOUNT;
}


// substract the spesific amount from the spesific  account (if there id enugh)
double withrawal(int account, double amount)
  {
  if(amount >= 0)
   {
    return dep_withr(account, -amount);
  }
  return WRONG_INDX;
}

