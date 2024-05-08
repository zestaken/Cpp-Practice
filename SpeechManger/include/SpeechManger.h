//
// Created by Zestaken on 2024/4/23.
//

#pragma once //防止多次包含
#include <iostream>
#include <vector>
#include <map>
#include "Speaker.h"

using namespace std;

class SpeechManger
{
private:
    vector<int> all_speaker_ids; //第一轮存储所有比赛选手的编号（顺序就是比赛抽签的顺序）
    vector<int> second_speaker_ids; //存储第二轮比赛选手的编号
    map<int, Speaker*> id_speaker; // 存储所有比赛选手的编号与比赛选手对象的对应关系
    multimap<float, Speaker*> victor; //存储胜利者的信息(成绩和胜利选手)
    int index; //记录是第几轮比赛

public:
    static void  showMenu(); // 静态方法可以直接通过类来调用
    static void exitSystem();
    void initAttr();
    void createSpeakers();
    void drawLots();
    void startCompetition();
    void speechContest();
    void saveRecord();
    void readRecord();
    SpeechManger(); //构造函数
    ~SpeechManger(); //析构函数
};