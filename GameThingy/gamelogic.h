#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QMainWindow>
#include <QShortcut>
#include <string>
#include "player.h"
#include "bandit.h"
#include "warrior.h"
#include "quests.h"

namespace Ui {
class GameLogic;
}

class GameLogic : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameLogic(QWidget *parent = nullptr);
    ~GameLogic();

private slots:
    void on_btnQuit_clicked();

    void on_btnNewGame_clicked();

    void on_btnAttack_clicked();

    void on_btnBattle_clicked();

    void on_btnSave_clicked();

    void on_btnLoad_clicked();

    void on_btnUsePotion_clicked();

    void on_btnBuyPotion_clicked();

    void on_btnUsePotionBS_clicked();

    void on_btnIncreaseHP_clicked();

    void on_btnIncreaseAttack_clicked();

    void on_btnIncreaseCritChance_clicked();

    void on_btnBeginQuest_clicked();

    void on_btnCompleteQuest_clicked();

    void on_btnAbandonQuest_clicked();

    void on_btnSpecialAbility_clicked();

    void openMenuTab();
    void openActionTab();
    void openBattleTab();
    void openCharacterTab();
    void openQuestTab();
    void setPlayerHealth();
    void setEnemyHealth();
    void resetQuestInfo();

    void on_tabGame_tabBarClicked(int index);

private:
    Ui::GameLogic *ui;
    Player *player_;
    Bandit *bandit_;
    Bandit *banditBoss_;
    Warrior *warrior_;
    Warrior *warriorBoss_;
    quests *quest_;
    QString name_;
    QString message_;
    QShortcut *msNewGameSC_;
    QShortcut *msSaveGameSC_;
    QShortcut *msQuitGameSC_;
    QShortcut *msLoadGameSC_;
    QShortcut *asBuyPotionSC_;
    QShortcut *asUsePotionSC_;
    QShortcut *bsBattleSC_;
    QShortcut *bsUsePotionSC_;
    QShortcut *bsAttackSC_;
    QShortcut *bsSpecialSC_;
    QShortcut *csAddHPSC_;
    QShortcut *csAddAPSC_;
    QShortcut *csAddCCSC_;
    QShortcut *qsBeginSC_;
    QShortcut *qsAbandonSC_;
    QShortcut *qsHandInSC_;
    int enemyMaxHP_;

    void checkLevel();
    void createCharacter();
    void setPlayerInfo();
    void checkSkillPoints();
    void checkQuest();
};

#endif // GAMELOGIC_H
