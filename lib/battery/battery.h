#pragma once
#include <memory>
#include <cassert>
#include "bms_factory.h"
#define BAT_Test 1
#ifdef BAT_Test
#include "gtest/gtest.h"
#endif

/// @brief  Adds additional functionality like maximium current calculation if not available in the BMS
class Battery
{
private:
    std::shared_ptr<BMS> bms;

    // Define the grid sizes for SoC and Temperature.
    int SOC_SIZE = 5;
    int TEMP_SIZE = 4;

    // Discrete grid points for SoC (0.0 to 1.0) and temperature (in °C)
    std::vector<double> soc_points = {0.0, 0.25, 0.5, 0.75, 1.0};
    std::vector<double> temp_points = {-10.0, 0.0, 25.0, 40.0};

    // A 2D lookup table for maximum discharge current (in amperes)
    // Each row corresponds to a SoC value, and each column to a temperature.
    std::vector<std::vector<double>> discharge_current_table = {
        {10, 12, 15, 20}, // SoC = 0.0
        {15, 17, 20, 25}, // SoC = 0.25
        {20, 22, 25, 30}, // SoC = 0.5
        {25, 27, 30, 35}, // SoC = 0.75
        {30, 32, 35, 40}  // SoC = 1.0
    };

    // Helper function to find the lower index for a given value in a sorted array
    int findLowerIndex(const std::vector<double> &arr, double value);

    // Function performing bilinear interpolation.
    double bilinearInterpolate(double soc, double temp);

public:
    ~Battery() = default;

    // builder methodes
    void setBMSType(BMS_IMPL_TYPES impl_type);
    std::shared_ptr<BMS> getBMS(void);
    float getPackVoltage(void);
    float getPackCurrent(void);
    float getPackSOC(void);
    float getPackTemp(void);
    float getMaxCellVoltage(void);
    float getMinCellVoltage(void);

    int setMaxCurrent(float SOC, float temperature);

#ifdef BAT_Test
    FRIEND_TEST(MyClassTest, InterpolateCurrentValues);
#endif
};
