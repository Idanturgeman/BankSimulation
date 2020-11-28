#ifndef MYBANK_H
#define MYBANK_H

#include <stdbool.h>
double round2Digits(double);
int findPlace();
bool isActive(int);
double dep_withr(int, double);
int openAcc(double);
double getBalance(int);
double deposite(int, double);
double withrawal(int, double);
bool closeAcc(int);
void interest(double);
void printAll();
void closeAll();

#endif
