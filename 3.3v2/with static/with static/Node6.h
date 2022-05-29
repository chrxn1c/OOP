#ifndef __NODE6_H
#define __NODE6_H

#include "BaseClass.h"

class Node6 : public BaseClass {
public:
	Node6(BaseClass* parent, std::string name = "Node6Object");
	void signal(std::string& message) override;
	void handler(std::string message) override;
	SIGNAL_TYPE getSignal() override;
	HANDLER_TYPE getHandler() override;
};

#endif // __NODE6_H