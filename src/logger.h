#ifndef LOGGER
#define LOGGER

typedef enum { INFO, WARNING, ERROR } LogLevel;
void init_logger(const char* log_file);
void Log(LogLevel level, const char *format, ...);

#endif // !LOGGER
