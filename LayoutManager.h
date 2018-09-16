#pragma once

#include "Turnout.h"
#include "Feeder.h"
#include <ArduinoJson.h>
#include <ArduinoSTL.h>

using namespace std;

class LayoutManager {
public:
    /**
     * Constructor
     * @param dPin 5V電源ピン。実質的にON/OFFスイッチのような働きをする
     */
    LayoutManager(int dPin);

    void configure();

    Feeder &getFeeder(int id);

    Turnout &getTurnout(int id);

    bool isConfigured;

private:
    int dPin;
    vector<Turnout *> turnouts;
    vector<Feeder *> feeders;
};
