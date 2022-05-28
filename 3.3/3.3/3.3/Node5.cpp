#include "BaseClass.h"
#include "Node5.h"


Node5::Node5(BaseClass* parent, std::string name) : BaseClass(parent, name) {
	ID = 5;
}


void Node5::signal(std::string& message) {
	message += " (class: 5)";
	miscellaneousMessages.push_back("\nSignal from " + getFullPath());
}

void Node5::handler(std::string message) {
	miscellaneousMessages.push_back("\nSignal to " + getFullPath() + " Text: " + message);
}


SIGNAL_TYPE Node5::getSignal() {
	return (SIGNAL_TYPE)(&Node5::signal);
}


HANDLER_TYPE Node5::getHandler() {
	return (HANDLER_TYPE)(&Node5::handler);
}