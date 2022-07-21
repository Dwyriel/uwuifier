#include <string>
#include <vector>
#include "Logger.h"

namespace UwUifier{

    static std::vector<std::string> swapPairs {
        "Na", "Nya",
        "na", "nya",
        "No", "Nyo",
        "no", "nyo",
        "r", "w",
        "R", "W",
        "l", "w",
        "L", "W"
    };

    static std::string swapWith(std::string text, std::string textToFind, std::string textToImplement){
        size_t pos = text.find(textToFind);
        std::string tempStr = "";
        while(pos != std::string::npos){
            char buffer[pos+1];
            text.copy(buffer, pos);
            buffer[pos] = '\0';
            text.erase(0, pos);
            text.erase(0, textToFind.length());
            tempStr.append(buffer);
            tempStr.append(textToImplement);
            pos = text.find(textToFind);
        }
        tempStr.append(text);
        return tempStr;
    }

    static std::string uwuify(std::string text){
        std::string retStr = text;
        for(int index = 0; index < swapPairs.size(); index+=2)
            retStr = swapWith(retStr, swapPairs[index], swapPairs[index+1]);
        return retStr;
    }

}
