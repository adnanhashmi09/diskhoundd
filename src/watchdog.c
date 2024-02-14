#include <libnotify/notification.h>
#include <libnotify/notify.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/statvfs.h>
#include <time.h>
#include <unistd.h>

#include "config.h"
#include "disk_space_utils.h"
#include "exit_codes.h"
#include "globals.h"
#include "logger.h"
#include "notification_handler.h"

void watchdog_start(char **ProgramTitle) {

  time_t *notification_made_at =
      (time_t *)calloc(config.path_list_size, sizeof(time_t));

  if (notification_made_at == NULL) {
    perror("Memory allocation failed");
    exit(EXIT_FAILURE);
  }

  char *notification_msg = (char *)malloc(150 * sizeof(char));
  NotifyNotification *notify_handle;

  struct statvfs stat;
  Log(INFO, "Diskhound Started.\n");

  while (true) {
    for (size_t i = 0; i < config.path_list_size; i++) {
      const char *path = config.paths[i];

      if (statvfs(path, &stat) == 0) {

        double free_space_perc = get_free_disk_percentage(&stat);

        time_t curr_time = time(NULL);
        if (free_space_perc > config.critical_disk_perc ||
            (curr_time - notification_made_at[i] <= ONE_HOUR)) {
          continue;
        }

        sprintf(notification_msg, "(%s) - Disk space is less than %.0f%%", path,
                free_space_perc);

        Log(INFO, "'%s' - %s\n", path, notification_msg);

        sleep(3);

        init_notification(*ProgramTitle);
        make_notification(&notify_handle, notification_msg);
        clean_notification_handler(&notify_handle);

        Log(INFO, "notification made\n");
        notification_made_at[i] = curr_time;
        continue;
      }

      sprintf(notification_msg, "Error reading path \"%s\"", path);
      Log(ERROR, "%s\n", notification_msg);

      init_notification(*ProgramTitle);
      make_notification(&notify_handle, notification_msg);
      clean_notification_handler(&notify_handle);

      Log(INFO, "Exiting Diskhound\n");
      exit(EXIT_ERR_DISK_STATUS_STAVFS);
    }
    sleep(15);
  }
}
