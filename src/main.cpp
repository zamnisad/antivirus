#include <Windows.h>
#include <ZamniVirus/Analyzers/Scanner.h>


void process(const std::string& logPath, const std::string& scanDir, const std::string& quarantineDir, const std::string& signatureFile) {
    Logger logger(logPath);
    SignatureManager signatureManager(logger);

    signatureManager.load_signatures(signatureFile);
    
    DirWork dirWork(scanDir, logger);
    FileAnalyzer fileAnalyzer(signatureManager, logger);
    Scanner scanner(dirWork, fileAnalyzer, logger);
    
    scanner.scan();

    std::vector<ScanResult> result = scanner.get_results();
    VirusManager vm(result, logger);
    QuarantineManager qm(vm, quarantineDir);
    DeleteManager dm(vm);

    if (!result.empty()) {
        vm.choose_actions();
        qm.add_files();
        dm.delete_files();
        logger.print_deleted_quarantined(vm.get_removed(), vm.get_quarantined());
    }

    logger.close_file();
    std::cout << "Scanning process completed!" << std::endl;
}

int main(int argc, char* argv[]) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " <log_path> <scan_directory> <quarantine_directory> <signature_file>" << std::endl;
        return 1;
    }

    std::string logPath = argv[1];
    std::string scanDir = argv[2];
    std::string quarantineDir = argv[3];
    std::string signatureFile = argv[4];

    process(logPath, scanDir, quarantineDir, signatureFile);
    return 0;
}
