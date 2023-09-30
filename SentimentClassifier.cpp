#include "SentimentClassifier.h"
#include "DSString.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>
#include <algorithm>

SentimentClassifier::SentimentClassifier() {}

void SentimentClassifier::train(const char* trainingDataFile) {
    std::ifstream file(trainingDataFile);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open training data file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<DSString> tokens = tokenize(line.c_str());

        int sentiment = tokens[0].customToInt(); // Convert DSString to int

        for (size_t i = 1; i < tokens.size(); ++i) {
            // Count positive and negative words based on sentiment value
            if (sentiment == 4) {
                positiveWordCounts[tokens[i]]++;
            } else if (sentiment == 0) {
                negativeWordCounts[tokens[i]]++;
            }
        }
    }

    file.close();
}

void SentimentClassifier::predict(const char* testingDataFile, const char* predictionsFile) {
    std::ifstream file(testingDataFile);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open testing data file." << std::endl;
        return;
    }

    std::ofstream output(predictionsFile);
    if (!output.is_open()) {
        std::cerr << "Error: Could not create sentiment output file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Skip empty lines
        if (line.empty()) {
            continue;
        }

        DSString dsLine = line.c_str(); // Convert std::string to DSString
        std::vector<DSString> tokens = tokenize(dsLine.c_str());

        // Ensure the line has the expected number of tokens
        if (tokens.size() < 2) {
            std::cerr << "Invalid data format in testing file: " << line << std::endl;
            continue;
        }

        DSString tweetID = tokens[0];
        DSString sentiment = "4";

        // Write output file
        output << sentiment << ", " << tweetID << std::endl;

        // Store accuracy calculation
        predictions.push_back(std::make_pair(tweetID, sentiment));
    }

    file.close();
    output.close();
}

void SentimentClassifier::evaluatePredictions(const char* groundTruthFile) {
    std::ifstream truthFileStream(groundTruthFile);
    if (!truthFileStream.is_open()) {
        std::cerr << "Error: Could not open ground truth sentiment file: " << groundTruthFile << std::endl;
        return;
    }

    // Skip the header line
    std::string header;
    std::getline(truthFileStream, header);

    std::string line;
    int sentiment;

    while (std::getline(truthFileStream, line)) {
        std::istringstream iss(line);
        std::string token;

        // Read sentiment label from the first column
        std::getline(iss, token, ',');
        sentiment = std::stoi(token);

        groundTruth.push_back(sentiment);
    }

    truthFileStream.close();

    /* Check if there are predictions to evaluate
    if (groundTruth.size() != predictions.size()) {
        std::cerr << "Error: Number of predictions does not match the number of ground truth sentiments." << std::endl;
        std::cout << "Ground Truth Size: " << groundTruth.size() << std::endl;
        std::cout << "Predictions Size: " << predictions.size() << std::endl;
        return;
    }
    */

    int correctPredictions = 0;
    int totalPredictions = groundTruth.size();

    // Compare predictions with ground truth
    for (size_t i = 0; i < predictions.size(); ++i) {
        int predictedSentiment = predictions[i].second.customToInt();
        if (predictedSentiment == groundTruth[i]) {
            correctPredictions++;
        }
    }

    double accuracy = 0.0;
    if (totalPredictions != 0) {
        accuracy = (static_cast<double>(correctPredictions) / totalPredictions) * 100.0;
    }

    // Output accuracy to console
    std::cout << "Accuracy: " << accuracy << "%" << std::endl;

    // Write accuracy to "output.txt"
    std::ofstream accuracyFileStream("output.txt");
    if (accuracyFileStream.is_open()) {
        accuracyFileStream << "Accuracy: " << accuracy << "%" << std::endl;
        accuracyFileStream.close();
        std::cout << "Accuracy saved to output.txt." << std::endl;
    } else {
        std::cerr << "Error: Could not write accuracy to file." << std::endl;
    }
}



std::vector<std::string> tokenize(const std::string& input) {
    std::vector<std::string> tokens;
    std::istringstream iss(input);
    std::string word;
    while (iss >> word) {
        // Convert word to lowercase for basic lemmatization
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        tokens.push_back(word);
    }
    return tokens;
}
