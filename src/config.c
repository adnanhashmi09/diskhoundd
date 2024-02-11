#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "exit_codes.h"

#define MAX_CONFIG_LINE_LENGTH 255

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

void set_value_if_valid_key(char *key, char *value, struct Config *config) {
  if (strcmp(key, "log_file_path") == 0) {
    // free((char *)config->log_file_path);
    config->log_file_path = strdup(value);
  }

  if (strcmp(key, "icon_path") == 0) {
    // free((char *)config->icon_path);
    config->icon_path = strdup(value);
  }
}

struct Config *init_config(const char *config_file) {
  struct Config *config = malloc(sizeof(struct Config));
  config->log_file_path = "/var/log/diskhoundd.log";
  config->config_file_path = NULL;
  config->icon_path = NULL;

  if (config_file == NULL) {
    return config;
  }

  FILE *file = fopen(config_file, "r");
  if (file == NULL) {
    fprintf(stderr, "config file %s not found.\n", config_file);
    exit(EXIT_CONFIG_FILE_NOT_FOUND);
  }
  config->config_file_path = config_file;

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
      // printf("%s->%s\n", key, value);
      set_value_if_valid_key(key, value, config);
      // printf("%s->%s\n", key, config->log_file_path);
    }
  }

  return config;
}
