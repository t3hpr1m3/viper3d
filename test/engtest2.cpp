#include <cstdio>
#include <unistd.h>
#include "engtest2.h"
#include <viper3d/util/Log.h>
#include <viper3d/Viper3D.h>
#include <viper3d/Window.h>
#include <viper3d/RawInput.h>
#include <viper3d/RenderSystem.h>
#include <viper3d/Camera.h>
//#include <GL/glx.h>
//#include <X11/extensions/xf86vmode.h>
#include <iostream>

using std::cout;
using std::endl;


int main(int argc, char *argv[])
{
	Viper3D	vEngine;
	VLog::SetName("Viper3D.log");
	VLog::SetFlush();
	VCPU::Init();

	//VCPU::mOSSSE = false;
	/*
	TestVectors();
	TestMatrices();
	*/

	VRenderSystem* vRenderer = vEngine.CreateRenderer("GL");

	if (vRenderer == NULL)
	{
		cout << "Unable to create renderer." << endl;
		return 0;
	}

	if (!vRenderer->Init())
	{
		cout << "Unable to initialize renderer." << endl;
		vEngine.DestroyRenderer();
		return 0;
	}

	VWindowOpts pOpts;
	pOpts.mWidth = 800;
	pOpts.mHeight = 600;
	pOpts.mFullScreen = false;
	VWindow *vWin = vRenderer->CreateWin(&pOpts);
	vWin->SetCaption("OpenGL test");
	float vRotScale = 0.5f;
	float vMoveScale = 5.0f;
	if (vWin == NULL)
	{
		cout << "Unable to create window." << endl;
	}
	else
	{
		VCamera vCamera;
		vCamera.SetPosition(VVector(0, 0, 0, 1));
		vCamera.SetDirection(-VVector::VECTOR_UNIT_Z);
		VRawInput vInput;
		if (!vInput.StartCapture(vWin))
			cout << "Unable to initiate input capture" << endl;
		VMouseState vMouse;
		for (;;)
		{
			vInput.Update();
			if (vInput.IsKeyDown(KC_UP))
				vCamera.RotatePitch(-1 * vRotScale);
			if (vInput.IsKeyDown(KC_DOWN))
				vCamera.RotatePitch(1 * vRotScale);
			if (vInput.IsKeyDown(KC_LEFT))
				vCamera.RotateRoll(1 * vRotScale);
			if (vInput.IsKeyDown(KC_RIGHT))
				vCamera.RotateRoll(-1 * vRotScale);
			if (vInput.IsKeyDown(KC_A))
				vCamera.MoveRelative(VVector(0, 0, -1 * vMoveScale));
			if (vInput.IsKeyDown(KC_Z))
				vCamera.MoveRelative(VVector(0, 0, 1 * vMoveScale));
			if (vInput.IsKeyDown(KC_Q))
				break;
			/*
			vMouse = vInput.GetMouseState();
			if (vMouse.mXdelta != 0)
			{
				cout << "X-delta: " << vMouse.mXdelta << endl;
				vCamera.RotateRoll(vMouse.mXdelta * vRotScale);
			}
			if (vMouse.mYdelta != 0)
			{
				vCamera.RotatePitch(vMouse.mYdelta * vRotScale);
				cout << "Y-delta: " << vMouse.mYdelta << endl;
			}
			*/
			//vCamera.Render();
			vRenderer->Render(vWin, &vCamera);
		}
		vInput.EndCapture();
		cout << "Destroying Window" << endl;
		vRenderer->DestroyWin(vWin);
	}

	cout << "Destroying Renderer" << endl;
	vEngine.DestroyRenderer();

	/*
	if (!vEngine.Create(800, 600, false))
	{
		cerr << "Unable to create engine." << endl;
		return -1;
	}
	printf("engine created\n");

	vEngine.MainLoop();
	*/
	return 0;
}
