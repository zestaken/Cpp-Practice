#include <iostream>

#include "../include/SpeechManger.h"

using namespace std;

int main() {

    //静态方法通过类直接调用（使用::）运算符
     SpeechManger::showMenu();
     SpeechManger sm;

    //while(true) 加上switch不断读取用户输入，并进入分支流程，直到用户选择退出
    while (true)
    {
        cout << "请输入你的选择：";
        int cmd = 0;
       cin >> cmd;
        switch (cmd)
        {
            case 1:
                //进行比赛
                sm.startCompetition();
                break;
            case 2:
                // 查看往届结果
                break;
            case 3:
                // 清空比赛结果
                break;
            case 4:
                // 退出比赛程序
                SpeechManger::exitSystem();
                break;
            default:
                cout << "请输入，1，2，3，4进行选择" << endl;
                break;
        }
        break;
    }

    return 0;
}