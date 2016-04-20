#include <iostream>
#include <string>
#include <sstream>		/*ostringstream*/

#include "highway.h"
#include "spchar.h"

extern void separate(const string, const char, const char, const char);
extern bool print;
extern bool debug;

using namespace std;
using namespace spchar;

Highway::Highway(const unsigned int NSegs, unsigned int K)
: nodes(NSegs + 1), enter_v(0), left_v(0), max_traffic(0)
{
	n = new Node*[nodes];
	Node* tmp = NULL;

	for (unsigned int i = 0; i < nodes; i++){
		ostringstream name;
		name << 'Y' << i + 1;
		n[i] = new Node(i, name.str(), nodes, K, enter_v);

		/*if it's the first , set left to NULL*/
		n[i]->set_left(tmp);

		/*if it's not the first , left has a pointer
		to right and it's the one we just created*/
		if (tmp != NULL) tmp->set_right(n[i]);

		/*Now tmp we set to point to the segment that was created in the end,
		we dont set right of the last node. But it's NULL by default*/
		tmp = n[i];
	}

	if (::debug) cout << dark_magenta << "\nHighway has just been created!" << rst << endl;
}

unsigned int Highway::get_capacity() const{
	unsigned int c = 0;
	for (unsigned int i = 0; i < nodes; i++){
		c += n[i]->get_capacity();
	}
	return c;
}

unsigned int Highway::get_vehicles() const{
	unsigned int v = 0;
	for (int i = nodes - 1; i >= 0; i--)
		v += n[i]->get_vehicles();
	return v;
}

unsigned int Highway::get_load(unsigned int vehicles, unsigned int capacity) const{
	return (capacity > 0 ? (vehicles * 100 / capacity) : 0);
}

unsigned int Highway::get_max_traffic(){
	unsigned int v = get_vehicles();
	if (v > max_traffic)
		max_traffic = v;
	return max_traffic;
}

void Highway::operate(){
	cout << dark_aqua << "The highway is running" << endl << rst;
	for (int i = nodes - 1; i >= 0; i--){
		if (::print) separate("", '_', '_', '_');

		if (n[i]->operate(enter_v, left_v)){
			if (i == nodes - 1)
				cout << green << "\n+Thank you for driving safely on the highway!" << rst;
			else
				cout << green << "\n+Observe safety distances in the segment after the node " << i + 1 << "!" << rst;
		}

		if (::print) n[i]->print();
	}
}

void Highway::print(){
	//separate("", '_', '_', '_');
	unsigned int vehicles = get_vehicles(), capacity = get_capacity(), max_traffic = get_max_traffic();
	unsigned int l1 = get_load(vehicles, capacity), l2 = get_load(max_traffic, capacity);
	cout
		<< dark_aqua << "\n\n+Available: " << vehicles << "/" << capacity << ' ' << get_load_color(l1)
		<< l1 << "%" << rst << dark_aqua << " (Record: " << max_traffic << ' ' << get_load_color(l2)
		<< l2 << "%" << rst << dark_aqua << ") - Entering: " << enter_v << " - Left: " << left_v
		<< "\nThe highway has " << nodes - 1 << " entry nodes: => " << rst;

	for (unsigned int i = 0; i < nodes - 1; i++){
		l1 = n[i]->get_entry_load(); l2 = n[i]->get_segment_load();
		cout << dark_aqua << '[' << get_load_color(l1) << l1 << '%' << rst << dark_aqua << '|' << get_load_color(l2) << l2 << '%' << rst << dark_aqua << "] => ";
	}

	cout << "[Terminal]" << rst << endl;
}


Highway::~Highway(){
	if (::debug) cout << dark_magenta << "\nHighway object is about to be destroyed!" << rst << endl;
	for (unsigned int i = 0; i < nodes; i++)
		delete n[i];
	delete[] n;
}
