#include <iostream>
#include <QString>
#include <random>
#include <ctime>
#include <QTime>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QInputDialog>
#include <QSound>
#include <QShortcut>
#include <QDir>
#include "gamelogic.h"
#include "ui_IntroMenu.h"

GameLogic::GameLogic(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameLogic)
{
    //asBuyPotionSC_ = new QShortcut(QKeySequence(Qt), this, SLOT);
    new QShortcut(QKeySequence(Qt::Key_1), this, SLOT(openMenuTab()));
    msNewGameSC_ = new QShortcut(QKeySequence(Qt::Key_N), this, SLOT(on_btnNewGame_clicked()));
    msSaveGameSC_ = new QShortcut(QKeySequence(Qt::Key_F5), this, SLOT(on_btnSave_clicked()));
    msLoadGameSC_ = new QShortcut(QKeySequence(Qt::Key_F6), this, SLOT(on_btnLoad_clicked()));
    msQuitGameSC_ = new QShortcut(QKeySequence(Qt::Key_Q), this, SLOT(on_btnQuit_clicked()));

    new QShortcut(QKeySequence(Qt::Key_2), this, SLOT(openActionTab()));
    asBuyPotionSC_ = new QShortcut(QKeySequence(Qt::Key_B), this, SLOT(on_btnBuyPotion_clicked()));
    asUsePotionSC_ = new QShortcut(QKeySequence(Qt::Key_P), this, SLOT(on_btnUsePotion_clicked()));

    new QShortcut(QKeySequence(Qt::Key_3), this, SLOT(openBattleTab()));
    bsBattleSC_ = new QShortcut(QKeySequence(Qt::Key_B), this, SLOT(on_btnBattle_clicked()));
    bsUsePotionSC_ = new QShortcut(QKeySequence(Qt::Key_P), this, SLOT(on_btnUsePotionBS_clicked()));
    bsAttackSC_ = new QShortcut(QKeySequence(Qt::Key_A), this, SLOT(on_btnAttack_clicked()));
    bsSpecialSC_ = new QShortcut(QKeySequence(Qt::Key_S), this, SLOT(on_btnSpecialAbility_clicked()));

    new QShortcut(QKeySequence(Qt::Key_4), this, SLOT(openCharacterTab()));
    csAddHPSC_ = new QShortcut(QKeySequence(Qt::Key_H), this, SLOT(on_btnIncreaseHP_clicked()));
    csAddAPSC_ = new QShortcut(QKeySequence(Qt::Key_A), this, SLOT(on_btnIncreaseAttack_clicked()));
    csAddCCSC_ = new QShortcut(QKeySequence(Qt::Key_C), this, SLOT(on_btnIncreaseCritChance_clicked()));

    new QShortcut(QKeySequence(Qt::Key_5), this, SLOT(openQuestTab()));
    qsBeginSC_ = new QShortcut(QKeySequence(Qt::Key_B), this, SLOT(on_btnBeginQuest_clicked()));
    qsAbandonSC_ = new QShortcut(QKeySequence(Qt::Key_A), this, SLOT(on_btnAbandonQuest_clicked()));
    qsHandInSC_ = new QShortcut(QKeySequence(Qt::Key_H), this, SLOT(on_btnCompleteQuest_clicked()));

    msNewGameSC_->setEnabled(true);
    msSaveGameSC_->setEnabled(false);
    msLoadGameSC_->setEnabled(true);
    msQuitGameSC_->setEnabled(true);
    asBuyPotionSC_->setEnabled(false);
    asUsePotionSC_->setEnabled(false);
    bsBattleSC_->setEnabled(false);
    bsUsePotionSC_->setEnabled(false);
    bsAttackSC_->setEnabled(false);
    bsSpecialSC_->setEnabled(false);
    csAddHPSC_->setEnabled(false);
    csAddAPSC_->setEnabled(false);
    csAddCCSC_->setEnabled(false);
    qsBeginSC_->setEnabled(false);
    qsAbandonSC_->setEnabled(false);
    qsHandInSC_->setEnabled(false);

    ui->setupUi(this);
    ui->tabStoreScreen->setEnabled(false);
    ui->tabCInfoScreen->setEnabled(false);
    ui->tabQuestScreen->setEnabled(false);
    ui->txtBattleInfo->setEnabled(false);
    ui->btnAttack->setEnabled(false);
    ui->btnAttack->setFixedHeight(41);
    ui->btnSpecialAbility->setEnabled(false);
    ui->btnSpecialAbility->setVisible(false);
    ui->btnBattle->setEnabled(false);
    ui->btnTravel->setEnabled(false);
    ui->btnUsePotionBS->setEnabled(false);
    ui->btnUseRationBS->setEnabled(false);
    ui->btnRestBS->setEnabled(false);
    ui->btnBeginQuest->setEnabled(false);
    ui->btnCompleteQuest->setEnabled(false);
    ui->btnAbandonQuest->setEnabled(false);
    ui->btnSpecialAbility->setEnabled(false);
    ui->btnUse->setEnabled(false);
    ui->btnEquip->setEnabled(false);
    ui->btnSell->setEnabled(false);
    ui->btnDrop->setEnabled(false);
    ui->lblEHealth->setFixedWidth(0);
    ui->lblEHealthAmount->setText("0");
    ui->lblQuestTabBG->setPixmap(QPixmap("Img\\tabQuestBG.png"));
    ui->lblMenuTabBG->setPixmap(QPixmap("Img\\tabMenuBG.png"));
    ui->lblBattleTabBG->setPixmap(QPixmap("Img\\tabBattleBG.png"));
    ui->lblCharTabBG->setPixmap(QPixmap("Img\\tabCharacterBG.png"));
    ui->lblActionTabBG->setPixmap(QPixmap("Img\\tabActionBG.png"));
    ui->lblInvTabBG->setPixmap(QPixmap("Img\\tabCharacterBG.png"));

    ui->btnNewGame->setStyleSheet("background-color: rgb(225, 225, 225, 200)");
    ui->btnLoad->setStyleSheet("background-color: rgb(225, 225, 225, 200)");
    ui->btnSave->setStyleSheet("background-color: rgb(225, 225, 225, 200)");
    ui->btnQuit->setStyleSheet("background-color: rgb(225, 225, 225, 200)");
    bandit_ = new Bandit("", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    banditBoss_ = new Bandit("", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    warrior_ = new Warrior("", 0, 0, 0, 0, 0);
    warriorBoss_ = new Warrior("", 0, 0, 0, 0, 0);
    player_ = new Player(0, 0, 0, 0, 0, 0);
    quest_ = new quests(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "");
    itemXRef = new itemCrossReference();
    lootDrops_ = new enemyLootDrops();
    isBagOpen_ = false;
    isEquipping = true;
    qsrand(QTime::currentTime().msec());
}

GameLogic::~GameLogic()
{
    delete ui;
}

void GameLogic::on_btnQuit_clicked()
{
    this->close();
}

void GameLogic::on_btnNewGame_clicked()
{
    ui->btnSave->setEnabled(true);
    ui->tabStoreScreen->setEnabled(true);
    ui->tabCInfoScreen->setEnabled(true);
    ui->tabQuestScreen->setEnabled(true);
    ui->btnBattle->setEnabled(false);
    ui->btnTravel->setEnabled(true);
    ui->btnBeginQuest->setEnabled(true);
    msSaveGameSC_->setEnabled(true);
    ui->btnUsePotionBS->setEnabled(true);
    ui->btnUseRationBS->setEnabled(true);
    ui->btnRestBS->setEnabled(true);
    ui->lblEHealth->setFixedWidth(0);
    ui->lblEHealthAmount->setText("0");
    ui->lblELevel->setText("0");
    ui->lblEnemyName->setText(" ");
    ui->txtBattleInfo->setText(" ");
    resetQuestInfo();
    createCharacter();
    setPlayerInfo();
    checkLocation();
    ui->txtBattleInfo->setText(message_);
    ui->txtBattleInfo->setEnabled(true);

    QMessageBox msgBox;
    msgBox.setWindowTitle("First Time Player Info");
    msgBox.setText(QString("<b>Welcome to Rendinshire, %1</b><br>"
                           "-------------------------------------------------------------------------------------------<br><br>"
                           "There are many places to visit here in Rendinshire.<br>"
                           "To travel to these locations, go to the <b>Battle</b> tab<br>"
                           "and press the <b>Travel</b> button.<br><br>"
                           "When you travel, it costs you <b>Stamina</b>. That's right, you need <b>Stamina</b><br>"
                           "to complete actions here in Rendinshire.<br>"
                           "<b>Stamina</b> is indicated by a small blue bar at the bottom left of the <b>Battle</b> tab<br><br>"
                           "Actions are defined as traveling and fighting. When you travel or fight<br>"
                           "an enemy, it costs <b>Stamina</b>. If you run out of <b>Stamina</b>, you can no longer<br>"
                           "travel between areas and must rest or eat a ration to restore your <b>Stamina</b><br>"
                           "You can rest by setting up camp or by visiting a town or city and rest<br>"
                           "at an Inn. However, a room at an Inn will cost you gold, but they will<br>"
                           "retore both <b>Health</b> and <b>Stamina</b>. City Inns fully restore you, and town Inns<br>"
                           "restore just a bit of your <b>Health</b> and <b>Stamina</b>.<br>"
                           "Camping is free but only restores a small amount of <b>Stamina</b> and no <b>Health</b>.<br>"
                           "If you want to restore your <b>Health</b> at camp, you must have rations to eat.<br><br>"
                           "When traveling to an area, if you have an active quest, or enemies are rampant<br>"
                           "you will be able to start a battle by clicking the <b>Battle</b> button.<br>"
                           "Again, battles cost you <b>Stamina</b>. If you are out of <b>Stamina</b>, you can still fight<br>"
                           "but you will be at a disadvantage. You will only do 50% damage to enemies<br>"
                           "and have a much harder time dodging an enemies attack. So it is best to rest<br>"
                           "and not take on a fight when you are tired.<br><br>"
                           "The <b>Action</b> tab allows you to buy and use your potions and rations<br><br>"
                           "The <b>Character</b> tab shows you information about your character. This is also<br>"
                           "where you go when you level up to spread your skill points between stats<br><br>"
                           "Quests will give you rewards such gold, potions, rations and equipment as well<br>"
                           "as experience to level up your character. You must also complete quests if you<br>"
                           "wish to progress the story.<br>"
                           "Go to the <b>Quests</b> tab to start, abandon, or hand in quests.<br><br>"
                           "Speaking of quests, it looks like Bormier has a quest for you here in Windlehelm.<br>"
                           "Go to the <b>Quests</b> tab now to begin your first quest!<br><br>"
                           "Good luck out there!").arg(player_->getName()));
    msgBox.exec();
}

void GameLogic::on_btnAttack_clicked()
{
    //QSound::play("Sounds\\doHit.wav");
    message_ = "";
    int playerLevel = 0;
    int enemyLevel = 0;
    int levelDiff = 0;

   // if (player_->getLevel() >= 1 && player_->getLevel() <= 15)
   // {
        if (player_->isAlive())
        {
            if (player_->hasActiveDoT())
            {
                player_->doDotEffect();
                message_ += player_->getMessage();
            }
            bandit_->doHit(player_->doAttack(bandit_->getName()), player_->doHitRoll(), player_->getName(), player_->getWeaponDotType(), player_->getClassType());

            if (player_->getClassType() == 2 && player_->didRoguePassSecondAttackCheck())
            {
                bandit_->doHit(player_->doAttack(bandit_->getName()) / 2, player_->doHitRoll(), player_->getName(), player_->getWeaponDotType(), player_->getClassType());
            }

            if (bandit_->isHit())
            {
                player_->addSpecialAbilityCharge(1);
            }

            message_ += player_->getMessage() + bandit_->getMessage();

            if (player_->IsSpecialReady())
            {
                ui->btnSpecialAbility->setEnabled(true);
                bsSpecialSC_->setEnabled(true);
            }
        }

        if (bandit_->isAlive())
        {
            if (bandit_->hasActiveDoT())
            {
                bandit_->doDotEffect();
                message_ += bandit_->getMessage();
            }
            player_->doHit(bandit_->doAttack(player_->getName()), bandit_->doHitRoll(), bandit_->getName(), bandit_->isAlive(), bandit_->getWeaponDot());
            message_ += bandit_->getMessage() + player_->getMessage();
        }

        ui->txtBattleInfo->setText(message_);
        setPlayerHealth();
        setPlayerStamina();
        setEnemyHealth();

        if (!bandit_->isAlive())
        {
            message_ += player_->getName() + " Wins the battle!\n\n";
            ui->txtBattleInfo->setText(message_);
            bsAttackSC_->setEnabled(false);
            ui->btnUsePotionBS->setEnabled(true);
            ui->btnUseRationBS->setEnabled(true);
            ui->btnRestBS->setEnabled(true);
            setEnemyHealth();

            playerLevel = player_->getLevel();
            enemyLevel = bandit_->getLevel();

            if (playerLevel >= enemyLevel)
            {
                levelDiff = playerLevel - enemyLevel + 1;
                if (levelDiff == 1 || levelDiff == 2 || levelDiff == 3)
                    player_->addXP(bandit_->getXPReward() / levelDiff);
            }
            else if (playerLevel < enemyLevel)
            {
                player_->addXP(bandit_->getXPReward());
            }

            //player_->addXP(bandit_->getXPReward());
            if (quest_->getQuestType() == bandit_->getEnemyType())
            {
                if (bandit_->getObjType() == 1)
                    quest_->setAmountComplete(1);
                else if (bandit_->getObjType() == 2)
                    quest_->setAmountCompleteII(1);
            }

            player_->addGold(bandit_->goldDrop());
            player_->addItemsToInventory(lootDrops_->doLootDrop(bandit_->getName(), bandit_->getEnemyLoot(), bandit_->getItemDropChance()));
            setPlayerInventory();
            ui->lblGoldAmount->setText(QString("Gold: %1").arg(player_->getGold()));
            ui->lblGoldInv->setText(QString("Gold: %1").arg(player_->getGold()));

            player_->removeStamina(1);
            player_->checkXP();
            player_->resetSpecialAbility();
            checkSkillPoints();
            ui->tabStoreScreen->setEnabled(true);
            ui->tabCInfoScreen->setEnabled(true);
            ui->tabMenuScreen->setEnabled(true);
            ui->tabQuestScreen->setEnabled(true);

            ui->txtBattleInfo->setEnabled(false);
            ui->btnAttack->setEnabled(false);
            ui->btnSpecialAbility->setEnabled(false);
            ui->btnBattle->setEnabled(true);
            ui->btnTravel->setEnabled(true);
            setPlayerInfo();
            checkQuest();
            bsBattleSC_->setEnabled(true);
        }

    if (!player_->isAlive())
    {
        ui->tabStoreScreen->setEnabled(false);
        ui->tabCInfoScreen->setEnabled(false);
        ui->tabMenuScreen->setEnabled(true);
        ui->txtBattleInfo->setEnabled(false);
        ui->tabQuestScreen->setEnabled(false);
        ui->btnAttack->setEnabled(false);
        ui->btnSpecialAbility->setEnabled(false);
        ui->btnBattle->setEnabled(false);
        ui->btnTravel->setEnabled(false);
        ui->btnUsePotionBS->setEnabled(false);
        ui->btnUseRationBS->setEnabled(false);
        ui->btnRestBS->setEnabled(false);
        ui->btnSave->setEnabled(false);
        ui->btnUsePotionBS->setEnabled(false);
        setPlayerHealth();
        setPlayerStamina();
    }
}

void GameLogic::on_btnSpecialAbility_clicked()
{
    message_ = "";
    int playerLevel = 0;
    int enemyLevel = 0;
    int levelDiff = 0;

    if (player_->isAlive())
    {
        bandit_->doHit(player_->doSpecialAbility(bandit_->getName()), 20, player_->getName(), player_->getWeaponDotType(), player_->getClassType());
        message_ += player_->getMessage() + bandit_->getMessage();
    }

    if (bandit_->isAlive())
    {
        player_->doHit(bandit_->doAttack(player_->getName()), bandit_->doHitRoll(), bandit_->getName(), bandit_->isAlive(), bandit_->getWeaponDot());
        message_ += bandit_->getMessage() + player_->getMessage();
    }

    ui->txtBattleInfo->setText(message_);
    setEnemyHealth();
    setPlayerHealth();
    setPlayerStamina();

    if (!bandit_->isAlive())
    {
        message_ += player_->getName() + " Wins the battle!\n\n";
        ui->txtBattleInfo->setText(message_);
        setEnemyHealth();

        playerLevel = player_->getLevel();
        enemyLevel = bandit_->getLevel();

        if (playerLevel >= enemyLevel)
        {
            levelDiff = playerLevel - enemyLevel + 1;
            if (levelDiff == 1 || levelDiff == 2 || levelDiff == 3)
                player_->addXP(bandit_->getXPReward() / levelDiff);
        }
        else if (playerLevel < enemyLevel)
        {
            player_->addXP(bandit_->getXPReward());
        }

        //player_->addXP(bandit_->getXPReward());
        if (quest_->getQuestType() == bandit_->getEnemyType())
        {
            if (bandit_->getObjType() == 1)
                quest_->setAmountComplete(1);
            else if (bandit_->getObjType() == 2)
                quest_->setAmountCompleteII(1);
        }

        player_->addGold(bandit_->goldDrop());
        ui->lblGoldAmount->setText(QString("Gold: %1").arg(player_->getGold()));
        ui->lblGoldInv->setText(QString("Gold: %1").arg(player_->getGold()));

        player_->removeStamina(1);
        player_->checkXP();
        checkSkillPoints();
        ui->tabStoreScreen->setEnabled(true);
        ui->tabCInfoScreen->setEnabled(true);
        ui->tabMenuScreen->setEnabled(true);
        ui->tabQuestScreen->setEnabled(true);

        ui->txtBattleInfo->setEnabled(false);
        ui->btnAttack->setEnabled(false);
        ui->btnSpecialAbility->setEnabled(false);
        ui->btnBattle->setEnabled(true);
        ui->btnTravel->setEnabled(true);
        setPlayerInfo();
        checkQuest();
    }

    if (!player_->isAlive())
    {
        ui->tabStoreScreen->setEnabled(false);
        ui->tabCInfoScreen->setEnabled(false);
        ui->tabMenuScreen->setEnabled(true);
        ui->txtBattleInfo->setEnabled(false);
        ui->tabQuestScreen->setEnabled(false);
        ui->btnAttack->setEnabled(false);
        ui->btnSpecialAbility->setEnabled(false);
        ui->btnBattle->setEnabled(false);
        ui->btnTravel->setEnabled(false);
        ui->btnUsePotionBS->setEnabled(false);
        ui->btnUseRationBS->setEnabled(false);
        ui->btnRestBS->setEnabled(false);
        ui->btnSave->setEnabled(false);
        setPlayerHealth();
        setPlayerStamina();
    }

    player_->resetSpecialAbility();

    if (!player_->IsSpecialReady())
        ui->btnSpecialAbility->setEnabled(false);
}

void GameLogic::on_btnBattle_clicked()
{

    if (player_->isSpecialAbilityLeanred())
    {
        ui->btnAttack->setFixedHeight(21);
        ui->btnSpecialAbility->setVisible(true);
    }
    else
    {
        ui->btnAttack->setFixedHeight(41);
        ui->btnSpecialAbility->setVisible(false);
    }

    //ui->tabBattleScreen->setEnabled(true);
    ui->txtBattleInfo->setEnabled(true);
    ui->btnAttack->setEnabled(true);
    ui->btnBattle->setEnabled(false);
    ui->btnTravel->setEnabled(false);

    ui->tabMenuScreen->setEnabled(false);
    ui->tabStoreScreen->setEnabled(false);
    ui->tabCInfoScreen->setEnabled(false);
    ui->tabQuestScreen->setEnabled(false);
    checkLevel();

    if (bandit_->getEnemyType() == 20)
    {
        ui->txtBattleInfo->setText("You were attacked by Thragg!");
        //ui->lblQReward->setText(QString("Reward: %1 XP").arg(quest_->getXPReward()));
        ui->lblPLevel->setText(QString("%1").arg(player_->getLevel()));
        ui->lblELevel->setText(QString("%1").arg(bandit_->getLevel()));
        ui->lblEnemyName->setText(bandit_->getName());
        ui->btnUsePotionBS->setEnabled(true);
        ui->btnUseRationBS->setEnabled(false);
        ui->btnRestBS->setEnabled(false);
        setEnemyHealth();
    }
    else if (bandit_->getEnemyType() == 6)
    {
        ui->txtBattleInfo->setText(QString("You saved an %1").arg(bandit_->getName()));
        quest_->setAmountComplete(1);
        ui->tabStoreScreen->setEnabled(true);
        ui->tabCInfoScreen->setEnabled(true);
        ui->tabMenuScreen->setEnabled(true);
        ui->tabQuestScreen->setEnabled(true);
        bsAttackSC_->setEnabled(false);

        ui->txtBattleInfo->setEnabled(false);
        ui->btnAttack->setEnabled(false);
        ui->btnSpecialAbility->setEnabled(false);
        ui->btnBattle->setEnabled(true);
        ui->btnTravel->setEnabled(true);
        setPlayerInfo();
        checkQuest();
        bsBattleSC_->setEnabled(true);
    }
    else if (bandit_->getEnemyType() == 998)
    {
        ui->txtBattleInfo->setText(" ");
        ui->tabStoreScreen->setEnabled(true);
        ui->tabCInfoScreen->setEnabled(true);
        ui->tabMenuScreen->setEnabled(true);
        ui->tabQuestScreen->setEnabled(true);

        ui->txtBattleInfo->setEnabled(false);
        ui->btnAttack->setEnabled(false);
        ui->btnBattle->setEnabled(true);
        ui->btnTravel->setEnabled(true);
        ui->lblELevel->setText(" ");
        ui->lblEnemyName->setText(" ");
        ui->lblEHealth->setFixedWidth(0);
        ui->lblEHealthAmount->setText("0");
        ui->lblELevel->setText("0");
        ui->lblEnemyName->setText(" ");
    }
    else if (bandit_->getEnemyType() == 999)
    {
        ui->txtBattleInfo->setText(" ");
        ui->tabStoreScreen->setEnabled(true);
        ui->tabCInfoScreen->setEnabled(true);
        ui->tabMenuScreen->setEnabled(true);
        ui->tabQuestScreen->setEnabled(true);

        ui->txtBattleInfo->setEnabled(false);
        ui->btnAttack->setEnabled(false);
        ui->btnSpecialAbility->setEnabled(false);
        ui->btnBattle->setEnabled(true);
        ui->btnTravel->setEnabled(true);
        bsBattleSC_->setEnabled(true);
    }
    else
    {
        ui->txtBattleInfo->setText(QString("You were attacked by %1").arg(bandit_->getName()));
        //ui->lblQReward->setText(QString("Reward: %1 XP").arg(quest_->getXPReward()));
        ui->lblPLevel->setText(QString("%1").arg(player_->getLevel()));
        ui->lblELevel->setText(QString("%1").arg(bandit_->getLevel()));
        ui->lblEnemyName->setText(bandit_->getName());
        ui->btnUsePotionBS->setEnabled(false);
        ui->btnUseRationBS->setEnabled(false);
        ui->btnRestBS->setEnabled(false);
        setEnemyHealth();
    }
}

void GameLogic::on_btnTravel_clicked()
{
    if (player_->getStamina() >= 2)
    {
        message_ = "";
        QMessageBox msgBox;
        msgBox.setWindowTitle("Choose A Location to Travel to");
        msgBox.setText("Where would you like to travel?");
        QPushButton *btnWindlehelm = msgBox.addButton(tr("Windlehelm"), QMessageBox::ActionRole);
        QPushButton *btnBanditBarracks = msgBox.addButton(tr("Bandit Barracks"), QMessageBox::ActionRole);
        QPushButton *btnDeepwoodForest = msgBox.addButton(tr("Deepwood Forest"), QMessageBox::ActionRole);
        QPushButton *btnRiverbane = msgBox.addButton(tr("Riverbane"), QMessageBox::ActionRole);
        QPushButton *btnRiverbaneMine = msgBox.addButton(tr("Riverbane Mine"), QMessageBox::ActionRole);
        QPushButton *btnAndorjaul = msgBox.addButton(tr("Andorjaul"), QMessageBox::ActionRole);
        QPushButton *btnCancel = msgBox.addButton(QMessageBox::Cancel);
        msgBox.exec();

        //message_ += QString("Location: %1\n\n").arg(strLocations_[location_]);
        if (msgBox.clickedButton() == btnWindlehelm)
        {
            location_ = windlehelm;
        }
        else if (msgBox.clickedButton() == btnBanditBarracks)
        {
            if (quest_->getQuestType() == 0)
            {
                location_ = banditBarracks;
            }
            else if (quest_->getQuestType() >= 4)
            {
                location_ = locations_(player_->getLocation());
            }
            else
            {
                location_ = banditBarracks;
            }
        }
        else if (msgBox.clickedButton() == btnDeepwoodForest)
        {
            if (quest_->getQuestType() < 3)
            {
                location_ = deepwoodForest;
            }
            else
            {
                location_ = deepwoodForest;
            }
        }
        else if (msgBox.clickedButton() == btnRiverbane)
        {
            if (quest_->getQuestType() < 4 )
            {
                location_ = riverbane;
            }
            else if (quest_->getQuestType() > 4)
            {
                location_ = riverbane;
            }
            else
            {
                location_ = riverbane;
            }
        }
        else if (msgBox.clickedButton() == btnRiverbaneMine)
        {
            if (quest_->getQuestType() < 7 )
            {
                location_ = riverbaneMine;
            }
            else if (quest_->getQuestType() > 7 || player_->getQuestsCompleted() == 7)
            {
                location_ = riverbaneMine;
            }
            else
            {
                location_ = riverbaneMine;
            }
        }
        else if (msgBox.clickedButton() == btnAndorjaul)
        {
            if (quest_->getQuestType() < 6)
            {
                location_ = andorjaul;
            }
            else
            {
                location_ = andorjaul;
            }
        }
        else if (msgBox.clickedButton() == btnCancel)
        {
            //player's location doesn't change
        }
        else
        {
            //player's location doesn't change
        }

        if (player_->getLocation() != location_ && player_->getStamina() > 1)
        {
            player_->removeStamina(0);
            switch(location_)
            {
                case windlehelm :
                    player_->setLocation(0);
                    break;
                case banditBarracks :
                    player_->setLocation(1);
                    break;
                case deepwoodForest :
                    player_->setLocation(2);
                    break;
                case riverbane :
                    player_->setLocation(3);
                    break;
                case riverbaneMine :
                    player_->setLocation(4);
                    break;
                case andorjaul :
                    player_->setLocation(5);
                    break;
            }
            checkLocation();
        }
        else if (player_->getLocation() == location_)
        {
            message_ = QString("You are already in %1").arg(strLocations_[location_]);
        }
    }
    else if (player_->getStamina() < 2)
    {
        message_ = QString("You are too tired to travel. "
                           "Eat some rations to get some energy "
                           "or rest for the night and travel in the morning.");
    }

    ui->txtBattleInfo->setText(message_);
    ui->txtBattleInfo->setEnabled(true);
    setPlayerStamina();
}

void GameLogic::checkLevel()
{

    if (location_ == banditBarracks)
    {
        if (quest_->getQuestType() == 0)
        {
            bandit_ = new Bandit("banditName", 0, 0, 0, 0, 0, 0, 999, 0, 0, 0, 0, 0);
        }
        else if (quest_->getQuestType() >= 4)
        {
            bandit_ = new Bandit("banditName", 0, 0, 0, 0, 0, 0, 999, 0, 0, 0, 0, 0);
        }
        else
        {
            bsAttackSC_->setEnabled(true);
            bsBattleSC_->setEnabled(false);
            QString banditName = "Bandit Initiate";
            int banditHealth = 0;
            int banditMaxAttackPower = 0;
            int banditMinAttackPower = 0;
            int banditCritChance = 0;
            int banditXPReward = 0;
            //int banditLevel = (rand() % 3 + 1);
            int banditLevel = 1;
            // attackDmg_ = rand() % ((maxAttackPower_ + 1) - minAttackPower_) + minAttackPower_;
            int trainerChance = rand() % ((100 + 1) - 1) + 1;
            int banditType = 0;
            int banditAgility = 3;
            int objType = 1;
            int banditDropChance = 90;
            int weaponDot;
            int armourType = 2;

            if (quest_->getQuestType() == 2 && quest_->getIsQuestActive() == 1 && trainerChance >= 75)
            {
                banditName = "Bandit Trainer";
                banditHealth = 12;
                enemyMaxHP_ = 12;
                banditMaxAttackPower = 5;
                banditMinAttackPower = 1;
                banditCritChance = 20;
                banditXPReward = 12;
                banditType = 2;
                banditLevel = 2;
                banditAgility = 5;
                weaponDot = rand()% 2 + 1;

            }
            else
            {
                banditHealth = rand() % ((9 + 1) - 5) + 5;
                enemyMaxHP_ = banditHealth;
                banditMaxAttackPower = 2;
                banditMinAttackPower = 1;
                banditCritChance = 20;
                banditXPReward = 6;
                banditType = 1;
                weaponDot = 1;
            }

            bandit_ = new Bandit(banditName, banditHealth, banditMaxAttackPower, banditMinAttackPower,
                                 banditCritChance, banditXPReward, banditLevel, banditType, banditAgility, objType, banditDropChance, weaponDot, armourType);
            lootDrops_->setLoot(bandit_->getEnemyType(), bandit_->getName());
            bandit_->addLoot(lootDrops_->getDefaultLoot(),lootDrops_->getEnemySpecificLoot());
        }
    }
    else if (location_ == deepwoodForest)
    {
        if (player_->getQuestsCompleted() < 2)
        {
            bandit_ = new Bandit("banditName", 0, 0, 0, 0, 0, 0, 999, 0, 0, 0, 0, 0);
        }
        else
        {
            bsAttackSC_->setEnabled(true);
            bsBattleSC_->setEnabled(false);
            QString banditName = "Bandit Initiate";
            int banditHealth = 0;
            int banditMaxAttackPower = 0;
            int banditMinAttackPower = 0;
            int banditCritChance = 0;
            int banditXPReward = 0;
            //int banditLevel = (rand() % 3 + 1);
            int banditLevel = 1;
            // attackDmg_ = rand() % ((maxAttackPower_ + 1) - minAttackPower_) + minAttackPower_;
            int trainerChance = rand() % ((100 + 1) - 1) + 1;
            int banditType = 0;
            int banditAgility = 3;
            int objType = 1;
            int banditDropChance = 90;
            int weaponDot;
            int armourType = 2;

            if (quest_->getQuestType() == 3 && quest_->getIsQuestActive() == 1 && trainerChance >= 85)
            {
                banditName = "Trainer Gren";
                banditHealth = 15;
                enemyMaxHP_ = 15;
                banditMaxAttackPower = 6;
                banditMinAttackPower = 2;
                banditCritChance = 19;
                banditXPReward = 24;
                banditType = 3;
                banditLevel = 2;
                banditAgility = 6;
                weaponDot = rand()% 3 + 1;
            }
            else if (quest_->getQuestType() == 5 && quest_->getIsQuestActive() == 1)
            {
                banditName = "Initiate Ambusher";
                banditHealth = rand() % ((9 + 1) - 5) + 5;
                enemyMaxHP_ = banditHealth;
                banditMaxAttackPower = 3;
                banditMinAttackPower = 1;
                banditCritChance = 20;
                banditXPReward = 6;
                banditType = 5;
                weaponDot = 3;
            }
            else
            {
                banditHealth = rand() % ((9 + 1) - 5) + 5;
                enemyMaxHP_ = banditHealth;
                banditMaxAttackPower = 2;
                banditMinAttackPower = 1;
                banditCritChance = 20;
                banditXPReward = 6;
                banditType = 1;
                weaponDot = 1;
            }

            bandit_ = new Bandit(banditName, banditHealth, banditMaxAttackPower, banditMinAttackPower,
                                 banditCritChance, banditXPReward, banditLevel, banditType, banditAgility, objType, banditDropChance, weaponDot, armourType);
            lootDrops_->setLoot(bandit_->getEnemyType(), bandit_->getName());
            bandit_->addLoot(lootDrops_->getDefaultLoot(),lootDrops_->getEnemySpecificLoot());
        }
    }
    else if (location_ == riverbane)
    {
        if (quest_->getQuestType() < 4 )
        {
            bandit_ = new Bandit("banditName", 0, 0, 0, 0, 0, 0, 999, 0, 0, 0, 0, 0);
        }
        else if (quest_->getQuestType() > 4)
        {
            bandit_ = new Bandit("banditName", 0, 0, 0, 0, 0, 0, 999, 0, 0, 0, 0, 0);
        }
        else
        {
            bsAttackSC_->setEnabled(true);
            bsBattleSC_->setEnabled(false);
            //QString banditName = "Bandit Thug";
            QString banditName = "Bandit Raider";
            int banditHealth = 0;
            int banditMaxAttackPower = 0;
            int banditMinAttackPower = 0;
            int banditCritChance = 0;
            int banditXPReward = 0;
            // attackDmg_ = rand() % ((maxAttackPower_ + 1) - minAttackPower_) + minAttackPower_;
            int banditLevel = 2; //(rand() % ((6 + 1) - 4) + 4);
            int banditType = 4;
            int banditAgility = 4;
            int objType = 1;
            int banditDropChance = 90;
            int weaponDot = rand()% 2 + 1;
            int armourType = 2;

            banditHealth = rand() % ((12 + 1) - 9) + 9;
            enemyMaxHP_ = banditHealth;
            banditMaxAttackPower = 3;
            banditMinAttackPower = 1;
            banditCritChance = 20;
            banditXPReward = 12;

            bandit_ = new Bandit(banditName, banditHealth, banditMaxAttackPower, banditMinAttackPower,
                                 banditCritChance, banditXPReward, banditLevel, banditType, banditAgility, objType, banditDropChance, weaponDot, armourType);
            lootDrops_->setLoot(bandit_->getEnemyType(), bandit_->getName());
            bandit_->addLoot(lootDrops_->getDefaultLoot(),lootDrops_->getEnemySpecificLoot());
        }
    }
    else if (location_ == riverbaneMine)
    {
        if (quest_->getQuestType() < 7 )
        {
            bandit_ = new Bandit("banditName", 0, 0, 0, 0, 0, 0, 999, 0, 0, 0, 0, 0);
        }
        else if (quest_->getQuestType() > 7 || player_->getQuestsCompleted() == 7 ||
                 (quest_->getQuestType() == 7 && quest_->getAmountCompleteII() == quest_->getObjectiveII()))
        {
            bandit_ = new Bandit("banditName", 0, 0, 0, 0, 0, 0, 999, 0, 0, 0, 0, 0);
        }
        else
        {
            bsAttackSC_->setEnabled(true);
            bsBattleSC_->setEnabled(false);
            //QString banditName = "Bandit Thug";
            QString banditName = "Kobold Invader";
            int banditHealth = 0;
            int banditMaxAttackPower = 0;
            int banditMinAttackPower = 0;
            int banditCritChance = 0;
            int banditXPReward = 0;
            // attackDmg_ = rand() % ((maxAttackPower_ + 1) - minAttackPower_) + minAttackPower_;
            int banditLevel = 2; //(rand() % ((6 + 1) - 4) + 4);
            int banditType = 7;
            int banditAgility = 4;
            int objType = 1;
            int banditDropChance = 90;
            int weaponDot = rand()% 2 + 1;
            int armourType = 2;

            if (quest_->getAmountComplete() == quest_->getObjective())
            {
                banditName = "Menzid";
                banditHealth = 20;
                enemyMaxHP_ = 20;
                //banditType = 8;
                banditMaxAttackPower = 6;
                banditMinAttackPower = 1;
                banditCritChance = 18;
                banditXPReward = 24;
                banditLevel = 3;
                banditAgility = 4;
                objType = 2;
            }
            else
            {
                banditHealth = rand() % ((12 + 1) - 9) + 9;
                enemyMaxHP_ = banditHealth;
                banditMaxAttackPower = 4;
                banditMinAttackPower = 1;
                banditCritChance = 20;
                banditXPReward = 12;
            }

            bandit_ = new Bandit(banditName, banditHealth, banditMaxAttackPower, banditMinAttackPower,
                                 banditCritChance, banditXPReward, banditLevel, banditType, banditAgility, objType, banditDropChance, weaponDot, armourType);
            lootDrops_->setLoot(bandit_->getEnemyType(), bandit_->getName());
            bandit_->addLoot(lootDrops_->getDefaultLoot(),lootDrops_->getEnemySpecificLoot());
        }
    }
    else if (location_ == andorjaul)
    {
        if (quest_->getQuestType() < 6 && player_->getQuestsCompleted() < 7)
        {
            bandit_ = new Bandit("banditName", 0, 0, 0, 0, 0, 0, 999, 0, 0, 0, 0, 0);
        }
        else
        {
            bsAttackSC_->setEnabled(true);
            bsBattleSC_->setEnabled(false);
            //QString banditName = "Bandit Thug";
            QString banditName = "Bandit Raider";
            int banditHealth = 0;
            int banditMaxAttackPower = 0;
            int banditMinAttackPower = 0;
            int banditCritChance = 0;
            int banditXPReward = 0;
            // attackDmg_ = rand() % ((maxAttackPower_ + 1) - minAttackPower_) + minAttackPower_;
            int banditLevel = 2; //(rand() % ((6 + 1) - 4) + 4);
            int banditType = 4;
            int banditAgility = 5;
            int objType = 1;
            int banditDropChance = 75;
            int andorjaulSettlerChance = rand() % ((100 + 1) - 1) + 1;
            int weaponDot = rand()% 2 + 1;
            int armourType = 2;

            if (quest_->getQuestType() == 6  && quest_->getIsQuestActive() == 1 && andorjaulSettlerChance >= 60)
            {
                banditName = "Andorjaul Settler";
                banditHealth = 2;
                enemyMaxHP_ = banditHealth;
                banditMaxAttackPower = 1;
                banditMinAttackPower = 1;
                banditCritChance = 20;
                banditXPReward = 0;
                banditType = 6;
                banditAgility = 0;
            }
            else
            {
                banditHealth = rand() % ((12 + 1) - 9) + 9;
                enemyMaxHP_ = banditHealth;
                banditMaxAttackPower = 3;
                banditMinAttackPower = 1;
                banditCritChance = 20;
                banditXPReward = 12;
            }

            bandit_ = new Bandit(banditName, banditHealth, banditMaxAttackPower, banditMinAttackPower,
                                 banditCritChance, banditXPReward, banditLevel, banditType, banditAgility, objType, banditDropChance, weaponDot, armourType);
            lootDrops_->setLoot(bandit_->getEnemyType(), bandit_->getName());
            bandit_->addLoot(lootDrops_->getDefaultLoot(),lootDrops_->getEnemySpecificLoot());
        }
    }
    else
    {
        bandit_ = new Bandit("banditName", 0, 0, 0, 0, 0, 0, 998, 0, 0, 0, 0, 0);
    }
}

void GameLogic::createCharacter()
{
    QString classRogue = "Rogue";
    QString classWarrior = "Warrior";
    QString classKnight = "Knight";



    QMessageBox msgBox;
    msgBox.setWindowTitle("Choose a class");
    msgBox.setText("Which class would you like to make?");
    QPushButton *btnRogue = msgBox.addButton(classRogue, QMessageBox::ActionRole);
    QPushButton *btnWarrior = msgBox.addButton(classWarrior, QMessageBox::ActionRole);
    QPushButton *btnKnight = msgBox.addButton(classKnight, QMessageBox::ActionRole);
    msgBox.exec();

    if (msgBox.clickedButton() == btnRogue)
    {
        //defaultHealth, intelligence, defaultStamina, agilityDefault, luckDefault, classType
        player_ = new Player(16, 0, 10, 7, 20, 2);
    }
    else if (msgBox.clickedButton() == btnWarrior)
    {
        //defaultHealth, intelligence, defaultStamina, agilityDefault, luckDefault, classType
        player_ = new Player(20, 0, 10, 6, 20, 3);
    }
    else if (msgBox.clickedButton() == btnKnight)
    {
        //defaultHealth, intelligence, defaultStamina, agilityDefault, luckDefault, classType
        player_ = new Player(26, 0, 10, 5, 20, 4);
    }

    bool ok;
    name_ = QInputDialog::getText(this, tr("New Game"), tr("<p>Greetings traveler, welcome to <b>Windlehelm</b>.<br>"
                                                           "I am <b>Bormeir</b>, head of the <b>Windlehelm City Guard</b>.<br>"
                                                           "What might I call you?<br><br>"
                                                           "Enter a character name:</p>"), QLineEdit::Normal, "", &ok);

    if(ok)
    {
        player_->setName(name_);
        player_->addStarterEquipment();
        player_->setStrength();
        setPlayerInfo();
        setPlayerEquipment();
        QMessageBox msgBox;
        msgBox.setWindowTitle("Bormeir");
        msgBox.setText(QString("Good to meet you %1.\n"
                               "You look to be a capable fighter.\n"
                               "would you be so kind as to help out Windlehelm City?").arg(player_->getName()));
        QPushButton *btnYes = msgBox.addButton(tr("Yes"), QMessageBox::ActionRole);
        QPushButton *btnNo = msgBox.addButton(tr("No"), QMessageBox::ActionRole);
        msgBox.exec();

        if (msgBox.clickedButton() == btnYes)
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Bormeir");
            msgBox.setText(QString("Thank you, %1. \nPlease meet me in the my barracks when you are ready.").arg(player_->getName()));
            msgBox.exec();
        }
        else if (msgBox.clickedButton() == btnNo)
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Bormeir");
            msgBox.setText(QString("I See. \nWell if you have a change of heart, \nI'll be in my barracks if you wish to talk.").arg(player_->getName()));
            msgBox.exec();
        }
    }
}

void GameLogic::on_btnSave_clicked()
{
    QString playerName = " ";
    int maxSaves = 3;
    QDir directory("saves");
    QStringList saves = directory.entryList(QStringList() << "Save*.save",QDir::Files);

    if (saves.size() == 0)
    {
        player_->save();
        quest_->save(player_->getName());
        QMessageBox msgBox;
        msgBox.setWindowTitle("Save Game");
        msgBox.setText("      Game Saved.            ");
        msgBox.exec();
    }
    else
    {
        foreach (QString fileName, saves)
        {
            QFile file("saves\\" + fileName);
            file.open(QIODevice::ReadOnly| QIODevice::Text);
            QTextStream saveFile(&file);
            playerName += saveFile.readLine();
        }

        if (playerName.contains(player_->getName()))
        {
            player_->save();
            quest_->save(player_->getName());
            QMessageBox msgBox;
            msgBox.setWindowTitle("Save Game");
            msgBox.setText("      Game Saved.            ");
            msgBox.exec();
        }
        else if (!playerName.contains(player_->getName()) && saves.size() != maxSaves)
        {
            player_->save();
            quest_->save(player_->getName());
            QMessageBox msgBox;
            msgBox.setWindowTitle("Save Game");
            msgBox.setText("      Game Saved.            ");
            msgBox.exec();
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Saves Full");
            msgBox.setText("You cannot save more than 3 games");
            msgBox.exec();
        }
    }

}

void GameLogic::on_btnLoad_clicked()
{
    QString playerName = "";
    QString save1BtnName = "Save 1";
    QString save2BtnName = "Save 2";
    QString save3BtnName = "Save 3";

    QDir directory("saves");
    QStringList saves = directory.entryList(QStringList() << "Save*.save",QDir::Files);
    if (saves.size() > 0)
    {
        if (saves.size() == 1)
        {
            QString fileName = saves.at(0);
            QFile file("saves\\" + fileName);
            file.open(QIODevice::ReadOnly| QIODevice::Text);
            QTextStream saveFile(&file);
            save1BtnName = saveFile.readLine();
        }
        else if (saves.size() == 2)
        {
            QString fileName = saves.at(0);
            QFile file("saves\\" + fileName);
            file.open(QIODevice::ReadOnly| QIODevice::Text);
            QTextStream saveFile(&file);
            save1BtnName = saveFile.readLine();

            QString fileName2 = saves.at(1);
            QFile file2("saves\\" + fileName2);
            file2.open(QIODevice::ReadOnly| QIODevice::Text);
            QTextStream saveFile2(&file2);
            save2BtnName = saveFile2.readLine();
        }
        else if (saves.size() == 3)
        {
            QString fileName = saves.at(0);
            QFile file("saves\\" + fileName);
            file.open(QIODevice::ReadOnly| QIODevice::Text);
            QTextStream saveFile(&file);
            save1BtnName = saveFile.readLine();

            QString fileName2 = saves.at(1);
            QFile file2("saves\\" + fileName2);
            file2.open(QIODevice::ReadOnly| QIODevice::Text);
            QTextStream saveFile2(&file2);
            save2BtnName = saveFile2.readLine();

            QString fileName3 = saves.at(2);
            QFile file3("saves\\" + fileName3);
            file3.open(QIODevice::ReadOnly| QIODevice::Text);
            QTextStream saveFile3(&file3);
            save3BtnName = saveFile3.readLine();
        }

        QMessageBox msgBox;
        msgBox.setWindowTitle("Load A Game");
        msgBox.setText("Which game do you want to load?");
        QPushButton *btnSave1 = msgBox.addButton(save1BtnName, QMessageBox::ActionRole);
        QPushButton *btnSave2 = msgBox.addButton(save2BtnName, QMessageBox::ActionRole);
        QPushButton *btnSave3 = msgBox.addButton(save3BtnName, QMessageBox::ActionRole);
        msgBox.exec();

        if (msgBox.clickedButton() == btnSave1)
        {
            playerName = save1BtnName;
        }
        else if (msgBox.clickedButton() == btnSave2)
        {
            playerName = save2BtnName;
        }
        else if (msgBox.clickedButton() == btnSave3)
        {
            playerName = save3BtnName;
        }

        if (!playerName.contains("Save"))
        {
            player_->load(playerName);
            quest_->load(player_->getName());
            ui->btnSave->setEnabled(true);
            ui->tabStoreScreen->setEnabled(true);
            ui->tabCInfoScreen->setEnabled(true);
            ui->tabQuestScreen->setEnabled(true);
            ui->btnBattle->setEnabled(true);
            ui->btnTravel->setEnabled(true);
            msSaveGameSC_->setEnabled(true);
            ui->btnUsePotionBS->setEnabled(true);
            ui->btnUseRationBS->setEnabled(true);
            ui->btnRestBS->setEnabled(true);
            ui->lblEHealth->setFixedWidth(0);
            ui->lblEHealthAmount->setText("0");
            ui->lblELevel->setText("0");
            ui->lblEnemyName->setText(" ");
            ui->txtBattleInfo->setText(" ");

            if ((quest_->getIsQuestActive() == 1 && quest_->getIsQuestComplete() == 0) ||
                (quest_->getIsQuestActive() == 0 && quest_->getIsQuestComplete() == 0))
            {
                ui->btnCompleteQuest->setEnabled(true);
                ui->btnAbandonQuest->setEnabled(true);
                ui->btnBeginQuest->setEnabled(false);

                ui->lblQTitle->setText(quest_->getQuestTitle());
                ui->lblQProgress->setText(quest_->getObjectiveProgress());
                ui->lblQReward->setText(QString("Reward: %1 XP").arg(quest_->getXPReward()));
            }
            else
            {
                ui->btnCompleteQuest->setEnabled(false);
                ui->btnAbandonQuest->setEnabled(false);
                ui->btnBeginQuest->setEnabled(true);

                ui->lblQTitle->setText("Quest Title");
                ui->lblQProgress->setText("Progess:");
                ui->lblQReward->setText("Reward:");
            }

            setPlayerInfo();
            setPlayerInventory();
            setPlayerEquipment();
            checkSkillPoints();
            checkLocation();
            ui->lblGoldAmount->setText(QString("Gold: %1").arg(player_->getGold()));
            ui->lblGoldInv->setText(QString("Gold: %1").arg(player_->getGold()));
            //ui->txtBattleInfo->setText("");
            ui->lblEHealth->setFixedWidth(0);
            ui->lblEHealthAmount->setText("0");

            if (player_->isSpecialAbilityLeanred())
            {
                ui->btnAttack->setFixedHeight(21);
                ui->btnSpecialAbility->setVisible(true);
            }
            else
            {
                ui->btnAttack->setFixedHeight(41);
                ui->btnSpecialAbility->setVisible(false);
            }

            QMessageBox msgBox2;
            msgBox2.setWindowTitle("Load Game");
            msgBox2.setText("      Game Loaded.            ");
            msgBox2.exec();

        }
    }
}

void GameLogic::on_btnBuyPotion_clicked()
{
    if (player_->getGold() >= 50)
    {
        if (strRestLocation_[player_->getLocation()] == "City" || strRestLocation_[player_->getLocation()] == "Town")
        {
            Item item;
            //numItems.push_back(banditItemDrops_[e][0]);

            item.name = "Potion";
            item.itemRarity = 0;
            item.itemType = 1;
            item.armourRating = 0;
            item.armourType = 0;
            item.healType = 1;
            item.healAmount = 5;
            item.isEquippable = false;
            item.sellPrice = 10;
            item.isUsable = true;
            item.minAtk = 0;
            item.maxAtk = 0;
            item.block = 0;
            item.holdType = 0;
            item.stat1 = 0;
            item.stat2 = 0;
            item.stat3 = 0;
            item.statType1 = 0;
            item.statType2 = 0;
            item.statType3 = 0;
            item.amount = 1;
            item.numStats = 0;

            QSound::play("Sounds\\potionDrop.wav");
            player_->removeGold(50);
            player_->addItemToInventory(item);
            ui->lblGoldAmount->setText(QString("Gold: %1").arg(player_->getGold()));
            ui->lblGoldInv->setText(QString("Gold: %1").arg(player_->getGold()));
            setPlayerInfo();
            setPlayerInventory();
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Buy Item");
            msgBox.setText("You need to be in a City<br>or Town to buy items.");
            msgBox.exec();
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Buy Item");
        msgBox.setText("You do not have enough gold for this item.");
        msgBox.exec();
    }
}

void GameLogic::on_btnBuyRation_clicked()
{
    if (player_->getGold() >= 30)
    {
        if (strRestLocation_[player_->getLocation()] == "City" || strRestLocation_[player_->getLocation()] == "Town")
        {
            Item item;
            //numItems.push_back(banditItemDrops_[e][0]);

            item.name = "Ration";
            item.itemRarity = 0;
            item.itemType = 1;
            item.armourRating = 0;
            item.armourType = 0;
            item.healType = 2;
            item.healAmount = 5;
            item.isEquippable = false;
            item.sellPrice = 10;
            item.isUsable = true;
            item.minAtk = 0;
            item.maxAtk = 0;
            item.block = 0;
            item.holdType = 0;
            item.stat1 = 0;
            item.stat2 = 0;
            item.stat3 = 0;
            item.statType1 = 0;
            item.statType2 = 0;
            item.statType3 = 0;
            item.amount = 1;
            item.numStats = 0;

            QSound::play("Sounds\\rationDrop.wav");
            player_->removeGold(30);
            player_->addItemToInventory(item);
            ui->lblGoldAmount->setText(QString("Gold: %1").arg(player_->getGold()));
            ui->lblGoldInv->setText(QString("Gold: %1").arg(player_->getGold()));
            setPlayerInfo();
            setPlayerInventory();
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Buy Item");
            msgBox.setText("You need to be in a City<br>or Town to buy items.");
            msgBox.exec();
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Buy Item");
        msgBox.setText("You do not have enough gold for this item.");
        msgBox.exec();
    }
}

void GameLogic::setPlayerInfo()
{
    ui->lblCName->setText(QString("Name: %1").arg(player_->getName()));
    ui->lblCHealth->setText(QString("Health: %1/%2").arg(player_->getHealth()).arg(player_->getMaxHealth()));
    ui->lblCAttack->setText(QString("Attack: %1-%2").arg(player_->getMinAttackPower()).arg(player_->getMaxAttackPower()));
    ui->lblCLevel->setText(QString("Level: %1").arg(player_->getLevel()));
    ui->lblCXP->setText(QString("Experience: %1/%2").arg(player_->getXP()).arg(player_->getXPTillLevel()));
    ui->lblCXPTillLvl->setText(QString("XP till next level: %1").arg(player_->getXPTillLevel() - player_->getXP()));
    ui->lblCSkillPoints->setText(QString("Skill Points: %1").arg(player_->getSkillPoints()));
    ui->lblGoldAmount->setText(QString("Gold: %1").arg(player_->getGold()));
    ui->lblGoldInv->setText(QString("Gold: %1").arg(player_->getGold()));
    ui->lblPLevel->setText(QString("%1").arg(player_->getLevel()));
    ui->lblCStrength->setText(QString("Strength: %1").arg(player_->getTotalStrengthPoints()));
    ui->lblCStamina->setText(QString("Stamina: %1").arg(player_->getTotalStaminaPoints()));
    ui->lblCAgility->setText(QString("Agility: %1").arg(player_->getTotalAgilityPoints()));
    ui->lblCAgilScore->setText(QString("Score: %1").arg(player_->getAgility()));
    ui->lblCLuck->setText(QString("Luck: %1").arg(player_->getTotalLuckPoints()));
    ui->lblCLuckScore->setText(QString("Crit Chance: %1%").arg(QString::number(player_->getCritChance(), 'f', 2).remove(0,2)));
    ui->lblCVitality->setText(QString("Vitality: %1").arg(player_->getTotalVitalityPoints()));
    ui->lblCHit->setText(QString("Precision: %1").arg(player_->getTotalPrecisionPoints()));
    ui->lblCHitScore->setText(QString("Score: +%1").arg(player_->getPrecision()));
    ui->lblCBlock->setText(QString("Block: %1").arg(player_->getBlock()));
    double xpPercent = (double(player_->getXP()) / double(player_->getXPTillLevel())) * 100;
    double xpPercent2 = (double(player_->getXP()) / double(player_->getXPTillLevel())) * 400;
    ui->lblXpPercent->setText(QString("%1%").arg(int(xpPercent)));
    ui->lblXpBar->setFixedWidth(int(xpPercent2));
    setPlayerHealth();
    setPlayerStamina();
    location_ = locations_(player_->getLocation());
}

void GameLogic::setPlayerHealth()
{
    int playerHPPercent = int((double(player_->getHealth()) / double(player_->getMaxHealth())) * 100);
    double playerHP = (double(player_->getHealth()) / double(player_->getMaxHealth())) * 125;
    ui->lblPHealth->setFixedWidth(int(playerHP));
    ui->lblPHealthAmount->setText(QString("%1").arg(player_->getHealth()));

    if (playerHPPercent >= 51)
    {
        ui->lblPHealth->setStyleSheet("background-color: rgb(0, 255, 0)");
    }
    else if (playerHPPercent >= 26 && playerHPPercent <= 50)
    {
        ui->lblPHealth->setStyleSheet("background-color: rgb(255, 255, 0)");
    }
    else
    {
        ui->lblPHealth->setStyleSheet("background-color: rgb(255, 0, 0)");
    }

    if (player_->getHealth() < 0)
    {
        ui->lblPHealthAmount->setText("0");
        ui->lblPHealth->setFixedWidth(0);
    }
}

void GameLogic::setPlayerStamina()
{
    double playerStam = (double(player_->getStamina()) / double(player_->getMaxStamina())) * 125;
    ui->lblPStamina->setFixedWidth(int(playerStam));
    ui->lblPStaminaAmount->setText(QString("%1").arg(player_->getStamina()));

    if (player_->getStamina() < 0)
    {
        ui->lblPStaminaAmount->setText("0");
        ui->lblPStamina->setFixedWidth(0);
    }
}

void GameLogic::setEnemyHealth()
{
    double enemyHPPercent = (double(bandit_->getHealth()) / double(enemyMaxHP_)) * 100;
    double enemyHP = (double(bandit_->getHealth()) / double(enemyMaxHP_)) * 125;
    ui->lblEHealth->setFixedWidth(int(enemyHP));
    ui->lblEHealthAmount->setText(QString("%1").arg(bandit_->getHealth()));

    if (enemyHPPercent >= 51)
    {
        ui->lblEHealth->setStyleSheet("background-color: rgb(0, 255, 0)");
    }
    else if (enemyHPPercent >= 26 && enemyHPPercent <= 50)
    {
        ui->lblEHealth->setStyleSheet("background-color: rgb(255, 255, 0)");
    }
    else
    {
        ui->lblEHealth->setStyleSheet("background-color: rgb(255, 0, 0)");
    }

    if (bandit_->getHealth() < 0)
    {
        ui->lblEHealthAmount->setText("0");
        ui->lblEHealth->setFixedWidth(0);
    }
}

void GameLogic::resetQuestInfo()
{
    //xpReward, objective, amountComplete, isQuestComplete, isQuestActive, questType
    quest_ = new quests(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "");
    ui->lblQTitle->setText("No Active Quest");
    ui->lblQProgress->setText("Progess:");
    ui->lblQReward->setText("Reward:");
    ui->btnBeginQuest->setEnabled(true);
    ui->btnCompleteQuest->setEnabled(false);
    ui->btnAbandonQuest->setEnabled(false);
}

void GameLogic::closeBag()
{
    isBagOpen_ = false;
}

void GameLogic::equipItem()
{
    ui->lstEquipment->clear();

    int itemIndex;
    QString itemName;
    QVector<Item> inventoryItems;

    inventoryItems = player_->getInventory();
    itemName = ui->lstInventory->currentItem()->text();

    for (int x = 0; x < inventoryItems.length(); x++)
    {
        if (itemName == inventoryItems.value(x).name)
        {
            itemIndex = x;
        }
    }

    player_->addEquipment(inventoryItems.value(itemIndex));

    if (player_->itemEquipped())
        player_->removeItemFromInventory(itemIndex);

    setPlayerEquipment();
}

void GameLogic::unequipItem()
{
    int itemIndex;
    QString itemName;
    QVector<Item> equipedItems;
    QVector<Item> removedItem;

    equipedItems = player_->getEquiped();
    itemName = ui->lstEquipment->currentItem()->text();

    for (int x = 0; x < equipedItems.length(); x++)
    {
        if (itemName == equipedItems.value(x).name)
        {
            itemIndex = x;
        }
    }

    removedItem.push_back(player_->getEquiped().value(itemIndex));
    player_->removeEquipment(itemIndex);
    player_->addItemsToInventory(removedItem);
    setPlayerInfo();
    setPlayerInventory();
    setPlayerEquipment();
}

void GameLogic::useItem()
{
    int itemIndex;
    QVector<Item> inventoryItems;
    QString item = ui->lstInventory->currentItem()->text();

    inventoryItems = player_->getInventory();

    for (int a = 0; a < inventoryItems.length(); a++)
    {
        if (item == inventoryItems.value(a).name)
        {
            itemIndex = a;
        }
    }

    if (inventoryItems.value(itemIndex).itemType == 1)
    {
        if (inventoryItems.value(itemIndex).healType == 1)
        {
            player_->usePotion(inventoryItems.value(itemIndex).healAmount, itemIndex);
            setPlayerInfo();
            setPlayerInventory();
        }
        else if (inventoryItems.value(itemIndex).healType == 2)
        {
            player_->useRation(inventoryItems.value(itemIndex).healAmount, itemIndex);
            setPlayerInfo();
            setPlayerInventory();
        }
    }
}

void GameLogic::sellItem()
{
    if (strRestLocation_[player_->getLocation()] == "City" || strRestLocation_[player_->getLocation()] == "Town")
    {
        QSound::play("Sounds\\goldDrop.wav");
        int itemIndex;
        int itemType;
        QVector<Item> inventoryItems;
        QVector<int> junkIndexs;
        int junkAmount = 0;
        QString item = ui->lstInventory->currentItem()->text();

        inventoryItems = player_->getInventory();

        for (int a = 0; a < inventoryItems.length(); a++)
        {
            if (item == inventoryItems.value(a).name)
            {
                itemIndex = a;
            }
        }

        itemType = inventoryItems.value(itemIndex).itemType;

        if (itemType != 9)
        {
            player_->addGold(inventoryItems.value(itemIndex).sellPrice);
            player_->removeItemFromInventory(itemIndex);

            if (inventoryItems.value(itemIndex).name == "Bedroll")
                player_->removeBedroll();
            if (inventoryItems.value(itemIndex).name == "Firestarter Kit")
                player_->removeFireStarterKit();
        }
        else
        {
            for (int b = 0; b < inventoryItems.length(); b++)
            {
                if (item == inventoryItems.value(b).name)
                {
                    junkIndexs.push_back(b);
                    junkAmount += 1;
                }
            }

            player_->addGold(inventoryItems.value(itemIndex).sellPrice * junkAmount);
            std::sort(junkIndexs.rbegin(), junkIndexs.rend());

            for (int b = 0; b < junkIndexs.length(); b++)
            {
                player_->removeItemFromInventory(junkIndexs.value(b));
            }
        }

        setPlayerInfo();
        setPlayerInventory();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Sell Item");
        msgBox.setText("You need to be in a City<br>or Town to sell items.");
        msgBox.exec();
    }
}

void GameLogic::on_btnRestBS_clicked()
{
    message_ = "";
    if (strRestLocation_[player_->getLocation()] == "City")
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Rest");
        msgBox.setText("Would you like to rest at an Inn<br>"
                       "Or set up camp outside the City?");
        QPushButton *btnInn = msgBox.addButton(tr("Inn"), QMessageBox::ActionRole);
        QPushButton *btnCamp = msgBox.addButton(tr("Camp"), QMessageBox::ActionRole);
        QPushButton *btnCancel = msgBox.addButton(QMessageBox::Cancel);
        msgBox.exec();

        if (msgBox.clickedButton() == btnInn)
        {
            if (player_->getGold() >= 1000)
            {
                message_ += QString("You pay 50 gold to rest for the night at the %1 Inn\n"
                                    "Health and Stamina are fully restored").arg(strLocations_[player_->getLocation()]);
                player_->setHealth(player_->getMaxHealth());
                player_->setStamina(player_->getMaxStamina());
                player_->removeGold(1000);
            }
            else
            {
                message_ += QString("You do not have enough gold to stay at the %1 Inn.\n"
                                    "This Inn costs 1000 gold for the night.").arg(strLocations_[player_->getLocation()]);
            }
        }
        else if (msgBox.clickedButton() == btnCamp)
        {
            if (!player_->hasBedroll() && !player_->hasFireStarterKit())
            {
                message_ += "You need a Bedroll or Firestarter Kit to set up camp\n";
            }
            else
            {
                message_ += QString("You set up camp outside %1 City\n").arg(strLocations_[player_->getLocation()]);

                int itemIndex;
                bool hasRation = false;
                QVector<Item> inventoryItems;

                inventoryItems = player_->getInventory();

                for (int a = 0; a < inventoryItems.length(); a++)
                {
                    if (inventoryItems.value(a).name.toUpper() == "RATION")
                    {
                        itemIndex = a;
                        hasRation = true;
                        break;
                    }
                }

                if (hasRation)
                {
                    QMessageBox msgBox;
                    msgBox.setWindowTitle("Rest");
                    msgBox.setText("Would you like to eat a ration before resting?<br>"
                                   "If no, you will not gain health from resting.");
                    QPushButton *btnYes = msgBox.addButton(tr("Yes"), QMessageBox::ActionRole);
                    QPushButton *btnNo = msgBox.addButton(tr("No"), QMessageBox::ActionRole);
                    msgBox.exec();

                    if (msgBox.clickedButton() == btnYes)
                    {
                        if (player_->hasBedroll() && !player_->hasFireStarterKit())
                        {
                            player_->addHealth(player_->getMaxHealth() * .25);
                            player_->addStamina(player_->getMaxStamina() * .30);
                            message_ += QString("You eat a ration and sleep in your Bedroll\n"
                                                "Health is restored by 25%\n"
                                                "Stamina is restored by 30%\n");
                        }
                        else if (!player_->hasBedroll() && player_->hasFireStarterKit())
                        {
                            player_->addHealth(player_->getMaxHealth() * .25);
                            player_->addStamina(player_->getMaxStamina() * .40);
                            message_ += QString("You eat a ration and sleep next to a warm fire\n"
                                                "Health is restored by 25%\n"
                                                "Stamina is restored by 40%\n");
                        }
                        else if (player_->hasBedroll() && player_->hasFireStarterKit())
                        {
                            player_->addHealth(player_->getMaxHealth() * .30);
                            player_->addStamina(player_->getMaxStamina() * .70);
                            message_ += QString("You eat a ration and sleep in your Bedroll next to a warm fire\n"
                                                "Health is restored by 30%\n"
                                                "Stamina is restored by 70%\n");
                        }
                        player_->removeRation(itemIndex);
                    }
                    else if (msgBox.clickedButton() == btnNo)
                    {
                        if (player_->hasBedroll() && !player_->hasFireStarterKit())
                        {
                            player_->addStamina(player_->getMaxStamina() * .20);
                            message_ += QString("You sleep in your Bedroll\n"
                                                "Stamina is restored by 20%\n");
                        }
                        else if (!player_->hasBedroll() && player_->hasFireStarterKit())
                        {
                            player_->addStamina(player_->getMaxStamina() * .30);
                            message_ += QString("You sleep next to a warm fire\n"
                                                "Stamina is restored by 30%\n");
                        }
                        else if (player_->hasBedroll() && player_->hasFireStarterKit())
                        {
                            player_->addStamina(player_->getMaxStamina() * .70);
                            message_ += QString("You sleep in your Bedroll next to a warm fire\n"
                                                "Stamina is restored by 50%\n");
                        }
                    }
                }
            }
        }
        else if (msgBox.clickedButton() == btnCancel)
        {
            //do nothing
        }
    }
    else if (strRestLocation_[player_->getLocation()] == "Town")
    {
        if ((quest_->getQuestType() == 4 && location_ == riverbane) ||
             (quest_->getQuestType() >= 6 && location_ == andorjaul))
        {
            message_ += QString("%1 is under attack.\n"
                                "You can not rest here right now.").arg(strLocations_[player_->getLocation()]);
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Rest");
            msgBox.setText("Would you like to rest at an Inn<br>"
                           "Or set up camp outside the town?");
            QPushButton *btnInn = msgBox.addButton(tr("Inn"), QMessageBox::ActionRole);
            QPushButton *btnCamp = msgBox.addButton(tr("Camp"), QMessageBox::ActionRole);
            QPushButton *btnCancel = msgBox.addButton(QMessageBox::Cancel);
            msgBox.exec();

            if (msgBox.clickedButton() == btnInn)
            {
                if (player_->getGold() >= 700)
                {
                    message_ += QString("You pay 30 gold to rest for the night at the %1 Inn\n"
                                        "Health and Stamina are restored by 4").arg(strLocations_[player_->getLocation()]);
                    player_->addHealth(player_->getMaxHealth() * .50);
                    player_->addStamina(player_->getMaxHealth() * .50);
                    player_->removeGold(700);
                }
                else
                {
                    message_ += QString("You do not have enough gold to stay at the %1 Inn.\n"
                                        "This Inn costs 700 gold for the night.").arg(strLocations_[player_->getLocation()]);
                }
            }
            else if (msgBox.clickedButton() == btnCamp)
            {
                if (!player_->hasBedroll() || !player_->hasFireStarterKit())
                {
                    message_ += "You need a Bedroll or Firestarter Kit to set up camp\n";
                }
                else
                {
                    message_ += QString("You set up camp outside %1 City\n").arg(strLocations_[player_->getLocation()]);

                    int itemIndex;
                    bool hasRation = false;
                    QVector<Item> inventoryItems;

                    inventoryItems = player_->getInventory();

                    for (int a = 0; a < inventoryItems.length(); a++)
                    {
                        if (inventoryItems.value(a).name.toUpper() == "RATION")
                        {
                            itemIndex = a;
                            hasRation = true;
                            break;
                        }
                    }

                    if (hasRation)
                    {
                        QMessageBox msgBox;
                        msgBox.setWindowTitle("Rest");
                        msgBox.setText("Would you like to eat a ration before resting?<br>"
                                       "If no, you will not gain health from resting.");
                        QPushButton *btnYes = msgBox.addButton(tr("Yes"), QMessageBox::ActionRole);
                        QPushButton *btnNo = msgBox.addButton(tr("No"), QMessageBox::ActionRole);
                        msgBox.exec();

                        if (msgBox.clickedButton() == btnYes)
                        {
                            if (player_->hasBedroll() && !player_->hasFireStarterKit())
                            {
                                player_->addHealth(player_->getMaxHealth() * .25);
                                player_->addStamina(player_->getMaxStamina() * .30);
                                message_ += QString("You eat a ration and sleep in your Bedroll\n"
                                                    "Health is restored by 25%\n"
                                                    "Stamina is restored by 30%\n");
                            }
                            else if (!player_->hasBedroll() && player_->hasFireStarterKit())
                            {
                                player_->addHealth(player_->getMaxHealth() * .25);
                                player_->addStamina(player_->getMaxStamina() * .40);
                                message_ += QString("You eat a ration and sleep next to a warm fire\n"
                                                    "Health is restored by 25%\n"
                                                    "Stamina is restored by 40%\n");
                            }
                            else if (player_->hasBedroll() && player_->hasFireStarterKit())
                            {
                                player_->addHealth(player_->getMaxHealth() * .30);
                                player_->addStamina(player_->getMaxStamina() * .70);
                                message_ += QString("You eat a ration and sleep in your Bedroll next to a warm fire\n"
                                                    "Health is restored by 30%\n"
                                                    "Stamina is restored by 70%\n");
                            }
                            player_->removeRation(itemIndex);
                        }
                        else if (msgBox.clickedButton() == btnNo)
                        {
                            if (player_->hasBedroll() && !player_->hasFireStarterKit())
                            {
                                player_->addStamina(player_->getMaxStamina() * .20);
                                message_ += QString("You sleep in your Bedroll\n"
                                                    "Stamina is restored by 20%\n");
                            }
                            else if (!player_->hasBedroll() && player_->hasFireStarterKit())
                            {
                                player_->addStamina(player_->getMaxStamina() * .30);
                                message_ += QString("You sleep next to a warm fire\n"
                                                    "Stamina is restored by 30%\n");
                            }
                            else if (player_->hasBedroll() && player_->hasFireStarterKit())
                            {
                                player_->addStamina(player_->getMaxStamina() * .70);
                                message_ += QString("You sleep in your Bedroll next to a warm frire\n"
                                                    "Stamina is restored by 50%\n");
                            }
                        }
                    }
                }
            }
            else if (msgBox.clickedButton() == btnCancel)
            {
                //do nothing
            }
        }
    }
    else if (strRestLocation_[player_->getLocation()] == "Camp")
    {
        if (!player_->hasBedroll() || !player_->hasFireStarterKit())
        {
            message_ += "You need a Bedroll or Firestarter Kit to set up camp\n";
        }
        else
        {
            message_ += QString("You set up camp\n");

            int itemIndex;
            bool hasRation = false;
            QVector<Item> inventoryItems;

            inventoryItems = player_->getInventory();

            for (int a = 0; a < inventoryItems.length(); a++)
            {
                if (inventoryItems.value(a).name.toUpper() == "RATION")
                {
                    itemIndex = a;
                    hasRation = true;
                    break;
                }
            }

            if (hasRation)
            {
                QMessageBox msgBox;
                msgBox.setWindowTitle("Rest");
                msgBox.setText("Would you like to eat a ration before resting?<br>"
                               "If no, you will not gain health from resting.");
                QPushButton *btnYes = msgBox.addButton(tr("Yes"), QMessageBox::ActionRole);
                QPushButton *btnNo = msgBox.addButton(tr("No"), QMessageBox::ActionRole);
                msgBox.exec();

                if (msgBox.clickedButton() == btnYes)
                {
                    if (player_->hasBedroll() && !player_->hasFireStarterKit())
                    {
                        player_->addHealth(player_->getMaxHealth() * .25);
                        player_->addStamina(player_->getMaxStamina() * .30);
                        message_ += QString("You eat a ration and sleep in your Bedroll\n"
                                            "Health is restored by 25%\n"
                                            "Stamina is restored by 30%\n");
                    }
                    else if (!player_->hasBedroll() && player_->hasFireStarterKit())
                    {
                        player_->addHealth(player_->getMaxHealth() * .25);
                        player_->addStamina(player_->getMaxStamina() * .40);
                        message_ += QString("You eat a ration and sleep next to a warm fire\n"
                                            "Health is restored by 25%\n"
                                            "Stamina is restored by 40%\n");
                    }
                    else if (player_->hasBedroll() && player_->hasFireStarterKit())
                    {
                        player_->addHealth(player_->getMaxHealth() * .30);
                        player_->addStamina(player_->getMaxStamina() * .70);
                        message_ += QString("You eat a ration and sleep in your Bedroll next to a warm fire\n"
                                            "Health is restored by 30%\n"
                                            "Stamina is restored by 70%\n");
                    }
                    player_->removeRation(itemIndex);
                }
                else if (msgBox.clickedButton() == btnNo)
                {
                    if (player_->hasBedroll() && !player_->hasFireStarterKit())
                    {
                        player_->addStamina(player_->getMaxStamina() * .20);
                        message_ += QString("You sleep in your Bedroll\n"
                                            "Stamina is restored by 20%\n");
                    }
                    else if (!player_->hasBedroll() && player_->hasFireStarterKit())
                    {
                        player_->addStamina(player_->getMaxStamina() * .30);
                        message_ += QString("You sleep next to a warm fire\n"
                                            "Stamina is restored by 30%\n");
                    }
                    else if (player_->hasBedroll() && player_->hasFireStarterKit())
                    {
                        player_->addStamina(player_->getMaxStamina() * .70);
                        message_ += QString("You sleep in your Bedroll next to a warm frire\n"
                                            "Stamina is restored by 50%\n");
                    }
                }
            }
        }
    }

    setPlayerInfo();
    setPlayerHealth();
    setPlayerStamina();
    setPlayerInventory();
    ui->txtBattleInfo->setText(message_);
    ui->txtBattleInfo->setEnabled(true);
}


void GameLogic::on_btnUsePotionBS_clicked()
{
    bool hasPotion = false;
    QString lastPotionType = "";
    QVector<Item> inventoryItems;
    QVector<QString> potionNames;

    inventoryItems = player_->getInventory();

    for (int a = 0; a < inventoryItems.length(); a++)
    {
        if (inventoryItems.value(a).name.toUpper().contains("POTION"))
        {
            hasPotion = true;

            if (potionNames.length() > 0)
            {
                if (std::find(potionNames.begin(), potionNames.end(), inventoryItems.value(a).name) != potionNames.end())
                {
                    //do nothing
                }
                else
                {
                    potionNames.push_back(inventoryItems.value(a).name);
                }
            }
            else
            {
                potionNames.push_back(inventoryItems.value(a).name);
            }
        }
    }

    if (hasPotion)
    {
        if (potionNames.length() == 1)
        {
            for (int i = 0; i < inventoryItems.length(); i++)
            {
                if (inventoryItems.value(i).name.toUpper() == potionNames.value(0).toUpper())
                {
                    player_->usePotion(inventoryItems.value(i).healAmount, i);
                    break;
                }
            }
        }

        setPlayerInfo();
        setPlayerInventory();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Drink Potion");
        msgBox.setText("    You have no Potions         ");
        msgBox.exec();
    }
}

void GameLogic::on_btnUseRationBS_clicked()
{
    int itemIndex;
    bool hasRation = false;
    QVector<Item> inventoryItems;

    inventoryItems = player_->getInventory();

    for (int a = 0; a < inventoryItems.length(); a++)
    {
        if (inventoryItems.value(a).name.toUpper() == "RATION")
        {
            itemIndex = a;
            hasRation = true;
            break;
        }
    }

    if (hasRation)
    {
        player_->useRation(inventoryItems.value(itemIndex).healAmount, itemIndex);

        setPlayerInfo();
        setPlayerInventory();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Eat Ration");
        msgBox.setText("    You have no Rations         ");
        msgBox.exec();
    }
}

void GameLogic::checkSkillPoints()
{
    if (player_->getSkillPoints() >= 1)
    {
        ui->btnIncreaseAttack->setEnabled(true);
        ui->btnIncreaseHP->setEnabled(true);
        ui->btnIncreaseCritChance->setEnabled(true);
        ui->btnIncreaseAgility->setEnabled(true);
        ui->btnIncreaseHitChance->setEnabled(true);
        ui->btnIncreaseStamina->setEnabled(true);
    }
    else if (player_->getSkillPoints() == 0)
    {
        ui->btnIncreaseAttack->setEnabled(false);
        ui->btnIncreaseHP->setEnabled(false);
        ui->btnIncreaseCritChance->setEnabled(false);
        ui->btnIncreaseAgility->setEnabled(false);
        ui->btnIncreaseHitChance->setEnabled(false);
        csAddHPSC_->setEnabled(false);
        csAddAPSC_->setEnabled(false);
        csAddCCSC_->setEnabled(false);
        ui->btnIncreaseStamina->setEnabled(false);
    }

    if (player_->getStatVitality() == 20)
    {
        ui->btnIncreaseHP->setEnabled(false);
        ui->btnIncreaseHP->setVisible(false);
    }

    if (player_->getStatStrength() == 20)
    {
        ui->btnIncreaseAttack->setEnabled(false);
        ui->btnIncreaseAttack->setVisible(false);
    }

    if (player_->getStatStamina() == 20)
    {
        ui->btnIncreaseStamina->setEnabled(false);
        ui->btnIncreaseStamina->setVisible(false);
    }

    if (player_->getStatAgility() == 20)
    {
        ui->btnIncreaseAgility->setEnabled(false);
        ui->btnIncreaseAgility->setVisible(false);
    }

    if (player_->getStatLuck() == 20)
    {
        ui->btnIncreaseCritChance->setEnabled(false);
        ui->btnIncreaseCritChance->setVisible(false);
    }

    if (player_->getStatPrecision() == 20)
    {
        ui->btnIncreaseHitChance->setEnabled(false);
        ui->btnIncreaseHitChance->setVisible(false);
    }
}

void GameLogic::checkQuest()
{
    if (quest_->getQuestType() == 1)
    {
        if (quest_->getIsQuestActive() == 1 && quest_->getAmountComplete() != quest_->getObjective())
        {
            QString questText = QString("Progress: %1/%2 Bandit Initiates killed.").arg(quest_->getAmountComplete()).arg(quest_->getObjective());
            ui->lblQTitle->setText(QString("Kill %1 Bandit Initiates").arg(quest_->getObjective()));
            ui->lblQProgress->setText(questText);
            ui->lblQReward->setText(QString("Reward: %1 XP | Gold: 10").arg(quest_->getXPReward()));

            quest_->setObjectiveProgress(questText);
        }
        else if (quest_->getIsQuestActive() == 1 && quest_->getAmountComplete() == quest_->getObjective())
        {
            ui->lblQTitle->setText(QString("Kill %1 Bandit Initiates").arg(quest_->getObjective()));
            ui->lblQProgress->setText(QString("Progress: %1/%2 Bandit Initiates killed.").arg(quest_->getAmountComplete()).arg(quest_->getObjective()));
            ui->lblQReward->setText(QString("Reward: %1 XP | Gold: 10").arg(quest_->getXPReward()));
            QSound::play("Sounds\\questComplete.wav");
            QMessageBox msgBox;
            msgBox.setWindowTitle("Quest");
            msgBox.setText("Quest Completed!");
            msgBox.exec();
            quest_->setIsQuestActive(0);
        }

    }
    else if (quest_->getQuestType() == 2)
    {
        if (quest_->getIsQuestActive() == 1 && quest_->getAmountComplete() != quest_->getObjective())
        {
            QString questText = QString("Progress: Take an Initiate Trainer's Outfit.");
            ui->lblQTitle->setText(QString("Fashionable New Clothes").arg(quest_->getObjective()));
            ui->lblQProgress->setText(questText);
            ui->lblQReward->setText(QString("Reward: %1 XP | Gold: 15").arg(quest_->getXPReward()));

            quest_->setObjectiveProgress(questText);
        }
        else if (quest_->getIsQuestActive() == 1 && quest_->getAmountComplete() == quest_->getObjective())
        {
            ui->lblQTitle->setText(QString("Fashionable New Clothes").arg(quest_->getObjective()));
            ui->lblQProgress->setText(QString("Progress: Trainer Outfit Collected.").arg(quest_->getAmountComplete()).arg(quest_->getObjective()));
            ui->lblQReward->setText(QString("Reward: %1 XP | Gold: 15").arg(quest_->getXPReward()));
            QSound::play("Sounds\\questComplete.wav");
            QMessageBox msgBox;
            msgBox.setWindowTitle("Quest");
            msgBox.setText("Quest Completed!");
            msgBox.exec();
            quest_->setIsQuestActive(0);
        }
    }
    else if (quest_->getQuestType() == 3)
    {
        if (quest_->getIsQuestActive() == 1 && quest_->getAmountComplete() != quest_->getObjective())
        {
            QString questText = QString("Progress: Kill Gren and take his head.");
            ui->lblQTitle->setText(QString("An Opportunity Arises"));
            ui->lblQProgress->setText(questText);
            ui->lblQReward->setText(QString("Reward: %1 XP | Gold 20").arg(quest_->getXPReward()));

            quest_->setObjectiveProgress(questText);
        }
        else if (quest_->getIsQuestActive() == 1 && quest_->getAmountComplete() == quest_->getObjective())
        {
            ui->lblQTitle->setText(QString("An Opportunity Arises"));
            ui->lblQProgress->setText(QString("Progress: Bring Gren's head to Bromeir."));
            ui->lblQReward->setText(QString("Reward: %1 XP | Gold 20").arg(quest_->getXPReward()));
            QSound::play("Sounds\\questComplete.wav");
            QMessageBox msgBox;
            msgBox.setWindowTitle("Quest");
            msgBox.setText("Quest Completed!");
            msgBox.exec();
            quest_->setIsQuestActive(0);
        }
    }
    else if (quest_->getQuestType() == 4)
    {
        if (quest_->getIsQuestActive() == 1 && quest_->getAmountComplete() != quest_->getObjective())
        {
            QString questText = QString("Progress: %1/%2 Raiders killed.").arg(quest_->getAmountComplete()).arg(quest_->getObjective());
            ui->lblQTitle->setText(QString("What's Mine is not Yours"));
            ui->lblQProgress->setText(questText);
            ui->lblQReward->setText(QString("Reward: %1 XP | Gold: 30").arg(quest_->getXPReward()));

            quest_->setObjectiveProgress(questText);
        }
        else if (quest_->getIsQuestActive() == 1 && quest_->getAmountComplete() == quest_->getObjective())
        {
            ui->lblQTitle->setText(QString("What's Mine is not Yours").arg(quest_->getObjective()));
            ui->lblQProgress->setText(QString("Progress: %1/%2 Raiders killed.").arg(quest_->getAmountComplete()).arg(quest_->getObjective()));
            ui->lblQReward->setText(QString("Reward: %1 XP | Gold: 30").arg(quest_->getXPReward()));
            QSound::play("Sounds\\questComplete.wav");
            QMessageBox msgBox;
            msgBox.setWindowTitle("Quest");
            msgBox.setText("Quest Completed!");
            msgBox.exec();
            quest_->setIsQuestActive(0);
        }
    }
    else if (quest_->getQuestType() == 5)
    {
        if (quest_->getIsQuestActive() == 1 && quest_->getAmountComplete() != quest_->getObjective())
        {
            QString questText = QString("Progress: %1/%2 Initiate Ambushers killed.").arg(quest_->getAmountComplete()).arg(quest_->getObjective());
            ui->lblQTitle->setText(QString("Deepwood Cleanup").arg(quest_->getObjective()));
            ui->lblQProgress->setText(questText);
            ui->lblQReward->setText(QString("Reward: %1 XP | Gold: 15").arg(quest_->getXPReward()));

            quest_->setObjectiveProgress(questText);
        }
        else if (quest_->getIsQuestActive() == 1 && quest_->getAmountComplete() == quest_->getObjective())
        {
            ui->lblQTitle->setText(QString("Deepwood Cleanup").arg(quest_->getObjective()));
            ui->lblQProgress->setText(QString("Progress: %1/%2 Initiate Ambushers killed.").arg(quest_->getAmountComplete()).arg(quest_->getObjective()));
            ui->lblQReward->setText(QString("Reward: %1 XP | Gold: 15").arg(quest_->getXPReward()));
            QSound::play("Sounds\\questComplete.wav");
            QMessageBox msgBox;
            msgBox.setWindowTitle("Quest");
            msgBox.setText("Quest Completed!");
            msgBox.exec();
            quest_->setIsQuestActive(0);
        }
    }
    else if (quest_->getQuestType() == 6)
    {
        if (quest_->getIsQuestActive() == 1 && quest_->getAmountComplete() != quest_->getObjective())
        {
            QString questText = QString("Progress: %1/%2 Andorjaul Settlers saved.").arg(quest_->getAmountComplete()).arg(quest_->getObjective());
            ui->lblQTitle->setText(QString("Played The Fool").arg(quest_->getObjective()));
            ui->lblQProgress->setText(questText);
            ui->lblQReward->setText(QString("Reward: %1 XP | Gold: 20").arg(quest_->getXPReward()));

            quest_->setObjectiveProgress(questText);
        }
        else if (quest_->getIsQuestActive() == 1 && quest_->getAmountComplete() == quest_->getObjective())
        {
            ui->lblQTitle->setText(QString("Played The Fool").arg(quest_->getObjective()));
            ui->lblQProgress->setText(QString("Progress: %1/%2 Andorjaul Settlers saved.").arg(quest_->getAmountComplete()).arg(quest_->getObjective()));
            ui->lblQReward->setText(QString("Reward: %1 XP | Gold: 20").arg(quest_->getXPReward()));
            QSound::play("Sounds\\questComplete.wav");
            QMessageBox msgBox;
            msgBox.setWindowTitle("Quest");
            msgBox.setText("Quest Completed!");
            msgBox.exec();
            quest_->setIsQuestActive(0);
        }
    }
    else if (quest_->getQuestType() == 7)
    {
        if (quest_->getIsQuestActive() == 1)
        {
            if(quest_->getAmountComplete() == quest_->getObjective() && quest_->getAmountCompleteII() == quest_->getObjectiveII())
            {
                ui->lblQTitle->setText(QString("Clearing the Mine").arg(quest_->getObjective()));
                ui->lblQProgress->setText(QString("Progress: %1/%2 Kobolds Killed.<br>"
                                                  "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"
                                                  "%3/%4 Menzid Killed").arg(quest_->getAmountComplete()).arg(quest_->getObjective())
                                                                        .arg(quest_->getAmountCompleteII()).arg(quest_->getObjectiveII()));
                ui->lblQReward->setText(QString("Reward: %1 XP | Gold: 25").arg(quest_->getXPReward()));
                QSound::play("Sounds\\questComplete.wav");
                QMessageBox msgBox;
                msgBox.setWindowTitle("Quest");
                msgBox.setText("Quest Completed!");
                msgBox.exec();
                quest_->setIsQuestActive(0);
            }
            else
            {
                QString questText = QString("Progress: %1/%2 Kobolds Killed.<br>"
                                            "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"
                                            "%3/%4 Menzid Killed").arg(quest_->getAmountComplete()).arg(quest_->getObjective())
                                                                  .arg(quest_->getAmountCompleteII()).arg(quest_->getObjectiveII());
                ui->lblQTitle->setText(QString("Clearing the Mine").arg(quest_->getObjective()));
                ui->lblQProgress->setText(questText);
                ui->lblQReward->setText(QString("Reward: %1 XP | Gold: 25").arg(quest_->getXPReward()));

                quest_->setObjectiveProgress(questText);
            }

        }
    }
//    else if (quest_->getQuestType() == 6)
//    {
//        if (quest_->getIsQuestActive() == 1 && quest_->getAmountComplete() != quest_->getObjective())
//        {
//            //QString questText = QString("Progress: Kill Thragg.");
//            ui->lblQTitle->setText(quest_->getQuestTitle());
//            ui->lblQProgress->setText(quest_->getObjectiveProgress());
//            ui->lblQReward->setText(QString("Reward: %1 XP").arg(quest_->getXPReward()));
//        }
//        else if (quest_->getIsQuestActive() == 1 && quest_->getAmountComplete() == quest_->getObjective())
//        {
//            ui->lblQTitle->setText(quest_->getQuestTitle());
//            ui->lblQProgress->setText(QString("Progress: Thragg Killed."));
//            ui->lblQReward->setText(QString("Reward: %1 XP").arg(quest_->getXPReward()));
//            QSound::play("Sounds\\questComplete.wav");
//            QMessageBox msgBox;
//            msgBox.setWindowTitle("Quest");
//            msgBox.setText("Quest Completed!");
//            msgBox.exec();
//            quest_->setIsQuestActive(0);
//        }
    //    }
}

void GameLogic::checkLocation()
{
    message_ = "";
    location_ = locations_(player_->getLocation());

    switch(location_)
    {
        case windlehelm :
        message_ = QString("Location: %1\n\n"
                    "Windlehelm is the capital city of Rendinshire. This military city is run by the Windlehelm City Guard. "
                    "They protect the city and surrounding settlements from would be raiders. The City Guard has been "
                    "spread out in full force in the recent weeks as there has been a huge influx of bandit attacks "
                    "around the Rendinshire settlements.").arg(strLocations_[location_]);
            ui->btnBattle->setEnabled(false);
            break;
        case banditBarracks :
            if (quest_->getQuestType() == 0)
            {
                message_ += QString("Location: %1\n\n"
                            "The Bandit Barracks is where Thragg sends all of his new recruits to train. You look "
                            "on from the distance. It would not be wise to get too close.").arg(strLocations_[location_]);
                ui->btnBattle->setEnabled(false);
            }
            else if (quest_->getQuestType() >= 4)
            {
                message_ += QString("Location: %1\n\n"
                                    "It is too dangerous to travel to Thragg's Barracks right now.").arg(strLocations_[location_]);
                ui->btnBattle->setEnabled(false);
            }
            else
            {
                message_ += QString("Location: %1\n\n").arg(strLocations_[location_]);
                ui->btnBattle->setEnabled(true);
            }
            break;
        case deepwoodForest :
            if (player_->getQuestsCompleted() < 2)
            {
                message_ += QString("Location: %1\n\n"
                                    "Deepwood Forest is usually a pretty quite place. "
                                    "The Windlehelm City Guard built a road that runs through the forest "
                                    "that they use for trade convoys. "
                                    "Bandits like to wander the forest every now and then in small numbers. "
                                    "Nothing to be alarmed about, but always stay vigilant when travelling "
                                    "through Deepwood.\n"
                                    "Apart from some patrolling men of the Windlehelm City Guard, "
                                    "Deepwood is pretty quite at the moment.").arg(strLocations_[location_]);
                ui->btnBattle->setEnabled(false);
            }
            else
            {
                message_ += QString("Location: %1\n\n").arg(strLocations_[location_]);
                ui->btnBattle->setEnabled(true);
            }
            break;
        case riverbane :
            if (quest_->getQuestType() < 4 )
            {
                message_ += QString("Location: %1\n\n"
                                    "Riverbane is one of the smaller settlements outside of Windlehelm. "
                                    "Most of the inhabitants here are miners that work at the "
                                    "Riverbane Mine. They supply a huge amount of metals to Windlehelm, "
                                    "which they use for crafting weapons and armour.\n").arg(strLocations_[location_]);
                ui->btnBattle->setEnabled(false);
            }
            else if (quest_->getQuestType() > 4)
            {
                message_ += QString("Location: %1\n\n"
                                    "Riverbane is currently under heavy protection from the "
                                    "Windlehelm City Guard and is in no danger.").arg(strLocations_[location_]);
                ui->btnBattle->setEnabled(false);
            }
            else
            {
                message_ += QString("Location: %1\n\n").arg(strLocations_[location_]);
                ui->btnBattle->setEnabled(true);
            }
            break;
        case riverbaneMine :
            if (quest_->getQuestType() < 7 )
            {
                message_ += QString("Location: %1\n\n"
                                    "The Riverbane Mine is the most profitable mine of Rendinshire. "
                                    "It employs the largest number of miners in the province and "
                                    "supplies Windlehelm City with the majority of its metals. "
                                    "Riverbane also sends out travelling vendors to sell metals "
                                    "to other provinces around Rendinshire.").arg(strLocations_[location_]);
                ui->btnBattle->setEnabled(false);
            }
            else if (quest_->getQuestType() > 7 || player_->getQuestsCompleted() == 7)
            {
                message_ += QString("Location: %1\n\n"
                                    "The Riverbane Mine is now cleared of Kobold invaders and the miners "
                                    "are back to work.").arg(strLocations_[location_]);
                ui->btnBattle->setEnabled(false);
            }
            else
            {
                message_ += QString("Location: %1\n\n").arg(strLocations_[location_]);
                ui->btnBattle->setEnabled(true);
            }
            break;
        case andorjaul :
            if (quest_->getQuestType() < 6 && player_->getQuestsCompleted() < 7)
            {
                message_ += QString("Location: %1\n\n"
                                    "Andorjaul is one of the bigger settlements outside of Windlehelm. "
                                    "Many of the inhabitants here are just commoners, but there are also "
                                    "medical professionals here. There is a hospital and medical shops "
                                    "here that help out most of the travellers outside of Windlehelm. "
                                    "Andorjaul also provides medicines and medical aid to the "
                                    "Windlehelm City Guard.").arg(strLocations_[location_]);
                ui->btnBattle->setEnabled(false);
            }
            else
            {
                message_ += QString("Location: %1\n\n").arg(strLocations_[location_]);
                ui->btnBattle->setEnabled(true);
            }
            break;
    }

    ui->txtBattleInfo->setText(message_);
    ui->txtBattleInfo->setEnabled(true);
}

void GameLogic::openMenuTab()
{
    ui->tabGame->setCurrentIndex(0);
    msNewGameSC_->setEnabled(true);
    msQuitGameSC_->setEnabled(true);
    asBuyPotionSC_->setEnabled(false);
    asUsePotionSC_->setEnabled(false);
    bsBattleSC_->setEnabled(false);
    bsUsePotionSC_->setEnabled(false);
    bsAttackSC_->setEnabled(false);
    bsSpecialSC_->setEnabled(false);
    csAddHPSC_->setEnabled(false);
    csAddAPSC_->setEnabled(false);
    csAddCCSC_->setEnabled(false);
    qsBeginSC_->setEnabled(false);
    qsAbandonSC_->setEnabled(false);
    qsHandInSC_->setEnabled(false);
}

void GameLogic::openActionTab()
{
    ui->tabGame->setCurrentIndex(1);
    msNewGameSC_->setEnabled(false);
    msQuitGameSC_->setEnabled(false);
    asBuyPotionSC_->setEnabled(true);
    asUsePotionSC_->setEnabled(true);
    bsBattleSC_->setEnabled(false);
    bsUsePotionSC_->setEnabled(false);
    bsAttackSC_->setEnabled(false);
    bsSpecialSC_->setEnabled(false);
    csAddHPSC_->setEnabled(false);
    csAddAPSC_->setEnabled(false);
    csAddCCSC_->setEnabled(false);
    qsBeginSC_->setEnabled(false);
    qsAbandonSC_->setEnabled(false);
    qsHandInSC_->setEnabled(false);
}

void GameLogic::openBattleTab()
{
    ui->tabGame->setCurrentIndex(2);
    msNewGameSC_->setEnabled(false);
    msQuitGameSC_->setEnabled(false);
    asBuyPotionSC_->setEnabled(false);
    asUsePotionSC_->setEnabled(false);
    bsBattleSC_->setEnabled(true);
    bsUsePotionSC_->setEnabled(false);
    bsAttackSC_->setEnabled(false);
    bsSpecialSC_->setEnabled(false);
    csAddHPSC_->setEnabled(false);
    csAddAPSC_->setEnabled(false);
    csAddCCSC_->setEnabled(false);
    qsBeginSC_->setEnabled(false);
    qsAbandonSC_->setEnabled(false);
    qsHandInSC_->setEnabled(false);
}

void GameLogic::openCharacterTab()
{
    ui->tabGame->setCurrentIndex(3);
    msNewGameSC_->setEnabled(false);
    msQuitGameSC_->setEnabled(false);
    asBuyPotionSC_->setEnabled(false);
    asUsePotionSC_->setEnabled(false);
    bsBattleSC_->setEnabled(false);
    bsUsePotionSC_->setEnabled(false);
    bsAttackSC_->setEnabled(false);
    bsSpecialSC_->setEnabled(false);

    if (player_->getSkillPoints() > 0)
    {
        csAddHPSC_->setEnabled(true);
        csAddAPSC_->setEnabled(true);
        csAddCCSC_->setEnabled(true);
    }

    qsBeginSC_->setEnabled(false);
    qsAbandonSC_->setEnabled(false);
    qsHandInSC_->setEnabled(false);
}

void GameLogic::openQuestTab()
{
    ui->tabGame->setCurrentIndex(4);
    msNewGameSC_->setEnabled(false);
    msQuitGameSC_->setEnabled(false);
    asBuyPotionSC_->setEnabled(false);
    asUsePotionSC_->setEnabled(false);
    bsBattleSC_->setEnabled(false);
    bsUsePotionSC_->setEnabled(false);
    bsAttackSC_->setEnabled(false);
    bsSpecialSC_->setEnabled(false);
    csAddHPSC_->setEnabled(false);
    csAddAPSC_->setEnabled(false);
    csAddCCSC_->setEnabled(false);
    qsBeginSC_->setEnabled(true);
    qsAbandonSC_->setEnabled(false);
    qsHandInSC_->setEnabled(false);
}

void GameLogic::on_btnIncreaseHP_clicked()
{
    player_->addStatVitality(1);
    player_->setHealth(player_->getMaxHealth());
    ui->lblCHealth->setText(QString("Health: %1/%2").arg(player_->getHealth()).arg(player_->getMaxHealth()));
    ui->lblCVitality->setText(QString("Vitality: %1").arg(player_->getTotalVitalityPoints()));
    player_->setSkillPoints(1);
    ui->lblCSkillPoints->setText(QString("Skill Points: %1").arg(player_->getSkillPoints()));
    checkSkillPoints();
    setPlayerHealth();
}

void GameLogic::on_btnIncreaseAttack_clicked()
{
    player_->addStatStrength(1);
    ui->lblCAttack->setText(QString("Attack: %1-%2").arg(player_->getMinAttackPower()).arg(player_->getMaxAttackPower()));
    ui->lblCStrength->setText(QString("Strength: %1").arg(player_->getTotalStrengthPoints()));
    player_->setSkillPoints(1);
    ui->lblCSkillPoints->setText(QString("Skill Points: %1").arg(player_->getSkillPoints()));
    checkSkillPoints();
}

void GameLogic::on_btnIncreaseStamina_clicked()
{
    player_->addStatStamina(1);
    ui->lblCStamina->setText(QString("Stamina: %1").arg(player_->getTotalStaminaPoints()));
    player_->setSkillPoints(1);
    ui->lblCSkillPoints->setText(QString("Skill Points: %1").arg(player_->getSkillPoints()));
    checkSkillPoints();
    setPlayerStamina();
}

void GameLogic::on_btnIncreaseAgility_clicked()
{
    player_->addStatAgility(1);
    ui->lblCAgility->setText(QString("Agility: %1").arg(player_->getTotalAgilityPoints()));
    player_->setSkillPoints(1);
    ui->lblCSkillPoints->setText(QString("Skill Points: %1").arg(player_->getSkillPoints()));
    checkSkillPoints();
}

void GameLogic::on_btnIncreaseCritChance_clicked()
{
    player_->addStatLuck(1);
    ui->lblCLuck->setText(QString("Luck: %1").arg(player_->getTotalLuckPoints()));
    player_->setSkillPoints(1);
    ui->lblCSkillPoints->setText(QString("Skill Points: %1").arg(player_->getSkillPoints()));
    checkSkillPoints();
}

void GameLogic::on_btnIncreaseHitChance_clicked()
{
    player_->addStatPrecision(1);
    ui->lblCHit->setText(QString("Hit: %1").arg(player_->getTotalPrecisionPoints()));
    player_->setSkillPoints(1);
    ui->lblCSkillPoints->setText(QString("Skill Points: %1").arg(player_->getSkillPoints()));
    checkSkillPoints();
}

void GameLogic::on_btnBeginQuest_clicked()
{
    QString questTitle = "";
    QString questText = "";
    int goldReward = 0;

    if (player_->getQuestsCompleted() == 0)
    {
        if (location_ == windlehelm)
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Bormeir");
            msgBox.setText(QString("<b>Bandit Problems</b><br>"
                                   "---------------------------------------------------------------------<br><br>"
                                   "Thank you for seeing me, %1.<br>"
                                   "Windlehelm has been under attack by bandits for months now.<br>"
                                   "Their leader Thragg has a stronghold to the Northeast and has<br>"
                                   "been sending his bandits to attack Windlehelm and the small<br>"
                                   "settlements outside the city.<br><br>"
                                   "The Windlehelm City Guard has been doing its best to keep the<br>"
                                   "bandits out of the city, but we can only afford to send out so many<br>"
                                   "guards to protect the outside settlements.<br>"
                                   "The bandits keep growing in numbers and soon we won't<br>"
                                   "be able to hold them off any longer.<br><br>"
                                   "Thragg has a barracks west of his stronghold where he trains<br>"
                                   "his new followers. Go there, and take out as many bandits as you can.<br><br>"
                                   "<B>Objective:</b><br>Kill 6 Bandit Initiates<br>"
                                   "<b>Reward</b><br>"
                                   "50 XP<br>"
                                   "10 Gold<br>").arg(player_->getName()));
            QPushButton *btnAccept = msgBox.addButton(tr("Accept"), QMessageBox::ActionRole);
            QPushButton *btnDecline = msgBox.addButton(tr("Decline"), QMessageBox::ActionRole);
            msgBox.exec();

            if (msgBox.clickedButton() == btnAccept)
            {
                QSound::play("Sounds\\acceptQuest.wav");
                goldReward = 10;
                //xpReward, objective, objectiveII, amountComplete, amountCompleteII, isQuestComplete, isQuestActive, questType, numObjectives,  handInLocation,  handInNPC
                quest_ = new quests(50, 6, 0, 0, 0, 0, 1, 1, 1, 0, "Bormier");
                questTitle = QString("Kill %1 Bandit Initiates").arg(quest_->getObjective());
                questText = QString("Progress: %1/%2 Bandit Initiates killed.").arg(quest_->getAmountComplete()).arg(quest_->getObjective());
            }
            else if (msgBox.clickedButton() == btnDecline)
            {
                QSound::play("Sounds\\abondonQuest.wav");
                //xpReward, objective, objectiveII, amountComplete, amountCompleteII, isQuestComplete, isQuestActive, questType, numObjectives,  handInLocation,  handInNPC
                quest_ = new quests(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "");
            }
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Quest Log");
            msgBox.setText(QString("You need to talk to Bormeir in\n%1 to begin this quest.").arg(strLocations_[0]));
            msgBox.exec();
        }
    }
    else if (player_->getQuestsCompleted() == 1)
    {
        if (location_ == windlehelm)
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Bormeir");
            msgBox.setText(QString("<b>Fashionable New Clothes</b><br>"
                                   "---------------------------------------------------------------------<br><br>"
                                   "I've come up with a plan to disrupt the training of new bandits.<br><br>"
                                   "I want you to go back to the barracks and<br>"
                                   "find one of the Initiate Trainers.<br>"
                                   "They wear a special outfit to identify themselves.<br>"
                                   "Find one of the trainers,<br>"
                                   "kill them, and take their outfit. I'll explain later.<br><br>"
                                   "<B>Objective:</b><br>Take an Initiate Trainer's Outfit<br>"
                                   "<b>Reward</b><br>"
                                   "100 XP<br>"
                                   "15 Gold").arg(player_->getName()));
            QPushButton *btnAccept = msgBox.addButton(tr("Accept"), QMessageBox::ActionRole);
            QPushButton *btnDecline = msgBox.addButton(tr("Decline"), QMessageBox::ActionRole);
            msgBox.exec();

            if (msgBox.clickedButton() == btnAccept)
            {
                QSound::play("Sounds\\acceptQuest.wav");
                goldReward = 15;
                //xpReward, objective, objectiveII, amountComplete, amountCompleteII, isQuestComplete, isQuestActive, questType, numObjectives,  handInLocation,  handInNPC
                quest_ = new quests(100, 1, 0, 0, 0, 0, 1, 2, 1, 0, "Bormier");
                questTitle = QString("Fashionable New Clothes").arg(quest_->getObjective());
                questText = QString("Progress: Take an Initiate Trainer's Outfit.");
            }
            else if (msgBox.clickedButton() == btnDecline)
            {
                QSound::play("Sounds\\abondonQuest.wav");
                //xpReward, objective, objectiveII, amountComplete, amountCompleteII, isQuestComplete, isQuestActive, questType, numObjectives,  handInLocation,  handInNPC
                quest_ = new quests(0, 0, 0, 0, 0, 0, 0, 1, 0, 0, "");
            }
        }

        else
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Quest Log");
            msgBox.setText(QString("You need to talk to Bormeir in\n%1 to begin this quest.").arg(strLocations_[0]));
            msgBox.exec();
        }
    }
    else if (player_->getQuestsCompleted() == 2)
    {
        if (location_ == windlehelm)
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Bormeir");
            msgBox.setText(QString("<b>An Opportunity Arises</b><br>"
                                   "---------------------------------------------------------------------<br><br>"
                                   "%1, I just heard word from one of my scouts in Deepwood Forest that<br>"
                                   "a huge group of Bandit Initiates have set up camp inside the forest<br>"
                                   "lead by a high value target. They're lead by Gren, one of Thragg's<br>"
                                   "most trusted trainers.<br><br>"
                                   "They've set up their camp just out of site of a main road through<br>"
                                   "Deepwood Forest. Odds are they are setting up to ambush our convoys.<br><br>"
                                   "Gren will be hard to get to as he always throws his initiates ahead<br>"
                                   "of him into battle and retreats the second he gets a chance. My scouts<br>"
                                   "will be there to flank Gren if he tries to get away.<br><br>"
                                   "Kill Gren and bring me his head.<br><br>"
                                   "<B>Objective:</b><br>Kill Gren and bring his head to Bormier<br>"
                                   "<b>Reward</b><br>"
                                   "250 XP<br>"
                                   "20 Gold").arg(player_->getName()));
            QPushButton *btnAccept = msgBox.addButton(tr("Accept"), QMessageBox::ActionRole);
            QPushButton *btnDecline = msgBox.addButton(tr("Decline"), QMessageBox::ActionRole);
            msgBox.exec();

            if (msgBox.clickedButton() == btnAccept)
            {
                QSound::play("Sounds\\acceptQuest.wav");
                goldReward = 20;
                //xpReward, objective, objectiveII, amountComplete, amountCompleteII, isQuestComplete, isQuestActive, questType, numObjectives,  handInLocation,  handInNPC
                quest_ = new quests(250, 1, 0, 0, 0, 0, 1, 3, 1, 0, "Bormier");
                questTitle = QString("An Oportunity Arises").arg(quest_->getObjective());
                questText = QString("Progress: Kill Gren and take his head.");
            }
            else if (msgBox.clickedButton() == btnDecline)
            {
                QSound::play("Sounds\\abondonQuest.wav");
                //xpReward, objective, objectiveII, amountComplete, amountCompleteII, isQuestComplete, isQuestActive, questType, numObjectives,  handInLocation,  handInNPC
                quest_ = new quests(0, 0, 0, 0, 0, 0, 0, 2, 0, 0, "");
            }
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Quest Log");
            msgBox.setText(QString("You need to talk to Bormeir in\n%1 to begin this quest.").arg(strLocations_[0]));
            msgBox.exec();
        }
    }
    else if (player_->getQuestsCompleted() == 3)
    {
        if (location_ == windlehelm)
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Bormeir");
            msgBox.setText(QString("<b>What's Mine is not Yours</b><br>"
                                   "---------------------------------------------------------------------<br><br>"
                                   "%1, I just got a report back from my guard in Thragg's training<br>"
                                   "barracks. He said Thragg is planning a raid on the Riverbane settlement.<br><br>"
                                   "Riverbane is a mining colony that provides us with 30 percent of the<br>"
                                   "metals we use for weapons and armour. We cannot afford to lose Riverbane.<br>"
                                   "Get to Riverbane as soon as you can, and help my guards defend the settlement.<br><br>"
                                   "Speak with Werner when the raid has stopped. He will be leading the<br>"
                                   "defense on Riverbane.<br><br>"
                                   "<B>Objective:</b><br>Kill 10 Bandit Raiders<br>"
                                   "<b>Reward</b><br>"
                                   "150 XP<br>"
                                   "30 Gold").arg(player_->getName()));
            QPushButton *btnAccept = msgBox.addButton(tr("Accept"), QMessageBox::ActionRole);
            QPushButton *btnDecline = msgBox.addButton(tr("Decline"), QMessageBox::ActionRole);
            msgBox.exec();

            if (msgBox.clickedButton() == btnAccept)
            {
                QSound::play("Sounds\\acceptQuest.wav");
                goldReward = 30;
                //xpReward, objective, objectiveII, amountComplete, amountCompleteII, isQuestComplete, isQuestActive, questType, numObjectives,  handInLocation,  handInNPC
                quest_ = new quests(150, 10, 0, 0, 0, 0, 1, 4, 1, 3, "Werner");
                questTitle = QString("What's Mine is not Yours").arg(quest_->getObjective());
                questText = QString("Progress: %1/%2 Raiders killed.").arg(quest_->getAmountComplete()).arg(quest_->getObjective());
            }
            else if (msgBox.clickedButton() == btnDecline)
            {
                QSound::play("Sounds\\abondonQuest.wav");
                //xpReward, objective, objectiveII, amountComplete, amountCompleteII, isQuestComplete, isQuestActive, questType, numObjectives,  handInLocation,  handInNPC
                quest_ = new quests(0, 0, 0, 0, 0, 0, 0, 3, 0, 0, "");
            }
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Quest Log");
            msgBox.setText(QString("You need to talk to Bormeir in\n%1 to begin this quest.").arg(strLocations_[0]));
            msgBox.exec();
        }
    }
    else if (player_->getQuestsCompleted() == 4)
    {
        if (location_ == windlehelm)
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Bormeir");
            msgBox.setText(QString("<b>Deepwood Cleanup</b><br>"
                                   "---------------------------------------------------------------------<br><br>"
                                   "Good work in Riverbane. I'll send more guards to Werner to help his<br>"
                                   "defensive. In the meantime, I got reports from my scouts in Deepwood<br>"
                                   "Forest again that more bandits are still hanging around the main paths.<br><br>"
                                   "Those Initiates no longer have anyone guiding them, but they can still<br>"
                                   "cause more damage than I'd like to our convoys. Go back to Deepwood<br>"
                                   "and help my scouts take down more of those bandits.<br><br>"
                                   "<B>Objective:</b><br>Kill 10 Initiate Ambushers<br>"
                                   "<b>Reward</b><br>"
                                   "75 XP<br>"
                                   "15 Gold"));
            QPushButton *btnAccept = msgBox.addButton(tr("Accept"), QMessageBox::ActionRole);
            QPushButton *btnDecline = msgBox.addButton(tr("Decline"), QMessageBox::ActionRole);
            msgBox.exec();

            if (msgBox.clickedButton() == btnAccept)
            {
                QSound::play("Sounds\\acceptQuest.wav");
                goldReward = 15;
                //xpReward, objective, objectiveII, amountComplete, amountCompleteII, isQuestComplete, isQuestActive, questType, numObjectives,  handInLocation,  handInNPC
                quest_ = new quests(75, 10, 0, 0, 0, 0, 1, 5, 1, 0, "Bormier");
                questTitle = QString("Deepwood Cleanup").arg(quest_->getObjective());
                questText = QString("Progress: %1/%2 Initiate Ambushers killed.").arg(quest_->getAmountComplete()).arg(quest_->getObjective());
            }
            else if (msgBox.clickedButton() == btnDecline)
            {
                QSound::play("Sounds\\abondonQuest.wav");
                //xpReward, objective, objectiveII, amountComplete, amountCompleteII, isQuestComplete, isQuestActive, questType, numObjectives,  handInLocation,  handInNPC
                quest_ = new quests(0, 0, 0, 0, 0, 0, 0, 4, 0, 0, "");
            }
        }

        else
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Quest Log");
            msgBox.setText(QString("You need to talk to Bormeir in\n%1 to begin this quest.").arg(strLocations_[0]));
            msgBox.exec();
        }
    }
    else if (player_->getQuestsCompleted() == 5)
    {
        if (location_ == windlehelm)
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Bormeir");
            msgBox.setText(QString("<b>Played The Fool</b><br>"
                                   "---------------------------------------------------------------------<br><br>"
                                   "Thragg knew my guard at the barracks wasn't one of his trainers.<br>"
                                   "One of his bandits tossed my guard's head over the city wall when you<br>"
                                   "were in Deepwood. The raid on Riverbane was a decoy.<br><br>"
                                   "After I sent more men over to help Werner, Thragg lead a raid on<br>"
                                   "the Andorjaul Settlement. They slaughtered all my guards stationed<br>"
                                   "there except the one that made it back to tell me of the raid,<br>"
                                   "but he is badly injured and probably won't live much longer.<br><br>"
                                   "Many of the people there provide us with medicines and<br>"
                                   "medical aid. We need to save as many as we can or we won't have<br>"
                                   "enough doctors to tend to our wounded. Don't try to fight more<br>"
                                   "raiders then you need to. Get in, save as many Andorjaul settlers<br>"
                                   "as you can and get back to Windlehelm.<br><br>"
                                   "<B>Objective:</b><br>Save 7 Andorjaul Settlers<br>"
                                   "<b>Reward</b><br>"
                                   "150 XP<br>"
                                   "20 Gold"));
            QPushButton *btnAccept = msgBox.addButton(tr("Accept"), QMessageBox::ActionRole);
            QPushButton *btnDecline = msgBox.addButton(tr("Decline"), QMessageBox::ActionRole);
            msgBox.exec();

            if (msgBox.clickedButton() == btnAccept)
            {
                QSound::play("Sounds\\acceptQuest.wav");
                goldReward = 20;
                //xpReward, objective, objectiveII, amountComplete, amountCompleteII, isQuestComplete, isQuestActive, questType, numObjectives,  handInLocation,  handInNPC
                quest_ = new quests(150, 7, 0, 0, 0, 0, 1, 6, 1, 0, "Bormeir");
                questTitle = QString("Played The Fool").arg(quest_->getObjective());
                questText = QString("Progress: %1/%2 Andorjaul Settlers saved.").arg(quest_->getAmountComplete()).arg(quest_->getObjective());
            }
            else if (msgBox.clickedButton() == btnDecline)
            {
                QSound::play("Sounds\\abondonQuest.wav");
                //xpReward, objective, objectiveII, amountComplete, amountCompleteII, isQuestComplete, isQuestActive, questType, numObjectives,  handInLocation,  handInNPC
                quest_ = new quests(0, 0, 0, 0, 0, 0, 0, 5, 0, 0, "");
            }
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Quest Log");
            msgBox.setText(QString("You need to talk to Bormeir in\n%1 to begin this quest.").arg(strLocations_[0]));
            msgBox.exec();
        }
    }
    else if (player_->getQuestsCompleted() == 6)
    {
        if (location_ == riverbane)
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Werner");
            msgBox.setText(QString("<b>Clearing the Mine</b><br>"
                                   "---------------------------------------------------------------------<br><br>"
                                   "Andorjaul has been lost? That’s not the news I was hoping for. <br>"
                                   "We can’t worry about that now. Whilst you were gone, a few Raiders <br>"
                                   "came back and released a bunch of kobolds into the Riverbane Mine. <br>"
                                   "We lost a couple miners, but we managed to get most of them out. <br>"
                                   "With the kobolds in there they can’t continue mining. Take some of <br>"
                                   "my guards, go to the mine and kill the kobolds and their leader.<br><br>"
                                   "<B>Objective:</b><br>Kill 10 Kobolds<br>Kill Menzid<br>"
                                   "<b>Reward</b><br>"
                                   "175 XP<br>"
                                   "25 Gold"));
            QPushButton *btnAccept = msgBox.addButton(tr("Accept"), QMessageBox::ActionRole);
            QPushButton *btnDecline = msgBox.addButton(tr("Decline"), QMessageBox::ActionRole);
            msgBox.exec();

            if (msgBox.clickedButton() == btnAccept)
            {
                QSound::play("Sounds\\acceptQuest.wav");
                goldReward = 25;
                //xpReward, objective, objectiveII, amountComplete, amountCompleteII, isQuestComplete, isQuestActive, questType, numObjectives,  handInLocation,  handInNPC
                quest_ = new quests(175, 10, 1, 0, 0, 0, 1, 7, 2, 3, "Werner");
                questTitle = QString("Clearing the Mine").arg(quest_->getObjective());
                questText = QString("Progress: %1/%2 Kobolds Killed.<br>"
                                    "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"
                                    "%3/%4 Menzid Killed").arg(quest_->getAmountComplete()).arg(quest_->getObjective())
                                                          .arg(quest_->getAmountCompleteII()).arg(quest_->getObjectiveII());
            }
            else if (msgBox.clickedButton() == btnDecline)
            {
                QSound::play("Sounds\\abondonQuest.wav");
                //xpReward, objective, objectiveII, amountComplete, amountCompleteII, isQuestComplete, isQuestActive, questType, numObjectives,  handInLocation,  handInNPC
                quest_ = new quests(0, 0, 0, 0, 0, 0, 0, 6, 0, 0, "");
            }
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Quest Log");
            msgBox.setText(QString("You need to talk to Werner in\n%1 to begin this quest.").arg(strLocations_[3]));
            msgBox.exec();
        }
    }

    if (quest_->getIsQuestActive() == 1)
    {
        quest_->setQuestTitle(questTitle);
        quest_->setObjectiveProgress(questText);
        ui->lblQTitle->setText(quest_->getQuestTitle());
        ui->lblQProgress->setText(quest_->getObjectiveProgress());
        ui->lblQReward->setText(QString("Reward: %1 XP | Gold: %2").arg(quest_->getXPReward()).arg(goldReward));
        ui->btnCompleteQuest->setEnabled(true);
        ui->btnAbandonQuest->setEnabled(true);
        ui->btnBeginQuest->setEnabled(false);
        qsBeginSC_->setEnabled(false);
        qsAbandonSC_->setEnabled(true);
        qsHandInSC_->setEnabled(true);
    }
}

void GameLogic::on_btnCompleteQuest_clicked()
{
    if (location_ == locations_(quest_->getHandInLocation()))
    {
        int isQuestComplete = 0;
        quest_->completeQuest();
        if (quest_->getNumObjectives() == 1)
        {
            if (quest_->getAmountComplete() == quest_->getObjective())
            {
                player_->completeQuest();
            }
        }
        else if (quest_->getNumObjectives() == 2)
        {
            if (quest_->getAmountComplete() == quest_->getObjective() && quest_->getAmountCompleteII() == quest_->getObjectiveII())
            {
                player_->completeQuest();
            }
        }
        isQuestComplete = quest_->getIsQuestComplete();

        if (isQuestComplete == 1)
        {
            if (quest_->getQuestTitle().toLower().contains("thragg"))
            {
                QSound::play("Sounds\\deathOfThragg.wav");
                QMessageBox msgBox;
                msgBox.setWindowTitle("End Game");
                msgBox.setText("<b>You have defeated Thragg!</b>");
                msgBox.setInformativeText("You have saved the city of Windlehelm from Thragg and his bandits. "
                                          "They can now pick up the pieces of their destroyed city and start to rebuild. "
                                          "Thragg and his bandits can no longer hurt Windlehelm, thanks to you!");
                msgBox.exec();
                player_->addXP(quest_->getXPReward());
                ui->lblQTitle->setText("Quest Completed!");
                ui->lblQProgress->setText("Progess:");
                ui->lblQReward->setText("Reward:");
                player_->checkXP();
                checkSkillPoints();
                setPlayerInfo();
                ui->btnBeginQuest->setEnabled(true);
                ui->btnCompleteQuest->setEnabled(false);
                ui->btnAbandonQuest->setEnabled(false);
                qsBeginSC_->setEnabled(true);
                qsAbandonSC_->setEnabled(false);
                qsHandInSC_->setEnabled(false);
    //            ui->tabActionScreen->setEnabled(false);
    //            ui->tabCInfoScreen->setEnabled(false);
    //            ui->tabMenuScreen->setEnabled(true);
    //            ui->txtBattleInfo->setEnabled(false);
    //            ui->btnAttack->setEnabled(false);
    //            ui->pbarCHealth->setEnabled(false);
    //            ui->pbarEHealth->setEnabled(false);
    //            ui->btnBattle->setEnabled(false);
    //            ui->btnUsePotionBS->setEnabled(false);
    //            ui->btnSave->setEnabled(false);
    //            ui->pbarCHealth->setValue(0);
            }
            else
            {
                QSound::play("Sounds\\questComplete.wav");
                if (player_->getQuestsCompleted() == 1)
                {
                    QMessageBox msgBox;
                    msgBox.setWindowTitle("Bormeir");
                    msgBox.setText(QString("<b>Bandit Problems - Completed!</b><br>"
                                           "---------------------------------------------------------------------<br><br>"
                                           "Thank you, %1.<br>"
                                           "Now that we've taken out some of Thragg's initiates,<br>"
                                           "maybe that will deter others from joining his ranks.<br>"
                                           "Take this gold as a sign of my gratitude. It's not much,<br>"
                                           "but it's all I can offer you for the time being.<br><br>"
                                           "<b>Quest complete!</b><br>"
                                           "You are rewarded %2 XP and 10 Gold!").arg(player_->getName()).arg(quest_->getXPReward()));
                    msgBox.exec();
                    player_->addGold(10);
                }
                else if (player_->getQuestsCompleted() == 2)
                {
                    QMessageBox msgBox;
                    msgBox.setWindowTitle("Bormeir");
                    msgBox.setText(QString("<b>Fashionable New Clothes - Completed!</b><br>"
                                           "---------------------------------------------------------------------<br><br>"
                                           "Thank you, %1.<br>"
                                           "I will give this to one of my higher ranking guards.<br>"
                                           "He will use it to infiltrate the barracks and disrupt their training<br>"
                                           "and relay any useful information to us that may help us get to Thragg.<br><br>"
                                           "<b>Quest complete!</b><br>"
                                           "You are rewarded %2 XP and 15 Gold!").arg(player_->getName()).arg(quest_->getXPReward()));
                    msgBox.exec();
                    player_->addGold(15);
                }
                else if (player_->getQuestsCompleted() == 3)
                {
                    QMessageBox msgBox;
                    msgBox.setWindowTitle("Bormeir");
                    msgBox.setText(QString("<b>An Opportunity Arises - Completed!</b><br>"
                                           "---------------------------------------------------------------------<br><br>"
                                           "Look at that ugly mug. That's Gren all right. Good job, %1.<br>"
                                           "With Gren dead, Thragg has lost one of his best trainers. This was<br>"
                                           "only a small step towards defeating Thragg and his bandits. If you<br>"
                                           "continue to be successful like this, we'll get Thragg in no time.<br><br>"
                                           "<b>Quest complete!</b><br>"
                                           "You are rewarded %2 XP and 20 Gold!").arg(player_->getName()).arg(quest_->getXPReward()));
                    msgBox.exec();
                    player_->addGold(20);
                }
                else if (player_->getQuestsCompleted() == 4)
                {
                    QMessageBox msgBox;
                    msgBox.setWindowTitle("Werner");
                    msgBox.setText(QString("<b>What's Mine is not Yours - Completed!</b><br>"
                                           "---------------------------------------------------------------------<br><br>"
                                           "Thanks for the help. We've slowed them down for now, but I have a<br>"
                                           "feeling this is only the beginning. They won't let one failed raid stop<br>"
                                           "them from trying to take over Riverbane. We've got things from here,<br>"
                                           "but by all means give us a hand cleaning up the rest of them<br>"
                                           "if you feel so inclined.<br><br>"
                                           "Otherwise, Report back to Bormeir and tell him we need more guards<br>"
                                           "sent down to Riverbane to replace what we've lost. I'm sure he'll<br>"
                                           "have more for you to do.<br><br>"
                                           "<b>Quest complete!</b><br>"
                                           "You are rewarded %2 XP and 30 Gold!").arg(quest_->getXPReward()));
                    msgBox.exec();
                    player_->addGold(30);
                }
                else if (player_->getQuestsCompleted() == 5)
                {
                    QMessageBox msgBox;
                    msgBox.setWindowTitle("Bormeir");
                    msgBox.setText(QString("<b>Deepwood Cleanup - Completed!</b><br>"
                                           "---------------------------------------------------------------------<br><br>"
                                           "Thanks for helping out my scouts in Deepwood. They should be<br>"
                                           "fine on their own now, I have an urgent task for you.<br><br>"
                                           "<b>Quest complete!</b><br>"
                                           "You are rewarded %2 XP and 15 Gold!").arg(quest_->getXPReward()));
                    msgBox.exec();
                    player_->addGold(15);
                }
                else if (player_->getQuestsCompleted() == 6)
                {
                    QMessageBox msgBox;
                    msgBox.setWindowTitle("Bormeir");
                    msgBox.setText(QString("<b>Played The Fool - Completed!</b><br>"
                                           "---------------------------------------------------------------------<br><br>"
                                           "Well done. The loss of Andorjaul is going to hurt, but we cannot try<br>"
                                           "to take it back just yet. We can't lose more soldiers.<br><br>"
                                           "Return to Riverbane. I'm sure Werner could still use your help there.<br>"
                                           "Tell him what happened.<br><br>"
                                           "<b>Quest complete!</b><br>"
                                           "You are rewarded %2 XP and 20 Gold!").arg(quest_->getXPReward()));
                    msgBox.exec();
                    player_->addGold(20);
                }
                else if (player_->getQuestsCompleted() == 7)
                {
                    QMessageBox msgBox;
                    msgBox.setWindowTitle("Werner");
                    msgBox.setText(QString("<b>Clearing the Mine - Completed!</b><br>"
                                           "---------------------------------------------------------------------<br><br>"
                                           "Good job. Now the miners can get back to work. With Andorjaul gone,<br>"
                                           "we’re going to need to make more weapons and armour so we can even<br>"
                                           "stand a chance at getting it back.<br><br>"
                                           "<b>Quest complete!</b><br>"
                                           "You are rewarded %2 XP and 25 Gold!").arg(quest_->getXPReward()));
                    msgBox.exec();
                    player_->addGold(25);
                }
                player_->addXP(quest_->getXPReward());
                ui->lblQTitle->setText("Quest Completed!");
                ui->lblQProgress->setText("Progess:");
                ui->lblQReward->setText("Reward:");
                quest_ = new quests(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "");
                player_->checkXP();
                checkSkillPoints();
                setPlayerInfo();
                ui->btnBeginQuest->setEnabled(true);
                ui->btnCompleteQuest->setEnabled(false);
                ui->btnAbandonQuest->setEnabled(false);
                qsBeginSC_->setEnabled(true);
                qsAbandonSC_->setEnabled(false);
                qsHandInSC_->setEnabled(false);
            }
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Quest Progress");
            msgBox.setText("You have not finished this quest");
            msgBox.exec();
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Quest Log");
        msgBox.setText(QString("You need to talk to %1 in\n%2 to hand in this quest.").arg(quest_->getHandInNPC()).arg(strLocations_[quest_->getHandInLocation()]));
        msgBox.exec();
    }
}

void GameLogic::on_btnAbandonQuest_clicked()
{
    QSound::play("Sounds\\abondonQuest.wav");
    //xpReward, objective, amountComplete, isQuestComplete, isQuestActive
    quest_ = new quests(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "");

    ui->lblQTitle->setText("No Active Quest");
    ui->lblQProgress->setText("Progess:");
    ui->lblQReward->setText("Reward:");
    ui->btnBeginQuest->setEnabled(true);
    ui->btnCompleteQuest->setEnabled(false);
    ui->btnAbandonQuest->setEnabled(false);
    qsBeginSC_->setEnabled(true);
    qsAbandonSC_->setEnabled(false);
    qsHandInSC_->setEnabled(false);
}

void GameLogic::on_tabGame_tabBarClicked(int index)
{
    if (index == 0)
    {
        msNewGameSC_->setEnabled(true);
        msQuitGameSC_->setEnabled(true);
        asBuyPotionSC_->setEnabled(false);
        asUsePotionSC_->setEnabled(false);
        bsBattleSC_->setEnabled(false);
        bsUsePotionSC_->setEnabled(false);
        bsAttackSC_->setEnabled(false);
        bsSpecialSC_->setEnabled(false);
        csAddHPSC_->setEnabled(false);
        csAddAPSC_->setEnabled(false);
        csAddCCSC_->setEnabled(false);
        qsBeginSC_->setEnabled(false);
        qsAbandonSC_->setEnabled(false);
        qsHandInSC_->setEnabled(false);
    }
    else if (index == 1)
    {
        msNewGameSC_->setEnabled(false);
        msQuitGameSC_->setEnabled(false);
        asBuyPotionSC_->setEnabled(true);
        asUsePotionSC_->setEnabled(true);
        bsBattleSC_->setEnabled(false);
        bsUsePotionSC_->setEnabled(false);
        bsAttackSC_->setEnabled(false);
        bsSpecialSC_->setEnabled(false);
        csAddHPSC_->setEnabled(false);
        csAddAPSC_->setEnabled(false);
        csAddCCSC_->setEnabled(false);
        qsBeginSC_->setEnabled(false);
        qsAbandonSC_->setEnabled(false);
        qsHandInSC_->setEnabled(false);
    }
    else if (index == 2)
    {
        msNewGameSC_->setEnabled(false);
        msQuitGameSC_->setEnabled(false);
        asBuyPotionSC_->setEnabled(false);
        asUsePotionSC_->setEnabled(false);
        bsBattleSC_->setEnabled(true);
        bsUsePotionSC_->setEnabled(false);
        bsAttackSC_->setEnabled(false);
        bsSpecialSC_->setEnabled(false);
        csAddHPSC_->setEnabled(false);
        csAddAPSC_->setEnabled(false);
        csAddCCSC_->setEnabled(false);
        qsBeginSC_->setEnabled(false);
        qsAbandonSC_->setEnabled(false);
        qsHandInSC_->setEnabled(false);
    }
    else if (index == 3)
    {
        msNewGameSC_->setEnabled(false);
        msQuitGameSC_->setEnabled(false);
        asBuyPotionSC_->setEnabled(false);
        asUsePotionSC_->setEnabled(false);
        bsBattleSC_->setEnabled(false);
        bsUsePotionSC_->setEnabled(false);
        bsAttackSC_->setEnabled(false);
        bsSpecialSC_->setEnabled(false);

        if (player_->getSkillPoints() > 0)
        {
            csAddHPSC_->setEnabled(true);
            csAddAPSC_->setEnabled(true);
            csAddCCSC_->setEnabled(true);
        }

        qsBeginSC_->setEnabled(false);
        qsAbandonSC_->setEnabled(false);
        qsHandInSC_->setEnabled(false);
    }
    else if (index == 4)
    {
        msNewGameSC_->setEnabled(false);
        msQuitGameSC_->setEnabled(false);
        asBuyPotionSC_->setEnabled(false);
        asUsePotionSC_->setEnabled(false);
        bsBattleSC_->setEnabled(false);
        bsUsePotionSC_->setEnabled(false);
        bsAttackSC_->setEnabled(false);
        bsSpecialSC_->setEnabled(false);
        csAddHPSC_->setEnabled(false);
        csAddAPSC_->setEnabled(false);
        csAddCCSC_->setEnabled(false);
        qsBeginSC_->setEnabled(true);
        qsAbandonSC_->setEnabled(false);
        qsHandInSC_->setEnabled(false);
    }
}

void GameLogic::setPlayerInventory()
{
    ui->lstInventory->clear();

    if(isBagOpen_)
    {
        bag_->clearInventory();
    }
    int itemAmount;
    QVector<Item> inventoryItems;
    QVector<ItemColor> itemNames;
    QVector<int> itemAmounts;
    ItemColor IC;

    inventoryItems = player_->getInventory();

    for (int x = 0; x < inventoryItems.length(); x++)
    {
        IC.name = inventoryItems.value(x).name;

        if (inventoryItems.value(x).itemRarity == 0 && inventoryItems.value(x).itemType == 9)
        {
            IC.colorCode = "#808080";
        }
        else if (inventoryItems.value(x).itemRarity == 0 && inventoryItems.value(x).itemType == 1)
        {
            IC.colorCode = "#FFFFFF";
        }
        else if (inventoryItems.value(x).itemRarity == 1)
        {
            IC.colorCode = "#FFFFFF";
        }
        else if (inventoryItems.value(x).itemRarity == 2)
        {
            IC.colorCode = "#00FF21";
        }
        else if (inventoryItems.value(x).itemRarity == 3)
        {
            IC.colorCode = "#0026FF";
        }
        else if (inventoryItems.value(x).itemRarity == 4)
        {
            IC.colorCode = "#B200FF";
        }
        else if (inventoryItems.value(x).itemRarity == 5)
        {
            IC.colorCode = "#FF5D00";
        }

        itemNames.push_back(IC);
    }

    //std::sort(loot_.begin(),loot_.end(), [](Item &left, Item &right){return left.dropWeight > right.dropWeight;});
    std::sort(itemNames.begin(), itemNames.end(),[](ItemColor &left, ItemColor &right){return left.name < right.name;});

    auto comp1 = [] ( const ItemColor& lhs, const ItemColor& rhs ) {return lhs.name == rhs.name;};
    auto last = std::unique(itemNames.begin(), itemNames.end(),comp1);
    itemNames.erase(last, itemNames.end());
    //itemNames.erase(std::unique(itemNames.begin(), itemNames.end()), itemNames.end());

    for (int z = 0; z < itemNames.length(); z++)
    {
        itemAmount = 0;
        for (int a = 0; a < inventoryItems.length(); a++)
        {
            if (itemNames.value(z).name == inventoryItems.value(a).name)
            {
                itemAmount++;
            }
        }
        itemAmounts.push_back(itemAmount);
    }

    for (int i = 0; i < itemNames.length(); i++)
    {
        ui->lstInventory->addItem(QString("%1").arg(itemNames.value(i).name));
        ui->lstInventory->item(i)->setBackgroundColor(itemNames.value(i).colorCode);

        if (itemNames.value(i).colorCode == "#0026FF")
            ui->lstInventory->item(i)->setTextColor("#FFFFFF");
    }

    setInventoryItemToolTip(itemNames);

    ui->btnUse->setEnabled(false);
    ui->btnEquip->setEnabled(false);
    ui->btnSell->setEnabled(false);
    ui->btnDrop->setEnabled(false);
}

void GameLogic::setPlayerEquipment()
{
    ui->lstEquipment->clear();

    QVector<Item> equipedItems;
    QVector<ItemColor> itemNames;
    ItemColor IC;

    equipedItems = player_->getEquiped();

    for (int x = 0; x < equipedItems.length(); x++)
    {
        IC.name = equipedItems.value(x).name;

        if (equipedItems.value(x).itemRarity == 0 && equipedItems.value(x).itemType == 9)
        {
            IC.colorCode = "#808080";
        }
        else if (equipedItems.value(x).itemRarity == 0 && equipedItems.value(x).itemType == 1)
        {
            IC.colorCode = "#FFFFFF";
        }
        else if (equipedItems.value(x).itemRarity == 1)
        {
            IC.colorCode = "#FFFFFF";
        }
        else if (equipedItems.value(x).itemRarity == 2)
        {
            IC.colorCode = "#00FF21";
        }
        else if (equipedItems.value(x).itemRarity == 3)
        {
            IC.colorCode = "#0026FF";
        }
        else if (equipedItems.value(x).itemRarity == 4)
        {
            IC.colorCode = "#B200FF";
        }
        else if (equipedItems.value(x).itemRarity == 5)
        {
            IC.colorCode = "#FF5D00";
        }

        itemNames.push_back(IC);
    }

    std::sort(itemNames.begin(), itemNames.end(),[](ItemColor &left, ItemColor &right){return left.name < right.name;});

    for (int i = 0; i < itemNames.length(); i++)
    {
        //ui->lstInventory->addItem(QString("%1 x%2\n").arg(itemNames.value(i)).arg(itemAmounts.value(i)));
        ui->lstEquipment->addItem(QString("%1").arg(itemNames.value(i).name));
        ui->lstEquipment->item(i)->setBackgroundColor(itemNames.value(i).colorCode);

        if (itemNames.value(i).colorCode == "#0026FF")
            ui->lstEquipment->item(i)->setTextColor("#FFFFFF");
    }

    setEquipmentItemToolTip(itemNames);
    setPlayerInventory();
    setPlayerInfo();

    ui->btnUse->setEnabled(false);
    ui->btnEquip->setEnabled(false);
    ui->btnSell->setEnabled(false);
    ui->btnDrop->setEnabled(false);
}

void GameLogic::setInventoryItemToolTip(QVector<ItemColor> listItems)
{
    int itemAmount;
    int itemIndex;
    QString itemInfo;
    QVector<Item> inventoryItems;

    inventoryItems = player_->getInventory();

    for (int i = 0; i < listItems.length(); i++)
    {
        itemAmount = 0;
        itemInfo = "";
        itemIndex = 0;

        for (int a = 0; a < inventoryItems.length(); a++)
        {
            if (listItems.value(i).name == inventoryItems.value(a).name)
            {
                itemAmount++;
                itemIndex = a;
            }
        }

        if (inventoryItems.value(itemIndex).itemType == 1 || inventoryItems.value(itemIndex).itemType == 0)
        {
            QString healType = "";

            if (inventoryItems.value(itemIndex).itemType == 1)
            {
                if (inventoryItems.value(itemIndex).healType == 1)
                    healType = "Health";
                else if (inventoryItems.value(itemIndex).healType == 2)
                    healType = "Stamina";

                itemInfo = QString("Type: %1\nUse: +%4 %5\nSell Price: %2G\nAmount: %3")
                        .arg(itemXRef->getItemType(inventoryItems.value(itemIndex).itemType))
                        .arg(inventoryItems.value(itemIndex).sellPrice).arg(itemAmount)
                        .arg(inventoryItems.value(itemIndex).healAmount).arg(healType);
            }
            else
            {
                itemInfo = QString("Type: %1\nRarity: %4\n\nSell Price: %2G\nAmount: %3")
                        .arg(itemXRef->getItemType(inventoryItems.value(itemIndex).itemType))
                        .arg(inventoryItems.value(itemIndex).sellPrice).arg(itemAmount)
                        .arg(itemXRef->getItemRarity(inventoryItems.value(itemIndex).itemRarity));
            }

        }
        else if (inventoryItems.value(itemIndex).itemType == 2)
        {
            if (inventoryItems.value(itemIndex).statType1 == 0 && inventoryItems.value(itemIndex).statType2 == 0 && inventoryItems.value(itemIndex).statType3 == 0)
            {
                itemInfo = QString("Type: %1\nEdge: %8\nRarity: %4\n%5\nDamage: %6-%7\n\nSell Price: %2G\nAmount: %3")
                        .arg(itemXRef->getItemType(inventoryItems.value(itemIndex).itemType))
                        .arg(inventoryItems.value(itemIndex).sellPrice).arg(itemAmount)
                        .arg(itemXRef->getItemRarity(inventoryItems.value(itemIndex).itemRarity))
                        .arg(itemXRef->getHoldType(inventoryItems.value(itemIndex).holdType))
                        .arg(inventoryItems.value(itemIndex).minAtk)
                        .arg(inventoryItems.value(itemIndex).maxAtk)
                        .arg(itemXRef->getWeaponEdgeType(inventoryItems.value(itemIndex).weaponEdgeType));
            }
            else if (inventoryItems.value(itemIndex).statType1 > 0 && inventoryItems.value(itemIndex).statType2 == 0 && inventoryItems.value(itemIndex).statType3 == 0)
            {
                itemInfo = QString("Type: %1\nEdge: %11\nRarity: %4\n%5\nDamage: %6-%7\nItem Stats:\n+%9 %10\n\nSell Price: %2G\nAmount: %3")
                        .arg(itemXRef->getItemType(inventoryItems.value(itemIndex).itemType))
                        .arg(inventoryItems.value(itemIndex).sellPrice).arg(itemAmount)
                        .arg(itemXRef->getItemRarity(inventoryItems.value(itemIndex).itemRarity))
                        .arg(itemXRef->getHoldType(inventoryItems.value(itemIndex).holdType))
                        .arg(inventoryItems.value(itemIndex).minAtk)
                        .arg(inventoryItems.value(itemIndex).maxAtk)
                        .arg(inventoryItems.value(itemIndex).stat1).arg(itemXRef->getStatType(inventoryItems.value(itemIndex).statType1))
                        .arg(itemXRef->getWeaponEdgeType(inventoryItems.value(itemIndex).weaponEdgeType));
            }
            else if (inventoryItems.value(itemIndex).statType1 > 0 && inventoryItems.value(itemIndex).statType2 > 0 && inventoryItems.value(itemIndex).statType3 == 0)
            {
                if (inventoryItems.value(itemIndex).statType1 == inventoryItems.value(itemIndex).statType2)
                {
                    itemInfo = QString("Type: %1\nEdge: %11\nRarity: %4\n%5\nDamage: %6-%7\nItem Stats:\n+%9 %10\n\nSell Price: %2G\nAmount: %3")
                            .arg(itemXRef->getItemType(inventoryItems.value(itemIndex).itemType))
                            .arg(inventoryItems.value(itemIndex).sellPrice).arg(itemAmount)
                            .arg(itemXRef->getItemRarity(inventoryItems.value(itemIndex).itemRarity))
                            .arg(itemXRef->getHoldType(inventoryItems.value(itemIndex).holdType))
                            .arg(inventoryItems.value(itemIndex).minAtk)
                            .arg(inventoryItems.value(itemIndex).maxAtk)
                            .arg(inventoryItems.value(itemIndex).stat1 + inventoryItems.value(itemIndex).stat2).arg(itemXRef->getStatType(inventoryItems.value(itemIndex).statType1))
                            .arg(itemXRef->getWeaponEdgeType(inventoryItems.value(itemIndex).weaponEdgeType));
                }
                else
                {
                    itemInfo = QString("Type: %1\nEdge: %12\nRarity: %4\n%5\nDamage: %6-%7\nItem Stats:\n+%8 %9\n+%10 %11\n\nSell Price: %2G\nAmount: %3")
                            .arg(itemXRef->getItemType(inventoryItems.value(itemIndex).itemType))
                            .arg(inventoryItems.value(itemIndex).sellPrice).arg(itemAmount)
                            .arg(itemXRef->getItemRarity(inventoryItems.value(itemIndex).itemRarity))
                            .arg(itemXRef->getHoldType(inventoryItems.value(itemIndex).holdType))
                            .arg(inventoryItems.value(itemIndex).minAtk)
                            .arg(inventoryItems.value(itemIndex).maxAtk)
                            .arg(inventoryItems.value(itemIndex).stat1).arg(itemXRef->getStatType(inventoryItems.value(itemIndex).statType1))
                            .arg(inventoryItems.value(itemIndex).stat2).arg(itemXRef->getStatType(inventoryItems.value(itemIndex).statType2))
                            .arg(itemXRef->getWeaponEdgeType(inventoryItems.value(itemIndex).weaponEdgeType));
                }
            }
            else if (inventoryItems.value(itemIndex).statType1 > 0 && inventoryItems.value(itemIndex).statType2 > 0 && inventoryItems.value(itemIndex).statType3 > 0)
            {
                itemInfo = QString("Type: %1\nEdge: %14Rarity: %4\n%5\nDamage: %6-%7\nItem Stats:\n+%8 %9\n+%10 %11\n+%12 %13\n\nSell Price: %2G\nAmount: %3")
                        .arg(itemXRef->getItemType(inventoryItems.value(itemIndex).itemType))
                        .arg(inventoryItems.value(itemIndex).sellPrice).arg(itemAmount)
                        .arg(itemXRef->getItemRarity(inventoryItems.value(itemIndex).itemRarity))
                        .arg(itemXRef->getHoldType(inventoryItems.value(itemIndex).holdType))
                        .arg(inventoryItems.value(itemIndex).minAtk)
                        .arg(inventoryItems.value(itemIndex).maxAtk)
                        .arg(inventoryItems.value(itemIndex).stat1).arg(itemXRef->getStatType(inventoryItems.value(itemIndex).statType1))
                        .arg(inventoryItems.value(itemIndex).stat2).arg(itemXRef->getStatType(inventoryItems.value(itemIndex).statType2))
                        .arg(inventoryItems.value(itemIndex).stat3).arg(itemXRef->getStatType(inventoryItems.value(itemIndex).statType3))
                        .arg(itemXRef->getWeaponEdgeType(inventoryItems.value(itemIndex).weaponEdgeType));
            }

        }
        else if (inventoryItems.value(itemIndex).itemType == 3)
        {
            if (inventoryItems.value(itemIndex).statType1 == 0 && inventoryItems.value(itemIndex).statType2 == 0 && inventoryItems.value(itemIndex).statType3 == 0)
            {
                itemInfo = QString("Type: %1\nRarity: %4\n%5\n+%6 Dodge\n\nSell Price: %2G\nAmount: %3")
                        .arg(itemXRef->getItemType(inventoryItems.value(itemIndex).itemType))
                        .arg(inventoryItems.value(itemIndex).sellPrice).arg(itemAmount)
                        .arg(itemXRef->getItemRarity(inventoryItems.value(itemIndex).itemRarity))
                        .arg(itemXRef->getArmourType(inventoryItems.value(itemIndex).armourType))
                        .arg(inventoryItems.value(itemIndex).armourRating);
            }
            else if (inventoryItems.value(itemIndex).statType1 > 0 && inventoryItems.value(itemIndex).statType2 == 0 && inventoryItems.value(itemIndex).statType3 == 0)
            {
                itemInfo = QString("Type: %1\nRarity: %4\n%5\n+%6 Dodge\nItem Stats:\n+%7 %8\n\nSell Price: %2G\nAmount: %3")
                        .arg(itemXRef->getItemType(inventoryItems.value(itemIndex).itemType))
                        .arg(inventoryItems.value(itemIndex).sellPrice).arg(itemAmount)
                        .arg(itemXRef->getItemRarity(inventoryItems.value(itemIndex).itemRarity))
                        .arg(itemXRef->getArmourType(inventoryItems.value(itemIndex).armourType))
                        .arg(inventoryItems.value(itemIndex).armourRating)
                        .arg(inventoryItems.value(itemIndex).stat1).arg(itemXRef->getStatType(inventoryItems.value(itemIndex).statType1));
            }
            else if (inventoryItems.value(itemIndex).statType1 > 0 && inventoryItems.value(itemIndex).statType2 > 0 && inventoryItems.value(itemIndex).statType3 == 0)
            {
                if (inventoryItems.value(itemIndex).statType1 == inventoryItems.value(itemIndex).statType2)
                {
                    itemInfo = QString("Type: %1\nRarity: %4\n%5\n+%6 Dodge\nItem Stats:\n+%7 %8\n\nSell Price: %2G\nAmount: %3")
                            .arg(itemXRef->getItemType(inventoryItems.value(itemIndex).itemType))
                            .arg(inventoryItems.value(itemIndex).sellPrice).arg(itemAmount)
                            .arg(itemXRef->getItemRarity(inventoryItems.value(itemIndex).itemRarity))
                            .arg(itemXRef->getArmourType(inventoryItems.value(itemIndex).armourType))
                            .arg(inventoryItems.value(itemIndex).armourRating)
                            .arg(inventoryItems.value(itemIndex).stat1 + inventoryItems.value(itemIndex).stat2).arg(itemXRef->getStatType(inventoryItems.value(itemIndex).statType1));
                }
                else
                {
                    itemInfo = QString("Type: %1\nRarity: %4\n%5\n+%6 Dodge\nItem Stats:\n+%7 %8\n+%9 %10\n\nSell Price: %2G\nAmount: %3")
                            .arg(itemXRef->getItemType(inventoryItems.value(itemIndex).itemType))
                            .arg(inventoryItems.value(itemIndex).sellPrice).arg(itemAmount)
                            .arg(itemXRef->getItemRarity(inventoryItems.value(itemIndex).itemRarity))
                            .arg(itemXRef->getArmourType(inventoryItems.value(itemIndex).armourType))
                            .arg(inventoryItems.value(itemIndex).armourRating)
                            .arg(inventoryItems.value(itemIndex).stat1).arg(itemXRef->getStatType(inventoryItems.value(itemIndex).statType1))
                            .arg(inventoryItems.value(itemIndex).stat2).arg(itemXRef->getStatType(inventoryItems.value(itemIndex).statType2));
                }
            }
            else if (inventoryItems.value(itemIndex).statType1 > 0 && inventoryItems.value(itemIndex).statType2 > 0 && inventoryItems.value(itemIndex).statType3 > 0)
            {
                itemInfo = QString("Type: %1\nRarity: %4\n%5\n+%6 Dodge\nItem Stats:\n+%7 %8\n+%9 %10\n+%11 %12\n\nSell Price: %2G\nAmount: %3")
                        .arg(itemXRef->getItemType(inventoryItems.value(itemIndex).itemType))
                        .arg(inventoryItems.value(itemIndex).sellPrice).arg(itemAmount)
                        .arg(itemXRef->getItemRarity(inventoryItems.value(itemIndex).itemRarity))
                        .arg(itemXRef->getArmourType(inventoryItems.value(itemIndex).armourType))
                        .arg(inventoryItems.value(itemIndex).armourRating)
                        .arg(inventoryItems.value(itemIndex).stat1).arg(itemXRef->getStatType(inventoryItems.value(itemIndex).statType1))
                        .arg(inventoryItems.value(itemIndex).stat2).arg(itemXRef->getStatType(inventoryItems.value(itemIndex).statType2))
                        .arg(inventoryItems.value(itemIndex).stat3).arg(itemXRef->getStatType(inventoryItems.value(itemIndex).statType3));
            }
        }
        else if (inventoryItems.value(itemIndex).itemType == 4)
        {
            if (inventoryItems.value(itemIndex).statType1 == 0 && inventoryItems.value(itemIndex).statType2 == 0 && inventoryItems.value(itemIndex).statType3 == 0)
            {
                itemInfo = QString("Type: %1\nRarity: %4\nItem Stats:\n+%5 Block\n\nSell Price: %2G\nAmount: %3")
                        .arg(itemXRef->getItemType(inventoryItems.value(itemIndex).itemType))
                        .arg(inventoryItems.value(itemIndex).sellPrice).arg(itemAmount)
                        .arg(itemXRef->getItemRarity(inventoryItems.value(itemIndex).itemRarity))
                        .arg(inventoryItems.value(itemIndex).block);
            }
            else if (inventoryItems.value(itemIndex).statType1 > 0 && inventoryItems.value(itemIndex).statType2 == 0 && inventoryItems.value(itemIndex).statType3 == 0)
            {
                itemInfo = QString("Type: %1\nRarity: %4\nItem Stats:\n+%5 Block\n+%6 %7\n\nSell Price: %2G\nAmount: %3")
                        .arg(itemXRef->getItemType(inventoryItems.value(itemIndex).itemType))
                        .arg(inventoryItems.value(itemIndex).sellPrice).arg(itemAmount)
                        .arg(itemXRef->getItemRarity(inventoryItems.value(itemIndex).itemRarity))
                        .arg(inventoryItems.value(itemIndex).block)
                        .arg(inventoryItems.value(itemIndex).stat1).arg(itemXRef->getStatType(inventoryItems.value(itemIndex).statType1));
            }
            else if (inventoryItems.value(itemIndex).statType1 > 0 && inventoryItems.value(itemIndex).statType2 > 0 && inventoryItems.value(itemIndex).statType3 == 0)
            {
                if (inventoryItems.value(itemIndex).statType1 == inventoryItems.value(itemIndex).statType2)
                {
                    itemInfo = QString("Type: %1\nRarity: %4\nItem Stats:\n+%5 Block\n+%6 %7\n\nSell Price: %2G\nAmount: %3")
                            .arg(itemXRef->getItemType(inventoryItems.value(itemIndex).itemType))
                            .arg(inventoryItems.value(itemIndex).sellPrice).arg(itemAmount)
                            .arg(itemXRef->getItemRarity(inventoryItems.value(itemIndex).itemRarity))
                            .arg(inventoryItems.value(itemIndex).block)
                            .arg(inventoryItems.value(itemIndex).stat1 + inventoryItems.value(itemIndex).stat2).arg(itemXRef->getStatType(inventoryItems.value(itemIndex).statType1));
                }
                else
                {
                    itemInfo = QString("Type: %1\nRarity: %4\nItem Stats:\n+%5 Block\n+%6 %7\n+%8 %10\n\nSell Price: %2G\nAmount: %3")
                            .arg(itemXRef->getItemType(inventoryItems.value(itemIndex).itemType))
                            .arg(inventoryItems.value(itemIndex).sellPrice).arg(itemAmount)
                            .arg(itemXRef->getItemRarity(inventoryItems.value(itemIndex).itemRarity))
                            .arg(inventoryItems.value(itemIndex).block)
                            .arg(inventoryItems.value(itemIndex).stat1).arg(itemXRef->getStatType(inventoryItems.value(itemIndex).statType1))
                            .arg(inventoryItems.value(itemIndex).stat2).arg(itemXRef->getStatType(inventoryItems.value(itemIndex).statType2));

                }
            }
            else if (inventoryItems.value(itemIndex).statType1 > 0 && inventoryItems.value(itemIndex).statType2 > 0 && inventoryItems.value(itemIndex).statType3 > 0)
            {
                itemInfo = QString("Type: %1\nRarity: %4\nItem Stats:\n+%5 Block\n+%6 %7\n+%8 %9\n+%10 %11\n\nSell Price: %2G\nAmount: %3")
                        .arg(itemXRef->getItemType(inventoryItems.value(itemIndex).itemType))
                        .arg(inventoryItems.value(itemIndex).sellPrice).arg(itemAmount)
                        .arg(itemXRef->getItemRarity(inventoryItems.value(itemIndex).itemRarity))
                        .arg(inventoryItems.value(itemIndex).block)
                        .arg(inventoryItems.value(itemIndex).stat1).arg(itemXRef->getStatType(inventoryItems.value(itemIndex).statType1))
                        .arg(inventoryItems.value(itemIndex).stat2).arg(itemXRef->getStatType(inventoryItems.value(itemIndex).statType2))
                        .arg(inventoryItems.value(itemIndex).stat3).arg(itemXRef->getStatType(inventoryItems.value(itemIndex).statType3));
            }
        }
        else if (inventoryItems.value(itemIndex).itemType == 5)
        {
            //fill in later when you have actual quest items
        }
        else if (inventoryItems.value(itemIndex).itemType == 6 || inventoryItems.value(itemIndex).itemType == 7)
        {
            if (inventoryItems.value(itemIndex).statType1 == 0 && inventoryItems.value(itemIndex).statType2 == 0 && inventoryItems.value(itemIndex).statType3 == 0)
            {
                itemInfo = QString("Type: %1\nRarity: %4\n\nSell Price: %2G\nAmount: %3")
                        .arg(itemXRef->getItemType(inventoryItems.value(itemIndex).itemType))
                        .arg(inventoryItems.value(itemIndex).sellPrice).arg(itemAmount)
                        .arg(itemXRef->getItemRarity(inventoryItems.value(itemIndex).itemRarity));
            }
            else if (inventoryItems.value(itemIndex).statType1 > 0 && inventoryItems.value(itemIndex).statType2 == 0 && inventoryItems.value(itemIndex).statType3 == 0)
            {
                itemInfo = QString("Type: %1\nRarity: %4\nItem Stats:\n+%5 %6\n\nSell Price: %2G\nAmount: %3")
                        .arg(itemXRef->getItemType(inventoryItems.value(itemIndex).itemType))
                        .arg(inventoryItems.value(itemIndex).sellPrice).arg(itemAmount)
                        .arg(itemXRef->getItemRarity(inventoryItems.value(itemIndex).itemRarity))
                        .arg(inventoryItems.value(itemIndex).stat1).arg(itemXRef->getStatType(inventoryItems.value(itemIndex).statType1));
            }
            else if (inventoryItems.value(itemIndex).statType1 > 0 && inventoryItems.value(itemIndex).statType2 > 0 && inventoryItems.value(itemIndex).statType3 == 0)
            {
                if (inventoryItems.value(itemIndex).statType1 == inventoryItems.value(itemIndex).statType2)
                {
                    itemInfo = QString("Type: %1\nRarity: %4\nItem Stats:\n+%5 %6\n\nSell Price: %2G\nAmount: %3")
                            .arg(itemXRef->getItemType(inventoryItems.value(itemIndex).itemType))
                            .arg(inventoryItems.value(itemIndex).sellPrice).arg(itemAmount)
                            .arg(itemXRef->getItemRarity(inventoryItems.value(itemIndex).itemRarity))
                            .arg(inventoryItems.value(itemIndex).stat1 + inventoryItems.value(itemIndex).stat2).arg(itemXRef->getStatType(inventoryItems.value(itemIndex).statType1));
                }
                else
                {
                    itemInfo = QString("Type: %1\nRarity: %4\nItem Stats:\n+%5 %6\n+%7 %8\n\nSell Price: %2G\nAmount: %3")
                            .arg(itemXRef->getItemType(inventoryItems.value(itemIndex).itemType))
                            .arg(inventoryItems.value(itemIndex).sellPrice).arg(itemAmount)
                            .arg(itemXRef->getItemRarity(inventoryItems.value(itemIndex).itemRarity))
                            .arg(inventoryItems.value(itemIndex).stat1).arg(itemXRef->getStatType(inventoryItems.value(itemIndex).statType1))
                            .arg(inventoryItems.value(itemIndex).stat2).arg(itemXRef->getStatType(inventoryItems.value(itemIndex).statType2));
                }
            }
            else if (inventoryItems.value(itemIndex).statType1 > 0 && inventoryItems.value(itemIndex).statType2 > 0 && inventoryItems.value(itemIndex).statType3 > 0)
            {
                itemInfo = QString("Type: %1\nRarity: %4\nItem Stats:\n+%5 %6\n+%7 %8\n+%9 %10\n\nSell Price: %2G\nAmount: %3")
                        .arg(itemXRef->getItemType(inventoryItems.value(itemIndex).itemType))
                        .arg(inventoryItems.value(itemIndex).sellPrice).arg(itemAmount)
                        .arg(itemXRef->getItemRarity(inventoryItems.value(itemIndex).itemRarity))
                        .arg(inventoryItems.value(itemIndex).stat1).arg(itemXRef->getStatType(inventoryItems.value(itemIndex).statType1))
                        .arg(inventoryItems.value(itemIndex).stat2).arg(itemXRef->getStatType(inventoryItems.value(itemIndex).statType2))
                        .arg(inventoryItems.value(itemIndex).stat3).arg(itemXRef->getStatType(inventoryItems.value(itemIndex).statType3));
            }
        }
        else if (inventoryItems.value(itemIndex).itemType == 9)
        {
            itemInfo = QString("Type: %1\nSell Price: %2G\nAmount: %3")
                    .arg(itemXRef->getItemType(inventoryItems.value(itemIndex).itemType))
                    .arg(inventoryItems.value(itemIndex).sellPrice).arg(itemAmount);
        }

        //item->setToolTip(itemInfo);
        ui->lstInventory->item(i)->setToolTip(itemInfo);
    }
}

void GameLogic::setEquipmentItemToolTip(QVector<ItemColor> listItems)
{
    int itemIndex;
    QString itemInfo;
    QVector<Item> equippedItems;

    equippedItems = player_->getEquiped();

    for (int i = 0; i < listItems.length(); i++)
    {
        itemInfo = "";
        itemIndex = 0;

        for (int a = 0; a < equippedItems.length(); a++)
        {
            if (listItems.value(i).name == equippedItems.value(a).name)
            {
                itemIndex = a;
            }
        }

        if (equippedItems.value(itemIndex).itemType == 2)
        {
            if (equippedItems.value(itemIndex).statType1 == 0 && equippedItems.value(itemIndex).statType2 == 0 && equippedItems.value(itemIndex).statType3 == 0)
            {
                itemInfo = QString("Type: %1\nEdge: %7\nRarity: %3\n%4\nDamage: %5-%6\n\nSell Price: %2G")
                        .arg(itemXRef->getItemType(equippedItems.value(itemIndex).itemType))
                        .arg(equippedItems.value(itemIndex).sellPrice)
                        .arg(itemXRef->getItemRarity(equippedItems.value(itemIndex).itemRarity))
                        .arg(itemXRef->getHoldType(equippedItems.value(itemIndex).holdType))
                        .arg(equippedItems.value(itemIndex).minAtk)
                        .arg(equippedItems.value(itemIndex).maxAtk)
                        .arg(itemXRef->getWeaponEdgeType(equippedItems.value(itemIndex).weaponEdgeType));
            }
            else if (equippedItems.value(itemIndex).statType1 > 0 && equippedItems.value(itemIndex).statType2 == 0 && equippedItems.value(itemIndex).statType3 == 0)
            {
                itemInfo = QString("Type: %1\nEdge: %9\nRarity: %3\n%4\nDamage: %5-%6\nItem Stats:\n+%7 %8\n\nSell Price: %2G")
                        .arg(itemXRef->getItemType(equippedItems.value(itemIndex).itemType))
                        .arg(equippedItems.value(itemIndex).sellPrice)
                        .arg(itemXRef->getItemRarity(equippedItems.value(itemIndex).itemRarity))
                        .arg(itemXRef->getHoldType(equippedItems.value(itemIndex).holdType))
                        .arg(equippedItems.value(itemIndex).minAtk)
                        .arg(equippedItems.value(itemIndex).maxAtk)
                        .arg(equippedItems.value(itemIndex).stat1).arg(itemXRef->getStatType(equippedItems.value(itemIndex).statType1))
                        .arg(itemXRef->getWeaponEdgeType(equippedItems.value(itemIndex).weaponEdgeType));
            }
            else if (equippedItems.value(itemIndex).statType1 > 0 && equippedItems.value(itemIndex).statType2 > 0 && equippedItems.value(itemIndex).statType3 == 0)
            {
                if (equippedItems.value(itemIndex).statType1 == equippedItems.value(itemIndex).statType2)
                {
                    itemInfo = QString("Type: %1\nEdge: %9\nRarity: %3\n%4\nDamage: %5-%6\nItem Stats:\n+%7 %8\n\nSell Price: %2G")
                            .arg(itemXRef->getItemType(equippedItems.value(itemIndex).itemType))
                            .arg(equippedItems.value(itemIndex).sellPrice)
                            .arg(itemXRef->getItemRarity(equippedItems.value(itemIndex).itemRarity))
                            .arg(itemXRef->getHoldType(equippedItems.value(itemIndex).holdType))
                            .arg(equippedItems.value(itemIndex).minAtk)
                            .arg(equippedItems.value(itemIndex).maxAtk)
                            .arg(equippedItems.value(itemIndex).stat1 + equippedItems.value(itemIndex).stat2).arg(itemXRef->getStatType(equippedItems.value(itemIndex).statType1))
                            .arg(itemXRef->getWeaponEdgeType(equippedItems.value(itemIndex).weaponEdgeType));
                }
                else
                {
                    itemInfo = QString("Type: %1\nEdge: %11\nRarity: %3\n%4\nDamage: %5-%6\nItem Stats:\n+%7 %8\n+%9 %10\n\nSell Price: %2G")
                            .arg(itemXRef->getItemType(equippedItems.value(itemIndex).itemType))
                            .arg(equippedItems.value(itemIndex).sellPrice)
                            .arg(itemXRef->getItemRarity(equippedItems.value(itemIndex).itemRarity))
                            .arg(itemXRef->getHoldType(equippedItems.value(itemIndex).holdType))
                            .arg(equippedItems.value(itemIndex).minAtk)
                            .arg(equippedItems.value(itemIndex).maxAtk)
                            .arg(equippedItems.value(itemIndex).stat1).arg(itemXRef->getStatType(equippedItems.value(itemIndex).statType1))
                            .arg(equippedItems.value(itemIndex).stat2).arg(itemXRef->getStatType(equippedItems.value(itemIndex).statType2))
                            .arg(itemXRef->getWeaponEdgeType(equippedItems.value(itemIndex).weaponEdgeType));
                }
            }
            else if (equippedItems.value(itemIndex).statType1 > 0 && equippedItems.value(itemIndex).statType2 > 0 && equippedItems.value(itemIndex).statType3 > 0)
            {
                itemInfo = QString("Type: %1\nEdge: %13Rarity: %3\n%4\nDamage: %5-%6\nItem Stats:\n+%7 %8\n+%9 %10\n+%11 %12\n\nSell Price: %2G")
                        .arg(itemXRef->getItemType(equippedItems.value(itemIndex).itemType))
                        .arg(equippedItems.value(itemIndex).sellPrice)
                        .arg(itemXRef->getItemRarity(equippedItems.value(itemIndex).itemRarity))
                        .arg(itemXRef->getHoldType(equippedItems.value(itemIndex).holdType))
                        .arg(equippedItems.value(itemIndex).minAtk)
                        .arg(equippedItems.value(itemIndex).maxAtk)
                        .arg(equippedItems.value(itemIndex).stat1).arg(itemXRef->getStatType(equippedItems.value(itemIndex).statType1))
                        .arg(equippedItems.value(itemIndex).stat2).arg(itemXRef->getStatType(equippedItems.value(itemIndex).statType2))
                        .arg(equippedItems.value(itemIndex).stat3).arg(itemXRef->getStatType(equippedItems.value(itemIndex).statType3))
                        .arg(itemXRef->getWeaponEdgeType(equippedItems.value(itemIndex).weaponEdgeType));
            }

        }
        else if (equippedItems.value(itemIndex).itemType == 3)
                {
                    if (equippedItems.value(itemIndex).statType1 == 0 && equippedItems.value(itemIndex).statType2 == 0 && equippedItems.value(itemIndex).statType3 == 0)
                    {
                        itemInfo = QString("Type: %1\nRarity: %3\n%4\n+%5 Dodge\n\nSell Price: %2G")
                                .arg(itemXRef->getItemType(equippedItems.value(itemIndex).itemType))
                                .arg(equippedItems.value(itemIndex).sellPrice)
                                .arg(itemXRef->getItemRarity(equippedItems.value(itemIndex).itemRarity))
                                .arg(itemXRef->getArmourType(equippedItems.value(itemIndex).armourType))
                                .arg(equippedItems.value(itemIndex).armourRating);
                    }
                    else if (equippedItems.value(itemIndex).statType1 > 0 && equippedItems.value(itemIndex).statType2 == 0 && equippedItems.value(itemIndex).statType3 == 0)
                    {
                        itemInfo = QString("Type: %1\nRarity: %3\n%4\n+%5 Dodge\nItem Stats:\n+%6 %7\n\nSell Price: %2G")
                                .arg(itemXRef->getItemType(equippedItems.value(itemIndex).itemType))
                                .arg(equippedItems.value(itemIndex).sellPrice)
                                .arg(itemXRef->getItemRarity(equippedItems.value(itemIndex).itemRarity))
                                .arg(itemXRef->getArmourType(equippedItems.value(itemIndex).armourType))
                                .arg(equippedItems.value(itemIndex).armourRating)
                                .arg(equippedItems.value(itemIndex).stat1).arg(itemXRef->getStatType(equippedItems.value(itemIndex).statType1));
                    }
                    else if (equippedItems.value(itemIndex).statType1 > 0 && equippedItems.value(itemIndex).statType2 > 0 && equippedItems.value(itemIndex).statType3 == 0)
                    {
                        if (equippedItems.value(itemIndex).statType1 == equippedItems.value(itemIndex).statType2)
                        {
                            itemInfo = QString("Type: %1\nRarity: %3\n%4\n+%5 Dodge\nItem Stats:\n+%6 %7\n\nSell Price: %2G")
                                    .arg(itemXRef->getItemType(equippedItems.value(itemIndex).itemType))
                                    .arg(equippedItems.value(itemIndex).sellPrice)
                                    .arg(itemXRef->getItemRarity(equippedItems.value(itemIndex).itemRarity))
                                    .arg(itemXRef->getArmourType(equippedItems.value(itemIndex).armourType))
                                    .arg(equippedItems.value(itemIndex).armourRating)
                                    .arg(equippedItems.value(itemIndex).stat1 + equippedItems.value(itemIndex).stat2).arg(itemXRef->getStatType(equippedItems.value(itemIndex).statType1));
                        }
                        else
                        {
                            itemInfo = QString("Type: %1\nRarity: %3\n%4\n+%5 Dodge\nItem Stats:\n+%6 %7\n+%8 %9\n\nSell Price: %2G")
                                    .arg(itemXRef->getItemType(equippedItems.value(itemIndex).itemType))
                                    .arg(equippedItems.value(itemIndex).sellPrice)
                                    .arg(itemXRef->getItemRarity(equippedItems.value(itemIndex).itemRarity))
                                    .arg(itemXRef->getArmourType(equippedItems.value(itemIndex).armourType))
                                    .arg(equippedItems.value(itemIndex).armourRating)
                                    .arg(equippedItems.value(itemIndex).stat1).arg(itemXRef->getStatType(equippedItems.value(itemIndex).statType1))
                                    .arg(equippedItems.value(itemIndex).stat2).arg(itemXRef->getStatType(equippedItems.value(itemIndex).statType2));
                        }
                    }
                    else if (equippedItems.value(itemIndex).statType1 > 0 && equippedItems.value(itemIndex).statType2 > 0 && equippedItems.value(itemIndex).statType3 > 0)
                    {
                        itemInfo = QString("Type: %1\nRarity: %3\n%4\n+%5 Dodge\nItem Stats:\n+%6 %7\n+%8 %9\n+%10 %11\n\nSell Price: %2G")
                                .arg(itemXRef->getItemType(equippedItems.value(itemIndex).itemType))
                                .arg(equippedItems.value(itemIndex).sellPrice)
                                .arg(itemXRef->getItemRarity(equippedItems.value(itemIndex).itemRarity))
                                .arg(itemXRef->getArmourType(equippedItems.value(itemIndex).armourType))
                                .arg(equippedItems.value(itemIndex).armourRating)
                                .arg(equippedItems.value(itemIndex).stat1).arg(itemXRef->getStatType(equippedItems.value(itemIndex).statType1))
                                .arg(equippedItems.value(itemIndex).stat2).arg(itemXRef->getStatType(equippedItems.value(itemIndex).statType2))
                                .arg(equippedItems.value(itemIndex).stat3).arg(itemXRef->getStatType(equippedItems.value(itemIndex).statType3));
                    }
                }
                else if (equippedItems.value(itemIndex).itemType == 4)
                {
                    if (equippedItems.value(itemIndex).statType1 == 0 && equippedItems.value(itemIndex).statType2 == 0 && equippedItems.value(itemIndex).statType3 == 0)
                    {
                        itemInfo = QString("Type: %1\nRarity: %3\nItem Stats:\n+%4 Block\n\nSell Price: %2G")
                                .arg(itemXRef->getItemType(equippedItems.value(itemIndex).itemType))
                                .arg(equippedItems.value(itemIndex).sellPrice)
                                .arg(itemXRef->getItemRarity(equippedItems.value(itemIndex).itemRarity))
                                .arg(equippedItems.value(itemIndex).block);
                    }
                    else if (equippedItems.value(itemIndex).statType1 > 0 && equippedItems.value(itemIndex).statType2 == 0 && equippedItems.value(itemIndex).statType3 == 0)
                    {
                        itemInfo = QString("Type: %1\nRarity: %3\nItem Stats:\n+%4 Block\n+%5 %6\n\nSell Price: %2G")
                                .arg(itemXRef->getItemType(equippedItems.value(itemIndex).itemType))
                                .arg(equippedItems.value(itemIndex).sellPrice)
                                .arg(itemXRef->getItemRarity(equippedItems.value(itemIndex).itemRarity))
                                .arg(equippedItems.value(itemIndex).block)
                                .arg(equippedItems.value(itemIndex).stat1).arg(itemXRef->getStatType(equippedItems.value(itemIndex).statType1));
                    }
                    else if (equippedItems.value(itemIndex).statType1 > 0 && equippedItems.value(itemIndex).statType2 > 0 && equippedItems.value(itemIndex).statType3 == 0)
                    {
                        if (equippedItems.value(itemIndex).statType1 == equippedItems.value(itemIndex).statType2)
                        {
                            itemInfo = QString("Type: %1\nRarity: %3\nItem Stats:\n+%4 Block\n+%5 %6\n\nSell Price: %2G")
                                    .arg(itemXRef->getItemType(equippedItems.value(itemIndex).itemType))
                                    .arg(equippedItems.value(itemIndex).sellPrice)
                                    .arg(itemXRef->getItemRarity(equippedItems.value(itemIndex).itemRarity))
                                    .arg(equippedItems.value(itemIndex).block)
                                    .arg(equippedItems.value(itemIndex).stat1 + equippedItems.value(itemIndex).stat2).arg(itemXRef->getStatType(equippedItems.value(itemIndex).statType1));
                        }
                        else
                        {
                            itemInfo = QString("Type: %1\nRarity: %3\nItem Stats:\n+%4 Block\n+%5 %6\n+%7 %8\n\nSell Price: %2G")
                                    .arg(itemXRef->getItemType(equippedItems.value(itemIndex).itemType))
                                    .arg(equippedItems.value(itemIndex).sellPrice)
                                    .arg(itemXRef->getItemRarity(equippedItems.value(itemIndex).itemRarity))
                                    .arg(equippedItems.value(itemIndex).block)
                                    .arg(equippedItems.value(itemIndex).stat1).arg(itemXRef->getStatType(equippedItems.value(itemIndex).statType1))
                                    .arg(equippedItems.value(itemIndex).stat2).arg(itemXRef->getStatType(equippedItems.value(itemIndex).statType2));

                        }
                    }
                    else if (equippedItems.value(itemIndex).statType1 > 0 && equippedItems.value(itemIndex).statType2 > 0 && equippedItems.value(itemIndex).statType3 > 0)
                    {
                        itemInfo = QString("Type: %1\nRarity: %3\nItem Stats:\n+%4 Block\n+%5 %6\n+%7 %8\n+%9 %10\n\nSell Price: %2G")
                                .arg(itemXRef->getItemType(equippedItems.value(itemIndex).itemType))
                                .arg(equippedItems.value(itemIndex).sellPrice)
                                .arg(itemXRef->getItemRarity(equippedItems.value(itemIndex).itemRarity))
                                .arg(equippedItems.value(itemIndex).block)
                                .arg(equippedItems.value(itemIndex).stat1).arg(itemXRef->getStatType(equippedItems.value(itemIndex).statType1))
                                .arg(equippedItems.value(itemIndex).stat2).arg(itemXRef->getStatType(equippedItems.value(itemIndex).statType2))
                                .arg(equippedItems.value(itemIndex).stat3).arg(itemXRef->getStatType(equippedItems.value(itemIndex).statType3));
                    }
                }
                else if (equippedItems.value(itemIndex).itemType == 6 || equippedItems.value(itemIndex).itemType == 7)
                {
                    if (equippedItems.value(itemIndex).statType1 == 0 && equippedItems.value(itemIndex).statType2 == 0 && equippedItems.value(itemIndex).statType3 == 0)
                    {
                        itemInfo = QString("Type: %1\nRarity: %3\n\nSell Price: %2G")
                                .arg(itemXRef->getItemType(equippedItems.value(itemIndex).itemType))
                                .arg(equippedItems.value(itemIndex).sellPrice)
                                .arg(itemXRef->getItemRarity(equippedItems.value(itemIndex).itemRarity));
                    }
                    else if (equippedItems.value(itemIndex).statType1 > 0 && equippedItems.value(itemIndex).statType2 == 0 && equippedItems.value(itemIndex).statType3 == 0)
                    {
                        itemInfo = QString("Type: %1\nRarity: %3\nItem Stats:\n+%4 %5\n\nSell Price: %2G")
                                .arg(itemXRef->getItemType(equippedItems.value(itemIndex).itemType))
                                .arg(equippedItems.value(itemIndex).sellPrice)
                                .arg(itemXRef->getItemRarity(equippedItems.value(itemIndex).itemRarity))
                                .arg(equippedItems.value(itemIndex).stat1).arg(itemXRef->getStatType(equippedItems.value(itemIndex).statType1));
                    }
                    else if (equippedItems.value(itemIndex).statType1 > 0 && equippedItems.value(itemIndex).statType2 > 0 && equippedItems.value(itemIndex).statType3 == 0)
                    {
                        if (equippedItems.value(itemIndex).statType1 == equippedItems.value(itemIndex).statType2)
                        {
                            itemInfo = QString("Type: %1\nRarity: %3\nItem Stats:\n+%4 %5\n\nSell Price: %2G")
                                    .arg(itemXRef->getItemType(equippedItems.value(itemIndex).itemType))
                                    .arg(equippedItems.value(itemIndex).sellPrice)
                                    .arg(itemXRef->getItemRarity(equippedItems.value(itemIndex).itemRarity))
                                    .arg(equippedItems.value(itemIndex).stat1 + equippedItems.value(itemIndex).stat2).arg(itemXRef->getStatType(equippedItems.value(itemIndex).statType1));
                        }
                        else
                        {
                            itemInfo = QString("Type: %1\nRarity: %3\nItem Stats:\n+%4 %5\n+%6 %7\n\nSell Price: %2G")
                                    .arg(itemXRef->getItemType(equippedItems.value(itemIndex).itemType))
                                    .arg(equippedItems.value(itemIndex).sellPrice)
                                    .arg(itemXRef->getItemRarity(equippedItems.value(itemIndex).itemRarity))
                                    .arg(equippedItems.value(itemIndex).stat1).arg(itemXRef->getStatType(equippedItems.value(itemIndex).statType1))
                                    .arg(equippedItems.value(itemIndex).stat2).arg(itemXRef->getStatType(equippedItems.value(itemIndex).statType2));
                        }
                    }
                    else if (equippedItems.value(itemIndex).statType1 > 0 && equippedItems.value(itemIndex).statType2 > 0 && equippedItems.value(itemIndex).statType3 > 0)
                    {
                        itemInfo = QString("Type: %1\nRarity: %3\nItem Stats:\n+%4 %5\n+%6 %7\n+%8 %9\n\nSell Price: %2G")
                                .arg(itemXRef->getItemType(equippedItems.value(itemIndex).itemType))
                                .arg(equippedItems.value(itemIndex).sellPrice)
                                .arg(itemXRef->getItemRarity(equippedItems.value(itemIndex).itemRarity))
                                .arg(equippedItems.value(itemIndex).stat1).arg(itemXRef->getStatType(equippedItems.value(itemIndex).statType1))
                                .arg(equippedItems.value(itemIndex).stat2).arg(itemXRef->getStatType(equippedItems.value(itemIndex).statType2))
                                .arg(equippedItems.value(itemIndex).stat3).arg(itemXRef->getStatType(equippedItems.value(itemIndex).statType3));
                    }
                }

        //item->setToolTip(itemInfo);
        ui->lstEquipment->item(i)->setToolTip(itemInfo);
    }
}

void GameLogic::on_lstInventory_itemClicked(QListWidgetItem *item)
{
    int itemIndex;
    QVector<Item> inventoryItems;

    inventoryItems = player_->getInventory();

    for (int a = 0; a < inventoryItems.length(); a++)
    {
        if (item->text() == inventoryItems.value(a).name)
        {
            itemIndex = a;
        }
    }

    if (inventoryItems.value(itemIndex).itemType == 1)
    {
        ui->btnUse->setEnabled(true);
        ui->btnEquip->setEnabled(false);
        ui->btnSell->setEnabled(true);
        ui->btnDrop->setEnabled(true);
    }
    else if (inventoryItems.value(itemIndex).itemType == 2 ||
             inventoryItems.value(itemIndex).itemType == 3 ||
             inventoryItems.value(itemIndex).itemType == 4 ||
             inventoryItems.value(itemIndex).itemType == 6 ||
             inventoryItems.value(itemIndex).itemType == 7)
    {
        ui->btnUse->setEnabled(false);
        ui->btnEquip->setText("Equip");
        ui->btnEquip->setEnabled(true);
        ui->btnSell->setEnabled(true);
        ui->btnDrop->setEnabled(true);
    }
    else if (inventoryItems.value(itemIndex).itemType == 5)
    {
        ui->btnUse->setEnabled(false);
        ui->btnEquip->setEnabled(false);
        ui->btnSell->setEnabled(false);
        ui->btnDrop->setEnabled(false);
    }
    else if (inventoryItems.value(itemIndex).itemType == 9)
    {
        ui->btnUse->setEnabled(false);
        ui->btnEquip->setEnabled(false);
        ui->btnSell->setEnabled(true);
        ui->btnDrop->setEnabled(true);
    }
}

void GameLogic::on_lstInventory_doubleClicked(const QModelIndex &index)
{
    int itemIndex;
    QString itemName;
    QVector<Item> inventoryItems;

    inventoryItems = player_->getInventory();
    itemName = ui->lstInventory->currentItem()->text();

    for (int x = 0; x < inventoryItems.length(); x++)
    {
        if (itemName == inventoryItems.value(x).name)
        {
            itemIndex = x;
        }
    }

    if (inventoryItems.value(itemIndex).isEquippable)
    {
        equipItem();
    }
    else
    {
        if (inventoryItems.value(itemIndex).itemType == 1)
        {
            useItem();
        }
        else if (inventoryItems.value(itemIndex).itemType == 9)
        {
           sellItem();
        }
    }
}

void GameLogic::on_lstEquipment_itemDoubleClicked(QListWidgetItem *item)
{
    unequipItem();
}

void GameLogic::on_btnUse_clicked()
{
    useItem();
}

void GameLogic::on_btnEquip_clicked()
{
    if (ui->btnEquip->text().toUpper() == "EQUIP")
    {
        equipItem();
    }
    else if (ui->btnEquip->text().toUpper() == "UNEQUIP")
    {
        unequipItem();
    }
}

void GameLogic::on_btnSell_clicked()
{
    sellItem();
}

void GameLogic::on_btnDrop_clicked()
{
    int itemIndex;
    QVector<Item> inventoryItems;
    QString item = ui->lstInventory->currentItem()->text();

    inventoryItems = player_->getInventory();

    for (int a = 0; a < inventoryItems.length(); a++)
    {
        if (item == inventoryItems.value(a).name)
        {
            itemIndex = a;
        }
    }

    player_->removeItemFromInventory(itemIndex);
    setPlayerInfo();
    setPlayerInventory();
}


void GameLogic::on_lstEquipment_itemClicked(QListWidgetItem *item)
{
    ui->btnEquip->setText("Unequip");
    ui->btnEquip->setEnabled(true);
}


void GameLogic::on_btnBuyBedroll_clicked()
{
    if (player_->getGold() >= 250)
    {
        if (strRestLocation_[player_->getLocation()] == "City" ||strRestLocation_[player_->getLocation()] == "Town")
        {
            Item item;
            //numItems.push_back(banditItemDrops_[e][0]);

            item.name = "Bedroll";
            item.itemRarity = 1;
            item.itemType = 0;
            item.armourRating = 0;
            item.armourType = 0;
            item.healType = 0;
            item.healAmount = 0;
            item.isEquippable = false;
            item.sellPrice = 50;
            item.isUsable = false;
            item.minAtk = 0;
            item.maxAtk = 0;
            item.block = 0;
            item.holdType = 0;
            item.stat1 = 0;
            item.stat2 = 0;
            item.stat3 = 0;
            item.statType1 = 0;
            item.statType2 = 0;
            item.statType3 = 0;
            item.amount = 1;
            item.numStats = 0;

            player_->removeGold(250);
            player_->addItemToInventory(item);
            player_->addBedroll();
            ui->lblGoldAmount->setText(QString("Gold: %1").arg(player_->getGold()));
            ui->lblGoldInv->setText(QString("Gold: %1").arg(player_->getGold()));
            setPlayerInfo();
            setPlayerInventory();
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Buy Item");
            msgBox.setText("You need to be in a City<br>or Town to buy items.");
            msgBox.exec();
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Buy Item");
        msgBox.setText("You do not have enough gold for this item.");
        msgBox.exec();
    }
}


void GameLogic::on_btnBuyFirestarterKit_clicked()
{
    if (player_->getGold() >= 200)
    {
        if (strRestLocation_[player_->getLocation()] == "City" ||strRestLocation_[player_->getLocation()] == "Town")
        {
            Item item;
            //numItems.push_back(banditItemDrops_[e][0]);

            item.name = "Firestarter Kit";
            item.itemRarity = 1;
            item.itemType = 0;
            item.armourRating = 0;
            item.armourType = 0;
            item.healType = 0;
            item.healAmount = 0;
            item.isEquippable = false;
            item.sellPrice = 35;
            item.isUsable = false;
            item.minAtk = 0;
            item.maxAtk = 0;
            item.block = 0;
            item.holdType = 0;
            item.stat1 = 0;
            item.stat2 = 0;
            item.stat3 = 0;
            item.statType1 = 0;
            item.statType2 = 0;
            item.statType3 = 0;
            item.amount = 1;
            item.numStats = 0;

            player_->removeGold(200);
            player_->addItemToInventory(item);
            player_->addFireStarterKit();
            ui->lblGoldAmount->setText(QString("Gold: %1").arg(player_->getGold()));
            ui->lblGoldInv->setText(QString("Gold: %1").arg(player_->getGold()));
            setPlayerInfo();
            setPlayerInventory();
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Buy Item");
            msgBox.setText("You need to be in a City<br>or Town to buy items.");
            msgBox.exec();
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Buy Item");
        msgBox.setText("You do not have enough gold for this item.");
        msgBox.exec();
    }
}

