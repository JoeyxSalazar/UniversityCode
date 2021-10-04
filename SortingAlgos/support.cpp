/*
* support.cpp
*
* Author: nigel
*/

#include "support.h"


double getCPUTime(void) {
#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
	struct timeval tv;
	struct rusage ru;
	getrusage(RUSAGE_SELF, &ru);
	tv = ru.ru_utime;
	double t = (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
	tv = ru.ru_stime;
	t += (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
	return t;
#elif defined(_WIN32)
	return clock() / (double)CLOCKS_PER_SEC;
#endif
}


int randomInRange(const int start, const int end) {
#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
	return (start + random() % (end - start + 1));
#elif defined(_WIN32)
	return (start + rand() % (end - start + 1));
#endif
}
