#include <stdio.h>
#include <stdlib.h>

#define SIZE     100


/*** struct *****/
struct two_side
{
  int flag1;
  int l;
  int r;
};

struct slove_eq
{
  int ans_num;
  int ans_var;
};


/*******************/
/*** Prototypes ****/
/*******************/
void set_null(char[]);
void set_zero(int[]);
void reverse(char[]);

void two_side(char, char[], char[], struct two_side *);
void separate(char[],char[],char[]);
void separate2(char[],char[],char[]);
int  cal_number(char[]);
void variables_to_num(char[], char[]);
void slove_eq(int, int, int, int, struct slove_eq *);
void linear_1(struct two_side *, struct slove_eq *);


int main(void)
{
  char command[10];
  
  struct two_side buff1 = {0, 0, 0};
  struct slove_eq buff2 = {0, 0};
  
  
  
  printf("Enter (a) to slove Linear equation(1 variable):\n");fflush(stdout);
  printf("Enter (exit) to  Exit:\n");fflush(stdout);
  scanf("%s", command);
  while(strcmp(command, "exit") != 0)
    {
      if(strcmp(command, "a") == 0)
	{
	  linear_1(&buff1, &buff2);
	}
      printf("Enter (a) to slove Linear equation(1 variable):\n");fflush(stdout);
      printf("Enter (exit) to  Exit:\n");fflush(stdout);
      scanf("%s", command);
    }//end of while loop
  return 0;
}




/*******************/
/*** set to null ***/
/*******************/
void set_null(char temp[])
{
  int i = 0;

  for(i = 0; i < SIZE; i++)
    {
      temp[i] = '\0';
    }
}

/*******************/
/*** set to zero ***/
/*******************/
void set_zero(int temp[])
{
  int i = 0;

  for(i = 0; i < SIZE; i++)
    {
      temp[i] = 0;
    }
}

/**************************/
/*** reverse char array ***/
/**************************/
void reverse(char rev[])
{
  int i = 0;
  int x = 0;
 
  char temp[SIZE];



  set_null(temp);

  for(i = SIZE - 1; i > -1; i--)
    {
      if(rev[i] != '\0')
	{
	  temp[x] = rev[i]; 
	  x++;
	}    
    }
  
  i = 0;
  x = 0;
  for(i = 0; i < SIZE; i++)
    {
      rev[x] = temp[i];
      x++;
    }
}








/****************************************************/
/**************** 3x+2-8x=4x-0+2+x ******************/
/*                   /       \                      */
/* left_side:  3x+2-8x       right_side: 4x-0+2+x   */
/****************************************************/
void two_side(char ch, char left_side[], char right_side[], struct two_side * buff1)
{
  if(ch == ' ')
    {
      ch = '\0';
    }
  if(ch == '=')
    {
      buff1->flag1 = 1;
    }
  
  if(buff1->flag1 == 0)
    {
      left_side[buff1->l] = ch;
      buff1->l++;
    }
  else if(buff1->flag1 == 1)
    {
      if(ch == '=')
	{
	  ch = '\0';
	}
      right_side[buff1->r] = ch;
      buff1->r++;
    }
}









 /**************************************************/
 /********** LEFT_SIDE:   2x-3+4-0-3x **************/
 /*                       /      \                 */
 /******* left_num: -2+4-0     left_var: 2x-3x   ***/
 /**************************************************/

 /**************************************************/
 /*** LEFT_SIDE: separate number from variables ****/
 /************** store  backward *******************/
 /**************************************************/

void separate(char left_side[], char left_num[], char left_var[])
{

  int flag = 0;
  int i = 0;
  int ln = 0;
  int lv = 0;
  int b = 0;

  


   for(b = SIZE - 1; b > -1; b--)
    {
      if(left_side[b] != '\0')
	{
	  if(left_side[b] == 'x')
	    {
	      flag = 1;
	    }
	  if(flag == 0)
	    {
	      left_num[ln] = left_side[b];
	      ln++;
	    }
	  else if(flag == 1)
	    {
	      left_var[lv] = left_side[b];
	      lv++;
	      if(left_side[b] == '+' || left_side[b] == '-')
		{
		  flag = 0;
		}
	    }
	}
    }

  
 
  /*** straight array ***/
   reverse(left_num);
   reverse(left_var);
}

void separate2(char left_side[], char left_num[], char left_var[])
{

  int flag = 0;
  int i = 0;
  int ln = 0;
  int lv = 0;
  int b = 0;

  


   for(b = SIZE - 1; b > -1; b--)
    {
      if(left_side[b] != '\0')
	{
	  if(left_side[b] == 'x')
	    {
	      flag = 1;
	    }
	  if(flag == 0)
	    {
	      left_num[ln] = left_side[b];
	      ln++;
	    }
	  else if(flag == 1)
	    {
	      left_var[lv] = left_side[b];
	      lv++;
	      if(left_side[b] == '+' || left_side[b] == '-')
		{
		  flag = 0;
		}
	    }
	}
    }

  
 
  /*** straight array ***/
   reverse(left_num);
   reverse(left_var);
}






 /**********************************************/
 /************* LEFT_SIDE: cal NUMBER **********/
 /*********** left_num = 3+4-2 *****************/
/*********** l_cal_num = 5 ********************/
 /**********************************************/
int cal_number(char left_num[])
{
  int i = 0;
  int x = 0;
 
  int flag = 0;                   //plus or minus;

  char total[SIZE];  
  int  tot_num = 0;
 
  char second[SIZE];
  int sec_num = 0;
 
  char operater;



 
  set_null(total);
  set_null(second);  
  i=0;

  if(left_num[i] == '0' || left_num[i] == '\0')
    {
      return 0;
    }
  else if(left_num[i] == '+')
    {
      i++;
    }
  else if(left_num[i] == '-')
    {
      flag = 1;
      i++;
    }

  do
    {
      if(left_num[i] == '+' || left_num[i] == '-')
	{
	  break;
	}
      else
	{  
	  total[x] = left_num[i];
	  x++;
	  i++;
	}
    }while(left_num[i] != '\0');
  
  tot_num = atoi(total);

  if(flag == 1)                              //if 1st number if minus
    {
      
      tot_num = (tot_num - 2 * tot_num);
    }
 

  x = 0;
  while(left_num[i] != '\0')    
    {

      if(left_num[i] == '+' || left_num[i] == '-')
	{ 
	  operater = left_num[i];
	  i++;
	}
      x = 0;
      do
	{
	  if(left_num[i] == '+' || left_num[i] == '-')
	    {
	      break;
	    }
	  second[x] = left_num[i];
	  i++; x++;
	}
      while(left_num[i] != '\0');
  
      sec_num = atoi(second);

      if(operater == '+') { 
	tot_num = tot_num + sec_num; 
	sec_num = 0; 
      }
      if(operater == '-')
	{ 
	  tot_num = tot_num - sec_num;
	  sec_num = 0;
	}
    }
  return tot_num;
}








/*******************************/
/*********** x-2x-3x ***********/
/*********** 1-2-3  ************/
/*******************************/
void variables_to_num(char left_var[], char left_var_num[])
{
  int i = 0;
  int x = 0;
  
  int flag = 0;



  for(i = SIZE - 1; i > -1; i--) 
    {
      if(left_var[i] != '\0')
	{
	  if(left_var[i] == 'x') 
	    {
	      if(left_var[i-1] == '+' || left_var[i-1] == '-')
	      {
		left_var_num[x] = '1';
		i--;
		x++;  
	      }
	      else if(left_var[i-1] >= '0' && left_var[i-1] <= '9')
		{
		  flag = 1;
		  i--;
		}
	      else
		{
		  left_var_num[x] = '1';
		  i--;
		  x++;
		  break;
		}
	    }
	  
	  if(flag == 0)
	    {
	      left_var_num[x] = left_var[i];
	      x++;
	    }
	  else if(flag == 1)
	    {
	      left_var_num[x] = left_var[i];
	      x++;
	      if(left_var[i] == '+' || left_var[i] == '-')
		{
		  flag = 0;
		}
	    }
	}
    }//end of for loop 

  /*** reverse string ***/ 
  reverse(left_var_num);
}








/***********************/
/**** slove equation ***/
/***********************/
void slove_eq(int l_total_var, int l_total_num, int r_total_var, int r_total_num,
	      struct slove_eq *buff2)
{
  buff2->ans_var = 0;
  buff2->ans_num = 0;
 
  
  if(r_total_var <= 0)
    {
      r_total_var = (r_total_var - r_total_var) - r_total_var;
      buff2->ans_var = l_total_var + r_total_var;
    }
  else if(r_total_var > 0)
    {
     buff2->ans_var = l_total_var - r_total_var;
    }


  if(l_total_num <= 0)
    {
      l_total_num = (l_total_num - l_total_num) - l_total_num;
      buff2->ans_num = r_total_num  + l_total_num;
    }
  else if(l_total_num > 0)
    {
      buff2->ans_num = r_total_num - l_total_num;
    } 
}












void linear_1(struct two_side *buff1, struct slove_eq *buff2)
{
  char ch;

  char left_side[SIZE];
  char left_num[SIZE];
  char left_var[SIZE];
  char left_var_num[SIZE];
  int l_total_num = 0;
  int l_total_var = 0;
  
  char right_side[SIZE];
  char right_num[SIZE];
  char right_var[SIZE];
  char right_var_num[SIZE];
  int r_total_num = 0;
  int r_total_var = 0;
  int i = 0;
  
  buff1->l = 0;
  buff1->r = 0;
  buff1->flag1 = 0;
  
  set_null(left_side);
  set_null(left_num);
  set_null(left_var);
  set_null(left_var_num);
  
  set_null(right_side);
  set_null(right_num);
  set_null(right_var);
  set_null(right_var_num);




  //printf("Enter a Linear equation(1 variable): ");fflush(stdout);
  while((ch = getchar()) != '\n')
    {
      two_side(ch, left_side, right_side, buff1);
    }  
  // printf("%s ",left_side);fflush(stdout);

  /**** Left_side: Sparate numbers from variables ****/
  separate(left_side, left_num, left_var);
  
  /**** Left_side: calculator numbers ***/
  l_total_num = cal_number(left_num);
  
  /********Left_side: variables to number ***/
  variables_to_num(left_var, left_var_num);
  
  /**** Left_side: calculator variables ***/
  l_total_var = cal_number(left_var_num);
  
  
  
  /**** Right_side: Sparate numbers from variables ****/
  separate(right_side, right_num, right_var);
  
  /**** Right_side: calculator numbers ***/
  r_total_num = cal_number(right_num);
  
  /******* Right_side: variables to number ***/
  variables_to_num(right_var, right_var_num);
  
  /**** Right_side: calculator variables ***/
  r_total_var = cal_number(right_var_num);
  
  
  /*** Slove equation ***/
  slove_eq(l_total_var, l_total_num, r_total_var, r_total_num, buff2);
  
 
  if(buff2->ans_var == 0)
    {
      printf("- Error -\n\n"); fflush(stdout);
    }
  else
    {
      printf("x = %d/%d\n\n",buff2->ans_num, buff2->ans_var); fflush(stdout);
    }
}















	     
