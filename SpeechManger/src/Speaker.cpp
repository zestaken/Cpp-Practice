//
// Created by Zestaken on 2024/4/24.
//

#include <utility>

#include "../include/Speaker.h"
using namespace  std;

Speaker::Speaker(string name) {
    this->name = std::move(name); //name只使用一次，赋值后即丢弃，使用move
}

