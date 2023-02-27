#include <iostream>
#include <vector>
#include <unordered_map>
#include "text.hpp"
#include "io.hpp"
#include "cpp_lang.hpp"
#include <algorithm>

using namespace std;

// Function declarations
template <class T>
void print_vec_sameline(vector<T> vec);

vector<string> process_cmd(string cmd);
vector<string> translate_cmd(vector<string> cmd);
vector<string> transform_cmd(vector<string> cmd, vector<string> match);


// Function definitions
template <class T>
void print_vec_sameline(vector<T> vec) {
	int i = 1;
	for ( const T& item : vec ) {
		if ( i == vec.size() ) {
			cout << item << endl;
		} else {
			cout << item << ", ";
		}
		i++;
	}
}

vector<string> process_cmd(string cmd) {
	vector<string> fcmd;
	bool is_block = false;
	bool is_start = true;
	int pos = 0;

	for ( const char& c : cmd ) {
		if ( is_start == true ) { fcmd.push_back(""); is_start = false; }
		if ( c == '<' || c == '>' ) { is_block = !is_block; }
		
		if ( is_block == true ) {
			fcmd.at(pos) += c;
		} else {
			if ( c == ' ' ) { pos++; is_start = true; continue; }
			fcmd.at(pos) += c;
		}
	}
	return fcmd;
}

vector<string> transform_cmd(vector<string> cmd, vector<string> match) {
	vector<string> result;
	
	for ( const string& part : match ) {
		if ( part == "n" || part == "v" ) { continue; }

		if ( part.find("{") != string::npos && part.find("}") != string::npos ) {		
			string npart = part;
			int first = npart.find("{");
			int last = npart.find("}");

			int index = stoi(
				npart.substr(first + 1, (last - first) - 1) 
			);

			string sub = cmd.at(index);
			if ( sub.at(0) != '<' && sub.at(sub.size() - 1) != '>' && npart.at(0) != '<' && npart.at(npart.size() - 1) != '>' ) {
				sub.insert(0, "<");
				sub.insert(sub.size(), ">");
			}
            if ( sub.at(0) == '<' && sub.at(sub.size() - 1) == '>' && npart.at(0) == '<' && npart.at(npart.size() - 1) == '>' ) {
                sub = sub.substr(1, sub.size() - 2);
            }

			if ( part.at(0) != '<' && part.at(part.size() - 1) != '>' ) { last += 1; }

			npart.replace(first, last, sub);

			result.push_back(npart);
			continue;
		}

		if ( part.at(0) == '|' ) {
			string npart = part;
			int index = stoi(
				npart.substr(1, npart.size() - 1)
			);

			int i = 0;
			for ( const string& arg : cmd ) {
				if ( i > index ) { 
					if ( arg.at(0) != '<' && arg.at(arg.size() - 1) != '>' ) {
						result.push_back("<" + arg + ">");
					} else {
						result.push_back(arg);
					}
				}
				i++;
			}

			continue;
		}
		
		result.push_back(part);
	}

	if ( result.at(0) == "[ac]" ) {
		int i = 0;
		int count = 0;

		for ( const string& part : result ) {
			if ( i > 1 ) { count++; }
			i++;
		}
		result.at(0) = to_string(count);
	}

	return result;
}

vector<string> translate_cmd(vector<string> cmd) {
	vector<string> result;
	string arg0 = cmd.at(0);
	vector<string> match = cpp_lang::keyword_translations.at(arg0);
	string type = match.at(0);
		
	if ( type == "n" ) {
		return transform_cmd(cmd, match);
	} else {
		match.erase(match.begin());
		return match;
	}
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cout << "Incorrect number of arguments!" << endl;
		cout << "Example: occ main.gxs out.gxc" << endl;
		return 1;
	}

	// File metadata and lines
	string						file_name = argv[1];
	string						out_file_name = argv[2];
	vector<string>				lines = io::basic_read_lines(file_name);

	// Properties read from file
	string						target_line = lines.at(0); // target stored on first line		
	vector<string> 				target_args = text::index_sep(target_line, ' '); // args separated by spaces
	string						target_name = target_args.at(1); 

	// Variables used for storage later
	vector<vector<string>>		cmds;
	vector<string>				res;

	/* Debugging lines, enable if necessary
	cout << "target_line: " << target_line << endl;
	cout << "target_name: " << target_name << endl;
	*/

	// Parse lines and insert into cmds vector
	for ( const string& line : lines ) {
		// Skip line if it is only spaces, tabs, or if it starts with a # (comment)
		if ( text::char_count(line, ' ') == line.size() || text::char_count(line, '\t') == line.size() || line.at(0) == '#')
			continue;

		vector<string> cmd = process_cmd(line);

		// Add cmd to vector of all cmds
		cmds.push_back(cmd);
	}

	for ( const vector<string>& cmd : cmds ) {
		vector<string> tcmd = translate_cmd(cmd);
		string line;

		int i = 1;
		for ( const string& part : tcmd ) {
			if ( i == tcmd.size() ) {
				line += part;
			} else {
				line += (part + "\t");
			}
			i++;
		}
		res.push_back(line);
	}

	io::basic_write_lines(out_file_name, res);

	return 0;
}
