#include "exit_codes.h"
#include <stdio.h>
#include <stdlib.h>

void signal_handler(int signal){
  fprintf(stdout, "\nSignal recieved. Cleaning up.\n");
  exit(EXT_SUCCESS);
}
