#pragma once
#ifndef LEERROR_H
#define LEERROR_H

#include <stdlib.h>
#include <tuple>
#include <string>

/*
	A basic error handling type.
	If an error is present, the boolean will be
	true and the string will contain the error.
	Otherwise, false and "".
*/
class LE_Error : public std::tuple<bool, std::string> {
public:
	LE_Error(bool has, std::string str) : std::tuple<bool, std::string>(has, str){};

	bool has_error();
	std::string get_status();
};

#endif // LEERROR_H