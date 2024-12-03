#ifndef BOXES_H
#define BOXES_H

#include <vector>
#include "FlashCard.h"
using namespace std;
class Boxes
{
public:
    vector<FlashCard> dailyBox;
    vector<FlashCard> per3DayBox;
    vector<FlashCard> perWeekBox;
    vector<FlashCard> perMonthBox;
    vector<FlashCard> mastered;
    vector<FlashCard> allCards;
};

#endif 