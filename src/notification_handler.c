#include <gdk-pixbuf/gdk-pixbuf.h>
#include <libnotify/notification.h>
#include <libnotify/notify.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "exit_codes.h"
#include "globals.h"
#include "logger.h"

void init_notification(char *ProgramTitle) {
  bool notify_init_status;
  notify_init_status = notify_init(ProgramTitle);
  if (!notify_init_status) {
    Log(ERROR, "Error initialising with libnotify!\n");
    exit(EXIT_ERR_INIT_LIBNOTIFY);
  }
}

void make_notification(NotifyNotification **notify_handle,
                       char *notification_msg) {

  *notify_handle = notify_notification_new("Diskhound", notification_msg,
                                           "dialog-information-symbolic");
  notify_notification_set_urgency(*notify_handle, NOTIFY_URGENCY_CRITICAL);
  notify_notification_set_timeout(*notify_handle, NOTIFICATION_TIMEOUT);
  notify_notification_set_icon_from_pixbuf(
      *notify_handle,
      gdk_pixbuf_new_from_file("/home/adnan/data/Code/daemons/diskhound/storage.svg", NULL));
  notify_notification_show(*notify_handle, NULL);
}

void clean_notification_handler(NotifyNotification **notify_handle) {
  g_object_unref(G_OBJECT(*notify_handle));
  notify_uninit();
}
