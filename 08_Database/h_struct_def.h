/*ikhlas ahmed
ia787858
*/

//struct to build linked list for .sch files
struct node
{
  char attribute[16];  //size 16
  char type[2];
  char space[10];
  struct node *next;
};
