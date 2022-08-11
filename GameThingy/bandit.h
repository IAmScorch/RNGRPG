#ifndef BANDIT_H
#define BANDIT_H
#include <QString>
#include "item.h"

class Bandit
{
private:
    QString name_;
    int health_;
    int maxAttackPower_;
    int minAttackPower_;
    int attackDmg_;
    int critChance_;
    int critNum_;
    int critDmg_;
    int XPReward_;
    int level_;
    int enemyType_;
    int agility_;
    int objType_;
    int itemDropChance_;
    bool isAlive_;
    bool isHit_;
    QString message_;

    QString itemStatNames[7] = {"Vitality","Strength","Stamina","Agility","Luck","Precision","Block"};
    QString weaponTypes[3] = {"Dagger","Short Sword","Long Sword"};
    QString armourTypes[4] = {"Cloth","Leather","Mail","Plate"};
    QString weaponPrefixes[20] = {"Sharp", "Sharpened", "Pointy", "Radient", "Rigid", "Immaculate", "Gouging", "Dangerous", "Vibrant", "Fancy",
                                  "Menacing", "Slick",  "Jagged", "Dancing", "Blistering", "Mincing","Elegant", "Ravenous", "Fierce",  "Righteous"};
    QString armourPrefixes[7] = {"Radient","Immaculate","Vibrant","Fancy","Slick","Elegant","Righteous"};
    QString ShieldPrefixes[7] = {"Steel", "Tower", "Buckler", "Small", "Kiting", "Large", "Aspis"};
    QString ringPrefixes[3] = {"Copper", "Silver", "Gold"};
    QString trinketPrefixes[3] = {"Small", "Medium", "Large"};

    QString banditItemDrops_ [17][16] = {
        {"Tattered Shirt",      "0","9","0","0","0","0","0","5","0","1","0","0","0","0","200"},
        {"Weak potion",         "0","1","0","0","1","2","0","2","1","1","0","0","0","0","100"},
        {"Weak Dagger",         "1","2","0","0","0","0","1","10","0","2","1","3","0","2","40"},
        {"Weak Short Sword",    "1","2","0","0","0","0","1","15","0","4","1","4","0","1","40"},
        {"Weak Wooden Shield",  "1","4","0","0","0","0","1","10","0","5","0","0","4","2","40"},
        {"Wooden Shield",       "1","4","0","0","0","0","1","12","0","5","0","0","5","2","40"},
        {"Weak Long Sword",     "1","2","0","0","0","0","1","20","0","6","1","7","0","3","35"},
        {"Ration",              "0","1","0","0","2","5","0","10","1","1","0","0","0","0","20"},
        {"Short Sword",         "1","2","0","0","0","0","1","17","0","4","2","5","0","1","20"},
        {"Dagger",              "1","2","0","0","0","0","1","12","0","2","1","4","0","2","20"},
        {"Long Sword",          "1","2","0","0","0","0","1","25","0","6","3","7","0","3","15"},
        {"Sharp Dagger",        "1","2","0","0","0","0","1","15","0","2","1","5","0","2","10"},
        {"Sharp Short Sword",   "1","2","0","0","0","0","1","20","0","4","2","7","0","1","10"},
        {"Sharp Long Sword",    "1","2","0","0","0","0","1","27","0","6","3","9","0","3","10"},
        {"Steel Shield",        "1","4","0","0","0","0","1","15","0","6","0","0","7","2","10"},
        {"Uncommon Item",       "2","8","0","0","0","0","1","0","0","0","0","0","0","0","5"},
        {"Rare Item",           "3","8","0","0","0","0","1","0","0","0","0","0","0","0","1"}
    };

    QString banditItemDropsChance_ [2][9] = {
        {"200","100","40","35","20","15","10","5","1"},
        {"1", "1", "4", "1", "3", "1", "4", "1","1"}
    };

    QString banditInitiateItemDrops_ [1][16] = {
        {"Bandit Initiate Armour","0","9","0","0","0","0","0","7","0","3","0","0","0","0","50"}
    };

    QString banditTrainerItemDrops_ [2][16] = {
        {"Bandit Trainer Armour","0","9","0","0","0","0","0","7","0","3","0","0","0","0","50"},
        {"Potion","0","1","0","0","1","5","0","10","0","1","0","0","0","0","30"}
    };

    QString banditGrenItemDrops_ [2][16] = {
        {"Trainer Gren's Head","0","9","0","0","0","0","0","7","0","3","0","0","0","0","100"},
        {"Potion","0","1","0","0","1","5","0","10","0","1","0","0","0","0","30"}
    };

    QString banditRaiderItemDrops_ [2][16] = {
        {"Bandit Raider Armour","0","9","0","0","0","0","0","7","0","3","0","0","0","0","50"},
        {"Potion","0","1","0","0","1","5","0","10","0","1","0","0","0","0","30"}
    };

    QString banditAmbusherItemDrops_ [2][16] = {
        {"Bandit Initiate Armour","0","9","0","0","0","0","0","7","0","3","0","0","0","0","50"},
        {"Potion","0","1","0","0","1","5","0","10","0","1","0","0","0","0","30"}
    };

public:
    Bandit(QString name, int health, int maxAttackPower, int minAttackPower,
        int critChance, int XPReward, int level, int enemyType, int agility, int objType, int itemDropChance);
    ~Bandit(void);

    int doAttack(QString enemy);
    int doHitRoll();
    void doHit(int dmg, int playerHitRoll, QString playerName);
    int goldDrop();
    QVector<Item> doLootDrop(QString enemyName, int enemyType, int itemDropChance);

    int getHealth();
    void setHealth(int health);

    int getMaxAttackPower();
    void setMaxAttackPower(int maxAttackPower);

    int getMinAttackPower();
    void setMinAttackPower(int minAttackPower);

    int getCritChance();
    void setCritChance(int critChance);

    int getLevel();
    void setLevel(int level);

    int getAttackDmg();
    void setAttackDmg(int attackDmg);

    int getXPReward();
    void setXPReward(int XPReward);

    QString getName();
    void setName(QString name);

    int getObjType();

    bool isAlive();

    bool isHit();

    QString getMessage();
    void setMessage(QString message);

    int getEnemyType();
    void setEnemyType(int enemyType);

    int getItemDropChance();
};

#endif // BANDIT_H
