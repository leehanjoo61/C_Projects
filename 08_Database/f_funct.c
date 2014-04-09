/*
 Ikhlas Ahmed
ia787858
*/

//includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//header files
#include "h_define.h"
#include "h_struct_def.h"
#include "h_externs.h"
#include "h_prototype.h"


/* this fuction build a linked it take in line2 array and dont output any thing*/
void build_linked_list(char line2[])
{
  //two structs and a pointer for token
  struct node *cur_node = head;
  struct node *new_node;
  char *tptr2;
  
  /* if cur node is empty creat head*/
       if(cur_node == NULL)
	{
	  //creat memory for head
	  head = (struct node *) malloc(sizeof (struct node));
	  if(head == NULL)
	    {
	      printf("Node allocation failed.\n"); fflush(stdout); 
	      exit(1);
	    }
	  //get 1st word and copy in head
	  tptr2 = strtok(line2," ");
	  if(tptr2 != NULL) 
	    {
	      strcpy(head->attribute, tptr2); 
	    }
	  //get 2nd word and copy in head
	  tptr2 = strtok(NULL, " ");
	  if(tptr2 != NULL)
	    {
	      strcpy(head->type, tptr2);
	    }
	  //get 3rd word and copy in head
	  tptr2 = strtok(NULL, " ");
	  if(tptr2 != NULL) 
	    { 
	      strcpy(head->space, tptr2);
	    }
	  head->next = NULL;  //set next nodeto null
	}
       //do this if head is not empty
      else
	{
	  //go in end of list
	  while(cur_node->next != NULL)
	    {
	      cur_node = cur_node->next;    
	    }
	  //create nre node
	      new_node = (struct node *) malloc(sizeof (struct node));
	      if(new_node == NULL)
		{
		  printf("Node allocation failed.\n"); fflush(stdout);
		  exit(1);
		}
	      //get 1st word and copy in new node
	      tptr2 = strtok(line2," ");
	      if(tptr2 != NULL) 
		{
		  strcpy(new_node->attribute, tptr2);
		}
	      //get 2nd word and copy in new node
	      tptr2 = strtok(NULL," ");
	      if(tptr2 != NULL) 
		{
		  strcpy(new_node->type, tptr2);
		}
	      //get 3rd word and copy in new node
	      tptr2 = strtok(NULL, " ");
	      if(tptr2 != NULL)
		{
		  strcpy(new_node->space, tptr2);
		}
	      //sset new node next to null
	      new_node->next = NULL;
	      //set cur next to new node
	      cur_node->next = new_node;
	}       
}//end of method









/* del linked list */
void del_linked_list()
{
  //creaate node
  struct node *cur_node = head;
  //if empty
  if(cur_node == NULL)
    {
      printf("List is empty.\n");
      fflush(stdout);
    }
  //not empty
  else
    {
      //loop linked list and del
      head = NULL;
      while(cur_node != NULL)
	{
	  cur_node = NULL;
	  //  cur_node = cur_node->next;
	}
    }
}







/* this function print tuplen command */
void print_tuplen()
{
  //variabnle to add number
  int num = 0;
  int total = 0;
  char *error;  //for strtod

  struct node *cur_node = head;

  //if list is empty
  if(cur_node == NULL)
    {
      printf("There are no tuplen.\n");
      fflush(stdout);
    }
  //nod empty
  else
    {
      //loop linked list and all all number
      while(cur_node != NULL)
	{
	  num = strtod(cur_node->space, &error);
	  total = total + num;
	  cur_node = cur_node->next;
	}
      //print anser
      printf("tuplen: %d\n\n", total); fflush(stdout);
    }
}









/* print infattr commadn and it take in attrname array*/
void print_infattr(char attrname[])
{
  int flag3 = 0; //boolean 

  struct node *cur_node = head;  //creat node

  //if list is empty
  if(cur_node == NULL)
    {
      printf("infattr is empty\n"); fflush(stdout);
    }
  //not empty
  else
    {
      //loop linked list
      while(cur_node != NULL)
	{
	  //compare two vaue
	  if(strcmp(attrname, cur_node->attribute) == 0)
	    {
	      //check to see if its i or s than print it
	      if(strcmp("I", cur_node->type) == 0)
		{
		  printf("Attribute type: %s\n",cur_node->type); fflush(stdout);
		}
	      else
		{
		  printf("Attribute typee: %s\n",cur_node->type); fflush(stdout);
		}
	      printf("Attribute length: %s\n\n",cur_node->space); fflush(stdout);
	      flag3 = 0;   
	      break;   //exit from loop
	    }
	  else
	    {
	      flag3 = T_SIZE;  //boolean flag
	    }
	  cur_node = cur_node->next; //next node
	}
    
      //if boolean flag is 1 than its error
      if(flag3 == 1)
	{
	  printf("Error: Invalid attribute -- %s\n\n",attrname); 
	  fflush(stdout);
	}
    }//end of else
}//end of method







/* get length of tuple and return reslut*/
int len_tuple()
{
  //number for adding
  int num = 0;
  int total = 0;
  char *error;   //for atrtod

  struct node *cur_node = head;

  //if linked list is empty
  if(cur_node == NULL)
    {
      printf("There are no tuplen.\n");
      fflush(stdout);
    }
  else
    {
      //loop linked list and add all the numbers
      while(cur_node != NULL)
	{
	  num = strtod(cur_node->space, &error);
	  total = total + num;
	  cur_node = cur_node->next;  //next node
	}
    }
  return total;  //return resutlt
}










/* find what line is attribute is on . take inchar  attrname[] and return int*/
int find_row(char attrname[])
{
  struct node *cur_node = head;  //creat node
  int count = T_SIZE;    //counter
  //if list is empty
  if(cur_node == NULL)
    {
      printf("infattr is empty\n"); fflush(stdout);
    }
  //list is not empty
  else
    {
      //loop linked list
      while(cur_node != NULL)
	{
	  //compter two value and break
	  if(strcmp(attrname, cur_node->attribute) == 0)
	    {
	      break;
	    }
	  else
	    {
	      count++; //count roww
	    }
	 
	  cur_node = cur_node->next;
	}
    }//end of else
  return count;   //return count
}//end of method










/* get starting positon take in char attrname[] and return int*/
int start_pos(char attrname[])
{
  int flag3 = 0;
  int r_num = 0;
  int l_num = 0;
  int num = 0;

  char *error; 

  struct node *cur_node = head;
  
  //if its empty
  if(cur_node == NULL)
    {
      printf("infattr is empty\n"); fflush(stdout);
    }
  else
    {
      //loop linked list
      while(cur_node != NULL)
	{
	  //compare two value if true get starting pos and break
	  if(strcmp(attrname, cur_node->attribute) == 0)
	    {
	      r_num = strtod(cur_node->space, &error);
	      r_num = r_num + l_num;
	      break;
	    }
	  else
	    {
	      num = strtod(cur_node->space, &error);
	      l_num = l_num + num;
	    }
	 
	  cur_node = cur_node->next;
	}
    }//end of else
  return  l_num; 
}//end of method






/* it will find col and it take char attrname[] and return int*/
int find_col(char attrname[])
{
  char *error;
  int r_num;  


  struct node *cur_node = head;
  //if list is empty
  if(cur_node == NULL)
    {
      printf("infattr is empty\n"); fflush(stdout);
    }
  //if not empty
  else
    {
      //loop linked list
      while(cur_node != NULL)
	{
	  //compare two value if true get length
	  if(strcmp(attrname, cur_node->attribute) == 0)
	    {
	      r_num = strtod(cur_node->space, &error);
	    }
	  cur_node = cur_node->next;
	}
    }//end of else
      return r_num;
    
}//end of method







/* check to see if attrname is in file and it take char arrtname[] and return int*/
int check_att(char attrname[])
{
  struct node *cur_node = head;

  //if list is empty
  if(cur_node == NULL)
    {
      printf("list is empty\n"); fflush(stdout);
    }
  //not empty
  else
    {
      //loop linked list and computer two value
      while(cur_node != NULL)
	{
	  //if true return 1 else 0
	  if(strcmp(attrname, cur_node->attribute) == 0)
	    {
	    return 1;
	    }
	 
	  cur_node = cur_node->next;
	}
    }//end of else
  return 0;
}//end of method









/* return 1 for string 0 for int*/
int check_string(char attrname[])
{
  struct node *cur_node = head;
  //if empty
  if(cur_node == NULL)
    {
      printf("list is empty\n"); fflush(stdout);
    }
  //not empty
  else
    {
      //loop linkedl list 
      while(cur_node != NULL)
	{
	  //compare two value 
	  if(strcmp(attrname, cur_node->attribute) == 0)
	    {
	      //if its I return 0
	      if(strcmp("I", cur_node->type) == 0)
		{
		  return 0;
		}
	      else
		{
		  return 1;
		}
	    }
	  cur_node = cur_node->next;
	}
    }
}
