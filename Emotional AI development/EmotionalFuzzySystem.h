#include "sources\fuzzylite-5.0\fuzzylite\fl\Headers.h"
#include "sources\fuzzylite-5.0\fuzzylite\fl\variable\Variable.h"
#include <windows.h> 
#include <stdio.h> 
#include <iostream>


#include <time.h>
#include <conio.h>
#include <stdlib.h>

using namespace std;
using namespace fl;

class FL_Agent
{
public:
	FL_Agent();

	virtual ~FL_Agent();

	// Initial values for emotions (Primary Emotions)
	float sadnessTOjoy;
	float disgustTOtrust;
	float fearTOanger;
	float anticipationTOsurprise;


	// Secondary Emotions (Found from fuzzying inital values)
	float hateTOlove;
	float contemptTOsubmission;
	float aggressionTOawe;
	float disapprovalTOoptimism;

	// Values to store membership values (Primary Emotions)
	string sadnessTOjoyMemValues;
	string disgustTOtrustMemValues;
	string fearTOangerMemValues;
	string anticipationTOsurpriseMemValues;


	// Values to store membership values (Secondary Emotions)
	string hateTOloveMemValues;
	string contemptTOsubmissionMemValues;
	string aggressionTOaweMemValues;
	string disapprovalTOoptimismMemValues;


	fl::scalar sadnessTOjoyScalar;
	fl::scalar disgustTOtrustScalar;
	fl::scalar fearTOangerScalar;
	fl::scalar anticipationTOsurpriseScalar;

	fl::scalar hateTOloveScalar;
	fl::scalar contemptTOsubmissionScalar;
	fl::scalar aggressionTOaweScalar;
	fl::scalar disapprovalTOoptimismScalar;

	// List of emotions that can be displayed.
	float joy, distress, happy_for, pity, gloating, resentment, hope, fear,
		satisfaction, fears_confirmed, relief, disapointment, pride, shame,
		admiration, reproach, gratification, remorse, gratitude, anger, love, hate;



	void Update();

	void initalise_Emotions();

	// Functions for getting fuzzy values for secondary emotions
	void FLfor_All_Emotions(float sadnessTOjoy, float disgustTOtrust, float fearTOanger, float anticipationTOsurprise);
	void FLfor_HateTOLove(float sadnessTOjoy, float disgustTOtrust);
	void FLfor_ContemptTOSubmission(float disgustTOtrust, float fearTOanger);
	void FLfor_AggressionTOAwe(float fearTOanger, float anticipationTOsurprise);
	void FLfor_DisapprovalTOOptimism(float anticipationTOsurprise, float sadnessTOjoy);


	// Function for running all emotional functions
	void GetAllEmotionalValues();

	// Function for running all event emotion functions
	void GetAllEventEmotionalValues();

	// Function for running all event emotion functions
	void GetAllReactionEmotionalValues();

	// Function for running all event emotion functions
	void GetAllObjectEmotionalValues();

	// Emotions used for events reactions
	void Emotionalvalueof_joy();
	void Emotionalvalueof_distress();
	void Emotionalvalueof_happy_for();
	void Emotionalvalueof_pity();
	void Emotionalvalueof_gloating();
	void Emotionalvalueof_resentment();
	void Emotionalvalueof_hope();
	void Emotionalvalueof_fear();
	void Emotionalvalueof_satisfaction();
	void Emotionalvalueof_fears_confirmed();
	void Emotionalvalueof_relief();
	void Emotionalvalueof_disapointment();

	// emotions used for reacting to actions from agents
	void Emotionalvalueof_pride();
	void Emotionalvalueof_shame();
	void Emotionalvalueof_admiration();
	void Emotionalvalueof_reproach();
	void Emotionalvalueof_gratification();
	void Emotionalvalueof_remorse();
	void Emotionalvalueof_gratitude();
	void Emotionalvalueof_anger();

	// Aspects of objects
	void Emotionalvalueof_love();
	void Emotionalvalueof_hate();


private:
};