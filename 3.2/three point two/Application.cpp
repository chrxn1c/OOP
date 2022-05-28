#include "Application.h"
#include "BaseClass.h"
#include "Node2.h"
#include "Node3.h"
#include "Node4.h"
#include "Node5.h"
#include "Node6.h"
#include <iostream>
#include <vector>

static std::vector <std::string> findSetMessages;


Application::Application(BaseClass* parent, const std::string name) : BaseClass(parent, name) {
	this->changeParent(parent);
	this->setName(name);
	currentHead = this;
}


void Application::inputHierarchy() {
	std::string applicationName;
	std::cin >> applicationName;
	this->setName(applicationName);

	std::string route, objectName;
	int nodeNumber = 0;

	while (std::cin >> route && route != "endtree") {
		std::cin >> objectName >> nodeNumber;

		if (nodeNumber < 2 || nodeNumber > 6)
			std::cin.clear();

		BaseClass* parent = findRouteObject(route);
		if (parent == nullptr) {
			this->printRoot();
			std::cout << std::endl << "The head object " << route << " is not found";
			exit(0);
		}
		BaseClass* child;

		switch (nodeNumber) {
		case 2: { child = new Node2(parent, objectName); break; }
		case 3: { child = new Node3(parent, objectName); break; }
		case 4: { child = new Node4(parent, objectName); break; }
		case 5: { child = new Node5(parent, objectName); break; }
		case 6: { child = new Node5(parent, objectName); break; }
		}
	}

	std::string command;
	while (std::cin >> command && command != "END") {
		std::cin.get();
		getline(std::cin, route, '\n');

		if (command == "FIND") {
			BaseClass* foundObject = findRouteObject(route);
			findSetMessages.push_back(findRouteObjectReport(route, foundObject));
		}

		if (command == "SET") {
			BaseClass* setObject = setRouteObject(route);
			findSetMessages.push_back(setRouteObjectReport(route, setObject));
		}
	}
}



void Application::buildHierarchy() {
	this->inputHierarchy();

	if (this->getName() != "") {
		this->printRoot();
		this->displayFindSetMessages();
	}
}


int Application::start() {
	return 0;
}


const std::string Application::subNameExtraction(const std::string& route, const std::string mode) const {

	std::string name;
	int startIndex;
	mode == "fromCurrent" ? startIndex = 0 : startIndex = 1;

	for (int i = startIndex; i < route.size() && route[i] != '/'; i++)
		name += route[i];

	return name;
}


BaseClass* Application::routeToAdress(std::string route) {
	if (route == "/")
		return this;

	else if (route == ".")
		return currentHead;

	else if (route == "")
		return nullptr;


	else if (route.size() > 2 && route[0] == '/' && route[1] == '/') {
		route.erase(0, 2);
		return this->findObjectInTree(route); //route without starting // is objectName
	}

	else if (route.size() > 2 && route[0] == '/' && route[1] != '/') {
		BaseClass* temporary = this;
		std::string name;
		while (route.size() && temporary != nullptr) {
			name = subNameExtraction(route, "fromApplication");
			route.erase(0, name.size() + 1);
			temporary = temporary->findObjectAmongChildren(name);
		}

		return temporary;
	}

	else if (route.size() > 2 && route[0] != '/') {
		BaseClass* temporary = currentHead;
		std::string name;
		while (route.size() && temporary != nullptr) {
			name = subNameExtraction(route, "fromCurrent");
			route.erase(0, name.size() + 1);
			temporary = temporary->findObjectAmongChildren(name);
		}

		return temporary;
	}


	return nullptr;
}




BaseClass* Application::findRouteObject(const std::string& route) {
	return routeToAdress(route);
}


const std::string Application::findRouteObjectReport(const std::string& route, const BaseClass* foundObject) const {
	if (foundObject != nullptr)
		return std::string("\n" + route + "     " + "Object name: " + foundObject->getName());
	return std::string("\n" + route + "     " + "Object is not found");
}


BaseClass* Application::setRouteObject(const std::string& route) {
	BaseClass* newHead = findRouteObject(route);
	if (newHead != nullptr)
		currentHead = newHead;

	return newHead;
}


const std::string Application::setRouteObjectReport(const std::string& route, const BaseClass* setObject) const {
	if (setObject == nullptr)
		return std::string("\nObject is not found: " + currentHead->getName() + " " + route);
	return std::string("\nObject is set: " + currentHead->getName());
}


void Application::displayFindSetMessages() const {
	for (std::string message : findSetMessages)
		std::cout << message;
}


Application::~Application() {
	for (BaseClass*& child : children)
		child->recursiveCleanUp();
}

