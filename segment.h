#ifndef SEGMENT_H
#define SEGMENT_H

#include <deque>
#include "vehicle.h"

using namespace std;

class Segment{
	const unsigned int nodes;
	const unsigned int position;
	const unsigned int capacity;
	deque<Vehicle *> q;
	Segment * right;
	Segment * left;
	bool import_new_vehicle();
	unsigned int init();
	bool is_last() const;
	bool is_first() const;
	Vehicle * pop();
	unsigned int exit();
	unsigned int pass();
	unsigned int get_no_of_ready() const;
	bool exit_vehicles;
	bool incoming_vehicles;
public:
	Segment(unsigned int, unsigned int, unsigned int, unsigned int&);
	void set_right(Segment *);
	void set_left(Segment *);
	unsigned int set_ready();
	void set_exit_vehicles();
	void set_not_exit_vehicles();
	void set_incoming_vehicles();
	void set_not_incoming_vehicles();
	unsigned int get_capacity() const;
	unsigned int get_load() const;
	unsigned int get_vehicles() const;
	bool is_full() const;
	bool is_empty() const;
	bool enter(Vehicle *);
	bool operate(unsigned int&);
	void print() const;
	~Segment();
};

#endif // !SEGMENT_H
