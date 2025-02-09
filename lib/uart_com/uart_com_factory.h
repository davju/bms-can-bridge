#pragma once
#include "uart_com_impl.h"
#include <memory>

class UartComFactory
{
private:
public:
    static std::shared_ptr<UartComInterface> createUartComImpl();
};
