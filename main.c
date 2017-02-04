
#include <stdio.h>

#include "logger.h"


int main(int ac, char **av) {
	if (loggerInit(LOGGER_TRACE, "test")) {
		printf("unable to initialize logger\n");
		goto term;
	}

	loggerInfo("starting up...");
	loggerInfo("initializing...");
	loggerInfo("lol");
term:
	loggerInfo("terminating...");
	loggerCleanup();
}
