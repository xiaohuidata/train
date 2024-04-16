#include "common.h"
#include <sstream>

void Split(const std::string& str, char delim, std::vector<std::string>* out) {
	std::stringstream stream(str);
	std::string item;
	while (std::getline(stream, item, delim)) {
		out->push_back(item);
	}
}
