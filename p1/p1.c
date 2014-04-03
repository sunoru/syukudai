#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 60
#define RIGHT 1
#define WRONG 0

#define PLUS '+'
#define MINUS '-'
#define MULTI '*'
#define DIV '/'
#define POW '^'
#define BOTTOM '$'
#define TOP '#'
#define SPACE ' '
#define VOID 0
#define SIN -1
#define COS -2

#ifndef DEBUG
#define DEBUG
#endif

char str_inf[MAXN];
char str_suf[MAXN];
int j = 0;
/* The node structure of the stack. */
struct node
{
    int data;
    double num;
    struct node *next;
} *top;

/* The function to create a new stack. */
struct node *
create ()
{
    struct node *top = (struct node *) malloc (sizeof (struct node));
    top->data = BOTTOM;
    top->next = NULL;

    return top;
}

void push(int data, double num)
{
    struct node *p = (struct node *) malloc (sizeof (struct node));
    p->data = data;
    p->num = num;
    p->next = top;
    top = p;
}

struct node *
pop()
{
    struct node *p = top;
    top = p->next;
    return p;
}

int pop_data()
{
    struct node *p = pop();
    int t = p->data;
    free(p);
    return t;
}

double pop_num()
{
    struct node *p = pop();
    double t = p->num;
    free(p);
    return t;
}

/* The function to create a reverse Polish notation. */
struct node *
change ()
{
    struct node *p;
    int i;
    int m;
    char a;

    m = strlen (str_inf);
    for (i = 0; i <= m; i++)
    {
        a = str_inf[i];
        if ('0' <= str_inf[i] && str_inf[i] <= '9' || str_inf[i] == '.' ||
            tolower(str_suf[i]) == 'e')
        {
	        str_suf[j] = str_inf[i];
            j++;
        }
        else
        {
	        switch (a)
	        {
	            case '(': 
	            {
                    push(a, 0);
        		    break;
	            }
	            case MULTI:
	            case DIV:
	                str_suf[j] = ' ';
	                j++;
	                if ((top->data == MULTI) || (top->data == DIV))
                    {
                        str_suf[j] = top->data;
                        j++;
                        top->data = a;
                        break;
                    }
	            else
                {
                    push(a, 0);
                    break;
                }
	        case PLUS:
	        case MINUS:
                {
	                str_suf[j] = ' ';
                    j++;
                    if (top->data == PLUS || top->data == MINUS || top->data == MULTI ||
                        top->data == DIV)
                    {
                        str_suf[j] = top->data;
                        j++;
                        top->data = a;
                        break;
                    }
                    else
                    {
                        push(a, 0);
                        break;
                    }
               }
            case POW:
                {
                    str_suf[j] = ' ';
                    j++;
                    if (top->data == PLUS || top->data == MINUS || top->data == MULTI ||
                        top->data == DIV || top->data == POW)
                    {
                        str_suf[j] = top->data;
                        j++;
                        top->data = a;
                        break;
                    }
                    else
                    {
                        push(a, 0);
                        break;
                    }
                }
	        case ')':
                {
                    str_suf[j] = SPACE;
                    j++;
                    while (top->data != '(')
                    {
                        str_suf[j] = top->data;
                        j++;
                        pop_num();
                    }
                    pop_num();
                    
                    break;
                }
            case 's':
                {
                    i += 2;
                    push(SIN, 0);
                    break;
                }
            case 'c':
                {
                    i += 2;
                    push(COS, 0);
                    break;
                }
            }
        }
    }
    while (top->data != BOTTOM)
    {
        str_suf[j] = top->data;
        j++;
        pop_num();
    }
    
#ifdef DEBUG
    printf("%s\n", str_suf);
#endif
    str_suf[j] = TOP;

}

void calculate ()
{
    struct node *p;
    char *q;
    double x, y, a;
    int i;

    for (i = 0; i <= j; i++)
    {
        if (str_suf[i] >= '0' && str_suf[i] <= '9')
        {
            q = &str_suf[i];
            a = atof (q);
            for (; str_suf[i] >= '0' && str_suf[i] <= '9' || str_suf[i] == '.' || 
                tolower(str_suf[i]) == 'e'; i++);
            push(VOID, a);
            i--;
        }
        else if (str_suf[i] == TOP)
            printf ("result: %lf\n", top->num);
        else
        {
            if (str_suf[i] == SPACE)
                continue;
            else
            {
                y = pop_num();
	            switch (str_suf[i])
                {
                    case PLUS:
                        {
                            x = pop_num();
                            a = x + y;
                            break;
                        }
                    case MINUS:
                        {
                            x = pop_num();
                            a = x - y;
                            break;
                        }
                    case MULTI:
                        {
                            x = pop_num();
                            a = x * y;
                            break;
                        }
                    case DIV:
                        {
                            x = pop_num();
                            a = x / y;
                            break;
                        }
                    case SIN:
                        {
                            a = sin(y);
                            break;
                        }
                    case COS:
                        {
                            a = cos(y);
                            break;
                        }
                    case POW:
                        {
                            x = pop_num();
                            a = pow(x, y);
                        }

                }
                push(VOID, a);
            }
        }
    }
}

void clear()
{ 
    while(top->data != BOTTOM)
        free(pop());
    j = 0;
}
int main ()
{
    top = create ();
    printf ("Input:\n");
    for(;;)
    {
        clear();
        gets (str_inf);
        if(str_inf == "Exit")
            break;
        change();
        calculate();
    }

    return 0;
}
