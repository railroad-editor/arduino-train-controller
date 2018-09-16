#include "utils.h"

int split(String *result, size_t resultsize, String data, char delimiter) {
    int index = 0;
    int datalength = data.length();
    for (int i = 0; i < datalength; i++) {
        char tmp = data.charAt(i);
        if (tmp == delimiter) {
            result[index].trim();
            index++;
            if (index > (resultsize - 1)) return -1;
        } else result[index] += tmp;
    }
    result[index].trim();
    return (index + 1);
}