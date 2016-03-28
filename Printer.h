#ifndef PRINTER_H_INCLUDED
#define PRINTER_H_INCLUDED
#include "mutex.h"
#pragma once

typedef struct  NumPrinter  NumPrinter;

void CONSTR(mutex_t * print_mut);
void DESTR();

NumPrinter* num_pr_new(int msg);
void printer_free( NumPrinter* p);

void printStart( NumPrinter* p);

#endif // PRINTER_H_INCLUDED
