#include <boost/process.hpp>
#include <boost/system/error_code.hpp>
#include <boost/asio.hpp>
// #include <boost/process/child.hpp>
// #include <boost/process/cmd.hpp>
// #include <boost/process/group.hpp>
// #include <boost/process/pipe.hpp>
// #include <boost/process/posix.hpp>
// #include <boost/process/system.hpp>
#include <iostream>
#include <thread>

namespace bp = boost::process;

std::vector<std::string> read_outline(std::string & file) {
	    bp::ipstream is; //reading pipe-stream
	    bp::child c(bp::search_path("nm"), file, bp::std_out > is);

	    std::vector<std::string> data;
	    std::string line;

	    while (c.running() && std::getline(is, line) && !line.empty())
	        data.push_back(line);

	    c.wait();

	    return data;
	}

int main()
{
	int result = boost::system("g++ main.cpp");
	std::cout << result << std::endl;

	
}
