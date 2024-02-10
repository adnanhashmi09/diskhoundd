#ifndef NOTIFICATION_HANDLER
#define NOTIFICATION_HANDLER

#include <libnotify/notification.h>

void init_notification(char* ProgramTitle);
void make_notification(NotifyNotification **notify_handle, char *notification_msg);
void clean_notification_handler(NotifyNotification **notify_handle);

#endif // !NOTIFICATION_HANDLER
