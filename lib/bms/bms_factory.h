#pragma once
#include <memory>
#include "bms.h"
#include "tiny_bms_impl.h"
#include "bms_impl_types.h"
class BMSFactory
{
private:
    /* data */
public:
    static std::shared_ptr<BMS> createBMSImpl(BMS_IMPL_TYPES impl_type)
    {
        switch (impl_type)
        {
        case BMS_IMPL_TYPES::TINY_BMS:
            return TinyBMSImpl::getInstance();
        default:
            return nullptr;
        }
    }
};
