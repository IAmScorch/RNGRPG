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

QVector<Item> Bandit::doLootDrop(QString enemyName, int enemyType, int itemDropChance)
{
    int dropChance;
    int oddsRoll;
    QString itemChance;
    int itemsToDropped;
    QString lootMessage;
    QMessageBox msgBox;
    QVector<Item> droppedItems_;

    dropChance = rand()% 100 + 1;
    lootMessage = enemyName + " dropped no loot";
    oddsRoll = 0;
    itemChance = "";

    if (dropChance <= itemDropChance)
    {
        lootMessage = enemyName + " dropped:\n";
        itemsToDropped = rand()% 3 + 1;

        for (int i = 0; i < itemsToDropped; i++)
        {
            if (enemyType == 1 || enemyType == 2 || enemyType == 3 || enemyType == 4 || enemyType == 5)
            {
                int cols = sizeof(*banditItemDropsChance_)/(sizeof (int *));
                int rows =  sizeof banditItemDrops_ / sizeof banditItemDrops_[0];
                //int itemCols = sizeof(*banditItemDrops_)/(sizeof (int *));

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

                for (int b = 0; b < odds.length(); b++)
                {
                    std::random_shuffle (odds.begin(), odds.end());
                }

                oddsRoll = rand()% odds.length();
                itemChance = odds.value(oddsRoll);

                for (int c = 0; c < cols; c++)
                {
                    if (itemChance == banditItemDropsChance_[0][c])
                    {
                        //QVector<QString> numItems;
                        QVector<Item> tempItems;
                        for (int e = 0; e < rows; e++)
                        {
                            if (itemChance == banditItemDrops_[e][15])
                            {
                                Item item;
                                //numItems.push_back(banditItemDrops_[e][0]);

                                item.name = banditItemDrops_[e][0];
                                item.itemRarity = banditItemDrops_[e][1].toInt();
                                item.itemType = banditItemDrops_[e][2].toInt();
                                item.armourRating = banditItemDrops_[e][3].toInt();
                                item.armourType = banditItemDrops_[e][4].toInt();
                                item.healType = banditItemDrops_[e][5].toInt();
                                item.healAmount = banditItemDrops_[e][6].toInt();
                                item.isEquippable = banditItemDrops_[e][7].toInt();
                                item.sellPrice = banditItemDrops_[e][8].toInt();
                                item.isUsable = banditItemDrops_[e][9].toInt();
                                item.weight = banditItemDrops_[e][10].toInt();
                                item.minAtk = banditItemDrops_[e][11].toInt();
                                item.maxAtk = banditItemDrops_[e][12].toInt();
                                item.block = banditItemDrops_[e][13].toInt();
                                item.holdType = banditItemDrops_[e][14].toInt();
                                item.stat1 = 0;
                                item.stat2 = 0;
                                item.stat3 = 0;
                                item.statType1 = 0;
                                item.statType2 = 0;
                                item.statType3 = 0;
                                item.amount = 1;
                                item.numStats = 0;

                                if (item.itemRarity > 1)
                                {
                                    int itemStatTypes[7] = {1,2,3,4,5,6,7};
                                    int itemStatType1 = 0;
                                    int itemStatType2 = 0;
                                    int itemStatType3 = 0;
                                    int numStats = 0;

                                    if (item.itemType == 4)
                                    {
                                        itemStatType1 = rand()% 7 + 1;
                                        itemStatType2 = rand()% 7 + 1;
                                        itemStatType3 = rand()% 7 + 1;
                                    }
                                    else
                                    {
                                        itemStatType1 = itemStatTypes[rand()% 7];
                                        itemStatType2 = itemStatTypes[rand()% 7];
                                        itemStatType3 = itemStatTypes[rand()% 7];
                                    }

                                    if (item.itemType != 8)
                                    {
                                        switch (item.itemRarity)
                                        {
                                            case 2: //uncommon
                                                item.statType1 = itemStatType1;
                                                item.stat1 = 1;
                                                item.numStats = 1;
                                                numStats = 1;
                                                break;
                                            case 3: //rare
                                                item.statType1 = itemStatType1;
                                                item.statType2 = itemStatType2;
                                                item.stat1 = 1;
                                                item.stat2 = 1;
                                                item.numStats = 2;
                                                numStats = 2;
                                                break;
                                            case 4: //epic
                                                item.statType1 = itemStatType1;
                                                item.statType2 = itemStatType2;
                                                item.statType3 = itemStatType3;
                                                item.stat1 = 1;
                                                item.stat2 = 1;
                                                item.stat3 = 1;
                                                item.numStats = 3;
                                                numStats = 3;
                                                break;
                                            case 5: //legendary
                                                item.statType1 = itemStatType1;
                                                item.statType2 = itemStatType2;
                                                item.statType3 = itemStatType3;
                                                item.stat1 = rand()% 2 + 1;
                                                item.stat2 = rand()% 2 + 1;
                                                item.stat3 = rand()% 2 + 1;
                                                item.numStats = 3;
                                                numStats = 3;
                                                break;
                                        }
                                    }
                                    else if (item.itemType == 8)
                                    {
                                        int itemTypes[5] = {2,3,4,6,7};
                                        int itemType = rand()% 5;
                                        QString statName1 = "";
                                        QString statName2 = "";
                                        QString statName3 = "";
                                        item.itemType = itemTypes[itemType];

                                        if (item.itemType == 4)
                                        {
                                            itemStatType1 = rand()% 8 + 1;
                                            itemStatType2 = rand()% 8 + 1;
                                            itemStatType3 = rand()% 8 + 1;
                                        }
                                        else
                                        {
                                            itemStatType1 = itemStatTypes[rand()% 7];
                                            itemStatType2 = itemStatTypes[rand()% 7];
                                            itemStatType3 = itemStatTypes[rand()% 7];
                                        }

                                        switch (item.itemRarity)
                                        {
                                            case 2: //uncommon
                                                item.statType1 = itemStatType1;
                                                item.stat1 = 1;
                                                item.numStats = 1;
                                                statName1 = itemStatNames[itemStatType1 - 1];
                                                numStats = 1;
                                                break;
                                            case 3: //rare
                                                item.statType1 = itemStatType1;
                                                item.statType2 = itemStatType2;
                                                item.stat1 = 1;
                                                item.stat2 = 1;
                                                item.numStats = 2;
                                                statName1 = itemStatNames[itemStatType1 - 1];
                                                statName2 = itemStatNames[itemStatType2 - 1];
                                                numStats = 2;
                                                break;
                                            case 4: //epic
                                                item.statType1 = itemStatType1;
                                                item.statType2 = itemStatType2;
                                                item.statType3 = itemStatType3;
                                                item.stat1 = 1;
                                                item.stat2 = 1;
                                                item.stat3 = 1;
                                                item.numStats = 3;
                                                statName1 = itemStatNames[itemStatType1 - 1];
                                                statName2 = itemStatNames[itemStatType2 - 1];
                                                statName3 = itemStatNames[itemStatType3 - 1];
                                                numStats = 3;
                                                break;
                                            case 5: //legendary
                                                item.statType1 = itemStatType1;
                                                item.statType2 = itemStatType2;
                                                item.statType3 = itemStatType3;
                                                item.stat1 = rand()% 2 + 1;
                                                item.stat2 = rand()% 2 + 1;
                                                item.stat3 = rand()% 2 + 1;
                                                item.numStats = 3;
                                                statName1 = itemStatNames[itemStatType1 - 1];
                                                statName2 = itemStatNames[itemStatType2 - 1];
                                                statName3 = itemStatNames[itemStatType3 - 1];
                                                numStats = 3;
                                                break;
                                        }

                                        switch (item.itemType)
                                        {
                                            case 2: //weapons
                                                item.name = weaponPrefixes[rand()%20];
                                                item.name +=  " " + weaponTypes[rand()% 3];
                                                if (item.name.contains("Dagger"))
                                                {
                                                    item.sellPrice = (15 * item.itemRarity) - 10;
                                                    item.weight = 2;
                                                    item.minAtk = 1;
                                                    item.maxAtk = (5 + item.itemRarity) - 1;
                                                    item.holdType = 2;
                                                }
                                                else if (item.name.contains("Short Sword"))
                                                {
                                                    item.sellPrice = (20 * item.itemRarity) - 10;
                                                    item.weight = 4;
                                                    item.minAtk = 2;
                                                    item.maxAtk = (7 + item.itemRarity);
                                                    item.holdType = rand()%1 + 1;
                                                }
                                                else if (item.name.contains("Long Sword"))
                                                {
                                                    item.sellPrice = (27 * item.itemRarity) - 15;
                                                    item.weight = 6;
                                                    item.minAtk = 3;
                                                    item.maxAtk = (9 + item.itemRarity);
                                                    item.holdType = 3;
                                                }
                                                break;
                                            case 3: //armour
                                                item.name = armourPrefixes[rand()%7];
                                                item.name +=  " " + armourTypes[rand()% 4];
                                                if (item.name.contains("Cloth"))
                                                {
                                                    item.sellPrice = (5 * item.itemRarity);
                                                    item.weight = 3;
                                                    item.armourType = 1;
                                                    item.armourRating = 4;
                                                }
                                                else if (item.name.contains("Leather"))
                                                {
                                                    item.sellPrice = (7 * item.itemRarity);
                                                    item.weight = 8;
                                                    item.armourType = 2;
                                                    item.armourRating = 3;
                                                }
                                                else if (item.name.contains("Mail"))
                                                {
                                                    item.sellPrice = (10 * item.itemRarity);
                                                    item.weight = 30;
                                                    item.armourType = 3;
                                                    item.armourRating = 2;
                                                }
                                                else if (item.name.contains("Plate"))
                                                {
                                                    item.sellPrice = (15 * item.itemRarity);
                                                    item.weight = 50;
                                                    item.armourType = 4;
                                                    item.armourRating = 1;
                                                }
                                                break;
                                            case 4: //Shield
                                                item.name = ShieldPrefixes[rand()%7] + " Shield";
                                                item.sellPrice = (15 * item.itemRarity) - 5;
                                                item.weight = 6;
                                                item.block = (7 + item.itemRarity) - 1;
                                                break;
                                            case 6: //ring
                                                item.name = ringPrefixes[rand()%2] + " Ring";
                                                item.sellPrice = (5 + item.itemRarity) - 3;
                                                item.weight = 1;
                                                break;
                                            case 7: //trinket
                                                item.name = trinketPrefixes[rand()%3] + " Trinket";
                                                item.sellPrice = (5 + item.itemRarity) - 3;
                                                item.weight = 1;
                                                break;
                                        }

                                        switch(numStats)
                                        {
                                            case 1:
                                                item.name += " of " + statName1;
                                                break;
                                            case 2:
                                                if (itemStatType1 == itemStatType2)
                                                {
                                                    item.name += " of Major " + statName1;
                                                }
                                                else
                                                {
                                                    item.name += " of " + statName1 + " and " + statName2;
                                                }
                                                break;
                                            case 3:
                                                if (itemStatType1 == itemStatType2)
                                                {
                                                    item.name += " of Major " + statName1 + " and " + statName3;
                                                }
                                                else if (itemStatType1 == itemStatType3)
                                                {
                                                    item.name += " of Major " + statName1 + " and " + statName2;
                                                }
                                                else if (itemStatType2 == itemStatType3)
                                                {
                                                    item.name += " of Major " + statName2 + " and " + statName1;
                                                }
                                                else if (itemStatType1 == itemStatType2 && itemStatType1 == itemStatType3)
                                                {
                                                    item.name += " of Maximum " + statName1;
                                                }
                                                else
                                                {
                                                    item.name += " of " + statName1 + ", " + statName2 + " and " +statName3;
                                                }
                                                break;
                                        }

                                    }
                                }
                                tempItems.push_back(item);
                            }
                        }

                        for (int f = 0; f < tempItems.length(); f++)
                        {
                            std::random_shuffle (tempItems.begin(), tempItems.end());
                        }

                        int whichItem = rand()% tempItems.length();
                        //lootMessage += numItems.value(whichItem) + "\n";
                        lootMessage += tempItems.value(whichItem).name + "\n";
                        droppedItems_.push_back(tempItems.value(whichItem));
                    }
                }
            }
        }
    }
    msgBox.setWindowTitle("Loot Drop");
    msgBox.setText(QString(lootMessage));
    msgBox.exec();

    return droppedItems_;
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

