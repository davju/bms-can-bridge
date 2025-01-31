#include "tiny_bms_impl.h"

std::vector<uint8_t> TinyBMSImpl::createReadWordCommand(READ_WORDS read_word)
{

    switch (read_word)
    {
    case PACK_VOLTAGE:
    {
        static std::vector<uint8_t> command = {0xAA, 0x14};
        static std::vector<uint8_t> message = addCRC(command);
        return message;
    }

    case PACK_CURRENT:
    {
        std::vector<uint8_t> command = {0xAA, 0x15};
        static std::vector<uint8_t> message = addCRC(command);
        return message;
    }

    case PACK_SOC:
    {
        std::vector<uint8_t> command = {0xAA, 0x1A};
        static std::vector<uint8_t> message = addCRC(command);
        return message;
    }

    case BMS_TEMPERATURES:
    {
        std::vector<uint8_t> command = {0xAA, 0x1B};
        static std::vector<uint8_t> message = addCRC(command);
        return message;
    }

    default:
    {
        return std::vector<uint8_t>();
    }
    }
}

std::vector<uint8_t> TinyBMSImpl::addCRC(std::vector<uint8_t> &data)
{
    uint16_t crc = CRC16(data.data(), data.size());
    uint8_t crc_low = crc & 0xFF;
    uint8_t crc_high = (crc >> 8) & 0xFF;
    data.push_back(crc_low);
    data.push_back(crc_high);
    return data;
}

// converts a uart response
float TinyBMSImpl::decodeBMSResponse(const std::vector<uint8_t> &response)
{
    if (response.size() < 3 || checkCRC(response) == false)
    {
        return 0;
    }
    std::vector<uint8_t> payload = extractPayload(response);

    if (payload.size() == 2)
    {
        // 2 byte response
        uint16_t value = (payload[0] << 8) | payload[1];

        return value;
    }
    else if (payload.size() == 4)
    {
        float value = convertIEEEFloat(payload);
        return value;
    }
    else if (payload.size() > 4)
    {
        // multiple values in one response -> currently not  supported

        return 0;
    }
    else
    {
        // other message detected -> currently not supported

        return 0;
    }
}

bool TinyBMSImpl::checkCRC(const std::vector<uint8_t> &response)
{
    if (response.size() < 3)
    {
        return false;
    }

    std::vector<uint8_t> sliced(response.begin(), response.end() - 2);

    uint16_t crc = CRC16(sliced.data(), sliced.size());

    uint8_t crc_low = crc & 0xFF;
    uint8_t crc_high = (crc >> 8) & 0xFF;

    if (crc_low == response[response.size() - 2] && crc_high == response[response.size() - 1])
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::vector<uint8_t> TinyBMSImpl::extractPayload(const std::vector<uint8_t> &response)
{
    uint8_t payload_length = response[2];

    std::vector<uint8_t> payload(response.begin() + 3, response.begin() + 3 + payload_length);

    return payload;
}

float TinyBMSImpl::convertIEEEFloat(const std::vector<uint8_t> &data)
{
    if (data.size() < 4)
    {
        return 0;
    }

    std::vector<unsigned char> data_copy = data; // Kopie erstellen
    std::reverse(data_copy.begin(), data_copy.end());

    float value;
    std::memcpy(&value, data_copy.data(), sizeof(float));
    return value;
}