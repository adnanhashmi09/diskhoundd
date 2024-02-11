#include <sys/statvfs.h>
#include "globals.h"

double get_free_disk_percentage(struct statvfs *stat) {
  unsigned long block_size = stat->f_frsize;
  unsigned long free_size = block_size * (stat->f_bavail);

  double free_size_gb = (double)free_size / GB;
  double total_size_gb = (double)(stat->f_bsize * stat->f_blocks) / GB;

  double free_space_perc = (free_size_gb / total_size_gb) * 100;
  return free_space_perc;
}
