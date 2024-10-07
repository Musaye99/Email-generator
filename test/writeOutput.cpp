#include <QtTest>
#include "./email-generator-master/emailGenerator/emailGeneratorProgram/functions.h"
#include <QFile>

class TestWriteOutput : public QObject
{
    Q_OBJECT

private slots:
    void test_validFilePath();
    void test_emptyContent();
};

void TestWriteOutput::test_validFilePath()
{
    // Test Case: Writing valid content to a valid file path
    QStringList content = { "Dear John Doe,", "Your appointment is on April 15, 2024." };

    // File path for test
    QString filePath = "output_email.txt";

    // Call the function
    writeOutput(filePath, content);

    // Verify file was written correctly
    QFile outputFile(filePath);
    QVERIFY(outputFile.open(QIODevice::ReadOnly | QIODevice::Text));  // Ensure file can be opened

    QTextStream in(&outputFile);
    QString fileContent = in.readAll();

    // Expected content in the file
    QString expectedContent = "Dear John Doe,\nYour appointment is on April 15, 2024.\n";

    // Compare file content with expected content
    QCOMPARE(fileContent, expectedContent);

    outputFile.close();
}

void TestWriteOutput::test_emptyContent()
{
    // Test Case: Writing empty content should create an empty file
    QStringList emptyContent;  // Empty QStringList

    // File path for test
    QString filePath = "empty_output.txt";

    // Call the function with empty content
    writeOutput(filePath, emptyContent);

    // Verify file was created and is empty
    QFile outputFile(filePath);
    QVERIFY(outputFile.open(QIODevice::ReadOnly | QIODevice::Text));  // Ensure file can be opened

    QCOMPARE(outputFile.size(), qint64(0));  // Verify file size is zero

    outputFile.close();
}

QTEST_APPLESS_MAIN(TestWriteOutput)
#include "testwriteoutput.moc"
