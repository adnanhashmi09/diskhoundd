#include <libnotify/notification.h>
#include <libnotify/notify.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/statvfs.h>
#include <unistd.h>

#include "exit_codes.h"
#include "globals.h"
#include "notification_handler.h"
#include "signal_handler.h"

char *ProgramTitle = "diskhound";

double get_free_disk_percentage(struct statvfs *stat) {
  unsigned long block_size = stat->f_frsize;
  unsigned long free_size = block_size * (stat->f_bavail);

  double free_size_gb = (double)free_size / GB;
  double total_size_gb = (double)(stat->f_bsize * stat->f_blocks) / GB;

  double free_space_perc = (free_size_gb / total_size_gb) * 100;
  return free_space_perc;
}

int main(int argc, char **argv) {
  bool notify_init_status;
  char *notification_msg = (char *)malloc(150 * sizeof(char));

  NotifyNotification *notify_handle;
  if (argc < 2) {
    fprintf(stderr, "USAGE: diskhound [PATH]\n");
    exit(ERR_TOO_FEW_ARGUMENTS);
  }

  struct statvfs stat;
  const char *path = argv[1];

  signal(SIGABRT, signal_handler);
  signal(SIGINT, signal_handler);
  signal(SIGTERM, signal_handler);

  while (true) {
    if (statvfs(path, &stat) == 0) {

      double free_space_perc = get_free_disk_percentage(&stat);
      if (free_space_perc > 20) {
        continue;
      }

      sprintf(notification_msg, "Disk space is less than %.0f%%",
              free_space_perc);

      sleep(5);

      init_notification(ProgramTitle);
      make_notification(&notify_handle, notification_msg);
      clean_notification_handler(&notify_handle);

      fprintf(stdout, "notification made\nsleeping for 1 hour\n");
      fflush(stdout);
      sleep(SLEEP_TIME);
      continue;
    }

    sprintf(notification_msg, "Error reading path \"%s\"", path);
    init_notification(ProgramTitle);
    make_notification(&notify_handle, notification_msg);
    clean_notification_handler(&notify_handle);
    exit(EXIT_ERR_DISK_STATUS_STAVFS);
  }
}
