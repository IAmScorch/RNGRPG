#include <iostream>
#include <random>
#include <ctime>
#include <QTime>
#include <QMessageBox>
#include <QSound>
#include <algorithm>
#include "bandit.h"
#include "item.h"

Bandit::Bandit(QString name, int health, int maxAttackPower, int minAttackPower,
               int critChance, int XPReward, int level, int enemyType, int agility, int objType, int itemDropChance, int weaponDot, int armourType)
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
    itemDropChance_(itemDropChance),
    weaponDot_(weaponDot),
    armourType_(armourType)
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

void Bandit::doHit(int dmg, int playerHitRoll, QString playerName, int playerDotType, int playerClass)
{
    if (playerHitRoll >= agility_)
    {
        int dotChance = rand() % ((100 + 1) - 1) + 1;
        isHit_ = true;
        health_ = health_ - dmg;
        if (health_ <= 0)
        {
            isAlive_ = false;
            message_ = name_ + " takes " + QString("%1").arg(dmg) + " damage.\n" + name_ + " is dead.\n\n";
            isHit_ = false;
        }
        else
        {
            message_ = name_ + " takes " + QString("%1").arg(dmg) + " damage.\n\n";
            DoT dotInfo;
            int dotEffectiveness = rand()% 5 + 3;

            if (armourType_ == 0)
            {
                if (playerDotType == 1 && dotChance >= 50)
                {
                    dotInfo.name = "Bleeding";
                    dotInfo.dotType = playerDotType;
                    dotInfo.dotDamage = 1;

                    for (int i = 0; i < dotEffectiveness; i++)
                    {
                        dot_.push_back(dotInfo);
                    }

                    message_ += playerName + " slashed " + name_ + " and caused a " + dotInfo.name + " effect\n\n";
                }
                else if (playerDotType == 2 && dotChance >= 30)
                {
                    dotInfo.name = "Blunt Trauma";
                    dotInfo.dotType = playerDotType;
                    dotInfo.dotDamage = 1;

                    for (int i = 0; i < dotEffectiveness; i++)
                    {
                        dot_.push_back(dotInfo);
                    }

                    message_ += playerName + " crushed " + name_ + " and caused a " + dotInfo.name + " effect\n\n";
                }
                else if (playerDotType == 3 && dotChance >= 50)
                {
                    if (playerClass == 2)
                        dotEffectiveness += 1;

                    dotInfo.name = "Poison";
                    dotInfo.dotType = playerDotType;
                    dotInfo.dotDamage = 1;

                    for (int i = 0; i < dotEffectiveness; i++)
                    {
                        dot_.push_back(dotInfo);
                    }

                    message_ += playerName + " slashed " + name_ + " with a poison laced blade and caused a " + dotInfo.name + " effect\n\n";
                }
            }
            else if (armourType_ == 1)
            {
                if (playerDotType == 1 && dotChance >= 80)
                {
                    dotInfo.name = "Bleeding";
                    dotInfo.dotType = playerDotType;
                    dotInfo.dotDamage = 1;

                    for (int i = 0; i < dotEffectiveness; i++)
                    {
                        dot_.push_back(dotInfo);
                    }

                    message_ += playerName + " slashed " + name_ + " and caused a " + dotInfo.name + " effect\n\n";
                }
                else if (playerDotType == 2 && dotChance >= 60)
                {
                    dotInfo.name = "Blunt Trauma";
                    dotInfo.dotType = playerDotType;
                    dotInfo.dotDamage = 1;

                    for (int i = 0; i < dotEffectiveness; i++)
                    {
                        dot_.push_back(dotInfo);
                    }

                    message_ += playerName + " crushed " + name_ + " and caused a " + dotInfo.name + " effect\n\n";
                }
                else if (playerDotType == 3 && dotChance >= 80)
                {
                    if (playerClass == 2)
                        dotEffectiveness += 1;

                    dotInfo.name = "Poison";
                    dotInfo.dotType = playerDotType;
                    dotInfo.dotDamage = 1;

                    for (int i = 0; i < dotEffectiveness; i++)
                    {
                        dot_.push_back(dotInfo);
                    }

                    message_ += playerName + " slashed " + name_ + " with a poison laced blade and caused a " + dotInfo.name + " effect\n\n";
                }
            }
            else if (armourType_ == 2)
            {
                if (playerDotType == 1 && dotChance >= 85)
                {
                    dotInfo.name = "Bleeding";
                    dotInfo.dotType = playerDotType;
                    dotInfo.dotDamage = 1;

                    for (int i = 0; i < dotEffectiveness; i++)
                    {
                        dot_.push_back(dotInfo);
                    }

                    message_ += playerName + " slashed " + name_ + " and caused a " + dotInfo.name + " effect\n\n";
                }
                else if (playerDotType == 2 && dotChance >= 65)
                {
                    dotInfo.name = "Blunt Trauma";
                    dotInfo.dotType = playerDotType;
                    dotInfo.dotDamage = 1;

                    for (int i = 0; i < dotEffectiveness; i++)
                    {
                        dot_.push_back(dotInfo);
                    }

                    message_ += playerName + " crushed " + name_ + " and caused a " + dotInfo.name + " effect\n\n";
                }
                else if (playerDotType == 3 && dotChance >= 85)
                {
                    if (playerClass == 2)
                        dotEffectiveness += 1;

                    dotInfo.name = "Poison";
                    dotInfo.dotType = playerDotType;
                    dotInfo.dotDamage = 1;

                    for (int i = 0; i < dotEffectiveness; i++)
                    {
                        dot_.push_back(dotInfo);
                    }

                    message_ += playerName + " slashed " + name_ + " with a poison laced blade and caused a " + dotInfo.name + " effect\n\n";
                }
            }
            else if (armourType_ == 3)
            {
                if (playerDotType == 1 && dotChance >= 90)
                {
                    dotInfo.name = "Bleeding";
                    dotInfo.dotType = playerDotType;
                    dotInfo.dotDamage = 1;

                    for (int i = 0; i < dotEffectiveness; i++)
                    {
                        dot_.push_back(dotInfo);
                    }

                    message_ += playerName + " slashed " + name_ + " and caused a " + dotInfo.name + " effect\n\n";
                }
                else if (playerDotType == 2 && dotChance >= 70)
                {
                    dotInfo.name = "Blunt Trauma";
                    dotInfo.dotType = playerDotType;
                    dotInfo.dotDamage = 1;

                    for (int i = 0; i < dotEffectiveness; i++)
                    {
                        dot_.push_back(dotInfo);
                    }

                    message_ += playerName + " crushed " + name_ + " and caused a " + dotInfo.name + " effect\n\n";
                }
                else if (playerDotType == 3 && dotChance >= 90)
                {
                    if (playerClass == 2)
                        dotEffectiveness += 1;

                    dotInfo.name = "Poison";
                    dotInfo.dotType = playerDotType;
                    dotInfo.dotDamage = 1;

                    for (int i = 0; i < dotEffectiveness; i++)
                    {
                        dot_.push_back(dotInfo);
                    }

                    message_ += playerName + " slashed " + name_ + " with a poison laced blade and caused a " + dotInfo.name + " effect\n\n";
                }
            }
            else if (armourType_ == 4)
            {
                if (playerDotType == 1 && dotChance >= 95)
                {
                    dotInfo.name = "Bleeding";
                    dotInfo.dotType = playerDotType;
                    dotInfo.dotDamage = 1;

                    for (int i = 0; i < dotEffectiveness; i++)
                    {
                        dot_.push_back(dotInfo);
                    }

                    message_ += playerName + " slashed " + name_ + " and caused a " + dotInfo.name + " effect\n\n";
                }
                else if (playerDotType == 2 && dotChance >= 75)
                {
                    dotInfo.name = "Blunt Trauma";
                    dotInfo.dotType = playerDotType;
                    dotInfo.dotDamage = 1;

                    for (int i = 0; i < dotEffectiveness; i++)
                    {
                        dot_.push_back(dotInfo);
                    }

                    message_ += playerName + " crushed " + name_ + " and caused a " + dotInfo.name + " effect\n\n";
                }
                else if (playerDotType == 3 && dotChance >= 95)
                {
                    if (playerClass == 2)
                        dotEffectiveness += 1;

                    dotInfo.name = "Poison";
                    dotInfo.dotType = playerDotType;
                    dotInfo.dotDamage = 1;

                    for (int i = 0; i < dotEffectiveness; i++)
                    {
                        dot_.push_back(dotInfo);
                    }

                    message_ += playerName + " slashed " + name_ + " with a poison laced blade and caused a " + dotInfo.name + " effect\n\n";
                }
            }
        }
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

int Bandit::getWeaponDot()
{
    return weaponDot_;
}

bool Bandit::hasActiveDoT()
{
    bool hasDot = false;

    if (dot_.length() >= 1)
        hasDot = true;

    return hasDot;
}

void Bandit::doDotEffect()
{
    health_ -= dot_.value(0).dotDamage;
    dot_.remove(0);

    message_ = QString("%3 takes %1 damage from the %2 effect\n\n").arg(dot_.value(0).dotDamage).arg(dot_.value(0).name).arg(name_);
}

void Bandit::addLoot(QVector<Item> defaultLoot, QVector<Item> enemySpecificLoot)
{
    loot_.clear();

    for (int i = 0; i < defaultLoot.length(); i++)
        loot_.push_back(defaultLoot.value(i));

    for (int i = 0; i < enemySpecificLoot.length(); i++)
        loot_.push_back(enemySpecificLoot.value(i));

    std::sort(loot_.begin(),loot_.end(), [](Item &left, Item &right){return left.dropWeight > right.dropWeight;});
}

QVector<Item> Bandit::getEnemyLoot()
{
    return loot_;
}

bool Bandit::compareByWeight(const Item &a, const Item &b)
{
    return a.dropWeight < b.dropWeight;
}

