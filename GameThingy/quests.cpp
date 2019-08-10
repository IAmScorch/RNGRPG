#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <QTime>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "quests.h"

quests::quests(int xpReward, int objective, int objectiveII, int amountComplete, int amountCompleteII,
               int isQuestComplete, int isQuestActive, int questType, int numObjectives, int handInLocation, QString handInNPC)
    : xpReward_(xpReward),
      objective_(objective),
      objectiveII_(objectiveII),
      amountComplete_(amountComplete),
      amountCompleteII_(amountCompleteII),
      isQuestComplete_(isQuestComplete),
      isQuestActive_(isQuestActive),
      questType_(questType),
      numObjectives_(numObjectives),
      handInLocation_(handInLocation),
      handInNPC_(handInNPC)
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
    if (numObjectives_ == 1)
    {
        if (amountComplete_ == objective_)
        {
            isQuestComplete_ = 1;
            isQuestActive_ = 0;
            //questType_ = 0;
        }
    }
    else if (numObjectives_ == 2)
    {
        if (amountComplete_ == objective_ && amountCompleteII_ == objectiveII_)
        {
            isQuestComplete_ = 1;
            isQuestActive_ = 0;
            //questType_ = 0;
        }
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
    saveFile << objectiveII_ << "\n";
    saveFile << amountComplete_ << "\n";
    saveFile << amountCompleteII_ << "\n";
    saveFile << isQuestComplete_ << "\n";
    saveFile << isQuestActive_ << "\n";
    saveFile << questTitle_ << "\n";
    saveFile << objectiveProgress_ << "\n";
    saveFile << questType_ << "\n";
    saveFile << numObjectives_ << "\n";
    saveFile << handInLocation_ << "\n";
    saveFile << handInNPC_ << "\n";
    file.close();
}

void quests::load(QString playerName)
{
    QString filename = "saves\\" + playerName + "QuestLog.save";
    QFile file(filename);
    file.open(QIODevice::ReadOnly| QIODevice::Text);
    QTextStream saveFile(&file);
    if (file.exists() && file.isOpen())
    {
        xpReward_ = saveFile.readLine().toInt();
        objective_ = saveFile.readLine().toInt();
        objectiveII_ = saveFile.readLine().toInt();
        amountComplete_ = saveFile.readLine().toInt();
        amountCompleteII_ = saveFile.readLine().toInt();
        isQuestComplete_ = saveFile.readLine().toInt();
        isQuestActive_ = saveFile.readLine().toInt();
        questTitle_ = saveFile.readLine();
        objectiveProgress_ = saveFile.readLine();
        questType_ = saveFile.readLine().toInt();
        numObjectives_ = saveFile.readLine().toInt();
        handInLocation_ = saveFile.readLine().toInt();
        handInNPC_ = saveFile.readLine();
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

int quests::getObjectiveII()
{
    return objectiveII_;
}

void quests::setObjectiveII(int objectiveII)
{
    objectiveII_ = objectiveII;
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

int quests::getAmountCompleteII()
{
    return amountCompleteII_;
}

void quests::setAmountCompleteII(int amountCompleteII)
{
    if (amountCompleteII_ != objectiveII_)
        amountCompleteII_ += amountCompleteII;
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

int quests::getNumObjectives()
{
    return numObjectives_;
}

int quests::getHandInLocation()
{
    return handInLocation_;
}

QString quests::getHandInNPC()
{
    return handInNPC_;
}
