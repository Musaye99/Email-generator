#include <QtTest>

// add necessary includes here

class EmaukGeneratorTest : public QObject
{
    Q_OBJECT

public:
    EmaukGeneratorTest();
    ~EmaukGeneratorTest();

private slots:
    void test_case1();
};

EmaukGeneratorTest::EmaukGeneratorTest() {}

EmaukGeneratorTest::~EmaukGeneratorTest() {}

void EmaukGeneratorTest::test_case1() {}

QTEST_APPLESS_MAIN(EmaukGeneratorTest)

#include "tst_emaukgeneratortest.moc"
