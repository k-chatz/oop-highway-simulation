#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <sstream>		/*ostringstream*/

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

#include "highway.h"
#include "spchar.h"

using namespace std;
using namespace spchar;

unsigned int screen_column_size(){
	unsigned int col = 0;
#ifdef _WIN32
	/*The following code is from:
	* http://stackoverflow.com/questions/6812224/getting-terminal-size-in-c-for-windows
	*/
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	col = csbi.srWindow.Right - csbi.srWindow.Left + 1;
#else
	/*The following code is from:
	* http://stackoverflow.com/questions/1022957/getting-terminal-width-in-c
	*/
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	col = w.ws_col;		
#endif
	return col;
}

void separate(const string description, const char l_corner, const char intermediate, const char r_corner){
	unsigned int col = screen_column_size(), length = description.length(), L = (col / 2) - (length / 2) - 1;
	ostringstream out;

	out << endl;
	for (unsigned int i = 0; i < col; i++){
		if (i == 0)
			out << l_corner;
		else if (i <= L)
			out << intermediate;
		else if (i > L && i <= L + length){
			out << description;
			i = L + length;
		}
		else if (i > L + length){
			if (i < col - 1)
				out << intermediate;
			else
				out << r_corner;
		}
	}
	cout << out.str();
}

unsigned int percent = 0;
bool toll_size_input = false, initialize = false, manually = false, print = false, debug = false;

int main(int argc, char * argv[]){
	srand((unsigned int)time(NULL));

	//The following variables will take values ​​from the command line:
	unsigned int N = 0, NSegs = 0, K = 0;

	if (argc < 5){
		cerr
			<< "Invalid arguments!\nRun again with these integer values:\n"
			<< "[N: >= 0] [NSegs: >= 0] [K: >= 0] [Percent: 0/100] [Toll size input 0/1] [Initialize: 0/1] [Manually: 0/1] [Print: 0/1] [Debug: 0/1]" << endl;
		cin.get();
		exit(1);
	}
	else{
		for (int i = 0; i < argc; i++){
			switch (i){
			case 1:
				N = atoi(argv[i]);
				N = (N >= 0) ? N : 0;
				break;
			case 2:
				NSegs = atoi(argv[i]);
				NSegs = (NSegs >= 0) ? NSegs : 0;
				break;
			case 3:
				K = atoi(argv[i]);
				K = (K >= 0) ? K : 0;
				break;
			case 4:
				percent = atoi(argv[i]);
				percent = (percent >= 0) ? percent : 0;
				break;
			case 5:
				toll_size_input = (atoi(argv[i]) > 0 ? true : false);
				break;
			case 6:
				initialize = (atoi(argv[i]) > 0 ? true : false);
				break;
			case 7:
				manually = (atoi(argv[i]) > 0 ? true : false);
				break;
			case 8:
				print = (atoi(argv[i]) > 0 ? true : false);
				break;
			case 9:
				debug = (atoi(argv[i]) > 0 ? true : false);
				break;
			}
		}
	}

	cout
		<< "Start Highway Simulation with: " << N << " simulation cycles, "
		<< NSegs << " segments for highway, " << K << " (K) maximum number of vehicles that can enter into a segment of highway."
		<< percent << "% vehicles at segments in highway can switches to standby.";

	separate("", '_', '_', '_');
	cout << "Press enter to continue..";
	cin.get();
	{
		cout << "\nMessages from constructors or initialization:" << endl;
		Highway hw(NSegs, K);
		cin.get();

		for (unsigned int i = 0; i < N; i++){
			ostringstream cycle;
			cycle << "CYCLE " << i + 1 << " STARTS";

			cout << bg_green << black;
			separate(cycle.str(), '-', '-', '-');
			cout << rst;

			hw.operate();

			hw.print();

			if (manually){
				cout << "\nPress enter to continue..";
				cin.get();
			}
			cout << endl;
		}
		cout << "The simulation has ended!" << endl;
		cin.get();
	}
#ifdef _WIN32
	cin.get();
#endif
	return 0;
}
