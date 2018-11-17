#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <QTime>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QSound>
#include "player.h"


Player::Player(int health, int maxHealth, int maxAttackPower, int minAttackPower,
               int critChance)
    : health_(health),
      maxHealth_(maxHealth),
      maxAttackPower_(maxAttackPower),
      minAttackPower_(minAttackPower),
      critChance_(critChance)
{
    level_ = 1;
    XP_ = 0;
    XPTillLevel_ = 100;
    critNum_ = 0;
    isAlive_ = true;
    potion_ = 0;
    gold_ = 0;
    skillpoints_ = 0;
    specialAbilityCharge_ = 0;
    specialAbilityCharged_ = 0;
    specialAbilityMaxCharges_ = 0;
    isSpecialAbilityLearned_ = false;
    isSpecialReady_ = false;
    qsrand(QTime::currentTime().msec());
}


Player::~Player(void)
{
}

int Player::doAttack(QString enemy)
{
    //bool doesCrit;
    int critical;
    if (critNum_ == 0)
        critNum_ = (rand() % critChance_ + 1);

    //attackDmg_ = (rand() % 10 + minAttackPower_);
    attackDmg_ = rand() % ((maxAttackPower_ + 1) - minAttackPower_) + minAttackPower_;

    critical   = (rand() % critChance_ + 1);
    if (level_ <= 15)
        critDmg_   = (rand() % 10 + 5);
    else if (level_ >= 16)
        critDmg_   = (rand() % 30 + 10);

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

int Player::doSpecialAbility(QString enemy)
{
    attackDmg_ = maxAttackPower_ * 3;
    message_ = name_ + " Attacks " + enemy + " for " + QString("%1").arg(attackDmg_) + " damage.\n";

    isSpecialReady_ = false;
    specialAbilityCharge_ = 0;
    specialAbilityCharged_ = 0;

    return attackDmg_;
}

void Player::doHit(int dmg)
{
    health_ = health_ - dmg;
    if (dmg == 0)
    {
        message_ = name_ + " Wins the battle!\n\n";
    }
    else
    {
        if (health_ <= 0)
        {
            isAlive_ = false;
            message_ = name_ + " takes " + QString("%1").arg(dmg) + " damage.\nAww you dead.\n\n";
            QMessageBox msgBox;
            msgBox.setWindowTitle("You Dead");
            msgBox.setText("Aww you dead. Start a new game or load a previous one.");
            msgBox.exec();
        }
        else
            message_ = name_ + " takes " + QString("%1").arg(dmg) + " damage.\n\n";
    }

}

void Player::checkXP()
{
    if (XP_ >= XPTillLevel_)
    {
        doLevelUp();
    }
}

void Player::addHealthUpgrade(int health)
{
    maxHealth_ += health;
}

void Player::resetSpecialAbility()
{
    isSpecialReady_ = false;
    specialAbilityCharge_ = 0;
    specialAbilityCharged_ = 0;
}

void Player::doLevelUp()
{
    while (XP_ >= XPTillLevel_)
    {
        QSound::play("../Sounds/levelUp.wav");
        QMessageBox msgBox;
        msgBox.setWindowTitle("Level Up");
        msgBox.setText("      LEVEL UP!               ");
        msgBox.exec();
        level_+= 1;
        //maxHealth_+= 10;
        health_ = maxHealth_;
        //maxAttackPower_+= 10;
        //minAttackPower_+= 10;

        //if (critChance_ > 5)
        //    critChance_-= 5;
        skillpoints_ += 3;
        XP_ -= XPTillLevel_;
        XPTillLevel_ *= 2;
        critNum_ = 0;

        if (level_ == 10)
        {
            msgBox.setWindowTitle("Level Up");
            msgBox.setText(        "<b>You have reached level 10 and unlocked a special ability!</b>");
            msgBox.setInformativeText("This ability does <b>3x</b> your max attack power,\n"
                                      "but it needs to be charged before use.\n"
                                      "After <b>3</b> successfull hits on your enemy,\n"
                                      "the ability will be charged and can be used.");
            msgBox.exec();
            learnSpecialAbility();
        }
    }
}

void Player::usePotion()
{
    if (potion_ >= 1)
    {
        if (health_ == maxHealth_)
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Use Potion");
            msgBox.setText("Your health is full.");
            msgBox.exec();
        }
        else if (level_ <= 14)
        {
            health_ += 50;
            potion_ -= 1;
            if (health_ > maxHealth_)
                health_ = maxHealth_;
            QSound::play("../Sounds/drinkPotion.wav");
            QMessageBox msgBox;
            msgBox.setWindowTitle("Use Potion");
            msgBox.setText("      Potion used.            ");
            msgBox.exec();

        }
        else if (level_ >= 15 && level_ <= 29)
        {
            health_ += 75;
            potion_ -= 1;
            if (health_ > maxHealth_)
                health_ = maxHealth_;
            QSound::play("../Sounds/drinkPotion.wav");
            QMessageBox msgBox;
            msgBox.setWindowTitle("Use Potion");
            msgBox.setText("      Potion used.            ");
            msgBox.exec();
        }
        else if (level_ >= 30)
        {
            health_ += 100;
            potion_ -= 1;
            if (health_ > maxHealth_)
                health_ = maxHealth_;
            QSound::play("../Sounds/drinkPotion.wav");
            QMessageBox msgBox;
            msgBox.setWindowTitle("Use Potion");
            msgBox.setText("      Potion used.            ");
            msgBox.exec();
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Use Potion");
        msgBox.setText("You do not have a potion.");
        msgBox.exec();
    }
}

void Player::buyPotion()
{
    if (gold_ >= 5)
    {
        if (potion_ == 10)
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Buy Potion");
            msgBox.setText("You cannot carry any more potions.");
            msgBox.exec();
        }
        else if (level_<= 12)
        {
            QSound::play("../Sounds/potionDrop.wav");
            gold_ -= 5;
            potion_ += 1;
            QMessageBox msgBox;
            msgBox.setWindowTitle("Buy Potion");
            msgBox.setText("You bought a potion.");
            msgBox.exec();
        }
        else if (level_ >= 13 && level_ <= 14)
        {
            QSound::play("../Sounds/potionDrop.wav");
            gold_ -= 8;
            potion_ += 1;
            QMessageBox msgBox;
            msgBox.setWindowTitle("Buy Potion");
            msgBox.setText("You bought a potion.");
            msgBox.exec();
        }
        else if (level_ >= 15)
        {
            QSound::play("../Sounds/potionDrop.wav");
            gold_ -= 10;
            potion_ += 1;
            QMessageBox msgBox;
            msgBox.setWindowTitle("Buy Potion");
            msgBox.setText("You bought a potion.");
            msgBox.exec();
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Buy Potion");
        msgBox.setText("You do not have enough gold.");
        msgBox.exec();
    }
}

QString Player::printPlayerInfo()
{
    QString info = QString("Character Info\n------------------------------------\nName: %1\nHealth: %2/%3\nAttack: %4-%5\nLevel: %6\nCritical Hit Chance: %7\nGold: %8\nPotions: %9\nCurrent XP: %10/%11\nXP Till Next Level: %12")
            .arg(name_).arg(health_).arg(maxHealth_)
            .arg(minAttackPower_).arg(maxAttackPower_).arg(level_).arg(critChance_).arg(gold_)
            .arg(potion_).arg(XP_).arg(XPTillLevel_).arg(XPTillLevel_ - XP_);

    return info;
}

void Player::save()
{
    QFile file("mySave.save");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream saveFile(&file);
    saveFile << name_ << "\n";
    saveFile << health_ << "\n";
    saveFile << maxHealth_ << "\n";
    saveFile << minAttackPower_ << "\n";
    saveFile << maxAttackPower_ << "\n";
    saveFile << level_ << "\n";
    saveFile << critChance_ << "\n";
    saveFile << gold_ << "\n";
    saveFile << potion_ << "\n";
    saveFile << XP_ << "\n";
    saveFile << XPTillLevel_ << "\n";
    saveFile << isAlive_ << "\n";
    saveFile << critNum_ << "\n";
    saveFile << skillpoints_ << "\n";
    saveFile << specialAbilityCharge_ << "\n";
    saveFile << specialAbilityCharged_ << "\n";
    saveFile << specialAbilityMaxCharges_ << "\n";
    saveFile << isSpecialAbilityLearned_ << "\n";
    saveFile << isSpecialReady_ << "\n";
    file.close();
}

void Player::load()
{
    QFile file("mySave.save");
    file.open(QIODevice::ReadOnly| QIODevice::Text);
    QTextStream saveFile(&file);
    if (file.exists() && file.isOpen())
    {
        name_ = saveFile.readLine();
        health_ = saveFile.readLine().toInt();
        maxHealth_ = saveFile.readLine().toInt();
        minAttackPower_ = saveFile.readLine().toInt();
        maxAttackPower_ = saveFile.readLine().toInt();
        level_ = saveFile.readLine().toInt();
        critChance_ = saveFile.readLine().toInt();
        gold_ = saveFile.readLine().toInt();
        potion_ = saveFile.readLine().toInt();
        XP_ = saveFile.readLine().toInt();
        XPTillLevel_ = saveFile.readLine().toInt();
        isAlive_ = saveFile.readLine().toInt();
        critNum_ = saveFile.readLine().toInt();
        skillpoints_ = saveFile.readLine().toInt();
        specialAbilityCharge_ = saveFile.readLine().toInt();
        specialAbilityCharged_ = saveFile.readLine().toInt();
        specialAbilityMaxCharges_ = saveFile.readLine().toInt();
        isSpecialAbilityLearned_ = saveFile.readLine().toInt();
        isSpecialReady_ = saveFile.readLine().toInt();
        file.close();
    }
}

bool Player::isAlive()
{
    return isAlive_;
}

int Player::getHealth()
{
    return health_;
}

void Player::setHealth(int health)
{
    health_ = health;
}

int Player::getMaxAttackPower()
{
    return maxAttackPower_;
}

void Player::setMaxAttackPower(int maxAttackPower)
{
    maxAttackPower_ += maxAttackPower;
}

int Player::getMinAttackPower()
{
    return minAttackPower_;
}

void Player::setMinAttackPower(int minAttackPower)
{
    QString maxAtk = QString::number(maxAttackPower_);
    if (maxAtk.endsWith('0'))
    {
        minAttackPower_ += minAttackPower;
    }
}

int Player::getCritChance()
{
    return critChance_;
}

void Player::setCritChance(int critChance)
{
    critChance_ -= critChance;
}

int Player::getMaxHealth()
{
    return maxHealth_;
}

void Player::setMaxHealth(int maxHealth)
{
    maxHealth_ += maxHealth;
}

int Player::getLevel()
{
    return level_;
}

void Player::setLevel(int level)
{
    level_ = level;
}

int Player::getAttackDmg()
{
    return attackDmg_;
}

int Player::getXP()
{
    return XP_;
}

void Player::addXP(int XP)
{
    XP_ += XP;
}

int Player::getXPTillLevel()
{
    return XPTillLevel_;
}

void Player::setXPTillLevel(int XPTillLevel)
{
    XPTillLevel_ = XPTillLevel;
}

int Player::getSkillPoints()
{
    return skillpoints_;
}

void Player::setSkillPoints(int skillPoints)
{
    skillpoints_ -= skillPoints;
}

int Player::getPotion()
{
    return potion_;
}

void Player::addPotion(int potion)
{
    if (potion_ == 10)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Buy Potion");
        msgBox.setText("You cannot carry any more potions.");
        msgBox.exec();
    }
    else
        potion_ += potion;
}

int Player::getGold()
{
    return gold_;
}

void Player::addGold(int gold)
{
    gold_ += gold;
}

QString Player::getName()
{
    return name_;
}

void Player::setName(QString name)
{
    name_ = name;
}

QString Player::getMessage()
{
    return message_;
}

void Player::setMessage(QString message)
{
    message_ = message;
}

int Player::getSpecialAbilityMaxCharges()
{
    return specialAbilityMaxCharges_;
}

void Player::setSpecialAbilityMaxCharges(int specialAbilityMaxCharges)
{
    specialAbilityMaxCharges_ = specialAbilityMaxCharges;
}

int Player::getSpecialAbilityCharge()
{
    return specialAbilityCharge_;
}

void Player::addSpecialAbilityCharge(int specialAbilityCharge)
{
    if (specialAbilityCharged_ != specialAbilityMaxCharges_)
        specialAbilityCharge_ += specialAbilityCharge;

    if (specialAbilityCharge_ == 3 && specialAbilityCharged_ != specialAbilityMaxCharges_)
    {
        isSpecialReady_ = true;
        specialAbilityCharged_ = 1;
    }
}

int Player::getSpecialAbilityCharged()
{
    return specialAbilityCharged_;
}

void Player::setSpecialAbilityCharged(int specialAbilityCharged)
{
    specialAbilityCharged_ = specialAbilityCharged;
}

bool Player::isSpecialAbilityLeanred()
{
    return isSpecialAbilityLearned_;
}

void Player::learnSpecialAbility()
{
    isSpecialAbilityLearned_ = true;
    isSpecialReady_ = false;
    specialAbilityCharge_ = 0;
    specialAbilityCharged_ = 0;
    specialAbilityMaxCharges_ = 1;
}

bool Player::IsSpecialReady()
{
    return isSpecialReady_;
}

void Player::setIsSpecialReady(bool isSpecialReady)
{
    isSpecialReady_ = isSpecialReady;
}

