#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <QString>

class Player
{
private:
    int health_;
    int maxHealth_;
    int maxAttackPower_;
    int minAttackPower_;
    int attackDmg_;
    int critChance_;
    int critNum_;
    int critDmg_;
    int XP_;
    int XPTillLevel_;
    int skillpoints_;
    int level_;
    int potion_;
    int gold_;
    int specialAbilityMaxCharges_;
    int specialAbilityCharged_;
    int specialAbilityCharge_;

    int stamina_;
    int strength_;
    int agility_;
    int agilityBonus_;
    int agilityDefault_;
    int luck_;
    int luckBonus_;
    int intelligence_;
    int intelligenceBonus_;

    bool isSpecialAbilityLearned_;
    bool isSpecialReady_;
    bool isAlive_;
    QString name_;
    QString message_;

    void doLevelUp();
public:
    Player(int health, int maxHealth, int maxAttackPower, int minAttackPower, int critChance);
    ~Player(void);

    int doAttack(QString enemy);
    int doSpecialAbility(QString enemy);
    int doHitRoll();
    void doHit(int dmg, int enemyHitRoll, QString enemyName, bool isEnemyAlive);
    QString printPlayerInfo();
    void checkXP();
    void usePotion();
    void buyPotion();
    void save();
    void load(QString playerName);
    void addHealthUpgrade(int health);
    void resetSpecialAbility();

    int getHealth();
    void setHealth(int health);

    int getMaxHealth();
    void setMaxHealth(int maxHealth);

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

    int getXP();
    void addXP(int XP);

    int getXPTillLevel();
    void setXPTillLevel(int XPTillLevel);

    int getSkillPoints();
    void setSkillPoints(int skillPoints);

    int getPotion();
    void addPotion(int potion);

    int getGold();
    void addGold(int gold);

    QString getName();
    void setName(QString name);

    bool isAlive();

    QString getMessage(); 
    void setMessage(QString message);

    int getSpecialAbilityMaxCharges();
    void setSpecialAbilityMaxCharges(int specialAbilityMaxCharges);

    int getSpecialAbilityCharge();
    void addSpecialAbilityCharge(int specialAbilityCharge);

    bool isSpecialAbilityLeanred();
    void learnSpecialAbility();

    bool IsSpecialReady();
    void setIsSpecialReady(bool isSpecialReady);

    int getSpecialAbilityCharged();
    void setSpecialAbilityCharged(int specialAbilityCharged);
};

#endif // PLAYER_H
