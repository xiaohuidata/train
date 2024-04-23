#pragma once

#include "Filed.h"
//#include "google/protobuf/compiler/cpp/Formatter.h"
#include "Formatter.h"
#include <google/protobuf/io/printer.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

class Solution {
public:
	Solution(Filed* filed, const std::string& filename);
	virtual ~Solution();

	virtual void Run() = 0;
protected:
	void Close();

	google::protobuf::compiler::cpp::Formatter& Print() { return *format; }

	Filed*filed;
	std::string filename;
	int file;
	std::map<std::string, std::string> vars;
	google::protobuf::io::FileOutputStream* output;
	google::protobuf::io::Printer* printer;
	google::protobuf::compiler::cpp::Formatter* format;
};
