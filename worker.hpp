#ifndef _WORKER_H__
#define _WORKER_H__

#include <atomic>
#include <sstream>
#include <future>
#include <unordered_map>


class worker {
public:
    void start();
    void cancel();
    bool done() const;
    float progress() const;

    virtual void output() = 0;

protected:
    virtual int task(const std::atomic_bool &end, std::atomic<float> &prog) = 0;

private:
    std::future<int> fut_;
    std::atomic_bool end_{false};
    std::atomic<float> prog_{0.0f};
};


// -----------------------------------------------------------------------------

class occ_worker : public worker {
public:
    occ_worker(std::istream &is, std::ostream &os);

    void output() override;

private:
    std::istream &is_;
    std::ostream &os_;
    std::unordered_map<std::string, std::size_t> map_;

    int task(const std::atomic_bool &end, std::atomic<float> &prog) override;
};

#endif // _WORKER_H__
