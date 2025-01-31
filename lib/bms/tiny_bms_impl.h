#pragma once
#ifndef TINY_BMS_H
#define TINY_BMS_H

#ifndef SUPPORTS_MAX_CURRENT
#define SUPPORTS_MAX_CURRENT 0
#endif // SUPPORTS_MAX_CURRENT

#include <iostream>
#include <memory>
#include <vector>
#include <cstring>
#include <algorithm>
#include "crc.h"
#include "bms.h"

class TinyBMSImpl : public BMS
{
public:
    // Delete copy constructor and assignment operator to prevent copies
    TinyBMSImpl(const TinyBMSImpl &) = delete;
    TinyBMSImpl &operator=(const TinyBMSImpl &) = delete;

    // Static method to get the singleton instance
    static std::shared_ptr<TinyBMSImpl> getInstance()
    {
        static std::shared_ptr<TinyBMSImpl> instance(new TinyBMSImpl());
        return instance;
    }

    // Public methods for TinyBMSInterface
    std::vector<uint8_t> createReadWordCommand(READ_WORDS readWord) override;

    float decodeBMSResponse(const std::vector<uint8_t> &response) override;

private:
    // Private constructor to prevent instantiation
    TinyBMSImpl() {}
    std::vector<uint8_t> addCRC(std::vector<uint8_t> &data);

    bool checkCRC(const std::vector<uint8_t> &response);

    std::vector<uint8_t> extractPayload(const std::vector<uint8_t> &response);

    float convertIEEEFloat(const std::vector<uint8_t> &data);
};

#endif // TINY_BMS_H
