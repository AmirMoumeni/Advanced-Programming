#include "FlashCard.h"
#include <iostream>
using namespace std;

void FlashCard::addQuestion(string str) {
    question = str;
}

void FlashCard::addAnswers(string str) {
    answer = str;
}

void FlashCard::report() {
    cout << "Question : " << question << endl
              << "Answer : " << answer << endl
              << "Number of Total Reviews : " << numOfReview << endl
              << "Day of Next Review : " << dayOfnextReview << endl
              << "-----------------------" << endl;
}

string FlashCard::showQuestion() {
    return question;
}

string FlashCard::showAnswer() {
    return answer;
}

void FlashCard::setDayOfReview(int dayNum) {
    dayOfnextReview = dayNum;
}

void FlashCard::reviewed(int dayNum) {
    if (numOfReview == 0) {
        if (dayNum % 3 == 0) {
            dayOfnextReview = dayNum + 3;
        } else if (dayNum % 7 == 0) {
            dayOfnextReview = dayNum + 7;
        } else if (dayNum % 30 == 0) {
            dayOfnextReview = dayNum + 30;
        } else {
            dayOfnextReview = ((dayNum / 3) * 3) + 3;
        }
    } else if (numOfReview == 1) {
        if (dayNum % 7 == 0) {
            dayOfnextReview = dayNum + 7;
        } else if (dayNum % 30 == 0) {
            dayOfnextReview = dayNum + 30;
        } else {
            dayOfnextReview = ((dayNum / 7) * 7) + 7;
        }
    } else if (numOfReview == 2) {
        if (dayNum % 30 == 0) {
            dayOfnextReview = dayNum + 30;
        } else {
            dayOfnextReview = ((dayNum / 30) * 30) + 30;
        }
    } else if (numOfReview >= 3) {
        dayOfnextReview = 0;
    }
    numOfReview++;
    numOfWrongAnswer = 0;
}

int FlashCard::dayStatus() {
    return dayOfReview;
}

void FlashCard::setDay(int dayNum) {
    dayOfReview = dayNum;
}

int FlashCard::reviewStatus() {
    return numOfReview;
}

void FlashCard::demoted() {
    numOfWrongAnswer = 0;
    numOfReview--;
}
