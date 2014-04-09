/*
  Ikhlas Ahmed
  Email - ia787858@albany.edu
  Main method - this method will read from input file and set up tree, 
  by calling insert method. Than it will compute information and write
  all the information on to a output file.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


/* constants.h */
#define COMMAND_ARG   3 
#define IN_FILE_ARG   1  
#define OUT_FILE_ARG  2  

#define SSIZE         16 
#define ZERO          0 
/* Struct_def.h */
struct tree_node
{
  char line[SSIZE];            
  struct tree_node *left_child; 
  struct tree_node *right_child; 
}; struct tree_node *head;  



struct tree_node*  insert(struct tree_node* ,char *);
int max_string(struct tree_node *);
int max_height(struct tree_node *);
int max_leaves(struct tree_node *);


/* argc(how many command entered-output(3)) */
/* argv(point to 1st char-output(point to p)) */
int main(int argc, char *argv[])
{

  int count0 = ZERO;
  int count1 = ZERO;
  int count2 = ZERO;
  int count3 = ZERO;
  int count4 = ZERO;
  int count5 = ZERO;
  int count6 = ZERO;


  char line[SSIZE];
  

  FILE *finp;
  FILE *foutp;
  


  /*** Check for 3 commands ***/
  if(argc == COMMAND_ARG) 
    {
      /*** Open and read input file ***/
      if((finp = fopen(argv[IN_FILE_ARG], "r")) == NULL)
	{
	  fprintf(stderr, "Could not open file: %s.\n", argv[IN_FILE_ARG]);
	  exit(1);
	}
      /*** Open and write output file ***/
      if((foutp = fopen(argv[OUT_FILE_ARG], "w")) == NULL)
	{
	  fprintf(stderr, "Could not open file: %s.\n", argv[OUT_FILE_ARG]);
	  exit(1);
	}



     
         /* Read lines from input file */
	  while(fscanf(finp, "%s", line) != EOF)
	    {
	      //call insert method and store in head
	      head = insert(head,line);
	    }
	  /*** Call funct and store in counts ***/
	  count0 = max_string(head);  //string
	  count1 = max_height(head);  //height
	  count2 = max_leaves(head);  //leaves
	  count3 = max_height(head->left_child);  //left leave
	  count4 = max_string(head->left_child);  //right string
	  count5 = max_height(head->right_child); //righ leave
	  count6 = max_string(head->right_child); //right string
	  
	  /* If height is negitve number than change to zero */
	   if(count1 <= ZERO) { count1 = ZERO; }
	   if(count3 <= ZERO) { count3 = ZERO; }
	   if(count5 <= ZERO) { count5 = ZERO; }




/*** Write in ouput file ***/
fprintf(foutp,"Total number of strings in the input file: %d\n", count0);
fprintf(foutp,"The height of the binary search tree: %d\n", count1);
fprintf(foutp,"The number of leaves in the binary search tree: %d\n", count2);
fprintf(foutp,"The height of the left subtree of the root: %d\n", count3);
fprintf(foutp,"The number of strings in the left subtree of the root: %d\n",count4);
fprintf(foutp,"The height of the right subtree of the root: %d\n", count5); 
fprintf(foutp,"The number of string in the right subtree of the root: %d\n",count6);	  
	

/* Close input file */
 if(fclose(finp) == EOF)
   {
     fprintf(stderr, "Error in colsing file %s.\n", argv[IN_FILE_ARG]);
   }
 /* Close output file */
 if(fclose(foutp) == EOF)
   {
     fprintf(stderr, "Error in closing file %s.\n", argv[OUT_FILE_ARG]);
   }
    }
  else
    {
      //Error - enter three commands
      printf("Error - Enter three commands.\n");
      fflush(stdout);
    }
   return 0;
}
















struct tree_node* insert(struct tree_node *h, char *li)
{
  //base case - if head is empty 
  if(h == NULL)
    {
      //creat memory for h
      h = (struct tree_node *) malloc(sizeof(struct tree_node));
      if(h == NULL)
	{
	  printf("Node allocation failed.\n");  fflush(stdout); 
	  exit(1);
	}
      strcpy(h->line,li);   //store li in head
      h->left_child = NULL;  //set left child to null
      h->right_child = NULL; //set right child to null
      return h;              //return h;
    }
  //else = head is not empty
  else
    {
      //right side of tree
      if(strcmp(h->line, li) < 0)
	{
	  //insert on right side
	  h->right_child = insert(h->right_child, li);
	}
      //left side of tree
      else
	{
	  //insert on left side
	  h->left_child = insert(h->left_child, li);
	}
    }
}//end of method

















/********************************************************************** 
void insert(char *li)
{
  struct tree_node *cur_node = head;
  struct tree_node *new_node;
  

  
  if(cur_node == NULL)
    {
     
      head = (struct tree_node *) malloc(sizeof(struct tree_node));
      if(head == NULL)
	  {
	  printf("Node allocation failed.\n");  fflush(stdout); 
	  exit(1);
	  }
      strcpy(head->line,li);
      head->left_child = NULL;
      head->right_child = NULL;
    }
  
    
  else
    {
       //right side of tree
      if(strcmp(cur_node->line, li) < 0)
	{
	    insert(cur_node->right_child, li);
	   new_node = (struct tree_node *) malloc(sizeof(struct tree_node));
      if(new_node == NULL)
	  {
	  printf("Node allocation failed.\n");  fflush(stdout); 
 	 exit(1);
	  }
      strcpy(new_node->line,li);
      new_node->left_child = NULL;
      new_node>right_child = NULL;
	}
      //left side of tree
      else
	{
	  insert(h-head>left_child, li);
       new_node = (struct tree_node *) malloc(sizeof(struct tree_node));
      if(new_node == NULL)
	  {
	  printf("Node allocation failed.\n");  fflush(stdout); 
	  exit(1);
	  }
      strcpy(new_node->line,li);
      new_node>left_child = NULL;
      new_node>right_child = NULL;
	} 
    }               
}
******************************************************************************/






int max_string(struct tree_node *h)
{
  //return 0 if head is empty
  if(h == NULL)
    {
      return 0;
    }
  //return 1 if there is one node
  else if(h->left_child == NULL && h->right_child == NULL)
    {
      return 1;
    }
  //recursive call to count all the nodes in tree
  else 
    {
      //count left tree nodes and add the all right tree nodes.
      //add 1 for head/root
      return (max_string(h->left_child)) +
	     (max_string(h->right_child)) + 1;
    }
}







/* Height of the binary search tree */
/* MAX_HEIGHT METHOD - it will  find the height for left subtree and right subtree.
   Than it find the biggest value and return it to main method. */
/* Parameter - It will take node *h for starting point, which is the head/root */
int max_height(struct tree_node *h)
{
  int left = 0;
  int right = 0;

  //base case if its empty return -1
  if(h == NULL)
    {
      return -1;
    }
  //store value in left and right
  else
    {
      //count the height for left subtree and store in left valuable
      left = max_height(h->left_child);
      //count the height for right subtree and store in right valuable
      right = max_height(h->right_child);
    }
  //find biggest number and return it to main
  if(left > right)
    {
      return left+1;
    }
  else
    {
      return right+1;
    }
}




/* Number of leaves in the binar search tree: */
/* MAX_LEAVES - it will count leaves and return it to main method*/
/* Parameter - It will take node *h for starting point, which is the head/root */
int max_leaves(struct tree_node *h)
{
  //no leaves
  if(h == NULL)
    {
      return  0;
    }
  //only head is a leaf
  else if(h->left_child == NULL && h->right_child == NULL)
     {
       return  1;
     }
  //recursve call to find leaves in tree
  else 
     {
       //count leaves from left and right subtree
      return (max_leaves(h->left_child)) +
              (max_leaves(h->right_child));
     }
}
