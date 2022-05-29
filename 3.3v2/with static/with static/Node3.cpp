#include "BaseClass.h"
#include "Node3.h"


Node3::Node3(BaseClass* parent, std::string name) : BaseClass(parent, name) {
	ID = 3;
}

void Node3::signal(std::string& message) {
	message += " (class: 3)";
	miscellaneousMessages.push_back("\nSignal from " + getFullPath());
}

void Node3::handler(std::string message) {
	miscellaneousMessages.push_back("\nSignal to " + getFullPath() + " Text: " + message);
}


SIGNAL_TYPE Node3::getSignal() {
	return SIGNAL_REFERENCE(Node3::signal);
}


HANDLER_TYPE Node3::getHandler() {
	return HANDLER_REFERENCE(Node3::handler);
}