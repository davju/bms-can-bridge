#pragma once
#include <memory>
#include "tiny_bms_impl.h"

/// @brief  Adds additional functionality like maximium current calculation if not available in the BMS
class Battery
{
private:
    std::shared_ptr<BMS> bms;

public:
    Battery(std::shared_ptr<BMS> bms_type);
    ~Battery();

    float getPackVoltage(void);
    float getPackCurrent(void);
    float getPackSOC(void);
    float getPackTemp(void);
    float getMaxCellVoltage(void);
    float getMinCellVoltage(void);
};
