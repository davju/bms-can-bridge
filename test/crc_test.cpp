#include "crc.h"
#include "gtest/gtest.h"

TEST(CRC16, TestCRC16)
{
    const uint8_t data[] = {0xAA, 0x1B};
    const uint16_t length = sizeof(data) / sizeof(data[0]);
    const uint16_t expected = 0x1B3F;
    const uint16_t actual = CRC16(data, length);
    EXPECT_EQ(expected, actual);
}

// Main function for Google Test
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();

    return 0;
}