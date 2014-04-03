#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 60
#define RIGHT 1
#define WRONG 0

char string1[MAX];
char string2[MAX];
int j = 0;

/* The node structure of the stack. */
struct node
{
    int data;
    struct node *next;
};

/* The function to create a new stack. */
struct node *
create ()
{
    struct node *top;
    top = (struct node *) malloc (sizeof (struct node));
    top->data = '$';
    top->next = NULL;

    return top;
}

/* The function to create a reverse Polish notation. */
struct node *
change (struct node *s)
{
    struct node *p, *top;
    int i;
    int m;
    char a;

    top = s;
    m = strlen (string1);
    for (i = 0; i <= m; i++)
        {
            a = string1[i];
            if ('0' <= string1[i] && string1[i] <= '9')
	{
	    string2[j] = string1[i];
	    j++;
	}
            else
	{
	    switch (a)
	    {
	        case '(': 
	        {
		        p = (struct node *) malloc (sizeof (struct node));
		        p->data = a;
        		p->next = top;
		        top = p;
        		break;
	        }
	        case '*':
	        case '/':		//ŽË²Ù×÷Îª³Ë³ý 
	            string2[j] = ' ';
	            j++;		//¿ÕžñÊÇÎªÁËÇø·Öž÷žö²»Í¬µÄÊý         
	            if ((top->data == '*') || (top->data == '/'))	//Èç¹ûÉÏÒ»žö²Ù×÷Îª³Ë³ý£¬ÔòÉÏÒ»žö²Ù×÷³öÕ»£¬a ÈëÕ» 
		{
		    string2[j] = top->data;
		    j++;
		    top->data = a;
		    break;
		}
	            else		//·ñÔò aÈëÕ»    
		{
		    p = (struct node *) malloc (sizeof (struct node));
		    p->data = a;
		    p->next = top;
		    top = p;
		    break;
		}
	        case '+':
	        case '-':
	            {
		string2[j] = ' ';
		j++;
		if (top->data == '+' || top->data == '-' || top->data == '*' || top->data == '/')	//ÈôÉÏÒ»žö²Ù×÷ÎªŒÓŒõ³Ë³ý£¬ÔòÉÏÒ»žö²Ù×÷³öÕ»£¬a ÈëÕ» 
		    {
		        string2[j] = top->data;
		        j++;
		        top->data = a;
		        break;
		    }
		else
		    {
		        p = (struct node *) malloc (sizeof (struct node));	//·ñÔò aÈëÕ»         
		        p->data = a;
		        p->next = top;
		        top = p;
		        break;
		    }
	            }
	        case ')':		//ÓöµœÓÒÀšºÅ
	            {
		string2[j] = ' ';
		j++;
		while (top->data != '(')	//ÖŽÐÐ³öÕ»²Ù×÷£¬Ö±µœµ¯³öÕ»µÄÊÇ×óÀšºÅ
		    {
		        string2[j] = top->data;
		        j++;
		        p = top;
		        top = top->next;
		        free (p);
		    }
		p = top;
		top = top->next;
		free (p);	//×óÀšºÅ²»Êä³ö
		break;
	            }
	        }
	}
        }
    while (top->data != '$')	//×îÖÕœ«Õ»ÖÐµÄÔªËØÒÀŽÎ³öÕ»
        {
            string2[j] = top->data;
            j++;
            p = top;
            top = top->next;
            free (p);
        }
    printf ("%s\n", string2);
    string2[j] = '#';		//ÒÔ#Îªstring2œáÊø±êÖŸ 

}



struct node *
calculate (struct node *s)
{
    struct node *top, *p;
    char *q;
    int x, y, a;
    int i;
    top = s;
    for (i = 0; i <= j; i++)
        {
            if (string2[i] >= '0' && string2[i] <= '9')
	{
	    q = &string2[i];
	    a = atoi (q);		//°Ñ×Ö·ûŽ®×ª»»³ÉÕûÐÍÊý£¬ŽÓÊý×Ö¿ªÊŒ×ª»»£¬Ö±µœµÚÒ»žö·ÇÊý×Ö×Ö·ûÍ£Ö¹ 
	    for (; string2[i] >= '0' && string2[i] <= '9'; i++);	//Ìø¹ýÊý×Ö×Ö·û    
	    p = (struct node *) malloc (sizeof (struct node));
	    p->num = a;
	    p->next = top;
	    top = p;
	    i--;
	}
            else if (string2[i] == '#')	//Óöµœ#Êä³öœá¹û 
	printf ("result:%d\n", top->num);
            else
	{
	    if (string2[i] == ' ')
	        continue;		//Ìø¹ý¿Õžñ 
	    else
	        {
	            y = top->num;
	            p = top;
	            top = top->next;
	            free (p);		//ÓöµœÔËËã·ûÈÃÇ°ÁœžöÊý×Ö³öÕ»         
	            x = top->num;
	            p = top;
	            top = top->next;
	            free (p);
	            switch (string2[i])
		{		//œøÐÐŒÓŒõ³Ë³ýÔËËã
		case '+':
		    {
		        a = x + y;
		        p = (struct node *) malloc (sizeof (struct node));
		        p->num = a;
		        p->next = top;
		        top = p;	//ËãÍêœ«œá¹ûÈëÕ»
		        break;
		    }
		case '-':
		    {
		        a = x - y;
		        p = (struct node *) malloc (sizeof (struct node));
		        p->num = a;
		        p->next = top;
		        top = p;
		        break;
		    }
		case '*':
		    {
		        a = x * y;
		        p = (struct node *) malloc (sizeof (struct node));
		        p->num = a;
		        p->next = top;
		        top = p;
		        break;
		    }
		case '/':
		    {
		        a = x / y;
		        p = (struct node *) malloc (sizeof (struct node));
		        p->num = a;
		        p->next = top;
		        top = p;
		        break;
		    }
		}
	        }
	}
        }
    return 0;
}

main ()
{
    struct node *top;

    top = create ();
    printf ("Input£º\n");
    gets (string1);
    calculate (change (top));
    getch ();
}
