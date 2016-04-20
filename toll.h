#ifndef TOLL_H
#define TOLL_H

#include <deque>

#include "vehicle.h"
#include "segment.h"

using namespace std;

class Toll{
	const unsigned int nodes;
	const unsigned int position;
	const unsigned int toll;
	unsigned int capacity;
	Segment& segment;
	const bool epass;
	deque<Vehicle *> q;
	void import_new_vehicle();
	unsigned int init();
	void push(Vehicle *);
	Vehicle * pop();
public:
	Toll(Segment&, bool, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int&);
	void set_capacity(const unsigned int);
	bool is_active() const;
	bool is_full() const;
	bool is_empty() const;
	bool is_epass() const;
	unsigned int get_load() const;
	unsigned int get_vehicles() const;
	unsigned int get_free_size() const;
	unsigned int get_capacity() const;
	void import_vehicle(Vehicle *);
	bool pass_vehicle_to_segment();
	void print() const;
	~Toll();
};

#endif // !TOLL_H
