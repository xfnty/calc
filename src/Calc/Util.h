#ifndef _CALC_UTIL_H_
#define _CALC_UTIL_H_


namespace Calc {

    unsigned constexpr Hash(char const *input) {
        return *input ?
            static_cast<unsigned int>(*input) + 33 * Hash(input + 1) :
            5381;
    }

}


#endif