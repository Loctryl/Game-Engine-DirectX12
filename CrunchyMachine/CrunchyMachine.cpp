#include "Resources/framework.h"
#include "Application.h"


int main()
{
	Application app = Application();

	app.Init();
	int msgRet = app.Run();

	return msgRet;
}