/*
 * logging
 */

#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "logger.h"


/*
 * constants
 */

static const int LINE_1_MAX = 100;
static const int LINE_2_MAX = 2048;

static const char const *LEVELS[] = {
	"ERROR",
	"WARN",
	"INFO",
	"DEBUG",
	"TRACE"
};


/*
 * data
 */

LOGGER loggerState;


/*
 * initialize logging
 */
int loggerInit(short int level, const char *appName) {
	memset(&loggerState, 0, sizeof(LOGGER));
	loggerState.logLevel = level;
	loggerState.pid = getpid();
	loggerState.appNameLen = strlen(appName);
	if ((loggerState.appNameLen + 53) > LINE_1_MAX) {
		loggerState.appNameLen = LINE_1_MAX - 53;
	}
	loggerState.appName = malloc(loggerState.appNameLen + 1);
	if (loggerState.appName == NULL) {
		return(1);
	}
	strncpy((char *)loggerState.appName, (char *)appName, loggerState.appNameLen);
	return(0);
}


/*
 * cleanup resources
 */
void loggerCleanup(void) {
	if (loggerState.appName != NULL) {
		free((char *)loggerState.appName);
	}
}


/*
 * write a log entry
 */
void loggerWrite(short int level, const char *sourceName, const int lineNumber, const char *format, ...) {
	char line1[LINE_1_MAX];
	char line2[LINE_2_MAX];
	va_list ap;
	time_t rawTime;
	struct tm tm;
	struct tm *tmPtr = &tm;
	time(&rawTime);
	gmtime_r(&rawTime, tmPtr);
	va_start(ap, format);
	if ((strlen(sourceName) + loggerState.appNameLen + 52) > LINE_1_MAX) {
		sourceName = "";
	}
	snprintf(line1, LINE_1_MAX, "%04i-%02i-%02i %02i:%02i:%02i  %s  %05u  %08lx  %s  %i  %s  ", tmPtr->tm_year + 1900, tmPtr->tm_mon + 1, tmPtr->tm_mday, tmPtr->tm_hour, tmPtr->tm_min, tmPtr->tm_sec, loggerState.appName, loggerState.pid, (long unsigned int)pthread_self(), sourceName, lineNumber, LEVELS[level]);
	vsnprintf(line2, LINE_2_MAX, format, ap);
	fprintf(stdout, "%s%s\n", line1, line2);
	va_end(ap);
}
