/*
 * logging
 */

#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "logger.h"


/*
 * constants
 */

#define LOGGER_LINE_MIN_SIZE 49 
#define LOGGER_LINE_MAX_SIZE 2048

static const char const *LEVELS[] = {
	"ERROR",
	"WARN",
	"INFO",
	"DEBUG",
	"TRACE"
};


/*
 * cleanup resources
 */
void logger_cleanup(LOGGER *logger) 
{
    if (logger != NULL) {
        free(logger);
    }
}


/*
 * initialize logging
 */
LOGGER *logger_init(LOGGER_LEVELS level, const char *app_name) 
{
    int len;
    LOGGER *logger = NULL;
    
    if (app_name == NULL) {
        app_name = "unknown";
    }
    len = strlen(app_name);

    if (len >= LOGGER_LINE_MAX_SIZE - LOGGER_LINE_MIN_SIZE) {
        return NULL;
    }
    if ((logger = malloc(sizeof(LOGGER) + LOGGER_LINE_MAX_SIZE + len + 1)) == NULL) {
        return NULL;
    }

	memset(logger, 0, sizeof(LOGGER) + LOGGER_LINE_MAX_SIZE + len + 1);
	logger->log_level = level;
	logger->pid = getpid();
    logger->tid = syscall(__NR_gettid);
	logger->app_name_len = len;
    logger->app_name = (char *)logger + sizeof(LOGGER);
    logger->buffer = (char *)logger + sizeof(LOGGER) + len + 1;

	strncpy((char *)logger->app_name, (char *)app_name, len);
	return logger;
}


/*
 * write a log entry
 */
void logger_write(LOGGER *logger, LOGGER_LEVELS level, const char *source_name, const int line_number, const char *format, ...) 
{
	va_list ap;
	time_t raw_time;
	struct tm tm;
	struct tm *tm_ptr = &tm;
    int len;

	time(&raw_time);
	gmtime_r(&raw_time, tm_ptr);
	va_start(ap, format);
	len = snprintf(logger->buffer, LOGGER_LINE_MAX_SIZE, "%04i-%02i-%02i %02i:%02i:%02i  %s  %05u  %04x  %s  %i  %s  ", tm_ptr->tm_year + 1900, tm_ptr->tm_mon + 1, tm_ptr->tm_mday, tm_ptr->tm_hour, tm_ptr->tm_min, tm_ptr->tm_sec, logger->app_name, logger->pid, logger->tid, source_name, line_number, LEVELS[level]);
	len += vsnprintf(logger->buffer + len, LOGGER_LINE_MAX_SIZE - len, format, ap);
    if (len < LOGGER_LINE_MAX_SIZE - 1) {
        logger->buffer[len++] = '\n';
        logger->buffer[len++] = 0;
    }
    fputs(logger->buffer, stdout);
	va_end(ap);
}

