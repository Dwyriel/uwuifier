#include <string>
#include <vector>

namespace UwUifier{

    static std::string trim(std::string &textToTrim){
        const std::string whitespace = " \t";
        size_t firstCharacterPosition = textToTrim.find_first_not_of(whitespace);
        if(firstCharacterPosition == std::string::npos)
            return "";
        size_t lastCharacterPosition = textToTrim.find_last_not_of(whitespace);
        size_t lastCharacterPositionAfterTrim = lastCharacterPosition - firstCharacterPosition;
        return textToTrim.substr(firstCharacterPosition, lastCharacterPositionAfterTrim + 1);
    }

    static std::vector<std::string> swapPairs {
        "Na", "Nya",
        "na", "nya",
        "No", "Nyo",
        "no", "nyo",
        "Ma", "Mya",
        "ma", "mya",
        "r", "w",
        "R", "W",
        "l", "w",
        "L", "W"
    };

    static std::vector<std::string> stutterLetters {" p", " P", " b", " B" , "\np", "\nP", "\nb", "\nB"};

    static void swapWith(std::string &text, std::string &textToFind, std::string &textToImplement){
        size_t pos = text.find(textToFind);
        std::string tempStr;
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

    static void uwuify(std::string &text){
        for(int index = 0; index < swapPairs.size(); index+=2)
            swapWith(text, swapPairs[index], swapPairs[index+1]);
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

    static void addStutterByWord(std::vector<std::string> &words, const float &stutterFrequency){
        float counter = 0;
        for(std::string &word : words){
            for(std::vector<std::string>::iterator i = stutterLetters.begin(); i < stutterLetters.end(); i++) {
                size_t pos = word.find(*i);
                if(pos != std::string::npos){
                    counter += stutterFrequency;
                    if(counter >= 1){
                        counter -= 1;
                        char firstChar = (*i)[0];
                        char secondChar = (*i)[1];
                        std::string stringToImplement = firstChar + secondChar + "-" + tolower(secondChar);
                        word.replace(pos, (*i).length(), stringToImplement);
                    }
                }
            }
        }
    }

    static void addUwUByWord(std::vector<std::string> &words, const float &uwuFrequency){
        float counter = 0;
        std::string foundText;
        for(std::string &word : words){
            std::string tempWord = trim(word);
            if(tempWord.empty() || tempWord == "\n")
                continue;
            std::vector<size_t> positions;
            size_t pos = 0;
            while(true){
                size_t previousPos = pos;
                pos = word.find('\n', pos+1);
                if(pos == std::string::npos)
                    break;
                if(pos != previousPos + 1)
                    positions.push_back(pos);
            }
            size_t offset = 0;
            for(long i = 0; i < positions.size(); i++){
                counter += uwuFrequency;
                if(counter >= 1){
                    counter -= 1;
                    word.replace(positions[i] + offset, 1, " UwU\n");
                    offset += 4;
                }
            }
        }
    }

    static void uwuifyByWord(std::string &text, const float &stutterFrequency, const float &uwuFrequency){
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
        //addStutterByWord(std::ref(words), stutterFrequency);
        addUwUByWord(std::ref(words), uwuFrequency);
        for(std::string& word : words){
            text += word + space;
        }
        text.pop_back();
        while(text[text.size()-1] == '\n')
            text.pop_back();
    }

}
