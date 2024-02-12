#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "exit_codes.h"

#define MAX_CONFIG_LINE_LENGTH 255

struct Config config = {NULL, NULL, NULL};

void trim(char **line) {
  while (isspace(**line)) {
    (*line)++;
  }

  char *end = (*line) + strlen((*line)) - 1;
  while (end > (*line) && isspace(*end)) {
    end--;
  }

  *(end + 1) = '\0';
}

void set_value_if_valid_key(char *key, char *value) {
  if (strcmp(key, "log_file_path") == 0) {
    config.log_file_path = strdup(value);
  }

  if (strcmp(key, "icon_path") == 0) {
    config.icon_path = strdup(value);
  }
  if (strcmp(key, "critical_disk_perc") == 0) {
    config.critical_disk_perc = atoi(value);
  }
}

void init_config(char **config_file, char ***paths, int number_of_paths) {
  config.log_file_path = "/var/log/diskhoundd.log";
  config.critical_disk_perc = 20;
  config.path_list_size = number_of_paths;
  config.config_file_path = NULL;
  config.icon_path = NULL;

  if (config_file == NULL) {
    return;
  }

  FILE *file = fopen(*config_file, "r");
  if (file == NULL) {
    fprintf(stderr, "config file %s not found.\n", *config_file);
    exit(EXIT_CONFIG_FILE_NOT_FOUND);
  }
  config.config_file_path = strdup(*config_file);
  // free(*config_file);

  config.paths =
      (const char **)malloc(config.path_list_size * sizeof(const char *));

  if (config.paths == NULL) {
    perror("Memory allocation failed");
    exit(EXIT_FAILURE);
  }


  for (int i = 0; i < config.path_list_size; i++) {
    config.paths[i] = strdup((*paths)[i]);
    if (config.paths[i] == NULL) {
      perror("Memory allocation failed");
      exit(EXIT_FAILURE);
    }
    // free((*paths)[i]);
  }

  char line[MAX_CONFIG_LINE_LENGTH];
  while (fgets(line, sizeof(line), file)) {
    char *newline = strchr(line, '\n');
    if (newline != NULL) {
      *newline = '\0';
    }

    char *key = strtok(line, "=");
    char *value = strtok(NULL, "=");

    if (key != NULL && value != NULL) {
      trim(&key);
      trim(&value);
      set_value_if_valid_key(key, value);
    }
  }
}
