/*
 * C++ HEADER FILE FOR OPEN CROSS COMPILER
*/
#include <unordered_map>
#include <vector>

using namespace std;

string ctab = "\t\t";



namespace cpp_lang {


// Vanilla gxc calls (vgxcc) - standalone calls that do not require args
unordered_map<string, vector<string>> vgxcc = {
	
	{"start", {"v", "1", "call", "start"}},
	
	{"end", {"v", "1", "call", "end"}},

};

unordered_map<string, vector<string>> keyword_translations = {
	
	{"@target",			{"n", "#target", "{1}"}},
	
	{"@make",			{"n", "2", "call", "make", "{1}"}},

	{"@add_text",		{"n", "2", "call", "addt", "{1}"}},

	{"@define",			{"n", "3", "def", "+{1}", "<{2}>", "<{3}>"}}, 

	{"@print",			{"n", "[ac]", "call", "vp", "|0"}},

	{"@start",			vgxcc.at("start")},
	
	{"@end",			vgxcc.at("end")},

};


}
