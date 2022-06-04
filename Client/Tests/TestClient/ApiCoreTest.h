#include <gtest/gtest.h>
#include <QWidget>
#include "ApiCore/ApiCore.h"

namespace UnitTest
{
    class ApiCoreTest : public ::testing::Test , public Photon::ApiCore
    {
        Q_OBJECT
    protected:
        ApiCoreTest()
            : Photon::ApiCore()
        {
        }

        ~ApiCoreTest()
        {
        }

        void SetUp() override
        {
        }

        void TearDown() override
        {
        }
    };
}
