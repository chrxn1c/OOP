#ifndef __APPLICATION_H
#define __APPLICATION_H

#include "BaseClass.h"

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
	const std::string findRouteObjectReport(const std::string& route, const BaseClass* foundObject) const;
	BaseClass* setRouteObject(const std::string& route);
	const std::string setRouteObjectReport(const std::string& route, const BaseClass* setObject) const;
	void displayFindSetMessages() const;
};

#endif // __APPLICATION_H