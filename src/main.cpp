#include <iostream>
#include <string>
#include <thread>
#include "Logger.h"
#include "UwUifier.h"

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
const std::string file_cmd = "-f", text_cmd = "-t";

int main(int argc, char **argv) {/*
    std::string text = "nano is ok, rodopiante, laranja";

    Logger::LogInfo(UwUifier::uwuify(text));


    return 0;*/
    Logger::Log(LogLevel::None, TEXT_OUTPUT_MESSAGE);
    Logger::Log(LogLevel::None, UwUifier::uwuify("The affectionate stuff that people do when they are in love, such as kissing and hugging.\nHaving strong feelings of happiness or satisfaction.\nFutilely pursuing something that will never be attainable."));
    return 0;

    std::string arg1, arg2;
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
        arg1 = argv[1];
        if(arg1.compare(text_cmd) && arg1.compare(file_cmd)){
            Logger::LogWarning(INVALID_COMMAND);
            return 1;
        }
        if(argc<=2){
            if(!arg1.compare(text_cmd))
                Logger::LogWarning(NO_TEXT_ARG_PASSED);
            if(!arg1.compare(file_cmd))
                Logger::LogWarning(NO_FILE_ARG_PASSED);
            return 1;
        }
        arg2 = argv[2];
        if(!arg1.compare(text_cmd)){
            Logger::Log(LogLevel::None, TEXT_OUTPUT_MESSAGE);
            Logger::Log(LogLevel::None, UwUifier::uwuify(arg2));
        }
        if(!arg1.compare(file_cmd)){
            Logger::Log(LogLevel::None, FILE_OUTPUT_MESSAGE);
            //TODO file stuff
        }
    }

    return 0;
}

