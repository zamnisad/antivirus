#pragma once
#include <ZamniVirus/Signatures/SignatureManager.h>


void SignatureManager::load_signatures(const std::string& filename) {
    logger.write_start("Signature");
    std::ifstream sigFile(filename);

    if (sigFile.is_open()) {
        std::string line;
        while (std::getline(sigFile, line)) {
            size_t delim1 = line.find(';');
            size_t delim2 = line.find(';', delim1+1);

            VirusSignature sig;
            if (delim1 != std::string::npos && delim2 != std::string::npos) {
                sig.pattern = hexToBytes(line.substr(0, delim1));
                sig.name = line.substr(delim1+1, delim2-delim1-1);
                sig.description = line.substr(delim2+1);
                signatures.push_back(sig);
            }
        }
        logger.write_end("Signature");
    }
    else {
        logger.write_e(get_error(6, filename));
        std::cerr << "Error: Unable to open signature file." << std::endl;
        exit(1);
    }
}

CheckResult SignatureManager::check_signature(const std::string& filename) {
    CheckResult result;
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        logger.write_e(get_error(7, filename));
        std::cerr << "Error: Unable to open file: " << filename << std::endl;
        return result;
    }

    const std::streamsize chunk_size = 1024 * 1024 * 2; // 2 MB блоки
    std::vector<uint8_t> buffer(chunk_size);
    std::vector<uint8_t> prev_block_end;

    while (file) {
        std::fill(buffer.begin(), buffer.end(), 0);
        file.read(reinterpret_cast<char*>(buffer.data()), chunk_size);
        std::streamsize bytes_read = file.gcount();

        if (!prev_block_end.empty()) {
            std::copy(prev_block_end.begin(), prev_block_end.end(), buffer.begin());
            prev_block_end.clear();
            bytes_read += prev_block_end.size();
        }

        for (const auto& sig : signatures) {
            if (sig.pattern.empty()) continue;

            if (bmh_search(buffer, sig.pattern)) {
                result.is_infected = true;
                result.signature = const_cast<VirusSignature*>(&sig);
                break;
            }
        }

        if (result.is_infected) {
            break;
        }

        std::size_t bytes_to_save = min(bytes_read, static_cast<std::streamsize>(chunk_size));
        prev_block_end.insert(prev_block_end.end(), buffer.end() - bytes_to_save, buffer.end());
    }

    return result;
}

bool SignatureManager::bmh_search(const std::vector<uint8_t>& text, const std::vector<uint8_t>& pattern) {
    size_t t_len = text.size();
    size_t p_len = pattern.size();

    if (p_len == 0 || t_len < p_len)
        return false;

    // Таблица сдвигов
    std::array<std::size_t, 256> shift_table;
    shift_table.fill(p_len);

    for (size_t i = 0; i < p_len - 1; ++i) {
        shift_table[pattern[i]] = p_len - 1 - i;
    }

    size_t i = 0;
    while (i <= t_len - p_len) {
        size_t j = p_len - 1;
        while (text[i + j] == pattern[j]) {
            if (j == 0) return true;  // Совпадение найдено
            --j;
        }
        i += shift_table[text[i + p_len - 1]];
    }

    return false;
}

std::vector<uint8_t> SignatureManager::hexToBytes(const std::string& hex) {
    std::vector<uint8_t> bytes;
    for (size_t i = 0; i < hex.length(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        bytes.push_back(static_cast<uint8_t>(strtol(byteString.c_str(), nullptr, 16)));
    }
    return bytes;
}

bool SignatureManager::containsPattern(const std::vector<uint8_t>& data, const std::vector<uint8_t>& pattern) {
    return std::search(
        data.begin(), data.end(),
        pattern.begin(), pattern.end()
    ) != data.end();
}
    