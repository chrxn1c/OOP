#include "Application.h"
#include "BaseClass.h"
#include "Node1.h"
#include "Node2.h"
#include <iostream>


Application::Application(BaseClass* parent, std::string name) : BaseClass(parent, name) {
	this->changeParent(parent);
	this->setName(name);
}


void Application::inputHierarchy() {
	std::string applicationName;
	std::cin >> applicationName;
	this->setName(applicationName);

	std::string parentName, childName;
	int nodeCounter = 0;

	while (std::cin >> parentName >> childName && parentName != childName) {
		BaseClass* parent = this->findParent(parentName); 
		
		BaseClass* child;
		if (++nodeCounter % 2 == 1)
			child = new Node1(parent, childName);
		else
			child = new Node2(parent, childName);
	}
}


void Application::buildHierarchy() {
	this->inputHierarchy();
	std::cout << this->getName(); 
	this->printRoot();
}


int Application::start() {
	return 0;
}


Application::~Application() {
	for (BaseClass*& child : children)
		child->recursiveCleanUp();
}
