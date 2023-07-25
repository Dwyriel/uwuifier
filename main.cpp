#include <iostream>

#include "cmake_config.h"

#include "DArgumentParser.h"

constexpr const char *helpDescription() { return UWUIFIED ? "Pwints this message." : "Prints this message."; }

constexpr const char *versionDescription() { return UWUIFIED ? "Pwints the vewsion." : "Prints the version."; }

constexpr const char *inputDescription() { return UWUIFIED ? "Fiwe to be UwUified" : "File to be UwUified"; }

constexpr const char *outputDescription() { return UWUIFIED ? "Fiwe to save the output to." : "File to save the output to."; }

constexpr const char *seedDescription() { return UWUIFIED ? "Seed to be used when wandomizing." : "Seed to be used when randomizing."; }

std::tuple<> parseArgs(int argc, char **argv) {
    DArgumentOption helpOption(DArgumentOptionType::HelpOption, {'h'}, {"help", "hewp"}, helpDescription());
    DArgumentOption versionOption(DArgumentOptionType::VersionOption, {'v'}, {"version", "vewsion"}, versionDescription());
    DArgumentOption inputOption(DArgumentOptionType::InputOption, {'i'}, {"input"}, inputDescription());
    DArgumentOption outputOption(DArgumentOptionType::InputOption, {'o'}, {"output"}, outputDescription());
    DArgumentOption seedOption(DArgumentOptionType::InputOption, {'s'}, {"seed"}, seedDescription());
    DArgumentParser parser(argc, argv, PROJECT_NAME, PROJECT_VER);
    parser.AddArgumentOption({&helpOption, &versionOption, &inputOption, &outputOption, &seedOption});
    parser.Parse();
    //todo
    std::cout << parser.VersionText() << parser.HelpText();
    return std::make_tuple();
}

int main(int argc, char **argv) {
    auto w = parseArgs(argc, argv);
    std::cout << "Hewwo Wowld";
}
