#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

std::string gammaStr,epsilonStr;
int gammaDec, epsiDec;

std::vector<std::string> erase_bit_at_pos(int pos, std::vector<std::string> bitArray, char bitToErase) {
    for (auto it = bitArray.begin(); it != bitArray.end();) {
        std::string str = std::string(it->c_str());

        if (str[pos] == bitToErase)
            it = bitArray.erase(it);
        else
            it++;
    }
    return bitArray;
}

void get_gamma_epsilon(const std::vector<std::string> posArray, bool isOxygen) {
    int nb_1 = 0;
    int nb_0 = 0;
    int x = 0;
    std::vector<std::string> tmpArray(posArray);
    bool keepGoing = true;

    while (keepGoing) {
        for (auto it = tmpArray.begin(); it != tmpArray.end(); it++) {
            std::string test = std::string(it->c_str());

            if (test[x] == '1')
                nb_1++;
            else if (test[x] == '0')
                nb_0++;
        }
        
        if (isOxygen) {
            if (nb_1 > nb_0)
                tmpArray = erase_bit_at_pos(x, tmpArray, '0');
            else if (nb_1 < nb_0)
                tmpArray = erase_bit_at_pos(x, tmpArray, '1');
            else if (nb_1 == nb_0)
                tmpArray = erase_bit_at_pos(x, tmpArray, '0');
        } else {
            if (nb_1 > nb_0)
                tmpArray = erase_bit_at_pos(x, tmpArray, '1');
            else if (nb_1 < nb_0)
                tmpArray = erase_bit_at_pos(x, tmpArray, '0');
            else if (nb_1 == nb_0)
                tmpArray = erase_bit_at_pos(x, tmpArray, '1');
        }



        if (tmpArray.size() <= 1) {
            // std::cout << tmpArray[0] << std::endl;
            std::cout << "\n---" << x << "----\n" << std::endl;
            if (isOxygen)
                std::cout << "OXYGEN" << std::endl;
            else
                std::cout << "C02" << std::endl;
            std::cout << "nb_1: " << nb_1 << std::endl;
            std::cout << "nb_0: " << nb_0 << std::endl;
            std::cout << "arraysize: " << tmpArray.size() << std::endl;

            for (int t = 0; t < tmpArray.size(); t++)
                std::cout << tmpArray[t] << std::endl;
            std::cout << "\n------\n" << std::endl;
            isOxygen ? gammaStr = tmpArray[0] : epsilonStr = tmpArray[0];
            keepGoing = false;
        }
        nb_1 = 0;
        nb_0 = 0;
        x++;
    }
}

int main(void) {
    //std::cout << "Hello World" << std::end;
    std::fstream newfile;
    std::vector<std::string> posArray;

    newfile.open("puzzle_input", std::ios::in);
    if(newfile.is_open()) {
        std::string line;
        
        while(getline(newfile, line)) {
            posArray.push_back(line);
        }

        get_gamma_epsilon(posArray, 1);
        get_gamma_epsilon(posArray, 0);

        int pow = gammaStr.size() - 1;
        for (int i = 0; i < gammaStr.size(); i++) {
            gammaDec += ((gammaStr[i] - 48) * std::pow(2, pow));
            pow--;
        }

        pow = epsilonStr.size() - 1;
        for (int i = 0; i < epsilonStr.size(); i++) {
            epsiDec += ((epsilonStr[i] - 48) * std::pow(2, pow));
            pow--;
        }

        std::cout << "Gammaval : " << gammaDec << std::endl;
        std::cout << "Epsival : " << epsiDec << std::endl;
        std::cout << "Final: " << gammaDec * epsiDec << std::endl;
    }

    return 0;
}
