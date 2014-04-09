/**************************** GOAL OF PROGRAM ***************************/
/* Given two decimal integers d and r, convert d into its repesentaion in
radix r and print the resulting representation */    
/************************************************************************/

/******************************* NOTE ************************************/
/* 1- The first integer(d) will be a non-negative decimal integer */
/* 2- The second integer(r) will be one of 2,3,4...15,16 */
/* 3- Use letter A, B, C, D, E and F to represent 10, 11, 12, 13, 14, 15
   repectively(as in hex) */
/**************************************************************************/

/************************* EXAMPLES *******************************
Example 1:                    |      Example2:
Enter two integers: 128 16    |      Enter two integers: 284 13
Answer = 8A                   |      Answer = 138B               
--------------------------------------------------------------------
Example 3:
Enter two integer: 68 2
Answer = 1000100                                                                  
*******************************************************************/




#include <stdio.h>

#define SIZE 200

int main(void)
{
  // Input variables
  int d , r;

  // Loops variables
  int i = 1;
  int x, w, p;

  // Cal variables
  int quo = 0;
  int rem = 0;
  char ch2[SIZE];

  
  // Put 0's in ch2 array
  for(x = 0; x < SIZE; x++)
    {
      ch2[x] = '0';
    }

  // Get user input:
  printf("Enter two integers: ");
  scanf("%d%d", &d, &r);

  // Make sure decimal is postive
  if(d < 0)
    {
      printf("Error 1 - choose postive number \n"); fflush(stdout);
    }
  //make use radix is betwee 2-16
  else if(r < 2 || r > 16)
    {
      printf("Error 2 - choose radix between 2-16 \n"); fflush(stdout);
    }
  else
    {
      //get 1st number for slot one in ch2 array
      quo = d / r;
      rem = d % r;
      
      //if its between 0-9 - take rem and add '0'(48)
         if(rem >= 0 && rem <= 9)
	{
	  ch2[0] = rem + '0';
	}
	 //if its between 10-15 - take rem and add '7'(55)
	 if(rem >= 10 && rem <= 15)
	 {
           ch2[0] = rem + ('A'-10);
         }


      // Loop if its quo is not = to 0 and SIZE is begger than i
      while(i < SIZE && quo != 0)
	{
	  rem = quo % r;
	  quo = quo / r;
	
	    //if its bwtween 0-9 - take rem and add '0'(48)
	    if (rem >= 0 && rem <= 9)
	    {
	     ch2[i] = '0' + rem;
	    }
	    //if its between 10-15 - take rem and add '7'(55)
	    if(rem >= 10 && rem <= 15)
	    {
	     ch2[i] = rem + ('A'-10);
	    }
	  ++i;
	} // End of while loop
      
    //print array backward
      printf("Answer = "); fflush(stdout);
    for(p = i - 1; p > -1; p--)
      {
        printf("%c", ch2[p]); fflush(stdout);
      }  
    printf("\n");
    } // end of else
}
