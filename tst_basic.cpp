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

void basic::algorithmCase1()
{
    Algorithm algorithm;
    std::vector<Job*> all_jobs;
    std::vector<Worker*> all_workers;
    Loader::Load("case1.csv", algorithm, all_workers, all_jobs);
    algorithm.run();
    auto completed = algorithm.get_completed();
    QCOMPARE(completed[0].job_id, 3);
    QCOMPARE(completed[0].start, 9);
    QCOMPARE(completed[1].job_id, 2);
    QCOMPARE(completed[1].start, 0);
    QCOMPARE(completed[2].job_id, 1);
    QCOMPARE(completed[2].start, 0);
    QCOMPARE(completed[3].job_id, 0);
    QCOMPARE(completed[3].start, 0);
}

void basic::algorithmCase2()
{
    Algorithm algorithm;
    std::vector<Job*> all_jobs;
    std::vector<Worker*> all_workers;
    Loader::Load("case2.csv", algorithm, all_workers, all_jobs);
    algorithm.run();
    auto completed = algorithm.get_completed();
    QCOMPARE(completed[0].job_id, 3);
    QCOMPARE(completed[0].start, 1);
    QCOMPARE(completed[1].job_id, 2);
    QCOMPARE(completed[1].start, 0);
    QCOMPARE(completed[2].job_id, 1);
    QCOMPARE(completed[2].start, 0);
    QCOMPARE(completed[3].job_id, 0);
    QCOMPARE(completed[3].start, 1);
}

QTEST_APPLESS_MAIN(basic)

#include "tst_basic.moc"
