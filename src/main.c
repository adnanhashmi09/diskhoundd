#include <stdio.h>
#include <stdlib.h>
#include <sys/statvfs.h>

#include "cli.h"
#include "config.h"
#include "logger.h"
#include "signal_handler.h"
#include "watchdog.h"

char *ProgramTitle = "diskhound";

int main(int argc, char **argv) {
  const char *config_file_path = NULL;
  char **paths = NULL;

  int number_of_paths = init_cli(argc, argv, &config_file_path, &paths);
  register_exit_signals();

  init_config(config_file_path, number_of_paths);

  init_logger(config.log_file_path);

  watchdog_start(&paths, &ProgramTitle);
}
