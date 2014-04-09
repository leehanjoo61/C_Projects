/* Ikhlas Ahmed
   Email = ia787858@albany.edu
   Main Method - this program will implement a relational database system that
supports simple retrieval querys. relational databse has data stored as relations
(table). the database may have relations. relation will have list of attributes and 
each row of tuple. the schema for each relation gives name, type, length of 
attribute. there will be 7 different command in queryfile. 1st is nattr relname,
2nd is tuplen relname, 3rd is infattr relname attrname, 4th is count relname,
5th is project relname attrname 6th is select relname attrname relop value,
last its exit.  
*/

  //includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
  //header files
#include "h_define.h"
#include "h_struct_def.h"
#include "h_globals.h"
#include "h_prototype.h"

 
//argc(how many command entered)
//argv(point to 1st char)
int main(int argc, char*argv[])
{
  
  int i = 0;        //index variable
  int j = 0;         //index variable
  int flag = 0;    //boolean flag
  int flag2 = 0;   //boolean flag

  char *tptr;   //pointer for token

  char q_line[L_SIZE];   //read from query_file.txt (size = 101)
  char cmd[S_SIZE];    //1st command(nattr,tuplen,infattr,count,project,select,exit)
  char schema_name[S_SIZE];  //2nd command (.sch)
  char data_name[S_SIZE];    //2nd command (.dat)
  char attrname[S_SIZE];    //3rd command  (name of attribute)
  char relop[N_SIZE];       //4th command (==, <= ,>= ,> ,<)
  char value[S_SIZE];       //5th command (number)

  char line2[L_SIZE];     //read from file
  char data_file[L_SIZE];  //name of data file
  int len_t = 0;           //length of each row
  int count_row = 0;        //number of row
  
  char line3[L_SIZE];      //read from file
  char *temp_line3;         //pointer to store value from line3
  char *build_array[L_SIZE]; //build array of pointers
  
  int flag_skip = 0;         //boolean flag
  int set = 0;              //store length 
  int l_num = 0;            //store left length
  int r_num = 0;            //store right length
  int row = 0;             //count row
  int c_a = 0;   //check attrname
  int c_t = 0;   //1 for string, 0 for int
  int count;            //counter
  int flag5 = 0;          //boolean flag
  char c;                 //char c for reading one char
  int test[L_SIZE];       //test

  FILE *finp1;  //configfile
  FILE *finp2;  //queryfile
  FILE *finp3;  //.sch file
  FILE *finp4;  //.dat file
  
 
  /* check to see if user enter 3 command */
  if(argc == COMMAND_ARG)
    {
      //open  CONFIGFILE
      if((finp1 = fopen(argv[CONFIGFILE], "r")) == NULL)
	{
	  fprintf(stderr, "Could not open file %s.\n", argv[CONFIGFILE]);
	  exit(1);
	}
      //Open QUERYFILE
      if((finp2 = fopen(argv[QUERYFILE],"r")) == NULL)
	{
	  fprintf(stderr, "Could not open file %s.\n", argv[QUERYFILE]);
	  exit(1);
	}
      
      

      /* Read one line at a time */
      while(fgets(q_line, L_SIZE, finp2) != NULL)
	{
	  //loop to erase the '\n' at end of q_line
	  for(i = 0; i < L_SIZE; i++)
	    {
	      if(q_line[i] == '\n')
		{
		  q_line[i] = '\0'; 
		}
	    }
	  
	  
	  tptr = strtok(q_line," "); //use token
	  if(tptr != NULL)           //test 
	    {
	      strcpy(cmd, tptr);      //store 1st value in cmd
	    }
	  
	  tptr = strtok(NULL," ");         //use token
	  if(tptr != NULL)                 //test
	    {
	      strcpy(schema_name, tptr);      //copy schema name
	      strcpy(data_name, tptr);        //copy data name
	      strcat(schema_name, ".sch");      //add .sch in end
	      strcat(data_name, ".dat");         //add .dat in end
	    }
	      
	  tptr = strtok(NULL," ");                //use token
	  if(tptr != NULL)                   //test
	    {
	      strcpy(attrname, tptr);          //store 3nd value in attrname
	    }
	  
	  tptr = strtok(NULL," ");            //token
	  if(tptr != NULL)               //test
	    {
	      strcpy(relop, tptr);       //store 4th value in relop
	    }
	  
	  tptr = strtok(NULL," ");        //token
	  if(tptr != NULL)          //test
	    {
	      strcpy(value, tptr);         //add 5th value in value
	    }
	  
	  /* quit command*/
	  if(strncmp(cmd, "quit", A_SIZE) == 0)
	    {  
	      break;                    //exit
	    }


	  /* open schema file */
	  flag = 0;
	  if((finp3 = fopen(schema_name, "r")) == NULL)
	    {
	      printf("Error: Invalid realation -- %s\n\n", schema_name);
	      fflush(stdout);
	      flag = T_SIZE;           
	    }
	  
	  
	  /* if flag 1 than skip all the commands*/
	  if(flag == 0)
	    {
	      //COMMAND: NATTR
	      if(strncmp(cmd, "nattr", F_SIZE) == 0)
		{
		  if((fgets(line2, L_SIZE, finp3) != NULL))  //read one line
		    {
		      printf("nattr: %s\n", line2);    //print 1st line
		      fflush(stdout);
		    }  
		}      
	      
	      //COMMAND: TUPLEN
	      else if(strncmp(cmd, "tuplen", Z_SIZE) == 0)  
		{
		  //keep on reading from file until it reach end
		  flag2 = 0;
		  while(fgets(line2, L_SIZE, finp3) != NULL)  //loop for reading
		    {  
		      //skip 1st time
		      if(flag2 == 0)
			{
			}
		      //else build linked list
		      else if(flag2 == T_SIZE)
			{
			  build_linked_list(line2);
			}
		      flag2 = T_SIZE;  //set flag2 back to 1
		    }  
		  //functch wich just print the result
		  print_tuplen();        
		  del_linked_list();         //del linked list
		}
	      

	      /* infattr command */
	      else if(strncmp(cmd, "infattr", Q_SIZE) == 0)
		{
		  flag2 = 0;
		  while(fgets(line2, L_SIZE, finp3) != NULL) //loop for reading
		    {  
		      if(flag2 == 0)          //skip 1st line
			{
			}
		      else if(flag2 == T_SIZE)       //build linked list
			{
			  build_linked_list(line2);
			}
		      flag2 = T_SIZE;             //set flag = 1
		    }  
		  print_infattr(attrname);       //print function 
		  del_linked_list();           //del linked list
		}



	      /* count command */
	      else if(strncmp(cmd, "count", F_SIZE) == 0)
		{
		  len_t = 0;         //set len to 0
		  count_row = 0;      //set row to o 
		  flag2 = 0;           //set flag = 0
		  
		  //open data file
		  if((finp4 = fopen(data_name, "r")) == NULL)
		    {
		      printf("Error: Invalid realation -- %s\n\n", data_name);
		      fflush(stdout);
		    }
		  //keep on reading until it goes to end
		  while(fgets(line2, L_SIZE, finp3) != NULL)
		    {  
		      //skip 1st time
		      if(flag2 == 0)
			{
			}
		      //build linked list
		      else if(flag2 == T_SIZE)
			{
			  build_linked_list(line2);
			}
		      flag2 = T_SIZE;     //set flag = 1
		    }  

		  len_t = len_tuple();      //get len of one line
		  
		  //reading from data file and use counter
		  while(fread(line2, len_t, 1, finp4)  != 0)
		    {
		      count_row++;            //endt row number
		    }
		  //print counter
		  printf("Count: %d\n\n", count_row); fflush(stdout);
		  
		  del_linked_list();  //del linked list
		  //close data file
		  if(fclose(finp4) == EOF)
		    {
		      printf("Error in colsing file %s\n", data_name);
		      fflush(stdout);
		    }
		}

	      


	      

	      /*project command */
	      else if(strncmp(cmd, "project", Q_SIZE) == 0)
		{
		  //set all variable to 0
		  count_row = 0;
		  len_t = 0;
		  l_num = 0;
		  set = 0;
		  flag2 = 0;
		  i = 0;

		  //open data file 
		  if((finp4 = fopen(data_name,"r")) == NULL)
		    {
		      printf("Error: Invalid realation -- %s\n\n",data_name);
		      fflush(stdout);
		    }
		  //build linked list and skip 1st line
		  while(fgets(line2, L_SIZE, finp3) != NULL)
		    {
		      if(flag2 == 0)
			{
			}
		      else if (flag2 == T_SIZE)
			{
			  build_linked_list(line2);
			}
		      flag2 = T_SIZE;
		    }
		  //get length of a tuple
		  len_t = len_tuple();
		
		  //count lines from data file
		  while(fread(line2, len_t, 1, finp4) != 0)
		    {
		      count_row++;
		    }
		  
		  c_a = check_att(attrname); //check if att if valied
		  c_t = check_string(attrname);  //check if its s or i
		  //if its string
		  if(c_a == T_SIZE)
		    {
		      l_num = start_pos(attrname); //get starting postion
		      set = find_col(attrname);    //how many char to read
		    
		      //loop how many rows 
		      while(i < count_row)
			{
			  //seek starting postion 
			  fseek(finp4, l_num, SEEK_SET);
			  //if its string
			  if(c_t == T_SIZE)
			    {
			      //read from data file
			      if(fread(line3, 1, set, finp4) != 0)
				{
				  //create space and test if its NULL or not
				  temp_line3 = (char *)malloc(L_SIZE * sizeof(char));
				  if(temp_line3 == NULL)
				    {
				      printf("Storage allocation failure.\n");
				      exit(1);
				    }
				  strcpy(temp_line3, line3); //copy line3 to pointer
				  build_array[i] = temp_line3; //build array
				}
			    }
			  else
			    {
			      //if its int reand and print
			      if(fread((int*)line3, 1, set, finp4) != 0)
				{
				  printf("%d\n",*(int*)line3); fflush(stdout);
				}
			      printf("\n");fflush(stdout);
			    }
			     
			  i++;                    //add one to i
			  l_num = l_num + len_t;   //go to next row
			}//end of while loop




		      /* del doubles from build array */
		      for(i = 0; i < count_row; i++)
			{
			  for(j = i+1; j<count_row; j++)
			    {
			      if(strcmp(build_array[i],build_array[j]) == 0)
				{
				  *build_array[j] = '\0';
				}
			    }
			}
		      /* print array*/
		      for(i = 0; i < count_row; i++)
			{
			  printf("%s\n",build_array[i]);fflush(stdout);
			}
		      
		    } //if(c_a == 1)
		  else
		    {
		      //print error
		      printf(" Error: Invalid attribute -- %s\n\n", attrname);
		    }
		  printf("\n");fflush(stdout);
		  del_linked_list();        //del linked list
		  //close data file
		  if(fclose(finp4) == EOF)
		    {
		      printf("Error in closing file %s\n",data_name);
		      fflush(stdout);
		    }
		    
		}//end of project command






	      
	      /* select command */
	      else if(strncmp(cmd, "select", Z_SIZE) == 0)
		{
		  //set all variable to 0
		  count_row = 0;
		  len_t = 0;
		  l_num = 0;
		  set = 0;
		  flag2 = 0;
		  i = 0;
		  c_a = 0;

		  //open data file
		  if((finp4 = fopen(data_name, "r")) == NULL)
		    {
		      printf("Error: Invalid realation -- %s\n\n", data_name);
		      fflush(stdout);
		    }
		  //build linked list
		  while(fgets(line2, L_SIZE, finp3) != NULL)
		    {  
		      if(flag2 == 0)
			{
			}
		      else if(flag2 == T_SIZE)
			{
			  build_linked_list(line2);
			}
		      flag2 = T_SIZE;           //set flag = 1
		    }
		  //get length of a oen tuple
		  len_t = len_tuple(); 
		  
		  //count lines
		  while(fread(line2, len_t, 1, finp4)  != 0)
		    {
		      count_row++;
		    }
		  
		  
		 
		  
		 
		  c_a = check_att(attrname);     //check if its valid attrname
		  c_t = check_string(attrname);  //check if its s or i
		  //if its s
		  if(c_a == T_SIZE)
		    {
		      l_num = start_pos(attrname);    //get starting postion
		      set = find_col(attrname);      //how many char to read
		    
		      //loop how many row there are
		      while(i < count_row)
			{
			  //set curser
			  fseek(finp4, l_num, SEEK_SET);
			  //if its s
			  if(c_t == T_SIZE)
			    {
			      //read one attri
			      if(fread(line3, 1, set, finp4) != 0)
				{
				  //create space and test it free or not
				  temp_line3 = (char *)malloc(L_SIZE * sizeof(char));
				  if(temp_line3 == NULL)
				    {
				      printf("Storage allocation failure.\n");
				      exit(1);
				    }
				  strcpy(temp_line3, line3); //copy line3 to pointer
				  build_array[i] = temp_line3; //build array
				}
			    }
			  else
			    {
			      // if its i
			      if(fread((int*)line3, 1, set, finp4) != 0)
				{
				 
				}
			      printf("\n");fflush(stdout);
			    }
			     
			  i++;                  //add one to i
			  l_num = l_num + len_t;    //get next row
			}//end of while loop


		      
		      //if its ==
 
		      if(strcmp(relop, "==") == 0)
			{
		        
	   printf("Error -- Wrong type of value for attribute %s\n",attrname);
		 fflush(stdout);
			}
		      

		      //if its !=
		      else if(strcmp(relop, "!=") == 0)
			{
		 printf("Error -- Wrong type of value for attribute %s\n",attrname);
		 fflush(stdout);	  
			}

		      //if its <= and check for error if its s or i
		      else if(strcmp(relop, "<=") == 0)
			{
		 printf("Error -- Wrong type of value for attribute %s\n",attrname);
		 fflush(stdout);      
			}





		      //if its >= and check to see if its s or i
		      else if(strcmp(relop, ">=") == 0)
			{
		 printf("Error -- Wrong type of value for attribute %s\n",attrname);
			      fflush(stdout);      
			}
		      
		      
		      //if its < and check to see if its s or i
		      else if(strcmp(relop, "<") == 0)
			{
		 printf("Error -- Wrong type of value for attribute %s\n",attrname);
		 fflush(stdout);      
			}



		      //if its > and check to see if its s or i
		      else if(strcmp(relop, ">") == 0)
			{
		 printf("Error --Wrong type of value for attribute %s\n",attrname);
		 fflush(stdout);      
			}
		    }
		  //else give error
		      else
			{
			  printf("Error: Invalid attribute -- %s\n\n",attrname);
			  fflush(stdout);
			}
		  
		  del_linked_list(); //error
		  
		  //close data file
		  if(fclose(finp4) == EOF)
		    {
		      printf("Error in closing file %s\n", data_name);
		      fflush(stdout);
		    }
		}
	      




	      //else give error
	      else
		{
		  printf("Error - Command not found.\n"); fflush(stdout);
		}
	      
	      //close file 
	      if(fclose(finp3) == EOF)
		{
		  printf("Error in closing file %s\n", schema_name);
		  fflush(stdout);
		}
	    }//if(flag == 0)
	}//end of while loop
	  
	  
	  
	  
	      
      /* Close CONFIGFILE */
      if(fclose(finp1) == EOF)
	{
	  fprintf(stderr, "Error in colsing file %s.\n", argv[CONFIGFILE]);
	}
      /* Close QUERYFILE */
      if(fclose (finp2) == EOF)
	{
	  fprintf(stderr, "Error in closing file %s.\n", argv[QUERYFILE]);
	}
    }
  //else give error
  else
    {
      fprintf(stderr, "Enter three commands.\n");
    }
  return 0;

}//end of method
