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
	Print()("#pragma once\n"
		"#include <iostream>\n"
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

void Header::wirteClasss(list<string> & classs, const string& name)
{
	auto parameters = (filed->GetTrainFunction())->mutable_class_()->find(name);
	if (parameters == (filed->GetTrainFunction())->mutable_class_()->end()) {
		cerr << "no class name " << name << " defined." << endl;
		exit(1);
	}
	auto cp = parameters->second.mutable_inherit();
	for (auto iter : *cp) {
		if (std::find(classs.begin(), classs.end(), iter.second) != classs.end()) {
			continue;
		}
		wirteClasss(classs, iter.second);
		classs.push_back(iter.second);
	}
}

void Header::wirteClass()
{
	list<string> classs;
	for (auto it : *(filed->GetTrainFunction())->mutable_class_()) {
		if (std::find(classs.begin(), classs.end(), it.first) != classs.end()) {
			continue;
		}

		wirteClasss(classs, it.first);
		classs.push_back(it.first);
	}

	for (auto it : classs) {
		auto iter = (filed->GetTrainFunction())->mutable_class_()->find(it);
		wirteClass(it, iter->second);
	}
}

void Header::wirteClass(string name, train::Parameter& parameters)
{
	Print()("class $1$", name);
	if (parameters.inherit().size() != 0) {
		string inherits = "\n        :";
		for (auto iter: parameters.inherit()) {
			inherits += iter.first + " " + iter.second + ", ";
		}
		inherits = inherits.substr(0, inherits.size()-2);
		Print()("$1$", inherits);
	}
	Print()("{\n"
		"public:\n");
	Print().Indent();
	Print()("$1$() {};\n", name);

	// 参数初始化
	string argv = "";
	string newargv = "";
	if (parameters.inherit().size() != 0) {
		for (auto iter: parameters.inherit()) {
			auto classs = (filed->GetTrainFunction())->mutable_class_();
			auto itclass = classs->find(iter.second);
			string itargv = "", argvs = "";
			if (itclass != classs->end()) {
				for (auto itparameter : itclass->second.parameter()){
					itargv += itparameter.first + " " + itparameter.second + ", ";
					argvs += itparameter.second + ", ";
				}
				if (itargv != "")
				{
					newargv += iter.second + "(" + argvs.substr(0, argvs.size()-2) +"), ";
				}
			}
			argv += itargv;
		}
	}

	for (auto iter: parameters.parameter()) {
		argv += iter.first + " " + iter.second + ", ";
		newargv += iter.second + "(" + iter.second +"), ";
	}

	if (argv.size() > 2 ) {
		argv = argv.substr(0, argv.size()-2);
		newargv = newargv.substr(0, newargv.size()-2);

		Print()("$1$($2$)\n", name, argv);
		Print()("    : $1$\n", newargv);
		Print()("{}\n");
	}

	// 拷贝构造函数
	string constructor = "";
	if ((parameters.inherit().size() != 0)) {
		constructor = " : ";
		for (auto iter: parameters.inherit()) {
			constructor += iter.second + "(o)";
		}
	}
	Print()("$1$(const $1$& o)$2${\n", name, constructor);
	Print().Indent();
	for (auto iter: parameters.parameter()) {
		Print()("this->$1$=o.$1$;\n", iter.second);
	}
	Print().Outdent();
	Print()("}\n");

	// 复制构造函数
	Print()("$1$& operator=(const $1$&o) {\n", name);
	Print().Indent();
	Print()("if(this == &o) {\n");
	Print().Indent();
	Print()("return *this;\n");
	Print().Outdent();
	Print()("}\n");

	for (auto iter: parameters.inherit()) {
		Print()("$1$::operator=(o);\n", iter.second);
	}
	for (auto iter: parameters.parameter()) {
		Print()("this->$1$=o.$1$;\n", iter.second);
	}
	Print()("return *this;\n");
	Print().Outdent();
	Print()("}\n");

	// ==比较
	Print()("bool operator==(const $1$&o) {\n", name);
	Print().Indent();
	for (auto iter: parameters.inherit()) {
		Print()("if (!$1$::operator==(o)) return false;\n", iter.second);
	}
	for (auto iter: parameters.parameter()) {
		Print()("if (this->$1$!=o.$1$) return false;\n", iter.second);
	}
	Print()("return true;\n");
	Print().Outdent();
	Print()("}\n");

	// 析构函数
	Print()("virtual ~$1$() {};\n", name);

	// set，get函数
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

void Header::wirteFucntion()
{
	Print()("void Run();\n");
	Print().Outdent();
	Print()("protected:\n");
	Print().Indent();
	Print()("$1$;\n", filed->GetTrainFunction()->function());
}
