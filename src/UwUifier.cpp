#include <string>
#include <vector>

namespace UwUifier {

    static std::vector<std::string> swapPairs{
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

    static std::vector<char> stutterLetters{'p', 'P', 'b', 'B'};

    static std::string trim(std::string &textToTrim) {
        const std::string whitespace = " \t";
        size_t firstCharacterPosition = textToTrim.find_first_not_of(whitespace);
        if (firstCharacterPosition == std::string::npos)
            return "";
        size_t lastCharacterPosition = textToTrim.find_last_not_of(whitespace);
        size_t lastCharacterPositionAfterTrim = lastCharacterPosition - firstCharacterPosition;
        return textToTrim.substr(firstCharacterPosition, lastCharacterPositionAfterTrim + 1);
    }

    static void swapWith(std::string &text, std::string &textToFind, std::string &textToImplement) {
        size_t pos = text.find(textToFind);
        std::string tempStr;
        while (pos != std::string::npos) {
            char buffer[pos + 1];
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

    static void uwuify(std::string &text) {
        for (int index = 0; index < swapPairs.size(); index += 2)
            swapWith(text, swapPairs[index], swapPairs[index + 1]);
    }

    static void swapWithByWord(std::vector<std::string> &words, std::string &textToFind, std::string &textToImplement) {
        for (std::string &word: words) {
            size_t pos = word.find(textToFind);
            while (pos != std::string::npos) {
                word.replace(pos, textToFind.length(), textToImplement);
                pos = word.find(textToFind);
            }
        }
    }

    static void addStutterByWord(std::vector<std::string> &words, const float &stutterFrequency) {
        float counter = 0;
        for (std::string &word: words) {
            if (word == "\n")
                continue;
            for (auto i = stutterLetters.begin(); i != stutterLetters.end(); i++) {
                if ((*i) != word[0])
                    continue;
                counter += stutterFrequency;
                if (counter >= 1) {
                    counter -= 1;
                    char buffer[] = {'1', '\0'};
                    std::string stringToImplement;
                    buffer[0] = *i;
                    stringToImplement.append(buffer);
                    stringToImplement.append("-");
                    buffer[0] = tolower(*i);
                    stringToImplement.append(buffer);
                    word.replace(0, 1, stringToImplement);
                }
            }
        }
    }

    static void addUwUByWord(std::vector<std::string> &words, const float &uwuFrequency) {
        float counter = 0;
        std::string foundText;
        for (std::string &word: words) {
            if (word == "\n")
                continue;
            std::vector<size_t> positions;
            size_t pos = 0;
            while (true) {
                size_t previousPos = pos;
                pos = word.find('\n', pos + 1);
                if (pos == std::string::npos)
                    break;
                if (pos != previousPos + 1)
                    positions.push_back(pos);
            }
            size_t offset = 0;
            for (long i = 0; i < positions.size(); i++) {
                counter += uwuFrequency;
                if (counter >= 1) {
                    counter -= 1;
                    word.replace(positions[i] + offset, 1, " UwU\n");
                    offset += 4;
                }
            }
        }
    }

    static void uwuifyByWord(std::string &text, const float &stutterFrequency, const float &uwuFrequency) {
        const std::string space = " ";
        const std::string linebreak = "\n";
        std::vector<std::string> words;
        text = trim(text);
        size_t firstSpacePos = text.find(space);
        size_t firstNonSpacePos = text.find_first_not_of(space);
        while (firstNonSpacePos != std::string::npos) {
            size_t positionToCopyAndDelete = (firstSpacePos == std::string::npos) ? std::string::npos : firstSpacePos +
                                                                                                        1;
            std::string buffer = text.substr(firstNonSpacePos, positionToCopyAndDelete);
            text.erase(0, positionToCopyAndDelete);
            size_t linebreakPos = buffer.find_first_of(linebreak);
            while (linebreakPos != std::string::npos) {
                std::string buffer2 = buffer.substr(0, linebreakPos + 1);
                buffer.erase(0, linebreakPos + 1);
                if (!buffer2.empty())
                    words.push_back(buffer2);
                linebreakPos = buffer.find_first_of(linebreak);
            }
            if (!buffer.empty())
                words.push_back(buffer);
            text = trim(text);
            firstSpacePos = text.find(space);
            firstNonSpacePos = text.find_first_not_of(space);
        }
        for (int index = 0; index < swapPairs.size(); index += 2)
            swapWithByWord(std::ref(words), swapPairs[index], swapPairs[index + 1]);
        addStutterByWord(std::ref(words), stutterFrequency);
        addUwUByWord(std::ref(words), uwuFrequency);
        for (std::string &word: words) {
            text += word;
        }
        while (text[text.size() - 1] == '\n')
            text.pop_back();
    }
}
