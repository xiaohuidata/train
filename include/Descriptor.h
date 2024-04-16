#pragma once

#include "Filed.h"

class Descriptor
{
public:
	Descriptor(std::string json);
	~Descriptor() { }

private:
	void Run();
	void AnalysisFucntion();
	void AnalysisParameter(const std::string& argv);
	void AnalysisExecute(const std::string& str);

	Filed filed;
	train::Function* function;
};
