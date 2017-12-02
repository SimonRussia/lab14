#include "json.hpp"
#include <iostream>
#include <fstream>
#include <iomanip> // for std::setw

using json = nlohmann::json;

struct Email {
  std::string nickname;
  std::string server;
};

struct Person {
  std::string  first_name;
  std::string  last_name;
  Email        email;
  size_t       age;
  std::string  phone;
  void devideEmail();
};


int main(int argc, char const *argv[]) {
	try {
		if(argc == 1)
			throw std::runtime_error("ERROR: have no any path...");

		Person A;

		std::cout << "Enter data to fields of the Person structure." << std::endl;
		std::cout << "First name:" << std::endl;
		std::cin >> A.first_name;
		std::cout << "Last name:" << std::endl;
		std::cin >> A.last_name;
		std::cout << "Email:" << std::endl;
		A.devideEmail();
		std::cout << "Age(optional):" << std::endl;
		std::cin >> A.age;
		std::cout << "Phone(optional):" << std::endl;
		std::cin >> A.phone;

		json j = {
			  { "Fisrt name",	A.first_name },
			  { "Last name",	A.last_name },
			  { "Email",		A.email.nickname + A.email.server },
			  { "Age",			A.age },
			  { "Phone",		A.phone }
		};

		std::ofstream out( argv[1] );
		out << std::setw(4) << j << std::endl;
		out.close();

	} catch(const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

	return 0;
}

void Person::devideEmail() {
  	std::string address;
  	std::cin >> address;
  	std::string::size_type pos = address.find("@");
	if(pos != std::string::npos) {
		email.nickname = address.substr(0, pos);
		email.server = address.substr(pos);
	} else {
		throw std::runtime_error("ERROR: incorret email address...");
	}
};
