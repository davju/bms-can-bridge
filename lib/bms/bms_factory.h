#include <memory>
#include "bms.h"
#include "tiny_bms_impl.h"
#include "impl_types.h"
class BMSFactory
{
private:
    /* data */
public:
    std::shared_ptr<BMS> createBMSImpl(IMPL_TYPES impl_type)
    {
        switch (impl_type)
        {
        case IMPL_TYPES::TINY_BMS:
            return TinyBMSImpl::getInstance();
        default:
            break;
        }
    }
};
