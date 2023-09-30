cmake_minimum_required(VERSION 3.15)
project(Assignment2_sentiment)

set(CMAKE_CXX_STANDARD 17)

# Specify input file paths
set (input01 "data/train_dataset_20k.csv")
set (input02 "data/test_dataset_10k.csv")
set (input03 "data/test_dataset_sentiment_10k.csv")


# Copy data files to build directory
foreach(file IN LISTS input01 input02 input03)
    configure_file(${file} ${file} COPYONLY)
endforeach()

# Show compiler output and enable warnings
set(CMAKE_VERBOSE_MAKEFILE ON)
add_compile_options(-Wall -Wextra -pedantic)

# Create the executable(s)
add_executable(SentimentClassifier main.cpp DSString.cpp SentimentClassifier.cpp)
add_executable(test_DSString test_DSString.cpp DSString.cpp)

set(CMAKE_VERBOSE_MAKEFILE OFF)
