#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>

#include "exit_codes.h"
void init_cli(int argc, char** argv, const char** config_file_path, const char** path){

  int opt;
  while ((opt = getopt(argc, argv, "c:")) != -1) {
    switch (opt) {
    case 'c':
      *config_file_path = optarg;
      break;
    case '?':
      if (optopt == 'c') {
        fprintf(stderr, "Option -%c requires an argument.\n", optopt);
      } else if (isprint(optopt)) {
        fprintf(stderr, "Unknown option `-%c'.\n", optopt);
      } else
        fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);

      exit(EXIT_WRONG_ARGUMENTS);
    default:
      fprintf(stderr, "Usage: %s [-c] [config filepath] monitor_file_path\n",
              argv[0]);
      exit(EXIT_WRONG_ARGUMENTS);
    }
  }

  if (optind == argc) {
    fprintf(stderr, "Usage: %s [-c] [config filepath] monitor_file_path\n",
            argv[0]);
    exit(EXIT_WRONG_ARGUMENTS);
  }

  *path = argv[optind];
}
