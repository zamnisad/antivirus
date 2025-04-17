#pragma once
#include <ZamniVirus/FileManager/VirusManager.h>


VirusManager::VirusManager(std::vector<ScanResult> results, Logger& logger) : logger(logger) {
    add_to_infected(results);
    if (!infected.empty()) {
        logger.write_vir(infected);
        logger.print_infected_all(infected);
    }
    else {
        logger.write_vir0();
        logger.print_infected_not();
    }
}

void VirusManager::choose_actions() {
    auto read_numbers = [](const std::string& prompt) {
        std::cout << prompt;
        std::string input;
        std::getline(std::cin, input);
        
        std::vector<int>* numbers;
        std::istringstream iss(input);
        int num;
        
        while (iss >> num) {
            numbers->push_back(num);
        }
        
        return numbers;
    };
    logger.print_choose_files(0);
    auto remove_nums = read_numbers("");

    check_err(remove_nums);

    logger.print_choose_files(1);
    auto quarantine_nums = read_numbers("");

    check_err(quarantine_nums);

    std::set<int> remove_set(remove_nums->begin(), remove_nums->end());
    std::set<int> quarantine_set(quarantine_nums->begin(), quarantine_nums->end());

    std::vector<int> intersection;
    std::set_intersection(
        remove_set.begin(), remove_set.end(),
        quarantine_set.begin(), quarantine_set.end(),
        std::back_inserter(intersection)
    );

    if (!intersection.empty()) {
        logger.print_both_numbers(intersection);
    
        remove_nums->erase(
            std::remove_if(remove_nums->begin(), remove_nums->end(), [&](int x) {
                return quarantine_set.count(x) > 0;
            }),
            remove_nums->end()
        );
    }

    logger.print_result_lists(*remove_nums, *quarantine_nums);

    for (int idx : *remove_nums) {
        to_remove.push_back(infected[idx - 1]);
    }
    for (int idx : *quarantine_nums) {
        to_quarantine.push_back(infected[idx - 1]);
    }
}

void VirusManager::check_err(std::vector<int>* nums) {
    if (nums->back() == -1) {
        nums->pop_back();
        for (int inf = 1; inf < infected.size() + 1; inf++) {
            nums->push_back(inf);
        }
    }
    else {
        nums->erase(
            std::remove_if(
                nums->begin(),
                nums->end(),
                [&](int idx){
                    return idx < 1 || idx > static_cast<int>(infected.size());
                }
            ),
            nums->end()
        );
    }
}

void VirusManager::add_to_infected(std::vector<ScanResult> results) {
    for (auto r : results) {
        if (r.is_infected) {
            Infected temp = Infected(r.filename, r.file_size, r.signature, r.date);
            infected.push_back(temp);
        }
    }
}
    