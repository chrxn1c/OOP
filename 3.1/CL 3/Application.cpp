#include "Application.h"
#include "BaseClass.h"
#include "Node2.h"
#include "Node3.h"
#include "Node4.h"
#include "Node5.h"
#include "Node6.h"
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
	int nodeNumber = 0;

	while (std::cin >> parentName && parentName != "endtree" && std::cin >> childName >> nodeNumber) {
		BaseClass* parent = this->findObject(parentName);
		BaseClass* child;

		switch (nodeNumber) {
		case 2: { child = new Node2(parent, childName); break; }
		case 3: { child = new Node3(parent, childName); break; }
		case 4: { child = new Node4(parent, childName); break; }
		case 5: { child = new Node5(parent, childName); break; }
		case 6: { child = new Node5(parent, childName); break; }
		}
	}

	std::string objectName;
	int objectReadiness;

	while (std::cin >> objectName >> objectReadiness && objectName != "Z") {
		BaseClass* object = findObject(objectName);
		if (objectReadiness)
			object->setTrueReadiness(object);
		else
			object->setFalseReadiness(object);

	}
}



void Application::buildHierarchy() {
	this->inputHierarchy();

	if (this->getName() != "") {
		std::cout << "Object tree";
		this->printRoot();
		std::cout << std::endl << "The tree of objects and their readiness";
		this->printReadinessRoot();
	}
}


int Application::start() {
	return 0;
}


Application::~Application() {
	for (BaseClass*& child : children)
		child->recursiveCleanUp();
}




