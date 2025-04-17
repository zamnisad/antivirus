#pragma once
#include <queue>
#include <ZamniVirus/Errors/Error.h>
#include <ZamniVirus/Logging/Logger.h>


class DirWork : Error {
private:
    std::string start_dir = "";
    int count_files = 0;
    int count_dirs = 1;
    Logger& logger;
    std::queue<std::string> dirs_queue;
public:
    DirWork(std::string directory, Logger& logger);
    bool check_directory(const std::string& dirPath);
    std::string get_start_dir() { return start_dir; }
    int get_count_files() { return count_files; }
    int get_count_dirs() { return count_dirs; }
    std::string get_current_dir();
private:
    void add_dirs_to_queue();
};
    