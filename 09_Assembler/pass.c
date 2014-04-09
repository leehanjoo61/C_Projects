/************************************************************************************
File ./h_define.h Starts Here:
************************************************************************************/
#define COMMAND_ARG  2              //number of arg
#define IN_FILE_ARG  1             //input file

#define OBJ_SIZE     65536          //obj_table
#define L_SIZE       81             //size of one line
#define MT_SIZE      36              //mnemonic size
#define S_SIZE       35              //mnemonic index size
#define ES_SIZE      20             //file name size

#define R_SIZE1      11            //for r format
#define R_SIZE2      13            //for r format
#define R_SIZE3      17            //max mnemonic value for r-format

#define I_SIZE1      18             //for i format
#define I_SIZE2      19             //for i format
#define I_SIZE3      23             //for i format
#define I_SIZE4      25             //for i format

#define J_SIZE1      26            //for j format
#define J_SIZE2      27            //for j format
#define J_SIZE3      28            //for j format
#define J_SIZE4      29            //for j format 
#define J_SIZE5      35            //for j format

#define SIZE1        11            //for shifting
#define SIZE2        21            //for shifting
#define SIZE3        6             //for shifting
#define SIZE4        26            //for shifting
#define SIZE5        16            //for shifting

#define LINE_NUM     1             //line starting number
#define C_SIZE       -1            //count in data_table struct




/************************************************************************************
File ./h_global.h Starts Here:
************************************************************************************/
struct node *head;          //head for linked list 1
struct err_node *head2;     //head for linked list 2



/************************************************************************************
File ./h_extern.h Starts Here:
************************************************************************************/
extern struct node *head;       //head for linked list 1
extern struct err_node *head2;  //head for linked list 2





/************************************************************************************
File ./h_prototype.h Starts Here:
************************************************************************************/
void set_null(char[]);                        //set char array to '\0'
void del_newline(char[]);                     //replace '\n' with '\0'

void get_file_name(char[], char[], char [], char[], char[]);  //get file names

int empty_line(char[]);                          //skip empty lines
int comment_line(char[]);                         //skip comment lines
void inline_comment(char[], char[]);              //del in line comments

/******************************************/
/********* Sym table function *************/
/******************************************/
void sym_token(char[], struct data_table *);                    //token on sym  
void insert_sym_table(char *, int, struct data_table *);        //insert sym
void print(FILE *, char[]);                                     //print sym

/******************************/
/**** Error file functions ****/
/*****************************/
void insert_err_opcode(char *);                         //insert wrong opcode
void print_err_opcode(FILE *);                          //print wrong opcode
void repeat_err_label(char []);                         //insert repeat label
void print_repeat_err_label(FILE *);                    //print repeat label
void insert_wro__label(char *, struct data_table *);    //insert wrong label
void print_wrong_err_label();                           //print wrong label

/**********************************************************/
/************ Obj file functions **************************/
/**********************************************************/
void obj_token(char[], char*[], int[], struct data_table *);
void resw(char[], int[], struct data_table *, int);             //.resw(with label)
void word(char[], int[], struct data_table *, int);             //.word(with label)
void R_rrs(char[], int[], int, int, int);                       //R-FORMAT
void R_rrr(char[], int[], int, int, int);                       //R-FORMAT
void I_ri(char[], int[], int, int, int);                        //I-FORMAT
void I_rri(char[], int[], int, int, int);                       //I-FORMAT
void I_rir(char[], int[], int, int, int);                       //I-FORMAT
void J_ra(char[], int[], int, int, int, struct data_table *);   //J-FORMAT
void J_a(char[], int[], int, int, int, struct data_table *);    //J-FORMAT
void J_rra(char[], int[], int, int, int, struct data_table *);  //J-FORMAT
int check_label(char *, int *);                                 //check for label



/************************************************************************************
File ./h_struct.h Starts Here:
************************************************************************************/
/* sym_table */
struct node
{
  char label[ES_SIZE];                 //sym table - label name
  int line;                          //LC-VALUE
  struct node *next;                 //point to next
};


/* wrong opcode*/
struct err_node
{
  char err_opcode[ES_SIZE];          //wrong opcode names
  char err_repeat_label[ES_SIZE];   //repeating labels
  char err_wrong_label[ES_SIZE];    //wrong label
  struct err_node *next;      //pointe to next
};

struct data_table
{
  int count;       //sym file 
  int r;           //obj file address
  int print_flag;  //what file to print
  int flag0;       //label or no label
};


/************************************************************************************
File ./f_main.c Starts Here:
************************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "h_define.h"
#include "h_struct_def.h"
#include "h_global.h"
#include "h_prototype.h"

int main(int argc, char *argv[])
{
  /* store mnemonic value*/
  char *mnemonic_table[MT_SIZE] = { "hlt", "add", "sub", "mul", "div", "mod",
				    "move", "and", "or", "xor", "com", "sll",
				    "srl", "sra", "jr", "rdr", "prr", "prh",
				    "li", "addi", "subi", "muli", "divi", 
				    "modi", "lwb", "swb", "lwa", "swa", "j", 
				    "jal", "jeq", "jne", "jlt", "jle", "jgt", 
				    "jge" };
  
  /* store obj_table */
  int obj_table[OBJ_SIZE];       //SIZE 65536
  int total = 0;              //length of obj_table array


  /* read from files */
  char line[L_SIZE];          //SIZE 81
  char line2[L_SIZE];         //SIZE 81
  
  /* tem variables */
  char temp1[L_SIZE];         //SIZE 81
  char temp2[L_SIZE];         //SIZE 81
  
  /* roste file names*/
  char sym_name[S_SIZE];
  char obj_name[S_SIZE];
  char err_name[S_SIZE];
  
  /* file variables */
  FILE *finp1;                 //input file
  FILE *foutp2;                //sym file
  FILE *foutp3;                //obj file
  FILE *foutp4;                //error file
  
  struct data_table buff1 = {C_SIZE, 0, 0, 0};     //store index values
  int l = LINE_NUM;                             //eroor file - line number

  
  /* Check for two commands */
  if(argc == COMMAND_ARG)
    {
      /* Open input file*/
      if((finp1 = fopen(argv[IN_FILE_ARG], "r")) == NULL)
	{
	  fprintf(stderr, "Could not open file %s\n", argv[IN_FILE_ARG]);
	  exit(1);
	}
      
      /* set char arrays to null*/
      set_null(line);
      set_null(line2);
      set_null(temp1); 
      set_null(temp2);
      set_null(sym_name);
      set_null(obj_name);
      set_null(err_name);
         
      strcpy(temp1, argv[IN_FILE_ARG]);          //copy name in to temp1 
    
      /* create sym, obj, err file name */
      get_file_name(temp1, temp2, obj_name, sym_name, err_name);

      /*********************************/
      /** Pass one -- create sym_file **/
      /*********************************/
      while(fgets(line, L_SIZE, finp1) != NULL)          //read one line 
	{
	  del_newline(line);                             //del \n symbol
	  
	  if(empty_line(line) != 0)                      //skip empty lines
	    {
	      if(comment_line(line) != 0)                //skip comment lines
		{
		  if(strstr(line, ".text") == 0)          //skip .text lines
		    {
		      if(strstr(line, ".data") == 0)       //skip .data lines
			{
			 
			  inline_comment(line, line2);     //del in line comments
			  sym_token(line2, &buff1);        //create sym table
			}
		    }
		}
	    }
	  set_null(line);                                    //set to null
	  set_null(line2);                                   //set to null
	}//end of while loop
    

      /*****************************************/
      /*** Pass two -- obj_file or  err_file ***/
      /*****************************************/               
      fseek(finp1, 0, SEEK_SET);                           //set curser in begining
      while(fgets(line, L_SIZE, finp1) != NULL)            //read one line
	{
	  del_newline(line);                               //del \n sym

	  if(empty_line(line) != 0)                        //skip empty lines
	    {
	      if(comment_line(line) != 0)                   //skip comment lines
		{
		  if(strstr(line, ".text") == 0)             //skip .text lines
		    {
		      if(strstr(line, ".data") == 0)         //skip .data lines
			{
			  inline_comment(line, line2);       //del in line comments 
			  /* Create obj table */
			  obj_token(line2, mnemonic_table, obj_table, &buff1);
			}
		    }
		}
	    }
	  set_null(line);                                    //set to null
	  set_null(line2);                                   //set to null
	}//end of while loop
                 
      
      /******************** Print files ******************/
      if(buff1.print_flag == 0)                      //if there are no errors
	{
	  /* open foutp3 file*/
	  if((foutp3 = fopen(obj_name, "w")) == NULL)
	    {
	      fprintf(stderr, "Could not open file %s\n", obj_name);
	      exit(1);
	    }
	  
	  
	  /* print in sym file */
	  print(foutp2, sym_name);
	 
	  total = buff1.r;                                 //get max value of array
	  /*** print obj table ***/
	  for(buff1.r = 0; buff1.r < total; buff1.r++)
	    {
	      fprintf(foutp3, "%X %X\n", buff1.r, obj_table[buff1.r]); 
	    }
	  
	  
	  /* Close input file*/
	  if(fclose(foutp3) == EOF)
	    {
	      fprintf(stderr, "Error in closing file %s", obj_name);
	    }
	}
      else
	{
	  /* open foutp3 file*/
	  if((foutp4 = fopen(err_name, "w")) == NULL)
	    {
	      fprintf(stderr, "Could not open file %s\n", err_name);
	      exit(1);
	    }
	  
	  
	  /* Error file part -- 1 */
	  fseek(finp1, 0, SEEK_SET);                       //set curser in begining
	  while(fgets(line, L_SIZE, finp1) != NULL)            //read one line
	    {
	      del_newline(line);                               //del \n sym
	      
	      fprintf(foutp4, " %d   %s\n", l, line);         //print line number
	      l++;
	    }
	  
	  /* Error file part -- 2.2 */
	  print_err_opcode(foutp4);        //wrong opcode
	  print_repeat_err_label(foutp4);  //repeating labels
	  print_wrong_err_label(foutp4);   //print wrong lables
	  
	  /* Close input file*/
	  if(fclose(foutp4) == EOF)
	    {
	      fprintf(stderr, "Error in closing file %s", err_name);
	    }
	}
      /* Close input file */
      if(fclose(finp1) == EOF)
	{
	  fprintf(stderr, "Error in closing file %s", argv[IN_FILE_ARG]); 
	}
    }
  else
    {
      fprintf(stderr, "Error -- Enter two commands");    //error- enter 2 commands
    }
  return 0;
}



/************************************************************************************
File ./f_funct.c Starts Here:
************************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "h_define.h"
#include "h_struct_def.h"
#include "h_extern.h"
#include "h_prototype.h"

/* set char array to '\0' */
// takes in char array 
void set_null(char temp[])
{
  int i = 0;                          //index value

  for(i = 0; i <= L_SIZE; i++)        //loop
    {
      temp[i] = '\0';                //set to null
    }
}

/* replace '\n' with '\0' */
//takes in char array 
void del_newline(char line[])
{
  int i = 0;                       //index value

  for(i = 0; i <= L_SIZE; i++)      //loop
    {
      if(line[i] == '\n')            //find \n
	{
	  line[i] = '\0';            //set to null
	}
    }
}

/* create obj_name, sym_name, err_name files */
//takes in 5 char arrays
void get_file_name(char temp1[], char temp2[], 
	   char obj_name[], char sym_name[], char err_name[])
{
  int i = 0;                      //index value

  int flag = 0;                   //flag 1
  int flag2 = 0;                  //flag 2
  

  for(i = 0; i < S_SIZE; i++)     //loop
    {
      if(temp1[i] != '.')         //if it dont have .
	{
	}
      else
	{
	  flag = 0;                 //else set flag to 0
	  break;                    //break from loop
	}
      flag = LINE_NUM;                     //set to flag 1
    }

  /* 1 for no dot */
  if(flag == LINE_NUM)                        //if there is no dot
    {
      
      for(i = 0; i < S_SIZE; i++)                  //loop
	{
	  temp2[i] = temp1[i];                    //store in different array
	}
    }
  else
    {
      for(i = S_SIZE; i >= 0; i--)             //lopp backward
	{
	  if(flag2 == LINE_NUM)                 //set flag to 1
	    {
	      temp2[i] = temp1[i];             //store in different array
	    }
	  if(temp1[i] == '.')                   //find .
	    {
	      flag2 = LINE_NUM;                //set flag2 to 1 
	    }
	}
    }

  strcpy(obj_name, temp2);                    //copy value in different array
  strcpy(sym_name, temp2);                    //copy value in different array
  strcpy(err_name, temp2);                    //copy value in different array
  strcat(obj_name, ".obj");                   //add .obj at end
  strcat(sym_name, ".sym");                   //add .sym at end
  strcat(err_name, ".err");                   //add .err at end
}

/* check for empty lines -- return 1 for empty line */
//takes in char array and return int
int empty_line(char line[])
{
  int i = 0;                                      //index value
  
  for(i = 0; line[i] != '\0'; i++)               //loop
    {
      //if there isnt \n, \t, or ' '
      if((line[i] != '\n') && (line[i] != '\t') && (line[i] != ' '))
	{
	  return 1;                            //not empty
	}
    }
  return 0;                                       //empty
}

/* check for comment lines -- return 1 for comment line */
//takes in char array and return int
int comment_line(char line[])
{
  if(line[0] == '#')                   //find #
    {
      return 0;                       //comment line
    }
  else
    {
      return 1;                         //not comment line
    }
}

/* del in line comments */
//takes in 2 char arrays
void inline_comment(char line[], char line2[])
{
  int i = 0;                              //index value
 
 
  for(i = 0; i <= L_SIZE; i++)           //loop
    {
      if(line[i] == '#')                 //find #
	{
	  break;                          //break if found
	}
      else
	{
	  line2[i] = line[i];            //else store in different array
	}
    }
 
}


/* first pass - create sym_file */
//takes in char array and a struct
void sym_token(char line2[], struct data_table *buff1)
{
  char temp_line2[L_SIZE];                      //read line
  
  char *tptr;                                    //pointer for token   
  char *tptr2;                                  //2nd pointer for token
  
  char *error;                                  //stdtod
  int num = 0;                                 //covert char to int

  int flag = 0;                                //flag 1
  int mini = 0;                                //flag 2


  strcpy(temp_line2, line2);                         //copy value
  
  /* does not have label */
  if(strstr(temp_line2, ":") == 0)                     //does not have label
    {
      if(strstr(temp_line2, ".resw") != 0)              // .resw in line 
	{
	  tptr = strtok(temp_line2, " \t:\n");          //1st value
	  tptr = strtok(NULL, " \t:\n");                //2nd value
	  if(tptr != NULL)                     
	    {
	      num = strtod(tptr, &error);               //convert to int
	      buff1->count = buff1->count + num;        //add to buff1->count
	      flag = LINE_NUM;                          //set flag to 1   
	    }
	}
      else                                              //add $1,$2,$3
	{
	  buff1->count++;                               //add 1 to buff1->count
	  flag = LINE_NUM;                             //add 1 to flag 
	}
    }
  
  if(flag == 0)                                            //label: 
    {  
      tptr = strtok(temp_line2, " \t:\n");                 //get 1st word
      if(tptr != NULL)
	{
	  if(strstr(temp_line2, ".word") != 0)             //.word -3:1
	    {
	      tptr = strtok(NULL, " \t:\n");               //get 2nd word
	      tptr = strtok(NULL, " \t:\n");               //get 3rd word
	      if(tptr != NULL)
		{
		  num = strtod(tptr, &error);             //convert to int
		  buff1->count = buff1->count + num;       //add to buff1->count
		  mini = LINE_NUM;                        //set flag to 1 
		}
	    }
	}
      if (mini == 0)                                    //if flag2 is 0
	{ 
	  buff1->count++;                                 //add one to buff1->count
	  insert_sym_table(tptr, buff1->count, buff1);   //call insert method
	  if(strstr(line2, ".resw") != 0)                    //label: .resw 3
	    {
	      tptr2 = strtok(line2, " \t\n");               //get 1st word
	      tptr2 = strtok(NULL, " \t\n");               //get 2nd word
	      tptr2 = strtok(NULL, " \t\n");               //get 3rd word
	      if(tptr2 != NULL)
		{
		  num = strtod(tptr2, &error);              //convert to int
		  buff1->count = buff1->count + num;         //add to buff1->count
		  buff1->count--;                          //sub from buff1->count
		}
	    }
	 else if(strstr(line2, ".word") != 0)               //label: .word -1:2
	    {
	      tptr2 = strtok(line2, " :\t\n");               //get 1st word
	      tptr2 = strtok(NULL, " :\t\n");               //get 2nd word
	      tptr2 = strtok(NULL, " :\t\n");               //get 3rd word
	      tptr2 = strtok(NULL, " :\t\n");               //get 4th word
	      if(tptr2 != NULL)
		{
		  num = strtod(tptr2, &error);               //convert to int
		  buff1->count = buff1->count + num;        //add to buff1->count
		  buff1->count--;                          //sub from buff1->count
		} 
	    }
	}
    }
}


/* create linked list for sym_file */
//takes in char pointer and int
void insert_sym_table(char *tptr, int count, struct data_table *buff1)
{
  struct node *cur_node = head;    //point to head
  struct node *new_node;           //new node

  
  if(cur_node == NULL)                      //if its empty
    {
      head = (struct node *) malloc(sizeof(struct node));     //create head
      if(head == NULL)                                        //check for space
	{
	  printf("Node allocation failed.\n"); fflush(stdout);  //exit if fail
	  exit(1);
	}
      strcpy(head->label, tptr);      //copy to head label
      head->line = count;            //add to head line
      head->next = NULL;              //set next head to null
    }
  else                                  //if not empty
    {
      while(cur_node != NULL)                     //check for repeating errors
	{
	  if(strcmp(cur_node->label, tptr) == 0)  //if string isnt in linked list
	    {
	      repeat_err_label(cur_node->label);      //call function for error
	      buff1->print_flag = LINE_NUM;                 //set flag to 1
	    }
	  cur_node = cur_node->next;                    //go to next node
	}
      
      cur_node = head;                                 //start from begining
      while(cur_node->next != NULL)                    //go to last node
	{ 
	  cur_node = cur_node->next;                    //next node
	}
      new_node = (struct node *) malloc(sizeof(struct node)); //create new node
      if(new_node == NULL)                                  //test space
	{
	  printf("Node allocation failed.\n"); fflush(stdout); //exit if failed
	  exit(1);
	}
      strcpy(new_node->label, tptr);               //copy to node 
      new_node->line = count;                      //add to node
      new_node->next = NULL;                     //set next to null
      cur_node->next = new_node;                //link nodes
    }
}


/* print sym table */
//takes in FILE and char array
void print(FILE *foutp2, char sym_name[])
{
  struct node *cur_node = head;             //point to head


  /* Open sym file for writing */
  if((foutp2 = fopen(sym_name, "w")) == NULL)
    {
      fprintf(stderr, "Could not open file %s\n", sym_name);
      exit(1);
    }
  
  if(cur_node == NULL) 
    {
      //do nothing if list is empty
    }
  else
    {
      while(cur_node != NULL)         //if its not empty, loop through it 
	{
	  //print to file and go to next node
	  fprintf(foutp2, "%s\t\t%d\n", cur_node->label, cur_node->line);
	  cur_node = cur_node->next;
	}
    }

  /* Close sym file*/
  if(fclose(foutp2) == EOF)
    {
      fprintf(stderr, "Error in closing file %s", sym_name);
    }
}


/********************************************************************/
/**************** Error files functions *****************************/
/********************************************************************/
//insert wrong opcode in linked list 2
//takes in char pointer
void insert_err_opcode(char *tptr)
{
  struct err_node *cur_node2 = head2;      //point to head2
  struct err_node *new_node2;              //new node2
  
  
  if(cur_node2 == NULL)                     //if empty node
    {
      head2 = (struct err_node *) malloc(sizeof(struct err_node)); //create head2
      if(head2 == NULL)                        //test space, exit if failed
	{
	  printf("Node allocation failed.\n"); fflush(stdout);
	  exit(1);
	}
      strcpy(head2->err_opcode, tptr);          //copy in to head array
      head2->next = NULL;                         //set next to null
    }
  else
    {
      while(cur_node2->next != NULL)             //if not empty
	{ 
	  cur_node2 = cur_node2->next;          //go to last node
	}
      new_node2 = (struct err_node *) malloc(sizeof(struct err_node)); //create node
      if(new_node2 == NULL)     //test space, exit if failed
	{
	  printf("Node allocation failed.\n"); fflush(stdout);
	  exit(1);
	}
      strcpy(new_node2->err_opcode, tptr);  //add to new node
      new_node2->next = NULL;              //set next to null
      cur_node2->next = new_node2;             //link nodes
    }
}


/* print wrong opcodes  */
//takes in file pointer foutp4
void print_err_opcode(FILE *foutp4)
{
  struct err_node *cur_node2 = head2;  //pointer to head2
  
  if(cur_node2 == NULL)               
    {
      //if empty print nothing
    }
  else
    {
      fprintf(foutp4, "\n\nIllegal opcodes:\n");     //print title
      while(cur_node2 != NULL)                        //if not empty
	{
	  fprintf(foutp4, "  %s\n", cur_node2->err_opcode); //print to file
	  cur_node2 = cur_node2->next;                    //next node
	}
    }
}


/* insert wrong label in to linked list 2 */
//take in array
void repeat_err_label(char str[])
{
  struct err_node *cur_node2 = head2;   //point to head2
  struct err_node *new_node2;          //new node
  
  
  if(cur_node2 == NULL)               //if empty
    {
      head2 = (struct err_node *) malloc(sizeof(struct err_node)); //create head
      if(head2 == NULL)      //test for space, exit if failed
	{
	  printf("Node allocation failed.\n"); fflush(stdout);
	  exit(1);
	}
      strcpy(head2->err_repeat_label, str);  //copy to head
      head2->next = NULL;                 //set next head to null
    }
  else
    {
      while(cur_node2->next != NULL)       //go to last node
	{ 
	  cur_node2 = cur_node2->next;
	}
      new_node2 = (struct err_node *) malloc(sizeof(struct err_node)); //create node
      if(new_node2 == NULL)  //test space, exit if failed
	{
	  printf("Node allocation failed.\n"); fflush(stdout);
	  exit(1);
	}
      strcpy(new_node2->err_repeat_label, str); //copy to new node
      new_node2->next = NULL;                   //set next to null
      cur_node2->next = new_node2;            //link nodes
    }
}


//print repeat label errors
//takes in file pointer foutp4
void print_repeat_err_label(FILE *foutp4)
{
  struct err_node *cur_node2 = head2;   //point to head
  
  if(cur_node2 == NULL)               
    {
      //if empty print nothing
    }
  else
    {        //if not empty print title
      fprintf(foutp4,"\n\nMultiply defined symbols:\n");
      while(cur_node2 != NULL)      //if not empty
	{                    //print to error file
	  fprintf(foutp4, "  %s\n", cur_node2->err_repeat_label);
	  cur_node2 = cur_node2->next;   //point to next node
	}
    }
}

/* insert wrong labels in link list 2 */
//take in char pointer 
void insert_wro_label(char *str)
{
  struct err_node *cur_node2 = head2;          //point to head2
  struct err_node *new_node2;                  //new node
  
  
  if(cur_node2 == NULL)                //if empty
    {
      head2 = (struct err_node *) malloc(sizeof(struct err_node)); //create head2
      if(head2 == NULL)    //test space, and exit if failed
	{
	  printf("Node allocation failed.\n"); fflush(stdout);
	  exit(1);
	}
      strcpy(head2->err_wrong_label, str);   //copy in head
      head2->next = NULL;                    //set next head to null
    }
  else
    {
      while(cur_node2->next != NULL)      //go to last node
	{ 
	  cur_node2 = cur_node2->next;
	}
      new_node2 = (struct err_node *) malloc(sizeof(struct err_node)); //create node
      if(new_node2 == NULL)         //test space, exit if failed
	{
	  printf("Node allocation failed.\n"); fflush(stdout);
	  exit(1);
	}
      strcpy(new_node2->err_wrong_label, str);   //copy to node
      new_node2->next = NULL;                    //set next node to null
      cur_node2->next = new_node2;              //link nodes
    }
}

//print wrong labels errors
//take in file pointer foutp4
void print_wrong_err_label(FILE *foutp4)
{
  struct err_node *cur_node2 = head2;      //point to head2
  
  if(cur_node2 == NULL) 
    {
      //if empty print nothing
    }
  else
    {         //if not empty, print title
      fprintf(foutp4, "\n\nUndefined symbols:\n");
      while(cur_node2 != NULL)      
	{                //print to error file and go to next node
	  fprintf(foutp4, "  %s\n", cur_node2->err_wrong_label);
	  cur_node2 = cur_node2->next;
	}
    }
}


/*******************************************************************/
/************************ obj file functions ***********************/
/*******************************************************************/
//creates a obj table 
//take in 2 arrays, 1 array of pointer and 1 struct
void obj_token(char line2[], char *mnemonic_table[], int obj_table[],
	       struct data_table *buff1)
{
  int i = 0;                            //index value
  
  int flag = 0;                        //flag
  
  char tem_line2[L_SIZE];                 //temp for line2    
  char *tptr;                           //pointer for token
  char *tptr2;                         //pointer for token
  
  buff1->flag0 = 0;                    //start with flag to 0

  strcpy(tem_line2, line2);              //copy to tem_line2

  tptr = strtok(line2, " \t");              //get 1st word
  if(tptr != NULL)                      //if not empty
    {
      if(strstr(tptr, ":") != 0)            //if its label
	{
	  tptr = strtok(NULL, " \t");      //mnemonic, .resw, .word
	  if(tptr != NULL)                      //if not empty
	    {
	      if(strstr(tptr, ".resw") != 0)        //.resw
		{
		  buff1->flag0 = LINE_NUM;           //set flag to 1, call function
		  resw(tem_line2, obj_table, buff1, buff1->flag0);  
		}
	      else if(strstr(tptr, ".word") != 0)     //if .word
		{
		  buff1->flag0 = LINE_NUM;   //set flag to 1 and call word function
		  word(tem_line2, obj_table, buff1, buff1->flag0);
		}
	      else                                        //if mnemonic
		{
		  for(i = 0; i <= S_SIZE; i++)                //check mnemonic
		    {     
		      if(strcmp(mnemonic_table[i], tptr) == 0) //if found
			{
			  flag = LINE_NUM;           //set flag to 1 
			  break;                    //break from for loop
			}
		    }//end of for loop

		  if(flag == LINE_NUM)              //mnemonic is ok
		    {                               //(opcode-rs1-rs2-rt-sa-uncused)
		      if(i >= 0 && i <= R_SIZE3)                  //1-17 R-Format
			{
			  if(i == 0)                         //htl
			    {
			    }
			  else if(i >= R_SIZE1 && i <= R_SIZE2)   //sll srl,sra
			    {
			      buff1->flag0 = LINE_NUM; //set flag to 1
			      //call function-take in 2 array,int,int,int
			     R_rrs(tem_line2, obj_table, i ,buff1->r, buff1->flag0);
			    }
			  else                                //1-10 14-17  
			    {		
			      buff1->flag0 = LINE_NUM; //set flag to 1
			      //call function-take in char[],char[],int,int,int
			     R_rrr(tem_line2, obj_table, i, buff1->r, buff1->flag0);
			    }
			}                         //[opcode-rs-rt-immediate operand]
		      else if(i >= I_SIZE1 && i <= I_SIZE4)   //1-25 I-Format
			{
			  if(i == I_SIZE1)                         // li 
			    {
			      buff1->flag0 = LINE_NUM;  //set flag to 1
			      //call function-take in char[],char[],int,int,int
			      I_ri(tem_line2, obj_table, i, buff1->r, buff1->flag0);
			    }
			  //addi,subi,muli,divi,modi
			  else if(i >= I_SIZE2 && i <= I_SIZE3) 
			    {
			      buff1->flag0 = LINE_NUM;  //set flag to 1
			      //call function-take in char[].char[],int,int,int
			     I_rri(tem_line2, obj_table, i, buff1->r, buff1->flag0);
			    }
			  else                            //lwb, sub
			    {
			      buff1->flag0 = LINE_NUM;  //set flag to 1
			      //char function-2char[],int,int,int
			     I_rir(tem_line2, obj_table, i, buff1->r, buff1->flag0);
			    }
			}                                  //[opcode-rs-rt-address]
		             //26-35 J-Format
		      else if(i >= J_SIZE1 && i <= J_SIZE5)    
			{
			  if(i == J_SIZE1 || i == J_SIZE2)               //lwa, swa
			    {
			      buff1->flag0 = LINE_NUM;  //set flag to 1
			      //call function-take 2char[],int,int,int
		     J_ra(tem_line2, obj_table, i, buff1->r, buff1->flag0, buff1);
			    }
			  else if(i == J_SIZE3 || i == J_SIZE4)          //j, jal
			    {
			      buff1->flag0 = LINE_NUM;    //set flag to 1
			      //call function-2char[],int,int,int
		       J_a(tem_line2, obj_table, i, buff1->r, buff1->flag0, buff1);
			    }
			  else                          //jeq,jne,jlt,jle,jgt,jge
			    {
			      buff1->flag0 = LINE_NUM; //set flag to 1
			      //call function-take in 2char[],int,int,int
		     J_rra(tem_line2, obj_table, i, buff1->r, buff1->flag0, buff1);
			    } 
			}
		    }
		  else            //error
		    {
		      // wrong opcode
		      insert_err_opcode(tptr); //insert in linked list
		      buff1->print_flag = LINE_NUM;    //set flag to 1 
		    }
		}
	    }
	  
	}
      
      /************ Not a label ***********/
      else if(strstr(tptr, ":") == 0)             //not label
	{
	  if(strstr(tptr, ".resw") != 0)            //if .resw in line
	    {
	      //call function that take care of it. 
	      //take in 2char[],struct,int
	      resw(tem_line2, obj_table, buff1, buff1->flag0); 
	    }
	  else if(strstr(tptr, ".word") != 0)      //if .word
	    {
	      //call function that take care of it
	      //take in  2 char[],struct, int
	      word(tem_line2, obj_table, buff1, buff1->flag0);
	    }
	  else                                    //else mnemonic
	    {
	      for(i = 0; i < S_SIZE; i++)                  //check for mnemonic
		{
		  if(strcmp(mnemonic_table[i], tptr) == 0) //if found
		    {
		      flag = LINE_NUM;       //set flag to 1
		      break;               //break from for loop
		    }
		}//end of for loop
	      
	      if(flag == LINE_NUM)         //if flag == 1    
		{
		  if(i >= 0 && i <= R_SIZE3)                  //1-17 R-Format
		    {
		      if(i == 0)                         //htl
			{
			  //do nothing
			}
		      else if(i >= R_SIZE1 && i <= R_SIZE3)         //sll srl,sra
			{
			  //call function
			  R_rrs(tem_line2, obj_table, i ,buff1->r, buff1->flag0);
			}
		      else                                //1-10 14-17  
			{		
			  //call function
			  R_rrr(tem_line2, obj_table, i, buff1->r, buff1->flag0);
			}
		    }                         //[opcode-rs-rt-immediate operand]
		  else if(i >= I_SIZE1 && i <= I_SIZE4)    //18-25 I-Format
		    {
		      if(i == I_SIZE1)                         // li 
			{
			  //call function
			  I_ri(tem_line2, obj_table, i, buff1->r, buff1->flag0);
			}
		          //addi,subi,muli,divi,modi
		      else if(i >= I_SIZE2 && i <= I_SIZE3) 
			{
			  //call function
			  I_rri(tem_line2, obj_table, i, buff1->r, buff1->flag0);
			}
		      else                            //lwb, sub
			{
			  //call function
			  I_rir(tem_line2, obj_table, i, buff1->r, buff1->flag0);
			}
		    }                                  //[opcode-rs-rt-address]
		          //26-35 J-Format
		  else if(i >= J_SIZE1 && i <= J_SIZE5)   
		    {
		      if(i == J_SIZE1 || i == J_SIZE2)               //lwa, swa
			{
			  //call function
		      J_ra(tem_line2, obj_table, i, buff1->r, buff1->flag0, buff1);
			}
		      else if(i == J_SIZE3 || i == J_SIZE4)          //j, jal
			{
			  //call function
		      J_a(tem_line2, obj_table, i, buff1->r, buff1->flag0, buff1);
			}
		      else                          //jeq,jne,jlt,jle,jgt,jge
			{
			  //call function
		     J_rra(tem_line2, obj_table, i, buff1->r, buff1->flag0, buff1);
			}
		    }
		}
	      else        //error
		{
		  // wrong opcode
		  insert_err_opcode(tptr);      //insert in linked list 2
		  buff1->print_flag = LINE_NUM;  //set flag to 1
		}

	    }
	}
    }
  buff1->r++;          //add one to buff1->r
}//end of method


/*** resw ***/
//function that take care if there is .resw in char array
//take in 2char arrays, 1 struct, 1 int
void resw(char tem_line2[], int obj_table[], struct data_table *buff1, int flag0)
{
  char *tem_tptr;           //pointer for token

  char *error;             //for strtod
  int num = 0;             //for converting


  tem_tptr = strtok(tem_line2, " :$,\t\n");          //get 1st word
  if(flag0 == LINE_NUM)                            //if flag is 1
    {
      tem_tptr = strtok(NULL, " :$,\t\n");         //get 2nd word
      flag0 = 0;                                   //set flag to 0
    }
  if(flag0 == 0)                                 //if flag is 0
    {
      tem_tptr = strtok(NULL, " :$,\t\n");          //get 3rd word
      if(tem_tptr != NULL)                         //if not empty
	{
	  num = strtod(tem_tptr, &error);         //convert to int
	  buff1->r = buff1->r + num;             //add to buff1->r
	  buff1->r--;                          //sub 1
	}
    }
}

/*** word ***/
//function that take care if there if .word in char array
//take in 2 char array, 1 struct, 1 int
void word(char tem_line2[], int obj_table[], struct data_table *buff1, int flag0)
{
  char *tem_tptr;                              //pointer for token

  char *error;                                 //for strtod
  int i = 0;                                   //index value
  int num = 0;                                //for converting
  int num2 = 0;                                  //for converting

  tem_tptr = strtok(tem_line2, " :$,\t\n");     //get 1st word
  if(flag0 == LINE_NUM)                          //if flag is 1
    {
      tem_tptr = strtok(NULL, " :$,\t\n");         //get 2nd word
      flag0 = 0;                               //set flag to 0
    }
  if(flag0 == 0)                               //if flag is 0
    {
      tem_tptr = strtok(NULL, " :$,\t\n");            //3rd word
      if(tem_tptr != NULL)                         //if not empty
	{
	  num = strtod(tem_tptr, &error);          //convert to int
	}
      tem_tptr = strtok(NULL, " :$,\t\n");         //get next word
      if(tem_tptr != NULL)                          //if not empty
	{
	  num2 = strtod(tem_tptr, &error);         //convert to int
	}
      while(i < num2)                          //loop through num2 times
	{
	  //add to obj_table array, add 1 to i and buff1->r
	  obj_table[buff1->r] = obj_table[buff1->r] | (num << 0);
	  i++;
	  buff1->r++;
	}
      buff1->r--;  //sub -1 from buff1->r
    }
}

/************************** R-FORMAT ***********************************/
//take care of r-format part 2.
//takes in 2 char arrays, 3 ints
/*  R-FORMAT -sll srl,sra- */
//the first two are register and the last is a non--nogative inteager in the 
//range 0-31 dec.
void R_rrs(char tem_line2[], int obj_table[], int i, int r, int flag0)
{
  char *tem_tptr;                               //pointer for token

  char *error;                                   //for strtod
  int num = 0;                                   //for converting
 
  tem_tptr = strtok(tem_line2, " :$,\t\n");     //get 1st word        
  if (flag0 == LINE_NUM)                        //if flag is 1
    {
      tem_tptr = strtok(NULL, " :$,\t\n");      //get next word
      flag0 = 0;                               //set flag to 0
    }
  if(flag0 == 0)                               //if flag is 0
    {
      if(tem_tptr != NULL)                     //if its not empty
	{
	  obj_table[r] = obj_table[r] | (i << 26);  //add to int array        
	}
      tem_tptr = strtok(NULL, " :$,\t\n");            //get next word
      if(tem_tptr != NULL)                                   //RT
	{
	  num = strtod(tem_tptr, &error);               //convert to int
	  obj_table[r] =  obj_table[r] | (num << SIZE1);   //add to int array
	}
      tem_tptr = strtok(NULL, " :$,\t\n");             //get next word
      if(tem_tptr != NULL)                                    //RS1
	{
	  num = strtod(tem_tptr, &error);            //convert to int
	  obj_table[r] =  obj_table[r] | (num << SIZE2);  //shift to int array
	}
      tem_tptr = strtok(NULL, " :$,\t\n");            //next word
      if(tem_tptr != NULL)                                    //sa
	{
	  num = strtod(tem_tptr, &error);                  //convert to int
	  obj_table[r] =  obj_table[r] | (num << SIZE3);       //shift to int array
	}
    }
}

/* R-FORMAT 1-10 14-17 */
//take care of r format, part 3
//each of the opcode add, sub, mul, div, mod, and , or and xor, uses three
//register operands. 
//take in 2 char array, 3 ints
void R_rrr(char temp_line2[], int obj_table[], int i, int r, int flag0)
{ 
  char *tem_tptr;                            //pointer for token

  char *error;                                  //for strtod
  int num = 0;                                   //converting

  
  tem_tptr = strtok(temp_line2, " :$,\t\n");       //get 1st wword
  if(flag0 == LINE_NUM)                           //if flag to 1
    {
      tem_tptr = strtok(NULL, " :$,\t\n");        //get next word        
      flag0 = 0;                                  //set flag to 0
    }
  if(flag0 == 0)                                   //if flag is 0
    {
      if(tem_tptr != NULL)                           //if its not empty
	{
	  obj_table[r] = obj_table[r] | (i << SIZE4);  //shift from int array      
	}
      tem_tptr = strtok(NULL, " :$,\t\n");                   //RT
      if(tem_tptr != NULL)                               //get next word     
	{
	  num = strtod(tem_tptr, &error);               //convert to int
	  obj_table[r] =  obj_table[r] | (num << SIZE1);    //shift from int array
	}
      tem_tptr = strtok(NULL, " :$,\t\n");                     //Rs1
      if(tem_tptr != NULL)                                //get next word      
	{
	  num = strtod(tem_tptr, &error);                 //convert to int
	  obj_table[r] =  obj_table[r] | (num << SIZE2);   //shift from int array
	}
      tem_tptr = strtok(NULL, " :$,\t\n");           //get next word
      if(tem_tptr != NULL)                                    //RS2
	{
	  num = strtod(tem_tptr, &error);              //convert to int
	  obj_table[r] =  obj_table[r] | (num << SIZE5);  //shift from int array
	}
    }
}

/************************* I-FORMAT ******************************/
/* I-FORMAT li  */
//opcode li uses two oprands the first of which is the target register and 
//second is an integer
//take care of i format part 1
//take in 2 char array, 3 ints
void I_ri(char temp_line2[], int obj_table[], int i, int r, int flag0)
{ 
  char *tem_tptr;                             //pointer for token
  
  char *error;                                   //strtod
  int num = 0;                                  //converting
  
  tem_tptr = strtok(temp_line2, " :$,\t\n");    //get 1st word
  if(flag0 == LINE_NUM)
    {
      tem_tptr = strtok(NULL, " :$,\t\n");         //get next word               
      flag0 = 0;                                   //set flag to 1
    }
  if(flag0 == 0)                                    //if flag is 0
    {
      if(tem_tptr != NULL)                                //opcode
	{
	  obj_table[r] = obj_table[r] | (i << SIZE4);     //shif from int array    
	}
      tem_tptr = strtok(NULL, " :$,\t\n");                   //RT
      if(tem_tptr != NULL)                                 //get next word        
	{
	  num = strtod(tem_tptr, &error);                   //convert to int
	  obj_table[r] =  obj_table[r] | (num << SIZE5);      //shift from int array
	}
      tem_tptr = strtok(NULL, " :$,\t\n");                   //I.O
      if(tem_tptr != NULL)                                 //get next word  
	{
	  num = strtod(tem_tptr, &error);                 //converting to int
	  obj_table[r] =  obj_table[r] | (num << 0);     //shift from int array
	}
    }
}


/* I-FORMAT  */
//opcode addi, subi, muli, divi, and modi. use three oprands/ the first two are
//registers and the last is an interger.
//takes in 2 char array, 3 ints
void I_rri(char temp_line2[], int obj_table[], int i, int r, int flag0)
{ 
  char *tem_tptr;                                 //pointer to token

  char *error;                                   //strtod
  int num = 0;                                   //for converting


  tem_tptr = strtok(temp_line2, " ():$,\t\n");         //get 1st word  
  if(flag0 == LINE_NUM)                                    //if flag == 1
    {
      tem_tptr = strtok(NULL, " ():$,\t\n");         //get next word
      flag0 = 0;                                  //set to 0
    }
  if(flag0 == 0)                                //if its == to 0
    {
      if(tem_tptr != NULL)                                   //Opcode
	{
	  obj_table[r] = obj_table[r] | (i << SIZE4);    //shift to int array
	}
      tem_tptr = strtok(NULL, " ():$,\t\n");                  //RT
      if(tem_tptr != NULL)                                  //if its not empty  
	{
	  num = strtod(tem_tptr, &error);                 //convert to int
	  obj_table[r] =  obj_table[r] | (num << SIZE5);   //shift from int array
	}
      tem_tptr = strtok(NULL, " ()$,\t\n");                    //RS
      if(tem_tptr != NULL)                                      //if its empty
	{
	  num = strtod(tem_tptr, &error);                   //convert to int
	  obj_table[r] =  obj_table[r] | (num << SIZE2);     //shift from int array
	}
      tem_tptr = strtok(NULL, " ()$,\t\n");                     //I.O
      if(tem_tptr != NULL)                                //if its not empty    
	{
	  num = strtod(tem_tptr, &error);              //convert to int
	  obj_table[r] =  obj_table[r] | (num << 0);   //shift to int array
	}
    }
}


/* I-FORMAT  */
//take care of i format part 3
//opcode lwb, sub use the base + displacement from of addressing.
//take in 2 char arrays, 3 ints
void I_rir(char temp_line2[], int obj_table[], int i, int r, int flag0)
{ 
  char *tem_tptr;                               //pointer to token
  
  char *error;                                 //strtod
  int num = 0;                                 //converting
  
  
  tem_tptr = strtok(temp_line2, " ():$,\t\n");   //get 1st word
  if(flag0 == LINE_NUM)                          //if flag == 1
    {
      tem_tptr = strtok(NULL, " ():$,\t\n");     //get next word
      flag0 = 0;                                 //if its = 0
    }
  if(flag0 == 0)                                  //if flag == 0
    {
      if(tem_tptr != NULL)                                //Opcode
	{                                      
	  obj_table[r] = obj_table[r] | (i << SIZE4);        //shift from int array
	}
      tem_tptr = strtok(NULL, " ():$,\t\n");           //get next word
      if(tem_tptr != NULL)                                  //RT
	{
	  num = strtod(tem_tptr, &error);                //convert to int
	  obj_table[r] =  obj_table[r] | (num << SIZE5);    //shift from int array
	}
      tem_tptr = strtok(NULL, " ()$,\t\n");                //I.O
      if(tem_tptr != NULL)                               //if its not empty
	{
	  num = strtod(tem_tptr, &error);              //convert to int
	  obj_table[r] =  obj_table[r] | (num << 0);   //shift 0 place
	}
      tem_tptr = strtok(NULL, " ()$,\t\n");                 //RS
      if(tem_tptr != NULL)                             //if its empty
	{
	  num = strtod(tem_tptr, &error);             //convert to int
	  obj_table[r] =  obj_table[r] | (num << SIZE2);  //shift from int array
	}
    }
}



/******************** J-FORMAT ***************************************/
//take care of j-format part 1
//opcodes lwa, swa have two operands, namely a register and a symbol.
//take in 2 char arrays, 3 ints
void J_ra(char temp_line2[], int obj_table[], int i, int r, int flag0, 
	   struct data_table *buff1)
{
  int  li = 0;                              //sifting

  char *tem_tptr;                          //pointer for token
  
  char *error;                               //strtod
  int num = 0;                                 //converting
  
  tem_tptr = strtok(temp_line2, " :$,\t\n");            //get 1st word
  if(flag0 == LINE_NUM)                              //if flag  == 1 
    {
      tem_tptr = strtok(NULL, " :$,\t\n");             //get next word
      flag0 = 0;                                    //set flag = 0
    }
  if(flag0 == 0)                                      //if flag == 0
    {
      if(tem_tptr != NULL)                           //if not empty
	{  
	  obj_table[r] = obj_table[r] | (i << SIZE4);     //opcode shifting
	}
      tem_tptr = strtok(NULL, " :$,\t\n");                      //RT
      if(tem_tptr != NULL)                                     //if not empty
	{  
	  num = strtod(tem_tptr, &error);                 //convert to int
	  obj_table[r] =  obj_table[r] | (num << SIZE4);      //shift rt
	}
      tem_tptr = strtok(NULL, " :$,\t\n");                  //get next word
      if(tem_tptr != NULL)                                 //if not empty
	{
	  if(check_label(tem_tptr, &li) == 0)            //check function == 0
	    {     
	      obj_table[r] = obj_table[r] | (li << 0);   //shif from int array
	    }
	  else
	    {
	      insert_wro_label(tem_tptr);            //insert in linked list error
	      buff1->print_flag = LINE_NUM;                //set flag to 1
	    }
	}
    }
}


//j-format part 2
//opcode j and jal have only one operand, namely a symbol.
//take in 2 char array, and 3 ints
void J_a(char temp_line2[], int obj_table[], int i, int r, int flag0, 
	 struct data_table *buff1)
{
  char *tem_tptr;                          //point to token

  char *error;                               //strtod
  int num = 0;                               //converting
  int li = 0;                                //shifting


  tem_tptr = strtok(temp_line2, " :$,\t\n");               //opcode
  if(flag0 == LINE_NUM)                                  //if flag == 1 
    {
      tem_tptr = strtok(NULL, " :$,\t\n");               //opcode
      flag0 = 0;                                        //set flag = 0
    }
  if(flag0 == 0)                                        //if flag == 0
    {
      if(tem_tptr != NULL)                             //if line empty
	{
	  obj_table[r] = obj_table[r] | (i << SIZE4);     //shift from int array
	}
      tem_tptr = strtok(NULL, " :$,\t\n");               //opcode
      if(tem_tptr != NULL)                              //if its not empty
	{
	  if(check_label(tem_tptr, &li) == 0)    //check if function === 0
	    {
	      obj_table[r] = obj_table[r] | (li << 0);   //shift from int arry
	    }
	  else
	    {
	      insert_wro_label(tem_tptr);     //else its eoor. and call function
	      buff1->print_flag = LINE_NUM;  //set flag = 1
	    }
	}
    }
}

//j-format part 3
//opcodes jeq,jne,jlt,jle,jgt,jge have three operands. the first two are register
//and the last is a symbol.
//takes in 2 char array and 3 ints
void J_rra(char temp_line2[], int obj_table[], int i, int r, int flag0,
	   struct data_table *buff1)
{
  char *tem_tptr;                                        //pointer for token

  char *error;                                          //strtod
  int num = 0;                                          //for converting
  int li = 0;                                              //for shifting

  tem_tptr = strtok(temp_line2, " :$,\t\n");               //opcode
  if(flag0 == LINE_NUM)                                 //if flag == 1 
    {
      tem_tptr = strtok(NULL, " :$,\t\n");               //opcode
      flag0 = 0;                                        //set flag = 0
    }
  if(flag0 == 0)                                        //if flag == 1
    {
      if(tem_tptr != NULL)                          //if its not empty
	{
	  obj_table[r] = obj_table[r] | (i << SIZE4);   //shif from int array       
	}
      tem_tptr = strtok(NULL, " :$,\t\n");               //opcode
      if(tem_tptr != NULL)                               //RT
	{                                           //get next word
	  num = strtod(tem_tptr, &error);             //convert to int
	  obj_table[r] =  obj_table[r] | (num << SIZE5);  //shift from int array
	}
      tem_tptr = strtok(NULL, " :$,\t\n");               //RS
      if(tem_tptr != NULL)                               //get next word
	{
	  num = strtod(tem_tptr, &error);
	  obj_table[r] =  obj_table[r] | (num << SIZE2); //sift from int array
	}
      tem_tptr = strtok(NULL, " :$,\t\n");               //adress
      if(tem_tptr != NULL)                             //get next word
	{
	  if(check_label(tem_tptr, &li) == 0)         //call function, == 0
	    {
	      obj_table[r] = obj_table[r] | (li << 0); //shif from int array
	    }
	  else
	    {
	      insert_wro_label(tem_tptr);  //create error linked list
	      buff1->print_flag = LINE_NUM;        //set flag = 1
	    }
	}
    }
}


/* check right label error */
//check if its a valid label or not
//return int, takes in char pointer and int pointer
int check_label(char *tem_tptr, int *li)
{
  struct node *cur_node = head;        //point to head
  
  if(cur_node == NULL) 
    {
      //if empty do nothing
    }
  else
    {
      while(cur_node != NULL)            //not empty
	{
	  if(strcmp(cur_node->label, tem_tptr) == 0) //cmp label with tptr
	    { 
	      *li = cur_node->line;        //lc-value
	      return 0;                 //in list
	    }
	  cur_node = cur_node->next;      //next node
	}
    }
  return 1;                             //not in list
}

/************************************************************************************
File ./makefile Starts Here:
************************************************************************************/
#The following rule tells make about possible suffixes
#(extensions) of file names.

.SUFFIXES: .c .o

#The following definition of CC ensures that
#gcc will be used to compile the C source files.

CC = gcc

#The following definition of CFLAGS ensures that
#the debugger can be used with the executable file (sample)
#created by running make.

CFLAGS = -g

#The following rule tells make how a ".o" file should
#be created from the corresponding ".c" file.
#Note that the "-c" option must be used here since we are
#compiling source files separately. (Note that the line
#following the ".c.o:" line begins with the "tab" character.)

.c.o:
	$(CC) $(CFLAGS) -c $<

#Dependency rule for the default target and how the
#default target is to be created. (Note that the line
#following the dependency rule begins with the "tab"
#character.)

p4: f_main.o f_funct.o 
	gcc f_main.o f_funct.o -o p4

#Dependency rules for other targets. (We don't need to
#specify how these targets are created since we have already
#given a general rule for creating a ".o" file from the
#corresponding ".c" file.)

f_main.o: h_define.h h_struct_def.h h_global.h h_prototype.h 
f_funct.o: h_define.h h_struct_def.h h_extern.h h_prototype.h

#Target for removing unnecessary files.

clean:
	rm -f *.o core
