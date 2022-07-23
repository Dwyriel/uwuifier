#include <iostream>
#include <sstream>

const std::string RED = "\033[38;5;196m", ORANGE = "\033[38;5;220m", WHITE = "\033[38;5;252m", RESET = "\033[0m"; //I really hate this console BS, seriously
const std::string ERROR_LOG_PREFIX = "[ ERROR ] ", WARNING_LOG_PREFIX = "[WARNING] ", INFO_LOG_PREFIX = "[  LOG  ] ", NONE_PREFIX = "";

enum LogLevel : char {None, ErrorLog, WarningLog, InfoLog};

class Logger
{
    Logger() = delete;

    template <typename T>
    static void WriteToConsole(const std::string& color, const std::string& prefix, T const& log_text){
        std::cout << color << prefix << log_text << RESET << std::endl;
    }

    template <typename T>//useless, leaving as reference
    static std::string ConvertToString(const T& t){
        std::stringstream strStream;
        strStream << std::fixed << t;
        return strStream.str();
    }

public:

    template <typename T>
    static void Log(T const& log_text, const char& level = LogLevel::None, const bool& writeToFile = false){
        std::string prefix, color;
        switch (level){
            case None:
                color = WHITE;
                prefix = NONE_PREFIX;
                break;
            case ErrorLog:
                color = RED;
                prefix = ERROR_LOG_PREFIX;
                break;
            case WarningLog:
                color = ORANGE;
                prefix = WARNING_LOG_PREFIX;
                break;
            case InfoLog:
                color = WHITE;
                prefix = INFO_LOG_PREFIX;
                break;
            default:
                return;
        }
        WriteToConsole(color, prefix, log_text);
        if(!writeToFile)
            return;
            //todo writing to a file;
    }

    template <typename T>
    static void LogNone(T const& log_text, const bool& writeToFile = false){
        Logger::Log(log_text, LogLevel::None, writeToFile);
    }

    template <typename T>
    static void LogError(T const& log_text, const bool& writeToFile = false){
        Logger::Log(log_text, LogLevel::ErrorLog, writeToFile);
    }

    template <typename T>
    static void LogWarning(T const& log_text, const bool& writeToFile = false){
        Logger::Log(log_text, LogLevel::WarningLog, writeToFile);
    }

    template <typename T>
    static void LogInfo(T const& log_text, const bool& writeToFile = false){
        Logger::Log(log_text, LogLevel::InfoLog, writeToFile);
    }
};
