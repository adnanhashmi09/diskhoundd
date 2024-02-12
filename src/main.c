#include <sys/statvfs.h>

#include "cli.h"
#include "config.h"
#include "logger.h"
#include "signal_handler.h"
#include "watchdog.h"

char *ProgramTitle = "diskhound";

int main(int argc, char **argv) {
  init_cli(argc, argv);
  register_exit_signals();
  init_logger(config.log_file_path);
  watchdog_start(&ProgramTitle);
  // TODO: FREE MEMORY WHERE NECESSARY
}
