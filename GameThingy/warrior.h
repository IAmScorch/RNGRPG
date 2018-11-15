#ifndef WARRIOR_H
#define WARRIOR_H
#include <string>
#include <QString>

class Warrior
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
    bool isAlive_;
    QString message_;

public:
    Warrior(QString name, int health, int minAttackPower,
        int critChance, int XPReward, int level);
    ~Warrior(void);

    int doAttack(QString enemy);
    void doHit(int dmg);
    int goldDrop();
    int healthUpgradeDrop();

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

    QString getMessage();

    bool isAlive();
};

#endif // WARRIOR_H
