//
// Created by Zestaken on 2024/4/23.
//
#include "../include/SpeechManger.h"
#include "../include/Speaker.h"
#include <algorithm>
#include <deque>
#include <random>
#include <functional>
#include <ranges>

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

    if (this->index == 1) {
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
    else {
        cout << "第" << this->index << "轮比赛选手正在抽签......\n";
        cout << "---------------------------------------" << endl;
        random_shuffle(this->second_speaker_ids.begin(), this->second_speaker_ids.end());
        int i = 1;
        cout << "抽签结果如下：" << endl;
        for (auto iter = this->second_speaker_ids.begin(); iter != this->second_speaker_ids.end(); iter++, i++) {
            int id = *iter;
            string name = this->id_speaker[id]->name;
            cout << "No." << i << ": " << name << "; ";
            if (i % 3 == 0)
                cout << endl;
        }
    }


}

void SpeechManger::speechContest() {
    //如果是第一轮比赛，将选手分为每6人一组
    //随机为每个选手打分，模拟裁判打分(裁判有10位，每个选手将有10个得分，去除最高分和最低分之后，得到的平均分为总分）
    //如果是第一轮比赛，每个组的前三名晋级
    // 如果是第二轮比赛，组的前三名赢得最终胜利

    //构建c++11标准的随机数生成函数
    random_device rd;  //用于产生随机数种子
    auto gen = default_random_engine(rd()); //构建生成随机数的引擎
    uniform_real_distribution<float> dis(60, 100); //指定随机数生成的分布
    auto randFunc = bind(dis, gen);
    vector<int> speakers;
    if (this->index == 1) {
        speakers = this->all_speaker_ids;
        //因为key值是分数，有可能重复，所以使用允许key重复的multimap
        multimap<float, int> score_id_1; //存储第一组每个选手的分数和编号的对应关系，可根据score的key值进行排序
        multimap<float, int> score_id_2; //第二组
        // 为每个参赛选手打分并存储
        int speaker_num = 0;
        for (auto iter = speakers.begin(); iter != speakers.end(); iter++, speaker_num++) {
            deque<float> scores;
            for (int i = 0; i < 10; i++) {
                float score = randFunc(); //生成0-100之间0的浮点随机数
                scores.push_back(score);
            }
            sort(scores.begin(), scores.end()); //进行分数从小到大排序
            scores.pop_back();
            scores.pop_front(); //去掉首尾最高和最低分
            float avg_score = accumulate(scores.begin(), scores.end(), 0) / scores.size();
            if (speaker_num < 6) {
                //不同组的选手的成绩存入不同的容器中
                score_id_1.insert(make_pair(avg_score, *iter));
            } else {
                score_id_2.insert(make_pair(avg_score, *iter));
            }
        }
        //两组选手按照成绩排序，选出前三名
        int j = 1;
        cout << "第 1 组比赛成绩：" << endl;
        //反向遍历map，从大到小获取成绩
        for (auto & iter1 : std::ranges::reverse_view(score_id_1)) {
            if (j <= 3)
                this->second_speaker_ids.insert(this->second_speaker_ids.end(), iter1.second);
            cout << "No." << j << ": 编号： " << iter1.second << ", 姓名： " << this->id_speaker[iter1.second]->name
                 << ", 成绩： ";
            cout << iter1.first << endl;
            j++;
        }
        j = 1;
        cout << "第 2 组比赛成绩：" << endl;
        for (auto & iter2 : std::ranges::reverse_view(score_id_2)) {
            if (j <= 3)
                this->second_speaker_ids.insert(this->second_speaker_ids.end(), iter2.second);
            cout << "No." << j << ": 编号： " << iter2.second << ", 姓名： " << this->id_speaker[iter2.second]->name << ", 成绩： ";
            cout << iter2.first << endl;
            j++;
        }
        }
    else {
        //第二轮比赛
        speakers = this->second_speaker_ids;
        multimap<float, int> score_id;
        // 为每个参赛选手打分并存储
        int speaker_num = 0;
        for (auto iter = speakers.begin(); iter != speakers.end(); iter++, speaker_num++) {
            deque<float> scores;
            for (int i = 0; i < 10; i++) {
                float score = randFunc(); //生成0-100之间0的浮点随机数
                scores.push_back(score);
            }
            sort(scores.begin(), scores.end()); //进行分数从小到大排序
            scores.pop_back();
            scores.pop_front(); //去掉首尾最高和最低分
            float avg_score = accumulate(scores.begin(), scores.end(), 0) / scores.size();
            //将该选手的成绩插入score_id 映射中
            score_id.insert(make_pair(avg_score, *iter));
        }
        int j = 1;
        cout << "最终比赛成绩：" << endl;
        //使用rbegin的反向遍历方式。
        for (auto iter1 = score_id.rbegin(); iter1 != score_id.rend(); iter1++) {
            if (j <= 3)
                //存储最终胜利者信息
                this->victor.insert(make_pair(iter1->first, id_speaker[iter1->second]));
            cout << "No." << j << ": 编号： " << iter1->second << ", 姓名： " << this->id_speaker[iter1->second]->name << ", 成绩： ";
            cout << iter1->first << endl;
            j++;
        }
    }
}

void SpeechManger::startCompetition() {
    //完成比赛的逻辑

    //第一轮比赛
    //1. 抽签/
    this->drawLots();
    //2. 比赛
    this->speechContest();
    //3. 显示晋级结果

    this->index++;
    //第二轮比赛
    //1.抽签
    this->drawLots();
    //2. 比赛
    this->speechContest();
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