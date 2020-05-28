#include "common.h"
#include <locale.h>

int main(int argc, char *argv[]) {
  const char* locale = getenv("LANG");
  printf("Locale = \"%s\"\n\n", locale);
  exit(0);
}
