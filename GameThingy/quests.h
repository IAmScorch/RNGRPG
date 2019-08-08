#ifndef QUESTS_H
#define QUESTS_H
#include <string>
#include <QString>

class quests
{
private:
    int xpReward_;
    int objective_;
    int objectiveII_;
    int amountComplete_;
    int amountCompleteII_;
    int isQuestComplete_;
    int isQuestActive_;
    int questType_;
    int numObjectives_;
    QString questTitle_;
    QString objectiveProgress_;

public:
    quests(int xpReward, int objective, int objectiveII, int amountComplete, int amountCompleteII, int isQuestComplete, int isQuestActive, int questType, int numObjectives);
    ~quests(void);

    void beginQuest(QString title, QString objective, int isQuestActive);
    void progress(int kill);
    void completeQuest();
    void save(QString playerName);
    void load(QString playerName);

    int getXPReward();
    void setXpReward(int xpReward);

    int getObjective();
    void setObjective(int objective);

    int getObjectiveII();
    void setObjectiveII(int objectiveII);

    int getAmountComplete();
    void setAmountComplete(int amountComplete);

    int getAmountCompleteII();
    void setAmountCompleteII(int amountCompleteII);

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

    int getNumObjectives();
};

#endif // QUESTS_H
