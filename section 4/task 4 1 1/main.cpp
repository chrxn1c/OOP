#include "BaseClass.h"
#include "Application.h"
#include "Node1.h"
#include "Node2.h"


int main() {
	Application app(nullptr);
	app.buildHierarchy();
	return app.start();
}