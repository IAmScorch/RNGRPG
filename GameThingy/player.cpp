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


Player::Player(int defaultHealth, int intelligence, int defaultStamina,
               int agilityDefault, int luckDefault, int classType)
    : defaultHealth_(defaultHealth),
      maxHealth_(defaultHealth_),
      classType_(classType),
      agilityDefault_(agilityDefault),
      luckDefault_(luckDefault),
      intelligence_(intelligence),
      defaultStamina_(defaultStamina)
{
    level_ = 1;
    XP_ = 0;
    XPTillLevel_ = 500;
    health_ = defaultHealth;
    strength_ = 0;
    maxStamina_ = defaultStamina;
    stamina_ = defaultStamina;
    agility_ = agilityDefault;
    luck_ = luckDefault;
    precision_ = 0;
    isAlive_ = true;
    maxAttackPower_ = 0;
    minAttackPower_ = 0;
    maxWeaponAP_ = 0;
    minWeaponAP_ = 0;
    potion_ = 0;
    ration_ = 0;
    gold_ = 0;
    minAttackPower_ = 0;
    maxAttackPower_ = 0;
    skillpoints_ = 0;
    specialAbilityCharge_ = 0;
    specialAbilityCharged_ = 0;
    specialAbilityMaxCharges_ = 0;
    intelligenceBonus_ = 0;
    block_ = 0;
    isSpecialAbilityLearned_ = false;
    isSpecialReady_ = false;
    questsCompleted_ = 0;
    location_ = 0;
    statVitality_ = 0;
    statAgility_ = 0;
    statLuck_ = 0;
    statPrecision_ = 0;
    statStrength_ = 0;
    statStamina_ = 0;
    statIntelligence_ = 0;
    equippedAgility_ = 0;
    equippedVitality_ = 0;
    equippedLuck_ = 0;
    equippedIntelligence_ = 0;
    equippedLuck_ = 0;
    equippedPrecision_ = 0;
    equippedStamina_ = 0;
    equippedStrength_ = 0;
    isShieldEquipped_ = false;
    mainHandSlot_ = 0;
    offHandSlot_ = 0;
    armourSlot_ = 0;
    ringSlotOne_ = 0;
    ringSlotTwo_ = 0;
    trinketSlotOne_ = 0;
    trinketSlotTwo_ = 0;
    classXRef_ = new itemCrossReference();
    hasBedroll_ = 0;
    hasFireStarterKit_ = 0;
    armourType_ = 0;
    rogueDblAtkBonus_ = 0;
    warTwoHandAtkBonus_ = 0;
    knightAbsorbBonus_ = 0;
    knightBlockBonus_ = 0;
    fireStarterKitAmount_ = 0;
    hasBedroll_ = false;
    hasFireStarterKit_ = false;
    qsrand(QTime::currentTime().msec());
}


Player::~Player(void)
{
}

int Player::doAttack(QString enemy)
{
    int critRoll;

    if (classType_ == 3 && warTwoHandAtkBonus_ >= 1)
    {
        double atkBonus = warTwoHandAtkBonus_ * .10;
        atkBonus+=1;
        attackDmg_ = (rand() % ((maxAttackPower_ + 1) - minAttackPower_) + minAttackPower_);
        attackDmg_*= atkBonus;
    }
    else
        attackDmg_ = rand() % ((maxAttackPower_ + 1) - minAttackPower_) + minAttackPower_;


    critRoll   = rand() % ((20 + 1) - 1) + 1;

    if (stamina_ == 0)
        attackDmg_ = attackDmg_ / 2;

    if (attackDmg_ == 0)
        attackDmg_ = 1;

    if (critRoll >= luck_)
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
    return hitRoll + precision_;
}

void Player::doHit(int dmg, int enemyHitRoll, QString enemyName, bool isEnemyAlive, int enemyDotType)
{
    int dodgeChance = agility_;

    if (stamina_ == 0)
        dodgeChance = (agilityDefault_) / 2;

    if (!isEnemyAlive)
    {
        message_ = name_ + " Wins the battle!\n\n";
        dot_.clear();
    }
    else
    {
        if (enemyHitRoll >= dodgeChance)
        {
            if (enemyHitRoll >= block_ + getShieldBlockBonus())
            {
                int dotChance = rand() % ((100 + 1) - 1) + 1;
                bool absorbed = false;
                //int orgDmg = dmg;

                if (classType_ == 4 && didKnightAbsorb(enemyHitRoll))
                {
                    absorbed = 2;
                    dmg /= 2;
                }

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
                {
                    if (absorbed)
                        message_ = name_ + " absorbed " + enemyName + "'s attack, taking only " + QString("%1").arg(dmg) + " damage.\n\n";
                    else
                        message_ = name_ + " takes " + QString("%1").arg(dmg) + " damage.\n\n";

                    DoT dotInfo;
                    int dotEffectiveness = rand()% 5 + 3;

                    if (armourType_ == 0)
                    {
                        if (enemyDotType == 1 && dotChance >= 50)
                        {
                            dotInfo.name = "Bleeding";
                            dotInfo.dotType = enemyDotType;
                            dotInfo.dotDamage = 1;

                            for (int i = 0; i < dotEffectiveness; i++)
                            {
                                dot_.push_back(dotInfo);
                            }

                            message_ += enemyName + " slashed you and caused a " + dotInfo.name + " effect\n\n";
                        }
                        else if (enemyDotType == 2 && dotChance >= 30)
                        {
                            dotInfo.name = "Blunt Trauma";
                            dotInfo.dotType = enemyDotType;
                            dotInfo.dotDamage = 1;

                            for (int i = 0; i < dotEffectiveness; i++)
                            {
                                dot_.push_back(dotInfo);
                            }

                            message_ += enemyName + " crushed you and caused a " + dotInfo.name + " effect\n\n";
                        }
                        else if (enemyDotType == 3 && dotChance >= 50)
                        {
                            dotInfo.name = "Poison";
                            dotInfo.dotType = enemyDotType;
                            dotInfo.dotDamage = 1;

                            for (int i = 0; i < dotEffectiveness; i++)
                            {
                                dot_.push_back(dotInfo);
                            }

                            message_ += enemyName + " slashed you with a poison laced blade and caused a " + dotInfo.name + " effect\n\n";
                        }
                    }
                    else if (armourType_ == 1)
                    {
                        if (enemyDotType == 1 && dotChance >= 80)
                        {
                            dotInfo.name = "Bleeding";
                            dotInfo.dotType = enemyDotType;
                            dotInfo.dotDamage = 1;

                            for (int i = 0; i < dotEffectiveness; i++)
                            {
                                dot_.push_back(dotInfo);
                            }

                            message_ += enemyName + " slashed you and caused a " + dotInfo.name + " effect\n\n";
                        }
                        else if (enemyDotType == 2 && dotChance >= 60)
                        {
                            dotInfo.name = "Blunt Trauma";
                            dotInfo.dotType = enemyDotType;
                            dotInfo.dotDamage = 1;

                            for (int i = 0; i < dotEffectiveness; i++)
                            {
                                dot_.push_back(dotInfo);
                            }

                            message_ += enemyName + " crushed you and caused a " + dotInfo.name + " effect\n\n";
                        }
                        else if (enemyDotType == 3 && dotChance >= 80)
                        {
                            dotInfo.name = "Poison";
                            dotInfo.dotType = enemyDotType;
                            dotInfo.dotDamage = 1;

                            for (int i = 0; i < dotEffectiveness; i++)
                            {
                                dot_.push_back(dotInfo);
                            }

                            message_ += enemyName + " slashed you with a poison laced blade and caused a " + dotInfo.name + " effect\n\n";
                        }
                    }
                    else if (armourType_ == 2)
                    {
                        if (enemyDotType == 1 && dotChance >= 85)
                        {
                            dotInfo.name = "Bleeding";
                            dotInfo.dotType = enemyDotType;
                            dotInfo.dotDamage = 1;

                            for (int i = 0; i < dotEffectiveness; i++)
                            {
                                dot_.push_back(dotInfo);
                            }

                            message_ += enemyName + " slashed you and caused a " + dotInfo.name + " effect\n\n";
                        }
                        else if (enemyDotType == 2 && dotChance >= 65)
                        {
                            dotInfo.name = "Blunt Trauma";
                            dotInfo.dotType = enemyDotType;
                            dotInfo.dotDamage = 1;

                            for (int i = 0; i < dotEffectiveness; i++)
                            {
                                dot_.push_back(dotInfo);
                            }

                            message_ += enemyName + " crushed you and caused a " + dotInfo.name + " effect\n\n";
                        }
                        else if (enemyDotType == 3 && dotChance >= 85)
                        {
                            dotInfo.name = "Poison";
                            dotInfo.dotType = enemyDotType;
                            dotInfo.dotDamage = 1;

                            for (int i = 0; i < dotEffectiveness; i++)
                            {
                                dot_.push_back(dotInfo);
                            }

                            message_ += enemyName + " slashed you with a poison laced blade and caused a " + dotInfo.name + " effect\n\n";
                        }
                    }
                    else if (armourType_ == 3)
                    {
                        if (enemyDotType == 1 && dotChance >= 90)
                        {
                            dotInfo.name = "Bleeding";
                            dotInfo.dotType = enemyDotType;
                            dotInfo.dotDamage = 1;

                            for (int i = 0; i < dotEffectiveness; i++)
                            {
                                dot_.push_back(dotInfo);
                            }

                            message_ += enemyName + " slashed you and caused a " + dotInfo.name + " effect\n\n";
                        }
                        else if (enemyDotType == 2 && dotChance >= 70)
                        {
                            dotInfo.name = "Blunt Trauma";
                            dotInfo.dotType = enemyDotType;
                            dotInfo.dotDamage = 1;

                            for (int i = 0; i < dotEffectiveness; i++)
                            {
                                dot_.push_back(dotInfo);
                            }

                            message_ += enemyName + " crushed you and caused a " + dotInfo.name + " effect\n\n";
                        }
                        else if (enemyDotType == 3 && dotChance >= 90)
                        {
                            dotInfo.name = "Poison";
                            dotInfo.dotType = enemyDotType;
                            dotInfo.dotDamage = 1;

                            for (int i = 0; i < dotEffectiveness; i++)
                            {
                                dot_.push_back(dotInfo);
                            }

                            message_ += enemyName + " slashed you with a poison laced blade and caused a " + dotInfo.name + " effect\n\n";
                        }
                    }
                    else if (armourType_ == 4)
                    {
                        int BTBonus = (block_ / 5) * 5;

                        if (enemyDotType == 1 && dotChance >= 95)
                        {
                            dotInfo.name = "Bleeding";
                            dotInfo.dotType = enemyDotType;
                            dotInfo.dotDamage = 1;

                            for (int i = 0; i < dotEffectiveness; i++)
                            {
                                dot_.push_back(dotInfo);
                            }

                            message_ += enemyName + " slashed you and caused a " + dotInfo.name + " effect\n\n";
                        }
                        else if (enemyDotType == 2 && dotChance >= 75 + BTBonus)
                        {
                            dotInfo.name = "Blunt Trauma";
                            dotInfo.dotType = enemyDotType;
                            dotInfo.dotDamage = 1;

                            for (int i = 0; i < dotEffectiveness; i++)
                            {
                                dot_.push_back(dotInfo);
                            }

                            message_ += enemyName + " crushed you and caused a " + dotInfo.name + " effect\n\n";
                        }
                        else if (enemyDotType == 3 && dotChance >= 95)
                        {
                            dotInfo.name = "Poison";
                            dotInfo.dotType = enemyDotType;
                            dotInfo.dotDamage = 1;

                            for (int i = 0; i < dotEffectiveness; i++)
                            {
                                dot_.push_back(dotInfo);
                            }

                            message_ += enemyName + " slashed you with a poison laced blade and caused a " + dotInfo.name + " effect\n\n";
                        }
                    }
                }
            }
            else
                message_ = name_ + " blocks " + enemyName + "'s attack.\n\n";

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

int Player::getClassType()
{
    return classType_;
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
            QString lvlUpText = "<b>You achieved your first level up!</b><br>"
                                "---------------------------------------------------------------------<br><br>"
                                "Every time you level, you get 4 skill points to distribute between<br>"
                                "any of these 6 stats<br><br>"
                                "<b>Vitality</b><br>"
                                "Determines the amount of damage you can take from enemies<br>"
                                "Each point towards <b>Vitality</b> increases your HP by 2<br>";
            if (classType_ == 4)
            {
                lvlUpText+=     "As a <b>Knight</b>, every 5 points of <b>Vitality</b> gives you a 10% chance<br>"
                                "to absorb half the enemy's total attack damage<br>";
            }
            lvlUpText+=         "<br><b>Strength</b><br>"
                                "Determines how much damage you can do to enemies<br>"
                                "Each point towards <b>Strength</b> increases your maximum amount of damage by 1<br>"
                                "and every 5 points increases your minimum amount of damage by 1<br>";
            if (classType_ == 3)
            {
                lvlUpText+=     "As a <b>Warrior</b>, your minimum damage is increased every 3 points<br>"
                                "of <b>Strength</b> rather than every 5<br>";
            }
            lvlUpText+=         "<br><b>Stamina</b><br>"
                                "Determines how many actions you can take in  day<br>"
                                "Each point towards <b>Stamina</b> increases you maximum amount of stamina by 1<br><br>"
                                "<b>Agility</b><br>"
                                "Determines the chance at which you can dodge an enemy's attack<br>"
                                "Each 5 points towards <b>Agility</b> increases your chance at dodging<br>"
                                "an enemy's attack<br>";
            if (classType_ == 2)
            {
                lvlUpText+=     "As a <b>Rogue</b>, you gain this bonus every 3 points of <b>Agility</b><br>"
                                "rather than every 5.<br>";
            }
            if (classType_ == 4)
            {
                lvlUpText+=     "As a <b>Knight</b>, <b>Aglility</b> instead increases your <b>Block</b> chance<br>"
                                "This bonus only applies if you are wielding a shield<br>";
            }
            lvlUpText+=         "<br><b>Luck</b><br>"
                                "Determines the chance your attack can critically damage an enemy<br>"
                                "Each 5 points towards <b>Luck</b> increases your chance at critically<br>"
                                "damaging an enemy<br>"
                                "critical strikes cause 2x damage but can still be dodged<br>";
            if (classType_ == 2)
            {
                lvlUpText+=     "As a <b>Rogue</b>, your critical strike chance increases every 4<br>"
                                "points of <b>Luck</b> rather than every 5<br>";
            }
            lvlUpText+=         "<br><b>Precision</b><br>"
                                "Determines the chance at which you can successfully strike an enemy<br>"
                                "Each 5 points towards <b>Precision</b> increases your chance to successfully "
                                "strike an enemy<br>";
            if (classType_ == 3)
            {
                lvlUpText+=     "As a <b>Warrior</b>, every 3 points of <b>Precision</b> increases your<br>"
                                "strike chance rather than every 5<br>";
            }
            lvlUpText+=         "<br>Each skill can be raised to a maximum of 20, so spend your<br>"
                                "skill points wisely.";

            msgBox.setWindowTitle("Level Up");
            msgBox.setText(lvlUpText);
            msgBox.exec();

            QString addClaBon = "";

            if (classType_ == 2)
            {
                addClaBon = "<b>Additional Rogue Bonuses</b><br>"
                            "---------------------------------------------------------------------<br><br>"
                            "<b>Luck:</b><br>"
                            "Every 6 points of <b>Luck</b> gives you a 10% chance of striking your enemy<br>"
                            "an additional time. This strike deals half the damage of your first strike<br><br>"
                            "<b>Precision:</b><br>"
                            "Every 5 points of <b>Precision</b> increases your chance of poisoning<br>"
                            "a target with poison laced weapons by 5%";
            }
            else if (classType_ == 3)
            {
                addClaBon = "<b>Additional Warrior Bonuses</b><br>"
                            "---------------------------------------------------------------------<br><br>"
                            "<b>Strength:</b><br>"
                            "Every 6 points of <b>Strength</b> increases your damage ouput by 10%<br>"
                            "This bonus only applies if you are wielding a 2-Handed weapon<br><br>"
                            "Every 4 levels of <b>Strength</b> icreases your maximum damage<br>"
                            "by an additional 2 points";
            }
            else if (classType_ == 4)
            {
                addClaBon = "<b>Additional Knight Bonuses</b><br>"
                            "---------------------------------------------------------------------<br><br>"
                            "<b>Vitality:</b><br>"
                            "Every 4 points of <b>Vitality</b> increases your health by<br>"
                            "an additional 2 points<br><br>"
                            "<b>Blunt Trauma Resistence:</b><br>"
                            "Every 5 points of block reduces the chance that you will be affected<br>"
                            "by the <b>Blunt Trauma</b> DoT by 5%";
            }

            msgBox.setWindowTitle("Additional Class Bonuses");
            msgBox.setText(addClaBon);
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

void Player::usePotion(int healAmount, int itemIndex)
{
    if (health_ == maxHealth_)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Drink Potion");
        msgBox.setText("Your health is full.");
        msgBox.exec();
    }
    else
    {
        health_ += healAmount;
        removeItemFromInventory(itemIndex);
        //potion_ -= 1;
        if (health_ > maxHealth_)
            health_ = maxHealth_;
        QSound::play("Sounds\\drinkPotion.wav");
        QMessageBox msgBox;
        msgBox.setWindowTitle("Drink Potion");
        msgBox.setText("      Potion used.            ");
        msgBox.exec();
    }
}

void Player::useRation(int stamAmount, int itemIndex)
{
    if (stamina_ == maxStamina_)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Eat Ration");
        msgBox.setText("Your stamina is full.");
        msgBox.exec();
    }
    else
    {
        stamina_ += stamAmount;
        removeItemFromInventory(itemIndex);
        if (stamina_ > maxStamina_)
            stamina_ = maxStamina_;
        QSound::play("Sounds\\eatRation.wav");
        QMessageBox msgBox;
        msgBox.setWindowTitle("Eat Ration");
        msgBox.setText("      Ration Eaten.            ");
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
    saveFile << defaultHealth_ << "\n";
    saveFile << minAttackPower_ << "\n";
    saveFile << maxAttackPower_ << "\n";
    saveFile << minWeaponAP_ << "\n";
    saveFile << maxWeaponAP_ << "\n";
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
    saveFile << statVitality_ << "\n";
    saveFile << equippedVitality_ << "\n";
    saveFile << statStrength_ << "\n";
    saveFile << equippedStrength_ << "\n";
    saveFile << agility_ << "\n";
    saveFile << agilityDefault_ << "\n";
    saveFile << statAgility_ << "\n";
    saveFile << equippedAgility_ << "\n";
    saveFile << luck_ << "\n";
    saveFile << luckDefault_ << "\n";
    saveFile << statLuck_ << "\n";
    saveFile << equippedLuck_ << "\n";
    saveFile << intelligence_ << "\n";
    saveFile << intelligenceBonus_ << "\n";
    saveFile << questsCompleted_ << "\n";
    saveFile << precision_ << "\n";
    saveFile << statPrecision_ << "\n";
    saveFile << equippedPrecision_ << "\n";
    saveFile << stamina_ << "\n";
    saveFile << maxStamina_ << "\n";
    saveFile << defaultStamina_ << "\n";
    saveFile << statStamina_ << "\n";
    saveFile << equippedStamina_ << "\n";
    saveFile << ration_ << "\n";
    saveFile << location_ << "\n";
    saveFile << block_ << "\n";
    saveFile << classType_ << "\n";
    saveFile << mainHandSlot_ << "\n";
    saveFile << offHandSlot_ << "\n";
    saveFile << armourSlot_ << "\n";
    saveFile << ringSlotOne_ << "\n";
    saveFile << ringSlotTwo_ << "\n";
    saveFile << trinketSlotOne_ << "\n";
    saveFile << trinketSlotTwo_ << "\n";
    saveFile << isShieldEquipped_ << "\n";
    saveFile << armourType_ << "\n";
    saveFile << rogueDblAtkBonus_ << "\n";
    saveFile << warTwoHandAtkBonus_ << "\n";
    saveFile << knightAbsorbBonus_ << "\n";
    file.close();
    saveInventory();
    saveEquipment();
}

void Player::saveInventory()
{
    QString fileName = "saves\\" + name_ + "Inventory.save";
    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream saveFile(&file);

    for (int i = 0; i < inventory_.length(); i++)
    {
        saveFile << inventory_.value(i).name << ","
                 << inventory_.value(i).itemRarity << ","
                 << inventory_.value(i).itemType << ","
                 << inventory_.value(i).armourRating << ","
                 << inventory_.value(i).armourType << ","
                 << inventory_.value(i).healType << ","
                 << inventory_.value(i).healAmount << ","
                 << inventory_.value(i).isEquippable << ","
                 << inventory_.value(i).sellPrice << ","
                 << inventory_.value(i).isUsable << ","
                 << inventory_.value(i).minAtk << ","
                 << inventory_.value(i).maxAtk << ","
                 << inventory_.value(i).block << ","
                 << inventory_.value(i).holdType << ","
                 << inventory_.value(i).stat1 << ","
                 << inventory_.value(i).statType1 << ","
                 << inventory_.value(i).stat2 << ","
                 << inventory_.value(i).statType2 << ","
                 << inventory_.value(i).stat3 << ","
                 << inventory_.value(i).statType3 << ","
                 << inventory_.value(i).amount << ","
                 << inventory_.value(i).numStats << ","
                 << inventory_.value(i).weaponType << ","
                 << inventory_.value(i).weaponEdgeType << ","
                 << inventory_.value(i).dotType_ << "\n";
    }
    file.close();
}

void Player::saveEquipment()
{
    QString fileName = "saves\\" + name_ + "Equipment.save";
    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream saveFile(&file);

    for (int i = 0; i < equipment_.length(); i++)
    {
        saveFile << equipment_.value(i).name << ","
                 << equipment_.value(i).itemRarity << ","
                 << equipment_.value(i).itemType << ","
                 << equipment_.value(i).armourRating << ","
                 << equipment_.value(i).armourType << ","
                 << equipment_.value(i).healType << ","
                 << equipment_.value(i).healAmount << ","
                 << equipment_.value(i).isEquippable << ","
                 << equipment_.value(i).sellPrice << ","
                 << equipment_.value(i).isUsable << ","
                 << equipment_.value(i).minAtk << ","
                 << equipment_.value(i).maxAtk << ","
                 << equipment_.value(i).block << ","
                 << equipment_.value(i).holdType << ","
                 << equipment_.value(i).stat1 << ","
                 << equipment_.value(i).statType1 << ","
                 << equipment_.value(i).stat2 << ","
                 << equipment_.value(i).statType2 << ","
                 << equipment_.value(i).stat3 << ","
                 << equipment_.value(i).statType3 << ","
                 << equipment_.value(i).amount << ","
                 << equipment_.value(i).numStats << ","
                 << equipment_.value(i).weaponType << ","
                 << equipment_.value(i).weaponEdgeType << ","
                 << equipment_.value(i).dotType_ << "\n";
    }
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
        defaultHealth_ = saveFile.readLine().toUInt();
        minAttackPower_ = saveFile.readLine().toInt();
        maxAttackPower_ = saveFile.readLine().toInt();
        minWeaponAP_ = saveFile.readLine().toInt();
        maxWeaponAP_ = saveFile.readLine().toInt();
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
        statVitality_ = saveFile.readLine().toInt();
        equippedVitality_ = saveFile.readLine().toInt();
        statStrength_ = saveFile.readLine().toInt();
        equippedStrength_ = saveFile.readLine().toInt();
        agility_ = saveFile.readLine().toInt();
        agilityDefault_ = saveFile.readLine().toInt();
        statAgility_ = saveFile.readLine().toInt();
        equippedAgility_ = saveFile.readLine().toInt();
        luck_ = saveFile.readLine().toInt();
        luckDefault_ = saveFile.readLine().toInt();
        statLuck_ = saveFile.readLine().toInt();
        equippedLuck_ = saveFile.readLine().toInt();
        intelligence_ = saveFile.readLine().toInt();
        intelligenceBonus_ = saveFile.readLine().toInt();
        questsCompleted_ = saveFile.readLine().toInt();
        precision_ = saveFile.readLine().toInt();
        statPrecision_ = saveFile.readLine().toInt();
        equippedPrecision_ = saveFile.readLine().toInt();
        stamina_ = saveFile.readLine().toInt();
        maxStamina_ = saveFile.readLine().toInt();
        defaultStamina_ = saveFile.readLine().toInt();
        statStamina_ = saveFile.readLine().toInt();
        equippedStamina_ = saveFile.readLine().toInt();
        ration_ = saveFile.readLine().toInt();
        location_ = saveFile.readLine().toInt();
        block_ = saveFile.readLine().toInt();
        classType_ = saveFile.readLine().toInt();
        mainHandSlot_ = saveFile.readLine().toInt();
        offHandSlot_ = saveFile.readLine().toInt();
        armourSlot_ = saveFile.readLine().toInt();
        ringSlotOne_ = saveFile.readLine().toInt();
        ringSlotTwo_ = saveFile.readLine().toInt();
        trinketSlotOne_ = saveFile.readLine().toInt();
        trinketSlotTwo_ = saveFile.readLine().toInt();
        isShieldEquipped_ = saveFile.readLine().toInt();
        armourType_ = saveFile.readLine().toInt();
        rogueDblAtkBonus_ = saveFile.readLine().toInt();
        warTwoHandAtkBonus_ = saveFile.readLine().toInt();
        knightAbsorbBonus_ = saveFile.readLine().toInt();
        file.close();
    }
    loadInventory(playerName);
    loadEquipment(playerName);
    setMaxHealth();
    setStrength();
}

void Player::loadInventory(QString playerName)
{
    QString fileName = "saves\\" + playerName + "Inventory.save";
    QFile file(fileName);
    QStringList inventory;
    file.open(QIODevice::ReadOnly| QIODevice::Text);
    QTextStream saveFile(&file);
    inventory_.clear();
    if (file.exists() && file.isOpen())
    {
        while (!file.atEnd())
        {
            QByteArray line = file.readLine();
            inventory.append(line.split('\n').first());
        }
        file.close();
    }

    QStringList item;
    Item invItem;
    for (int i = 0; i < inventory.length(); i++)
    {
        item = inventory.value(i).split(',');
        invItem.name = item.value(0);
        invItem.itemRarity = item.value(1).toInt();
        invItem.itemType = item.value(2).toInt();
        invItem.armourRating = item.value(3).toInt();
        invItem.armourType = item.value(4).toInt();
        invItem.healType = item.value(5).toInt();
        invItem.healAmount = item.value(6).toInt();
        invItem.isEquippable = item.value(7).toInt();
        invItem.sellPrice = item.value(8).toInt();
        invItem.isUsable = item.value(9).toInt();
        invItem.minAtk = item.value(10).toInt();
        invItem.maxAtk = item.value(11).toInt();
        invItem.block = item.value(12).toInt();
        invItem.holdType = item.value(13).toInt();
        invItem.stat1 = item.value(14).toInt();
        invItem.statType1 = item.value(15).toInt();
        invItem.stat2 = item.value(16).toInt();
        invItem.statType2 = item.value(17).toInt();
        invItem.stat3 = item.value(18).toInt();
        invItem.statType3 = item.value(19).toInt();
        invItem.amount = item.value(20).toInt();
        invItem.numStats = item.value(21).toInt();
        invItem.weaponType = item.value(22).toInt();
        invItem.weaponType = item.value(23).toInt();
        invItem.dotType_ = item.value(24).toInt();
        addItemToInventory(invItem);

        if (invItem.name == "Bedroll")
        {
            addBedroll();
        }

        if (invItem.name == "Firestarter Kit")
        {
            addFireStarterKit();
        }
    }
}

void Player::loadEquipment(QString playerName)
{
    QString fileName = "saves\\" + playerName + "Equipment.save";
    QFile file(fileName);
    QStringList equipment;
    file.open(QIODevice::ReadOnly| QIODevice::Text);
    QTextStream saveFile(&file);
    equipment_.clear();
    if (file.exists() && file.isOpen())
    {
        while (!file.atEnd())
        {
            QByteArray line = file.readLine();
            equipment.append(line.split('\n').first());
        }
        file.close();
    }

    QStringList item;
    Item invItem;
    for (int i = 0; i < equipment.length(); i++)
    {
        item = equipment.value(i).split(',');
        invItem.name = item.value(0);
        invItem.itemRarity = item.value(1).toInt();
        invItem.itemType = item.value(2).toInt();
        invItem.armourRating = item.value(3).toInt();
        invItem.armourType = item.value(4).toInt();
        invItem.healType = item.value(5).toInt();
        invItem.healAmount = item.value(6).toInt();
        invItem.isEquippable = item.value(7).toInt();
        invItem.sellPrice = item.value(8).toInt();
        invItem.isUsable = item.value(9).toInt();
        invItem.minAtk = item.value(10).toInt();
        invItem.maxAtk = item.value(11).toInt();
        invItem.block = item.value(12).toInt();
        invItem.holdType = item.value(13).toInt();
        invItem.stat1 = item.value(14).toInt();
        invItem.statType1 = item.value(15).toInt();
        invItem.stat2 = item.value(16).toInt();
        invItem.statType2 = item.value(17).toInt();
        invItem.stat3 = item.value(18).toInt();
        invItem.statType3 = item.value(19).toInt();
        invItem.amount = item.value(20).toInt();
        invItem.numStats = item.value(21).toInt();
        invItem.weaponType = item.value(22).toInt();
        invItem.weaponType = item.value(23).toInt();
        invItem.dotType_ = item.value(24).toInt();
        equipment_.push_back(invItem);
    }
}

void Player::addStatVitality(int vitality)
{
    statVitality_ += vitality;
    setMaxHealth();
}

void Player::addEquippedVitality(int vitality)
{
    equippedVitality_ += vitality;
    setMaxHealth();
}

void Player::removeVitality(int vitality)
{
    equippedVitality_ -= vitality;
    setMaxHealth();
}

void Player::setMaxHealth()
{
    int knightHPBonus = 0;
    int statHealth = statVitality_ * 2;
    int equippedHealth = equippedVitality_ * 2;
    maxHealth_ = defaultHealth_ + statHealth + equippedHealth;
    vitality_ = statVitality_ + equippedVitality_;

    if (classType_ == 4)
    {
        knightAbsorbBonus_ = vitality_ / 5;
        knightHPBonus = vitality_ / 4;
        maxHealth_ += knightHPBonus * 2;
    }
}

int Player::getVitality()
{
    return vitality_;
}

int Player::getStatVitality()
{
    return statVitality_;
}

void Player::addStatStrength(int strength)
{
    statStrength_ += strength;
    setStrength();
}

void Player::addEquippedStrength(int strength)
{
    equippedStrength_ += strength;
    setStrength();
}

void Player::removeStrength(int strength)
{
    equippedStrength_ -= strength;
    setStrength();
}

void Player::setStrength()
{
    strength_ = statStrength_ + equippedStrength_;

    if (classType_ == 3)
        warTwoHandAtkBonus_ = strength_ / 6;

    calculateMinAttackPower();
    calculateMaxAttackPower();
}

int Player::getStrength()
{
    return strength_;
}

int Player::getStatStrength()
{
    return statStrength_;
}

void Player::addStatAgility(int agility)
{
    statAgility_ += agility;
    setAgility();
}

void Player::addEquippedAgility(int agility)
{
    equippedAgility_ += agility;
    setAgility();
}

void Player::removeAgility(int agility)
{
    equippedAgility_ -= agility;
    setAgility();
}

void Player::setAgility()
{
    int totalAgilityPoints = statAgility_ + equippedAgility_;
    int agilityBonus = 0;

    if (classType_ == 2)
        agilityBonus = totalAgilityPoints / 3;
    else if (classType_ == 4)
        knightBlockBonus_ = totalAgilityPoints / 5;
    else
        agilityBonus = totalAgilityPoints / 5;

    agility_ = agilityDefault_ + agilityBonus;
}

int Player::getAgility()
{
    return agility_;
}

int Player::getStatAgility()
{
    return statAgility_;
}

void Player::addStatLuck(int luck)
{
    statLuck_ += luck;
    setLuck();
}

void Player::addEquippedLuck(int luck)
{
    equippedLuck_ += luck;
    setLuck();
}

void Player::removeLuck(int luck)
{
    equippedLuck_ -= luck;
    setLuck();
}

void Player::setLuck()
{
    int totalLuckPoints = statLuck_ + equippedLuck_;
    int luckBonus;

    if (classType_ == 2)
    {
        luckBonus = totalLuckPoints / 4;
        rogueDblAtkBonus_ = totalLuckPoints / 6;
    }
    else
        luckBonus = totalLuckPoints / 5;

    luck_ = luckDefault_ - luckBonus;
}

double Player::getCritChance()
{
    return (double)((luckDefault_ - luck_) + 1)/(double)luckDefault_;
}

int Player::getLuck()
{
    return luck_;
}

int Player::getStatLuck()
{
    return statLuck_;
}

void Player::addIntelligence(int intelligence)
{
    intelligence_ += intelligence;

    if (intelligence_ % 5 == 0)
    {
        intelligenceBonus_ += 1;
    }
}

int Player::getIntelligence()
{
    return intelligence_;
}

void Player::addStatPrecision(int precision)
{
    statPrecision_ += precision;
    setPrecision();
}

void Player::addEquippedPrecision(int precision)
{
    equippedPrecision_ += precision;
    setPrecision();
}

void Player::removePrecision(int precision)
{
    equippedPrecision_ -= precision;
    setPrecision();
}

void Player::setPrecision()
{
    int totalPrecisionPoints = statPrecision_ + equippedPrecision_;

    if (classType_ == 3)
        precision_ = totalPrecisionPoints / 3;
    else
        precision_ = totalPrecisionPoints / 5;

}

int Player::getPrecision()
{
    return precision_;
}

int Player::getStatPrecision()
{
    return statPrecision_;
}

void Player::setStamina(int stamina)
{
    stamina_ = stamina;
}

void Player::setMaxStamina()
{
    maxStamina_ = defaultStamina_ + statStamina_ + equippedStamina_;
}

void Player::addStamina(int stamina)
{
    stamina_ += stamina;

    if (stamina_ > maxStamina_)
        stamina_ = maxStamina_;
}

void Player::removeStatStamina(int stamina)
{
    equippedStamina_ -= stamina;
    setMaxStamina();
}

void Player::addStatStamina(int stamina)
{
    statStamina_ += stamina;
    setMaxStamina();
}

void Player::addEquippedStamina(int stamina)
{
    equippedStamina_ += stamina;
    setMaxStamina();
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

int Player::getStatStamina()
{
    return statStamina_;
}

int Player::getTotalAgilityPoints()
{
    return statAgility_ + equippedAgility_;
}

int Player::getTotalVitalityPoints()
{
    return statVitality_ + equippedVitality_;
}

int Player::getTotalStrengthPoints()
{
    return statStrength_ + equippedStrength_;
}

int Player::getTotalPrecisionPoints()
{
    return statPrecision_ + equippedPrecision_;
}

int Player::getTotalLuckPoints()
{
    return statLuck_ + equippedLuck_;
}

int Player::getTotalStaminaPoints()
{
    return statStamina_ + equippedStamina_;
}

int Player::getBlock()
{
    return block_;
}

void Player::addBlock(int block)
{
    block_ += block;
}

void Player::removeBlock(int block)
{
    block_ -= block;
}

void Player::equipArmour(int armourRating)
{
    agilityDefault_ += armourRating;
    setAgility();
}

void Player::unequipArmour(int armourRating)
{
    agilityDefault_ -= armourRating;
    setAgility();
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

int Player::getMaxHealth()
{
    return maxHealth_;
}

void Player::setMaxHealth(int maxHealth)
{
    maxHealth_ += maxHealth;
}

void Player::calculateMaxAttackPower()
{
    int warrMaxBonus = 0;
    if (classType_ == 3)
    {
        warrMaxBonus = strength_ / 4;
        warrMaxBonus *= 2;
        maxAttackPower_ = maxWeaponAP_ + strength_ + warrMaxBonus;
    }
    else
        maxAttackPower_ = maxWeaponAP_ + strength_;

}

void Player::calculateMinAttackPower()
{
    int minBonus;

    if (classType_ == 3)
        minBonus = strength_ / 3;
    else
        minBonus = strength_ / 5;

    minAttackPower_ = minWeaponAP_ + minBonus;
}

int Player::getMaxAttackPower()
{
    return maxAttackPower_;
}

int Player::getMinAttackPower()
{
    return minAttackPower_;
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

void Player::removeRation(int itemIndex)
{
    inventory_.remove(itemIndex);
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
        inventory_.push_back(items.value(i));
    }
}

void Player::addItemToInventory(Item item)
{
    inventory_.push_back(item);
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
    itemEquipped_ = false;

    if (item.itemType == 2)
    {
        if (item.holdType == 1)
        {
            if (classType_ == 2 && (item.weaponType >= 3 && item.weaponType <= 7))
            {
                message_ = classXRef_->getClassType(classType_) + "s can only equip Daggers and Short Swords";
                displayMessage("Equipping Restriction", message_);
            }
            else if (classType_ == 1 && (item.weaponType >= 2 && item.weaponType <= 5))
            {
                message_ = classXRef_->getClassType(classType_) + "s can only equip Daggers, Staffs and Scepters";
                displayMessage("Equipping Restriction", message_);
            }
            else
            {
                if (mainHandSlot_ != 0)
                {
                    message_ = "You already have a weapon equipped\n in your main hand slot";
                    displayMessage("Equipping", message_);
                }
                else if (mainHandSlot_ == 0)
                {
                    itemEquipped_ = true;
                    mainHandSlot_ = 1;
                    minWeaponAP_ = item.minAtk;
                    maxWeaponAP_ = item.maxAtk;
                    equipment_.push_back(item);
                }
            }
        }

        if (item.holdType == 2)
        {
            if (classType_ == 2 && (item.weaponType >= 3 && item.weaponType <= 7))
            {
                message_ = classXRef_->getClassType(classType_) + "s can only equip Daggers and Short Swords";
                displayMessage("Equipping Restriction", message_);
            }
            else if (classType_ == 1 && (item.weaponType >= 2 && item.weaponType <= 5))
            {
                message_ = classXRef_->getClassType(classType_) + "s can only equip Daggers, Staffs and Scepters";
                displayMessage("Equipping Restriction", message_);
            }
            else
            {
                if (mainHandSlot_ == 0)
                {
                    itemEquipped_ = true;
                    mainHandSlot_ = 2;
                    minWeaponAP_ = item.minAtk;
                    maxWeaponAP_ = item.maxAtk;
                    equipment_.push_back(item);
                }
                else if (mainHandSlot_ != 0 && offHandSlot_ == 0)
                {
                    itemEquipped_ = true;
                    offHandSlot_ = 1;
                    minWeaponAP_ += item.minAtk;
                    maxWeaponAP_ += item.maxAtk;
                    equipment_.push_back(item);
                }
                else if (mainHandSlot_ != 0 and offHandSlot_ != 0)
                {
                    message_ = "Both hand slots are filled";
                    displayMessage("Equipping", message_);
                }
            }
        }

        if (item.holdType == 3)
        {
            if (classType_ == 2)
            {
                message_ = classXRef_->getClassType(classType_) + "s cannot equip 2 handed weapons";
                displayMessage("Equipping Restriction", message_);
            }
            else if (classType_ == 1 && item.weaponType != 6)
            {
                message_ = classXRef_->getClassType(classType_) + "s can only equip Staffs";
                displayMessage("Equipping Restriction", message_);
            }
            else
            {
                if (mainHandSlot_ == 0 && offHandSlot_ == 0)
                {
                    itemEquipped_ = true;
                    mainHandSlot_ = 3;
                    offHandSlot_ = 3;
                    minWeaponAP_ = item.minAtk;
                    maxWeaponAP_ = item.maxAtk;
                    equipment_.push_back(item);
                }
                else
                {
                    message_ = "You need both hands for this weapon";
                    displayMessage("Equipping", message_);
                }
            }
        }

        if (itemEquipped_)
        {
            calculateMinAttackPower();
            calculateMaxAttackPower();
        }
    }

    if (item.itemType == 4)
    {
        if (classType_ == 1 || classType_ == 2)
        {
            message_ = classXRef_->getClassType(classType_) + "s cannot equip shields";
            displayMessage("Equipping Restriction", message_);
        }
        else
        {
            if (offHandSlot_ == 0)
            {
                itemEquipped_ = true;
                offHandSlot_ = 2;
                addBlock(item.block);
                equipment_.push_back(item);
            }
            else
            {
                message_ = "Your off hand slot is filled";
                displayMessage("Equipping", message_);
            }
        }
    }

    if (item.itemType == 3)
    {
        if (classType_ == 1 && item.armourType != 1)
        {
            message_ = classXRef_->getClassType(classType_) + "s can only wear Cloth armour";
            displayMessage("Equipping Restriction", message_);
        }
        else if (classType_ == 2 && item.armourType != 2)
        {
            message_ = classXRef_->getClassType(classType_) + "s can only wear Leather armour";
            displayMessage("Equipping Restriction", message_);
        }
        else if (classType_ == 3 && item.armourType != 3)
        {
            message_ = classXRef_->getClassType(classType_) + "s can only wear Mail armour";
            displayMessage("Equipping Restriction", message_);
        }
        else if (classType_ == 4 && item.armourType != 4)
        {
            message_ = classXRef_->getClassType(classType_) + "s can only wear Plate armour";
            displayMessage("Equipping Restriction", message_);
        }
        else
        {
            if (armourSlot_ == 0)
            {
                itemEquipped_ = true;
                armourSlot_ = 1;
                armourType_ = item.armourType;
                equipment_.push_back(item);
                equipArmour(item.armourRating);
            }
            else
            {
                message_ = "Your armour slot is filled";
                displayMessage("Equipping", message_);
            }
        }
    }

    if (item.itemType == 6)
    {
        if (ringSlotOne_ == 0 && ringSlotTwo_ == 0)
        {
            itemEquipped_ = true;
            ringSlotOne_ = 1;
            equipment_.push_back(item);
        }
        else if (ringSlotOne_ == 1 && ringSlotTwo_ == 0)
        {
            itemEquipped_ = true;
            ringSlotTwo_ = 1;
            equipment_.push_back(item);
        }
        else
        {
            message_ = "Both ring slots are filled";
            displayMessage("Equipping", message_);
        }
    }

    if (item.itemType == 7)
    {
        if (trinketSlotOne_ == 0 && trinketSlotTwo_ == 0)
        {
            itemEquipped_ = true;
            trinketSlotOne_ = 1;
            equipment_.push_back(item);
        }
        else if (trinketSlotOne_ == 1 && trinketSlotTwo_ == 0)
        {
            itemEquipped_ = true;
            trinketSlotTwo_ = 1;
            equipment_.push_back(item);
        }
        else
        {
            message_ = "Both trinket slots are filled";
            displayMessage("Equipping", message_);
        }
    }

    if (itemEquipped_)
    {
        switch (item.statType1)
        {
            case 1: //Vitality
                addEquippedVitality(item.stat1);
                break;
            case 2: //Strength
                addEquippedStrength(item.stat1);
                break;
            case 3: //Stamina
                addEquippedStamina(item.stat1);
                break;
            case 4: //Agility
                addEquippedAgility(item.stat1);
                break;
            case 5: //Luck
                addEquippedLuck(item.stat1);
                break;
            case 6: //Precision
                addEquippedPrecision(item.stat1);
                break;
            case 7: //Block
                addBlock(item.stat1);
                break;
        }

        switch (item.statType2)
        {
            case 1: //Vitality
                addEquippedVitality(item.stat2);
                break;
            case 2: //Strength
                addEquippedStrength(item.stat2);
                break;
            case 3: //Stamina
                addEquippedStamina(item.stat2);
                break;
            case 4: //Agility
                addEquippedAgility(item.stat2);
                break;
            case 5: //Luck
                addEquippedLuck(item.stat2);
                break;
            case 6: //Precision
                addEquippedPrecision(item.stat2);
                break;
            case 7: //Block
                addBlock(item.stat2);
                break;
        }

        switch (item.statType3)
        {
            case 1: //Vitality
                addEquippedVitality(item.stat3);
                break;
            case 2: //Strength
                addEquippedStrength(item.stat3);
                break;
            case 3: //Stamina
                addEquippedStamina(item.stat3);
                break;
            case 4: //Agility
                addEquippedAgility(item.stat3);
                break;
            case 5: //Luck
                addEquippedLuck(item.stat3);
                break;
            case 6: //Precision
                addEquippedPrecision(item.stat3);
                break;
            case 7: //Block
                addBlock(item.stat3);
                break;
        }
    }
}

void Player::removeEquipment(int index)
{
    Item item = equipment_.value(index);
    equipment_.remove(index);

    if (item.itemType == 2)
    {
        minWeaponAP_ -= item.minAtk;
        maxWeaponAP_ -= item.maxAtk;
        calculateMinAttackPower();
        calculateMaxAttackPower();

        if (item.holdType == 3)
        {
            mainHandSlot_ = 0;
            offHandSlot_ = 0;
        }
        else if (item.holdType == 1)
        {
            mainHandSlot_ = 0;
        }
        else if (item.holdType == 2)
        {
            if (mainHandSlot_ == 1 && offHandSlot_ == 1)
            {
                offHandSlot_ = 0;
            }
            else if (mainHandSlot_ == 2 && offHandSlot_ == 1)
            {
                offHandSlot_ = 0;
            }
            else if (mainHandSlot_ == 2 && offHandSlot_ == 2)
            {
                mainHandSlot_ = 0;
            }
            else if (mainHandSlot_ == 2 && offHandSlot_ == 0)
            {
                mainHandSlot_ = 0;
            }
        }
    }

    if (item.itemType == 4)
    {
        offHandSlot_ = 0;
        removeBlock(item.block);
    }

    if (item.itemType == 3)
    {
        armourSlot_ = 0;
        armourType_ = 0;
        unequipArmour(item.armourRating);
    }

    if (item.itemType == 6)
    {
        if (ringSlotOne_ == 1 && ringSlotTwo_ == 1)
        {
            ringSlotTwo_ = 0;
        }
        else if (ringSlotOne_ == 1 && ringSlotTwo_ == 0)
        {
            ringSlotOne_ = 0;
        }
    }

    if (item.itemType == 7)
    {
        if (trinketSlotOne_ == 1 && trinketSlotTwo_ == 1)
        {
            trinketSlotTwo_ = 0;
        }
        else if (trinketSlotOne_ == 1 && trinketSlotTwo_ == 0)
        {
            trinketSlotOne_ = 0;
        }
    }

    switch (item.statType1)
    {
        case 1: //Vitality
            removeVitality(item.stat1);
            break;
        case 2: //Strength
            removeStrength(item.stat1);
            break;
        case 3: //Stamina
            removeStatStamina(item.stat1);
            break;
        case 4: //Agility
            removeAgility(item.stat1);
            break;
        case 5: //Luck
            removeLuck(item.stat1);
            break;
        case 6: //Precision
            removePrecision(item.stat1);
            break;
        case 7: //Block
            removeBlock(item.stat1);
            break;
    }

    switch (item.statType2)
    {
        case 1: //Vitality
            removeVitality(item.stat2);
            break;
        case 2: //Strength
            removeStrength(item.stat2);
            break;
        case 3: //Stamina
            removeStatStamina(item.stat2);
            break;
        case 4: //Agility
            removeAgility(item.stat2);
            break;
        case 5: //Luck
            removeLuck(item.stat2);
            break;
        case 6: //Precision
            removePrecision(item.stat2);
            break;
        case 7: //Block
            removeBlock(item.stat2);
            break;
    }

    switch (item.statType3)
    {
        case 1: //Vitality
            removeVitality(item.stat3);
            break;
        case 2: //Strength
            removeStrength(item.stat3);
            break;
        case 3: //Stamina
            removeStatStamina(item.stat3);
            break;
        case 4: //Agility
            removeAgility(item.stat3);
            break;
        case 5: //Luck
            removeLuck(item.stat3);
            break;
        case 6: //Precision
            removePrecision(item.stat3);
            break;
        case 7: //Block
            removeBlock(item.stat3);
            break;
    }
}

void Player::addStarterEquipment()
{
    Item starterWeapon;
    Item starterArmour;

    if (classType_ == 1)
    {
        //todo
    }
    else if (classType_ == 2)
    {
        starterWeapon.name="Weak Dagger";
        starterWeapon.itemRarity=1;
        starterWeapon.itemType=2;
        starterWeapon.armourRating=0;
        starterWeapon.armourType=0;
        starterWeapon.healType=0;
        starterWeapon.healAmount=0;
        starterWeapon.isEquippable=true;
        starterWeapon.sellPrice=10;
        starterWeapon.isUsable=false;
        starterWeapon.minAtk=1;
        starterWeapon.maxAtk=3;
        starterWeapon.block=0;
        starterWeapon.holdType=2;
        starterWeapon.stat1=0;
        starterWeapon.stat2=0;
        starterWeapon.stat3=0;
        starterWeapon.statType1=0;
        starterWeapon.statType2=0;
        starterWeapon.statType3=0;
        starterWeapon.amount=1;
        starterWeapon.numStats=0;
        starterWeapon.weaponType = 1;
        starterWeapon.weaponEdgeType = 1;
        starterWeapon.dotType_ = 1;
        addEquipment(starterWeapon);
        addEquipment(starterWeapon);

        starterArmour.name="Ruined Leather";
        starterArmour.itemRarity=1;
        starterArmour.itemType=3;
        starterArmour.armourRating=2;
        starterArmour.armourType=2;
        starterArmour.healType=0;
        starterArmour.healAmount=0;
        starterArmour.isEquippable=true;
        starterArmour.sellPrice=20;
        starterArmour.isUsable=false;
        starterArmour.minAtk=0;
        starterArmour.maxAtk=0;
        starterArmour.block=0;
        starterArmour.holdType=0;
        starterArmour.stat1=0;
        starterArmour.stat2=0;
        starterArmour.stat3=0;
        starterArmour.statType1=0;
        starterArmour.statType2=0;
        starterArmour.statType3=0;
        starterArmour.amount=1;
        starterArmour.numStats=0;
        addEquipment(starterArmour);
    }
    else if (classType_ == 3)
    {
        starterWeapon.name="Weak Long Sword";
        starterWeapon.itemRarity=1;
        starterWeapon.itemType=2;
        starterWeapon.armourRating=0;
        starterWeapon.armourType=0;
        starterWeapon.healType=0;
        starterWeapon.healAmount=0;
        starterWeapon.isEquippable=true;
        starterWeapon.sellPrice=20;
        starterWeapon.isUsable=false;
        starterWeapon.minAtk=1;
        starterWeapon.maxAtk=7;
        starterWeapon.block=0;
        starterWeapon.holdType=3;
        starterWeapon.stat1=0;
        starterWeapon.stat2=0;
        starterWeapon.stat3=0;
        starterWeapon.statType1=0;
        starterWeapon.statType2=0;
        starterWeapon.statType3=0;
        starterWeapon.amount=1;
        starterWeapon.numStats=0;
        starterWeapon.weaponType = 3;
        starterWeapon.weaponEdgeType = 1;
        starterWeapon.dotType_ = 1;
        addEquipment(starterWeapon);

        starterArmour.name="Ruined Mail";
        starterArmour.itemRarity=1;
        starterArmour.itemType=3;
        starterArmour.armourRating=1;
        starterArmour.armourType=3;
        starterArmour.healType=0;
        starterArmour.healAmount=0;
        starterArmour.isEquippable=true;
        starterArmour.sellPrice=25;
        starterArmour.isUsable=false;
        starterArmour.minAtk=0;
        starterArmour.maxAtk=0;
        starterArmour.block=0;
        starterArmour.holdType=0;
        starterArmour.stat1=0;
        starterArmour.stat2=0;
        starterArmour.stat3=0;
        starterArmour.statType1=0;
        starterArmour.statType2=0;
        starterArmour.statType3=0;
        starterArmour.amount=1;
        starterArmour.numStats=0;
        addEquipment(starterArmour);
    }
    else if (classType_ == 4)
    {
        starterWeapon.name="Weak Short Sword";
        starterWeapon.itemRarity=1;
        starterWeapon.itemType=2;
        starterWeapon.armourRating=0;
        starterWeapon.armourType=0;
        starterWeapon.healType=0;
        starterWeapon.healAmount=0;
        starterWeapon.isEquippable=true;
        starterWeapon.sellPrice=15;
        starterWeapon.isUsable=false;
        starterWeapon.minAtk=1;
        starterWeapon.maxAtk=5;
        starterWeapon.block=0;
        starterWeapon.holdType=1;
        starterWeapon.stat1=0;
        starterWeapon.stat2=0;
        starterWeapon.stat3=0;
        starterWeapon.statType1=0;
        starterWeapon.statType2=0;
        starterWeapon.statType3=0;
        starterWeapon.amount=1;
        starterWeapon.numStats=0;
        starterWeapon.weaponType = 2;
        starterWeapon.weaponEdgeType = 1;
        starterWeapon.dotType_ = 1;
        addEquipment(starterWeapon);

        starterWeapon.name="Weak Wooden Shield";
        starterWeapon.itemRarity=1;
        starterWeapon.itemType=4;
        starterWeapon.armourRating=0;
        starterWeapon.armourType=0;
        starterWeapon.healType=0;
        starterWeapon.healAmount=0;
        starterWeapon.isEquippable=true;
        starterWeapon.sellPrice=15;
        starterWeapon.isUsable=false;
        starterWeapon.minAtk=0;
        starterWeapon.maxAtk=0;
        starterWeapon.block=7;
        starterWeapon.holdType=0;
        starterWeapon.stat1=0;
        starterWeapon.stat2=0;
        starterWeapon.stat3=0;
        starterWeapon.statType1=0;
        starterWeapon.statType2=0;
        starterWeapon.statType3=0;
        starterWeapon.amount=1;
        starterWeapon.numStats=0;
        addEquipment(starterWeapon);

        starterArmour.name="Ruined Plate";
        starterArmour.itemRarity=1;
        starterArmour.itemType=3;
        starterArmour.armourRating=0;
        starterArmour.armourType=4;
        starterArmour.healType=0;
        starterArmour.healAmount=0;
        starterArmour.isEquippable=true;
        starterArmour.sellPrice=30;
        starterArmour.isUsable=false;
        starterArmour.minAtk=0;
        starterArmour.maxAtk=0;
        starterArmour.block=0;
        starterArmour.holdType=0;
        starterArmour.stat1=0;
        starterArmour.stat2=0;
        starterArmour.stat3=0;
        starterArmour.statType1=0;
        starterArmour.statType2=0;
        starterArmour.statType3=0;
        starterArmour.amount=1;
        starterArmour.numStats=0;
        addEquipment(starterArmour);
    }
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

void Player::equippedShield()
{
    isShieldEquipped_ = true;
}

void Player::unequippedShield()
{
    isShieldEquipped_ = false;
}

bool Player::itemEquipped()
{
    return itemEquipped_;
}

void Player::displayMessage(QString title, QString message)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(title);
    msgBox.setText(message);
    msgBox.exec();
}

bool Player::hasBedroll()
{
    return hasBedroll_;
}

void Player::addBedroll()
{
    hasBedroll_ = true;
}

void Player::removeBedroll()
{
    hasBedroll_ = false;
}

bool Player::hasFireStarterKit()
{
    return hasFireStarterKit_;
}

void Player::addFireStarterKit()
{
    fireStarterKitAmount_ += 1;

    if (!hasFireStarterKit_)
        hasFireStarterKit_ = true;
}

void Player::removeFireStarterKit()
{
    for (int a = 0; a < inventory_.length(); a++)
    {
        if (inventory_.value(a).name == "Firestarter Kit")
        {
            removeItemFromInventory(a);
            break;
        }
    }
    fireStarterKitAmount_ -= 1;

    if (fireStarterKitAmount_ < 1)
        hasFireStarterKit_ = false;
}

bool Player::hasActiveDoT()
{
    bool hasDot = false;

    if (dot_.length() >= 1)
        hasDot = true;

    return hasDot;
}

void Player::doDotEffect()
{
    health_ -= dot_.value(0).dotDamage;
    dot_.remove(0);

    message_ = QString("%3 takes %1 damage from the %2 effect\n\n").arg(dot_.value(0).dotDamage).arg(dot_.value(0).name).arg(name_);
}

int Player::getWeaponDotType()
{
    QVector<Item> weapons;
    int weaponDot;

    for (int i = 0; i < equipment_.length(); i++)
    {
        if (equipment_.value(i).itemType == 2)
        {
            weapons.push_back(equipment_.value(i));
        }
    }

    if (weapons.length() > 1)
    {
        int weapIndex = rand() % weapons.length() + 1;

        weaponDot = weapons.value(weapIndex).dotType_;
    }
    else
    {
        weaponDot = weapons.value(0).dotType_;
    }

    return weaponDot;
}

int Player::getWeapon()
{
    int weapon = 0;

    for (int i = 0; i < equipment_.length(); i++)
    {
        if (equipment_.value(i).itemType == 2)
        {
            weapon = equipment_.value(i).holdType;
        }
    }

    return weapon;
}

int Player::getRogueDblAtkBonus()
{
    return rogueDblAtkBonus_;
}

int Player::getShieldBlockBonus()
{
    int blockBonus = 0;

    if (classType_ == 4 && isShieldEquipped_)
        blockBonus = knightAbsorbBonus_;

    return blockBonus;
}

bool Player::didRoguePassSecondAttackCheck()
{
    bool passedCheck = false;
    int secondAttackChanceBonus = rogueDblAtkBonus_ * 10;
    int secondAttackChance = rand() % ((100 + 1) - 1) + 1;

    if (secondAttackChance >= (100 - secondAttackChanceBonus))
        passedCheck = true;

    return passedCheck;
}

bool Player::didKnightAbsorb(int enemyHitRoll)
{
    bool didAbsorb = false;
    int absorbChanceBonus = knightAbsorbBonus_ * 10;

    if (enemyHitRoll <= absorbChanceBonus)
        didAbsorb = true;

    return didAbsorb;
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

int Player::getQuestsCompleted()
{
    return questsCompleted_;
}

void Player::completeQuest()
{
    questsCompleted_ += 1;
}
