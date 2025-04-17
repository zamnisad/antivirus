#pragma once
#include <string>
#include <iostream>
#include <ZamniVirus/Errors/Error.h>


std::string Error::dir_not_found(std::string dir) {
    std::string e = "Directory " + dir + " not found!";
    return e;
}

std::string Error::file_not_found_in_vector(std::string filename) {
    std::string e = "File " + filename + " not found in infected!";
    return e;
}

std::string Error::q_add_failed(std::string filename) {
    std::string e = "Quarantine failed while store file " + filename + "!";
    return e;
}

std::string Error::q_restore_failed(std::string filename) {
    std::string e = "Quarantine filed while restore file " + filename + "!";
    return e;
}

std::string Error::file_not_exists(std::string filename) {
    std::string e = "File " + filename + " not exists!";
    return e;
}

std::string Error::signature_file_not_open(std::string filename) {
    std::string e = "Unable to open signature file " + filename + "!";
    return e;
}

std::string Error::file_not_open(std::string filename) {
    std::string e = "Unable to open file " + filename + "!";
    return e;
}

std::string Error::file_not_read(std::string filename) {
    std::string e = "Unable to read file " + filename + "!";
    return e; 
}


std::string Error::get_error(int type, std::string name) {
    switch (type) {
        case 1:
            return dir_not_found(name);
            break;
        case 2:
            return file_not_found_in_vector(name);
            break;
        case 3:
            return q_add_failed(name);
            break;
        case 4:
            return q_restore_failed(name);
            break;
        case 5:
            return file_not_exists(name);
            break;
        case 6:
            return signature_file_not_open(name);
            break;
        case 7:
            return file_not_open(name);
            break;
        case 8:
            return file_not_read(name);
            break;
        default:
            std::cerr << "Not founded type" << std::endl;
            exit(1);
    }
}