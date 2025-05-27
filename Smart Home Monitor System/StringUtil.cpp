#include "StringUtil.h"

std::string StringUtil::toLower(const std::string& str) {
	std::string lowerStr = str;
	for (char& c : lowerStr) {
		c = static_cast<char>(tolower(c));
	}
	return lowerStr;
}