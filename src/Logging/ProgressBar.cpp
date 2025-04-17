#pragma once
#include <ZamniVirus/Logging/ProgressBar.h>


void ProgressBar::print_progress_bar(int current, int total, int width) {
    if (total == 0 && current == 0) {
        std::cout << BLUE << "\r[";
        for (int i = 0; i < width; ++i) {
            std::cout << "#";
        }
        std::cout << "] " << 100 << "%";
    }
    else {
        float progress = static_cast<float>(current) / total;
        int filled = static_cast<int>(progress * width);
        std::cout << BLUE << "\r[";
        for (int i = 0; i < width; ++i) {
            if (i < filled) std::cout << "#";
            else std::cout << ".";
        }
        std::cout << "] " << static_cast<int>(progress * 100) << "%";
        std::cout.flush();
    }
}