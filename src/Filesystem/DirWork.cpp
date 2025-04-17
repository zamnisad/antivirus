#pragma once
#include <ZamniVirus/Filesystem/DirWork.h>


DirWork::DirWork(std::string directory, Logger& logger) : logger(logger) {
    if (check_directory(directory)) {
        start_dir = directory;
        add_dirs_to_queue();
        count_dirs = dirs_queue.size();

        logger.write_d(directory, count_files, count_dirs);
        logger.print_directory_info(start_dir, count_files, count_dirs);
    }
    else {
        exit(1);
    }
}

bool DirWork::check_directory(const std::string& dirPath) {
    if (!fs::exists(dirPath) || !fs::is_directory(dirPath)) {
        logger.write_e(get_error(1, dirPath));
        return false;
    }
    return true;
}

std::string DirWork::get_current_dir() { 
    if (dirs_queue.empty()) {
        return "end";
    }
    std::string folder = dirs_queue.front();
    dirs_queue.pop();
    return folder; 
}

void DirWork::add_dirs_to_queue() {
    dirs_queue.push(start_dir);
    std::queue<std::string> temp_dirs;
    temp_dirs.push(start_dir);

    while (!temp_dirs.empty()) {
        std::string current_dir = temp_dirs.front();
        temp_dirs.pop();

        for (const auto& entry : fs::directory_iterator(current_dir)) {
            try {  
                if (fs::is_directory(entry)) {
                    count_dirs++;
                    temp_dirs.push(fs::absolute(entry.path()).string());
                    dirs_queue.push(fs::absolute(entry.path()).string());
                }
                else {
                    count_files++;
                }
            } catch (const fs::filesystem_error& e) {
                logger.write_e("Ошибка доступа к: " + fs::absolute(entry.path()).string() + " — " + e.what());
            }
        }
    }
}
    