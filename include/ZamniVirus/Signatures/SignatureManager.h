#pragma once
#include <array>
#include <ZamniVirus/Filesystem/DirWork.h>


class SignatureManager : Error {
private:
    std::vector<VirusSignature> signatures;
    static const size_t BUFFER_SIZE = 1024 * 1024;
    Logger& logger;
public:
    SignatureManager(Logger& logger) : logger(logger) {}

    void load_signatures(const std::string& filename);
    CheckResult check_signature(const std::string& filename);
private:
    bool bmh_search(const std::vector<uint8_t>& text, const std::vector<uint8_t>& pattern);
    std::vector<uint8_t> hexToBytes(const std::string& hex);
    bool containsPattern(const std::vector<uint8_t>& data, const std::vector<uint8_t>& pattern);
};
    