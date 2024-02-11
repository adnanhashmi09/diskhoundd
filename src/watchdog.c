#include <libnotify/notification.h>
#include <libnotify/notify.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/statvfs.h>
#include <unistd.h>

#include "exit_codes.h"
#include "globals.h"
#include "logger.h"
#include "notification_handler.h"
#include "disk_space_utils.h"

void watchdog_start(const char** path, char** ProgramTitle, struct statvfs *stat){

  char *notification_msg = (char *)malloc(150 * sizeof(char));
  NotifyNotification *notify_handle;

  Log(INFO, "Diskhound Started.\n");
  while (true) {
    if (statvfs(*path, stat) == 0) {

      double free_space_perc = get_free_disk_percentage(stat);
      if (free_space_perc > 20) {
        continue;
      }

      sprintf(notification_msg, "Disk space is less than %.0f%%",
              free_space_perc);

      Log(INFO, "'%s' - %s\n", *path, notification_msg);

      sleep(5);

      init_notification(*ProgramTitle);
      make_notification(&notify_handle, notification_msg);
      clean_notification_handler(&notify_handle);

      Log(INFO, "notification made\n");
      Log(INFO, "sleeping for 1 hour\n");
      sleep(SLEEP_TIME);
      continue;
    }

    sprintf(notification_msg, "Error reading path \"%s\"", *path);
    Log(ERROR, "%s\n", notification_msg);

    init_notification(*ProgramTitle);
    make_notification(&notify_handle, notification_msg);
    clean_notification_handler(&notify_handle);

    Log(INFO, "Exiting Diskhound\n");
    exit(EXIT_ERR_DISK_STATUS_STAVFS);
  }
}
