#pragma once
#include <ZamniVirus/Signatures/SignatureManager.h>


class FileAnalyzer{
    private:
        SignatureManager signatureManager;
        Logger& logger;
    public:
        FileAnalyzer(SignatureManager sm, Logger& logger) : signatureManager(sm), logger(logger) {};
        ScanResult scan_file(const std::string& filename);
    };
    