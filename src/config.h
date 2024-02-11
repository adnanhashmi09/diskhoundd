#ifndef CONFIG
#define CONFIG

struct Config {
  const char *config_file_path;
  const char *log_file_path;
  const char* icon_path;
};

struct Config *init_config(const char* config_file_path);

#endif // !CONFIG
