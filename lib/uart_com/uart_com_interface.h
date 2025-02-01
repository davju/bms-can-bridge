#pragma once
#include <vector>
#include <stdint.h>

class UartComInterface
{
private:
    /* data */
public:
    ~UartComInterface() = default;

    virtual int setupUart(uint32_t baudrate, uint8_t data_bits, uint8_t stop_bits, bool has_parity_bit) = 0;
    virtual void send(const std::vector<uint8_t> &data) = 0;

    virtual std::vector<uint8_t> receive(uint32_t timeout) = 0;
};