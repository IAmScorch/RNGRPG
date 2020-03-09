#include <iostream>
#include <random>
#include <ctime>
#include <QTime>
#include <QMessageBox>
#include <QSound>
#include <algorithm>
#include "bandit.h"

Bandit::Bandit(QString name, int health, int maxAttackPower, int minAttackPower,
               int critChance, int XPReward, int level, int enemyType, int agility, int objType, int itemDropChance)
    :name_(name),
    health_(health),
    maxAttackPower_(maxAttackPower),
    minAttackPower_(minAttackPower),
    critChance_(critChance),
    XPReward_(XPReward),
    level_(level),
    enemyType_(enemyType),
    agility_(agility),
    objType_(objType),
    itemDropChance_(itemDropChance)
{
    qsrand(QTime::currentTime().msec());
    isAlive_ = true;

//    int drop = rand()% 17 + 1;
//    QMessageBox msgBox;
//    msgBox.setWindowTitle("Loot Drop");
//    msgBox.setText(QString("Bandit Leader dropped %1.").arg(banditItemDrops_[drop][0]));
//    msgBox.exec();
}


Bandit::~Bandit(void)
{
}

int Bandit::doAttack(QString enemy)
{

    //bool doesCrit;
    //int critical;
    int critRoll;
    //if (critNum_ == 0)
    //    critNum_ = (rand() % critChance_ + 1);

    critRoll   = rand() % ((20 + 1) - 1) + 1;

    //attackDmg_ = (rand() % 5 + minAttackPower_);
    attackDmg_ = rand() % ((maxAttackPower_ + 1) - minAttackPower_) + minAttackPower_;
  //  critical   = (rand() % critChance_ + 1);
  //  critDmg_   = (rand() % 10 + 5);

    if (isAlive_)
    {
        if (critRoll >= critChance_)
        {
            attackDmg_ *= 2;
            message_ = name_ + " Attacks " + enemy + " for " + QString("%1").arg(attackDmg_) + " damage. CRITICAL HIT!\n";
        }
        else
        {
            message_ = name_ + " Attacks " + enemy + " for " + QString("%1").arg(attackDmg_) + " damage.\n";
        }

        return attackDmg_;
    }
    else
        return 0;
}

int Bandit::doHitRoll()
{
    int hitRoll = rand()% ((20 + 1) - 1) + 1;
    return hitRoll;
}

void Bandit::doHit(int dmg, int playerHitRoll, QString playerName)
{
    if (playerHitRoll >= agility_)
    {
        isHit_ = true;
        health_ = health_ - dmg;
        if (health_ <= 0)
        {
            isAlive_ = false;
            message_ = name_ + " takes " + QString("%1").arg(dmg) + " damage.\n" + name_ + " is dead.\n\n";
            isHit_ = false;
        }
        else
            message_ = name_ + " takes " + QString("%1").arg(dmg) + " damage.\n\n";
    }
    else
    {
        message_ = name_ + " dodges " + playerName + "'s attack.\n\n";
        isHit_ = false;
    }
}

int Bandit::goldDrop()
{
    QSound::play("Sounds\\goldDrop.wav");
    int gold = 0;
    if (level_ == 15)
    {
        gold = 500;
        QMessageBox msgBox;
        msgBox.setWindowTitle("Gold Drop");
        msgBox.setText(QString("Bandit Leader dropped %1 gold.").arg(gold));
        msgBox.exec();
    }
    if (level_ == 13 || level_ == 14)
    {
        //attackDmg_ = rand() % ((maxAttackPower_ + 1) - minAttackPower_) + minAttackPower_;
        gold = rand()% ((30 + 1 ) - 20) + 20;
        QMessageBox msgBox;
        msgBox.setWindowTitle("Gold Drop");
        msgBox.setText(QString("Bandit Leader dropped %1 gold.").arg(gold));
        msgBox.exec();
    }
    else if (level_ >= 10 && level_ <= 12)
    {
        gold = rand()% ((10 + 1) - 5) + 5;
        QMessageBox msgBox;
        msgBox.setWindowTitle("Gold Drop");
        msgBox.setText(QString("Bandit dropped %1 gold.").arg(gold));
        msgBox.exec();
    }
    else if (level_ <= 11)
    {
        gold = rand()% 4 + 1;
        QMessageBox msgBox;
        msgBox.setWindowTitle("Gold Drop");
        msgBox.setText(QString("Bandit dropped %1 gold.").arg(gold));
        msgBox.exec();
    }
    return gold;
}

QString Bandit::doLootDrop(QString enemyName, int enemyType, int itemDropChance)
{
    int dropChance;
    int oddsRoll;
    QString itemChance;
    int itemsToDropped;
    int itemsDropped;
    QString lootMessage;

    dropChance = rand()% 100 + 1;
    lootMessage = enemyName + " dropped no loot";
    oddsRoll = 0;
    itemChance = "";

    if (dropChance <= itemDropChance)
    {
        lootMessage = enemyName + " dropped:\n";
        itemsToDropped = rand()% 3 + 1;
        itemsDropped = 0;

        for (int i = 0; i < itemsToDropped; i++)
        {
            if (enemyType == 1 || enemyType == 2 || enemyType == 3 || enemyType == 4 || enemyType == 5)
            {
                int cols = sizeof(*banditItemDropsChance_)/(sizeof (int *));
                int rows =  sizeof banditItemDrops_ / sizeof banditItemDrops_[0];

                int count = 0;
                QVector<QString> odds;

                for (int x = 0; x < cols; x++)
                {
                    count += banditItemDropsChance_[0][x].toInt();
                    for (int y = 0; y < banditItemDropsChance_[0][x].toInt(); y++)
                    {
                        odds.push_back(banditItemDropsChance_[0][x]);
                    }
                }

                QString vector;
                for (int z = 0; z < odds.length(); z++)
                {
                    vector += odds.value(z) + ", ";
                }
                vector = "";
                for (int b = 0; b < odds.length(); b++)
                {
                    std::random_shuffle (odds.begin(), odds.end());
                }
                for (int a = 0; a < odds.length(); a++)
                {
                    vector += odds.value(a) + ", ";
                }

                oddsRoll = rand()% odds.length();
                itemChance = odds.value(oddsRoll);

                for (int c = 0; c < cols; c++)
                {
                    if (itemChance == banditItemDropsChance_[0][c])
                    {
                        QVector<QString> numItems;
                        for (int e = 0; e < rows; e++)
                        {
                            if (itemChance == banditItemDrops_[e][15])
                            {
                                numItems.push_back(banditItemDrops_[e][0]);
                            }
                        }

                        for (int f = 0; f < numItems.length(); f++)
                        {
                            std::random_shuffle (numItems.begin(), numItems.end());
                        }

                        int whichItem = rand()% numItems.length();
                        lootMessage += numItems.value(whichItem) + "\n";
                    }
                }
            }
        }
    }


    QMessageBox msgBox3;
    msgBox3.setWindowTitle("Loot Drop");
    msgBox3.setText(QString(lootMessage));
    msgBox3.exec();

    return 0;
}

bool Bandit::isAlive()
{
    return isAlive_;
}

bool Bandit::isHit()
{
    return isHit_;
}

int Bandit::getHealth()
{
    return health_;
}

void Bandit::setHealth(int health)
{
    health_ = health;
}

int Bandit::getMaxAttackPower()
{
    return maxAttackPower_;
}

void Bandit::setMaxAttackPower(int maxAttackPower)
{
    maxAttackPower_ = maxAttackPower;
}

int Bandit::getMinAttackPower()
{
    return minAttackPower_;
}

void Bandit::setMinAttackPower(int minAttackPower)
{
    minAttackPower_ = minAttackPower;
}

int Bandit::getCritChance()
{
    return critChance_;
}

void Bandit::setCritChance(int critChance)
{
    critChance_ = critChance;
}

int Bandit::getLevel()
{
    return level_;
}

void Bandit::setLevel(int level)
{
    level_ = level;
}

int Bandit::getAttackDmg()
{
    return attackDmg_;
}

int Bandit::getXPReward()
{
    return XPReward_;
}

void Bandit::setXPReward(int XPReward)
{
    XPReward_ = XPReward;
}

QString Bandit::getName()
{
    return name_;
}

void Bandit::setName(QString name)
{
    name_ = name;
}

int Bandit::getObjType()
{
    return objType_;
}

QString Bandit::getMessage()
{
    return message_;
}

void Bandit::setMessage(QString message)
{
    message_ = message;
}

int Bandit::getEnemyType()
{
    return enemyType_;
}

void Bandit::setEnemyType(int enemyType)
{
    enemyType_ = enemyType;
}

int Bandit::getItemDropChance()
{
    return itemDropChance_;
}

