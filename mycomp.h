#include <string.h>
#include <ctype.h>
#include "complex.h"

#define MAX_LENGTH 80
#define DIVIDER ','
#define STOP_COMMAND "stop"
#define READ_COMP "read_comp"
#define PRINT_COMP "print_comp"
#define ADD_COMP "add_comp"
#define SUB_COMP "sub_comp"
#define MULT_COMP_REAL "mult_comp_real"
#define MULT_COMP_IMG "mult_comp_img"
#define MULT_COMP_COMP "mult_comp_comp"
#define ABS_COMP "abs_comp"

typedef struct
{
    char *op;
    char *params;
} Command;

typedef struct
{
    Complex *var;
    char *params;
} ComplexParams;

typedef struct
{
    double num;
    char *params;
} DoubleParams;

unsigned int isValidVariable(char v);
int isDoubleNumber(char* str);
unsigned int isDoubleComma(char *str);
char *removeSpaces(char *str);
char *trimString(char *str);

Command getop(char *str);
ComplexParams getComplexVar(char *str, unsigned int isLast);
DoubleParams getDoubleParams(char *str, unsigned int isLast);
Complex *getComplex(char var);
unsigned int handle_op(Command c);

void read_comp_op(char *str);
void print_comp_op(char *str);
void add_comp_op(char *str);
void sub_comp_op(char *str);
void mult_comp_real_op(char *str);
void mult_comp_img_op(char *str);
void mult_comp_comp_op(char *str);
void abs_comp_op(char *str);