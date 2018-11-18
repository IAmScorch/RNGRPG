#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <QTime>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "quests.h"

quests::quests(int xpReward, int objective, int amountComplete, int isQuestComplete, int isQuestActive, int questType)
    : xpReward_(xpReward),
      objective_(objective),
      amountComplete_(amountComplete),
      isQuestComplete_(isQuestComplete),
      isQuestActive_(isQuestActive),
      questType_(questType)
{
    qsrand(QTime::currentTime().msec());
}

quests::~quests()
{

}

void quests::beginQuest(QString title, QString objective, int isQuestActive)
{
    questTitle_ = title;
    objectiveProgress_ = objective;
    isQuestActive_ = isQuestActive;
}

void quests::progress(int kill)
{
    amountComplete_ += kill;
}

void quests::completeQuest()
{
    if (amountComplete_ == objective_)
    {
        isQuestComplete_ = 1;
        isQuestActive_ = 0;
        questType_ = 0;
    }
}

void quests::save(QString playerName)
{
    QString filename = "saves\\" + playerName + "QuestLog.save";
    QFile file(filename);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream saveFile(&file);
    saveFile << xpReward_ << "\n";
    saveFile << objective_ << "\n";
    saveFile << amountComplete_ << "\n";
    saveFile << isQuestComplete_ << "\n";
    saveFile << isQuestActive_ << "\n";
    saveFile << questTitle_ << "\n";
    saveFile << objectiveProgress_ << "\n";
    saveFile << questType_ << "\n";
    file.close();
}

void quests::load(QString playerName)
{
    QString filename = playerName + "QuestLog.save";
    QFile file(filename);
    file.open(QIODevice::ReadOnly| QIODevice::Text);
    QTextStream saveFile(&file);
    if (file.exists() && file.isOpen())
    {
        xpReward_ = saveFile.readLine().toInt();
        objective_ = saveFile.readLine().toInt();
        amountComplete_ = saveFile.readLine().toInt();
        isQuestComplete_ = saveFile.readLine().toInt();
        isQuestActive_ = saveFile.readLine().toInt();
        questTitle_ = saveFile.readLine();
        objectiveProgress_ = saveFile.readLine();
        questType_ = saveFile.readLine().toInt();
        file.close();
    }
}

int quests::getXPReward()
{
    return xpReward_;
}

void quests::setXpReward(int xpReward)
{
    xpReward_ = xpReward;
}

int quests::getObjective()
{
    return objective_;
}

void quests::setObjective(int objective)
{
    objective_ = objective;
}

int quests::getAmountComplete()
{
    return amountComplete_;
}

void quests::setAmountComplete(int amountComplete)
{
    if (amountComplete_ != objective_)
        amountComplete_ += amountComplete;
}

QString quests::getQuestTitle()
{
    return questTitle_;
}

void quests::setQuestTitle(QString &questTitle)
{
    questTitle_ = questTitle;
}

QString quests::getObjectiveProgress()
{
    return objectiveProgress_;
}

void quests::setObjectiveProgress(QString &objectiveProgress)
{
    objectiveProgress_ = objectiveProgress;
}

int quests::getIsQuestComplete()
{
    return isQuestComplete_;
}

void quests::setIsQuestComplete(int isQuestComplete)
{
    isQuestComplete_ = isQuestComplete;
}

int quests::getIsQuestActive()
{
    return isQuestActive_;
}

void quests::setIsQuestActive(int isQuestActive)
{
    isQuestActive_ = isQuestActive;
}

int quests::getQuestType()
{
    return questType_;
}

void quests::setQuestType(int questType)
{
    questType_ = questType;
}
