#pragma once
#include <ZamniVirus/Logging/ConsoleLogger.h>


void ConsoleLogger::print_directory_info(std::string& directory, int files, int dirs) {
    std::cout << CYAN << "[DIR]" << RESET << " Start directory Info:\n";
    std::cout << CYAN << "├────────────────────────────────────────────┤" << RESET << std::endl;
    std::cout << CYAN << "├─" << RESET << " Path      : " << directory << "\n";
    std::cout << CYAN << "├─" << RESET << " Files     : " << files << "\n";
    std::cout << CYAN << "├─" << RESET << " Folders   : " << dirs << "\n";
    std::cout << CYAN << "└────────────────────────────────────────────┘" << RESET << "\n";
}

void ConsoleLogger::print_process_start(std::string& name) {
    std::cout << GREEN << "[BEG]" << RESET << " Starting: " << name << "\n";
}

void ConsoleLogger::print_process_end(std::string& name) {
    std::cout << GREEN << "[END]" << RESET << " Finished: " << name << "\n";
}

void ConsoleLogger::print_scanning_dir(std::string& dir) {
    std::cout << BLUE << "[SCN]" << RESET << " Scanning: " << dir << std::endl;
}

void ConsoleLogger::print_log_file(const std::string& file, int type) {
    if (type == 0) { // file not found
        std::cout << GREEN << "[LOG]" << RESET << " Log file created by path: " << file << std::endl;
    }
    if (type == 1) { // file large
        std::cout << YELLOW << "[LOG]" << RESET << " Log file too large. It will be refactor: " << file << std::endl;
    }
    // all fine
}

void ConsoleLogger::print_scanned_dir_info(std::string& dir, int filesCount, int infected) {
    std::cout << CYAN << "\t[SCN]" << RESET << " Scanned directory: " << dir << std::endl;
    std::cout << CYAN << "├────────────────────────────────────────────┤" << RESET << std::endl;
    std::cout << CYAN << "├ " << RESET << "Files     : " << filesCount << "\n";
    std::cout << CYAN << "├ " << RESET << "Infected  : " << infected << "\n";
    std::cout << CYAN << "├ " << RESET << "Clear     : " << filesCount - infected << "\n";
    std::cout << CYAN << "└────────────────────────────────────────────┘" << RESET << "\n";
}

void ConsoleLogger::print_infected_in_dir(std::string& dir, std::vector<Infected>& infected) {
    std::cout << RED << "[VIR]" << RESET << " Search infected files in dir: " << dir << std::endl;
    std::cout << RED << "├────────────────────────────────────────────┤\n" << RESET;
    for (Infected item : infected) {
        std::cout << RED << "\t├ " << RESET << " File " << item.filename << " with size: " << item.file_size 
        << " is infected!" << std::endl;
    }
    std::cout << RED << "└────────────────────────────────────────────┘" << RESET << "\n";
}

void ConsoleLogger::print_infected_all(std::vector<Infected>& infected) {
    std::cout << RED << "[VIR]" << RESET << " Infected files:\n";
    std::cout << RED << "├────────────────────────────────────────────┤\n" << RESET;
    int i = 1;
    for (auto& f : infected) {
        std::cout << RED << "\t├ " << RESET << i << ". " << f.filename << CYAN << " -> " << RESET 
        << "Virus name: " << f.signature->name << "\n";
        i++;
    }
    std::cout << RED << "└────────────────────────────────────────────┘" << RESET << "\n";
}

void ConsoleLogger::print_infected_not() {
    std::cout << GREEN << "[VIR]" << RESET << " No one file not infected! All clear!" << std::endl;
}

void ConsoleLogger::print_both_numbers(std::vector<int> intersection) {
    std::cout << YELLOW << "[WRN]" << RESET << " These numbers are both in remove and quarantine lists: ";
    for (int num : intersection) std::cout << num << " ";
    std::cout << "\n";
}

void ConsoleLogger::print_result_lists(std::vector<int> remove, std::vector<int> quarantine) {
    std::cout << CYAN << "[INF]" << RESET << " Final remove list: ";
    for (int r : remove) std::cout << r << " ";
    std::cout << "\n";

    std::cout << CYAN << "[INF]" << RESET << "Final Quarantine List: ";
    for (int q : quarantine) std::cout << q << " ";
    std::cout << "\n\n";
}

void ConsoleLogger::print_choose_files(int type) {
    std::cout << CYAN << "[INF]" << " Below you will be asked to select the files that will be sent to the quarantine/trash" << std::endl;
    std::cout << "      If u need, u can write '-1' if u need to remove/quarantine all files";
    std::cout << "      However, quarantine takes precedence over deletion" << RESET << std::endl;
    if (type == 0) std::cout << BLUE << "\t[INP]" << RESET << " Input numbers to remove (with space): ";
    else std::cout << BLUE << "\t[INP]" << RESET << " Input numbers to quarantine (with space): ";
}

void ConsoleLogger::print_deleted_quarantined(std::vector<Infected> removed, std::vector<Infected> quarantined) {
    std::cout << CYAN << "[INF]" << RESET << " Removed infected files: " << std::endl;
    std::cout << CYAN << "├────────────────────────────────────────────┤\n" << RESET;
    for (Infected r : removed) std::cout << CYAN << "├─ " << RESET << r.filename << std::endl;
    std::cout << CYAN << "└────────────────────────────────────────────┘" << RESET << "\n";

    std::cout << CYAN << "[INF]" << RESET << " Files in quarantine: " << std::endl;
    std::cout << CYAN << "├────────────────────────────────────────────┤\n" << RESET;
    for (Infected q : quarantined) std::cout << CYAN << "├─ " << RESET << q.filename << std::endl;
    std::cout << CYAN << "└────────────────────────────────────────────┘" << RESET << "\n";
}