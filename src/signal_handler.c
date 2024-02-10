#include <stdlib.h>
#include "logger.h"

void signal_handler(int signal){
  Log(INFO, "Signal recieved. Cleaning up.\n");
  exit(EXIT_SUCCESS);
}
