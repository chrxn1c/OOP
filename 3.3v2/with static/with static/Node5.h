#ifndef __NODE5_H
#define __NODE5_H

#include "BaseClass.h"

class Node5 : public BaseClass {
public:
	Node5(BaseClass* parent, std::string name = "Node5Object");
	void signal(std::string& message) override;
	void handler(std::string message) override;
	SIGNAL_TYPE getSignal() override;
	HANDLER_TYPE getHandler() override;
};

#endif // __NODE5_H