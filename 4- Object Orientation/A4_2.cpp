#include <iostream>
#include <vector>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

const string ADD_FLASHCARD = "add_flashcard";
const string REPORT = "report";
const string REVIEW_TODAY = "review_today";
const string SUCCESFULL_ADD_MESSAGE = "flashcards added to the daily box\n";
const string CORRECT_ANSWER_MESSAGE = "Your answer was correct! Well done, keep it up!\n";
const string WRONG_ANSWER_MESSAGE = "Your answer was incorrect. Don't worry! The correct answer is: ";
const string TEST_FINISH_MESSAGE = "You’ve completed today’s review! Keep the momentum going and continue building your knowledge, one flashcard at a time!\n";
const string KEEP_PRACTICING = ". Keep practicing!\n";
const string NEXT_DAY = "next_day";
const string INCREASE = "increase";
const string RESET = "reset";
const string STREAK = "streak";
const string GET_REPORT = "get_report";
const string GET_PROGRESS_REPORT = "get_progress_report";

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

class FlashCard
{
private:
    string question;
    string answer;
    int numOfReview = 0;
    int dayOfReview = 0;

public:
    void addQuestion(string str)
    {
        question = str;
    }
    void addAnswers(string str)
    {
        answer = str;
    }
    void report()
    {
        cout << "Question : " << question << endl
             << "Answer : " << answer << endl
             << "Number of Total Reviews : " << numOfReview << endl
             << "Day of Next Review : " << dayOfnextReview << endl
             << "-----------------------" << endl;
    }
    string showQuestion()
    {
        return question;
    }
    string showAnswer()
    {
        return answer;
    }
    void setDayOfReview(int dayNum)
    {
        dayOfnextReview = dayNum;
    }

    void reviewed(int dayNum)
    {
        if (numOfReview == 0)
        {
            if (dayNum % 3 == 0)
            {
                dayOfnextReview = dayNum + 3;
            }
            else if (dayNum % 7 == 0)
            {
                dayOfnextReview = dayNum + 7;
            }
            else if (dayNum % 30 == 0)
            {
                dayOfnextReview = dayNum + 30;
            }
            else
            {
                dayOfnextReview = ((dayNum / 3) * 3) + 3;
            }
        }
        else if (numOfReview == 1)
        {
            if (dayNum % 7 == 0)
            {
                dayOfnextReview = dayNum + 7;
            }
            else if (dayNum % 30 == 0)
            {
                dayOfnextReview = dayNum + 30;
            }
            else
            {
                dayOfnextReview = ((dayNum / 7) * 7) + 7;
            }
        }
        else if (numOfReview == 2)
        {
            if (dayNum % 30 == 0)
            {
                dayOfnextReview = dayNum + 30;
            }
            else
            {
                dayOfnextReview = ((dayNum / 30) * 30) + 30;
            }
        }
        else if (numOfReview >= 3)
        {
            dayOfnextReview = 0;
        }
        numOfReview++;
        numOfWrongAnswer = 0;
    }

    int dayStatus()
    {
        return dayOfReview;
    }
    void setDay(int dayNum)
    {
        dayOfReview = dayNum;
    }
    int reviewStatus()
    {
        return numOfReview;
    }
    void demoted()
    {
        numOfWrongAnswer = 0;
        numOfReview--;
    }
    int numOfWrongAnswer = 0;
    bool isReviewedToday = false;
    int dayOfnextReview;
};

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

void dayReporter(vector<dayReport> &daysReport, int dayNum)
{
    dayReport todayInfo;
    daysReport.push_back(todayInfo);
}

void addFlashcard(Boxes &boxes, string mainInput, int dayNum)
{
    FlashCard inputCard;
    inputCard.setDayOfReview(dayNum);
    string input;
    stringstream ss(mainInput);
    string command;
    int cardNum;
    ss >> command >> cardNum;

    for (int i = 0; i < cardNum * 2; i++)
    {
        getline(cin, input);
        if (i % 2 == 0)
        {
            inputCard.addQuestion(input);
        }
        else if (i % 2 == 1)
        {
            inputCard.addAnswers(input);
            boxes.dailyBox.push_back(inputCard);
            boxes.allCards.push_back(inputCard);
        }
    }
    cout << SUCCESFULL_ADD_MESSAGE;
}

void streakReport(int &streak)
{
    cout << "Your current streak is: " << streak << endl
         << "Keep going!" << endl;
}

void demoteIfNotReviewed(Boxes &boxes, int dayNum)
{
    for (int i = 0; i < boxes.perMonthBox.size(); i++)
    {
        if (dayNum % 30 == 0 && boxes.perMonthBox[i].dayOfnextReview == dayNum && boxes.perMonthBox[i].reviewStatus() == 3)
        {
            boxes.perMonthBox[i].demoted();
            boxes.perMonthBox[i].dayOfnextReview = dayNum + 6;
            boxes.perWeekBox.push_back(boxes.perMonthBox[i]);
        }
    }

    for (int i = 0; i < boxes.perWeekBox.size(); i++)
    {
        if (dayNum % 7 == 0 && boxes.perWeekBox[i].dayOfnextReview == dayNum && boxes.perWeekBox[i].reviewStatus() == 2)
        {
            boxes.perWeekBox[i].demoted();
            boxes.perWeekBox[i].dayOfnextReview = dayNum + 2;
            boxes.per3DayBox.push_back(boxes.perWeekBox[i]);
        }
    }

    for (int i = 0; i < boxes.per3DayBox.size(); i++)
    {
        if (dayNum % 3 == 0 && boxes.per3DayBox[i].dayOfnextReview == dayNum && boxes.per3DayBox[i].reviewStatus() == 1)
        {
            boxes.per3DayBox[i].demoted();
            boxes.per3DayBox[i].dayOfnextReview = dayNum;
            boxes.dailyBox.push_back(boxes.per3DayBox[i]);
        }
    }
}

void streak(int &streak, string choose)
{
    if (choose == "increase")
    {
        streak++;
    }
    else if (choose == "reset")
    {
        streak = 0;
    }
}

void report(Boxes boxes)
{
    cout << "***********************" << endl;
    cout << "Daily Box:" << endl;
    for (int i = 0; i < boxes.dailyBox.size(); i++)
    {
        if (boxes.dailyBox[i].reviewStatus() == 0)
        {
            boxes.dailyBox[i].report();
        }
    }
    cout << "***********************" << endl;
    cout << "Per 3 Day Box:" << endl;
    for (int i = 0; i < boxes.per3DayBox.size(); i++)
    {
        if (boxes.per3DayBox[i].reviewStatus() == 1)
        {
            boxes.per3DayBox[i].report();
        }
    }
    cout << "***********************" << endl;
    cout << "Per Week Box:" << endl;
    for (int i = 0; i < boxes.perWeekBox.size(); i++)
    {
        if (boxes.perWeekBox[i].reviewStatus() == 2)
        {
            boxes.perWeekBox[i].report();
        }
    }
    cout << "***********************" << endl;
    cout << "Per Month Box:" << endl;
    for (int i = 0; i < boxes.perMonthBox.size(); i++)
    {
        if (boxes.perMonthBox[i].reviewStatus() == 3)
        {
            boxes.perMonthBox[i].report();
        }
    }
    cout << "***********************" << endl;
    cout << "Mastered Cards:" << endl;
    for (int i = 0; i < boxes.mastered.size(); i++)
    {
        if (boxes.mastered[i].reviewStatus() == 4)
        {
            boxes.mastered[i].report();
        }
    }
    cout << "***********************" << endl;
    cout << "_______________________________________________________" << endl;
}

void answerCheck(Boxes &boxes, FlashCard &card, vector<dayReport> &daysReport, string enteredAnswer, int &streakval, int dayNum, bool &hasReviewedToday)
{
    if (!hasReviewedToday)
    {
        streak(streakval, INCREASE);
        hasReviewedToday = true;
    }
    if (card.showAnswer() == enteredAnswer)
    {
        daysReport[dayNum - 1].correctAnswer++;
        cout << CORRECT_ANSWER_MESSAGE;
        switch (card.reviewStatus())
        {
        case 0:
        {
            card.reviewed(dayNum);
            boxes.per3DayBox.push_back(card);
            break;
        }
        case 1:
        {
            card.reviewed(dayNum);
            boxes.perWeekBox.push_back(card);
            break;
        }
        case 2:
        {
            card.reviewed(dayNum);
            boxes.perMonthBox.push_back(card);
            break;
        }
        case 3:
        {
            card.reviewed(dayNum);
            boxes.mastered.push_back(card);
            break;
        }
        }
    }
    else if (card.showAnswer() != enteredAnswer)
    {
        daysReport[dayNum - 1].wrongAnswer++;
        cout << WRONG_ANSWER_MESSAGE << card.showAnswer() << KEEP_PRACTICING;
        if (card.numOfWrongAnswer == 1)
        {
            switch (card.reviewStatus())
            {
            case 1:
            {
                card.demoted();
                boxes.dailyBox.push_back(card);
                break;
            }
            case 2:
            {
                card.demoted();
                boxes.per3DayBox.push_back(card);
                break;
            }
            case 3:
            {
                card.demoted();
                boxes.perWeekBox.push_back(card);
                break;
            }
            }
        }
        else
        {
            card.numOfWrongAnswer++;
        }
    }
}

void printBox(Boxes &boxes, vector<FlashCard> &box, vector<dayReport> &daysReport, int cardNum, int reviewStat, int &streak, int dayNum, bool &hasReviewedToday)
{
    string enteredAnswer;
    for (int i = 0; i < cardNum; i++)
    {
        if (box[i].reviewStatus() == reviewStat && box[i].dayOfnextReview == dayNum)
        {
            cout << "Flashcard: " << box[i].showQuestion() << endl
                 << "Your answer: ";
            getline(cin, enteredAnswer);
            cout << endl;
            answerCheck(boxes, box[i], daysReport, enteredAnswer, streak, dayNum, hasReviewedToday);
        }
        else
        {
            cardNum++;
        }
    }
}

int printableCards(vector<FlashCard> box, int reviewStat)
{
    int printable = 0;
    for (int i = 0; i < box.size(); i++)
    {
        if (box[i].reviewStatus() == reviewStat)
        {
            printable++;
        }
    }
    return printable;
}

void reviewToday(Boxes &boxes, vector<dayReport> &daysReport, int dayNum, string mainInput, int &streak, bool &hasReviewedToday)
{
    int cardNum = stoi(mainInput.substr(mainInput.find(' ')));
    int totalReviewed = 0;

    if (dayNum % 30 == 0 && cardNum > 0)
    {
        int monthlyCards = printableCards(boxes.perMonthBox, 3);
        int cardsToReview = min(cardNum, monthlyCards);
        printBox(boxes, boxes.perMonthBox, daysReport, cardsToReview, 3, streak, dayNum, hasReviewedToday);
        totalReviewed += cardsToReview;
        cardNum -= cardsToReview;
    }

    if (dayNum % 7 == 0 && cardNum > 0)
    {
        int weeklyCards = printableCards(boxes.perWeekBox, 2);
        int cardsToReview = min(cardNum, weeklyCards);
        printBox(boxes, boxes.perWeekBox, daysReport, cardsToReview, 2, streak, dayNum, hasReviewedToday);
        totalReviewed += cardsToReview;
        cardNum -= cardsToReview;
    }

    if (dayNum % 3 == 0 && cardNum > 0)
    {
        int threeDayCards = printableCards(boxes.per3DayBox, 1);
        int cardsToReview = min(cardNum, threeDayCards);
        printBox(boxes, boxes.per3DayBox, daysReport, cardsToReview, 1, streak, dayNum, hasReviewedToday);
        totalReviewed += cardsToReview;
        cardNum -= cardsToReview;
    }

    if (cardNum > 0)
    {
        int dailyCards = printableCards(boxes.dailyBox, 0);
        int cardsToReview = min(cardNum, dailyCards);
        printBox(boxes, boxes.dailyBox, daysReport, cardsToReview, 0, streak, dayNum, hasReviewedToday);
        totalReviewed += cardsToReview;
        cardNum -= cardsToReview;
    }

    if (totalReviewed > 0)
    {
        cout << TEST_FINISH_MESSAGE;
    }
}

void updateDayOfNextReview(Boxes &boxes, int currentDay)
{
    for (int i = 0; i < boxes.dailyBox.size(); i++)
    {
        if (!boxes.dailyBox[i].isReviewedToday && boxes.dailyBox[i].dayOfnextReview == currentDay)
        {
            boxes.dailyBox[i].dayOfnextReview += 1;
        }
    }

    for (int i = 0; i < boxes.per3DayBox.size(); i++)
    {
        if (!boxes.per3DayBox[i].isReviewedToday && boxes.per3DayBox[i].dayOfnextReview == currentDay)
        {
            boxes.per3DayBox[i].dayOfnextReview += 3;
        }
    }

    for (int i = 0; i < boxes.perWeekBox.size(); i++)
    {
        if (!boxes.perWeekBox[i].isReviewedToday && boxes.perWeekBox[i].dayOfnextReview == currentDay)
        {
            boxes.perWeekBox[i].dayOfnextReview += 7;
        }
    }

    for (int i = 0; i < boxes.perMonthBox.size(); i++)
    {
        if (!boxes.perMonthBox[i].isReviewedToday && boxes.perMonthBox[i].dayOfnextReview == currentDay)
        {
            boxes.perMonthBox[i].dayOfnextReview += 30;
        }
    }
}

void nextDay(Boxes &boxes, int &dayNum, vector<dayReport> &daysReport, int &streakval, bool &hasReviewedToday)
{
    if (daysReport[dayNum - 1].totalAnswer() == 0)
    {
        streak(streakval, RESET);
    }
    demoteIfNotReviewed(boxes, dayNum);
    updateDayOfNextReview(boxes, dayNum);

    dayNum++;
    hasReviewedToday = false;

    cout << "Good morning! Today is day " << dayNum << " of our journey.\n"
         << "Your current streak is: " << streakval << endl
         << "Start reviewing to keep your streak!" << endl;

    dayReporter(daysReport, dayNum);
}

void getReport(vector<dayReport> daysReport, string mainInput)
{
    int startDay, endDay;
    string command;
    stringstream ss(mainInput);
    ss >> command >> startDay >> endDay;
    int totalCorrect = 0, totalWrong = 0, totalQuestion = 0;
    for (int i = startDay - 1; i <= endDay - 1; i++)
    {
        totalCorrect += daysReport[i].correctAnswer;
        totalWrong += daysReport[i].wrongAnswer;
        totalQuestion += daysReport[i].totalAnswer();
    }
    if (startDay == endDay)
    {
        cout << "Day: " << startDay << endl
             << "Correct Answers: " << totalCorrect << endl
             << "Incorrect Answers: " << totalWrong << endl
             << "Total: " << totalQuestion << endl;
    }
    else
    {
        cout << "Day: " << startDay << " to " << endDay << endl
             << "Correct Answers: " << totalCorrect << endl
             << "Incorrect Answers: " << totalWrong << endl
             << "Total: " << totalQuestion << endl;
    }
}

int daysParticipated(vector<dayReport> daysReport)
{
    int participated = 0;
    for (int i = 0; i < daysReport.size(); i++)
    {
        if (daysReport[i].totalAnswer() > 0)
        {
            participated++;
        }
    }
    return participated;
}

void progressReport(Boxes boxes, vector<dayReport> daysReport, int streak, int dayNum)
{
    cout << "Challenge Progress Report:\n\n"
         << "Day of the Challenge: " << dayNum << endl
         << "Streak: " << streak << endl
         << "Total Days Participated: " << daysParticipated(daysReport) << endl
         << "Mastered Flashcards: " << boxes.mastered.size() << endl
         << endl
         << "Keep up the great work! You're making steady progress toward mastering your flashcards." << endl;
}

void takeAction(Boxes &boxes, vector<dayReport> &daysReport, string &mainInput, int &dayNum, int &streak, bool &hasReviewedToday)
{
    if (mainInput.find(ADD_FLASHCARD) == 0)
    {
        addFlashcard(boxes, mainInput, dayNum);
    }
    else if (mainInput.find(REPORT) == 0)
    {
        report(boxes);
    }
    else if (mainInput.find(REVIEW_TODAY) == 0)
    {
        reviewToday(boxes, daysReport, dayNum, mainInput, streak, hasReviewedToday);
    }
    else if (mainInput.find(NEXT_DAY) == 0)
    {
        nextDay(boxes, dayNum, daysReport, streak, hasReviewedToday);
        dayReporter(daysReport, dayNum);
    }
    else if (mainInput.find(STREAK) == 0)
    {
        streakReport(streak);
    }
    else if (mainInput.find(GET_REPORT) == 0)
    {
        getReport(daysReport, mainInput);
    }
    else if (mainInput.find(GET_PROGRESS_REPORT) == 0)
    {
        progressReport(boxes, daysReport, streak, dayNum);
    }
}

int main()
{
    Boxes boxes;
    vector<dayReport> daysReport;
    string mainInput;
    int dayNum = 1;
    int streak = 0;
    bool hasReviewedToday = false;
    dayReporter(daysReport, dayNum);
    while (getline(cin, mainInput))
    {
        takeAction(boxes, daysReport, mainInput, dayNum, streak, hasReviewedToday);
    }
}
