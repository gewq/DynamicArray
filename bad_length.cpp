#include "bad_length.h"

bad_length::bad_length(int capacity): std::exception(),
	errorMessage_("Error: capacity (" + std::to_string(capacity) + ") <= 0")
{
//	errorMessage_ = "Error: capacity (" + std::to_string(capacity) + ") <= 0";
};

const char* bad_length::what() const noexcept
{
	return errorMessage_.c_str();
}