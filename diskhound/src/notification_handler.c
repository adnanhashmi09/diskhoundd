#include <libnotify/notification.h>
#include <libnotify/notify.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "globals.h"
#include "exit_codes.h"

void init_notification(char* ProgramTitle) {
  bool notify_init_status;
  notify_init_status = notify_init(ProgramTitle);
  if (!notify_init_status) {
    fprintf(stderr, "Error initialising with libnotify!\n");
    exit(EXT_ERR_INIT_LIBNOTIFY);
  }
}

void make_notification(NotifyNotification **notify_handle,
                       char *notification_msg) {

  *notify_handle = notify_notification_new("Diskhound", notification_msg,
                                           "diaglog-information");
  notify_notification_set_urgency(*notify_handle, NOTIFY_URGENCY_CRITICAL);
  notify_notification_set_timeout(*notify_handle, NOTIFICATION_TIMEOUT);
  notify_notification_show(*notify_handle, NULL);
}

void clean_notification_handler(NotifyNotification **notify_handle) {
  g_object_unref(G_OBJECT(*notify_handle));
  notify_uninit();
}
