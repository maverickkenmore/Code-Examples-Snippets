#include "EmotionalDecisionTree.h"



EmotionalDecisions::EmotionalDecisions()
{

	FL_Agent Emotional_Agent;
	

}

EmotionalDecisions::~EmotionalDecisions()
{


}


void EmotionalDecisions::Update(FL_Agent EmotionaAgentObject)
{
	switch (State_of_Decisions)
	{

		// Runs all emotional fuzzy systems
		EmotionaAgentObject.FLfor_All_Emotions(EmotionaAgentObject.sadnessTOjoy, EmotionaAgentObject.disgustTOtrust, 
			EmotionaAgentObject.fearTOanger, EmotionaAgentObject.anticipationTOsurprise);

	case EVENTS:
		
		Consequences_of_Events(EmotionaAgentObject);
		break;

	case REACTION:
		Actions_of_agents(EmotionaAgentObject);
		break;

	case OBJECT:

		Aspects_of_objects(EmotionaAgentObject);
		break;

	default:
		break;
	}



}


void EmotionalDecisions::Consequences_of_Events(FL_Agent EmotionaAgentObject)
{
	EmotionaAgentObject.GetAllEventEmotionalValues();

}

void EmotionalDecisions::Actions_of_agents(FL_Agent EmotionaAgentObject)
{
	EmotionaAgentObject.GetAllReactionEmotionalValues();
}

void EmotionalDecisions::Aspects_of_objects(FL_Agent EmotionaAgentObject)
{
	EmotionaAgentObject.GetAllObjectEmotionalValues();
}