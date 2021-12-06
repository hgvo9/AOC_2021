#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <functional>
#include <unordered_map>

int horizontal,depth,aim,units = 0;
std::string direction;
typedef void (*callbackFunction)(const int);

void forward(const int val) {
    std::cout << "Forward" << std::endl;
    horizontal += val;
    aim != 0 ? depth += aim*val: depth;
}

void down(const int val) {
    std::cout << "Down" << std::endl;
    aim += val;
}

void up(const int val) {
    std::cout << "Up" << std::endl;
    aim -= val;
}

int main(void) {
    std::fstream newfile;
    std::map<std::string, callbackFunction> pointerFunction ;

    pointerFunction.emplace("forward", &forward);
    pointerFunction.emplace("down", &down);
    pointerFunction.emplace("up", &up);

    newfile.open("puzzle_input", std::ios::in);
    if(newfile.is_open()) {
        std::string line;
        
        while(getline(newfile, line)) {
            direction = line.substr(0, line.find(" "));
            units = std::stoi(line.substr(line.find(" ")+1));
            pointerFunction[direction](units);
        }
    }

    std::cout << "Horizontal Value: " << horizontal << " | Depth value" << depth << " | aim value: " << aim << std::endl;
    std::cout << horizontal * depth << std::endl;
    return 0;
}
