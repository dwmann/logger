/*
 * logging system global declarations
 */

#ifndef LOGGER_H
#define LOGGER_H


/*
 * constants
 */

#define LOGGER_ERROR 0
#define LOGGER_WARN 1
#define LOGGER_INFO 2
#define LOGGER_DEBUG 3
#define LOGGER_TRACE 4

#define loggerError(format, ...) if (loggerState.logLevel >= LOGGER_ERROR) loggerWrite(LOGGER_ERROR, __FILE__, __LINE__, (const char *)(format), ##__VA_ARGS__)
#define loggerWarn(format, ...) if (loggerState.logLevel >= LOGGER_WARN) loggerWrite(LOGGER_WARN, __FILE__, __LINE__, (const char *)(format), ##__VA_ARGS__)
#define loggerInfo(format, ...) if (loggerState.logLevel >= LOGGER_INFO) loggerWrite(LOGGER_INFO, __FILE__, __LINE__, (const char *)(format), ##__VA_ARGS__)
#define loggerDebug(format, ...) if (loggerState.logLevel >= LOGGER_DEBUG) loggerWrite(LOGGER_DEBUG, __FILE__, __LINE__, (const char *)(format), ##__VA_ARGS__)
#define loggerTrace(format, ...) if (loggerState.logLevel >= LOGGER_TRACE) loggerWrite(LOGGER_TRACE, __FILE__, __LINE__, (const char *)(format), ##__VA_ARGS__)


/*
 * data types
 */

typedef struct LOGGER {
	short int logLevel;
	unsigned int pid;
	const char *appName;
	int appNameLen;
} LOGGER;


/*
 * global data
 */

extern LOGGER loggerState;


/*
 * functions
 */

extern int loggerInit(short int level, const char *appName);

extern void loggerCleanup(void);

extern void loggerWrite(short int level, const char *sourceName, const int lineNumber, const char *format, ...);


#endif /* LOGGER_H */
