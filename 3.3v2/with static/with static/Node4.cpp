#include "BaseClass.h"
#include "Node4.h"


Node4::Node4(BaseClass* parent, std::string name) : BaseClass(parent, name) {
	ID = 4;
}


void Node4::signal(std::string& message) {
	message += " (class: 4)";
	miscellaneousMessages.push_back("\nSignal from " + getFullPath());
}

void Node4::handler(std::string message) {
	miscellaneousMessages.push_back("\nSignal to " + getFullPath() + " Text: " + message);
}

SIGNAL_TYPE Node4::getSignal() {
	return SIGNAL_REFERENCE(Node4::signal);
}


HANDLER_TYPE Node4::getHandler() {
	return HANDLER_REFERENCE(Node4::handler);
}