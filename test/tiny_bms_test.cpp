#include "tiny_bms_impl.h"
#include "gtest/gtest.h"
#include <memory>

TEST(TinyBMSTest, CreateReadWordCommand_PackVoltage)
{
    std::shared_ptr<TinyBMSImpl> bms = TinyBMSImpl::getInstance();
    std::vector<uint8_t> command = bms->createReadWordCommand(READ_WORDS::PACK_VOLTAGE);
    const uint8_t data[] = {0xAA, 0x14};
    uint16_t crc = CRC16(data, sizeof(data) / sizeof(data[0]));
    uint8_t crc_low = crc & 0xFF;
    uint8_t crc_high = (crc >> 8) & 0xFF;
    std::vector<uint8_t> expected = {0xAA, 0x14, crc_low, crc_high};
    EXPECT_EQ(command, expected);
}

TEST(TinyBMSTest, CreateReadWordCommand_PackCurrent)
{
    std::shared_ptr<TinyBMSImpl> bms = TinyBMSImpl::getInstance();
    std::vector<uint8_t> command = bms->createReadWordCommand(READ_WORDS::PACK_CURRENT);
    const uint8_t data[] = {0xAA, 0x15};
    uint16_t crc = CRC16(data, sizeof(data) / sizeof(data[0]));
    uint8_t crc_low = crc & 0xFF;
    uint8_t crc_high = (crc >> 8) & 0xFF;
    std::vector<uint8_t> expected = {0xAA, 0x15, crc_low, crc_high};
    EXPECT_EQ(command, expected);
}

TEST(TinyBMSTest, ParseResponseFloat)
{
    std::shared_ptr<TinyBMSImpl> bms = TinyBMSImpl::getInstance();

    // Test valid response

    std::vector<uint8_t> data = {
        0xAA,
        0x1B,
        0x04,
        0x40,
        0x00,
        0x00,
        0x00,
    };
    uint16_t crc = CRC16(data.data(), data.size());
    uint8_t crc_low = crc & 0xFF;
    uint8_t crc_high = (crc >> 8) & 0xFF;
    data.push_back(crc_low);
    data.push_back(crc_high);
    EXPECT_NE(bms->decodeBMSResponse(data), 0);
    EXPECT_EQ(bms->decodeBMSResponse(data), 2.0);
}

TEST(TinyBMSTest, ParseResponseInt)
{
    std::shared_ptr<TinyBMSImpl> bms = TinyBMSImpl::getInstance();

    // Test valid response

    std::vector<uint8_t> data = {0xAA, 0x1B, 0x02, 0x00, 0x40};
    uint16_t crc = CRC16(data.data(), data.size());
    uint8_t crc_low = crc & 0xFF;
    uint8_t crc_high = (crc >> 8) & 0xFF;
    data.push_back(crc_low);
    data.push_back(crc_high);
    EXPECT_NE(bms->decodeBMSResponse(data), 0);
    EXPECT_EQ(bms->decodeBMSResponse(data), 64);
}

/*
TEST(TinyBMSTest, FetchCommandTest)
{
    std::shared_ptr<TinyBMSImpl> bms = TinyBMSImpl::getInstance();
    bms->setupComunication(9600, 8, 1, false);
    float response = bms->fetchCommand(READ_WORDS::PACK_VOLTAGE);
    EXPECT_NE(response, 0);
}
*/
