#ifndef ENEMYLOOTDROPS_H
#define ENEMYLOOTDROPS_H

#include <QString>
#include <QVector>
#include "item.h"


class enemyLootDrops
{
private:
    QVector<Item> defaultLoot_;
    QVector<Item> enemySpecificLoot_;
    int totalDropWeight_;

    QString itemStatNames[7] = {"Vitality","Strength","Stamina","Agility","Luck","Precision","Block"};
    QString weaponTypes[3] = {"Dagger","Short Sword","Long Sword"};
    QString armourTypes[4] = {"Cloth","Leather","Mail","Plate"};
    QString weaponPrefixes[20] = {"Sharp", "Sharpened", "Pointy", "Radient", "Rigid", "Immaculate", "Gouging", "Dangerous", "Vibrant", "Fancy",
                                  "Menacing", "Slick",  "Jagged", "Dancing", "Blistering", "Mincing","Elegant", "Ravenous", "Fierce",  "Righteous"};
    QString armourPrefixes[7] = {"Radient","Immaculate","Vibrant","Fancy","Slick","Elegant","Righteous"};
    QString ShieldPrefixes[7] = {"Steel", "Tower", "Buckler", "Small", "Kiting", "Large", "Aspis"};
    QString ringPrefixes[3] = {"Copper", "Silver", "Gold"};
    QString trinketPrefixes[3] = {"Small", "Medium", "Large"};

    QString banditDefaultItemDrops_ [19][18] = {
        {"Tattered Shirt",      "0","9","0","0","0","0","0","5","0","0","0","0","0","0","0","0","200"},
        {"Bandana",             "0","9","0","0","0","0","0","2","0","0","0","0","0","0","0","0","85"},
        {"Busted Hilt",         "0","9","0","0","0","0","0","2","0","0","0","0","0","0","0","0","80"},
        {"Watch",               "0","9","0","0","0","0","0","7","0","0","0","0","0","0","0","0","75"},
        {"Leather Strap",       "0","9","0","0","0","0","0","4","0","0","0","0","0","0","0","0","60"},
        {"Weak potion",         "0","1","0","0","1","2","0","2","1","0","0","0","0","0","0","0","100"},
        {"Weak Dagger",         "1","2","0","0","0","0","1","10","0","1","3","0","2","1","1","1","40"},
        {"Weak Short Sword",    "1","2","0","0","0","0","1","15","0","1","4","0","1","2","1","1","40"},
        {"Weak Wooden Shield",  "1","4","0","0","0","0","1","10","0","0","0","4","2","0","0","0","40"},
        {"Weak Long Sword",     "1","2","0","0","0","0","1","20","0","1","7","0","3","3","1","1","40"},
        {"Ration",              "0","1","0","0","2","5","0","10","1","0","0","0","0","0","0","0","25"},
        {"Short Sword",         "1","2","0","0","0","0","1","17","0","2","5","0","1","2","1","1","20"},
        {"Dagger",              "1","2","0","0","0","0","1","12","0","1","4","0","2","1","1","1","20"},
        {"Long Sword",          "1","2","0","0","0","0","1","25","0","3","7","0","3","3","1","1","20"},
        {"Wooden Shield",       "1","4","0","0","0","0","1","12","0","0","0","5","2","0","0","0","20"},
        {"Sharp Dagger",        "1","2","0","0","0","0","1","15","0","1","5","0","2","1","1","1","10"},
        {"Sharp Short Sword",   "1","2","0","0","0","0","1","20","0","2","7","0","1","2","1","1","10"},
        {"Sharp Long Sword",    "1","2","0","0","0","0","1","27","0","3","9","0","3","3","1","1","10"},
        {"Steel Shield",        "1","4","0","0","0","0","1","15","0","0","0","7","2","0","0","0","10"}
    };

    QString banditInitiateItemDrops_ [5][18] = {
        {"Bandit Initiate Armour","0","9","0","0","0","0","0","15","0","0","0","0","0","0","0","0","50"},
        {"Broken Dagger",       "0","9","0","0","0","0","0","5","0","0","0","0","0","0","0","0","90"},
        {"Broken Short Sword",  "0","9","0","0","0","0","0","7","0","0","0","0","0","0","0","0","90"},
        {"Broken Long Sword",   "0","9","0","0","0","0","0","10","0","0","0","0","0","0","0","0","90"},
        {"Broken Wooden Shield","0","9","0","0","0","0","0","5","0","0","0","0","0","0","0","0","90"}
    };

    QString banditTrainerItemDrops_ [4][18] = {
        {"Bandit Trainer Armour","0","9","0","0","0","0","0","15","0","0","0","0","0","0","0","0","50"},
        {"Potion",               "0","1","0","0","1","5","0","10","0","0","0","0","0","0","0","0","50"},
        {"Uncommon Item",        "2","8","0","0","0","0","1","0","0","0","0","0","0","0","0","0","20"},
        {"Rare Item",            "3","8","0","0","0","0","1","0","0","0","0","0","0","0","0","0","5"}
    };

    QString banditGrenItemDrops_ [5][18] = {
        {"Gren's Armour",     "0","9","0","0","0","0","0","30","0","0","0","0","0","0","0","0","50"},
        {"Potion",            "0","1","0","0","1","5","0","10","0","0","0","0","0","0","0","0","50"},
        {"Uncommon Item",     "2","8","0","0","0","0","1","0","0","0","0","0","0","0","0","0","20"},
        {"Rare Item",         "3","8","0","0","0","0","1","0","0","0","0","0","0","0","0","0","5"},
        {"Epic Item",         "4","8","0","0","0","0","1","0","0","0","0","0","0","0","0","0","3"}
    };

    QString banditRaiderItemDrops_ [3][18] = {
        {"Bandit Raider Armour", "0","9","0","0","0","0","0","25","0","0","0","0","0","0","0","0","50"},
        {"Potion",               "0","1","0","0","1","5","0","10","0","0","0","0","0","0","0","0","50"},
        {"Uncommon Item",        "2","8","0","0","0","0","1","0","0","0","0","0","0","0","0","0","15"},
    };

    QString banditAmbusherItemDrops_ [8][18] = {
        {"Bandit Initiate Armour","0","9","0","0","0","0","0","25","0","0","0","0","0","0","0","0","50"},
        {"Potion",                "0","1","0","0","1","5","0","10","0","0","0","0","0","0","0","0","50"},
        {"Uncommon Item",         "2","8","0","0","0","0","1","0","0","0","0","0","0","0","0","0","5"},
        {"Rare Item",             "3","8","0","0","0","0","1","0","0","0","0","0","0","0","0","0","3"},
        {"Broken Dagger",         "0","9","0","0","0","0","0","5","0","0","0","0","0","0","0","0","90"},
        {"Broken Short Sword",    "0","9","0","0","0","0","0","7","0","0","0","0","0","0","0","0","90"},
        {"Broken Long Sword",     "0","9","0","0","0","0","0","10","0","0","0","0","0","0","0","0","90"},
        {"Broken Wooden Shield",  "0","9","0","0","0","0","0","5","0","0","0","0","0","0","0","0","90"}
    };
public:
    enemyLootDrops();
    QVector<Item> doLootDrop(QString enemyName, QVector<Item> enemyLoot, int itemDropChance);

    void setLoot(int enemyType);

    QVector<Item> getDefaultLoot();
    QVector<Item> getEnemySpecificLoot();

    void CalculateTotalDropWeight(QVector<Item> loot);
};

#endif // ENEMYLOOTDROPS_H
