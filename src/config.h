#ifndef CONFIG
#define CONFIG

struct Config {
  const char *config_file_path;
  const char *log_file_path;
  const char* icon_path;
};

void init_config(const char* config_file_path);
extern struct Config config;

#endif // !CONFIG
