/*
 * support.h
 *
 *      Author: nigel
 */

#ifndef SUPPORT_H_
#define SUPPORT_H_

#include <iostream>
using namespace std;

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#include <sys/time.h>
#include <sys/resource.h>
#elif defined(_WIN32)
#include <time.h>
#endif

#include <stdlib.h>

double getCPUTime(void);
int randomInRange(const int start, const int end);


#endif /* SUPPORT_H_ */