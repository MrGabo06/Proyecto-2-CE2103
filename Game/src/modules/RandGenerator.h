#ifndef RANDGENERATOR_H
#define RANDGENERATOR_H

#include <random>
#include <math.h>

class Generator {
public:
    Generator(){};

    int generateInt(int lower_bound, int upper_bound){
        int result  = 0;

        // Number generation
        std::random_device rd;
        std::mt19937 gen(rd());
        if ( lower_bound < upper_bound){
            std::uniform_int_distribution<int> dist(std::abs(lower_bound), std::abs(upper_bound));
            result = dist(gen);
        } else if (lower_bound > upper_bound){
            std::uniform_int_distribution<int> dist(std::abs(upper_bound), std::abs(lower_bound));
            result = dist(gen);
        }
        // Make negatives
        if (lower_bound < 0 || upper_bound < 0){
            std::uniform_int_distribution<int> dist(0,1);
            int negator = dist(gen);
            if (negator == 0){
                result *= -1;
            }
        }

        return result;
    }
};


#endif //RANDGENERATOR_H