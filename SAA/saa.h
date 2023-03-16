#pragma once

#include "common/common.h"

#define T0 100 //初始温度
#define alpha 0.99 //温度衰减系数
#define ex_explore //温度归零的额外探索回合数

class SAA {
public:
    SAA() {
        init_random_sequence();
    }

    SAA(unsigned int seed) {
        init_random_sequence(seed);
    }

    ~SAA() {}

    SAA& operator = (const SAA& o) = delete;

private:
};