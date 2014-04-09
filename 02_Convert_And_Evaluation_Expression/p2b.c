/**************************** GOAL OF PROGRAM ***************************/
/* Strict-left to-right evaluation of an arithmetic expression          */    
/************************************************************************/

/******************************* NOTE **************************************/
/* 1- Contains only single digit integer contants, operators (+, - , *, /) */
/* 2- Begins with an integer constant (without any peceding sign)          */
/* 3- integer contants and operators alternate                             */
/* 4- Each input expression is terminated by the newline \n character      */
/***************************************************************************/

/************************* EXAMPLES ***************************************
Example 1:                         |      Example2:
Enter expression: 7 +4 * 5 / 8 -9  |      Enter expression: 9*2 - 5/3 -9
Value = -5                         |      Value = -3                                                                               
**************************************************************************/

#include <stdio.h>

int main(void)
{
  char ch;
 
  char num1;
  int num2 = 0;
  int total = 0;

  char operater;

  // get 1st input and convert to int
  printf("Enter Expression: ");
  num1 = getchar();
       if((num1 >= '0' && num1 <= '9'))
	    {
	      total = (int)num1 - '0';
	    }
       // get rest of the input and do cal
  while((ch = getchar()) != '\n')
    {
      //get rid of spaces
      if(ch == ' ')
	{
	  ch = '\0';
	}
      //get + , - , *, / sign and store it to operaer
      if(ch == '+' || ch == '-' || ch == '*' || ch =='/')
	{
	  operater = ch;
	}
      //get next int and convert to int
       if((ch >= '0' && ch <= '9'))
        {
           num2 = (int)ch - '0';
	   //check sign and do cal
      if(operater == '+') { total = total + num2; num2=0;}
      if(operater == '-') { total = total - num2; num2=0;}
      if(operater == '*') { total = total * num2; num2=0;}
      if(operater == '/') { total = total / num2; num2=0;}
        }
    } // End of while loop
  
  printf("Value =  %d\n", total); fflush(stdout);
  
  return 0;
}
