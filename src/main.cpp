#include "Descriptor.h"
#include <iostream>
#include <string>
#include <getopt.h>
#include <fstream>

using namespace std;

void showVersion()
{
	cout << "=========================================" << endl;
	cout << "标准练习构建" << endl;
	cout << "Version tag: " << endl;
	cout << "Version commit: " << endl;
	cout << "=========================================" << endl;
}

void showHelp()
{
	showVersion();
	cout << endl;
}

int main(int argc, char* argv[])
{
	struct option longopts[] = {
		{"json",       0, 0, 'j'},
		{"jsonconfig", 0, 0, 'c'},
		{"version",    0, 0, 'v'},
		{"help",       0, 0, 'h'},
	};

	string jsonFile;
	bool file = false;

	int opt = 0;
	while((opt = getopt_long(argc, argv, "j:c:vh", longopts, NULL)) != -1)
	{
		switch(opt)
		{
			case 'j':
				jsonFile = optarg;
				break;
			case 'c':
				jsonFile = optarg;
				file = true;
				break;
			case 'v':
				showVersion();
				exit(0);
			case 'h':
				showHelp();
				exit(0);
			default:
				return 0;
		}
	}
	string strJson;
	if (file) {
		ifstream fs(jsonFile);
		if (!fs) {
			cerr << "open " << jsonFile << " failed." << endl;
			return 1;
		}

		string line;
		while (getline(fs, line)) {
			strJson += line + "\n";
		}
		fs.close();
	}
	if (jsonFile.empty() && argc == 2)
	{
		string function = argv[1];
		strJson = "{\"function\":\""+function+"\"}";
	} else if (strJson.empty()) {
		strJson = jsonFile;
	}
	cout << "json:" << endl << strJson << endl;

	Descriptor descriptor(strJson);
	return 0;
}
