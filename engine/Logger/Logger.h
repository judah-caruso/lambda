#pragma once
#ifndef LOGGER_H
#define LOGGER_H

#include "raylib.h"
#include <string>
#include <fstream>

void log_error(std::string err);
void log_warning(std::string warn);
void log_info(std::string info);
void log_debug(std::string debug);
void log_debug_clear_previous();

#endif // LOGGER_H