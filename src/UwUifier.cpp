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

    static void swapWith(std::string &text, std::string &textToFind, std::string &textToImplement){
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
        text.swap(tempStr);
    }
    static void swapWithByWord(std::vector<std::string> &words, std::string &textToFind, std::string &textToImplement){
        for(std::string &word : words){
            size_t pos = word.find(textToFind);
            while(pos != std::string::npos){
                word.replace(pos, textToFind.length(), textToImplement);
                pos = word.find(textToFind);
            }
        }
    }

    static void uwuify(std::string &text){
        for(int index = 0; index < swapPairs.size(); index+=2)
            swapWith(text, swapPairs[index], swapPairs[index+1]);
    }

    static void uwuifyByWord(std::string &text){
        const std::string space = " ";
        std::vector<std::string> words;
        size_t pos = text.find(space);
        while(pos != std::string::npos){
            char buffer[pos+1];
            text.copy(buffer, pos);
            buffer[pos] = '\0';
            text.erase(0, pos+1);
            words.push_back(buffer);
            pos = text.find(space);
        }
        words.push_back(text);
        text.clear();
        for(int index = 0; index < swapPairs.size(); index+=2)
            swapWithByWord(std::ref(words), swapPairs[index], swapPairs[index+1]);
        for(std::string word : words){
            text += word + space;
        }
        text.pop_back();
    }

}
