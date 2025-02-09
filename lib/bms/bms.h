#pragma once
#include <vector>
#include <stdint.h>
#include <cmath>

// possible read words from the BMS
enum READ_WORDS
{
    PACK_VOLTAGE,
    PACK_CURRENT,
    PACK_SOC,
    PACK_TEMP,
    MAX_CELL_VOLTAGE,
    MIN_CELL_VOLTAGE,
    BMS_TEMPERATURES
};

// purely virtual interface class for BMS
class BMS
{
private:
    /* data */
public:
    virtual ~BMS() = default;
    // Read the pack voltage from the BMS
    virtual float fetchCommand(READ_WORDS readWord) = 0;
    virtual std::vector<uint8_t> createReadWordCommand(READ_WORDS readWord) = 0;
    virtual float decodeBMSResponse(const std::vector<uint8_t> &response) = 0;
};
