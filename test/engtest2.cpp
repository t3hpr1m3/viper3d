#include <cstdio>
#include <unistd.h>
#include "engtest2.h"
#include "VLog.h"
#include "VWindow.h"
#include "VInput.h"
//#include <GL/glx.h>
//#include <X11/extensions/xf86vmode.h>


int main(int argc, char *argv[])
{
	VInput input;
	VWindow window;
	//XWindow window;
	VLog::SetName("Viper3D.log");
	VLog::SetFlush();
	VCPU::Init();
	TestVectors();

	if (!window.CreateDevice("X"))
	{
		cerr << "Unable to create window device." << endl;
		return 1;
	}

	if (!window.GetDevice()->Initialize())
	{
		cerr << "Unable to initialize XWindow." << endl;
		return 1;
	}

	if (!window.GetDevice()->CreateWindow(800, 600, false))
	{
		cerr << "Unable to create XWindow." << endl;
		return 1;
	}

	if (!input.CreateDevice("X"))
	{
		cerr << "Unable to create input device" << endl;
		return 1;
	}

	if (!input.GetDevice()->Initialize(window.GetDevice()))
	{
		cerr << "Unable to initialize input device" << endl;
		input.Release();
		return 1;
	}

	for (;;)
	{
		window.GetDevice()->Update();
		input.GetDevice()->Update();
		if (input.GetDevice()->IsKeyDown(UDP::KC_Q) == true)
			break;
		sleep(1);
	}

	input.Release();
	window.Release();
	return 0;
}
