#include <iostream>
#include "ReorderBuffer.h"

/*
The above header file(rob.h) contains below ROB class which contains all the Reorder Buffer Prototypes.

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

*/

ReorderBuffer::ReorderBuffer() {
    this->init();
}

ReorderBuffer::~ReorderBuffer() {
    // destructor, empty for now
}

// Display the instructions present in the Reorder Buffer
// it contains all the stage info
void ReorderBuffer::show_contents() {
    std::cout << "ReorderBuffer Contents:" << std::endl;
    for (auto stage : reorder_buffer) {
        stage.show_contents();
    }
}

//make the Reorder buffer empty
void ReorderBuffer::init() {
    reorder_buffer.clear();
}

//check if reorder buffer empty or not
bool ReorderBuffer::isEmpty() {
    return reorder_buffer.empty();
}

//commit the values to the registers and remove the commited instruction
void ReorderBuffer::commit_register_values(Registers &reg) {
    if (!isEmpty()) {
        Stage stage = reorder_buffer.front();
        if (stage.getCompletionCycle() <= reg.getCommitCycle()) {
            reg.setValue(stage.getDestReg(), stage.getResult());
            reorder_buffer.pop_front();
        }
    }
}

//push the instructions to the Reorder buffer
bool ReorderBuffer::push_robStage(Stage &stage) {
    if (reorder_buffer.size() < max_size) {
        reorder_buffer.push_back(stage);
        return true;
    }
    else {
        return false;
    }
}

// check the reorder buffer head with current pc
bool ReorderBuffer::check_robhead(Stage& stage) {
    if (!isEmpty()) {
        Stage head = reorder_buffer.front();
        return head.getPC() == stage.getPC() && head.getOpType() == stage.getOpType();
    }
    else {
        return false;
    }
}

// remove all the instructions in the rob.
void ReorderBuffer::flush_contents(int cycle) {
    while (!isEmpty()) {
        Stage stage = reorder_buffer.front();
        if (stage.getCompletionCycle() > cycle) {
            break;
        }
        reorder_buffer.pop_front();
    }
}
