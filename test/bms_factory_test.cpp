#include "bms_factory.h"
#include "gtest/gtest.h"
#include "tiny_bms_impl.h"

TEST(BMSFactoryTest, CreateBMSImplBasicTest)
{
    std::shared_ptr<BMS> bms = BMSFactory::createBMSImpl(BMS_IMPL_TYPES::TINY_BMS);
    EXPECT_NE(bms, nullptr);
}

/*
TEST(BMSFactoryTest, CreateBMSImplTinyBMSTest)
{
    std::shared_ptr<BMS> bms = BMSFactory::createBMSImpl(IMPL_TYPES::TINY_BMS);

    ASSERT_NE(std::dynamic_pointer_cast<TinyBMSImpl>(bms), nullptr);
}
*/