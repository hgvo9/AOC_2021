#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int main(void) {
    //std::cout << "Hello World" << std::end;
    std::fstream newfile;
    std::vector<int> depths;
    int three_measurement_window = 3;
    int firstSum = 0;
    int secondSum = 0;
    int oldSum = 0;
    int increased = 0;

    newfile.open("puzzle_input", std::ios::in);
    if(newfile.is_open()) {
        std::string line;
        
        while(getline(newfile, line)) {
            depths.push_back(std::stoi(line));
        }
    }

    for (int i = 3; i < depths.size(); i++) {
        firstSum = depths[i - 1];
        secondSum = depths[i];
        for (int j = 2; j <= three_measurement_window; j++) {
            firstSum += depths[i - j];
        }
        for (int x = 1; x < three_measurement_window; x++) {
            secondSum += depths[i - x];
        }
        if (secondSum > firstSum)
            increased++;

    }

    std::cout << "Increased: " << increased << std::endl;

    return 0;
}
