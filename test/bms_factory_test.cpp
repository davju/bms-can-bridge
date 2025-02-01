#include "bms_factory.h"
#include "gtest/gtest.h"
#include "tiny_bms_impl.h"

TEST(BMSFactoryTest, CreateBMSImplBasicTest)
{
    BMSFactory factory;
    std::shared_ptr<BMS> bms = factory.createBMSImpl(IMPL_TYPES::TINY_BMS);
    EXPECT_NE(bms, nullptr);
}

TEST(BMSFactoryTest, CreateBMSImplTinyBMSTest)
{
    BMSFactory factory;
    std::shared_ptr<BMS> bms = factory.createBMSImpl(IMPL_TYPES::TINY_BMS);

    ASSERT_NE(std::dynamic_pointer_cast<TinyBMSImpl>(bms), nullptr);
}
