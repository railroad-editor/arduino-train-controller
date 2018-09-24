#pragma once

#include "Switcher.h"
#include "PowerPack.h"
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

    PowerPack &getPowerPack(int id);

    Switcher &getSwitcher(int id);

    bool isConfigured;

private:
    int dPin;
    vector<Switcher *> switchers;
    vector<PowerPack *> powerPacks;
};
