#include <QtTest>
#include "./email-generator-master/emailGenerator/emailGeneratorProgram/functions.h"

class TestJsonData : public QObject
{
    Q_OBJECT

private slots:
    void test_validJson();
    void test_emptyJson();
    void test_invalidJson();
};

void TestJsonData::test_validJson()
{
    QFile jsonFile("data.json");
    jsonFile.open(QIODevice::WriteOnly);
    QTextStream out(&jsonFile);
    out << "{ \"name\": \"John Doe\", \"date\": \"April 15, 2024\", \"time\": \"3:00 PM\", \"sender\": \"The Office\" }";
    jsonFile.close();

    QMap<QString, QString> result = getJsonData("data.json");
    QCOMPARE(result["name"], QString("John Doe"));
    QCOMPARE(result["date"], QString("April 15, 2024"));
    QCOMPARE(result["time"], QString("3:00 PM"));
    QCOMPARE(result["sender"], QString("The Office"));
}

void TestJsonData::test_emptyJson()
{
    QFile emptyJsonFile("empty.json");
    emptyJsonFile.open(QIODevice::WriteOnly);
    emptyJsonFile.close();

    QMap<QString, QString> result = getJsonData("empty.json");
    QCOMPARE(result.size(), 0);  // Expecting an empty map
}

void TestJsonData::test_invalidJson()
{
    QFile invalidJsonFile("invalid.json");
    invalidJsonFile.open(QIODevice::WriteOnly);
    QTextStream out(&invalidJsonFile);
    out << "{ \"name\": \"John Doe\", \"date\": \"April 15, 2024\",, \"time\": \"3:00 PM\" }";  // Invalid syntax
    invalidJsonFile.close();

    QVERIFY_EXCEPTION_THROWN(getJsonData("invalid.json"), std::runtime_error);
}

QTEST_APPLESS_MAIN(TestJsonData)
#include "testjsondata.moc"
