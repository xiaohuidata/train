#pragma once

#include "Solution.h"

class Header : public Solution
{
public:
	Header(Filed* filed);
	virtual ~Header();

	virtual void Run();
private:
	void fileHeader();
	void end();
	void wirteClass();
	void wirteFucntion();
};
