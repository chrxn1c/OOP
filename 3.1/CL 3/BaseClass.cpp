#include <string>
#include "BaseClass.h"
#include <iostream>

BaseClass::BaseClass(BaseClass* parent, std::string name) {
	this->setName(name);
	this->changeParent(parent);

	if (parent != nullptr)
		parent->addChild(this);
}


void BaseClass::setName(std::string name) {
	this->name = name;
}


const std::string BaseClass::getName() {
	return name;
}


void BaseClass::changeParent(BaseClass* newParent) {
	parent = newParent;
}


BaseClass*& BaseClass::getParent() {
	return parent;
}


void BaseClass::printRoot(unsigned indent) {
	std::cout << std::endl;
	std::cout << std::string(indent, ' ') << this->name;

	for (BaseClass*& child : children)
		child->printRoot(indent + 4);
}


BaseClass* BaseClass::findObject(const std::string& objectName) {
	if (objectName == this->getName())
		return this;

	for (BaseClass*& child : children)
		if (child->findObject(objectName) != nullptr)
			return child->findObject(objectName);


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



bool BaseClass::areAllParentsReady(BaseClass*& object) {
	if (object->getParent() == nullptr)
		return true;

	if (object->getParent()->isReady)
		return true;
	else
		return false;
}


void BaseClass::setTrueReadiness(BaseClass* object) {
	if (object->areAllParentsReady(object))
		object->isReady = true;
}


void BaseClass::setFalseReadiness(BaseClass*& object) {
	object->isReady = false;
	if (object->children.size())
		for (BaseClass*& child : children)
			child->setFalseReadiness(child);
}


void BaseClass::printReadinessRoot(unsigned indent) {
	std::cout << std::endl;
	std::cout << std::string(indent, ' ') << this->name;
	(this->isReady) ? std::cout << " is ready" : std::cout << " is not ready";


	for (BaseClass*& child : children)
		child->printReadinessRoot(indent + 4);
}
