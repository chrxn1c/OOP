#include "BaseClass.h"
#include "Node2.h"
#include <string>



Node2::Node2(BaseClass* parent, std::string name) : BaseClass(parent, name) {
	ID = 2;
}


void Node2::signal(std::string& message) {
	message += " (class: 2)";
	miscellaneousMessages.push_back("\nSignal from " + (getFullPath()));
}


void Node2::handler(std::string message) {
	miscellaneousMessages.push_back("\nSignal to " + getFullPath() + " Text: " + message);
}


SIGNAL_TYPE Node2::getSignal() {
	return SIGNAL_REFERENCE(Node2::signal);

}


HANDLER_TYPE Node2::getHandler() {
	return HANDLER_REFERENCE(Node2::handler);
}