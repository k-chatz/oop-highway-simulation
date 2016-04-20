#include <iostream>

#include "spchar.h"

using namespace std;

namespace spchar{
	spchar get_load_color(unsigned int load){
		return (load > 25 ? load > 50 ? load > 75 ? red : orange : yellow : green);
	}

	ostream& operator<<(ostream& os, const spchar ch_code){
#ifndef _WIN32
		unsigned int code = (unsigned int)ch_code;
		if (code > 10 && code < 30 && code != 0){
			code += 10;
			os << "\033[" << "1;" << code << "m";
		}
		else
			os << "\033[" << code << "m";
#endif
		return os;
	}

}
