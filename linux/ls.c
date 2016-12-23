#include "common.h"
#include <dirent.h>

int main(int argc, char *argv[]) {
  DIR *dp;
  struct dirent *dirp;

  if (argc != 2) {
    puts("usage: ls directory_name");
    exit(1);
  }

  if ((dp = opendir(argv[1])) == NULL) {
    char* error_message = (char*) malloc(7 * sizeof(char) + sizeof(argv[1]));
    sprintf(error_message, "can’t open %s", argv[1]);
    err_sys(error_message);
  }

  while ((dirp = readdir(dp)) != NULL) {
    printf("%s\n", dirp->d_name);
  }

  closedir(dp);
  exit(0);
}
