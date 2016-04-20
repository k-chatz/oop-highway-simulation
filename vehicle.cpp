#include <iostream>
#include <iomanip>		/*setfill() - setw()*/
#include <cstdlib>		/*Rand*/
#include <string>
#include <sstream>		/*ostringstream*/

#include "vehicle.h"

extern bool print;
extern bool debug;

#include "spchar.h"

using namespace std;
using namespace spchar;

/*Private*/

/* There are 175.760.000 different possible outcomes
* The possibility of 2 vehicles having the same
* plate number is about 0.000000005689576695493855257169
* ( or 0.0000005689576695493855257169 % )
* If 2 or more vehicles have the same plate number then it's fake :P*/
string Vehicle::new_plate_number() const {
	ostringstream plate_number;
	plate_number
		<< (char)(rand() % 26 + 65)
		<< (char)(rand() % 26 + 65)
		<< (char)(rand() % 26 + 65)
		<< "-"
		<< setfill('0') << setw(4)
		<< rand() % 10000;
	return plate_number.str();
}

/*Public*/

/*Default Constructor*/
Vehicle::Vehicle(const unsigned int p, const unsigned int d)
: plate_number(new_plate_number()), ready(false), position(p), destination(d){
	if (::debug){
		cout 
			<< dark_magenta << "\nVehicle with plate number: '" << plate_number 
			<< "' and destination: " << destination + 1 << " has just been created!" << rst << endl;
	}
}

unsigned int Vehicle::get_destination() const { return destination; }

string Vehicle::get_plate_number() const { return plate_number; }

unsigned int Vehicle::get_position() const { return position; }

bool Vehicle::is_ready() const { return ready; }

void Vehicle::set_not_ready(){ ready = false; }

void Vehicle::set_ready(){ ready = true; }

void Vehicle::set_position(const unsigned int c){ position = c; }

/*Return true if is ready to leave the segment-node and is at the destination. */
bool Vehicle::can_exit() const { return (position + 1 == destination); }

/*Print a vehicle*/
void Vehicle::print() const{
	cout << (ready ? green : blue) << "{" << plate_number << "|" << position + 1 << "|" << destination + 1 << "} " << rst;
}

Vehicle::~Vehicle(){
	if (::debug){
		cout
			<< dark_magenta << "\nVehicle with plate number: '" << plate_number 
			<< "' and destination: " << destination + 1 << "' is about to be destroyed!" << rst << endl;
	}
}
