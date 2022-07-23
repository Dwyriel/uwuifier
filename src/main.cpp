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
#define INVALID_COMMAND(str) ("Invalid argument " + '"' + str + '"' + ". try -h or --help for help")
#define NO_ARG_PASSED "No arguments passed, try -h or --help for help"
#define HELP_COMMAND "I can't help you yet, sorry :("
#define NO_TEXT_ARG_PASSED "No text passed"
#define NO_FILE_ARG_PASSED "No file passed"
#define NO_OUTPUT_FILE_ARG_PASSED "No output file passed"
#define FILE_DOESNT_EXIST "Input file doesn't exist"
#define TEXT_OR_FILE_ARGS_NOT_PASSED "Neither \"-t\" or \"-f\" arguments passed"
#define TEXT_AND_FILE_ARGS_PASSED "Both \"-t\" and \"-f\" arguments passed"
#define TEXT_OUTPUT_MESSAGE "UwUfied text:"
#define FILE_OUTPUT_MESSAGE "UwUfied file:"
#define FILE_ALREADY_EXIST "Output file already exist, pass --force to overwrite it"
#define EXPORTED_TO_FILE(str) ("Exported to " + str)
#endif
#if UWUIFIED == 1
#define INVALID_COMMAND(str) ("Invawid awgument \"" + str + "\". twy -h ow --hewp fow hewp")
#define NO_ARG_PASSED "Nyo awguments passed, twy -h ow --hewp fow hewp"
#define HELP_COMMAND "I can't hewp yowo yet, sowwy >.<"
#define NO_TEXT_ARG_PASSED "Nyo text passed"
#define NO_FILE_ARG_PASSED "Nyo fiwe passed"
#define NO_OUTPUT_FILE_ARG_PASSED "Nyo output fiwe passed"
#define FILE_DOESNT_EXIST "Input fiwe doesn't exist"
#define TEXT_OR_FILE_ARGS_NOT_PASSED "Neithew \"-t\" or \"-f\" awguments passed"
#define TEXT_AND_FILE_ARGS_PASSED "Both \"-t\" and \"-f\" awguments passed"
#define TEXT_OUTPUT_MESSAGE "UwUfied text:"
#define FILE_OUTPUT_MESSAGE "UwUfied fiwe:"
#define FILE_ALREADY_EXIST "Output fiwe aw-weady exist, pass --fowce to ovew-wwite it"
#define EXPORTED_TO_FILE(str) ("Expowted to " + str)
#endif

// Arguments
#define HELP_CMD1 "-h"
#define HELP_CMD2 "--help"
#define HELP_CMD3 "--hewp"
#define TEXT_CMD1 "-t"
#define TEXT_CMD2 "--text"
#define FILE_CMD1 "-f"
#define FILE_CMD2 "--file"
#define FILE_CMD3 "--fiwe"
#define OUTPUT_FILE_CMD1 "-o"
#define OUTPUT_FILE_CMD2 "--output"
#define FORCE_FILE_WRITE1 "--force"
#define FORCE_FILE_WRITE2 "--fowce"
#define CMD_COUNT 12
const char* ALL_CMDS[CMD_COUNT] = {HELP_CMD1, HELP_CMD2, HELP_CMD3, TEXT_CMD1, TEXT_CMD2, FILE_CMD1, FILE_CMD2, FILE_CMD3, OUTPUT_FILE_CMD1, OUTPUT_FILE_CMD2, FORCE_FILE_WRITE1, FORCE_FILE_WRITE2};

static std::string EXEC_FOLDER_PATH;
static std::string EXECUTABLE_PATH;

void setProgramPaths(char* relative_path){
    /*char* pointer = realpath(relative_path, NULL);
    if(pointer == NULL)
        return false;*///leaving it here for reference or in case it may be better (pre C++17, though linux only)

    EXECUTABLE_PATH =  std::filesystem::canonical(relative_path);
    size_t pos = EXECUTABLE_PATH.find_last_of("/");
    EXEC_FOLDER_PATH = EXECUTABLE_PATH.substr(0, pos+1);
}

bool checkIfTextIsCommand(std::string str){
    for(int i = 0; i < CMD_COUNT; i++){
        if(str.compare(ALL_CMDS[i]) == 0)
            return true;
    }
    return false;
}

int main(int argc, char **argv) {
    if(argc <= 1){
        Logger::LogWarning(NO_ARG_PASSED);
        return 1;
    }
    std::vector<std::string> args;
    for (int index = 1; index < argc; index ++)
        args.push_back(argv[index]);
    bool fromText = false, fromFile = false, writeToFile = false, forceWriteToFile = false;
    std::string text, inputFile, outputFile;
    for(int index = 0; index < args.size(); index++){
        if(!checkIfTextIsCommand(args[index])){
            Logger::LogError(INVALID_COMMAND(args[index]));
            return 1;
        }
        if(args[index].compare(HELP_CMD1) == 0 || args[index].compare(HELP_CMD2) == 0 || args[index].compare(HELP_CMD3) == 0){
            Logger::LogNone(HELP_COMMAND);
            return 0;
        }
        if(args[index].compare(TEXT_CMD1) == 0 || args[index].compare(TEXT_CMD2) == 0){
            if(++index >= args.size()){
                Logger::LogError(NO_TEXT_ARG_PASSED);
                return 1;
            }
            fromText = true;
            text = args[index];
            if(checkIfTextIsCommand(text)){
                Logger::LogError(NO_TEXT_ARG_PASSED);
                return 1;
            }
        }
        if(args[index].compare(FILE_CMD1) == 0 || args[index].compare(FILE_CMD2) == 0 || args[index].compare(FILE_CMD3) == 0){
            if(++index >= args.size()){
                Logger::LogError(NO_FILE_ARG_PASSED);
                return 1;
            }
            fromFile = true;
            inputFile = args[index];
            if(checkIfTextIsCommand(inputFile)){
                Logger::LogError(NO_FILE_ARG_PASSED);
                return 1;
            }
            if(!std::filesystem::is_regular_file(inputFile)){
                Logger::LogError(FILE_DOESNT_EXIST);
                return 1;
            }
        }
        if(args[index].compare(OUTPUT_FILE_CMD1) == 0 || args[index].compare(OUTPUT_FILE_CMD2) == 0){
            if(++index >= args.size()){
                Logger::LogError(NO_OUTPUT_FILE_ARG_PASSED);
                return 1;
            }
            writeToFile = true;
            outputFile = args[index];
            if(checkIfTextIsCommand(outputFile)){
                Logger::LogError(NO_OUTPUT_FILE_ARG_PASSED);
                return 1;
            }
            //TODO verify if name is valid
        }
        if(args[index].compare(FORCE_FILE_WRITE1) == 0 || args[index].compare(FORCE_FILE_WRITE2) == 0)
            forceWriteToFile = true;
    }
    if(!fromText && !fromFile){
        Logger::LogError(TEXT_OR_FILE_ARGS_NOT_PASSED);
        return 1;
    }
    if(fromText && fromFile){
        Logger::LogError(TEXT_AND_FILE_ARGS_PASSED);
        return 1;
    }
    if(writeToFile && !forceWriteToFile){
        if(std::filesystem::exists(outputFile)){
            Logger::LogError(FILE_ALREADY_EXIST);
            return 1;
        }
    }
    if(fromText)
        UwUifier::uwuify(text);
    if(fromFile){
        std::stringstream stream;
        std::string line;
        std::fstream file;
        file.open(inputFile, std::ios::in);
        while (std::getline(file, line)){
            stream << line << std::endl;
            text += stream.str();
            stream.str(std::string());
        }
        file.close();
        UwUifier::uwuifyByWord(text);
    }
    if(writeToFile){
        std::fstream file;
        file.open(outputFile, std::ios::out | std::ios::trunc);
        file << text;
        file.close();
        Logger::LogInfo(EXPORTED_TO_FILE(outputFile));
        return 0;
    }
    Logger::Log((fromText) ? TEXT_OUTPUT_MESSAGE : FILE_OUTPUT_MESSAGE);
    Logger::Log("");
    Logger::Log(text);
    return 0;
}

