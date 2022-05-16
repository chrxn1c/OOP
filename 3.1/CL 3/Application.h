#ifndef __APPLICATION_H
#define __APPLICATION_H

#include "BaseClass.h"

class Application : public BaseClass {
public:
	Application(BaseClass* parent, std::string name = "Application");
	void inputHierarchy();
	void buildHierarchy();
	int start();
	~Application();
};

#endif // __APPLICATION_H