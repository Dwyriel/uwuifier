#include <iostream>
#include <string>
#include <thread>
#include <fstream>
#include <filesystem>

#include "Logger.h"
#include "UwUifier.h"

#define UWUIFIED 1

// Error/Warning/Help messages
#if UWUIFIED == 0
static std::string NO_ARG_PASSED = "No arguments passed, try -h or --help for help";
static std::string HELP_COMMAND = "?";
static std::string INVALID_COMMAND = "Invalid argument, try -h or --help for help";
static std::string NO_TEXT_ARG_PASSED = "No text passed";
static std::string NO_FILE_ARG_PASSED = "No file passed";
static std::string TEXT_OUTPUT_MESSAGE = "UwUfied text:";
static std::string FILE_OUTPUT_MESSAGE = "UwUfied file:";
static std::string FILE_DOESNT_EXIST = "File doesn't exist";
#endif
#if UWUIFIED == 1
static std::string NO_ARG_PASSED = "Nyo awguwumewnts passed, twy -h ow --hewp fow hewp";
static std::string HELP_COMMAND = "?";
static std::string INVALID_COMMAND = "Invawid awgument, twy -h ow --hewp fow hewp";
static std::string NO_TEXT_ARG_PASSED = "Nyo text passed";
static std::string NO_FILE_ARG_PASSED = "Nyo fiwe passed";
static std::string TEXT_OUTPUT_MESSAGE = "UwUfied text:";
static std::string FILE_OUTPUT_MESSAGE = "UwUfied fiwe:";
static std::string FILE_DOESNT_EXIST = "Fiwe doesn't exist";
#endif

// Arguments
const std::string help1 = "-h", help2 = "--help", help3 = "--hewp";
const std::string file_cmd = "-f", text_cmd = "-t", output_file_cmd = "-o";

static std::string EXEC_FOLDER_PATH = "";
static std::string EXECUTABLE_PATH = "";

void setProgramPaths(char* relative_path){
    /*char* pointer = realpath(relative_path, NULL);
    if(pointer == NULL)
        return false;*///leaving it here for reference or in case it may be better (pre C++17, though linux only)

    EXECUTABLE_PATH =  std::filesystem::canonical(relative_path);
    size_t pos = EXECUTABLE_PATH.find_last_of("/");
    EXEC_FOLDER_PATH = EXECUTABLE_PATH.substr(0, pos+1);
}

int main(int argc, char **argv) {//TODO rework all this garbage
    std::string firstCommand, text, secondCommand, outputFile;
    bool outputToFile = false;
    setProgramPaths(argv[0]);
    if(argc==1){
        Logger::LogWarning(NO_ARG_PASSED);
        return 1;
    }
    if(argc > 1){
        //help command
        if(help1.compare(argv[1]) == 0 || help2.compare(argv[1]) == 0 || help3.compare(argv[1]) == 0){ //TODO help command
            std::cout << "\033[38;5;252m" << "I can't hewp yowo yet, sowwy >.<" << std::endl;
            return 0;
        }
        firstCommand = argv[1];
        if(firstCommand.compare(text_cmd) && firstCommand.compare(file_cmd)){
            Logger::LogError(INVALID_COMMAND);
            return 1;
        }
        if(argc<=2){
            if(!firstCommand.compare(text_cmd))
                Logger::LogError(NO_TEXT_ARG_PASSED);
            if(!firstCommand.compare(file_cmd))
                Logger::LogError(NO_FILE_ARG_PASSED);
            return 1;
        }
        text = argv[2];
        if(argc>4){
            secondCommand = argv[3];
            outputFile = argv[4];
            if(!secondCommand.compare(output_file_cmd)){
                //TODO verify if output file is valid (if it doesn't exist already, if it can be created, etc)
                Logger::LogInfo("Outputing to file..");
                outputToFile = true;
            }
        }
        if(!firstCommand.compare(text_cmd)){
            UwUifier::uwuify(text);
            if(!outputToFile){
                Logger::Log(TEXT_OUTPUT_MESSAGE+"\n");
                Logger::Log(text);
                return 0;
            }
        }
        if(!firstCommand.compare(file_cmd)){
            std::stringstream stream;
            std::string line, filePath = "";
            std::fstream file;
            filePath.swap(text);
            if(!std::filesystem::is_regular_file(filePath)){
                Logger::LogError(FILE_DOESNT_EXIST);
                return 1;
            }
            file.open(filePath);
            while (std::getline(file, line)){
                stream << line << std::endl;
                text += stream.str();
                stream.str(std::string());
            }
            file.close();
            UwUifier::uwuifyByWord(text);
            if(!outputToFile){
                Logger::Log(FILE_OUTPUT_MESSAGE+"\n");
                Logger::Log(text);
                return 0;
            }
        }
    }
    //TODO writeToFile
    return 0;
}

