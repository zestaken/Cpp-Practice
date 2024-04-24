//
// Created by Zestaken on 2024/4/24.
//

#ifndef SPEECHMANGER_SPEAKER_H
#define SPEECHMANGER_SPEAKER_H

#include <iostream>

using namespace  std;

class Speaker
{
public:
    string name; //选手的姓名
    double scores[2]; //选手两轮比赛的分数
    Speaker(string name);
};


#endif //SPEECHMANGER_SPEAKER_H
