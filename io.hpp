/*	GENERIC COMPILER TOOLS
 *	LIB-IO HEADER
 *	USED TO EASILY MANAGE FILES
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

namespace io {

std::vector<std::string> basic_read_lines(std::string name) {
	std::ifstream file(name);

	if (!file.good()) {
		std::cout << "[basic_read_lines(" << name << ")]{error: bad file read}" << std::endl;
		std::cout << "[basic_read_lines(" << name << ")]{exit_status: 1}" << std::endl;
		file.close();
		exit(1);
	}

	std::vector<std::string> lines;

	if (file.is_open()) {
		std::string line;
		while(std::getline(file, line)) {
			lines.push_back(line);
		}
	} else {
		lines[0] = "err";
	}
	file.close();
	return lines;
}

int basic_write_lines(std::string name, std::vector<std::string> lines) {
	std::ofstream file(name);

	if (file.is_open()) {
		for ( const std::string& line : lines ) {
			file << line << std::endl;
		}
	} else {
		std::cout << "[basic_write_lines(" << name << ", vector<string> @lines)]{error: bad file write}" << std::endl;
		return 1;
	}
	return 0;
}

}
