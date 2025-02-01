#pragma once

#include "uart_com_interface.h"

class UartComImpl : public UartComInterface
{
private:
    /* data */
public:
    int setupUart(uint32_t baudrate, uint8_t data_bits, uint8_t stop_bits, bool has_parity_bit) override;
    void send(const std::vector<uint8_t> &data) override;
    std::vector<uint8_t> receive(uint32_t timeout) override;
};
