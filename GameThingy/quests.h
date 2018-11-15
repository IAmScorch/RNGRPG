#ifndef QUESTS_H
#define QUESTS_H
#include <string>
#include <QString>

class quests
{
private:
    int xpReward_;
    int objective_;
    int amountComplete_;
    int isQuestComplete_;
    int isQuestActive_;
    int questType_;
    QString questTitle_;
    QString objectiveProgress_;

public:
    quests(int xpReward, int objective, int amountComplete, int isQuestComplete, int isQuestActive, int questType);
    ~quests(void);

    void beginQuest(QString title, QString objective, int isQuestActive);
    void progress(int kill);
    void completeQuest();
    void save();
    void load();

    int getXPReward();
    void setXpReward(int xpReward);

    int getObjective();
    void setObjective(int objective);

    int getAmountComplete();
    void setAmountComplete(int amountComplete);

    QString getQuestTitle();
    void setQuestTitle(QString &questTitle);

    QString getObjectiveProgress();
    void setObjectiveProgress(QString &objectiveProgress);

    int getIsQuestComplete();
    void setIsQuestComplete(int isQuestComplete);

    int getIsQuestActive();
    void setIsQuestActive(int isQuestActive);

    int getQuestType();
    void setQuestType(int questType);
};

#endif // QUESTS_H
