#include "bad_range.h"

bad_range::bad_range(int index): std::exception(),
	errorMessage_("Error: index (" + std::to_string(index) + ") is out_of_range")
{
	//errorMessage_ = "Error: index (" + std::to_string(index) + ") is out_of_range";
};

const char* bad_range::what() const noexcept
{
	return errorMessage_.c_str();
}