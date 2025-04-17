#pragma once
#include <ZamniVirus/FileManager/DeleteManager.h>


void DeleteManager::delete_files() {
    for (auto& file : vm.to_remove) {
        fs::remove(fs::absolute(file.filename));
    }
}