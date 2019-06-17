#include "LEError.h"

bool LE_Error::has_error()
{
	return std::get<0>(*this);
}

std::string LE_Error::get_status()
{
	return std::get<1>(*this);
}
