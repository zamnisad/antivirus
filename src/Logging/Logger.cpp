#pragma once
#include <ZamniVirus/Logging/Logger.h>


std::string Logger::current_time() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm tm_buf;
    localtime_s(&tm_buf, &in_time_t);
    
    std::ostringstream ss;
    ss << std::put_time(&tm_buf, "[%Y-%m-%d %H:%M:%S]");
    return ss.str();
}

Logger::Logger(std::string path) {
    fs::path p(path);
    
    pathFile = fs::absolute(p);

    if (!fs::exists(pathFile)) {
        std::ofstream f(pathFile);
        f.close();
        print_log_file(pathFile.string(), 0);
    }

    if (fs::exists(pathFile) && fs::file_size(pathFile) > static_cast<std::uint64_t>(1024) * 1024 * 100) {
        fs::remove(pathFile);
        std::ofstream f(pathFile);
        f.close();
        print_log_file(pathFile.string(), 1);
    }
    file.open(pathFile, std::ios::app);

    file << "\n" << std::string(80, '=') << "\n";
    file << current_time() << " LOGGER INITIALIZED\n";
    file << std::string(80, '=') << "\n\n";
}

void Logger::write_start(std::string type) {
    // types: Scanner, Quarantine, Signatures
    file << current_time() << " [BEG] " << std::left << std::setw(11) << type << " started!" << "\n"
            << std::string(80, '-') << "\n";
}

void Logger::write_end(std::string type) {
    // types: Scanner, Quarantine, Signatures
    file << current_time() << " [END] " << std::left << std::setw(12) << type << " ended!" << "\n"
            << std::string(80, '-') << "\n\n";
}

void Logger::write_qa(std::string time, const fs::path filePath, fs::path destPath, Infected& inf) {
    // add to quarantine
    file << current_time() << " [QRN] Added to quarantine: \n"
            << "  ├─ File: " << filePath << "\n"
            << "  ├─ Moved to: " << destPath << "\n";
    std::ostringstream hex_stream;
    hex_stream << std::hex << std::setfill('0');
    for (const auto& byte : inf.signature->pattern) {
        hex_stream << std::setw(2) << static_cast<int>(byte) << " ";
    }
    file << "  └─ Signature: " << hex_stream.str() << " ("
            << inf.signature->name << ")\n";
}

void Logger::write_e(std::string e) { // тут переделать тип под общий тип ошибок
    // error output
    file << current_time() << " [ERR] Error: " << e << "\n";
}

void Logger::write_qr(const fs::path& qFile, const fs::path& originalPath) {
    // reload from quarantine
    file << current_time() << " [QRN] Restored from quarantine: \n"
            << "  ├─ From quarantine: " << qFile << "\n"
            << "  └─ To location: " << originalPath << "\n";
}

void Logger::write_a(CheckResult& result, std::string filename) {
    // info about checked file (searched or no)
    file << current_time() << " [SCN] Scanned file: "
            << (result.is_infected ? "infected" : "clean") << " | "
            << "File: " << filename << "\n";
}

void Logger::write_d(std::string directory, int count_files, int count_dirs) {
    // start directory info
    file << std::string(80, '~') << "\n" 
            << current_time() << " [DIR] Directory info: \n"
            << "  ├─ Path: " << directory << "\n"
            << "  ├─ Files: " << count_files << "\n"
            << "  └─ Dirs: " << count_dirs << "\n"
            << std::string(80, '~') << "\n\n";
}

void Logger::write_vir(std::vector<Infected> inf) {
    int i = 1;
    file << "\n" << current_time() << " [VIR] Infected files:\n";
    for (auto& f : inf) {
        file << "  " << i << ") " << f.filename << " -> " << f.signature->description << "\n";
        i++;
    }
    file << "\n";
}

void Logger::write_vir0() {
    file << "\n" << current_time() << " [VIR] No one file in infected!\n\n";
}

void Logger::close_file() {
    file << "\n" << std::string(80, '=') << "\n";
    file << current_time() << " CLOSE LOGGER FILE!";
    file << "\n" << std::string(80, '=') << "\n";
    file.close();
}

// void write_d_q(std::vector<Infected> removed, std::vector<Infected> quarantined) {
    
// }