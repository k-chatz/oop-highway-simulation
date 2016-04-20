#ifndef SPCHAR
#define SPCHAR

#include <iostream>

namespace spchar{
	enum spchar{
		rst = 0,
		underline = 4,
		orange = 21,
		green = 22,
		yellow = 23,
		blue = 24,
		black = 30,
		red = 31,
		dark_magenta = 35,
		dark_aqua = 36,
		bg_red = 41,
		bg_green = 42
	};
	spchar get_load_color(unsigned int);
	std::ostream& operator<<(std::ostream&, const spchar);
}
#endif
