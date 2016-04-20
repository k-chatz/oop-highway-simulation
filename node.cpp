#include <iostream>
#include <cstdlib>
#include <string>

#include "node.h"
#include "spchar.h"

extern void separate(const string, const char, const char, const char);
extern bool print;
extern bool debug;

using namespace std;
using namespace spchar;

/**Private**/
bool Node::is_first() const { return (position == 0); }
bool Node::is_last() const { return (position + 1 == nodes); }

/**Public**/

Node::Node(const unsigned int p, const string name, const unsigned int n, const unsigned int K, unsigned int& enter_v)
: position(p), name(name), nodes(n), K(K), entry(NULL), segment(NULL), right(NULL), left(NULL)
{
	if (!is_last()){
		int capacity = 0;
		do{
			cout << "Enter a positive number for segment " << position + 1 << " capacity: ";
			cin >> capacity;
		} while (capacity < 0);
		segment = new Segment(position, nodes, (unsigned int)capacity, enter_v);
		entry = new Entry(position, nodes, *segment, K, enter_v);
	}
	/*there is no segment after node[nodes - 1] , and it has no entrance!*/
	if (::debug) cout << dark_magenta << "\nNode '" << name << "' at position: " << position + 1 << " has just been created!" << rst << endl;
}

inline string Node::get_name(){ return name; }

inline unsigned int Node::get_position() const{ return position; }

unsigned int Node::get_capacity() const {
	if (!is_last())
		return entry->get_capacity() + segment->get_capacity();
	else
		return 0;
}

unsigned int Node::get_entry_load() const{
	if (!is_last())
		return entry->get_load();
	else
		return 0;
}

unsigned int Node::get_entry_vehicles() const{
	if (!is_last())
		return entry->get_vehicles();
	else
		return 0;
}

unsigned int Node::get_segment_load() const{
	if (!is_last())
		return segment->get_load();
	else
		return 0;
}

unsigned int Node::get_vehicles() const{
	if (!is_last())
		return segment->get_vehicles() + entry->get_vehicles();
	else
		return 0;
}

void Node::set_right(Node* right_node){
	if (right_node != NULL){
		right = right_node;
		segment->set_right(right->segment);
	}
}

void Node::set_left(Node* left_node){
	if (left_node != NULL){
		left = left_node;
		segment->set_left(left->segment);
	}
}

void Node::print() const{
	if (!is_last()){
		segment->print();
		entry->print();
	}
}

bool Node::operate(unsigned int& enter_v, unsigned int& left_v) const {
	unsigned int delay = 0;
	if (::print) cout << "Node: " << name << (is_last() ? " (Terminal)" : (is_first() ? " (Start)" : "")) << endl;
	if (!is_last()){
		unsigned int ready = 0;
		if (segment->operate(left_v)){
			cout << yellow << "\n+Delays after node " << position + 1 << rst;
			delay++;
		}

		if (entry->operate(enter_v)){
			cout << yellow << "\n+Delays in the entrance of node " << position + 1 << rst;
			delay++;
		}

		ready = segment->set_ready();
		if (::print) cout << dark_aqua << "\n-Ready vehicles: " << ready << rst << endl;
	}
	return delay == 0;
}


Node::~Node(){
	if (segment != NULL)
		delete segment;
	if (entry != NULL)
		delete entry;
	if (::debug) cout << dark_magenta << "\nNode " << name << " is about to be destroyed!" << rst << endl;
}
