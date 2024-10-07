#include <QtTest>
#include "../emailGeneratorProgram/functions.h"


class TestGetFileData : public QObject
{
    Q_OBJECT

private slots:
    void test_emptyFile();
    void test_fileWithData();
};

void TestGetFileData::test_emptyFile()
{
    // Create an empty file for testing
    QFile emptyFile("empty.txt");
    QVERIFY(emptyFile.open(QIODevice::WriteOnly));  // Open file for writing (empty content)
    emptyFile.close();  // Close file after creating it

    // Call getFileData on an empty file
    QStringList result = getFileData("empty.txt");

    // Expecting an empty QStringList
    QCOMPARE(result.size(), 0);
}

void TestGetFileData::test_fileWithData()
{
    // Create a file with some content
    QFile dataFile("example_template.txt");
    QVERIFY(dataFile.open(QIODevice::WriteOnly));  // Open file for writing

    QTextStream out(&dataFile);
    out << "Dear #name#,\nYour appointment is scheduled for #date#.";
    dataFile.close();  // Close file after writing content

    // Call getFileData on this file
    QStringList result = getFileData("example_template.txt");

    // Verify the size and content of the QStringList
    QCOMPARE(result.size(), 2);  // Two lines in the file
    QCOMPARE(result[0], QString("Dear #name#,"));
    QCOMPARE(result[1], QString("Your appointment is scheduled for #date#."));
}

QTEST_APPLESS_MAIN(TestGetFileData)
#include "testfiledata.moc"
