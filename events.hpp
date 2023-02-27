/*	GENERIC COMPILER TOOLS
 *	LIB-EVENTS HEADER
 *	TOOLS FOR EVENT MANAGEMENT
*/

class eventStr {
	const char *varname;
	const char *value;
public:
	eventStr(const char *vn, const char *v) {	
		varname = vn;
		value = v;
  	}
	eventStr &operator=(const char *str) {
		std::cout << "[" << varname << "]{" << value << " -> " << str << "}" << std::endl;
    	value = str;

    	return *this;
	}
	const char *getValue() const { return this->value; }
};
