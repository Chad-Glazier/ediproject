#include "util.h"
#include <time.h>

Nanoseconds current_time(void) {
	struct timespec ts;
	timespec_get(&ts, TIME_UTC);

	return ((Nanoseconds) ts.tv_sec * 1000000000ULL) + (Nanoseconds) ts.tv_nsec;
}
