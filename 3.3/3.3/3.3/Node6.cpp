#include "BaseClass.h"
#include "Node6.h"


Node6::Node6(BaseClass* parent, std::string name) : BaseClass(parent, name) {
	ID = 6;
}


void Node6::signal(std::string& message) {
	message += " (class: 6)";
	miscellaneousMessages.push_back("\nSignal from " + getFullPath());
}


void Node6::handler(std::string message) {
	miscellaneousMessages.push_back("\nSignal to " + getFullPath() + " Text: " + message);
}


SIGNAL_TYPE Node6::getSignal() {
	return (SIGNAL_TYPE)(&Node6::signal);
}


HANDLER_TYPE Node6::getHandler() {
	return (HANDLER_TYPE)(&Node6::handler);
}