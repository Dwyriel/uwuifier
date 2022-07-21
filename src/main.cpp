#include <iostream>
#include <string>
#include <thread>
#include "Logger.h"
#include "UwUifier.h"
#include <fstream>

#define UWUIFIED

// Error/Warning/Help messages
#ifndef UWUIFIED
static std::string NO_ARG_PASSED = "No arguments passed";
static std::string HELP_COMMAND = "?";
static std::string INVALID_COMMAND = "Invalid argument, try -h or --help for help";
static std::string NO_TEXT_ARG_PASSED = "No text passed";
static std::string NO_FILE_ARG_PASSED = "No file passed";
static std::string TEXT_OUTPUT_MESSAGE = "Uwufied text:";
static std::string FILE_OUTPUT_MESSAGE = "Uwufied file:";
#endif
#ifdef UWUIFIED
static std::string NO_ARG_PASSED = "Nyo awguwumewnts passed";
static std::string HELP_COMMAND = "?";
static std::string INVALID_COMMAND = "Invawid awguwumewnt, twy -h ow --help fow hewp";
static std::string NO_TEXT_ARG_PASSED = "Nyo text passed";
static std::string NO_FILE_ARG_PASSED = "Nyo fiwe passed";
static std::string TEXT_OUTPUT_MESSAGE = "Uwufied text:";
static std::string FILE_OUTPUT_MESSAGE = "Uwufied fiwe:";
#endif

// Arguments
const std::string help1 = "-h", help2 = "--help";
const std::string file_cmd = "-f", text_cmd = "-t", output_file_cmd = "-o";

static std::string PROGRAM_PATH = "";

void setProgramPath(char* relative_path){
    PROGRAM_PATH = realpath(relative_path, NULL);
    size_t pos = PROGRAM_PATH.find_last_of("/");
    PROGRAM_PATH.erase(pos+1);
}

int main(int argc, char **argv) {

    setProgramPath(argv[0]);
    Logger::LogInfo(PROGRAM_PATH);

    return 0 ;

    std::ofstream outfile ("test.txt");

    outfile << "my text here!" << std::endl;

    outfile.close();

    return 0;
    std::string result, firstCommand, text, secondCommand, outputFile;
    bool outputToFile = false;
    if(argc==1){
        Logger::LogError(NO_ARG_PASSED);
        return 1;
    }
    if(argc > 1){
        //help command
        if((help1.compare(argv[1]) == 0 || help2.compare(argv[1]) == 0)){ //TODO help command
            std::cout << "\033[38;5;252m" << "I can't hewp yowo yet, sowwy >.<" << std::endl;
            return 0;
        }
        firstCommand = argv[1];
        if(firstCommand.compare(text_cmd) && firstCommand.compare(file_cmd)){
            Logger::LogWarning(INVALID_COMMAND);
            return 1;
        }
        if(argc<=2){
            if(!firstCommand.compare(text_cmd))
                Logger::LogWarning(NO_TEXT_ARG_PASSED);
            if(!firstCommand.compare(file_cmd))
                Logger::LogWarning(NO_FILE_ARG_PASSED);
            return 1;
        }
        text = argv[2];
        if(argc>4){
            secondCommand = argv[3];
            outputFile = argv[4];
            if(!secondCommand.compare(output_file_cmd)){
                //verify if output file is valid (if it doesn't exist already, if it can be created, etc)
                Logger::LogInfo("Outputing to file");
                outputToFile = true;
            }
        }
        if(!firstCommand.compare(text_cmd)){
            UwUifier::uwuify(text);
            if(!outputToFile){
                Logger::Log(LogLevel::None, TEXT_OUTPUT_MESSAGE);
                Logger::Log(LogLevel::None, text);
                return 0;
            }
        }
        if(!firstCommand.compare(file_cmd)){
            result = "";
            //TODO read from file
            if(!outputToFile){
                Logger::Log(LogLevel::None, FILE_OUTPUT_MESSAGE);
                Logger::Log(LogLevel::None, result);
                return 0;
            }
        }
    }
    //writeToFile
    return 0;
}

