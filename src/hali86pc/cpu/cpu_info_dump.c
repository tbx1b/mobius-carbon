#include <libcarbon/io.h>
#include <libc/stdarg.h>
#include "hali86pc/_internal.h"

static void formatter(void *data, const char *fmt, ...)
{
	va_list vl;

	va_start(vl, fmt);
	vprintf(fmt, vl);
	va_end(vl);
}

void cpu_info_dump(struct cpu_info *id)
{
	cpu_info_format(id, formatter, 0);
}

