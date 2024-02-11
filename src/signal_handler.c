#include <signal.h>
#include <stdlib.h>

#include "logger.h"

void signal_handler(int signal) {
  Log(INFO, "Signal recieved. Cleaning up.\n");
  exit(EXIT_SUCCESS);
}

void register_exit_signals() {
  signal(SIGABRT, signal_handler);
  signal(SIGINT, signal_handler);
  signal(SIGTERM, signal_handler);
}
