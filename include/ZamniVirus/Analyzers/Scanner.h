#pragma once
#include <ZamniVirus/FileManager/QuarantineManager.h>


class Scanner {
private:
    DirWork& dirWork;
    FileAnalyzer& fileAnalyzer;
    Logger& logger;
    std::vector<ScanResult> results;
public:
    Scanner(DirWork& dirWork, FileAnalyzer& fileAnalyzer, Logger& logger) : dirWork(dirWork), fileAnalyzer(fileAnalyzer), logger(logger) {};
    void scan_directory(std::string& cd);
    void scan();
    std::vector<ScanResult> get_results() {
        return results;
    }
};
