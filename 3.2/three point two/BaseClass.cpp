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





	