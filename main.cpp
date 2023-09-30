#include <iostream>
#include "SentimentClassifier.h"
#include "DSString.h"
#include <fstream>

int main(int argc, char **argv) {

    SentimentClassifier classifier;

    // Training using training data file
    std::vector<DSString> words;
    classifier.train("data/train_dataset_20k.csv");

    // Predict sentiments for tweets
    classifier.predict("data/test_dataset_10k.csv", "predictions.txt");

    // Evaluate predictions (without separate files)
    classifier.evaluatePredictions("data/test_dataset_sentiment_10k.csv");
    return 0;
}