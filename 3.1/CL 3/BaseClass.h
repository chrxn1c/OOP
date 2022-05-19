#ifndef __BASECLASS_H
#define __BASECLASS_H

#include <string>
#include <vector>

class BaseClass {
private:
	std::string name;
	BaseClass* parent;
	bool isReady = false;
protected:
	std::vector <BaseClass*> children;
public:
	BaseClass(BaseClass* parent, std::string name = "BaseClassObject");
	void setName(std::string name);
	const std::string getName();
	void changeParent(BaseClass* newParent);
	BaseClass*& getParent();
	void printRoot(unsigned indent = 0);
	BaseClass* findObject(const std::string& objectName);
	void addChild(BaseClass* child);
	~BaseClass();
	void recursiveCleanUp();
	void setTrueReadiness(BaseClass* object);
	void setFalseReadiness(BaseClass*& object);
	bool areAllParentsReady(BaseClass*& object);
	void printReadinessRoot(unsigned indent = 0);
};

#endif // __BASECLASS_H