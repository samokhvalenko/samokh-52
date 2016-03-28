#include <stdio.h>
#include "Printer.h"
#include "mutex.h"

int main(void){
NumPrinter *p1, *p2, *p3, *p4, *p5;
mutex_t * mut = mutex_new();
CONSTR(mut);

p1 = num_pr_new(1);
p2 = num_pr_new(2);
p3 = num_pr_new(3);
p4 = num_pr_new(4);
p5 = num_pr_new(5);

printStart(p1);
printStart(p2);
printStart(p3);
printStart(p4);
printStart(p5);

getchar();

printer_free(p1);
printer_free(p2);
printer_free(p3);
printer_free(p4);
printer_free(p5);

DESTR();
}
