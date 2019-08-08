#ifndef BANDIT_H
#define BANDIT_H
#include <QString>

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
    bool isAlive_;
    bool isHit_;
    QString message_;

public:
    Bandit(QString name, int health, int maxAttackPower, int minAttackPower,
        int critChance, int XPReward, int level, int enemyType, int agility, int objType);
    ~Bandit(void);

    int doAttack(QString enemy);
    int doHitRoll();
    void doHit(int dmg, int playerHitRoll, QString playerName);
    int goldDrop();

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
};

#endif // BANDIT_H
