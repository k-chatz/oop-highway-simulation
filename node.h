#ifndef NODE_H
#define NODE_H

#include "entry.h"
#include "segment.h"

using namespace std;

#include "entry.h"

class Node{
	const unsigned int nodes;
	const unsigned int position;
	const unsigned int K;
	const string name;
	Entry * entry;
	Segment * segment;
	Node * right;
	Node * left;
	bool is_first() const;
	bool is_last() const;
public:
	Node(const unsigned int, const string, const unsigned int, const unsigned int, unsigned int&);
	string get_name();
	unsigned int get_position() const;
	unsigned int get_capacity() const;
	unsigned int get_entry_load() const;
	unsigned int get_segment_load() const;
	unsigned int get_entry_vehicles() const;
	unsigned int get_vehicles() const;
	void set_right(Node*);
	void set_left(Node*);
	bool operate(unsigned int&, unsigned int&) const;
	void print() const;
	~Node();
};

#endif // !NODE_H