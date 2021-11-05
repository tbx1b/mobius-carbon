/* #(@) announce.h - simple bootup message */

#if !defined(_announce_h)
#define _announce_h

#include <sys/io.h>
#include <core.h>

MTSS_API void
_os_announce();
#define announce _os_announce

#endif /* _announce_h */