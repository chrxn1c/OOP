#include "BaseClass.h"
#include "Application.h"
#include "Node2.h"
#include "Node3.h"
#include "Node4.h"
#include "Node5.h"
#include "Node6.h"

int main()
{
	Application app(nullptr);
	app.buildHierarchy();
	return(app.start());
}
