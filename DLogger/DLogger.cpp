#include "pch.h"
#include "DLogger.h"
#include <cstdio>
#include <time.h>
#include <iostream>

// constant for the file path
extern "C" DLOGGER_API const char* LOG_PATH = "\0";

// constant for the log level
extern "C" DLOGGER_API int LOG_LEVEL = DLOGGER_DEBUG_LEVEL;

DLOGGER_API int DLoggerInit(const char* log_file_path, int log_level)
{
    // Check if the log file path is valid
    if (log_file_path == "\0")
    {
		return -1;
	}

    // Check if the log level is valid
    if (log_level < DLOGGER_DEBUG_LEVEL || log_level > DLOGGER_FATAL_LEVEL)
    {
		return -1;
	}

	// Set the log file path
	LOG_PATH = log_file_path;

    // Set the log level
    LOG_LEVEL = log_level;

	return 0;
}

DLOGGER_API int DLoggerLog(int log_level, const char* log_message)
{
    // Check if the log level is valid
    if (log_level < DLOGGER_DEBUG_LEVEL || log_level > DLOGGER_FATAL_LEVEL)
    {
		return -1;
	}
    
    // Check if the log message is valid
    if (log_message == NULL)
    {
        return -1;
    }

    if (LOG_PATH == "\0")
    {
		return -1;
	}

    // check if the log level is less than the current log level
    if (log_level < LOG_LEVEL)
    {
        return 0;
    }

    // Get the current time using localtime_s
    time_t now = time(0);
    struct tm timeinfo;
    localtime_s(&timeinfo, &now);

    // create the log file name with the date : log_YYYYMMDD.log
    char log_file_name[20];
    strftime(log_file_name, 20, "log_%Y%m%d.log", &timeinfo);

    // add it to the log file path
    char log_file_path[256];
    sprintf_s(log_file_path, "%s%s", LOG_PATH, log_file_name);

    // Open the log file
    FILE* log_file;
    fopen_s(&log_file, log_file_path, "a+");

    // Check if the log file is valid
    if (log_file == NULL)
    {
		return -1;
	}

    // Write the log message to the log file
    char now_str[20];
    strftime(now_str, 20, "%Y-%m-%d %H:%M:%S", &timeinfo);
    const char* log_level_str = NULL;
    switch (log_level)
    {
        case DLOGGER_DEBUG_LEVEL:
			log_level_str = DLOGGER_DEBUG_LEVEL_STR;
			break;
        case DLOGGER_INFO_LEVEL:
            log_level_str = DLOGGER_INFO_LEVEL_STR;
            break;
        case DLOGGER_WARNING_LEVEL:
            log_level_str = DLOGGER_WARNING_LEVEL_STR;
			break;
		case DLOGGER_ERROR_LEVEL:
			log_level_str = DLOGGER_ERROR_LEVEL_STR;
			break;
		case DLOGGER_FATAL_LEVEL:
			log_level_str = DLOGGER_FATAL_LEVEL_STR;
			break;
		default:
			break;
    }
	fprintf(log_file, "[%s] [%s] %s\n", now_str, log_level_str, log_message);

	// Close the log file
	fclose(log_file);

	return 0;
}
