#include "uart_com_factory.h"

std::shared_ptr<UartComInterface> UartComFactory::createUartComImpl()
{
    static std::shared_ptr<UartComInterface> instance(new UartComImpl());
    return instance;
}