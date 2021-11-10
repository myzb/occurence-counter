// < ------------------------------------------------------------------------- >
// < occurence-counter                                                         >
// < counts and reports the occurence of each word in the given text file      >
// < ------------------------------------------------------------------------- >

#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>

#include "utils.h"
#include "progressbar.hpp"
#include "worker.hpp"


static void print_usage(const char *app_name)
{
    std::cout << "Usage: " << app_name << " TEXTFILE\n";
    std::cout << "Read TEXTFILE and print the occurence of each word\n";
}


int main(int argc, char *argv[])
{
    if (argc < 2) {
        print_usage(argv[0]);
        return -1;
    }

    std::ifstream fs(argv[1]);

    // progressbar and occurence counter: output -> cout
    progressbar bar(30, std::cout);
    occ_worker worker(fs, std::cout);

    worker.start();
    std::cout << "Press \'c\' to cancel\n";

    while (!worker.done()) {
        if (get_keystroke() == 'c') {
            bar.text("Stopped");
            worker.cancel();
            break;
        }
        bar.draw(worker.progress());
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    bar.draw(worker.progress());
    worker.output();

    return 0;
}
