#include <cstdio>
#include <unistd.h>
#include "engtest2.h"
#include "VLog.h"
#include "Viper3D.h"
//#include <GL/glx.h>
//#include <X11/extensions/xf86vmode.h>


int main(int argc, char *argv[])
{
	Viper3D	vEngine;
	VLog::SetName("Viper3D.log");
	//VTRACE( "Hey\n" );
	VLog::SetFlush();
	VCPU::Init();
	TestVectors();
	TestMatrices();

	if (!vEngine.Create(800, 600, false))
	{
		cerr << "Unable to create engine." << endl;
		return -1;
	}
	printf("engine created\n");

	vEngine.MainLoop();
	return 0;
}
