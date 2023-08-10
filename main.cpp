#include <iostream>

#include "cmake_config.h"

#include "DArgumentParser.h"

#if UWUIFIED
const char *helpDescription = "Pwints this message.";
const char *versionDescription = "Pwints the vewsion.";
const char *inputDescription = "Fiwe to be UwUified. No need to pass [text] if set.";
const char *outputDescription = "Fiwe to save the output to.";
const char *seedDescription = "Seed to be used when wandomizing.";
#else
const char *helpDescription = "Prints this message.";
const char *versionDescription = "Prints the version.";
const char *inputDescription = "File to be UwUified. No need to pass [text] if set.";
const char *outputDescription = "File to save the output to.";
const char *seedDescription = "Seed to be used when randomizing.";
#endif

auto parseArgs(int argc, char **argv) {
    DArgumentOption helpOption(DArgumentOptionType::HelpOption, {'h'}, {"help", "hewp"}, helpDescription);
    DArgumentOption versionOption(DArgumentOptionType::VersionOption, {'v'}, {"version", "vewsion"}, versionDescription);
    DArgumentOption inputOption(DArgumentOptionType::InputOption, {'i', 'f'}, {"input", "file", "fiwe"}, inputDescription);
    DArgumentOption outputOption(DArgumentOptionType::InputOption, {'o'}, {"output"}, outputDescription);
    DArgumentOption seedOption(DArgumentOptionType::InputOption, {'s'}, {"seed"}, seedDescription);
    DArgumentParser parser(argc, argv, PROJECT_NAME, PROJECT_VER);
    parser.AddArgumentOption({&helpOption, &versionOption, &inputOption, &outputOption, &seedOption});
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
    //todo check if outputFile name is valid and creatable.
    if (seedOption.WasSet()) {
        //todo parse seed
    }
    if (!inputOption.WasSet() && parser.GetPositionalArguments().empty()) {
        std::cout << "No text or file passed, nothing to do.\n\n" << parser.HelpText();
        exit(EXIT_SUCCESS);
    }
    if (inputOption.WasSet() && !parser.GetPositionalArguments().empty()) {
        std::cout << "Both a file and some text were passed at the same time.\n\n" << parser.HelpText();
        exit(EXIT_FAILURE);
    }
    std::string textToUwUify;
    if (!inputOption.WasSet()) {
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
    } else {
        //todo check file, read from it and put in textToUwUify.
    }
    return std::make_tuple();
}

int main(int argc, char **argv) {
    auto w = parseArgs(argc, argv);
    std::cout << "Hewwo Wowld";
}
