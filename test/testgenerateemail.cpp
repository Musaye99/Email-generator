#include <QtTest>
#include "../emailGeneratorProgram/functions.h"

class TestGenerateEmail : public QObject
{
    Q_OBJECT

private slots:
    void test_correctTemplate();
    void test_emptyTemplate();
};

void TestGenerateEmail::test_correctTemplate()
{
    // Test Case: Correct template and data
    QStringList templateList = { "Dear #name#,", "Your appointment is on #date#." };
    QStringList dataList = { "name John Doe", "date April 15, 2024" };  // Data in the form expected by generateEmail

    // Call generateEmail
    QStringList result = generateEmail(templateList, dataList);

    // Verify the content of the generated email
    QCOMPARE(result[0], QString("Dear John Doe,"));
    QCOMPARE(result[1], QString("Your appointment is on April 15, 2024."));
}

void TestGenerateEmail::test_emptyTemplate()
{
    // Test Case: Empty template
    QStringList templateList;  // Empty QStringList
    QStringList dataList = { "name John Doe", "date April 15, 2024" };

    // Call generateEmail
    QStringList result = generateEmail(templateList, dataList);

    // The result should also be empty
    QCOMPARE(result.size(), 0);
}

QTEST_APPLESS_MAIN(TestGenerateEmail)
#include "testgenerateemail.moc"
