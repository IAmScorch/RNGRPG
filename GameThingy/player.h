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
    int XP_;
    int XPTillLevel_;
    int skillpoints_;
    int level_;
    int potion_;
    int gold_;
    int specialAbilityMaxCharges_;
    int specialAbilityCharged_;
    int specialAbilityCharge_;

    int vitality_;
    int strength_;
    int agility_;
    int luck_;
    int intelligence_;
    int hit_;

    int strengthCount_;
    int agilityCount_;
    int luckCount_;
    int intelligenceCount_;
    int hitCount_;

    int agilityBonus_;
    int luckBonus_;
    int intelligenceBonus_;
    int hitBonus_;

    int agilityDefault_;
    int luckDefault_;

    int questsCompleted_;

    bool isSpecialAbilityLearned_;
    bool isSpecialReady_;
    bool isAlive_;
    QString name_;
    QString message_;

    void doLevelUp();
public:
    Player(int health, int maxHealth, int maxAttackPower, int minAttackPower,
           int vitality, int strength, int agility, int luck, int intelligence, int hit,
           int agilityDefault, int luckDefault);
    ~Player(void);

    int doAttack(QString enemy);
    int doSpecialAbility(QString enemy);
    int doHitRoll();
    void doHit(int dmg, int enemyHitRoll, QString enemyName, bool isEnemyAlive);
    void checkXP();
    void usePotion();
    void buyPotion();
    void save();
    void load(QString playerName);
    void addHealthUpgrade(int health);
    void resetSpecialAbility();

    void addVitality(int vitality);
    int getVitality();

    void addStrength(int strength);
    int getStrength();

    void addAgility(int agility);
    int getAgility();

    void addLuck(int luck);
    int getLuck();

    void addIntelligence(int intelligence);
    int getIntelligence();

    void addHit(int hit);
    int getHit();

    int getHealth();
    void setHealth(int health);

    int getMaxHealth();
    void setMaxHealth(int maxHealth);

    int getMaxAttackPower();
    void setMaxAttackPower(int maxAttackPower);

    int getMinAttackPower();
    void setMinAttackPower(int minAttackPower);

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

    int getQuestsCompleted();
    void completeQuest();

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
