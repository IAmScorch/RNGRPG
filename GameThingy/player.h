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
    int defaultHealth_;
    int maxHealth_;
    int maxAttackPower_;
    int maxWeaponAP_;
    int minAttackPower_;
    int minWeaponAP_;
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
    int classType_;

    int vitality_;
    int statVitality_;
    int equippedVitality_;

    int strength_;
    int statStrength_;
    int equippedStrength_;

    int agility_;
    int agilityDefault_;
    int statAgility_;
    int equippedAgility_;

    int luck_;
    int luckDefault_;
    int statLuck_;
    int equippedLuck_;

    int intelligence_;
    int statIntelligence_;
    int equippedIntelligence_;
    int intelligenceBonus_;

    int precision_;
    int statPrecision_;
    int equippedPrecision_;

    int stamina_;
    int defaultStamina_;
    int statStamina_;
    int equippedStamina_;
    int maxStamina_;

    int block_;
    bool isShieldEquipped_;
    int mainHandSlot_;
    int offHandSlot_;
    int armourSlot_;
    int ringSlotOne_;
    int ringSlotTwo_;
    int trinketSlotOne_;
    int trinketSlotTwo_;
    bool itemEquipped_;

    int questsCompleted_;


    bool isSpecialAbilityLearned_;
    bool isSpecialReady_;
    bool isAlive_;
    QString name_;
    QString message_;
    QVector<Item> inventory_;
    QVector<Item> equipment_;

    int location_;

    void doLevelUp();
public:
    Player(int defaultHealth, int intelligence, int defaultStamina,
           int agilityDefault, int luckDefault, int classType);
    ~Player(void);

    int doAttack(QString enemy);
    int doSpecialAbility(QString enemy);
    int doHitRoll();
    void doHit(int dmg, int enemyHitRoll, QString enemyName, bool isEnemyAlive);
    void checkXP();
    void usePotion(int healAmount, int itemIndex);
    void useRation(int stamAmount, int itemIndex);
    void save();
    void saveInventory();
    void saveEquipment();
    void load(QString playerName);
    void loadInventory(QString playerName);
    void loadEquipment(QString playerName);
    void addHealthUpgrade(int health);
    void resetSpecialAbility();

    int getClassType();

    void addStatVitality(int vitality);
    void addEquippedVitality(int vitality);
    void removeVitality(int vitality);
    void setMaxHealth();
    int getVitality();
    int getStatVitality();

    void addStatStrength(int strength);
    void addEquippedStrength(int strength);
    void removeStrength(int strength);
    void setStrength();
    int getStrength();
    int getStatStrength();

    void addStatAgility(int agility);
    void addEquippedAgility(int agility);
    void removeAgility(int agility);
    void setAgility();
    int getAgility();
    int getStatAgility();

    void addStatLuck(int luck);
    void addEquippedLuck(int luck);
    void removeLuck(int luck);
    void setLuck();
    int getLuck();
    int getStatLuck();

    void addIntelligence(int intelligence);
    int getIntelligence();

    void addStatPrecision(int precision);
    void addEquippedPrecision(int precision);
    void removePrecision(int precision_);
    void setPrecision();
    int getPrecision();
    int getStatPrecision();

    void setStamina(int stamina);
    void setMaxStamina();
    void removeStamina(int action);
    void addStamina(int stamina);
    void removeStatStamina(int stamina);
    void addStatStamina(int stamina);
    void addEquippedStamina(int stamina);
    int getStamina();
    int getMaxStamina();
    int getStatStamina();

    int getTotalAgilityPoints();
    int getTotalVitalityPoints();
    int getTotalStrengthPoints();
    int getTotalPrecisionPoints();
    int getTotalLuckPoints();
    int getTotalStaminaPoints();

    int getBlock();
    void addBlock(int block);
    void removeBlock(int block);

    void equipArmour(int armourRating);
    void unequipArmour(int armourRating);

    int getHealth();
    void setHealth(int health);
    void addHealth(int health);

    int getMaxHealth();
    void setMaxHealth(int maxHealth);

    void calculateMaxAttackPower();
    void calculateMinAttackPower();
    int getMaxAttackPower();
    int getMinAttackPower();

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
    void addStarterEquipment();

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

    int getSpecialAbilityCharged();
    void setSpecialAbilityCharged(int specialAbilityCharged);

    void equippedShield();
    void unequippedShield();

    bool itemEquipped();
    void displayMessage(QString title, QString message);
};

#endif // PLAYER_H
