#ifndef FLASHCARD_H
#define FLASHCARD_H

#include <string>
using namespace std;

class FlashCard
{
private:
    string question;
    string answer;
    int numOfReview = 0;
    int dayOfReview = 0;

public:
    void addQuestion(string str);
    void addAnswers(string str);
    void report();
    string showQuestion();
    string showAnswer();
    void setDayOfReview(int dayNum);
    void reviewed(int dayNum);
    int dayStatus();
    void setDay(int dayNum);
    int reviewStatus();
    void demoted();
    
    int numOfWrongAnswer = 0;
    bool isReviewedToday = false;
    int dayOfnextReview;
};

#endif 
