#include "logger.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "exit_codes.h" 

const char *log_file_path = "./diskhoundd.log";
char *get_current_time() {
  time_t rawtime;
  struct tm *timeinfo;
  static char buffer[20];

  time(&rawtime);
  timeinfo = localtime(&rawtime);
  strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

  return buffer;
}

void init_logger(const char* log_file){
  log_file_path = log_file;
}

void Log(LogLevel level, const char *format, ...) {
  const char *level_string;
  FILE *stream;

  switch (level) {
  case INFO:
    level_string = "INFO";
    stream = stdout;
    break;
  case WARNING:
    level_string = "WARNING";
    stream = stdout;
    break;
  case ERROR:
    level_string = "ERROR";
    stream = stderr;
    break;
  }

  FILE *file = fopen(log_file_path, "a");
  if(file==NULL){
    fprintf(stderr, "[ERROR] Cannot log open file '%s'\n", log_file_path);
    exit(EXIT_LOG_FILE_ERROR);
  }
  va_list args, args_copy;

  fprintf(file, "- (%s) [%s]: ", get_current_time(), level_string);

  va_start(args, format);
  va_copy(args_copy, args);

  vfprintf(stream, format, args);
  vfprintf(file, format, args_copy);
  
  fflush(stream);
  fflush(file);

  va_end(args);
  va_end(args_copy);

  fclose(file);
}
