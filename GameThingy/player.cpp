#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <QTime>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QSound>
#include <QVector>
#include <algorithm>
#include "player.h"
#include "item.h"


Player::Player(int health, int maxHealth, int maxAttackPower, int minAttackPower,
               int vitality, int strength, int agility, int luck, int intelligence, int hit, int stamina, int maxStamina,
               int agilityDefault, int luckDefault)
    : health_(health),
      maxHealth_(maxHealth),
      maxAttackPower_(maxAttackPower),
      minAttackPower_(minAttackPower),
      vitality_(vitality),
      strength_(strength),
      agility_(agility),
      luck_(luck),
      intelligence_(intelligence),
      hit_(hit),
      stamina_(stamina),
      maxStamina_(maxStamina),
      agilityDefault_(agilityDefault),
      luckDefault_(luckDefault)
{
    level_ = 1;
    XP_ = 0;
    XPTillLevel_ = 500;
    isAlive_ = true;
    potion_ = 0;
    ration_ = 0;
    gold_ = 0;
    skillpoints_ = 0;
    specialAbilityCharge_ = 0;
    specialAbilityCharged_ = 0;
    specialAbilityMaxCharges_ = 0;
    strengthCount_ = 0;
    agilityCount_ = 0;
    luckCount_ = 0;
    intelligenceCount_ = 0;
    hitCount_ = 0;
    agilityBonus_ = 0;
    luckBonus_ = 0;
    intelligenceBonus_ = 0;
    hitBonus_ = 0;
    isSpecialAbilityLearned_ = false;
    isSpecialReady_ = false;
    wasHealed_ = false;
    rationConsumed_ = false;
    questsCompleted_ = 0;
    location_ = 0;
    qsrand(QTime::currentTime().msec());
}


Player::~Player(void)
{
}

int Player::doAttack(QString enemy)
{
    int critRoll;

    attackDmg_ = rand() % ((maxAttackPower_ + 1) - minAttackPower_) + minAttackPower_;

    critRoll   = rand() % ((20 + 1) - 1) + 1;

    if (stamina_ == 0)
        attackDmg_ = attackDmg_ / 2;

    if (attackDmg_ == 0)
        attackDmg_ = 1;

    if (critRoll >= luckDefault_ - luckBonus_)
    {
        attackDmg_*= 2;
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

    if (stamina_ == 0)
        attackDmg_ = attackDmg_ / 2;

    message_ = name_ + " Attacks " + enemy + " for " + QString("%1").arg(attackDmg_) + " damage.\n";

    isSpecialReady_ = false;
    specialAbilityCharge_ = 0;
    specialAbilityCharged_ = 0;

    return attackDmg_;
}

int Player::doHitRoll()
{
    int hitRoll = rand()% ((20 + 1) - 1) + 1;
    return hitRoll + hitBonus_;
}

void Player::doHit(int dmg, int enemyHitRoll, QString enemyName, bool isEnemyAlive)
{
    int dodgeChance = agilityDefault_ + agilityBonus_;

    if (stamina_ == 0)
        dodgeChance = (agilityDefault_ + agilityBonus_) / 2;

    if (!isEnemyAlive)
    {
        message_ = name_ + " Wins the battle!\n\n";
    }
    else
    {
        if (enemyHitRoll >= dodgeChance)
        {
            health_ = health_ - dmg;
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
        else
            message_ = name_ + " dodges " + enemyName + "'s attack.\n\n";
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
        QSound::play("Sounds\\levelUp.wav");
        QMessageBox msgBox;
        msgBox.setWindowTitle("Level Up");
        msgBox.setText("      LEVEL UP!               ");
        msgBox.exec();
        level_+= 1;
        //maxHealth_+= 10;
        health_ = maxHealth_;
        stamina_ = maxStamina_;
        //maxAttackPower_+= 10;
        //minAttackPower_+= 10;

        //if (critChance_ > 5)
        //    critChance_-= 5;
        skillpoints_ += 4;
        XP_ -= XPTillLevel_;
        XPTillLevel_ = int(double(XPTillLevel_) * 1.5);

        if (level_ == 2)
        {
            msgBox.setWindowTitle("Level Up");
            msgBox.setText("<b>You achieved your first level up!</b><br>"
                           "---------------------------------------------------------------------<br><br>"
                           "Every time you level, you get 4 skill points to distribute between<br>"
                           "any of these 6 stats<br><br>"
                           "<b>Vitality</b><br>"
                           "Determines the amount of damage you can take from enemies.<br>"
                           "Each point towards Vitality increases your HP by 2<br><br>"
                           "<b>Strength</b><br>"
                           "Determines how much damage you can do to enemies<br>"
                           "Each point towards Strength increases your maximum amount of damage by 1<br>"
                           "and every 5 points increases your minimum amount of damage by 5<br><br>"
                           "<b>Stamina</b><br>"
                           "Determines how many actions you can take in  day<br>"
                           "Each point towards stamina increases you maximum amount of stamina by 1<br><br>"
                           "<b>Agility</b><br>"
                           "Determines the chance at which you can dodge an enemy's attack<br>"
                           "Each 5 points towards Agility increases your chance at dodging<br>"
                           "an enemy's attack<br><br>"
                           "<b>Luck</b><br>"
                           "Determines the chance your attack can critically damage an enemy<br>"
                           "Each 5 points towards Luck increases your chance at critically<br>"
                           "damaging an enemy<br>"
                           "critical strikes cause 2x your maximum damage potential but can<br>"
                           "still be dodged by an enemy<br><br>"
                           "<b>Precision</b><br>"
                           "Determines the chance at which you can successfully strike an enemy<br>"
                           "Each 5 points towards Hit increases your chance to successfully "
                           "strike an enemy<br><br>"
                           "Each skill can be raised to a maximum of 20, so spend your<br>"
                           "skill points wisely.");
            msgBox.exec();
        }

        if (level_ == 10)
        {
            msgBox.setWindowTitle("Level Up");
            msgBox.setText(        "<b>You have reached level 10 and unlocked a special ability!</b>");
            msgBox.setInformativeText("This ability does <b>3x</b> your max attack power,\n"
                                      "but it needs to be charged before use.\n"
                                      "After <b>3</b> successfull hits on your enemy,\n"
                                      "the ability will be charged and can be used.\n"
                                      "<b>This ability cannot be dodged.</b>");
            msgBox.exec();
            learnSpecialAbility();
        }
    }
}

void Player::usePotion(int healAmount)
{
    //if (potion_ >= 1)
    //{
        if (health_ == maxHealth_)
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Use Potion");
            msgBox.setText("Your health is full.");
            msgBox.exec();
            wasHealed_ = false;
        }
        else
        {
            health_ += healAmount;
            //potion_ -= 1;
            if (health_ > maxHealth_)
                health_ = maxHealth_;
            QSound::play("Sounds\\drinkPotion.wav");
            QMessageBox msgBox;
            msgBox.setWindowTitle("Use Potion");
            msgBox.setText("      Potion used.            ");
            msgBox.exec();
            wasHealed_ = true;
        }
   // }
   // else
//    {
//        QMessageBox msgBox;
//        msgBox.setWindowTitle("Use Potion");
//        msgBox.setText("You do not have a potion.");
//        msgBox.exec();
//    }
}

void Player::buyPotion()
{
    if (gold_ >= 20)
    {
        if (potion_ == 10)
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Buy Potion");
            msgBox.setText("You cannot carry any more potions.");
            msgBox.exec();
        }
        else
        {
            QSound::play("Sounds\\potionDrop.wav");
            gold_ -= 20;
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

void Player::useRation(int stamAmount)
{
//    if (ration_ >= 1)
//    {
        if (stamina_ == maxStamina_)
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Use Ration");
            msgBox.setText("Your stamina is full.");
            msgBox.exec();
            rationConsumed_ = false;
        }
        else
        {
            stamina_ += stamAmount;
            //ration_ -= 1;
            if (stamina_ > maxStamina_)
                stamina_ = maxStamina_;
            QSound::play("Sounds\\eatRation.wav");
            QMessageBox msgBox;
            msgBox.setWindowTitle("Use Ration");
            msgBox.setText("      Ration used.            ");
            msgBox.exec();
            rationConsumed_ = true;
        }
//    }
//    else
//    {
//        QMessageBox msgBox;
//        msgBox.setWindowTitle("Use Ration");
//        msgBox.setText("You do not have a ration.");
//        msgBox.exec();
//    }
}

void Player::buyRation()
{
    if (gold_ >= 30)
    {
        if (ration_ == 10)
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Buy Ration");
            msgBox.setText("You cannot carry any more rations.");
            msgBox.exec();
        }
        else
        {
            QSound::play("Sounds\\rationDrop.wav");
            gold_ -= 30;
            ration_ += 1;
            QMessageBox msgBox;
            msgBox.setWindowTitle("Buy Ration");
            msgBox.setText("You bought a ration.");
            msgBox.exec();
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Buy Ration");
        msgBox.setText("You do not have enough gold.");
        msgBox.exec();
    }
}

void Player::save()
{
    QString fileName = "saves\\Save" + name_ + ".save";
    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream saveFile(&file);
    saveFile << name_ << "\n";
    saveFile << health_ << "\n";
    saveFile << maxHealth_ << "\n";
    saveFile << minAttackPower_ << "\n";
    saveFile << maxAttackPower_ << "\n";
    saveFile << level_ << "\n";
    saveFile << gold_ << "\n";
    saveFile << potion_ << "\n";
    saveFile << XP_ << "\n";
    saveFile << XPTillLevel_ << "\n";
    saveFile << isAlive_ << "\n";
    saveFile << skillpoints_ << "\n";
    saveFile << specialAbilityCharge_ << "\n";
    saveFile << specialAbilityCharged_ << "\n";
    saveFile << specialAbilityMaxCharges_ << "\n";
    saveFile << isSpecialAbilityLearned_ << "\n";
    saveFile << isSpecialReady_ << "\n";
    saveFile << vitality_ << "\n";
    saveFile << strength_ << "\n";
    saveFile << agility_ << "\n";
    saveFile << agilityBonus_ << "\n";
    saveFile << agilityDefault_ << "\n";
    saveFile << luck_ << "\n";
    saveFile << luckBonus_ << "\n";
    saveFile << luckDefault_ << "\n";
    saveFile << intelligence_ << "\n";
    saveFile << intelligenceBonus_ << "\n";
    saveFile << agilityCount_ << "\n";
    saveFile << luckCount_ << "\n";
    saveFile << intelligenceCount_ << "\n";
    saveFile << questsCompleted_ << "\n";
    saveFile << hit_ << "\n";
    saveFile << hitCount_ << "\n";
    saveFile << hitBonus_ << "\n";
    saveFile << stamina_ << "\n";
    saveFile << maxStamina_ << "\n";
    saveFile << ration_ << "\n";
    saveFile << location_ << "\n";
    file.close();
}

void Player::load(QString playerName)
{
    QString fileName = "saves\\Save" + playerName + ".save";
    QFile file(fileName);
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
        gold_ = saveFile.readLine().toInt();
        potion_ = saveFile.readLine().toInt();
        XP_ = saveFile.readLine().toInt();
        XPTillLevel_ = saveFile.readLine().toInt();
        isAlive_ = saveFile.readLine().toInt();
        skillpoints_ = saveFile.readLine().toInt();
        specialAbilityCharge_ = saveFile.readLine().toInt();
        specialAbilityCharged_ = saveFile.readLine().toInt();
        specialAbilityMaxCharges_ = saveFile.readLine().toInt();
        isSpecialAbilityLearned_ = saveFile.readLine().toInt();
        isSpecialReady_ = saveFile.readLine().toInt();
        vitality_ = saveFile.readLine().toInt();
        strength_ = saveFile.readLine().toInt();
        agility_ = saveFile.readLine().toInt();
        agilityBonus_ = saveFile.readLine().toInt();
        agilityDefault_ = saveFile.readLine().toInt();
        luck_ = saveFile.readLine().toInt();
        luckBonus_ = saveFile.readLine().toInt();
        luckDefault_ = saveFile.readLine().toInt();
        intelligence_ = saveFile.readLine().toInt();
        intelligenceBonus_ = saveFile.readLine().toInt();
        agilityCount_ = saveFile.readLine().toInt();
        luckCount_ = saveFile.readLine().toInt();
        intelligenceCount_ = saveFile.readLine().toInt();
        questsCompleted_ = saveFile.readLine().toInt();
        hit_ = saveFile.readLine().toInt();
        hitCount_ = saveFile.readLine().toInt();
        hitBonus_ = saveFile.readLine().toInt();
        stamina_ = saveFile.readLine().toInt();
        maxStamina_ = saveFile.readLine().toInt();
        ration_ = saveFile.readLine().toInt();
        location_ = saveFile.readLine().toInt();
        file.close();
    }
}

void Player::addVitality(int vitality)
{
    vitality_ += vitality;
    maxHealth_ += 2;
}

int Player::getVitality()
{
    return vitality_;
}

void Player::addStrength(int strength)
{
    strength_ += strength;
    strengthCount_ += strength;
    maxAttackPower_ += strength;

    if (strengthCount_ == 5)
    {
        minAttackPower_ += 5;
        strengthCount_ = 0;
    }
}

int Player::getStrength()
{
    return strength_;
}

void Player::addAgility(int agility)
{
    agility_ += agility;
    agilityCount_ += agility;

    if (agilityCount_ == 5)
    {
        agilityBonus_ += 1;
        agilityCount_ = 0;
    }
}

int Player::getAgility()
{
    return agility_;
}

void Player::addLuck(int luck)
{
    luck_ += luck;
    luckCount_ += luck;

    if (luckCount_ == 5)
    {
        luckBonus_ += 1;
        luckCount_ = 0;
    }
}

int Player::getLuck()
{
    return luck_;
}

void Player::addIntelligence(int intelligence)
{
    intelligence_ += intelligence;
    intelligenceCount_ += intelligence;

    if (intelligenceCount_ == 5)
    {
        intelligenceBonus_ += 1;
        intelligenceCount_ = 0;
    }
}

int Player::getIntelligence()
{
    return intelligence_;
}

void Player::addHit(int hit)
{
    hit_ += hit;
    hitCount_ += hit;

    if (hitCount_ == 5)
    {
        hitBonus_ += 1;
        hitCount_ = 0;
    }
}

int Player::getHit()
{
    return hit_;
}

void Player::setStamina(int stamina)
{
    stamina_ = stamina;
}

void Player::addStamina(int stamina)
{
    stamina_ += stamina;

    if (stamina_ > maxStamina_)
        stamina_ = maxStamina_;
}

void Player::removeStamina(int action)
{
    if (action == 0) //travel
        stamina_ -= 2;
    else if (action == 1) //battle
        stamina_ -= 1;

    if (stamina_ <= 0)
        stamina_ = 0;
}

int Player::getStamina()
{
    return stamina_;
}

int Player::getMaxStamina()
{
    return maxStamina_;
}

void Player::addMaxStamina(int maxStamina)
{
    maxStamina_ += maxStamina;
    stamina_ = maxStamina_;
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

void Player::addHealth(int health)
{
    health_ += health;

    if (health_ > maxHealth_)
        health_ = maxHealth_;
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

int Player::getRation()
{
    return ration_;
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

void Player::addRation(int ration)
{
    if (ration_ == 10)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Buy Ration");
        msgBox.setText("You cannot carry any more rations.");
        msgBox.exec();
    }
    else
        ration_ += ration;
}

void Player::removeRation()
{
    ration_ -= 1;
}

int Player::getGold()
{
    return gold_;
}

void Player::addGold(int gold)
{
    gold_ += gold;
}

void Player::removeGold(int gold)
{
    gold_ -= gold;
}

QVector<Item> Player::getInventory()
{
    return inventory_;
}

void Player::addItemsToInventory(QVector<Item> items)
{
    for (int i = 0; i < items.length(); i++)
    {
//        if (inventory_.length() > 0)
//        {
//            for (int j = 0; j < inventory_.length(); j++)
//            {
//                if (inventory_.value(j).name == items.value(i).name)
//                {
//                    int invAmount = inventory_.value(j).amount;
//                    int itemAmount = items.value(i).amount;
//                    //inventory_.erase(inventory_.begin() + j);
//                    inventory_.removeAt(j);
//                    Item newItem;
//                    newItem.name = items.value(i).name;
//                    newItem.itemRarity = items.value(i).itemRarity;
//                    newItem.itemType = items.value(i).itemType;
//                    newItem.armourRating = items.value(i).armourRating;
//                    newItem.armourType = items.value(i).armourType;
//                    newItem.healType = items.value(i).healType;
//                    newItem.healAmount = items.value(i).healAmount;
//                    newItem.isEquippable = items.value(i).isEquippable;
//                    newItem.sellPrice = items.value(i).sellPrice;
//                    newItem.isUsable = items.value(i).isUsable;
//                    newItem.weight = items.value(i).weight;
//                    newItem.minAtk = items.value(i).minAtk;
//                    newItem.maxAtk = items.value(i).maxAtk;
//                    newItem.block = items.value(i).block;
//                    newItem.holdType = items.value(i).holdType;
//                    newItem.stat1 = items.value(i).stat1;
//                    newItem.stat2 = items.value(i).stat2;
//                    newItem.stat3 = items.value(i).stat3;
//                    newItem.statType1 = items.value(i).statType1;
//                    newItem.statType2 = items.value(i).statType2;
//                    newItem.statType3 = items.value(i).statType3;
//                    newItem.amount = invAmount + itemAmount;
//                    inventory_.push_back(newItem);
//                }
//                else
//                {
//                    inventory_.push_back(items.value(i));
//                }
//            }
//        }
//        else
//        {
//            inventory_.push_back(items.value(i));
//        }
        inventory_.push_back(items.value(i));
    }
}

void Player::removeItemFromInventory(int index)
{
    inventory_.remove(index);
}

QVector<Item> Player::getEquiped()
{
    return equipment_;
}

void Player::addEquipment(Item item)
{
    equipment_.push_back(item);
}

void Player::removeEquipment(int index)
{
    equipment_.remove(index);
}

int Player::getLocation()
{
    return location_;
}

void Player::setLocation(int location)
{
    location_ = location;
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
    if (isSpecialAbilityLearned_)
    {
        if (specialAbilityCharged_ != specialAbilityMaxCharges_)
            specialAbilityCharge_ += specialAbilityCharge;

        if (specialAbilityCharge_ == 3 && specialAbilityCharged_ != specialAbilityMaxCharges_)
        {
            isSpecialReady_ = true;
            specialAbilityCharged_ = 1;
        }
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

bool Player::wasHealed()
{
    return wasHealed_;
}

bool Player::rationconsumed()
{
    return rationConsumed_;
}

int Player::getQuestsCompleted()
{
    return questsCompleted_;
}

void Player::completeQuest()
{
    questsCompleted_ += 1;
}
