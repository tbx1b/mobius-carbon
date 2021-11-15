#include <sys/defs.h>

int 
kmain() 
{
  /* stage 1 */
  cli();
  ttyinit(1,1);
  announce();

  if (seginit() == -1) {
    ttyputs("\nCouldn't initialize GDT");
    return -1;
  }
  ttyputs("\nInitialized GTD");

  return 0;
}