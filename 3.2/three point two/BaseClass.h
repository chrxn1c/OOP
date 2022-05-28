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
	BaseClass(BaseClass* parent, const std::string name = "BaseClassObject");
	~BaseClass();
	void setName(std::string name);
	const std::string getName() const;
	void changeParent(BaseClass* newParent);
	BaseClass* getParent() const;
	void printRoot(const unsigned indent = 0) const;
	BaseClass* findObjectInTree(const std::string& objectName) const;
	BaseClass* findObjectAmongChildren(const std::string& objectName) const;
	void addChild(BaseClass* child);
	void recursiveCleanUp();
};

#endif // __BASECLASS_H