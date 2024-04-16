#include "Header.h"

using namespace std;

Header::Header(Filed* filed) :
		Solution(filed, "Solution.h")
{
}

Header::~Header()
{
	Close();
}

void Header::Run()
{
	fileHeader();
	wirteClass();
	wirteFucntion();
	end();
}

void Header::fileHeader()
{
	Print()("#include <iostream>\n"
		"#include <string>\n"
		"#include <map>\n"
		"#include <vector>\n"
		"#include <list>\n"
		"#include <queue>\n"
		"\n"
		"using namespace std;\n"
		"\n");

	Print()("class $Solution$ {\n");
	Print()("public:\n");
	Print().Indent();
}

void Header::end()
{
	Print().Outdent();
	Print()("};");
}

void Header::wirteClass()
{
	for (auto it : *(filed->GetTrainFunction())->mutable_class_())
	{
		Print()("class $1$ {\n"
			"public:\n", it.first);
		Print().Indent();
		Print()("$1$() {};\n", it.first);
		train::Parameter& parameters = it.second;
		string argv = "";
		for (auto iter: parameters.parameter()) {
			argv = iter.first + " " + iter.second + ",";
		}
		argv = argv.substr(0, argv.size()-1);
		Print()("$1$($2$);\n", it.first, argv);
		Print()("$1$(const $1$& o) {\n", it.first);
		Print().Indent();
		for (auto iter: parameters.parameter()) {
			Print()("this->$1$=o.$1$;\n", iter.second);
		}
		Print().Outdent();
		Print()("}\n");

		Print()("$1$& operator=(const $1$&o) {\n", it.first);
		Print().Indent();
		Print()("if(this == &o) {\n");
		Print().Indent();
		Print()("return *this;\n");
		Print().Outdent();
		Print()("}\n");
		for (auto iter: parameters.parameter()) {
			Print()("this->$1$=o.$1$;\n", iter.second);
		}
		Print()("return *this;\n");
		Print().Outdent();
		Print()("}\n");
		Print()("bool operator==(const $1$&o) {\n", it.first);
		Print().Indent();
		for (auto iter: parameters.parameter()) {
			Print()("if (this->$1$!=o.$1$) return false;\n", iter.second);
		}
		Print()("return true;");
		Print().Outdent();
		Print()("}\n");
		Print()("~$1$() {};\n", it.first);

		for (auto iter: parameters.parameter()) {
			Print()("void set$1$($2$ $1$) { this->$1$ = $1$; }\n", iter.second, iter.first);
			Print()("$1$ get$2$() { return $2$; }\n", iter.first, iter.second);
		}

		Print().Outdent();
		Print()("protected:\n");
		Print().Indent();
		for (auto iter: parameters.parameter()) {
			Print()("$1$ $2$;\n", iter.first, iter.second);
		}
		Print().Outdent();
		Print()("};\n\n");
	}
}

void Header::wirteFucntion()
{
	Print()("void Run();\n");
	Print().Outdent();
	Print()("protected:\n");
	Print().Indent();
	Print()("$1$;\n", filed->GetTrainFunction()->function());
}
