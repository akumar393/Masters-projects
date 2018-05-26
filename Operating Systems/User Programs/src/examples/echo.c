#include <stdio.h>
#include <syscall.h>


int
main (int argc, char *argv[]) 
{
  int i;

  //test_name = "args";

  printf ("begin");
  printf ("argc = %d", argc);
  for (i = 0; i <= argc; i++)
    if (argv[i] != NULL)
      printf ("argv[%d] = '%s'", i, argv[i]);
    else
      printf ("argv[%d] = null", i);
  printf ("end");

  return 0;
}
