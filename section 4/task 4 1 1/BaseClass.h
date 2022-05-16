#ifndef __BASECLASS_H
#define __BASECLASS_H

#include <string>
#include <vector>

class BaseClass {
private:
	std::string name;
	BaseClass* parent;
protected: 
	std::vector <BaseClass*> children;
public:
	BaseClass(BaseClass* parent, std::string name = "BaseClassObject"); 

	void setName(std::string name);

	const std::string getName();

	void changeParent(BaseClass* newParent);

	BaseClass* getParent();

	void printRoot();

	BaseClass* findParent(const std::string& parentName); //have no idea how the recursion works so far

	void addChild(BaseClass* child);

	void recursiveCleanUp();

	~BaseClass();
};

#endif  // __BASECLASS_H