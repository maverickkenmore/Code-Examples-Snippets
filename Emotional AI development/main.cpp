//#pragma warning( disable : 4290 )

#include "EmotionalDecisionTree.h"
#include <windows.h> 
#include <stdio.h> 
#include <iostream>

#include <time.h>
#include <conio.h>
#include <stdlib.h>


COLORREF white = RGB(255, 255, 255);
COLORREF black = RGB(0, 0, 0);

COLORREF red = RGB(255, 0, 0);
COLORREF green = RGB(0, 255, 0);
COLORREF blue = RGB(0, 0, 255);

COLORREF yellow = RGB(255, 255, 0);
COLORREF purple = RGB(255, 0, 255);
COLORREF cyan = RGB(0, 255, 255);

using namespace std;
using namespace fl;



bool StillRunning = true;
int userOption = 0;
int userChoice = 0;

float SadnessJoyInput = 0.0f;
float DisgustTrustInput = 0.0f;
float FearAngerInput = 0.0f;
float AnticipationSurpriseInput = 0.0f;

FL_Agent Emotional_Agent;



string graphicMap[80][25];
int arrX = 0;
int arrY = 0;

int carPosX = 0;


// Used to initalise variables for seconds and nanoseconds
struct timespec {
	time_t tv_sec;        /* seconds */
	long   tv_nsec;       /* nanoseconds */
};


// initalization of the nanosleep function
int nanosleep(const struct timespec *req, struct timespec *rem);





int main(int argc, char*argv[])
{


	while (StillRunning == true)
	{

		cout << "What would you like to do? (Please input the number of the option \n";
		cout << "1 - Run the numerical input test.\n\n";
		cout << "2 - Run the Emotional Agent text test.\n";
		cout << "3 - Quit.\n";
		cout << "(Note: To exit test press 'E'.) \n\n";
		cout << "(A & S - Changes -sadnessTOjoy+ value.) \n";
		cout << "(Z & X - Changes -disgustTOtrust+ value.) \n";
		cout << "(D & F - Changes -fearTOanger+ value.) \n";
		cout << "(C & V - Changes -anticipationTOsurprise+ value.) \n";
		cout << "(Note: To exit test press 'E'.) \n\n";

		cin >> userOption;


		if (userOption == 1)
		{

			// Input from user to be converted for input vales
			cout << "What value would you like -SadnessJoy+ to be? (-1.0 to 1.0) \n";
			cin >> SadnessJoyInput;
			Emotional_Agent.sadnessTOjoy = SadnessJoyInput;

			cout << "What value would you like -DisgustTrust+ to be? (-1.0 to 1.0) \n";
			cin >> DisgustTrustInput;
			Emotional_Agent.disgustTOtrust = DisgustTrustInput;

			/*
			cout << "What value would you like -FearAnger+ to be? (-1.0 to 1.0) \n";
			cin >> FearAngerInput;
			Emotional_Agent.fearTOanger = FearAngerInput;

			cout << "What value would you like the -AnticipationSurprise+ from the line to be? (-1.0 to 1.0) \n";
			cin >> AnticipationSurpriseInput;
			Emotional_Agent.anticipationTOsurprise = AnticipationSurpriseInput;
			cout << "\n";
			*/

			//Emotional_Agent.FLfor_All_Emotions(Emotional_Agent.sadnessTOjoy, Emotional_Agent.disgustTOtrust,
			//	Emotional_Agent.fearTOanger, Emotional_Agent.anticipationTOsurprise);


			Emotional_Agent.FLfor_HateTOLove(Emotional_Agent.sadnessTOjoy, Emotional_Agent.disgustTOtrust);

			cout << " \n\n\n";
			cout << "-SadnessJoy+ = " << SadnessJoyInput << " \n";
			cout << "The -SadnessJoy+ mem.ships are -" << Emotional_Agent.sadnessTOjoy << " \n\n";


		}

		return 0;
	}
}