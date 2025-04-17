#pragma once
#include <cstdint>
#include <string>
#include <vector>


struct VirusSignature {
    std::vector<uint8_t> pattern;
    std::string name;              
    std::string description;

    VirusSignature() = default;
};

struct ScanResult {
    bool is_infected;

    std::string filename;
    std::size_t file_size;

    VirusSignature* signature = nullptr; 

    std::string date;
};

struct Infected {
    std::string filename;
    std::size_t file_size;

    VirusSignature* signature = nullptr; 

    std::string date;

    Infected() {};
    Infected(std::string fn, std::size_t fs, VirusSignature* s, std::string d) : filename(fn), file_size(fs), signature(s), date(d) {};
};

struct CheckResult {
    bool is_infected;
    VirusSignature* signature; 

    CheckResult() : is_infected(false), signature(nullptr) {}
};