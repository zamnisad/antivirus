#pragma once
#include <string>
#include <iostream>


class Error {
private:
    static std::string dir_not_found(std::string dir);
    static std::string file_not_found_in_vector(std::string filename);
    static std::string q_add_failed(std::string filename);
    static std::string q_restore_failed(std::string filename);
    static std::string file_not_exists(std::string filename);
    static std::string signature_file_not_open(std::string filename);
    static std::string file_not_open(std::string filename);
    static std::string file_not_read(std::string filename);
public:
    static std::string get_error(int type, std::string name);
};