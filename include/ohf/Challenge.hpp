//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_CHALLENGE_HPP
#define OKHTTPFORK_CHALLENGE_HPP

#include "string"

namespace ohf {
    class Challenge {
    public:
        bool operator==(const Challenge &challenge);

        std::string realm();

        std::string scheme();
    };
}

#endif //OKHTTPFORK_CHALLENGE_HPP
