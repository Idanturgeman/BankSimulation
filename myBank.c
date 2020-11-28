#ifndef FIELDS
#define FIELDS 2
#endif

#ifndef ACCOUNTS
#define ACCOUNTS 50
#endif

#ifndef FIRST_ACC
#define FIRST_ACC 901
#endif

#ifndef WRONG_INDX
#define WRONG_INDX -1
#endif

#ifndef OPEN
#define OPEN 1
#endif

#ifndef CLOSE
#define CLOSE 0
#endif

#ifndef ACC_STT
#define ACC_STT 0
#endif

#ifndef ACC_BLC
#define ACC_BLC 1
#endif

#include <stdbool.h>
#include <stdio.h>

double acc[FIELDS][ACCOUNTS] = {0};

// Removeing all non zero digits after 2 places from decimal point
double round2Digits(double x){
  x = (int)(x*100);
  return x/100.0;
}

// return the first empty place or -1 if no space
int findPlace(){
  for(int i = 0; i < ACCOUNTS; i++){
    if(acc[ACC_STT][i] == CLOSE)
      return i + FIRST_ACC;
  }
  return WRONG_INDX;
}

// true iff 'account' is in the allowd range (901-950) AND active
bool isActive(int account){
  account -= FIRST_ACC;
  return account >= 0 && account < ACCOUNTS && acc[ACC_STT][account] == OPEN;
}

// Helper for deposite() and withrawal(). return new balance or -1 not allowd
double dep_withr(int account, double amount){
  if(isActive(account) && acc[ACC_BLC][account-FIRST_ACC] + amount >= 0){
    account -= FIRST_ACC;
    acc[ACC_BLC][account] += amount;
    return acc[ACC_BLC][account];
  }
  return WRONG_INDX;
}
double deposite(int account, double amount){
  if(amount >= 0)
    return dep_withr(account, amount);
  return WRONG_INDX;
}

// open an account and return the account number or -1 if no space
int openAcc(double amount){

  int account = findPlace();
  if(account != WRONG_INDX){
    acc[ACC_STT][account - FIRST_ACC] = OPEN;
    double ans = deposite(account, amount);
    if(ans == WRONG_INDX){
      printf("I'm sorry. you can't deposite a negative ammpunt.\n");
    }
  }
  return account;
}

// return the current balance for the spesific account or -1 if account inactive
double getBalance(int account){
  if(isActive(account))
    return acc[ACC_BLC][account-FIRST_ACC];
  return WRONG_INDX;
}

// substract the spesific amount from the spesific  account (if there id enugh)
double withrawal(int account, double amount){
  if(amount >= 0)
    return dep_withr(account, -amount);
  return WRONG_INDX;
}

// set the balance to 0 and the status to close
bool closeAcc(int account){
  if(isActive(account)){
    account -= FIRST_ACC;
    acc[ACC_STT][account] = CLOSE;
    acc[ACC_BLC][account] = 0;
    return true;
  }
  return false;
}

// increas the balance of all accounts by 'inter' percent
void interest(double inter){
  double rate = (100 + inter)/100;
  for(int i = 0; i < ACCOUNTS; i++){
    if(acc[ACC_STT][i] == OPEN)
      acc[ACC_BLC][i] = round2Digits(acc[ACC_BLC][i]*rate);
  }
}
// print all active accounts - number and balance
void printAll(){
  for(int i = 0; i < ACCOUNTS; i++){
    if(acc[ACC_STT][i] == OPEN)
      printf("Account number: %d. Balance: %g\n", i + FIRST_ACC, acc[ACC_BLC][i]);
  }
}

// close all acounts
void closeAll(){
  for(int i = 0; i < ACCOUNTS; i++)
    closeAcc(i);
}
