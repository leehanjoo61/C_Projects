/**********************************************/
/****** NAMES ******************** COMMANDS ***/
/* Insert Command                 : ins str   */ 
/* Delete Command                 : del str   */
/* Forced Delete Command          : fde val   */
/* Print Statistics Command       : pst       */
/* Print List Command             : prl       */
/* Print using Count Range Command: pcr v1 v2 */
/* Print Prefix Command           : ppr str   */
/* Print Suffix Command           : psu str   */
/* End Command                    : end       */
/***********************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define CSIZE 4
#define SSIZE 11


/* Struct for each node in the linked list */
struct node
{
  int count;
  char symbol[SSIZE];
  struct node *next;
};
struct node *head;
 

  /* Prototypes for the functions */
  void insert(char *);         
  void delete(char *);          
  void forced_delete(int value);      
  void print_stats();           
  void print_list();            
  void print_count(int, int);  
  void print_prefix(char pre[]);   
  void print_suffix(char suf[]); 
  void sort_list();


/****************
** Main Method **
****************/

int main(void)                
{
  int count;
  char symbol[SSIZE];
  char cmd[CSIZE];

  int v1;
  int v2;

  /* Enter commands */
  printf("Command? "); fflush(stdout);
  scanf("%s", cmd);
  /* Check for command*/
  while(strcmp(cmd,"end") != 0)
    {
     /* check which function to use */
     if(strcmp(cmd,"ins") == 0) { scanf("%s", symbol); insert(symbol); }
     if(strcmp(cmd,"del") == 0) { scanf("%s", symbol); delete(symbol); }
     else if(strcmp(cmd,"fde")==0){scanf("%d",&count); forced_delete(count); } 
     if(strcmp(cmd,"pst") == 0) { print_stats();}
     if(strcmp(cmd,"prl") == 0) { print_list(); }
     if(strcmp(cmd,"pcr") == 0) { scanf("%d %d",&v1,&v2); print_count(v1,v2); }
     if(strcmp(cmd,"ppr") == 0) { scanf("%s", symbol); print_prefix(symbol);}
     if(strcmp(cmd,"psu") == 0) { scanf("%s", symbol); print_suffix(symbol);}
     printf("Command? "); fflush(stdout);
     scanf("%s", cmd);
    }// End of While Loop
    
  return 0;
}// End of main method





     /***************************
     ****** Insert Method *******
     ***************************/

     void insert(char *sym)
     {
       /* Set current node to head, create new new node, and a boolean */
       struct node *cur_node = head;
       struct node *new_node;
       int in_list = 0;
       
       /* If list is empty, then insert in head */
       if(cur_node == NULL)
	 {
	   // create memory for head, also test if head equal to NULL
	   head = (struct node *) malloc(sizeof(struct node));
	   if(head == NULL)
	     {
	       printf("Node allocation failed.\n"); fflush(stdout);
	       exit(1);
	     }
	   /* insert sym inside head->symbol and change count to one */
	   strncpy(head->symbol, sym, SSIZE);
	   head->count = 1;
	   head->next = NULL;
	 }
       
       /* do this part if list is not empty */
       else
	 {
	   // Insert inside of list
	   // Check if sym is in list
	   // Loop though all list 
	   while(cur_node != NULL)                        
	     {
	       // if list is in middle add one count
	       if(strcmp(sym, cur_node->symbol) == 0)
		 {
		   cur_node->count++;
		   in_list++;
		   /***** Sort Method *****/
		   sort_list();
		 }
	       //cur_node is bottom of the list right now
	      cur_node = cur_node->next;
	     }// End of while loop


	   /* Do this part if you want to insert in end of list */
	   if(in_list == 0)
	     {
	       // put cur_node at top of the list
	       cur_node = head;
	         //insert at end of list
	         //go at at end of list and put it in cur_node
	         while(cur_node->next != NULL)
		   {
		     //cur_node is at bottom right now
		     cur_node = cur_node->next;
		   }
		     /* Create new memory and test if new_node is NULL */
	             new_node = (struct node *) malloc(sizeof(struct node));
		     if(new_node == NULL)
		       {
			 printf("Node allocation failed.\n"); fflush(stdout);
			 exit(1);
		       }
		   //link cur_node with new_node and insert inside new_node
		   cur_node->next = new_node;
		   strncpy(new_node->symbol,sym,SSIZE);
		   new_node->count = 1;
		   new_node->next = NULL;
	     }
	 }
     }// End of insert method	 




         /*******************************
         ******** Delete Method *********
	     *******************************/

	 void delete(char *sym)
	 {
	   struct node *cur_node = head;
	   struct node *to_delete;

	   /* Do this if list is empty */
	   if(cur_node == NULL)
	   {
	     printf("List is empty.\n"); fflush(stdout);
	   }
	     

	   /* Do this is list is not empty */
	     else
	     {
	       /* del or minus head node*/
	       if(strcmp(sym, head->symbol) == 0)
		 {
		   if(head->count > 1)
		     {
		       head->count--;
		       /**** Sort Method ***/
		     } 
		   //if cur_node equal one than remove it
		   else if(cur_node->count == 1)
		     {
		       to_delete = head;
		       head = cur_node->next;
		       free(to_delete);
		       to_delete = NULL;
		     }
		 }
	       //check rest of the list
	        while(cur_node != NULL && cur_node->next != NULL)
	        {
		  //If symbol is inside the list
		  if(strcmp(sym, cur_node->next->symbol) == 0)
		    {
		      // if symbol has more than one count
		      if(cur_node->next->count > 1)
			{
			  cur_node->next->count--;
			  /******* Sort Method ********/
			}
		      //if symbol has one count than del it
		      else if(cur_node->next->count == 1)
			{ 
			  to_delete = cur_node->next;
			  cur_node->next = cur_node->next->next;   
			  free(to_delete);
			  to_delete = NULL;
			}
		   }
		   cur_node = cur_node->next;
	        }//End of while loop
			sort_list();
	      } 
	  }//End of delete method






		 /**********************
		  **Forced Delete Method* 
		 ***********************/
	void forced_delete(int value)
	{

	 //Set the struct node cur_node equal to the head
	 struct node *cur_node = head;

	 //If the current node is null return to cmd prompt
	  if(cur_node==NULL)
		return;

	  //if the the head.next value is null set the head
	  //equal to null as well
	  if((head->next==NULL))
		head = NULL;
	  
	  //Else if the given count value of the head is less
	  //than the value stated set the head equal to null
	  else if(head-> count <= value)
		head = NULL;

	  //Else if the nodes after the head count are less
	  //than the given value set the current.next value
	  //equal to null and traverse through the rest of the list
	  else
		while(cur_node!=NULL){
		  if(cur_node-> next-> count <= value)
		  cur_node-> next = NULL;
		  cur_node = cur_node->next;
		}
	}





     /**********************
     ******Prefix Method**** 
     ***********************/

	void print_prefix(char pre[SSIZE]){

	//Variables declared for the total size of the string.
	//Num used as a boolean like value where 0 is false and 1 is true.
	//I declared for use in the for loop
	  int i, size, num; 
	  struct node *cur_node = head;
	  size = strlen(pre);

   //If the head is null return that the list is empty
	  if(head == NULL)
		printf("Empty!.\n");
	  else
	  { 
   //While the head is not null traverse
		while(cur_node != NULL)
		{ 
   // for loop to compare the full string to the string held in the array
   // so it can determine if the string is held in the array value
   // return 0 for false and 1 for true;


		  for(i = 0; i < size; i++)
			{ 
		  if(cur_node->symbol[i] != pre[i]){
		  num = 0;
			break;
			
			}else
		  num = 1;
		  }
	//If num equals 1(true) print the prefix values of the given string
	//and it's integer value.
	//update to the next node;
		  if(num==1)
		printf("%s %i\n", cur_node->symbol, 
		cur_node->count);fflush(stdout);
		cur_node = cur_node->next;
		}
	  }
	}

    





	 /**********************
     ******Suffix Method**** 
     ***********************/

void print_suffix(char suf[SSIZE]){
 //Variables declard for the size of string,
 //a boolean type variable, curr to keep track of
 //the current string value and suf for the given suffix value
   int i, x , curr, size, num; 
   struct node *cur_node = head;
   num = 0;
   
//Find the size of the given suffix
   size = strlen(suf);
  
//If the head is equal to null the list is empty
   if(head == NULL)
    printf("Empty!\n");
  else
  {
//While the current node is not null, traverse.
    while(cur_node != NULL)
    { 
	  x =1;
      curr = strlen(cur_node->symbol);

//Loop through the given string size, if the current
//string -1 and the given i value is equal to the suf string
//" " " " return true and get the suffix
      for(i = 0; i < size; i++)
	  { 
	if(cur_node->symbol[curr - x - i] == suf[size - x - i])
	 
		num = 1;
	  else
	{ 
		num = 0; 
		  
		break; 
		  }
      }
    //If num equals 1(true) print the suffix values of the given string
	//and it's integer value.
	//update to the next node;
    if(num==1)
	printf("%s %i\n", cur_node->symbol, 
	cur_node->count);fflush(stdout);
    cur_node = cur_node->next;
	}
   }
}






	 /**********************
     ******Print Stats**** 
     ***********************/
	void print_stats()
	{

	//Variables declared to find the maximum, minimum, size
    // total number and the average
	//Set a struct node *cur_node = to the head of the list
	int max = 0, min = 0; int size = 0;
	double num = 0,avg = 0;
	struct node *cur_node = head;

	// If the current node is null return all values of 0
	if(cur_node==NULL){
		printf("Number of nodes: %d\n",size);fflush(stdout);
		printf("Maximum: %d\n",max);fflush(stdout);
		printf("Minimum: %d\n",min);fflush(stdout);
		printf("Average: %d\n\n",avg);fflush(stdout);
		return;
	}else

	//Increment size as we traverse the Linked List Nodes
	//Number is added to the ammount of cur_node->count for a total number
	//Increment to the next node of current
	min = head->count;
	while(cur_node!=NULL){
		size++;
		if(min>=cur_node->count)
			min = cur_node->count;
			num += cur_node->count;
			cur_node = cur_node->next;

	}
	//Calculate the average and set the max = to head->count 
	//which returns the maximum value
	avg = num/size;
	max =head->count;
	printf("Number of nodes: %d\n",size);fflush(stdout);
	printf("Maximum: %d\n", max);fflush(stdout);
	printf("Minimum:  %d\n",min);fflush(stdout);
	printf("Average: %.2f\n\n", avg);fflush(stdout);
	}





     /**********************
     ** Print List Method **
     ***********************/
     void print_list()
     {
      struct  node *cur_node = head;
      
      if(cur_node == NULL)
	{
	  printf("The list is empty.\n");fflush(stdout);
	  fflush(stdout);
	}

        else
         {
          while(cur_node != NULL)
	  {
        printf("   %s %d\n", cur_node->symbol, cur_node->count);fflush(stdout);
	   fflush(stdout);
	   cur_node = cur_node->next;
          }//end of while loop
	  printf("\n"); fflush(stdout);fflush(stdout);
         }
     }//end of print list method









       /***********************
       ** Print Count Method **
       ***********************/

       void print_count(int x1, int x2)
       {
        struct node *cur_node = head;
	     
	//print this is list is empty
          if(cur_node == NULL)
          {
            printf("The list is empty.\n"); fflush(stdout);
	    printf("\n");
	  }
	  //print range list
          else
	  {
	    //loop through list 
	   while(cur_node != NULL)
	     {
	       //if its between range than print it
             if ((cur_node->count >= x1) && (cur_node->count <= x2))
	        {
	           printf("     %s %d\n", cur_node->symbol, cur_node->count); 
	           fflush(stdout);
             }
	     cur_node = cur_node->next;
	   }// End of While Loop

	    printf("\n"); fflush(stdout); 

	 }
       }//End of Print Count Method








		/***********************
        ****** Sort Method *****
        ***********************/
	  void sort_list()
	  {
	  struct node *cur_node, *temp; 
	  int loop =1;
	 
	  
	  while(loop==1)
	  { 
	  temp = cur_node = head; 
	  loop = 0;
		

		while(cur_node->next != NULL)
		{ 
	  //case where the next node has a higher count that the cur_node
	  //the nodes will be swapped around to ensure descending order

	    if(cur_node->next->count > cur_node->count)
		{ // mark that the nodes have been swapped
		  loop = 1;

	 //If the cur_node is equal to the head of the list
		if(cur_node == head)
		{ 
	 //The current node is equal to the current.next value
	 //Set the next temp value equal to next current value
	 //Store the next current value in the temp variable
	 //The head is equal to the temp variable and is the current node
		  cur_node = cur_node->next;
		  temp->next = cur_node->next;
		  cur_node->next = temp;
		  head = temp = cur_node;
	
     //Swapping from other positions in the list
     //The next temp value is equal to the next current value
     //The next current value equals the next value of the current.next
     //the current node is equal to the next temp node value
		}else{
		  temp->next = cur_node->next;
		  cur_node->next = cur_node->next->next;
		  temp->next->next = cur_node;
		  cur_node = temp->next;
		  } 
		 } 
		  
	 //If we need to move the temp node value
	 //and it doesn't equal the current node..
	 //The temp value is equal to the next temp value
	 //Finally update the list to keep going
		 if(temp != cur_node)
			temp = temp->next;
		    cur_node = cur_node->next;
		}
	  }
  }

