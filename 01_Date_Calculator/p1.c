/**************************** GOAL OF PROGRAM ***************************/
/* Compute and print the number of days that are strictly between two
   specified dates in the year 2011                                     */    
/************************************************************************/

/*********************** NOTE ***************************/
/* 1- Each date is specified by two integers            */
/* 2- First representing the month                      */
/* 3- Second representing the day                       */
/* 4- Ex- The integers 3 and 17 repesent March 17, 2011 */
/********************************************************/

/******************** EXAMPLES **************************
Example 1:               |   Example2:
Enter start date: 2 10   |   Enter start date : 2 29
Enter end date  : 3 7    |   Error: Invalid date
Answer = 24              |
--------------------------------------------------------
Example 3:
Enter start date: 5 15
Enter end date  : 4 9
Error: End date precedes start date
******************************************************/

#include <stdio.h>

int main(void)
{
  // variables to get data and to do calculation
  int month1, month2, day1, day2;
  int total = 0;
  int answer = 0;
  int i = 0;
  
  //array to store months and its days
  int array[11];
  array[0] = 31;
  array[1] = 28;
  array[2] = 31;
  array[3] = 30;
  array[4] = 31;
  array[5] = 30;
  array[6] = 31;
  array[7] = 31;
  array[8] = 30;
  array[9] = 31;
  array[10]= 30;
  array[11]=31;

  // enter 1st date
  printf("Enter start date: ");
  scanf("%d%d", &month1, &day1);
    month1--;

    // 2 tests for 1st date
    // 1st test to see is month 1 is between 1 to 12
  if(month1 < 0 || month1 > 11)
    {
      printf("Error - month 1-12\n");
    }
  // 2nd test to see if 1st day is between its month
  else if(day1 > array[month1] || day1 <= 0)
    {
      printf("Error - Invalid date.\n");
    }
  // if there are no error on date 1 than move to "else"
  else
    {
      // enter 2nd date
      printf("Enter end date: ");
      scanf("%d%d", &month2, &day2);
	month2--;
	
	// 3 tests
	// 1st test to see if 2nd month is between 1-12
      if(month2 < 0 || month2 > 11)
	{
	  printf("Error - month 1-12\n");
	}
      // 2nd test to see if 2nd day is between its month
      else if(day2 > array[month2] || day2 <= 0)
	{
	  printf("Error - Invalid date\n");
	}
      // 3rd test to see if 1st month is bigger than 2nd month
      else if(month1 > month2)
	{
	  printf("Error - end date precedes start date\n");
	}
      // if there are no error than more to "else"
      else
	{
	  // here is all the calculation between two dates is done
	  // test to make sure 2nd month is bigger
	  if(month1 <  month2)
	    {
	      // if 2nd month is bigger than take month's day minus 1st day
	      // than add 2nd day to it
	      total = array[month1] - day1;
	      total = total + day2;
	      
	      // for loop to add month's days between two dates
	      for(i = month1+1; i < month2; i++)
		{
		  answer = answer + array[i];
		}
	      answer = answer + total;
	      answer--;
	      printf("Answer = %d\n", answer);
	    }
	  // test to see if month1 is equal to month2
	  else if(month1 == month2)
	    {
	      //test to see if day1 is bigger
	      // find the between of same month
	      if(day1 < day2)
		{
	      answer = day2 - day1;
	      answer--;
	      printf("Answer = %d\n", answer);
		}
	      // is day1 is bigger than give error
	      else if(day1 > day2)
		{
		  printf("Error - day1 is bigger than day2\n");
		}
	      // if both days are equal than minus day2 and day1
	      else if(day1 == day2)
		{
		  answer = day2 - day1;
		  printf("Answer = %d\n", answer);
		}
	    }
	}
    }
 return 0;
}
