#ifndef RAND_H
#define RAND_H

class Unique_Rand{
	unsigned int min;
	unsigned int max;
	int ** values;
	int index;
	void inline swap_(int&, int&);
	void reset();
public:
	Unique_Rand(const unsigned int, const unsigned int);
	void print() const;
	const int get();
	~Unique_Rand();
};

#endif