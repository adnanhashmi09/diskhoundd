#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "config.h"
#include "exit_codes.h"
void init_cli(int argc, char **argv) {
  char *config_file_path = NULL;
  char **paths = NULL;

  int opt;
  while ((opt = getopt(argc, argv, "c:")) != -1) {
    switch (opt) {
    case 'c':
      config_file_path = optarg;
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

  paths = (char **)malloc((argc - optind) * sizeof(char *));
  if (paths == NULL) {
    perror("Memory allocation failed");
    exit(EXIT_FAILURE);
  }

  for (int i = optind; i < argc; i++) {
    paths[i - optind] = argv[i];
  }

  init_config(&config_file_path, &paths, argc - optind);
}
