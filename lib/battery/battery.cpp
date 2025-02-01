#include "battery.h"

Battery::Battery(std::shared_ptr<BMS> bms_type) : bms(bms_type) {}

float Battery::getPackVoltage()
{
    std::vector<uint8_t> command = bms->createReadWordCommand(READ_WORDS::PACK_VOLTAGE);
    com->send(command);
    std::vector<uint8_t> response = com->receive(1000);
    return bms->decodeBMSResponse(response);
}
