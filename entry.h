#ifndef ENTRY_H
#define ENTRY_H

#include "toll.h"
#include "segment.h"

class Segment;

class Entry{
	const unsigned int nodes;
	const unsigned int position;
	const unsigned int tolls;
	unsigned int capacity;
	Segment& segment;
	Toll ** toll;
	unsigned int K;
	unsigned int get_free_size();
	unsigned int import_in_tolls();
	bool import_vehicle();
	int pick_a_free_toll() const;
	unsigned int pass_to_segment();
	bool passes;
	bool imports;
public:
	Entry(unsigned int, unsigned int, Segment&, unsigned int, unsigned int&);
	void set_passes();
	void set_not_passes();
	void set_imports();
	void set_not_imports();
	unsigned int get_load() const;
	unsigned int get_vehicles() const;
	unsigned int get_capacity() const;
	bool operate(unsigned int&);
	void print() const;
	~Entry();
};

#endif
