#include "EmotionalFuzzySystem.h"

FL_Agent::FL_Agent()
{
	
	// Initial values for emotions (Primary Emotions)
	sadnessTOjoy;
	disgustTOtrust;
	fearTOanger;
	anticipationTOsurprise;

	// Secondary Emotions (Found from fuzzying inital values)
	hateTOlove;
	contemptTOsubmission;
	aggressionTOawe;
	disapprovalTOoptimism;

	

	// Values to store membership values (Primary Emotions)
	sadnessTOjoyMemValues;
	disgustTOtrustMemValues;
	fearTOangerMemValues;
	anticipationTOsurpriseMemValues;


	// Values to store membership values (Secondary Emotions)
	hateTOloveMemValues;
	contemptTOsubmissionMemValues;
	aggressionTOaweMemValues;
	disapprovalTOoptimismMemValues;

}

FL_Agent::~FL_Agent()
{


}



void FL_Agent::initalise_Emotions()
{


}

void FL_Agent::FLfor_HateTOLove(float sadnessTOjoy, float disgustTOtrust)
{
	// Initalising of fl engine (Hate TO Love Fuzzy Engine)
	fl::Engine* HateLoveEngine = new fl::Engine;
	HateLoveEngine->setName("Fuzzy System - Hate <-> Love");

	// initalising of first input (Sadness TO Joy)
	fl:InputVariable* Sadness_Joy = new fl::InputVariable;
	Sadness_Joy->setEnabled(true);
	Sadness_Joy->setName("-Sadness<->Joy+");
	Sadness_Joy->setRange(-1.000, 1.000);
	Sadness_Joy->addTerm(new fl::Triangle("-Sadness", -1.000, -1.000, 0.00));
	Sadness_Joy->addTerm(new fl::Triangle("Neutral", -1.000, 0.000, 1.00));
	Sadness_Joy->addTerm(new fl::Triangle("Joy+", 0.000, 1.000, 1.00));
	HateLoveEngine->addInputVariable(Sadness_Joy);
	
	// Initalising of second Input (Disgust TO Trust)
	fl::InputVariable* Disgust_Trust = new fl::InputVariable;
	Disgust_Trust->setEnabled(true);
	Disgust_Trust->setName("-Disgust<->Trust+");
	Disgust_Trust->setRange(-1.000, 1.000);
	Disgust_Trust->addTerm(new fl::Triangle("-Disgust", -1.000, -1.000, 0.00));
	Disgust_Trust->addTerm(new fl::Triangle("Neutral", -1.000, 0.000, 1.00));
	Disgust_Trust->addTerm(new fl::Triangle("Trust+", 0.000, 1.000, 1.00));
	HateLoveEngine->addInputVariable(Disgust_Trust);


	// Fuzzy Output variable initalising (Hate TO Love)
	fl::OutputVariable* Hate_Love = new fl::OutputVariable;
	Hate_Love->setEnabled(true);
	Hate_Love->setName("-Hate<->Love+");
	Hate_Love->setRange(-1.000, 1.000);
	Hate_Love->fuzzyOutput()->setAccumulation(new fl::Maximum);
	Hate_Love->setDefuzzifier(new fl::Centroid(200));
	Hate_Love->setDefaultValue(fl::nan);
	Hate_Love->setLockPreviousOutputValue(false);
	Hate_Love->setLockOutputValueInRange(false);
	Hate_Love->addTerm(new fl::ZShape("-Hate", -0.900, -0.100));
	Hate_Love->addTerm(new fl::Bell("Neutral", 0.000, 0.500, 2.500));
	Hate_Love->addTerm(new fl::SShape("Love+", 0.100, 0.900));
	HateLoveEngine->addOutputVariable(Hate_Love);


	// Initalising rule block and defining rules for fuzzy logic
	fl::RuleBlock* Hate_Love_ruleBlock = new fl::RuleBlock;
	Hate_Love_ruleBlock->setEnabled(true);
	Hate_Love_ruleBlock->setName("");
	Hate_Love_ruleBlock->setConjunction(new fl::Minimum);
	Hate_Love_ruleBlock->setDisjunction(new fl::Maximum);
	Hate_Love_ruleBlock->setActivation(new fl::Minimum);
	Hate_Love_ruleBlock->addRule(fl::Rule::parse("if -Sadness<->Joy+ is -Sadness and -Disgust<->Trust+ is Trust+ then -Hate<->Love+ is Neutral", HateLoveEngine));
	Hate_Love_ruleBlock->addRule(fl::Rule::parse("if -Sadness<->Joy+ is -Sadness and -Disgust<->Trust+ is Neutral then -Hate<->Love+ is -Hate", HateLoveEngine));
	Hate_Love_ruleBlock->addRule(fl::Rule::parse("if -Sadness<->Joy+ is -Sadness and -Disgust<->Trust+ is -Disgust then -Hate<->Love+ is -Hate", HateLoveEngine));
	Hate_Love_ruleBlock->addRule(fl::Rule::parse("if -Sadness<->Joy+ is Neutral and -Disgust<->Trust+ is Trust+ then -Hate<->Love+ is Love+", HateLoveEngine));
	Hate_Love_ruleBlock->addRule(fl::Rule::parse("if -Sadness<->Joy+ is Neutral and -Disgust<->Trust+ is Neutral then -Hate<->Love+ is Neutral", HateLoveEngine));
	Hate_Love_ruleBlock->addRule(fl::Rule::parse("if -Sadness<->Joy+ is Neutral and -Disgust<->Trust+ is -Disgust then -Hate<->Love+ is -Hate", HateLoveEngine));
	Hate_Love_ruleBlock->addRule(fl::Rule::parse("if -Sadness<->Joy+ is Joy+ and -Disgust<->Trust+ is Trust+ then -Hate<->Love+ is Love+", HateLoveEngine));
	Hate_Love_ruleBlock->addRule(fl::Rule::parse("if -Sadness<->Joy+ is Joy+ and -Disgust<->Trust+ is Neutral then -Hate<->Love+ is Love+", HateLoveEngine));
	Hate_Love_ruleBlock->addRule(fl::Rule::parse("if -Sadness<->Joy+ is Joy+ and -Disgust<->Trust+ is -Disgust then -Hate<->Love+ is Neutral", HateLoveEngine));
	HateLoveEngine->addRuleBlock(Hate_Love_ruleBlock);

	Sadness_Joy->setInputValue(sadnessTOjoy);
	Disgust_Trust->setInputValue(disgustTOtrust);

	Sadness_Joy->fuzzify(sadnessTOjoy);
	Disgust_Trust->fuzzify(disgustTOtrust);

	HateLoveEngine->process();

	sadnessTOjoyScalar = Sadness_Joy->getInputValue();
	disgustTOtrustScalar = Disgust_Trust->getInputValue();
	hateTOloveScalar = Hate_Love->getOutputValue();


}

void FL_Agent::FLfor_ContemptTOSubmission(float disgustTOtrust, float fearTOanger)
{
	// Initalising of fl engine (Contempt TO Submission Fuzzy Engine)
	fl::Engine* ContemptSubmissionEngine = new fl::Engine;
	ContemptSubmissionEngine->setName("Fuzzy System - Contempt <-> Submission");

	// initalising of first input (Disgust TO Trust)
fl:InputVariable* Disgust_Trust = new fl::InputVariable;
	Disgust_Trust->setEnabled(true);
	Disgust_Trust->setName("-Disgust<->Trust+");
	Disgust_Trust->setRange(-1.000, 1.000);
	Disgust_Trust->addTerm(new fl::Triangle("-Disgust", -1.000, -1.000, 0.00));
	Disgust_Trust->addTerm(new fl::Triangle("Neutral", -1.000, 0.000, 1.00));
	Disgust_Trust->addTerm(new fl::Triangle("Trust+", 0.000, 1.000, 1.00));
	ContemptSubmissionEngine->addInputVariable(Disgust_Trust);

	// Initalising of second Input (Fear TO Anger)
	fl::InputVariable* Fear_Anger = new fl::InputVariable;
	Fear_Anger->setEnabled(true);
	Fear_Anger->setName("-Fear<->Anger+");
	Fear_Anger->setRange(-1.000, 1.000);
	Fear_Anger->addTerm(new fl::Triangle("-Fear", -1.000, -1.000, 0.00));
	Fear_Anger->addTerm(new fl::Triangle("Neutral", -1.000, 0.000, 1.00));
	Fear_Anger->addTerm(new fl::Triangle("Anger+", 0.000, 1.000, 1.00));
	ContemptSubmissionEngine->addInputVariable(Fear_Anger);


	// Fuzzy Output variable initalising (Hate TO Love)
	fl::OutputVariable* Contempt_Submission = new fl::OutputVariable;
	Contempt_Submission->setEnabled(true);
	Contempt_Submission->setName("-Contempt<->Submission+");
	Contempt_Submission->setRange(-1.000, 1.000);
	Contempt_Submission->fuzzyOutput()->setAccumulation(new fl::Maximum);
	Contempt_Submission->setDefuzzifier(new fl::Centroid(200));
	Contempt_Submission->setDefaultValue(fl::nan);
	Contempt_Submission->setLockPreviousOutputValue(false);
	Contempt_Submission->setLockOutputValueInRange(false);
	Contempt_Submission->addTerm(new fl::ZShape("-Contempt", -0.900, -0.100));
	Contempt_Submission->addTerm(new fl::Bell("Neutral", 0.000, 0.500, 2.500));
	Contempt_Submission->addTerm(new fl::SShape("Submission+", 0.100, 0.900));
	ContemptSubmissionEngine->addOutputVariable(Contempt_Submission);


	// Initalising rule block and defining rules for fuzzy logic
	fl::RuleBlock* Contempt_Submission_ruleBlock = new fl::RuleBlock;
	Contempt_Submission_ruleBlock->setEnabled(true);
	Contempt_Submission_ruleBlock->setName("");
	Contempt_Submission_ruleBlock->setConjunction(new fl::Minimum);
	Contempt_Submission_ruleBlock->setDisjunction(new fl::Maximum);
	Contempt_Submission_ruleBlock->setActivation(new fl::Minimum);
	Contempt_Submission_ruleBlock->addRule(fl::Rule::parse("if -Disgust<->Trust+ is -Disgust and -Fear<->Anger+ is Anger+ then -Contempt<->Submission+ is Neutral", ContemptSubmissionEngine));
	Contempt_Submission_ruleBlock->addRule(fl::Rule::parse("if -Disgust<->Trust+ is -Disgust and -Fear<->Anger+ is Neutral then -Contempt<->Submission+ is -Contempt", ContemptSubmissionEngine));
	Contempt_Submission_ruleBlock->addRule(fl::Rule::parse("if -Disgust<->Trust+ is -Disgust and -Fear<->Anger+ is -Fear then -Contempt<->Submission+ is -Contempt", ContemptSubmissionEngine));
	Contempt_Submission_ruleBlock->addRule(fl::Rule::parse("if -Disgust<->Trust+ is Neutral and -Fear<->Anger+ is Anger+ then -Contempt<->Submission+ is Submission+", ContemptSubmissionEngine));
	Contempt_Submission_ruleBlock->addRule(fl::Rule::parse("if -Disgust<->Trust+ is Neutral and -Fear<->Anger+ is Neutral then -Contempt<->Submission+ is Neutral", ContemptSubmissionEngine));
	Contempt_Submission_ruleBlock->addRule(fl::Rule::parse("if -Disgust<->Trust+ is Neutral and -Fear<->Anger+ is -Fear then -Contempt<->Submission+ is -Contempt", ContemptSubmissionEngine));
	Contempt_Submission_ruleBlock->addRule(fl::Rule::parse("if -Disgust<->Trust+ is Trust+ and -Fear<->Anger+ is Anger+ then -Contempt<->Submission+ is Submission+", ContemptSubmissionEngine));
	Contempt_Submission_ruleBlock->addRule(fl::Rule::parse("if -Disgust<->Trust+ is Trust+ and -Fear<->Anger+ is Neutral then -Contempt<->Submission+ is Submission+", ContemptSubmissionEngine));
	Contempt_Submission_ruleBlock->addRule(fl::Rule::parse("if -Disgust<->Trust+ is Trust+ and -Fear<->Anger+ is -Fear then -Contempt<->Submission+ is Neutral", ContemptSubmissionEngine));
	ContemptSubmissionEngine->addRuleBlock(Contempt_Submission_ruleBlock);

	Disgust_Trust->setInputValue(disgustTOtrust);
	Fear_Anger->setInputValue(fearTOanger);

	Disgust_Trust->fuzzify(disgustTOtrust);
	Fear_Anger->fuzzify(fearTOanger);

	ContemptSubmissionEngine->process();

	disgustTOtrustScalar = Disgust_Trust->getInputValue();
	fearTOangerScalar = Fear_Anger->getInputValue();
	contemptTOsubmissionScalar = Contempt_Submission->getOutputValue();
}

void FL_Agent::FLfor_AggressionTOAwe(float fearTOanger, float anticipationTOsurprise)
{
	// Initalising of fl engine (Aggression TO Awe Fuzzy Engine)
	fl::Engine* AggressionAweEngine = new fl::Engine;
	AggressionAweEngine->setName("Fuzzy System - Aggression <-> Awe");

	// initalising of first input (Fear TO Anger)
fl:InputVariable* Fear_Anger = new fl::InputVariable;
	Fear_Anger->setEnabled(true);
	Fear_Anger->setName("-Fear<->Anger+");
	Fear_Anger->setRange(-1.000, 1.000);
	Fear_Anger->addTerm(new fl::Triangle("-Fear", -1.000, -1.000, 0.00));
	Fear_Anger->addTerm(new fl::Triangle("Neutral", -1.000, 0.000, 1.00));
	Fear_Anger->addTerm(new fl::Triangle("Anger+", 0.000, 1.000, 1.00));
	AggressionAweEngine->addInputVariable(Fear_Anger);

	// Initalising of second Input (Anticipation TO Surprise)
	fl::InputVariable* Anticipation_Surprise = new fl::InputVariable;
	Anticipation_Surprise->setEnabled(true);
	Anticipation_Surprise->setName("-Anticipation<->Surprise+");
	Anticipation_Surprise->setRange(-1.000, 1.000);
	Anticipation_Surprise->addTerm(new fl::Triangle("-Anticipation", -1.000, -1.000, 0.00));
	Anticipation_Surprise->addTerm(new fl::Triangle("Neutral", -1.000, 0.000, 1.00));
	Anticipation_Surprise->addTerm(new fl::Triangle("Surprise+", 0.000, 1.000, 1.00));
	AggressionAweEngine->addInputVariable(Anticipation_Surprise);


	// Fuzzy Output variable initalising (Aggression TO Awe)
	fl::OutputVariable* Aggression_Awe = new fl::OutputVariable;
	Aggression_Awe->setEnabled(true);
	Aggression_Awe->setName("-Aggression<->Awe+");
	Aggression_Awe->setRange(-1.000, 1.000);
	Aggression_Awe->fuzzyOutput()->setAccumulation(new fl::Maximum);
	Aggression_Awe->setDefuzzifier(new fl::Centroid(200));
	Aggression_Awe->setDefaultValue(fl::nan);
	Aggression_Awe->setLockPreviousOutputValue(false);
	Aggression_Awe->setLockOutputValueInRange(false);
	Aggression_Awe->addTerm(new fl::ZShape("-Aggression", -0.900, -0.100));
	Aggression_Awe->addTerm(new fl::Bell("Neutral", 0.000, 0.500, 2.500));
	Aggression_Awe->addTerm(new fl::SShape("Awe+", 0.100, 0.900));
	AggressionAweEngine->addOutputVariable(Aggression_Awe);


	// Initalising rule block and defining rules for fuzzy logic
	fl::RuleBlock* Aggression_Awe_ruleBlock = new fl::RuleBlock;
	Aggression_Awe_ruleBlock->setEnabled(true);
	Aggression_Awe_ruleBlock->setName("");
	Aggression_Awe_ruleBlock->setConjunction(new fl::Minimum);
	Aggression_Awe_ruleBlock->setDisjunction(new fl::Maximum);
	Aggression_Awe_ruleBlock->setActivation(new fl::Minimum);
	Aggression_Awe_ruleBlock->addRule(fl::Rule::parse("if -Fear<->Anger+ is -Fear and -Anticipation<->Surprise+ is Surprise+ then -Aggression<->Awe+ is Neutral", AggressionAweEngine));
	Aggression_Awe_ruleBlock->addRule(fl::Rule::parse("if -Fear<->Anger+ is -Fear and -Anticipation<->Surprise+ is Neutral then -Aggression<->Awe+ is -Aggression", AggressionAweEngine));
	Aggression_Awe_ruleBlock->addRule(fl::Rule::parse("if -Fear<->Anger+ is -Fear and -Anticipation<->Surprise+ is -Anticipation then -Aggression<->-Aggression is Awe+", AggressionAweEngine));
	Aggression_Awe_ruleBlock->addRule(fl::Rule::parse("if -Fear<->Anger+ is Neutral and -Anticipation<->Surprise+ is Surprise+ then -Aggression<->Awe+ is Awe+", AggressionAweEngine));
	Aggression_Awe_ruleBlock->addRule(fl::Rule::parse("if -Fear<->Anger+ is Neutral and -Anticipation<->Surprise+ is Neutral then -Aggression<->Awe+ is Neutral", AggressionAweEngine));
	Aggression_Awe_ruleBlock->addRule(fl::Rule::parse("if -Fear<->Anger+ is Neutral and -Anticipation<->Surprise+ is -Anticipation then -Aggression<->Awe+ is -Aggression", AggressionAweEngine));
	Aggression_Awe_ruleBlock->addRule(fl::Rule::parse("if -Fear<->Anger+ is Anger+ and -Anticipation<->Surprise+ is Surprise+ then -Aggression<->Awe+ is Awe+", AggressionAweEngine));
	Aggression_Awe_ruleBlock->addRule(fl::Rule::parse("if -Fear<->Anger+ is Anger+ and -Anticipation<->Surprise+ is Neutral then -Aggression<->Awe+ is Awe+", AggressionAweEngine));
	Aggression_Awe_ruleBlock->addRule(fl::Rule::parse("if -Fear<->Anger+ is Anger+ and -Anticipation<->Surprise+ is -Anticipation then -Aggression<->Awe+ is Neutral", AggressionAweEngine));
	AggressionAweEngine->addRuleBlock(Aggression_Awe_ruleBlock);

	Fear_Anger->setInputValue(fearTOanger);
	Anticipation_Surprise->setInputValue(anticipationTOsurprise);

	Fear_Anger->fuzzify(fearTOanger);
	Anticipation_Surprise->fuzzify(anticipationTOsurprise);

	AggressionAweEngine->process();

	fearTOangerScalar = Fear_Anger->getInputValue();
	anticipationTOsurpriseScalar = Anticipation_Surprise->getInputValue();
	aggressionTOaweScalar = Aggression_Awe->getOutputValue();
}

void FL_Agent::FLfor_DisapprovalTOOptimism(float anticipationTOsurprise, float sadnessTOjoy)
{
	// Initalising of fl engine (Disapproval TO Optimism Fuzzy Engine)
	fl::Engine* DisapprovalOptimismEngine = new fl::Engine;
	DisapprovalOptimismEngine->setName("Fuzzy System - Disapproval <-> Optimism");

	// initalising of first input (Anticipation TO Surprise)
fl:InputVariable* Anticipation_Surprise = new fl::InputVariable;
	Anticipation_Surprise->setEnabled(true);
	Anticipation_Surprise->setName("-Anticipation<->Surprise+");
	Anticipation_Surprise->setRange(-1.000, 1.000);
	Anticipation_Surprise->addTerm(new fl::Triangle("-Anticipation", -1.000, -1.000, 0.00));
	Anticipation_Surprise->addTerm(new fl::Triangle("Neutral", -1.000, 0.000, 1.00));
	Anticipation_Surprise->addTerm(new fl::Triangle("Surprise+", 0.000, 1.000, 1.00));
	DisapprovalOptimismEngine->addInputVariable(Anticipation_Surprise);

	// Initalising of second Input (Sadness TO Joy)
	fl::InputVariable* Sadness_Joy = new fl::InputVariable;
	Sadness_Joy->setEnabled(true);
	Sadness_Joy->setName("-Sadness<->Joy+");
	Sadness_Joy->setRange(-1.000, 1.000);
	Sadness_Joy->addTerm(new fl::Triangle("-Sadness", -1.000, -1.000, 0.00));
	Sadness_Joy->addTerm(new fl::Triangle("Neutral", -1.000, 0.000, 1.00));
	Sadness_Joy->addTerm(new fl::Triangle("Joy+", 0.000, 1.000, 1.00));
	DisapprovalOptimismEngine->addInputVariable(Sadness_Joy);


	// Fuzzy Output variable initalising (Disapproval TO Optimism)
	fl::OutputVariable* Disapproval_Optimism = new fl::OutputVariable;
	Disapproval_Optimism->setEnabled(true);
	Disapproval_Optimism->setName("-Disapproval<->Optimism+");
	Disapproval_Optimism->setRange(-1.000, 1.000);
	Disapproval_Optimism->fuzzyOutput()->setAccumulation(new fl::Maximum);
	Disapproval_Optimism->setDefuzzifier(new fl::Centroid(200));
	Disapproval_Optimism->setDefaultValue(fl::nan);
	Disapproval_Optimism->setLockPreviousOutputValue(false);
	Disapproval_Optimism->setLockOutputValueInRange(false);
	Disapproval_Optimism->addTerm(new fl::ZShape("-Disapproval", -0.900, -0.100));
	Disapproval_Optimism->addTerm(new fl::Bell("Neutral", 0.000, 0.500, 2.500));
	Disapproval_Optimism->addTerm(new fl::SShape("Optimism+", 0.100, 0.900));
	DisapprovalOptimismEngine->addOutputVariable(Disapproval_Optimism);


	// Initalising rule block and defining rules for fuzzy logic
	fl::RuleBlock* Disapproval_Optimism_ruleBlock = new fl::RuleBlock;
	Disapproval_Optimism_ruleBlock->setEnabled(true);
	Disapproval_Optimism_ruleBlock->setName("");
	Disapproval_Optimism_ruleBlock->setConjunction(new fl::Minimum);
	Disapproval_Optimism_ruleBlock->setDisjunction(new fl::Maximum);
	Disapproval_Optimism_ruleBlock->setActivation(new fl::Minimum);
	Disapproval_Optimism_ruleBlock->addRule(fl::Rule::parse("if -Anticipation<->Surprise+ is -Anticipation and -Sadness<->Joy+ is Joy+ then -Disapproval<->Optimism+ is Neutral", DisapprovalOptimismEngine));
	Disapproval_Optimism_ruleBlock->addRule(fl::Rule::parse("if -Anticipation<->Surprise+ is -Anticipation and -Sadness<->Joy+ is Neutral then -Disapproval<->Optimism+ is -Disapproval", DisapprovalOptimismEngine));
	Disapproval_Optimism_ruleBlock->addRule(fl::Rule::parse("if -Anticipation<->Surprise+ is -Anticipation and -Sadness<->Joy+ is -Sadness then -Disapproval<->Optimism+ is -Disapproval", DisapprovalOptimismEngine));
	Disapproval_Optimism_ruleBlock->addRule(fl::Rule::parse("if -Anticipation<->Surprise+ is Neutral and -Sadness<->Joy+ is Joy+ then -Disapproval<->Optimism+ is Optimism+", DisapprovalOptimismEngine));
	Disapproval_Optimism_ruleBlock->addRule(fl::Rule::parse("if -Anticipation<->Surprise+ is Neutral and -Sadness<->Joy+ is Neutral then -Disapproval<->Optimism+ is Neutral", DisapprovalOptimismEngine));
	Disapproval_Optimism_ruleBlock->addRule(fl::Rule::parse("if -Anticipation<->Surprise+ is Neutral and -Sadness<->Joy+ is Sadness then -Disapproval<->Optimism+ is -Disapproval", DisapprovalOptimismEngine));
	Disapproval_Optimism_ruleBlock->addRule(fl::Rule::parse("if -Anticipation<->Surprise+ is Surprise+ and -Sadness<->Joy+ is Joy+ then -Disapproval<->Optimism+ is Optimism+", DisapprovalOptimismEngine));
	Disapproval_Optimism_ruleBlock->addRule(fl::Rule::parse("if -Anticipation<->Surprise+ is Surprise+ and -Sadness<->Joy+ is Neutral then -Disapproval<->Optimism+ is Optimism+", DisapprovalOptimismEngine));
	Disapproval_Optimism_ruleBlock->addRule(fl::Rule::parse("if -Anticipation<->Surprise+ is Surprise+ and -Sadness<->Joy+ is Sadness then -Disapproval<->Optimism+ is Neutral", DisapprovalOptimismEngine));
	DisapprovalOptimismEngine->addRuleBlock(Disapproval_Optimism_ruleBlock);

	Anticipation_Surprise->setInputValue(anticipationTOsurprise);
	Sadness_Joy->setInputValue(sadnessTOjoy);

	Anticipation_Surprise->fuzzify(anticipationTOsurprise);
	Sadness_Joy->fuzzify(sadnessTOjoy);

	DisapprovalOptimismEngine->process();

	anticipationTOsurpriseScalar = Anticipation_Surprise->getInputValue();
	sadnessTOjoyScalar = Sadness_Joy->getInputValue();
	disapprovalTOoptimismScalar = Disapproval_Optimism->getOutputValue();
}


void FL_Agent::GetAllEmotionalValues()
{
	GetAllEventEmotionalValues();
	GetAllReactionEmotionalValues();
	GetAllObjectEmotionalValues();
}

void FL_Agent::GetAllEventEmotionalValues()
{
	Emotionalvalueof_joy();
	Emotionalvalueof_distress();
	Emotionalvalueof_happy_for();
	Emotionalvalueof_pity();
	Emotionalvalueof_gloating();
	Emotionalvalueof_resentment();
	Emotionalvalueof_hope();
	Emotionalvalueof_fear();
	Emotionalvalueof_satisfaction();
	Emotionalvalueof_fears_confirmed();
	Emotionalvalueof_relief();
	Emotionalvalueof_disapointment();
}
void FL_Agent::GetAllReactionEmotionalValues()
{
	Emotionalvalueof_pride();
	Emotionalvalueof_shame();
	Emotionalvalueof_admiration();
	Emotionalvalueof_reproach();
	Emotionalvalueof_gratification();
	Emotionalvalueof_remorse();
	Emotionalvalueof_gratitude();
	Emotionalvalueof_anger();
}
void FL_Agent::GetAllObjectEmotionalValues()
{
	Emotionalvalueof_love();
	Emotionalvalueof_hate();
}

// Working out what values are for each emotion

// In the case of 2 emotions or more used, they are added togeather (As positive values if negative)
// and are divided by the number of emotions to get the average



// Emotions for Events reactions

// Joy = Joy+
void FL_Agent::Emotionalvalueof_joy()
{
	if (sadnessTOjoyScalar >= 0)
	{ 
		joy = sadnessTOjoyScalar;
	}
}

// Distress = -Sadness
void FL_Agent::Emotionalvalueof_distress()
{
	if (sadnessTOjoyScalar <= 0)
	{
		distress = sadnessTOjoyScalar;
	}
}

// Happy-for = Submission+ & Joy+
void FL_Agent::Emotionalvalueof_happy_for()
{
	if (contemptTOsubmissionScalar >= 0 && sadnessTOjoyScalar >= 0)
	{
		happy_for = (sadnessTOjoyScalar + contemptTOsubmissionScalar) / 2;
	}
}

// Pity = Submission+ & -Sadness
void FL_Agent::Emotionalvalueof_pity()
{
	if (contemptTOsubmissionScalar >= 0 && sadnessTOjoyScalar <= 0)
	{
		pity = (contemptTOsubmissionScalar + -sadnessTOjoyScalar) / 2;
	}
}

// Gloating = -Contempt & Joy+
void FL_Agent::Emotionalvalueof_gloating()
{
	if (contemptTOsubmissionScalar <= 0 && sadnessTOjoyScalar >= 0)
	{
		gloating = (-sadnessTOjoyScalar + contemptTOsubmissionScalar) / 2;
	}
}

// Resentment = -Contempt & -Sadness
void FL_Agent::Emotionalvalueof_resentment()
{
	if (contemptTOsubmissionScalar <= 0 && sadnessTOjoyScalar <= 0)
	{
		resentment = (-sadnessTOjoyScalar + -contemptTOsubmissionScalar) / 2;
	}
}

// Hope = -Anticipation & Joy+
void FL_Agent::Emotionalvalueof_hope()
{
	if (contemptTOsubmissionScalar <= 0 && sadnessTOjoyScalar >= 0)
	{
		hope = (-sadnessTOjoyScalar + sadnessTOjoyScalar) / 2;
	}
}

// Fear = -Anticipation & -Sadness
void FL_Agent::Emotionalvalueof_fear()
{
	if (anticipationTOsurpriseScalar <= 0 && sadnessTOjoyScalar <= 0)
	{
		fear = (-anticipationTOsurpriseScalar + -sadnessTOjoyScalar) / 2;
	}
}

// Satisfaction = Awe+
void FL_Agent::Emotionalvalueof_satisfaction()
{
	if (aggressionTOaweScalar >= 0)
	{
		satisfaction = (aggressionTOaweScalar);
	}
}

// Fears-Confirmed = -Aggression
void FL_Agent::Emotionalvalueof_fears_confirmed()
{
	if (aggressionTOaweScalar <= 0)
	{
		fears_confirmed = (-aggressionTOaweScalar);
	}
}

// Relief = Surprise+ & Joy+
void FL_Agent::Emotionalvalueof_relief()
{
	if (anticipationTOsurpriseScalar >= 0 && sadnessTOjoyScalar >= 0)
	{
		relief = (anticipationTOsurpriseScalar + sadnessTOjoyScalar) / 2;
	}
}

// Dissapointment = Surprise+ & -Sadness
void FL_Agent::Emotionalvalueof_disapointment()
{
	if (anticipationTOsurpriseScalar >= 0 && sadnessTOjoyScalar <= 0)
	{
		disapointment = (anticipationTOsurpriseScalar + -sadnessTOjoyScalar) / 2;
	}
}



// emotions used for reacting to actions from agents

// Pride = Optimism+ & Joy+
void FL_Agent::Emotionalvalueof_pride()
{
	if (disapprovalTOoptimismScalar >= 0 && sadnessTOjoyScalar >= 0)
	{
		pride = (disapprovalTOoptimismScalar + sadnessTOjoyScalar) / 2;
	}
}

// Shame = -Dissaproval & -Sadness
void FL_Agent::Emotionalvalueof_shame()
{
	if (disapprovalTOoptimism <= 0 && sadnessTOjoyScalar <= 0)
	{
		shame = (-disapprovalTOoptimismScalar + -sadnessTOjoyScalar) / 2;
	}
}

// Admiration = Optimism+ & Joy+
void FL_Agent::Emotionalvalueof_admiration()
{
	if (disapprovalTOoptimismScalar >= 0 && sadnessTOjoyScalar >= 0)
	{
		admiration = (disapprovalTOoptimismScalar + sadnessTOjoyScalar) / 2;
	}
}

// Reproach = -Contempt & -Dissaproval
void FL_Agent::Emotionalvalueof_reproach()
{
	if (contemptTOsubmissionScalar <= 0 && disapprovalTOoptimismScalar <= 0)
	{
		reproach = (-anticipationTOsurpriseScalar + -sadnessTOjoyScalar) / 2;
	}
}

// Gratificaiton = Submission+ & Optimism+
void FL_Agent::Emotionalvalueof_gratification()
{
	if (contemptTOsubmissionScalar >= 0 && disapprovalTOoptimismScalar >= 0)
	{
		gratification = (contemptTOsubmissionScalar + disapprovalTOoptimismScalar) / 2;
	}
}

// Remorse = -Dissaproval
void FL_Agent::Emotionalvalueof_remorse()
{
	if (disapprovalTOoptimismScalar <= 0)
	{
		remorse = -disapprovalTOoptimismScalar;
	}
}

// Gratitude = Optimism+
void FL_Agent::Emotionalvalueof_gratitude()
{
	if (disapprovalTOoptimismScalar >=0)
	{
		gratitude = disapprovalTOoptimismScalar;
	}
}

// Anger = Anger+
void FL_Agent::Emotionalvalueof_anger()
{
	if (fearTOangerScalar >= 0)
	{
		anger = fearTOangerScalar;
	}
}


// Aspects of objects

// Love = Love+
void FL_Agent::Emotionalvalueof_love()
{
	if (hateTOloveScalar >= 0)
	{
		love = hateTOloveScalar;
	}
}

// Hate = -Hate
void FL_Agent::Emotionalvalueof_hate()
{
	if (hateTOloveScalar <= 0)
	{
		hate = -hateTOloveScalar;
	}
}


void FL_Agent::Update()
{

	FLfor_HateTOLove(sadnessTOjoy, disgustTOtrust);
	FLfor_ContemptTOSubmission(disgustTOtrust, fearTOanger);
	FLfor_AggressionTOAwe(fearTOanger, anticipationTOsurprise);
	FLfor_DisapprovalTOOptimism(anticipationTOsurprise, sadnessTOjoy);

	GetAllEmotionalValues();
}


void FL_Agent::FLfor_All_Emotions(float sadnessTOjoy, float disgustTOtrust, float fearTOanger, float anticipationTOsurprise)
{
	FLfor_HateTOLove(sadnessTOjoy, disgustTOtrust);
	FLfor_ContemptTOSubmission(disgustTOtrust, fearTOanger);
	FLfor_AggressionTOAwe(fearTOanger, anticipationTOsurprise);
	FLfor_DisapprovalTOOptimism(anticipationTOsurprise, sadnessTOjoy);

}