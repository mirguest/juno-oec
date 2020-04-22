#ifndef OECStep_h
#define OECStep_h

/*
 * OECStep represents a step during event classification in OEC Controller.
 * It contains a pair of OECProcessor and OECClassifier.
 *
 * During processing one step, the OECProcessor will be invoked first, 
 * then the tag will be decided in the OECClassifier.
 *
 * After processing one step, the controller could decide to jump to another step or return.
 */

class OECStep {
public:
    OECStep();

    bool ();
private:
    OECProcessor* processor;
    OECClassifier* classifier;
};

#endif
