#ifndef __NODE4_H
#define __NODE4_H

#include "BaseClass.h"

class Node4 : public BaseClass {
public:
	Node4(BaseClass* parent, std::string name = "Node4Object");
	void signal(std::string& message) override;
	void handler(std::string message) override;
	SIGNAL_TYPE getSignal() override;
	HANDLER_TYPE getHandler() override;
};

#endif // __NODE4_H