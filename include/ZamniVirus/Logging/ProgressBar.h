#pragma once
#include <chrono>
#include <iostream>
#include <ZamniVirus/Config/Common.h>


class ProgressBar {
private:
    std::chrono::steady_clock::time_point get_time() {
        return std::chrono::steady_clock::now();
    }
public:
    void print_progress_bar(int current, int total, int width = 50);
};