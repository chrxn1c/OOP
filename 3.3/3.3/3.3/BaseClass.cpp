#include <string>
#include "BaseClass.h"
#include "Node2.h"
#include "Node3.h"
#include "Node4.h"
#include "Node5.h"
#include "Node6.h"
#include <iostream>

//https://docs.microsoft.com/en-us/cpp/error-messages/tool-errors/linker-tools-error-lnk2005?f1url=%3FappId%3DDev16IDEF1%26l%3DEN-US%26k%3Dk(LNK2005)%26rd%3Dtrue&view=msvc-170
std::vector <std::string> miscellaneousMessages = {}; 

//void recastThePointer(BaseClass*& pointer) {
//	switch (pointer->getID()) {
//	case 2: {reinterpret_cast <Node2*> (pointer); break; }
//	case 3: {reinterpret_cast <Node3*> (pointer); break; }
//	case 4: {reinterpret_cast <Node4*> (pointer); break; }
//	case 5: {reinterpret_cast <Node5*> (pointer); break; }
//	case 6: {reinterpret_cast <Node6*> (pointer); break; }
//	}
//}

BaseClass::BaseClass(BaseClass* parent, std::string name) {
	this->setName(name);
	this->changeParent(parent);

	if (parent != nullptr)
		parent->addChild(this);
}


void BaseClass::setName(std::string name) {
	this->name = name;
}


const std::string BaseClass::getName() const {
	return name;
}


void BaseClass::changeParent(BaseClass* newParent) {
	parent = newParent;
}


BaseClass* BaseClass::getParent() const {
	return parent;
}


void BaseClass::printRoot(const unsigned indent) const {
	if (getParent() != nullptr)
		std::cout << std::endl;
	else
		std::cout << "Object tree" << std::endl;

	std::cout << std::string(indent, ' ') << this->name;

	for (BaseClass* child : children)
		child->printRoot(indent + 4);
}


BaseClass* BaseClass::findObjectInTree(const std::string& objectName) const {
	if (objectName == this->getName())
		return (BaseClass*)this;

	for (BaseClass* child : children)
		if (child->findObjectInTree(objectName) != nullptr)
			return child->findObjectInTree(objectName);


	return nullptr;
}


BaseClass* BaseClass::findObjectAmongChildren(const std::string& objectName) const {
	for (BaseClass* child : children)
		if (child->getName() == objectName)
			return child;

	return nullptr;
}


void BaseClass::addChild(BaseClass* child) {
	children.push_back(child);
}


void BaseClass::recursiveCleanUp() {
	if (children.size())
		for (BaseClass*& child : children)
			child->recursiveCleanUp();

	delete this;
}


BaseClass::~BaseClass() {}


bool BaseClass::areAllParentsReady() {
	if (this->getParent() == nullptr)
		return true;

	if (this->getParent()->isReady)
		return true;
	else
		return false;
}


void BaseClass::setTrueReadiness() {
	if (areAllParentsReady())
		isReady = true;
}


void BaseClass::setFalseReadiness() {
	isReady = false;
	if (children.size())
		for (BaseClass*& child : children)
			child->setFalseReadiness();
}


const std::string BaseClass::getFullPath() {

	std::string path;
	BaseClass* temporary = this;

	while (temporary->getParent()) {
		path = "/" + temporary->getName() + path;
		temporary = temporary->getParent();
	}

	if (!path.size())
		return "/";
	return path;
}


void BaseClass::emitSignal(std::string& message) {

	if (!isReady)
		return;

	this->signal(message);
	for (Connection connected : connections) {
		if (connected.signalMethod == getSignal() && connected.object->getReadiness()) {
			//oh man i have zero knowledge about how this works
			//recastThePointer(connected.object);
			(connected.object->*connected.handlerMethod)(message);
		}
	}
}


void BaseClass::setConnection(BaseClass*& recipient, SIGNAL_TYPE donorSignal, HANDLER_TYPE recipientHandler) {

	//for (int i = 0; i < connections.size(); i++)
	//	if (connections[i].object == recipient)
	//		return;

	for (Connection& connected : connections) 
		if (connected.object == recipient)
			return;

	//recastThePointer(recipient);
	connections.push_back( {recipient, donorSignal, recipientHandler} );
}


void BaseClass::removeConnection(BaseClass*& target, SIGNAL_TYPE donorSignal, HANDLER_TYPE recipientHandler) {
	for (int i = 0; i < connections.size(); i++)
		if (connections[i].object == target) {
			connections.erase(connections.begin() + i);
			return;
		}
}


void BaseClass::setCondition(const int condition) {
	if (condition)
		setTrueReadiness();
	else
		setFalseReadiness();
}


unsigned int BaseClass::getID() {
	return ID;
}


bool BaseClass::getReadiness() {
	return isReady;
}