#ifndef CONFIG
#define CONFIG

struct Config {
  const char *config_file_path;
  const char *log_file_path;
  const char* icon_path;
  int critical_disk_perc;
  int path_list_size;
};

void init_config(const char* config_file_path, int number_of_paths);
extern struct Config config;

#endif // !CONFIG
