#ifndef __NODE3_H
#define __NODE3_H

#include "BaseClass.h"

class Node3 : public BaseClass {
public:
	Node3(BaseClass* parent, std::string name = "Node3Object");
	void signal(std::string& message) override;
	void handler(std::string message) override;
	SIGNAL_TYPE getSignal() override;
	HANDLER_TYPE getHandler() override;
};

#endif // __NODE3_H