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


BaseClass* BaseClass::getParent() {
	return parent;
}


void BaseClass::printRoot() {
	std::cout << std::endl;
	std::cout << this->name;

	for (BaseClass*& child : children)
		std::cout << " " << child->getName();

	if (this->children.size())
		for (BaseClass*& child : children)
			if (child->children.size())
				child->printRoot();
}


BaseClass* BaseClass::findParent(const std::string& parentName) {
	if (parentName == this->getName())
		return this;

	for (BaseClass*& child : children)
		if (child->findParent(parentName) != nullptr)
			return child->findParent(parentName);


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


