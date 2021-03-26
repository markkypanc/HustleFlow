#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
using namespace std;

class K {
private:
    // API key for OpenWeather provider
    string MY_API_KEY = "7133d90209f5ddf5b5ced05dcb7c34e9";

public:
    K();

    string getApiKey() {
        return this->MY_API_KEY;
    }
};

#endif // CONSTANTS_H
