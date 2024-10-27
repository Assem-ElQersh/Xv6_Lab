#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if (argc != 2) {
    fprintf(2, "Usage: sleep <ticks>\n");
    exit(1);
  }

  int ticks = atoi(argv[1]);  // Convert the argument to an integer
  sleep(ticks);  // Call the sleep system call for the specified ticks

  exit(0);  // Exit gracefully
}
