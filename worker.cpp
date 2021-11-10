#include <future>
#include <iostream>
#include <unordered_map>
#if defined(DEBUG)
#include <thread>
#include <chrono>
#endif

#include "worker.hpp"


void worker::start()
{
    end_ = false;
    fut_ = std::async([this] {return this->task(end_, prog_);});
}


void worker::cancel()
{
    end_ = true;
    fut_.wait();
}


bool worker::done() const
{
    auto status = fut_.wait_for(std::chrono::milliseconds(0));
    return status == std::future_status::ready;
}


float worker::progress() const
{
    return prog_;
}


// -----------------------------------------------------------------------------


occ_worker::occ_worker(std::istream &is, std::ostream &os) :
        is_(is), os_(os) {}


void occ_worker::output()
{
    os_ << "\nWord\t\t" << "Occurrence\n";
    for (auto &kv : map_)
        os_ << kv.first << "\t\t" << kv.second << "\n";
}


int occ_worker::task(const std::atomic_bool &end, std::atomic<float> &prog)
{
    // stream length
    is_.seekg(0, std::ios::end);
    float len = 100.0f/is_.tellg();
    is_.seekg(0, std::ios::beg);

    // count occurences
    std::string word;
    std::streampos pos;
    while (((pos = is_.tellg()) >= 0) && is_ >> word) {
        map_[word]++;
        prog = len * pos;
        if (end)
            return 1;
#if defined(DEBUG)
        // simulate delay
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
#endif
    }
    prog = 100.0f;
    return 0;
}
