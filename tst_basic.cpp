#include <QtTest>

// add necessary includes here
#include "../rcpsp_qt/algorithm.h"
#include "../rcpsp_qt/loader.h"

class basic : public QObject
{
    Q_OBJECT

public:
    basic();
    ~basic();

private slots:
    void workerTests();
    void algorithmCase1();
    void algorithmCase2();
    void algorithmCase3();
    void algorithmCase4();
    void algorithmCase5();
    void algorithmCase6();
    void algorithmCase7();
    void algorithmCase8();
private:
    void check_loaded(QString file_name, std::vector<int> expected);
    void compare_result(const std::vector<ResultPair> &completed, std::vector<int> expected);
};

basic::basic() {}

basic::~basic() {}

void basic::workerTests()
{
    Job firstJob(0, 0, {{2, 0.3}, {3, 0.7}, {4, 0.2}});
    Job secondJob(0, 0, {{2, 0.3}, {3, 0.7}, {4, 0.2}});
    Job thirdJob(0, 0, {{2, 0.3}, {3, 0.2}});

    {
        Worker worker(Plan({{11, 2}}));
        int clock = 0;
        worker.set_clock(&clock);

        QVERIFY(worker.is_free({{10, 1.0f}}));
        QCOMPARE(worker.current_occupancy(), 0);

        clock = 1;
        worker.assign(&firstJob);

        QVERIFY(worker.is_free({{1, 1.0f}}, 10));
        QCOMPARE(worker.is_free({{2, 1.0f}}, 10), false);
        QCOMPARE(worker.is_free({{2, 1.0f}}, 9), false);
        QVERIFY(worker.is_free({{2, 0.8f}}, 9));

        clock = 12;
        worker.update();
    }

    {
        Worker worker(Plan({{13, 1}}));
        int clock = 1;
        worker.set_clock(&clock);

        worker.assign(&firstJob);
        QCOMPARE(worker.can_be_placed_after(secondJob.get_occupancy()), 3);
    }
}

void basic::compare_result(const std::vector<ResultPair>& completed, std::vector<int> expected)
{
    for (int i = 0; i < expected.size(); i++)
    {
        QCOMPARE(completed[i].job_id, expected.size() - i - 1);
        QCOMPARE(completed[i].start, expected[expected.size() - i - 1]);
    }
}

void basic::check_loaded(QString file_name, std::vector<int> expected)
{
    Algorithm algorithm;
    std::vector<Job*> all_jobs;
    std::vector<Worker*> all_workers;
    Loader::Load("../rcpsp_test/" + file_name, algorithm, all_workers, all_jobs);
    algorithm.run();
    auto completed = algorithm.get_completed();
    compare_result(completed, expected);
}

void basic::algorithmCase1()
{
    check_loaded("case1.csv", {0, 0, 0, 9});
}

void basic::algorithmCase2()
{
    check_loaded("case2.csv", {1, 0, 0, 1});
}

void basic::algorithmCase3()
{
    check_loaded("case3.csv", {10, 1, 20, 22});
}

void basic::algorithmCase4()
{
    check_loaded("case4.csv", {1, 14, 10, 21, 9});
}

void basic::algorithmCase5()
{
    check_loaded("case5.csv", {1, 9, 16, 18});
}

void basic::algorithmCase6()
{
    check_loaded("case6.csv", {33, 0, 22, 11});
}

void basic::algorithmCase7()
{
    check_loaded("case7.csv", {5, 3});
}

void basic::algorithmCase8()
{
    Algorithm algorithm;
    std::vector<Job*> all_jobs;
    std::vector<Worker*> all_workers;
    Loader::Load("../rcpsp_test/case8_large.csv", algorithm, all_workers, all_jobs);
    algorithm.run();
    auto completed = algorithm.get_completed();
    QCOMPARE(completed.size(), 4000);
}

QTEST_APPLESS_MAIN(basic)

#include "tst_basic.moc"
