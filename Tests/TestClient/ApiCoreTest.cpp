#include "ApiCore.h"

#include <QJsonObject>
#include <QJsonDocument>

using namespace Photon;

// Create a gtest fixture class
class ApiCoreTest : public ::testing::Test , public ApiCore
{
    protected:
    ApiCoreTest() 
    {
    }
};

TEST_F(ApiCoreTest, test1)
{
    QJsonObject json;
    json["Username"] = "admin";
    json["Password"] = "123456";

    QUrl relativeUrl{"/login"};

    QNetworkReply* reply = nullptr;

    QString response = post(json, relativeUrl, reply);

    EXPECT_EQ(response, "{\"Message\":\"User is not found!\"}");
}
