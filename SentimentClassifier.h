#ifndef SENTIMENTCLASSIFIER_H
#define SENTIMENTCLASSIFIER_H

#include "DSString.h" // Include DSString header
#include <map>
#include <vector>

enum SentimentValue {
    POSITIVE,
    NEGATIVE,
    NEUTRAL
};

class SentimentClassifier {
public:
    SentimentClassifier();
    SentimentValue analyzeSentiment(const DSString& tweet); // Use DSString here

    void train(const char* trainingDataFile);
    void predict(const char* testingDataFile, const char* predictionsFile);
    void evaluatePredictions(const char* groundTruthFile);
    std::vector<DSString> tokenize(const DSString& input); // Use DSString here
    

private:
    std::map<DSString, int> positiveWordCounts;  // Use DSString here
    std::map<DSString, int> negativeWordCounts;  // Use DSString here
    std::vector<std::pair<DSString, DSString>> predictions;  // Use DSString here
    std::vector<int> groundTruth;

};

#endif
