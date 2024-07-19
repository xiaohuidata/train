#pragma once

#include "Solution.h"
#include <list>

class Header : public Solution
{
public:
	Header(Filed* filed);
	virtual ~Header();

	virtual void Run();
private:
	void fileHeader();
	void end();
	void wirteClasss(std::list<std::string>& classs, const std::string& name);
	void wirteClass();
	void wirteClass(std::string name, train::Parameter& par);
	void wirteFucntion();
};
