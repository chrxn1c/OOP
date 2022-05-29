#include "Application.h"
#include "BaseClass.h"

#include "Node2.h"
#include "Node3.h"
#include "Node4.h"
#include "Node5.h"
#include "Node6.h"


#include <iostream>
#include <vector>
//extern void recastThePointer(BaseClass*& pointer);

Application::Application(BaseClass* parent, const std::string name) : BaseClass(parent, name) {
	this->changeParent(parent);
	this->setName(name);
	currentHead = this;
	
	ID = 1;
}


void Application::inputTree() {
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

}


void Application::inputConnections() {
	std::string signalObjectPath, handlerObjectPath;
	while (std::cin >> signalObjectPath && signalObjectPath != "end_of_connections") {
		BaseClass* signalObject = findRouteObject(signalObjectPath);

		if (!signalObject) {
			findRouteObjectReport(signalObjectPath, signalObject, "object");
			continue;
		}

		std::cin >> handlerObjectPath;
		BaseClass* handlerObject = findRouteObject(handlerObjectPath);
			
		if (!handlerObject) {
			findRouteObjectReport(handlerObjectPath, handlerObject, "handlerObject");
			continue;
		}

		signalObject->setConnection(handlerObject, signalObject->getSignal(), handlerObject->getHandler());
	}
}


void Application::inputCommands() {
	std::string command, objectPath;
	while (std::cin >> command && command != "END") {
		std::cin >> objectPath;
		BaseClass* object = findRouteObject(objectPath);

		//recastThePointer(object);


		if (!object) {
			findRouteObjectReport(objectPath, object, "object");
			continue;
		}

		if (command == "EMIT") {
			std::cin.get();
			std::string message;
			std::getline(std::cin, message, '\n');
			object->emitSignal(message);
		}

		else if (command == "SET_CONNECT") {
			std::string handlerObjectPath;
			std::cin >> handlerObjectPath;
			BaseClass* handlerObject = findRouteObject(handlerObjectPath);

			if (!handlerObject) {
				findRouteObjectReport(handlerObjectPath, handlerObject, "handlerObject");
				continue;
			}

			object->setConnection(handlerObject, object->getSignal(), handlerObject->getHandler());
		}

		else if (command == "DELETE_CONNECT") {
			std::string handlerObjectPath;
			std::cin >> handlerObjectPath;
			BaseClass* handlerObject = findRouteObject(handlerObjectPath);

			if (!handlerObject) {
				findRouteObjectReport(handlerObjectPath, handlerObject, "handlerObject");
				continue;
			}

			object->removeConnection(handlerObject, object->getSignal(), handlerObject->getHandler());
		}

		else if (command == "SET_CONDITION") {
			int condition;
			std::cin >> condition;
			object->setCondition(condition);
		}

	}
}


void Application::inputHierarchy() {
	this->inputTree();
	this->inputConnections();
	this->inputCommands();
}


void Application::buildHierarchy() {
	this->inputHierarchy();

	if (this->getName() != "") {
		this->printRoot();
		this->displaySignalMessages();
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


void Application::findRouteObjectReport(const std::string& route, const BaseClass* foundObject, const std::string whatObject) const {
	if (whatObject == "object")
		miscellaneousMessages.push_back("\nObject " + route + " not found");
	else if (whatObject == "handlerObject")
		miscellaneousMessages.push_back("\nHandler Object " + route + " not found");
}


BaseClass* Application::setRouteObject(const std::string& route) {
	BaseClass* newHead = findRouteObject(route);
	if (newHead != nullptr)
		currentHead = newHead;

	return newHead;
}


void Application::displaySignalMessages() const {
	for (std::string message : miscellaneousMessages)
		std::cout << message;
}


Application::~Application() {
	for (BaseClass*& child : children)
		child->recursiveCleanUp();
}


void Application::signal(std::string& message) {
	message += " (class: 1)";
	miscellaneousMessages.push_back("\nSignal from " + (getFullPath()));
}


void Application::handler(std::string message) {
	miscellaneousMessages.push_back("\nSignal to " + getFullPath() + " Text: " + message);
}


SIGNAL_TYPE Application::getSignal() {
	return SIGNAL_REFERENCE(Application::signal);
}


HANDLER_TYPE Application::getHandler() {
	return HANDLER_REFERENCE(Application::handler);
}