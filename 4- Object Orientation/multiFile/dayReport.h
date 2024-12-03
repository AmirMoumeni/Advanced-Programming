#ifndef DAYREPORT_H
#define DAYREPORT_H

class dayReport
{
public:
    int correctAnswer = 0;
    int wrongAnswer = 0;
    int totalAnswer()
    {
        return correctAnswer + wrongAnswer;
    }
};

#endif 
