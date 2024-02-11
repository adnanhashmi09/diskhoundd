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
  const char *path = NULL;

  init_cli(argc, argv, &config_file_path, &path);
  register_exit_signals();

  struct Config *config = init_config(config_file_path);
  // printf("%s\n", config->log_file_path);
  // printf("%s\n", config->config_file_path);
  // printf("%s\n", config->icon_path);
  return 0;

  init_logger(config->log_file_path);

  struct statvfs stat;
  watchdog_start(&path, &ProgramTitle, &stat);
}
