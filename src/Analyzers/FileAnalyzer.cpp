#pragma once
#include <ZamniVirus/Analyzers/FileAnalyzer.h>


ScanResult FileAnalyzer::scan_file(const std::string& filename) {
    ScanResult result;
    result.filename = filename;
    result.file_size = fs::file_size(filename);
    CheckResult cr = signatureManager.check_signature(filename);
    result.is_infected = cr.is_infected;
    result.signature = cr.signature;

    logger.write_a(cr, result.filename);
    return result;
}
