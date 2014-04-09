/*Ikhlas Ahmed
  Project # 2
  Email - ia787858@albany.edu
  Main method: this method will first check for four errors to make sure user enter
  vaild commands. Than it will read one char from input file and convert to binary,
  quarternary, octal, or hexadecimal depending on what the user enter. it is going 
  to read from what user enter for starting arg and it will end depending on ending
  arg. after that i will print 10 string per line until it reach the end.
 */



#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define COMMAND_ARG 5 //5 command
#define IN_FILE_ARG 1 //file arg
#define START_ARG   2 //start arg
#define END_ARG     3 //end arg
#define FLAG_ARG    4 //flag arg(-b -q -o -h)

#define NINE        9 //9 space binary pointer
#define TWO         2 //divide by 2 

#define FIVE        5  //space for quarternay pointer
#define FOUR        4  //divide by 4


#define EIGHT       8  //divide by 8

#define THREE       3  //space for hex pointer
#define SIXTEEN     16 //divide by 16
/* h_define.h */
/* h_prototypes.h*/


int mydigit(char[]);     //check if it is digit or not
char* binary(unsigned char);      //convert char to binary
char* quarternary(unsigned char); //covert char to quarternary
char* octal(unsigned char);       //covert char to octal
char* hexadecimal(unsigned char); //convert char to hexadecimal


//argc(how many command entered)
//argv(point to 1st char)
int main(int argc, char *argv[])
{ 
  int count = 0;       //count for printing 10 string per line
  int start = 0;       //store START_ARG in int
  int end = 0;         //store END_ARG in end
  int file_length = 0; //length of file
  
  FILE *finp;          //store name of input file
  
  unsigned char c;     //store value from reading
  char *error = NULL;  //strtod  



  /*** Error 1 --- Check for 5 command ***/
  if(argc == COMMAND_ARG)
    {
      /*** Error 2 --- Check if file is open or not ***/
      if((finp = fopen(argv[IN_FILE_ARG], "r")) == NULL)
	{
	  fprintf(stderr, "Could not open file %s.\n", argv[IN_FILE_ARG]);
	  exit(1);
	}
      /*** Error 3 ---- Check if user enter -b -q -o -h ***/
      if((strcmp(argv[FLAG_ARG], "-b") == 0) || (strcmp(argv[FLAG_ARG], "-q") == 0)
        || (strcmp(argv[FLAG_ARG], "-o") == 0) || (strcmp(argv[FLAG_ARG], "-h") == 0))
	{
	  /*** 4.1 --- Value of start is not an integer or it is a negative integer. ***/
	  if(mydigit(argv[START_ARG]) == 1)
	    {
	      //convert string to int
	      start = strtod(argv[START_ARG],&error);

	      /*** Get file length ***/
	      fseek(finp,0L,SEEK_END);   //set curse at end
	      file_length = ftell(finp); //store in file_length
	      rewind(finp);              //set curser at begining

	      /*** Error 4.2 --- Value of start is larger than the largest byte position in the file ***/
	      if(start < file_length)
		{
		  /*** Error 4.3 --- Value of end is not an integer or it is a neg. integer other than -1 ***/
		  if(mydigit(argv[END_ARG]) == 1)
		    {
		      //convert string to int
		      end = strtod(argv[END_ARG],&error); 
		      
		      //check if user enter -1
		      if(end == -1) 
			{
			  end = file_length; //store length of file in end
			  end--;             //minus 1
			}
		      //[4.4]---[value of end is larger than the largest byte poition in the file]
		      if(end < file_length)
			{
			  /*** [4.5]---[Value of start is larger than that of end] ***/
			  if(start <= end)
			    {
			      //compare if user enter -b
			      if(strcmp(argv[FLAG_ARG], "-b") == 0)
				{
				  fseek(finp, start, SEEK_SET);           //put curser at starting arg
				  printf("%d: ",start); fflush(stdout);   //print begining starting  arg
				  //loop through util start is greatr than or equal to end
				  while(start <= end)
				    {
				      //count: for print 10 string per line
				      if(count < 10)
					{
					  //read one char at a time from inputfile
					  if((fread(&c, 1, 1,finp)) != 0)
					    {  
					      printf("%3s ",binary(c)); fflush(stdout);    //covert char by using binary method and print it 
					      start++;   //increment start
					      count++;   //increment count
					    }
					  else  //break from loop if there are no char to read
					    {
					      break;     
					    }
					}
				      else
					{
					  printf("\n%d: ",start); fflush(stdout);  //if count reach 10 than go to next line and print start
					  count = 0;                               //set count to 0
					}
				    }
				  printf("\n"); fflush(stdout);                     //put enter at end
				}
			      //compare if user enter -q
			      else if(strcmp(argv[FLAG_ARG], "-q") == 0)
				{
				  fseek(finp, start, SEEK_SET);              //put curser at starting arg
				  printf("%d: ",start); fflush(stdout);         //print begining starting arg
				  //loop through util start is greater than or equal to end
				  while(start <= end)
				    {
				      //count for print 10 string per line
				      if(count < 10)
					{
					  //read one char at a time
					  if((fread(&c, 1, 1,finp)) != 0)
					    {  
					      printf("%3s ",quarternary(c)); fflush(stdout);    //covert to quarternary by using method and print the reult
					      start++;    //increment start by 1
					      count++;     //increment count by 1
					    }
					  else   //break from loop if there are no char to read
					    {
					      break;
					    }
					}
				      else
					{
					  printf("\n%d: ",start);fflush(stdout);   //if count reach 10 than go to next line and print start
					  count = 0;                                //set count to 0
					}
				    }
				  printf("\n"); fflush(stdout);                    //put enter at end
				}
			      //compare if user entr -o
			      else if(strcmp(argv[FLAG_ARG], "-o") == 0)
				{
				  fseek(finp, start, SEEK_SET);                  //put curser at starting arg
				  printf("%d: ",start); fflush(stdout);          //print begining starting arg
				  //loop though until start is greater than or equal to
				  while(start <= end)
				    {
				      //count: for printing 10 strin per line
				      if(count < 10)
					{
					  //read one char at a time
					  if((fread(&c, 1, 1,finp)) != 0)
					    {  
					      printf("%3s ",octal(c)); fflush(stdout);       //convert to octal by using method and print the reuslt
					      start++;         //increment start by 1
					      count++;             //increment count by 1
					    }
					  else      //break from loop if there are no char to read
					    {
					      break;
					    }
					}
				      else
					{
					  printf("\n%d: ",start);fflush(stdout);      //if count reach 10 than go to next line and print start
					  count = 0;                                  //set count to 0
					}
				    }
				  printf("\n"); fflush(stdout);                     //put ent4er at end
				}
			      //comaper if user enter -h
			      else if(strcmp(argv[FLAG_ARG], "-h") == 0)
				{
				  fseek(finp, start, SEEK_SET);              //set curser at starting arg
				  printf("%d: ",start); fflush(stdout);          //print begining starting arg
				  //loop though until start is greater than or equal to end
				  while(start <= end)
				    {
				      //count: for print 10 string per line
				      if(count < 10)
					{
					  //read one char at a time from input file
					  if((fread(&c, 1, 1,finp)) != 0)
					    {  
					      printf("%3s ",hexadecimal(c)); fflush(stdout);         //convert to hexadecimal by using method and print thhe result
					      start++;      //incrememnt start by 1
					      count++;      //increment count by 1
					    }
					  else
					    {
					      printf("\n"); fflush(stdout);    //break from loop if there are no char to read
					      break;                          //exit from loop
					    }
					}
				      else
					{
					  printf("\n%d: ",start); fflush(stdout);  //after 10 string put enter and start at next line
					  count = 0;                                //set count to 0
					}
				    }
				  printf("\n"); fflush(stdout);                    //put enter at end
				}
			    }//4.5
			  else
			    {
			      printf("Invalid range specified.\n"); fflush(stdout);  //print error
			    }
			}//4.4
		      else
			{
			  printf("Invalid rang specified.\n"); fflush(stdout);  //print error
			}
		    }//4.3
		  else
		    {
		      printf("Invalid range specified.\n"); fflush(stdout);  //print error
		    }
		}//4.2
	      else
		{
		  printf("Invalid range specified.\n"); fflush(stdout);   //print error
		}
	    }//4.1
	  else
	    {
	      printf("Invalid range specified.\n"); fflush(stdout);    //print error
	    }
	}//error 3
      else
	{
	  printf("Error 3 - flag specified is not one of -b, -q, -o, -h \n"); fflush(stdout);  //print error 
	}
      //close input file
      if(fclose(finp) == EOF)
	{
	  fprintf(stderr, "Error in colsing file %s.\n", argv[IN_FILE_ARG]);
	}
    }//error 1
  else
    {
      printf("Error 1 - Enter five commands\n"); fflush(stdout);  //print error
    }
  return 0;
}//end of main method













int mydigit(char c[])
{
  int i; //index 
  
  //get size of string by using strlen and loop throgh it
  for(i = 0; i < strlen(c); i++)
    {
      //if 1st char is + or - than do nothing
      if(i == 0 && (c[i] == '+' || c[i] == '-'))
	{
	  //do nothing
	}
      //if its a '0' to '9' than do nothing
      else if(c[i] >= '0' && c[i] <= '9')
	{
	  //do nothing
	}
      //else return 0 - not number
      else
	{
	  return 0;
	}
    }
  //if its a number than return 1
  return 1;
}






/*** Convert to binary ***/
/* takes a char and convert in to binarry, and it return a char pointer */
char* binary(unsigned char c)
{
  int quo = c;     //put char in int quo
  int rem = 0;     //set rem = 0
  char *x;         //pointer char x - it will put the result in x
  int i = 7;      //index = 7

  /*** create 9 spaces for x,  1 space for /0 ***/
  if((x = (char *) malloc(NINE * sizeof(char))) == NULL)
    {
      printf("Storage allocation failure.\n"); fflush(stdout);   //if fail give error 
      exit(1);                                                  //exit
    }

  //put all 0's in string
  strcpy(x, "00000000");
  
  //while quo dont equal to 0
  while(quo != 0)
    {
      rem = quo % TWO;    //% quo with 2 and put it in rem
      quo = quo / TWO;     // divide quo with 2 and put it in quo

      x[i] = '0' + rem;     //convert it in to char and put it in x[i]
      --i;                    //decrement by 1
    }
  return x;                     //return x which has the result
}







/*** Convert to quarternary ***/
/* takes a char and convert in to quarternary, and it return a char pointer */
char* quarternary(unsigned char c)
{
  int quo = c;             //put char in int quo                     
  int rem = 0;             //set rem to 0
  char *x;                //pointer - which will hold the result
  int i = 3;              //set i = 3

  /*** create 5 spaces for x ***/
  //if fail print and exit
  if((x = (char *) malloc(FIVE * sizeof(char))) == NULL)
    {
      printf("Storage allocation failure.\n"); fflush(stdout);
      exit(1);
    }

  //put 0's in x
   strcpy(x, "0000");

   //while quo dont equal to 0
  while(quo != 0)
    {
      rem = quo % FOUR;  //% quo by 4 and put it in rem
      quo = quo / FOUR;  //divide quo by 4 and put it in quo
      
      x[i] = '0' + rem;  //convert to char and put it in x[i]
      --i;               //decrement by 1
    }

  return x;                 //return x which hold the result
}






/*** Convert to octal ***/
/* takes a char and convert in to octal, and it return a char pointer */
char* octal(unsigned char c)
{
  int quo = c;              //put char in int quo
  int rem = 0;          //set rem to 0
  char *x;              //pointer which will hold the result
  int i = 2;           //index
 
  /*** create 4 spaces for x ***/
  //if fail print and exit
  if((x = (char *) malloc(FOUR * sizeof(char))) == NULL)
    {
      printf("Storage allocation failure.\n"); fflush(stdout);
      exit(1);
    }

  //set all 0's in x
  strcpy(x, "000");

  //while quo dont equal to 0
  while(quo != 0)
    {
      rem = quo % EIGHT; //% quo by 8 and put it in rem
      quo = quo / EIGHT; //divide quo by 8 and put it in quo
      
      x[i] = '0' + rem; //covert to char and put it in x[i]
      --i; //decirement by 1
    }

  return x;  //return x which hold the result
}






/*** Convert to hexadecimal ***/
/* takes a char and convert in to hexadecimal, and it return a char pointer */
char* hexadecimal(unsigned char c)
{
  int quo = c; //put char in int quo
  int rem = 0; //set rem = 0
  char *x;     //pointer which hold the result
  int i = 1;   //index
 
  /*** create 3 spaces for x ***/
  //if fail print and exit
  if((x = (char *) malloc(THREE * sizeof(char))) == NULL)
    {
      printf("Storage allocation failure.\n"); fflush(stdout);
      exit(1);
    }

  //put all 0's in x
  strcpy(x, "00");      
      
  //while quo dont equal to 0
  while(quo != 0)
    {
      rem = quo % SIXTEEN; //% quo by 16 and put it in rem
      quo = quo / SIXTEEN;  //divide quo by 16 and put it in quo
      
      //if rem is between 0-9
      if(rem >= 0 && rem <= 9)
	{
	  x[i] = '0' + rem;  //convert to char and put it in x[i]
	}
      //if rem is between 10 and 15
      if(rem >= 10 && rem <= 15)
	{
	  x[i] = rem + ('A' - 10);  //convert to A,B,C,D,E,F and put it in x[i]
	}
      --i;  //decment by 1
    }
  return x;  //return x which hold the result
}
