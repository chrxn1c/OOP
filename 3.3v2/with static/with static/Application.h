#ifndef __APPLICATION_H
#define __APPLICATION_H

#include "BaseClass.h"


class Application : public BaseClass {
	BaseClass* currentHead;
public:
	Application(BaseClass* parent, const std::string name = "Application");
	~Application();
	void buildHierarchy();
	int start();
private:
	BaseClass* routeToAdress(std::string route);
	const std::string subNameExtraction(const std::string& route, const std::string mode) const;
	BaseClass* findRouteObject(const std::string& route);
	void findRouteObjectReport(const std::string& route, const BaseClass* foundObject, const std::string whatObject) const; //now adds message automatically
	BaseClass* setRouteObject(const std::string& route);

	void displaySignalMessages() const;

	void signal(std::string& message) override;
	void handler(std::string message) override;
	SIGNAL_TYPE getSignal() override;
	HANDLER_TYPE getHandler() override;

	void inputTree();
	void inputConnections();
	void inputCommands();

	void inputHierarchy();
	

};

#endif // __APPLICATION_H