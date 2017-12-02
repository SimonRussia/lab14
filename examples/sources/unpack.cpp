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
  void devideEmail(std::string _email);
};


int main(int argc, char const *argv[]) {
	try {
		if(argc == 1)
			throw std::runtime_error("ERROR: have no any path...");
		
		std::ifstream in( argv[1] );
		json j;
		in >> j;
		in.close();

		Person A;

		A.first_name = j["Fisrt name"];
		A.last_name = j["Last name"];
		A.age = j["Age"];
		A.phone = j["Phone"];
		A.devideEmail( j["Email"] );

		std::cout << "[Person]" << std::endl;
		std::cout << "Fisrt name:\t" << A.first_name << std::endl;
		std::cout << "Last name:\t" << A.last_name << std::endl;
		std::cout << "Email:\t\t" << A.email.nickname << A.email.server << std::endl;
		std::cout << "Age:\t\t" << A.age << std::endl;
		std::cout << "Phone:\t\t" << A.phone << std::endl;

	} catch(const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

	return 0;
}

void Person::devideEmail(std::string _email) {
  	std::string::size_type pos = _email.find("@");
	if(pos != std::string::npos) {
		email.nickname = _email.substr(0, pos);
		email.server = _email.substr(pos);
	} else {
		throw std::runtime_error("ERROR: incorret email address...");
	}
};