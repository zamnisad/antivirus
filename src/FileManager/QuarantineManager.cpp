#pragma once
#include <ZamniVirus/FileManager/QuarantineManager.h>



QuarantineManager::QuarantineManager(VirusManager& vm, std::string qdir) : QDir(fs::absolute(qdir)), vm(vm) {
    if (!fs::exists(QDir)) {
        fs::create_directory(QDir);
    }
}

bool QuarantineManager::add_file(fs::path filePath, Infected& inf) {
    std::string fileNameOnly = inf.filename.substr(inf.filename.find_last_of("/\\") + 1);
    std::string newName = "q_" + std::to_string(time(nullptr)) + "_" + fileNameOnly;
    fs::path destPath = QDir / newName;

    try {
        fs::rename(filePath, destPath);

        vm.logger.write_qa(getCurrentTime(), filePath, destPath, inf);
        return true;
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "Quarantine failed: " << e.what() << std::endl;
        vm.logger.write_e(vm.get_error(3, filePath.string()));
        return false;
    }
}

bool QuarantineManager::restore_file(const fs::path& qFile, const fs::path& originalPath) {
    if (!fs::exists(qFile)) {
        vm.logger.write_e(vm.get_error(4, qFile.string()));
        return false;
    }

    fs::rename(qFile, originalPath);
    vm.logger.write_qr(qFile, originalPath);
    return true;
}

void QuarantineManager::add_files() {
    vm.logger.write_start("Quarantine");
    for (auto& i : vm.to_quarantine) {
        add_file(fs::path(fs::absolute(i.filename)), i);
    }
    vm.logger.write_end("Quarantine");
}

void QuarantineManager::add_to_infected(std::vector<ScanResult> results) {
    for (auto r : results) {
        if (r.is_infected) {
            Infected temp = Infected(r.filename, r.file_size, r.signature, r.date);
            vm.infected.push_back(temp);
        }
    }
}

std::string QuarantineManager::getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&time);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}