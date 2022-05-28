#ifndef __APPLICATION_H
#define __APPLICATION_H

#include "BaseClass.h"
#include "Node2.h"
#include "Node3.h"
#include "Node4.h"
#include "Node5.h"
#include "Node6.h"


class Application : public BaseClass {
	BaseClass* currentHead;
public:
	Application(BaseClass* parent, const std::string name = "Application");
	void inputHierarchy();
	void buildHierarchy();
	int start();
	~Application();
private:
	BaseClass* routeToAdress(std::string route);
	const std::string subNameExtraction(const std::string& route, const std::string mode) const;
	BaseClass* findRouteObject(const std::string& route);
	void findRouteObjectReport(const std::string& route, const BaseClass* foundObject, const std::string object) const; //now adds message automatically
	BaseClass* setRouteObject(const std::string& route);
	//void setRouteObjectReport(const std::string& route, const BaseClass* setObject) const; //now adds message automatically


	void displaySignalMessages() const;

	void signal(std::string&) override;
	void handler(std::string) override;
	SIGNAL_TYPE getSignal() override;
	HANDLER_TYPE getHandler() override;

	void inputTree();
	void inputCommands();
	void inputConnections();

};

#endif // __APPLICATION_H