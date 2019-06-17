#include "Logger.h"

const char* DEBUG_FILE = "debug.log";

std::string _with_prefix(std::string str) {
	return ("[Lambda Engine] " + str);
}

void log_error(std::string err) {
	TraceLog(LOG_ERROR, _with_prefix(err).c_str());
}

void log_warning(std::string warn) {
	TraceLog(LOG_WARNING, _with_prefix(warn).c_str());
}

void log_info(std::string info) {
	TraceLog(LOG_INFO, _with_prefix(info).c_str());
}

void log_debug_clear_previous() {
	std::ofstream debug_filestream;	
	debug_filestream.open(DEBUG_FILE);

	if (!debug_filestream.is_open()) {
		log_error("Unable to clear previous debug file:" + (std::string) DEBUG_FILE);
		return;
	}

	debug_filestream << "";
	debug_filestream.close();
}

void log_debug(std::string debug) {
	std::string debug_string = _with_prefix(debug);

	std::ofstream debug_filestream;
	debug_filestream.open(DEBUG_FILE, std::ios_base::app);

	if (!debug_filestream.is_open()) {
		log_warning("Unable to write entry to debug file: " + (std::string) DEBUG_FILE);
		return;
	}

	debug_filestream << debug_string << std::endl;
	debug_filestream.close();

	TraceLog(LOG_DEBUG, debug_string.c_str());
}