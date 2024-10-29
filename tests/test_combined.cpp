/**
 * @file testcombine.cpp
 * @brief Unit tests for the Email Generator program.
 *
 * This file contains extended unit tests for testing the functionality of the email generation
 * process, including handling larger texts and multiple placeholders.
 */

#include <QtTest>
#include "../src/functions.h"
#include <QFile>
#include <QTextStream>

/**
 * @brief Test class for email generator tests.
 *
 * This class contains unit tests for verifying the behavior of the email generator functions.
 * Extended tests include large texts, more placeholders, and complex data handling.
 */
class TestCombined : public QObject
{
    Q_OBJECT

private slots:
    // Tests
    void test_validFilePath();
    void test_emptyContent();
    void test_correctTemplate();
    void test_missingPlaceholders();
    void test_emptyTemplate();
    void test_escapeSequences();
    void test_largeTextWithMultiplePlaceholders();
    void test_repeatedPlaceholders();
    void test_specialCharactersInTemplate();
    void test_incompleteData();
};

// Implementation of writeOutput tests
void TestCombined::test_validFilePath()
{
    QStringList content = { "Dear John Doe,", "Your appointment is on April 15, 2024." };
    QString filePath = "output_email.txt";
    writeOutput(filePath, content);

    QFile outputFile(filePath);
    QVERIFY(outputFile.open(QIODevice::ReadOnly | QIODevice::Text));
    QTextStream in(&outputFile);
    QString fileContent = in.readAll();

    QString expectedContent = "Dear John Doe,\nYour appointment is on April 15, 2024.\n";
    QCOMPARE(fileContent, expectedContent);

    outputFile.close();
}

void TestCombined::test_emptyContent()
{
    QStringList emptyContent;
    QString filePath = "empty_output.txt";
    writeOutput(filePath, emptyContent);

    QFile outputFile(filePath);
    QVERIFY(outputFile.open(QIODevice::ReadOnly | QIODevice::Text));
    QCOMPARE(outputFile.size(), qint64(0));  // File size should be 0

    outputFile.close();
}

// Implementation of generateEmail tests
void TestCombined::test_correctTemplate()
{
    QStringList templateList = { "Dear #name#,", "Your appointment is on #date#." };
    QStringList dataList = { "name: John Doe", "date: April 15, 2024" };

    QStringList result = generateEmail(templateList, dataList);

    QCOMPARE(result[0], QString("Dear John Doe,"));
    QCOMPARE(result[1], QString("Your appointment is on April 15, 2024."));
}

void TestCombined::test_missingPlaceholders()
{
    QStringList templateList = { "Dear #name#,", "We miss you at #place#!" };
    QStringList dataList = { "name: Alice" };  // Missing 'place'

    QStringList result = generateEmail(templateList, dataList);

    QCOMPARE(result[0], QString("Dear Alice,"));
    QCOMPARE(result[1], QString("We miss you at #place#!"));
}

void TestCombined::test_emptyTemplate()
{
    QStringList templateList;
    QStringList dataList = { "name: John Doe", "date: April 15, 2024" };

    QStringList result = generateEmail(templateList, dataList);

    QCOMPARE(result.size(), 0);
}

void TestCombined::test_escapeSequences()
{
    QStringList templateList = { "Dear #name#,\nYour appointment is on #date#.\tThank you." };
    QStringList dataList = { "name: Alice", "date: May 1, 2024" };

    QStringList result = generateEmail(templateList, dataList);

    QCOMPARE(result[0], QString("Dear Alice,\nYour appointment is on May 1, 2024.\tThank you."));
}


/**
 * @brief Test generating email with large text and multiple placeholders.
 *
 * This test verifies that the generateEmail() function handles large texts and multiple placeholders.
 */
void TestCombined::test_largeTextWithMultiplePlaceholders()
{
    QStringList templateList = {
        "Dear #name#,",
        "Thank you for being a valued customer for #years# years.",
        "Your next appointment is scheduled on #date#.",
        "If you have any questions, call us at #phone#."
    };
    QStringList dataList = {
        "name: John Doe",
        "years: 10",
        "date: April 15, 2024",
        "phone: 123-456-7890"
    };

    QStringList result = generateEmail(templateList, dataList);

    QCOMPARE(result[0], QString("Dear John Doe,"));
    QCOMPARE(result[1], QString("Thank you for being a valued customer for 10 years."));
    QCOMPARE(result[2], QString("Your next appointment is scheduled on April 15, 2024."));
    QCOMPARE(result[3], QString("If you have any questions, call us at 123-456-7890."));
}

/**
 * @brief Test handling repeated placeholders in the template.
 *
 * This test checks if generateEmail() correctly replaces repeated placeholders.
 */
void TestCombined::test_repeatedPlaceholders()
{
    QStringList templateList = {
        "Hello #name#,",
        "#name#, we noticed you haven't visited us since #date#.",
        "We hope to see you soon, #name#!"
    };
    QStringList dataList = {
        "name: Alice",
        "date: January 1, 2022"
    };

    QStringList result = generateEmail(templateList, dataList);

    QCOMPARE(result[0], QString("Hello Alice,"));
    QCOMPARE(result[1], QString("Alice, we noticed you haven't visited us since January 1, 2022."));
    QCOMPARE(result[2], QString("We hope to see you soon, Alice!"));
}

/**
 * @brief Test special characters in the template.
 *
 * This test verifies that the generateEmail() function correctly handles special characters like `@` and `#`.
 */
void TestCombined::test_specialCharactersInTemplate()
{
    QStringList templateList = { "Dear #name#, contact us at support@#company# for more details." };
    QStringList dataList = {
        "name: Bob",
        "company: example.com"
    };

    QStringList result = generateEmail(templateList, dataList);

    QCOMPARE(result[0], QString("Dear Bob, contact us at support@example.com for more details."));
}

/**
 * @brief Test incomplete data where some placeholders have no corresponding value.
 *
 * This test verifies how generateEmail() handles cases where data is incomplete.
 */
void TestCombined::test_incompleteData()
{
    QStringList templateList = {
        "Dear #name#,",
        "Your appointment is scheduled for #date# at #time#."
    };
    QStringList dataList = {
        "name: John Doe",
        // Missing 'time' key
        "date: April 15, 2024"
    };

    QStringList result = generateEmail(templateList, dataList);

    QCOMPARE(result[0], QString("Dear John Doe,"));
    QCOMPARE(result[1], QString("Your appointment is scheduled for April 15, 2024 at #time#."));
}

QTEST_APPLESS_MAIN(TestCombined)
#include "test_combined.moc"
