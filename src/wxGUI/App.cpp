#include "App.h"
//#include <chrono>
/*void f()
{
	std::this_thread::sleep_for(std::chrono::seconds(10));

}*/
//IMPLEMENT_APP_NO_MAIN(App)
//IMPLEMENT_WX_THEME_SUPPORT
//IMPLEMENT_APP(App)
bool App::OnInit()
{
	if (!wxApp::OnInit())
	{
		return false;
	}
	//frame =
	new Frame();
	//t = new std::thread(f);
	return true;
}

int App::OnExit()
{
	//t->join();
	//frame->Destroy();
	exit(0);
	return wxApp::OnExit();
}

