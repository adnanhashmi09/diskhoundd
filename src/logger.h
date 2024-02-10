#ifndef LOGGER
#define LOGGER

typedef enum { INFO, WARNING, ERROR } LogLevel;
void Log(LogLevel level, const char *format, ...);

#endif // !LOGGER
