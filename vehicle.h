#ifndef VEHICLE_H
#define VEHICLE_H

using namespace std;

class Vehicle{
	const string plate_number;
	bool ready;				/*Ready to leave a segment-node*/
	unsigned int position;			/*Current node*/
	unsigned int destination;		/*Destination node*/
	string new_plate_number() const;
public:
	/*Default Constructor*/
	Vehicle(const unsigned int p, const unsigned int d);
	unsigned int get_destination() const;
	string get_plate_number() const;
	unsigned int get_position() const;
	bool is_ready() const;
	void set_not_ready();
	void set_ready();
	void set_position(const unsigned int);
	bool can_exit() const;
	void print() const;
	~Vehicle();
};

#endif // !VEHICLE_H
