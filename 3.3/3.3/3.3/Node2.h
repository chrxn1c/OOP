#ifndef __NODE2_H
#define __NODE2_H

#include "BaseClass.h"

class Node2 : public BaseClass {
public:
	Node2(BaseClass* parent, std::string name = "Node2Object");
	void signal(std::string&) override;
	void handler(std::string) override;
	SIGNAL_TYPE getSignal() override;
	HANDLER_TYPE getHandler() override;

};

#endif // __NODE2_H
