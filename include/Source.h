#pragma once

#include "Solution.h"
#include <google/protobuf/io/printer.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

class Source : public Solution
{
public:
	Source(Filed* filed);
	virtual ~Source();

	virtual void Run();

protected:
	void wirteHead();
	void wirteFunction();
	void wirteTest();
	void wirteMain();
};
