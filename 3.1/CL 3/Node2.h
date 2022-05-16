#ifndef __NODE2_H
#define __NODE2_H

#include "BaseClass.h"

class Node2 : public BaseClass {
public:
	Node2(BaseClass* parent, std::string name = "Node2Object") : BaseClass(parent, name) {}
};

#endif // __NODE2_H
