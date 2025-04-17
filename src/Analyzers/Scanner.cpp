#pragma once
#include <ZamniVirus/Analyzers/Scanner.h>


void Scanner::scan_directory(std::string& cd) {
    std::set<std::string> processed_files;
    
    int total_files = 0;
    for (const auto& file : fs::directory_iterator(fs::path(fs::absolute(cd)))) {
        if (file.is_regular_file()) {
            std::string file_path = file.path().string();
            if (processed_files.find(file_path) == processed_files.end()) {
                ++total_files;
            }
        }
    }
    int current_file = 0;

    if (total_files == 0) {
        logger.print_progress_bar(current_file, total_files);
    }

    for (const auto& file : fs::directory_iterator(fs::path(fs::absolute(cd)))) {
        if (file.is_regular_file()) {
            std::string file_path = file.path().string();

            if (processed_files.find(file_path) != processed_files.end()) {
                continue;
            }

            ScanResult result = fileAnalyzer.scan_file(file_path);
            processed_files.insert(file_path);

            if (result.is_infected) {
                results.push_back(result);
            }

            ++current_file;
            logger.print_progress_bar(current_file, total_files);
        }
    }

    std::cout << RESET << std::endl;
}

void Scanner::scan() {
    logger.write_start("Scanner");
    std::string cd = dirWork.get_current_dir();
    while (cd != "end") {
        logger.print_scanning_dir(cd);
        scan_directory(cd);
        cd = dirWork.get_current_dir();
    }
    std::cout << "Check ready!" << std::endl;
    logger.write_end("Scanner");
}
