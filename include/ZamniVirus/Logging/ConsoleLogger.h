#pragma once
#include <string>
#include <vector>
#include <ZamniVirus/Logging/ProgressBar.h>
#include <ZamniVirus/Config/Types.h>


class ConsoleLogger : public ProgressBar {
    public:
        void print_directory_info(std::string& directory, int files, int dirs);
        void print_process_start(std::string& name);
        void print_process_end(std::string& name);
        void print_scanning_dir(std::string& dir);
        void print_log_file(const std::string& file, int type);
        void print_scanned_dir_info(std::string& dir, int filesCount, int infected);
        void print_infected_in_dir(std::string& dir, std::vector<Infected>& infected);
        void print_infected_all(std::vector<Infected>& infected);
        void print_infected_not();
        void print_both_numbers(std::vector<int> intersection);
        void print_result_lists(std::vector<int> remove, std::vector<int> quarantine);
        void print_choose_files(int type);
        void print_deleted_quarantined(std::vector<Infected> removed, std::vector<Infected> quarantined);
    };
    