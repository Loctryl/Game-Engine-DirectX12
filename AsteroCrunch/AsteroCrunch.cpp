#include "Application.h"
#include "EngineResources/framework.h"
#include <ostream>

/*#ifdef _DEBUG
#include <crtdbg.h>
#endif */


int main()
{
	/*#ifdef _DEBUG
		_CrtMemState memStateInit;
		_CrtMemCheckpoint(&memStateInit);
	#endif */

	Application app = Application();

	app.Init();
	int msgRet = app.Run();

	/*#ifdef _DEBUG
		_CrtMemState memStateEnd, memStateDiff;
		_CrtMemCheckpoint(&memStateEnd);
		if (_CrtMemDifference(&memStateDiff, &memStateInit, &memStateEnd))
		{
			MessageBoxA(NULL, "MEMORY LEAKS", "DISCLAIMER", 0);
			//std::cout << memStateInit.lTotalCount << " to " << memStateEnd.lTotalCount << "; Diff = " << memStateDiff.lTotalCount << endl;
		}
	#endif*/ 

	return msgRet;
}