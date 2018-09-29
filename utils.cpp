#include "utils.h"

std::vector<String> split(String data, char delimiter, int maxSize) {
    unsigned int beginIndex = 0;
    unsigned int dataLength = data.length();
    std::vector<String> result;
    for (unsigned int i = 0; i < dataLength; i++) {
        char tmp = data.charAt(i);
        if (tmp == delimiter) {
            if (result.size() >= maxSize) {
                return result;
            }
            String token = data.substring(beginIndex, i);
            token.trim();
            result.push_back(token);
            beginIndex = i + 1;
        }
    }
    String token = data.substring(beginIndex);
    token.trim();
    result.push_back(token);
    return result;
}