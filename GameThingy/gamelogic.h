#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QListWidget>
#include <QMainWindow>
#include <QShortcut>
#include <string>
#include "player.h"
#include "bandit.h"
#include "warrior.h"
#include "quests.h"
#include "inventorybag.h"
#include "itemcrossreference.h"
#include "enemylootdrops.h"
#include "itemcolor.h"

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
    void setPlayerStamina();
    void setEnemyHealth();
    void resetQuestInfo();
    void closeBag();
    void equipItem();
    void unequipItem();
    void useItem();
    void sellItem();

    void on_tabGame_tabBarClicked(int index);

    void on_btnIncreaseAgility_clicked();

    void on_btnIncreaseHitChance_clicked();

    void on_btnIncreaseStamina_clicked();

    void on_btnUseRationBS_clicked();

    void on_btnTravel_clicked();

    void on_btnBuyRation_clicked();

    void on_btnRestBS_clicked();

    void setPlayerInventory();

    void setPlayerEquipment();

    void setInventoryItemToolTip(QVector<ItemColor> listItems);

    void setEquipmentItemToolTip(QVector<ItemColor> listItems);

    void on_lstInventory_itemClicked(QListWidgetItem *item);

    void on_btnUse_clicked();

    void on_btnEquip_clicked();

    void on_btnSell_clicked();

    void on_btnDrop_clicked();

    void on_lstInventory_doubleClicked(const QModelIndex &index);

    void on_lstEquipment_itemDoubleClicked(QListWidgetItem *item);

    void on_lstEquipment_itemClicked(QListWidgetItem *item);

    void on_btnBuyBedroll_clicked();

    void on_btnBuyFirestarterKit_clicked();

private:
    //Locations
    //0 - Windlehelm
    //1 - Bandit Barracks
    //2 - Deepwood Forest
    //3 - Riverbane
    //4 - Riverbane Mine
    //5 - Andorjaul
    enum locations_ {
        windlehelm = 0,
        banditBarracks,
        deepwoodForest,
        riverbane,
        riverbaneMine,
        andorjaul
    };

    QString strLocations_[6] = {"Windlehelm",
                                "Bandit Barracks",
                                "Deepwood Forest",
                                "Riverbane",
                                "Riverbane Mine",
                                "Andorjaul"};

    QString strRestLocation_[6] = {"City",
                                   "Camp",
                                   "Camp",
                                   "Town",
                                   "Camp",
                                   "Town"};
    /*Item Types                      armourType	amourRating     statTypes
  1 = Consumable	6 = Ring		1 = Cloth	+4 dodge        1 = Vitality	6 = Precision
  2 = Weapon		7 = Trinket		2 = Leather	+3 dodge        2 = Strength	7 = Dodge
  3 = Armour		8 = random		3 = Mail	+2 dodge        3 = Stamina     8 = Block
  4 = Shield		9 = Junk		4 = Plate	+1 dodge        4 = Agility		9 = Hit
  5 = Quest                                                   5 = Luck

  itemRarity          healType            Class Types                                     holdType
  1 = common          1 = Health          1 = Wizard 	(Cloth) 	Agility default = 8     1 = main hand
  2 = uncommon        2 = Stamina         2 = Rogue	(Leather)	Agility default = 7     2 = 1 handed
  3 = rare                                3 = Warrior	(Mail)		Agility default = 6     3 = 2 handed
  4 = epic  5 = legendary                 4 = Knight	(Plate)		Agility default = 5
  0 = consumable, junk or quest item*/

    Ui::GameLogic *ui;
    Player *player_;
    Bandit *bandit_;
    Bandit *banditBoss_;
    Warrior *warrior_;
    Warrior *warriorBoss_;
    quests *quest_;
    InventoryBag *bag_;
    itemCrossReference *itemXRef;
    enemyLootDrops *lootDrops_;
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
    bool isBagOpen_;
    locations_ location_;
    bool isEquipping;

    void checkLevel();
    void createCharacter();
    void setPlayerInfo();
    void checkSkillPoints();
    void checkQuest();
    void checkLocation();
};

#endif // GAMELOGIC_H
