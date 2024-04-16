#include "Solution.h"
#include <string>
#include <map>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

using namespace std;

Solution::Solution(Filed* filed, const std::string& filename) :
		filed(filed), filename(filename)
{
	file = open(filename.c_str(), O_RDWR | O_CREAT | O_TRUNC , 0644);
	if (file == 0)
	{
		cerr << "open file: " << file << " failed" << endl;
		exit(0);
	}
	output = new google::protobuf::io::FileOutputStream(file, 1);
	printer = new google::protobuf::io::Printer(output, '$');
	vars.insert(pair<string, string>("Solution", "Solution"));
	vars.insert(pair<string, string>("execute", filed->GetExecute()));
	format = new google::protobuf::compiler::cpp::Formatter(printer, vars);
}

Solution::~Solution()
{
	Close();
}

void Solution::Close()
{
	delete output;
	output = NULL;
	delete printer;
	printer = NULL;
	delete format;
	format = NULL;
	close(file);
}
