#include "Source.h"
#include <string>

using namespace std;

Source::Source(Filed* filed) :
		Solution(filed, "Solution.cpp")
{
}

Source::~Source()
{
	Close();
}

void Source::Run()
{
	wirteHead();
	wirteFunction();
	wirteTest();
	wirteMain();
}

void Source::wirteHead()
{
	Print()("#include \"$Solution$.h\"\n\n");
}

void Source::wirteFunction()
{
	string line = filed->GetTrainFunction()->function();
	size_t pos = line.find(' ');
	if (pos == string::npos) {
		std::cerr << "wirte function failed " << line << std::endl;
		exit(0);
	}
	line.insert(pos+1, "Solution::");
	Print()("$1${\n", line);
	Print()("}\n\n");
}

void Source::wirteTest()
{
	Print()("void $Solution$::Run() {\n");
	Print().Indent();
	int i = 0;
	for (auto it: *(filed->GetTrainFunction())->mutable_test()) {
		i++;
		Print()("if ($1$ != $execute$($2$)) {\n", it.first, it.second);
		Print().Indent();
		Print()("cerr << $1$ << \": $2$ != $execute$($3$) \" << endl;\n", i, it.first, it.second);
		Print().Outdent();
		Print()("} else {\n");
		Print().Indent();
		Print()("cerr << $1$ << \": $2$ == $execute$($3$)\" << endl;\n", i, it.first, it.second);
		Print().Outdent();
		Print()("}\n");
		
	}
	Print().Outdent();
	Print()("}\n\n");
}

void Source::wirteMain()
{
	Print()("int main(int argc, char* argv[]) {\n");
	Print().Indent();

	Print()("$Solution$ source;\n");
	Print()("source.Run();\n");
	
	Print()("return 0;\n");
	Print().Outdent();
	Print()("}");
}
