#include "mycomp.h"

Complex a, b, c, d, e, f;

int main()
{
    char str[MAX_LENGTH];

    a = create_comp(0, 0);
    b = create_comp(0, 0);
    c = create_comp(0, 0);
    d = create_comp(0, 0);
    e = create_comp(0, 0);
    f = create_comp(0, 0);

    while (1)
    {
        printf("\nEnter a command:");
        if (fgets(str, MAX_LENGTH, stdin) != NULL)
        {
            Command cmd;
            cmd = getop(trimString(str));
            if (cmd.params != NULL && handle_op(cmd))
                break;
        }
        else
        {
            printf("End of input!!\n");
            break;
        }
    }

    return 0;
}

/*get the command from the user and separate it to operation and params*/
Command getop(char *str)
{
    Command p;
    int i;

    /*print current command*/
    printf("\n%s\n", str);
    p.op = NULL;
    p.params = NULL;

    for (i = 0; str[i] && str[i] != ' ' && str[i] != '\n' && str[i] != DIVIDER; i++)
        ;
    if (str[i] != DIVIDER)
    {
        char *op;
        op = malloc(MAX_LENGTH * sizeof(char));
        strcpy(op, str);
        op[i] = '\0';
        p.op = op;
        p.params = removeSpaces(str + i);
    }
    else
    {
        printf("Illegal comma\n");
    }
    return p;
}

/*return a reference to  an existing complex variable*/
Complex *getComplex(char var)
{
    switch (var)
    {
    case 65:
        return &a;
    case 66:
        return &b;
    case 67:
        return &c;
    case 68:
        return &d;
    case 69:
        return &e;
    default:
        return &f;
    }
}

/*get the first parameter and return it if it is a valid variable. and erase it from our current params string*/
ComplexParams getComplexVar(char *str, unsigned int isLast)
{
    ComplexParams cp;

    cp.var = NULL;
    cp.params = NULL;

    if (isValidVariable(str[0]))
    {
        if (isLast && str[1] != DIVIDER)
        {
            cp.params = "";
            cp.var = getComplex(str[0]);
        }
        else if (!isLast && str[1] == DIVIDER)
        {
            cp.params = str + 2;
            cp.var = getComplex(str[0]);
        }
        else if (!isLast)
        {
            if (str[1] != '\0')
                printf("Missing comma\n");
            else
                printf("Missing parameter\n");
        }
        else
        {
            printf("Extraneous text after end of command \n");
        }
    }
    else
    {
        if (str[0] == '\0')
        {
            printf("Missing parameter\n");
        }
        else
        {
            printf("Undefined complex variable\n");
        }
    }
    return cp;
}

/*get the first parameter and return it if it is a double. and erase it from our current params string*/
DoubleParams getDoubleParams(char *str, unsigned int isLast)
{
    DoubleParams dp;
    char *doubleStr;
    double number;
    int i;

    dp.num = 0;
    dp.params = NULL;

    for (i = 0; str[i] && str[i] != DIVIDER; i++)
        ;
    doubleStr = malloc((i + 1) * sizeof(char));
    strncpy(doubleStr, str, i);
    number = atof(doubleStr);
    if (isDoubleNumber(doubleStr))
    {
        if (isLast && str[i] != DIVIDER)
        {
            dp.params = "";
            dp.num = number;
        }
        else if (!isLast && str[i] == DIVIDER)
        {
            dp.params = str + i + 1;
            dp.num = number;
        }
        else if (!isLast)
        {
            if (str[i] != '\0')
                printf("Missing comma\n");
            else
                printf("Missing parameter\n");
        }
        else
        {
            printf("Extraneous text after end of command \n");
        }
    }
    else
    {
        if (str[0] == '\0')
        {
            printf("Missing parameter\n");
        }
        else
        {
            printf("Invalid parameter – not a number\n");
        }
    }
    free(doubleStr);

    return dp;
}

/*check the command and select the proper function to handle the params*/
unsigned int handle_op(Command c)
{
    int isExist;
    isExist = 0;
    if (c.params[0] == DIVIDER)
    {
        printf("Illegal comma\n");
    }
    else if (isDoubleComma(c.params))
    {
        printf("Multiple consecutive commas\n");
    }
    else if (!strcmp(c.op, READ_COMP))
    {
        read_comp_op(c.params);
    }
    else if (!strcmp(c.op, PRINT_COMP))
    {
        print_comp_op(c.params);
    }
    else if (!strcmp(c.op, ADD_COMP))
    {
        add_comp_op(c.params);
    }
    else if (!strcmp(c.op, SUB_COMP))
    {
        sub_comp_op(c.params);
    }
    else if (!strcmp(c.op, MULT_COMP_REAL))
    {
        mult_comp_real_op(c.params);
    }
    else if (!strcmp(c.op, MULT_COMP_IMG))
    {
        mult_comp_img_op(c.params);
    }
    else if (!strcmp(c.op, MULT_COMP_COMP))
    {
        mult_comp_comp_op(c.params);
    }
    else if (!strcmp(c.op, ABS_COMP))
    {
        abs_comp_op(c.params);
    }
    else if (!strcmp(c.op, STOP_COMMAND))
    {
        if (c.params[0] != '\0')
            printf("Extraneous text after end of command\n");
        else
            isExist = 1;
    }
    else
    {
        printf("Undefined command name\n");
    }
    free(c.op);
    return isExist;
}

/*handle read comp command*/
void read_comp_op(char *str)
{
    ComplexParams cp;
    DoubleParams dpReal;
    DoubleParams dpImg;
    cp = getComplexVar(str, 0);
    if (cp.params != NULL)
        dpReal = getDoubleParams(cp.params, 0);
    if (cp.params != NULL && dpReal.params != NULL)
        dpImg = getDoubleParams(dpReal.params, 1);

    if (cp.params != NULL && dpReal.params != NULL && dpImg.params != NULL)
    {
        *cp.var = create_comp(dpReal.num, dpImg.num);
    }
}

/*handle print comp command*/
void print_comp_op(char *str)
{
    ComplexParams cp;
    cp = getComplexVar(str, 1);
    if (cp.params != NULL)
    {
        print_comp(*cp.var);
    }
}

/*handle add two comp command*/
void add_comp_op(char *str)
{
    ComplexParams cp1;
    ComplexParams cp2;
    cp1 = getComplexVar(str, 0);
    if (cp1.params != NULL)
        cp2 = getComplexVar(cp1.params, 1);
    if (cp1.params != NULL && cp2.params != NULL)
    {
        print_comp(add_comp(*cp1.var, *cp2.var));
    }
}

/*handle sub two comp command*/
void sub_comp_op(char *str)
{
    ComplexParams cp1;
    ComplexParams cp2;
    cp1 = getComplexVar(str, 0);
    if (cp1.params != NULL)
        cp2 = getComplexVar(cp1.params, 1);
    if (cp1.params != NULL && cp2.params != NULL)
    {
        print_comp(sub_comp(*cp1.var, *cp2.var));
    }
}

/*handle multiply comp with real number command*/
void mult_comp_real_op(char *str)
{
    ComplexParams cp;
    DoubleParams dp;
    cp = getComplexVar(str, 0);
    if (cp.params != NULL)
        dp = getDoubleParams(cp.params, 1);
    if (cp.params != NULL && dp.params != NULL)
    {
        print_comp(mult_comp_real(dp.num, *cp.var));
    }
}

/*handle multiply comp with imaginary number command*/
void mult_comp_img_op(char *str)
{
    ComplexParams cp;
    DoubleParams dp;
    cp = getComplexVar(str, 0);
    if (cp.params != NULL)
        dp = getDoubleParams(cp.params, 1);
    if (cp.params != NULL && dp.params != NULL)
    {
        print_comp(mult_comp_img(dp.num, *cp.var));
    }
}

/*handle multiply two comp command*/
void mult_comp_comp_op(char *str)
{
    ComplexParams cp1;
    ComplexParams cp2;
    cp1 = getComplexVar(str, 0);
    if (cp1.params != NULL)
        cp2 = getComplexVar(cp1.params, 1);
    if (cp1.params != NULL && cp2.params != NULL)
    {
        print_comp(mult_comp_comp(*cp1.var, *cp2.var));
    }
}

/*handle abs comp command*/
void abs_comp_op(char *str)
{
    ComplexParams cp;
    cp = getComplexVar(str, 1);
    if (cp.params != NULL)
    {
        printf("%.2f\n", abs_comp(*cp.var));
    }
}

/*check if the char is one of the 6 variable options*/
unsigned int isValidVariable(char v)
{
    if (v >= 65 && v <= 70)
        return 1;
    return 0;
}

/*check for an occurrence of two dividers that are one next to the other*/
unsigned int isDoubleComma(char *str)
{
    int i;
    for (i = 0; str[i]; i++)
    {
        if (str[i] == DIVIDER && str[i + 1] == DIVIDER)
        {
            return 1;
        }
    }
    return 0;
}

/*remove whitespace from the string*/
char *removeSpaces(char *str)
{
    int i, j;
    for (i = 0, j = 0; str[i]; i++)
    {
        if (!isspace((unsigned char)str[i]))
        {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
    return str;
}

/*remove whitespace from both ends of a string*/
char *trimString(char *str)
{
    int start;
    int end;
    int i;
    int isStartSet;
    for (i = 0, start = 0, end = 0, isStartSet = 0; str[i]; i++)
    {
        if (!isspace((unsigned char)str[i]))
        {
            start = isStartSet ? start : i;
            isStartSet = 1;
            end = i + 1;
        }
        str[i - start] = str[i];
    }
    str[end - start] = '\0';
    return str;
}

/*check if the string is a valid number*/
int isDoubleNumber(char *str)
{
    int dotCount = 0;
    int digitCount = 0;
    int i = 0;

    /* Check for optional starting sign of (+/-)*/
    if (str[0] == '+' || str[0] == '-')
        str += 1;

    if (str[0] == '0' && (str[1] == '\0' || str[1] == '.'))
    {
        digitCount++;
        str += 1;
    }

    /* Check for digits before decimal point (if any)*/
    while (str[i] >= '0' && str[i] <= '9')
    {
        i++;
        digitCount++;
    }

    /* Check for decimal point (if any)*/
    if (str[i] == '.')
    {
        i++;
        dotCount++;

        /* Check for digits after decimal point*/
        while (str[i] >= '0' && str[i] <= '9')
        {
            i++;
            digitCount++;
        }
    }

    /* Check if the entire string was consumed and there was at least one digit*/
    if (str[i] == '\0' && digitCount > dotCount && dotCount <= 1)
        return 1;
    else
        return 0;
}
