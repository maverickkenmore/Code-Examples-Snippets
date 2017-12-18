#include "EmotionalFuzzySystem.h"

class EmotionalDecisions
{

public:
	EmotionalDecisions();

	virtual ~EmotionalDecisions();

	/*
	float joy, distress, happy_for, pity, gloating, resentment, hope, fear,
		satisfaction, fears_confirmed, relief, disapointment, pride, shame,
		admiration, reproach, gratification, remorse, gratitude, anger, love, hate;
		*/

	enum Emotional_state {JOY, DISTRESSED, HAPPY_FOR, PITY, GLOATING, RESENTMENT, HOPE, FEAR,
	SATISFACTION, FEARS_CONFIRMED, RELIEF, DISAPOINMENT, PRIDE, SHAME, ADMIRATION, REPROACH,
	GRATIFICATION, REMORSE, GRATITUDE, ANGER, LOVE, HATE};

	enum Decision_state {EVENTS, REACTION, OBJECT};

	Emotional_state State_of_Emotions;
	Decision_state State_of_Decisions;


	void Update(FL_Agent);

	void Consequences_of_Events(FL_Agent);

	/* Consequences of events total emotions - (Joy, Distress, happy-for, pity, gloating, Resentment, hope, 
	   fear, satisfaction, fears-confirmed, relief, disappointment, gratification, remorse, gratitude) 
	   

	   consequences for others(Fortune of others) - (Desirable for others(happy_for, resentment) Undesirable for others (gloating, pity))
	   

	   consequences for self (Prospect Based) - Potential to happen matters (pleased about the potential of desired event - Hope, 
																	displeased about the potential of a undesired event - Fear).


												Confirmed to happen (pleased about confirmation of desirable event - Satisfaction, 
																	displeased about confirmation of undesired event - fears_confirmed)


																	*Note - Disconfirmed means to have a belief or such to be shown to be not true

												Disconfirmed to happen (pleased about disconfirmed, undesired event - relief, 
																		displeased about disconfirmed, desired event - disappointment)

		consequences for self (Well-being) - Potential to happen not matter (pleased about desired event - Joy, 
																			displeased about udesirable event - Distress)
	   */
	



	/* Actions of Agents (pride, shame, admiration, reproach, gratification, remorse, gratitude, anger) */
	void Actions_of_agents(FL_Agent);

	/* Aspects of Objects (love, hate) */
	void Aspects_of_objects(FL_Agent);



private:

};