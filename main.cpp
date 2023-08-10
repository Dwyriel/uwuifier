#include <iostream>
#include <filesystem>
#include <fstream>

#include "cmake_config.h"

#include "DArgumentParser.h"

#if UWUIFIED
const char *helpDescription = "Pwints this message.";
const char *versionDescription = "Pwints the vewsion.";
const char *inputDescription = "Fiwe to be UwUified. No need to pass [text] if set.";
const char *outputDescription = "Fiwe to save the output to.";
const char *seedDescription = "Seed to be used when wandomizing.";
const char *forceOutputDescription = "Fowces output fiwe to be ovew-wwitten if it aw-weady exists.";
#else
const char *helpDescription = "Prints this message.";
const char *versionDescription = "Prints the version.";
const char *inputDescription = "File to be UwUified. No need to pass [text] if set.";
const char *outputDescription = "File to save the output to.";
const char *seedDescription = "Seed to be used when randomizing.";
const char *forceOutputDescription = "Forces output file to be overwritten if it already exists.";
#endif

#include <cstring>

auto parseArgs(int argc, char **argv) {
    auto fileError = [](const std::filesystem::path &path, const char *message) {
        std::cout << path << ' ' << message << '\n';
        exit(EXIT_FAILURE);
    };
    DArgumentOption helpOption(DArgumentOptionType::HelpOption, {'h'}, {"help", "hewp"}, helpDescription);
    DArgumentOption versionOption(DArgumentOptionType::VersionOption, {'v'}, {"version", "vewsion"}, versionDescription);
    DArgumentOption inputOption(DArgumentOptionType::InputOption, {'i'}, {"input"}, inputDescription);
    DArgumentOption outputOption(DArgumentOptionType::InputOption, {'o'}, {"output"}, outputDescription);
    DArgumentOption forceOutputOption(DArgumentOptionType::NormalOption, {'f'}, {"force", "fowce"}, forceOutputDescription);
    DArgumentOption seedOption(DArgumentOptionType::InputOption, {'s'}, {"seed"}, seedDescription);
    DArgumentParser parser(argc, argv, PROJECT_NAME, PROJECT_VER);
    parser.AddArgumentOption({&helpOption, &versionOption, &inputOption, &outputOption, &forceOutputOption, &seedOption});
    parser.AddPositionalArgument("text", "Text(s) to be uwuified", "[text...]");
    auto result = parser.Parse();
    if (result != DParseResult::ParseSuccessful) {
        std::cout << parser.ErrorText() << "\n\n" << parser.HelpText();
        exit(EXIT_FAILURE);
    }
    if (helpOption.WasSet() || versionOption.WasSet()) {
        if (versionOption.WasSet())
            std::cout << parser.VersionText();
        if (helpOption.WasSet())
            std::cout << parser.HelpText();
        exit(EXIT_SUCCESS);
    }
    std::string outputFile = outputOption.GetValue();
    if (outputOption.WasSet()) {
        std::filesystem::path outputFilePath(outputFile);
        if (std::filesystem::exists(outputFilePath)) {
            if (!std::filesystem::is_regular_file(outputFilePath))
                fileError(outputFilePath, "already exists but is not a file");
            if (!forceOutputOption.WasSet())
                fileError(outputFilePath, "already exists, use the \"force\" option if you wish to overwrite the file");
        } else {
            std::ofstream outputFileStream(outputFilePath);
            if (outputFileStream.fail()) {
                switch (errno) {
                    case EACCES:
                        fileError(outputFilePath, "is not writable, permission denied");
                        break;
                    default:
                        fileError(outputFilePath, "is not a valid file name");
                        break;
                }
            }
            outputFileStream.close();
            std::filesystem::remove(outputFilePath);
        }
    }
    if (seedOption.WasSet()) {
        //todo parse seed
    }
    if (!inputOption.WasSet() && parser.GetPositionalArguments().empty()) {
        std::cout << "No text or file passed, nothing to do\n\n" << parser.HelpText();
        exit(EXIT_SUCCESS);
    }
    if (inputOption.WasSet() && !parser.GetPositionalArguments().empty()) {
        std::cout << "Both a file and plain text were passed at the same time\n\n" << parser.HelpText();
        exit(EXIT_FAILURE);
    }
    std::string textToUwUify;
    if (inputOption.WasSet()) {
        std::filesystem::path inputFile(inputOption.GetValue());
        if (!std::filesystem::exists(inputFile))
            fileError(inputFile, "does not exist");
        if (!std::filesystem::is_regular_file(inputFile))
            fileError(inputFile, "is not a file");
        size_t fileSize = std::filesystem::file_size(inputFile);
        textToUwUify.resize(fileSize);
        std::ifstream fileStream(inputFile);
        fileStream.seekg(0);
        fileStream.read(&textToUwUify[0], fileSize);
        fileStream.close();
    } else {
        size_t argCount = parser.GetPositionalArguments().size();
        size_t reserveAmount = (argCount - 1) * 2; //for adding double newlines between texts.
        for (const auto &arg: parser.GetPositionalArguments())
            reserveAmount += arg.size();
        textToUwUify.reserve(reserveAmount);
        for (size_t i = 0; i < argCount; ++i) {
            textToUwUify += parser.GetPositionalArguments()[i];
            if (argCount > 1 && (i + 1) % argCount != 0)
                textToUwUify += "\n\n";
        }
    }
    return std::make_tuple(textToUwUify, (int) 0 /*temp seed*/, outputFile);
}

int main(int argc, char **argv) {
    auto w = parseArgs(argc, argv);
}
