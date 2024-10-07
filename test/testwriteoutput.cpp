#include <QtTest>
#include "../emailGeneratorProgram/functions.h"
#include <QFile>
#include <QTextStream>



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

void TestWriteOutput::test_emptyContent()
{
    // Test Case: Writing empty content should create an empty file
    QStringList emptyContent;

    QString filePath = "empty_output.txt";
    writeOutput(filePath, emptyContent);

    QFile outputFile(filePath);
    QVERIFY(outputFile.open(QIODevice::ReadOnly | QIODevice::Text));

    QCOMPARE(outputFile.size(), qint64(0));  // File size should be 0

    outputFile.close();
}

QTEST_APPLESS_MAIN(TestWriteOutput)
#include "testwriteoutput.moc"
