/*
	File:	Main_Framework.cpp
	Version:	2.2
	Date: 9th December 2013.
	Author:	Allan C. Milne.

	Uses:	WinCore, IState, XACore.

	Description:
	An outline main code file containing the Windows application entry point
	for use with the author's windows/audio framework.
	*	See WinCore.hpp for details of the windows abstraction.
	*	see IState.hpp for details of the game frame processing abstraction.
	*	see XACore.hpp for details of the audio engine abstraction.

	Find '//xxx' for code that requires to be amended for a specific application.
	If not using audio then delete code concerned with XACore.

*/

//--- system includes.
#include <windows.h>

//--- framework includes.
#include "WinCore.hpp"
#include "IState.hpp"
#include "XACore.hpp"
using AllanMilne::WinCore;
using AllanMilne::IState;
using AllanMilne::Audio::XACore;

//--- Application specific include.
//xxx specifically your frame processing class header.
#include "xxx.hpp"

//=== Application entry point. ===
int WINAPI WinMain (HINSTANCE hinstance,
				   HINSTANCE prevInstance, 
				   PSTR cmdLine,
				   int showCmd)
{
	WinCore* windowApp;
	IState* frameProcessor;
	
	//--- Create the singleton XACore objec that will initialize XAudio2 and X3DAudio.
	//--- Must do this before creating/initializing other objects since these may require XAudio2 functionality in creating sounds, etc.
	XACore::CreateInstance();
	if (XACore::GetStatus() != XACore::OK) {
		MessageBox (NULL, TEXT ("Error initializing XAudio2 - application aborted."), TEXT ("Main Application"), MB_OK | MB_ICONERROR );
		return 0;
	}

	//--- create the object that encapsulates frame processing.
	//xxx - This will be a client-defined class that inherits from IState and hence implements its member functions.
	frameProcessor = new xxx();

	//--- Create the WinCore object composed with the frame processor.
	windowApp = new WinCore (frameProcessor);

	//--- Initialize the WinCore object including creating the application window;
	//--- this will also call the IState::Initialize() method of the frame processor.
	bool ok = windowApp->Initialize (
				" Play A Sound. ",		//xxx Windows title bar text.
				800, 600,			// width x height
				false,				// use full screen; change to true if windowed is required.
				hinstance );
	if (!ok) {
		MessageBox (NULL, TEXT ("Error occurred while initializing WinCore; application aborted."), TEXT (" Main Application"), MB_OK | MB_ICONERROR );
		return 0;
	}

	//--- Run the application Windows messsage loop and associated frame processing.
	windowApp->RunApp();

	//--- Delete resources.
	//--- NB order of deletion is important - is in opposite order of creation.

	//--- delete the WinCore instance.
	delete windowApp;
	windowApp = NULL;

	//--- delete the IState object.
	delete frameProcessor;
	frameProcessor = NULL;

	//--- Delete the XACore singleton instance - will clear up all XAudio2 resources.
	XACore::DeleteInstance();
	
	return 0;
} // end WinMain function.

// end of code.