//
// Created by Zestaken on 2024/4/23.
//
#include "../include/SpeechManger.h"
#include "../include/Speaker.h"
#include <algorithm>

void SpeechManger::showMenu() {
    // 提供初始界面和初始输入判断
    cout << "欢迎来到演讲比赛管理程序" << endl;
    cout << "按1：进行比赛" << endl;
    cout << "按2：查看往届结果" << endl;
    cout << "按3：清空比赛结果" << endl;
    cout << "按4：退出比赛程序" << endl;
}

void SpeechManger::exitSystem() {
    //退出程序
    cout << "欢迎下次使用" << endl;
    system("pause");
    exit(0);
}

void SpeechManger::initAttr() {
    //初始化speechManger的属性，即清空所有容器
    this->all_speaker_ids.clear();
    this->id_speaker.clear();
    this->second_speaker_ids.clear();
    this->index = 1; //初始为1，从第一轮比赛开始
}

void SpeechManger::createSpeakers() {
    //创建speaker对象，设置其名字，并存入容器中
    int speakerNum = 12;
    string base_name = "speaker_";
    for (int i = 1; i <= speakerNum; i++){
        string name = base_name + to_string(i);
        auto sp = new Speaker(name);
        this->all_speaker_ids.insert(all_speaker_ids.end(),i);
        this->id_speaker.insert(make_pair(i,sp));
    }
}
void SpeechManger::drawLots() {
    //打乱id列表的顺序，实现抽签的功能
    cout << "第" << this->index << "轮比赛选手正在抽签......\n";
    cout << "---------------------------------------" << endl;
    random_shuffle(this->all_speaker_ids.begin(), this->all_speaker_ids.end());
    int i = 1;
    cout << "抽签结果如下：" << endl;
    for (auto iter = this->all_speaker_ids.begin(); iter != this->all_speaker_ids.end(); iter++, i++) {
        int id = *iter;
        string name = this->id_speaker[id]->name;
        cout << "No." << i << ": " << name << "; ";
        if (i % 3 == 0)
            cout << endl;
    }

}

void SpeechManger::startCompetition() {
    //完成比赛的逻辑

    //第一轮比赛
    //1. 抽签/
    this->drawLots();
    //2. 比赛
    //3. 显示晋级结果

    //第二轮比赛
    //1.抽签
    //2. 比赛
    //3.显示最终结果
    //4. 保存结果到文件中
}

SpeechManger::SpeechManger()
{
    this->initAttr();
    this->createSpeakers();
    cout << "SpeechManger构造成功" << endl;
}

SpeechManger::~SpeechManger()
{
    cout << "SpeechManger退出成功" << endl;
}