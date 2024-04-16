#include "Descriptor.h"
#include "Header.h"
#include "Source.h"
#include "common.h"
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <google/protobuf/util/json_util.h>
#include <google/protobuf/stubs/strutil.h>

using namespace std;

Descriptor::Descriptor(string json)
{
	google::protobuf::util::JsonParseOptions options;
	options.ignore_unknown_fields = true;
	train::Function* function = new train::Function;
	bool success = google::protobuf::util::JsonStringToMessage(json, function, options).ok();
	if (success) {
		filed.SetTrainFunction(function);
		Run();
	} else {
		cerr << "Failed to parse Person from JSON." << json << endl;
		exit(0);
	}
}

void Descriptor::Run()
{
	AnalysisFucntion();
	Header header(&filed);
	header.Run();
	Source source(&filed);
	source.Run();
}

void Descriptor::AnalysisFucntion()
{
	string line = filed.GetTrainFunction()->function();
	size_t bracket_pre = line.find('(');
	size_t bracket_end = line.find(')');

	if (bracket_pre == string::npos || bracket_end == string::npos || bracket_end - bracket_pre < 0) {
		cerr << "Failed function bracket" << line << endl;
		exit(0);
	}
	if (bracket_pre - bracket_end > 1) {
		string argv = line.substr(bracket_pre+1, bracket_end-bracket_pre-1);
		AnalysisParameter(argv);
	}

	string prefunction = line.substr(0, bracket_pre);
	AnalysisExecute(prefunction);
}

void Descriptor::AnalysisParameter(const string& argv)
{
	string strParameter = argv;
	size_t ignoe = string::npos;
	while (ignoe = strParameter.find('&') != string::npos) {
		strParameter.erase(ignoe, 1);
	}
	while (ignoe = strParameter.find('*') != string::npos) {
		strParameter.erase(ignoe, 1);
	}

	vector<string> parameters;
	Split(strParameter, ',', &parameters);
	map<string, string> mapParameter;
	for (auto it  : parameters) {
		vector<string> parameter;
		size_t pos = it.find_last_of(' ');
		if (pos != string::npos) {
			string a = it.substr(0, pos);
			string b = it.substr(pos+1);
			mapParameter.insert(pair<string, string> (a, b));
		} else {
			cerr << "Failed parameter " << it << endl;
			exit(0);
		}
	}
	filed.SetParameter(mapParameter);
}

void Descriptor::AnalysisExecute(const string& str)
{
	size_t pos = str.find_last_of(' ');
	string execute;
	if (pos != string::npos) {
		execute = str.substr(pos+1);
	} else {
		cerr << "Failed execute " << str << endl;
		exit(0);
	}
	filed.SetExecute(execute);
}
