#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <QString>
#include <QVector>
#include "item.h"

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
    int ration_;
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
    int stamina_;
    int maxStamina_;
    int block_;

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
    bool wasHealed_;
    bool rationConsumed_;
    QString name_;
    QString message_;
    QVector<Item> inventory_;
    QVector<Item> equipment_;

    int location_;

    void doLevelUp();
public:
    Player(int health, int maxHealth, int maxAttackPower, int minAttackPower,
           int vitality, int strength, int agility, int luck, int intelligence, int hit, int stamina, int maxStamina,
           int agilityDefault, int luckDefault);
    ~Player(void);

    int doAttack(QString enemy);
    int doSpecialAbility(QString enemy);
    int doHitRoll();
    void doHit(int dmg, int enemyHitRoll, QString enemyName, bool isEnemyAlive);
    void checkXP();
    void usePotion(int healAmount, int itemIndex);
    void useRation(int stamAmount, int itemIndex);
    void save();
    void load(QString playerName);
    void addHealthUpgrade(int health);
    void resetSpecialAbility();

    void addVitality(int vitality);
    void removeVitality(int vitality);
    int getVitality();

    void addStrength(int strength);
    void removeStrength(int strength);
    int getStrength();

    void addAgility(int agility);
    void removeAgility(int agility);
    int getAgility();

    void addLuck(int luck);
    void removeLuck(int luck);
    int getLuck();

    void addIntelligence(int intelligence);
    int getIntelligence();

    void addHit(int hit);
    void removeHit(int hit);
    int getHit();

    void setStamina(int stamina);
    void removeStamina(int action);
    void addStamina(int stamina);
    void removeStatStamina(int stamina);
    int getStamina();

    int getMaxStamina();
    void addMaxStamina(int maxStamina);

    int getBlock();
    void addBlock(int block);
    void removeBlock(int block);

    int getHealth();
    void setHealth(int health);
    void addHealth(int health);

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

    int getRation();
    void addRation(int ration);
    void removeRation();

    int getGold();
    void addGold(int gold);
    void removeGold(int gold);

    QVector<Item> getInventory();
    void addItemsToInventory(QVector<Item> items);
    void addItemToInventory(Item item);
    void removeItemFromInventory(int index);

    QVector<Item> getEquiped();
    void addEquipment(Item item);
    void removeEquipment(int index);

    int getLocation();
    void setLocation(int location);

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

    bool wasHealed();
    bool rationconsumed();

    int getSpecialAbilityCharged();
    void setSpecialAbilityCharged(int specialAbilityCharged);
};

#endif // PLAYER_H
