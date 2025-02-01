#include "uart_com_impl.h"

int UartComImpl::setupUart(uint32_t baudrate, uint8_t data_bits, uint8_t stop_bits, bool has_parity_bit)
{
    return 0;
}

void UartComImpl::send(const std::vector<uint8_t> &data)
{
}

std::vector<uint8_t> UartComImpl::receive(uint32_t timeout)
{
    return std::vector<uint8_t>();
}