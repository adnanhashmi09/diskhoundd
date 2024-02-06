#include <libnotify/notification.h>
#include <libnotify/notify.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/statvfs.h>
#include <unistd.h>

#define ERR_TOO_FEW_ARGUMENTS 1
#define EXT_ERR_INIT_LIBNOTIFY 2
#define GB (1024 * 1024 * 1024)

char *ProgramTitle = "diskhound";

double get_free_disk_percentage(struct statvfs *stat) {
  unsigned long block_size = stat->f_frsize;
  unsigned long free_size = block_size * (stat->f_bavail);

  double free_size_gb = (double)free_size / GB;
  double total_size_gb = (double)(stat->f_bsize * stat->f_blocks) / GB;

  double free_space_perc = (free_size_gb / total_size_gb) * 100;
  return free_space_perc;
}

void make_notification(NotifyNotification **notify_handle,
                       char *notification_msg) {

  *notify_handle = notify_notification_new("Low Disk Space", notification_msg,
                                           "diaglog-information");
  notify_notification_set_urgency(*notify_handle, NOTIFY_URGENCY_CRITICAL);
  notify_notification_set_timeout(*notify_handle, 2000);
  notify_notification_show(*notify_handle, NULL);
}

void clean_notification_handler(NotifyNotification **notify_handle) {
  g_object_unref(G_OBJECT(*notify_handle));
  notify_uninit();
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

  while (true) {
    if (statvfs(path, &stat) == 0) {

      double free_space_perc = get_free_disk_percentage(&stat);
      if (free_space_perc > 20) {
        continue;
      }
      sprintf(notification_msg, "Disk space is less than %.0f%%",
              free_space_perc);
      notify_init_status = notify_init(ProgramTitle);
      if (!notify_init_status) {
        fprintf(stderr, "Error initialising with libnotify!\n");
        exit(EXT_ERR_INIT_LIBNOTIFY);
      }
      make_notification(&notify_handle, notification_msg);
      clean_notification_handler(&notify_handle);
      fprintf(stdout, "notification made\nsleeping for 1 hour\n");
      fflush(stdout);
      sleep(3);

    } else {
      exit(1);
    }
  }
}
