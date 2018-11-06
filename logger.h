/*
 * logging system global declarations
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <sys/types.h>


/*
 * constants
 */

typedef enum {
    LOGGER_ERROR,
    LOGGER_WARN,
    LOGGER_INFO,
    LOGGER_DEBUG,
    LOGGER_TRACE
} LOGGER_LEVELS;

#define logger_error(logger, format, ...) if ((logger) && (logger)->log_level >= LOGGER_ERROR) logger_write(logger, LOGGER_ERROR, __FILE__, __LINE__, (const char *)(format), ##__VA_ARGS__)
#define logger_warn(logger, format, ...) if ((logger) && (logger)->log_level >= LOGGER_WARN) logger_write(logger, LOGGER_WARN, __FILE__, __LINE__, (const char *)(format), ##__VA_ARGS__)
#define logger_info(logger, format, ...) if ((logger) && (logger)->log_level >= LOGGER_INFO) logger_write(logger, LOGGER_INFO, __FILE__, __LINE__, (const char *)(format), ##__VA_ARGS__)
#define logger_debug(logger, format, ...) if ((logger) && (logger)->log_level >= LOGGER_DEBUG) logger_write(logger, LOGGER_DEBUG, __FILE__, __LINE__, (const char *)(format), ##__VA_ARGS__)
#define logger_trace(logger, format, ...) if ((logger) && (logger)->log_level >= LOGGER_TRACE) logger_write(logger, LOGGER_TRACE, __FILE__, __LINE__, (const char *)(format), ##__VA_ARGS__)


/*
 * data types
 */

typedef struct LOGGER {
	LOGGER_LEVELS log_level;
	pid_t pid;
    pid_t tid;
	const char *app_name;
	int app_name_len;
    char *buffer;
} LOGGER;


/*
 * functions
 */

extern void logger_cleanup(LOGGER *logger);

extern LOGGER *logger_init(LOGGER_LEVELS level, const char *app_name);

extern void logger_write(LOGGER *logger, LOGGER_LEVELS level, const char *source_name, const int line_number, const char *format, ...);


#endif /* LOGGER_H */
