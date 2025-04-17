#pragma once
#include <set>
#include <ZamniVirus/Analyzers/FileAnalyzer.h>


class VirusManager : Error {
private:
    std::vector<Infected> infected;
    std::vector<Infected> to_quarantine;
    std::vector<Infected> to_remove;
    Logger& logger;

    friend class QuarantineManager;
    friend class DeleteManager;
public:
    VirusManager(std::vector<ScanResult> results, Logger& logger);
    void choose_actions();
    std::vector<Infected> get_removed() { return this->to_remove; };
    std::vector<Infected> get_quarantined() { return this->to_quarantine; };

private:
    void check_err(std::vector<int>* nums);
    void add_to_infected(std::vector<ScanResult> results);
};
    