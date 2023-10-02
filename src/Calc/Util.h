#ifndef _CALC_UTIL_H_
#define _CALC_UTIL_H_

#define ASSERT_HAS_VALUE_RETURN(value)      do { if (!(value).has_value()) return; } while(0)
#define ASSERT_HAS_VALUE_PROPAGATE(value)   do { if (!(value).has_value()) return (value); } while(0)


namespace Calc {

    unsigned constexpr Hash(char const *input) {
        return *input ?
            static_cast<unsigned int>(*input) + 33 * Hash(input + 1) :
            5381;
    }

}


#endif