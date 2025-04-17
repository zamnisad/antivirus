#pragma once
#include <ZamniVirus/FileManager/DeleteManager.h>


class QuarantineManager {
private:
    fs::path QDir;
    VirusManager& vm;
public:
    QuarantineManager(VirusManager& vm, std::string qdir);
    bool add_file(fs::path filePath, Infected& inf);
    bool restore_file(const fs::path& qFile, const fs::path& originalPath);
    void add_files();

private:
    void add_to_infected(std::vector<ScanResult> results);
    std::string getCurrentTime();
};