#include <iostream>
#include <random>
#include <ctime>
#include <QTime>
#include <QMessageBox>
#include "warrior.h"


Warrior::Warrior(QString name, int health, int minAttackPower,
               int critChance, int XPReward, int level)
    :name_(name),
    health_(health),
    minAttackPower_(minAttackPower),
    critChance_(critChance),
    XPReward_(XPReward),
    level_(level)
{
    qsrand(QTime::currentTime().msec());
    isAlive_ = true;
}


Warrior::~Warrior(void)
{
}

int Warrior::doAttack(QString enemy)
{

    //bool doesCrit;
    int critical;
    if (critNum_ == 0)
        critNum_ = (rand() % critChance_ + 1);

    attackDmg_ = (rand() % 5 + minAttackPower_);
    critical   = (rand() % critChance_ + 1);
    critDmg_   = (rand() % 20 + 5);

    if (isAlive_)
    {
        if (critical == critNum_)
        {
            attackDmg_+= critDmg_;
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

void Warrior::doHit(int dmg)
{
    health_ = health_ - dmg;
    if (health_ <= 0)
    {
        isAlive_ = false;
        message_ = name_ + " takes " + QString("%1").arg(dmg) + " damage.\n" + name_ + " is dead.\n\n";
    }
    else
        message_ = name_ + " takes " + QString("%1").arg(dmg) + " damage.\n\n";
}

int Warrior::goldDrop()
{
    int gold = 0;
    if (level_ == 35)
    {
        gold = rand()% 100 + 20;
        QMessageBox msgBox;
        msgBox.setWindowTitle("Gold Drop");
        msgBox.setText(QString("Warrior Leader dropped %1 gold.").arg(gold));
        msgBox.exec();
    }
    else if (level_ >= 16 && level_ <= 34)
    {
        gold = rand()% 15 + 5;
        QMessageBox msgBox;
        msgBox.setWindowTitle("Gold Drop");
        msgBox.setText(QString("Warrior dropped %1 gold.").arg(gold));
        msgBox.exec();
    }
    return gold;
}

int Warrior::healthUpgradeDrop()
{
    return 10;
}

bool Warrior::isAlive()
{
    return isAlive_;
}

int Warrior::getHealth()
{
    return health_;
}

void Warrior::setHealth(int health)
{
    health_ = health;
}

int Warrior::getMaxAttackPower()
{
    return maxAttackPower_;
}

void Warrior::setMaxAttackPower(int maxAttackPower)
{
    maxAttackPower_ = maxAttackPower;
}

int Warrior::getMinAttackPower()
{
    return minAttackPower_;
}

void Warrior::setMinAttackPower(int minAttackPower)
{
    minAttackPower_ = minAttackPower;
}

int Warrior::getCritChance()
{
    return critChance_;
}

void Warrior::setCritChance(int critChance)
{
    critChance_ = critChance;
}

int Warrior::getLevel()
{
    return level_;
}

void Warrior::setLevel(int level)
{
    level_ = level;
}

int Warrior::getAttackDmg()
{
    return attackDmg_;
}

int Warrior::getXPReward()
{
    return XPReward_;
}

void Warrior::setXPReward(int XPReward)
{
    XPReward_ = XPReward;
}

QString Warrior::getName()
{
    return name_;
}

void Warrior::setName(QString name)
{
    name_ = name;
}

QString Warrior::getMessage()
{
    return message_;
}

