<<<<<<< Updated upstream
#include "Resources/framework.h"
#include "Application.h"


int main()
{
	Application app = Application();

	app.Init();
	int msgRet = app.Run();

	return msgRet;
}
=======
//#include "Resources/framework.h"
//#include "Application.h"
//#include <ostream>
//
////#ifdef _DEBUG
////#include <crtdbg.h>
////#endif 
//
//
//int main()
//{
////#ifdef _DEBUG
////	_CrtMemState memStateInit;
////	_CrtMemCheckpoint(&memStateInit);
////#endif 
//
//	Application app = Application();
//
//	app.Init();
//	int msgRet = app.Run();
//
////#ifdef _DEBUG
////	_CrtMemState memStateEnd, memStateDiff;
////	_CrtMemCheckpoint(&memStateEnd);
////	if (_CrtMemDifference(&memStateDiff, &memStateInit, &memStateEnd))
////	{
////		MessageBoxA(NULL, "MEMORY LEAKS", "DISCLAIMER", 0);
////		std::cout << memStateInit.lSizes << " : " << memStateEnd.lSizes << endl;
////	}
////#endif 
//
//	return msgRet;
//}
>>>>>>> Stashed changes
