#pragma once

#include "function.pb.h"
#include <string>
#include <map>

class Filed {
public:
	Filed() {};
	~Filed() {};

	void SetTrainFunction(const train::Function* function) { this->function = function; }
	train::Function* GetTrainFunction() { return this->function; }
	void SetParameter(const std::map<std::string, std::string>& parameter) { this->mapParameter = parameter; }
	std::map<std::string, std::string> GetParameter(){ return mapParameter; }
	void SetExecute(const std::string& execute) { this->execute = execute;}
	std::string& GetExecute() { return execute;}

private:
	train::Function* function;
	std::map<std::string, std::string> mapParameter;
	std::string execute;
	std::map<std::string, std::string> vars;
};
