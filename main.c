
#include <stdio.h>

#include "logger.h"


LOGGER *logger;


int main(int ac, char **av) {
	if (!(logger = logger_init(LOGGER_TRACE, "test"))) {
		printf("unable to initialize logger\n");
		goto term;
	}

	logger_info(logger, "starting up...");
	logger_info(logger, "initializing...");
	logger_info(logger, "lol");
term:
	logger_info(logger, "terminating...");
	logger_cleanup(logger);
}
