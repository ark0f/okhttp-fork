//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_CHALLENGE_HPP
#define OKHTTPFORK_CHALLENGE_HPP

namespace ohf {
    class Challenge {
    public:
        bool operator==(const Challenge &challenge);

        const char *realm();

        const char *scheme();
    };
}

#endif //OKHTTPFORK_CHALLENGE_HPP
