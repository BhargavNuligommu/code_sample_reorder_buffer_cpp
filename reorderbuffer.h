//reorder buffer header file 
#include "cpu_stage.h"
#include "cpu_register.h"
#include <deque>

#ifndef REORDER_BUFFER_H
#define REORDER_BUFFER_H


class ReorderBuffer{

private:

	int max_size = 20;
	std::deque<Stage> reorder_buffer;

public:

	ReorderBuffer(); //constructor
	~ReorderBuffer(); //destructor

	void show_contents();

	void init();

	bool isEmpty();

    bool check_robhead(Stage& stage);

	void flush_contents(int cycle);

	void commit_register_values(Registers &reg);

	bool push_robStage(Stage &stage);

};

#endif
