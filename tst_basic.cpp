#include <QtTest>

// add necessary includes here
#include "algorithm.h"
#include "../rcpsp_qt/algorithm/loader.h"

class basic : public QObject
{

    Q_OBJECT

public:
    basic();
    ~basic();

private slots:
    void workerTests();
    //void algorithmCase1();
    void algorithmCase2();
    void algorithmCase3();
    void algorithmCase4();
    void algorithmCase5();
    void algorithmCase6();
    void algorithmCase7();
    //void algorithmCase8();
    //friend class PendingFronts;
    void weights_1()
    {
        int current_time = 13;
        CompletedJobs c;
        AssignedJobs j(&current_time, &c);
        AlgorithmWeights w;
        for (const auto& n : Weights::WeightsNames)
        {
            Weights::set(w, n, 0.2);
        }
        PendingFronts p(&current_time, &j, Preference::NONE, 0, w);
        Job job = Job(0, 0, {{4, 0.3}, {5, 0.5}});
        job.set_start_after(13);
        job.set_end_before(30);
        job.set_critical_time(21);
        // job.set_ancestors in the future?
        WorkerGroup g;
        g.set_clock(&current_time);
        Plan plan = Plan({{9, 1}});
        auto* worker = new Worker(plan);
        worker->set_clock(&current_time);
        g.add_worker(worker);
        JobPair jp =
        {
            .start_after = 13,
            .end_before = 30,
            .job = &job,
            .worker_groups = {&g},
            .id = 0
        };
        p.add(13, jp);
        AlgorithmDataForWeights dw
        {
            .job_count_not_assigned = 0,
            .job_count_overall = 1,
            .max_critical_time = 21
        };
        //"ancestors_per_left" = 0, // кол-во последователей / кол-во оставшихся требований
        //"ancestors_per_job" = 0, // кол-во последователей / кол-во требований всего
        //"critical_time_per_max_critical_time" = 1, // критическое время требования / максимальное критическое время всех требований
        //"avg_occupancy" = (4 * 0.3 + 5 * 0.5) / 9, // средняя занятость станка во время выполнения
        //"time_after_begin_per_overall_time" = 0 // время от начала выполнения до текущего момента / время всего на выполнение этого требования
        p.tick(dw);
        //qDebug() << p._data.size() << p._data[0].job_pairs[0].current_preference << p._data[0].time;
        double preference = ((4.0 * 0.3 + 5.0 * 0.5) / 9.0 + 1.0) / 5;
        double current = p._data[0].job_pairs[0].current_preference;
        QVERIFY(std::abs(preference - current) < 0.0001);
        //QCOMPARE(p._data[0].job_pairs[0].current_preference, ((4.0 * 0.3 + 5.0 * 0.5) / 9.0 + 1.0) / 5);
    }
    void weights_2()
    {
        int current_time = 13;
        CompletedJobs c;
        AssignedJobs j(&current_time, &c);
        AlgorithmWeights w;
        for (const auto& n : Weights::WeightsNames)
        {
            Weights::set(w, n, 0.2);
        }
        PendingFronts p(&current_time, &j, Preference::NONE, 0, w);

        WorkerGroup g;
        g.set_clock(&current_time);
        Plan plan = Plan({{9, 1}});
        auto* worker = new Worker(plan);
        worker->set_clock(&current_time);
        g.add_worker(worker);

        Job job = Job(0, 0, {{4, 0.3}, {5, 0.5}});
        job.set_start_after(13);
        job.set_end_before(30);
        job.set_critical_time(21);
        JobPair jp =
        {
            .start_after = 13,
            .end_before = 30,
            .job = &job,
            .worker_groups = {&g},
            .id = 0
        };
        p.add(13, jp);

        Job job2 = Job(0, 0, {{5, 0.6}, {4, 0.9}});
        job2.set_start_after(18);
        job2.set_end_before(40);
        job2.set_critical_time(31);
        JobPair jp2 =
        {
            .start_after = 18,
            .end_before = 40,
            .job = &job2,
            .worker_groups = {&g},
            .id = 0
        };
        job.set_ancestors({&job2});

        AlgorithmDataForWeights dw
        {
            .job_count_not_assigned = 0,
            .job_count_overall = 2,
            .max_critical_time = 31
        };

        p.tick(dw);

        //"ancestors_per_left" = 1 / 1, // кол-во последователей / кол-во оставшихся требований
        //"ancestors_per_job" = 1 / 2, // кол-во последователей / кол-во требований всего
        //"critical_time_per_max_critical_time" = 21 / 31, // критическое время требования / максимальное критическое время всех требований
        //"avg_occupancy" = (4 * 0.3 + 5 * 0.5) / 9, // средняя занятость станка во время выполнения
        //"time_after_begin_per_overall_time" = 0 // время от начала выполнения до текущего момента / время всего на выполнение этого требования
        double preference = (1 + 0.5 + 21.0 / 31.0 + (4.0 * 0.3 + 5.0 * 0.5) / 9.0) / 5;
        double current = p._data[0].job_pairs[0].current_preference;
        QVERIFY(std::abs(preference - current) < 0.0001);

        p.tick(dw);
        j.tick();
        p.add(30, jp2);
        p.tick(dw);
        p.tick(dw);
        // now check second
        //"ancestors_per_left" = 0, // кол-во последователей / кол-во оставшихся требований
        //"ancestors_per_job" = 0, // кол-во последователей / кол-во требований всего
        //"critical_time_per_max_critical_time" = 1, // критическое время требования / максимальное критическое время всех требований
        //"avg_occupancy" = (5.0 * 0.6 + 4.0 * 0.9) / 9.0, // средняя занятость станка во время выполнения
        //"time_after_begin_per_overall_time" = 12 / 22 // время от начала выполнения до текущего момента / время всего на выполнение этого требования
        preference = (1.0 + (5.0 * 0.6 + 4.0 * 0.9) / 9.0 + 12.0 / 22.0) / 5;
        //current = p._data[0].job_pairs[0].current_preference;
        //QVERIFY(std::abs(preference - current) < 0.0001);
        //FIXME: i know that this is right but i need to actually pass the value somehow
    }
    void stats()
    {
        Job job = Job(0, 0, {{5, 0.6}, {4, 0.9}});
        job.set_start_after(10);
        job.set_end_before(35);
        ResultPair r;
        r.job = &job;
        r.job_id = 0;
        r.start = 20;

        Job job2 = Job(0, 0, {{3, 0.6}, {4, 0.9}});
        job2.set_start_after(10);
        job2.set_end_before(37);
        ResultPair r2;
        r2.job = &job2;
        r2.job_id = 1;
        r2.start = 25;

        Stats stats({r, r2}, 0.03);
        QVERIFY(stats.wait_coeff.at(0.39) == 1);
        QVERIFY(stats.work_coeff.at(0.36) == 1);

        QVERIFY(stats.wait_coeff.at(0.57) == 1);
        QVERIFY(stats.work_coeff.at(0.27) == 1);
        //qDebug() << "STATS (wait_coeff): \n";
        //for (auto point : stats.wait_coeff)
        //{
        //    qDebug() << "X = " << point.first << ", Y = " << point.second << "\n";
        //}
        //qDebug() << "STATS (work_coeff): \n";
        //for (auto point : stats.work_coeff)
        //{
        //    qDebug() << "X = " << point.first << ", Y = " << point.second << "\n";
        //}
    }
private:
    void check_loaded(QString file_name, QString preference_file_name, std::vector<int> expected);
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

void basic::check_loaded(QString file_name, QString preference_file_name, std::vector<int> expected)
{
    Algorithm algorithm;
    std::vector<Job*> all_jobs;
    std::vector<Worker*> all_workers;
    Loader::Load("../rcpsp_test/" + file_name, algorithm, all_workers, all_jobs);
    Loader::LoadPreferences("../rcpsp_test/" + preference_file_name, algorithm);
    Loader::LoadWeights("../rcpsp_test/weights.csv", algorithm);
    algorithm.run();
    auto completed = algorithm.get_completed();
    compare_result(completed, expected);
}

//void basic::algorithmCase1()
//{
//    check_loaded("case1.csv", "preferences1.csv", {0, 0, 0, 9});
//}

void basic::algorithmCase2()
{
    check_loaded("case2.csv", "preferences2.csv", {1, 0, 0, 1});
}

void basic::algorithmCase3()
{
    check_loaded("case3.csv", "preferences3.csv", {10, 1, 20, 22});
}

void basic::algorithmCase4()
{
    check_loaded("case4.csv", "preferences4.csv", {1, 14, 10, 21, 9});
}

void basic::algorithmCase5()
{
    check_loaded("case5.csv", "preferences5.csv", {1, 9, 16, 18});
}

void basic::algorithmCase6()
{
    check_loaded("case6.csv", "preferences6.csv", {0, 11, 22, 33});
}

void basic::algorithmCase7()
{
    check_loaded("case7.csv", "preferences7.csv", {5, 3});
}

//void basic::algorithmCase8()
//{
//    Algorithm algorithm;
//    std::vector<Job*> all_jobs;
//    std::vector<Worker*> all_workers;
//    Loader::Load("../rcpsp_test/case8_large.csv", algorithm, all_workers, all_jobs);
//    algorithm.run();
//    auto completed = algorithm.get_completed();
//    QCOMPARE(completed.size(), 4000);
//}

QTEST_APPLESS_MAIN(basic)

#include "tst_basic.moc"
