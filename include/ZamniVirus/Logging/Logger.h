#pragma once
#include <fstream>
#include <ZamniVirus/Logging/ConsoleLogger.h>


class Logger : public ConsoleLogger { // Просто для удобного логирования
private:
    fs::path pathFile;
    std::ofstream file;

    std::string current_time();
public:
    Logger(std::string path = "./log.txt");
    void write_start(std::string type);
    void write_end(std::string type);
    void write_qa(std::string time, const fs::path filePath, fs::path destPath, Infected& inf);
    void write_e(std::string e);
    void write_qr(const fs::path& qFile, const fs::path& originalPath);
    void write_a(CheckResult& result, std::string filename);
    void write_d(std::string directory, int count_files, int count_dirs);
    void write_vir(std::vector<Infected> inf);
    void write_vir0();
    void close_file();
    // void write_d_q(std::vector<Infected> removed, std::vector<Infected> quarantined);
};
    