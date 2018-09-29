#pragma once

#include <ArduinoSTL.h>
#include <vector>


#define SIZE_OF_ARRAY(ary)  (sizeof(ary)/sizeof((ary)[0]))

/**
 * 入力した文字列を区切り文字で分割する
 * @param result     分割された文字列を格納する配列
 * @param resultsize 配列の要素数
 * @param data       区切り文字を含む文字列のアドレス
 * @param delimiter  区切り文字
 * @return 成功で配列の要素数，要素数不足の場合は-1
 */
std::vector<String> split(String data, char delimiter, int maxSize);
