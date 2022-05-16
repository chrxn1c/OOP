#ifndef __NODE1_H
#define __NODE1_H

#include "BaseClass.h"

class Node1 :public BaseClass {
public:
	Node1(BaseClass* parent, std::string name = "Node1Object") : BaseClass(parent, name) {}
};

#endif // __NODE1_H
