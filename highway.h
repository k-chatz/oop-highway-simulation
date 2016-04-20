#ifndef HIGHWAY_H
#define HIGHWAY_H

#include "node.h"
#include "spchar.h"

using namespace spchar;

using namespace std;

class Highway{
	const unsigned int nodes;
	unsigned int enter_v;
	unsigned int left_v;
	unsigned int max_traffic;
	Node ** n;
public:
	Highway(const unsigned int, const unsigned int);
	unsigned int get_capacity() const;
	unsigned int get_vehicles() const;
	unsigned int get_load(unsigned int, unsigned int) const;
	unsigned int get_max_traffic();
	void operate();
	void print();
	~Highway();
};

#endif // !HIGHWAY_H
