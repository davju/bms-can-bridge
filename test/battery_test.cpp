#include "battery.h"
#include "gtest/gtest.h"
#define BAT_Test 1

TEST(BatteryTest, CreateBattery)
{
    Battery myBattery;
    myBattery.setBMSType(BMS_IMPL_TYPES::TINY_BMS);
    auto bms = myBattery.getBMS();

    ASSERT_NE(std::dynamic_pointer_cast<TinyBMSImpl>(bms), nullptr);
}

/*
TEST(BatteryTest, InterpolateCurrentValues)
{
    Battery myBattery;

    double value = myBattery.bilinearInterpolate(0.5, 25.0);
}

*/
