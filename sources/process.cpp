#include <iostream>
#include <chrono>
#include <boost/program_options.hpp>
#include <boost/process.hpp>

namespace bp = boost::process;
namespace po = boost::program_options;

bp::child Make(int time = 0, std::string build="Debug")
{
  // std::string cmd("cd examples && cmake -H. -B_build -DCMAKE_INSTALL_PREFIX=_install -DCMAKE_BUILD_TYPE=");
  // cmd += build;

  std::string cmd("cd examples && cmake -H. -B_build");
  // std::cout << "command = " << cmd << '\n';
  bp::child c(cmd, bp::std_out > stdout);
  if (time) {
    if (!c.wait_for(std::chrono::seconds(time)));
      c.terminate();
  } else {
    c.wait();
  }
  return c;
}

bp::child Build(int time = 0)
{
  std::string cmd("cd examples && cmake --build _build");

  // std::cout << "command = " << cmd << '\n';
  bp::child c(cmd, bp::std_out > stdout);
  if (time){
    if (!c.wait_for(std::chrono::seconds(time)));
      c.terminate();
  } else {
    c.wait();
  }
  return c;
}

bp::child Target(std::string inst)
{
  std::string cmd("cd examples && cmake --build _build");
  cmd += " --target ";
  cmd += inst;

  // std::cout << "command = " << cmd << '\n';
  bp::child c(cmd, bp::std_out > stdout);
  c.wait();
  return c;
}


int main(int argc, char const* const* argv)
{
    po::options_description desc("Allowed options");
    desc.add_options()
      ("help, h", "выводим вспомогательное сообщение")
      ("config", po::value<std::string>(), "указываем конфигурацию сборки (по умолчанию Debug)")
      ("install", "добавляем этап установки\n(в директорию _install)")
      ("pack", "добавляем этап упакови\n(в архив формата tar.gz)")
      ("timeout", po::value<int>(), "указываем время ожидания\n(в секундах)")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    int res;
    if(vm.count("help"))
    {
      std::cout << desc << std::endl;
    }

    //  Обрабатываем конфигурацию сборки <Release|Debug>
    else if (vm.count("config"))
    {
      std::string par(vm["config"].as<std::string>());

      if (Make(0, par).exit_code())
      	std::cerr << "make\truntime error" << std::endl;

      std::cout << "code == " << Build().exit_code() << std::endl;
    }
    
    //  Обрабатываем этап установки в директорию _install
    else if (vm.count("install"))
    {
      if (Make().exit_code())
      	std::cerr << "make\truntime error" << std::endl;

      if (Build().exit_code())
      	std::cerr << "build\truntime error" << std::endl;

      std::cout << "code == " << Target("install").exit_code() << std::endl;
    }

    //  Обрабатываем этап упаковки в архив формата tar.gz
    else if (vm.count("pack"))
    {
      if (Make().exit_code())
      	std::cerr << "make\truntime error" << std::endl;

      if (Build().exit_code())
      	std::cerr << "build\truntime error" << std::endl;

      std::cout << "code == " << Target("package").exit_code() << std::endl;
    }

    //  Обрабатываем время ожидания
    else if (vm.count("timeout"))
    {
      int tim = vm["timeout"].as<int>();

      if (Make(tim).exit_code())
      	std::cerr << "make\truntime error" << std::endl;

      std::cout << "code == " << Build(tim).exit_code() << std::endl;
    }

    //  default buld
    else {
      if (Make().exit_code())
        std::cerr << "make\truntime error" << std::endl;

      std::cout << "code == " << Build().exit_code() << std::endl;
    }
    return 0;
}
