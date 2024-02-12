#ifndef CONFIG
#define CONFIG

struct Config {
  const char *config_file_path;
  const char *log_file_path;
  const char *icon_path;
  const char** paths;
  int critical_disk_perc;
  int path_list_size;
};

void init_config(char **config_file_path, char ***paths, int number_of_paths);
extern struct Config config;

#endif // !CONFIG
