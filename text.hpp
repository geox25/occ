/*	GENERIC COMPILER TOOLS
 *	LIB-TEXT HEADER
 *	USED FOR TEXT MANIPULATION
*/
#include <vector>

namespace text {

int char_count(std::string str, char c) {
	int total = 0;

	for (int i = 0; i < str.size(); i++) {
		if (str[i] == c) {
    		total++;
		}
	}
	return total;
}

std::vector<std::string> index_sep(std::string str, char delimeter) {
	int words = (char_count(str, delimeter) + 1);
	std::vector<std::string> vec;

	int i = 0;
	while (i < words) {
    	vec.push_back("");
    	i++;
  	}

  	int pos = 0;
  	for (int i = 0; i < str.size(); i++) {
    	if (str[i] == delimeter) {
      		pos++;
    	} else {
      		vec.at(pos) += str[i];
    	}
 	}

  	return vec;
}

std::vector<std::string> index_tab_args(std::string str) {
	std::vector<std::string> u_args = index_sep(str, '\t');
	std::vector<std::string> f_args;

	for ( const std::string& item : u_args ) {
		if (item == "" || item == "\t" || char_count(item, ' ') == item.size()) {
			// skip element if empty
		} else {
			// otherwise, add to final vector of strings
			f_args.push_back(item);
		}
	}
	return f_args;
}

}
