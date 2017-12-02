#include <iostream>
#include <ctime>
#include <boost/filesystem.hpp>
#include <boost/process.hpp>
#include <boost/program_options.hpp>

#include <string> 
#include <vector> 

// namespace bp = ::boost::process; 

using namespace boost::filesystem;
// using namespace boost::process;
namespace bp = ::boost::process; 
using namespace boost::process::initializers;
using namespace boost::program_options;

// int timeTransform(int _time) {
// 	return _time * 1000;
// }

void Hello()
{
    //... contents does not matter for me now - I just want to make a new process running this function using Boost.Process.
} 

bp::child start_child() 
{ 
    std::string exec = "bjam"; 

    std::vector<std::string> args; 
    args.push_back("--version"); 

    bp::context ctx; 
    ctx.stdout_behavior = bp::silence_stream(); 

    return bp::launch(exec, args, ctx); 
} 

int main(int argc, char** argv) {
    try {

    	// options_description desc{"Options"};
     //    desc.add_options()
     //    ("help,h", "выводим вспомогательное сообщение")
     //    ("config", /*value<std::string>()->notifier(Debug),*/ "указываем конфигурацию сборки (по умолчанию Debug)")
     //    ("install", "добавляем этап установки (в директорию _install)")
     //    ("pack", "добавляем этап упаковки (в архив формата tar.gz)")
     //    ("timeout", value<int>()->default_value(0), "указываем время ожидания (в секундах)");

     //    variables_map vm_console;

     //    store(parse_command_line(argc, argv, desc), vm_console);
     //    notify(vm_console);

     //    if (vm_console.count("help")) {
     //        std::cout << desc << '\n';
     //    } else if(vm_console.count("timeout")) {
     //    	if(vm_console["timeout"].as<int>() != 0) {
     //    		std::cout << "TIME\tTIME\tTIME\tTIME\tTIME\tTIME\tTIME" << std::endl;
     //    	} else {
     //    		std::cout << "ZERO\tZERO\tZERO\tZERO\tZERO\tZERO\tZERO" << std::endl;
     //    	}
     //    } else {


	        // std::cout << "Hello world!" << std::endl;

	        // int result = system("cd examples && cmake -H. -B_build");
	        // if(result)
	        //     throw std::runtime_error("ERROR!\tCMakeLists.txt - not found!");

	        // result = system("cd examples && cmake --build _build");

	        // if(result)
	        //     throw std::runtime_error("ERROR!\tBulding - cancled!");


    		bp::child c = start_child(); 

            bp::status s = c.wait(); 

            return s.exited() ? s.exit_status() : EXIT_FAILURE;

	    // }


    } catch(const std::exception& e) {
        std::cout << e.what() << std::endl;
    } catch (const error &ex) {
        std::cerr << ex.what() << '\n';
    }
}
