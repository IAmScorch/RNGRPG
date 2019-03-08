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
    ui->tabActionScreen->setEnabled(false);
    ui->tabCInfoScreen->setEnabled(false);
    ui->tabQuestScreen->setEnabled(false);
    ui->txtBattleInfo->setEnabled(false);
    ui->btnAttack->setEnabled(false);
    ui->btnAttack->setFixedHeight(41);
    ui->btnSpecialAbility->setEnabled(false);
    ui->btnSpecialAbility->setVisible(false);
    ui->btnBattle->setEnabled(false);
    ui->btnUsePotionBS->setEnabled(false);
    ui->btnBeginQuest->setEnabled(false);
    ui->btnCompleteQuest->setEnabled(false);
    ui->btnAbandonQuest->setEnabled(false);
    ui->btnSpecialAbility->setEnabled(false);
    ui->lblEHealth->setFixedWidth(0);
    ui->lblEHealthAmount->setText("0");
    ui->lblQuestTabBG->setPixmap(QPixmap("Img\\tabQuestBG.png"));
    ui->lblMenuTabBG->setPixmap(QPixmap("Img\\tabMenuBG.png"));
    ui->lblBattleTabBG->setPixmap(QPixmap("Img\\tabBattleBG.png"));
    ui->lblCharTabBG->setPixmap(QPixmap("Img\\tabCharacterBG.png"));
    ui->lblActionTabBG->setPixmap(QPixmap("Img\\tabActionBG.png"));

    ui->btnNewGame->setStyleSheet("background-color: rgb(225, 225, 225, 200)");
    ui->btnLoad->setStyleSheet("background-color: rgb(225, 225, 225, 200)");
    ui->btnSave->setStyleSheet("background-color: rgb(225, 225, 225, 200)");
    ui->btnQuit->setStyleSheet("background-color: rgb(225, 225, 225, 200)");
    bandit_ = new Bandit("", 0, 0, 0, 0, 0, 0, 0, 0);
    banditBoss_ = new Bandit("", 0, 0, 0, 0, 0, 0, 0, 0);
    warrior_ = new Warrior("", 0, 0, 0, 0, 0);
    warriorBoss_ = new Warrior("", 0, 0, 0, 0, 0);
    player_ = new Player(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    quest_ = new quests(0, 0, 0, 0, 0, 0);
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
    ui->tabActionScreen->setEnabled(true);
    ui->tabCInfoScreen->setEnabled(true);
    ui->tabQuestScreen->setEnabled(true);
    ui->btnBattle->setEnabled(true);
    ui->btnBeginQuest->setEnabled(true);
    msSaveGameSC_->setEnabled(true);
    ui->btnUsePotionBS->setEnabled(true);
    ui->lblEHealth->setFixedWidth(0);
    ui->lblEHealthAmount->setText("0");
    ui->lblELevel->setText("0");
    ui->lblEnemyName->setText(" ");
    ui->txtBattleInfo->setText(" ");
    resetQuestInfo();
    createCharacter();
    setPlayerInfo();
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
            bandit_->doHit(player_->doAttack(bandit_->getName()), player_->doHitRoll(), player_->getName());

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
            player_->doHit(bandit_->doAttack(player_->getName()), bandit_->doHitRoll(), bandit_->getName(), bandit_->isAlive());
            message_ += bandit_->getMessage() + player_->getMessage();
        }

        ui->txtBattleInfo->setText(message_);
        setPlayerHealth();
        setEnemyHealth();

        if (!bandit_->isAlive())
        {
            message_ += player_->getName() + " Wins the battle!\n\n";
            ui->txtBattleInfo->setText(message_);
            bsAttackSC_->setEnabled(false);
            ui->btnUsePotionBS->setEnabled(true);
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
                quest_->setAmountComplete(1);

            int potChance = rand() % 10 + 1;
            player_->addGold(bandit_->goldDrop());
            ui->lblGoldAmount->setText(QString("Gold: %1").arg(player_->getGold()));
            if (potChance == 3 || potChance == 7)
            {
                QSound::play("Sounds\\potionDrop.wav");
                QMessageBox msgBox;
                msgBox.setWindowTitle("Item Drop");
                msgBox.setText("Bandit dropped a potion");
                msgBox.exec();
                player_->addPotion(1);
                ui->lblPotionAmount->setText(QString("Potions: %1").arg(player_->getPotion()));
            }
            player_->checkXP();
            player_->resetSpecialAbility();
            checkSkillPoints();
            ui->tabActionScreen->setEnabled(true);
            ui->tabCInfoScreen->setEnabled(true);
            ui->tabMenuScreen->setEnabled(true);
            ui->tabQuestScreen->setEnabled(true);

            ui->txtBattleInfo->setEnabled(false);
            ui->btnAttack->setEnabled(false);
            ui->btnSpecialAbility->setEnabled(false);
            ui->btnBattle->setEnabled(true);
            setPlayerInfo();
            checkQuest();
            bsBattleSC_->setEnabled(true);
        }
  //  }
//    else if (player_->getLevel() == 15)
//    {
//        if (banditBoss_->isAlive() && player_->isAlive())
//        {
//            banditBoss_->doHit(player_->doAttack(banditBoss_->getName()));
//            message_ += player_->getMessage() + banditBoss_->getMessage();
//            player_->doHit(banditBoss_->doAttack(player_->getName()));
//            message_ += banditBoss_->getMessage() + player_->getMessage();
//            ui->txtBattleInfo->setText(message_);
//            ui->pbarCHealth->setValue(player_->getHealth());
//            ui->pbarEHealth->setValue(banditBoss_->getHealth());
//        }
//        if (!banditBoss_->isAlive())
//        {
//            ui->pbarEHealth->setValue(0);
//            player_->addXP(banditBoss_->getXPReward());

//            int potChance = rand() % 10 + 1;
//            player_->addGold(banditBoss_->goldDrop());
//            ui->lblGoldAmount->setText(QString("Gold: %1").arg(player_->getGold()));
//            if (potChance == 3 || potChance == 7)
//            {
//                QSound::play("Sounds\\potionDrop.wav");
//                QMessageBox msgBox;
//                msgBox.setWindowTitle("Item Drop");
//                msgBox.setText("Bandit dropped a potion");
//                msgBox.exec();
//                player_->addPotion(1);
//                ui->lblPotionAmount->setText(QString("Potions: %1").arg(player_->getPotion()));
//            }
//            player_->checkXP();
//            checkSkillPoints();
//            ui->tabActionScreen->setEnabled(true);
//            ui->tabCInfoScreen->setEnabled(true);
//            ui->tabMenuScreen->setEnabled(true);
//            ui->tabQuestScreen->setEnabled(true);

//            ui->txtBattleInfo->setEnabled(false);
//            ui->btnAttack->setEnabled(false);
//            ui->pbarCHealth->setEnabled(false);
//            ui->pbarEHealth->setEnabled(false);
//            ui->btnBattle->setEnabled(true);
//            ui->btnUsePotionBS->setEnabled(false);
//            setPlayerInfo();
//            checkQuest();
//        }
//    }
//    else if (player_->getLevel() >= 16 && player_->getLevel() <= 34)
//    {
//        if (warrior_->isAlive() && player_->isAlive())
//        {
//            warrior_->doHit(player_->doAttack(warrior_->getName()));
//            message_ += player_->getMessage() + warrior_->getMessage();
//            player_->doHit(warrior_->doAttack(player_->getName()));
//            message_ += warrior_->getMessage() + player_->getMessage();
//            ui->txtBattleInfo->setText(message_);
//            ui->pbarCHealth->setValue(player_->getHealth());
//            ui->pbarEHealth->setValue(warrior_->getHealth());
//        }
//        if (!warrior_->isAlive())
//        {
//            ui->pbarEHealth->setValue(0);
//            player_->addXP(warrior_->getXPReward());

//            int potChance = rand() % 10 + 1;
//            int upgradeChance = rand() % 50 + 1;
//            player_->addGold(warrior_->goldDrop());
//            ui->lblGoldAmount->setText(QString("Gold: %1").arg(player_->getGold()));
//            if (potChance == 3 || potChance == 7)
//            {
//                QSound::play("Sounds\\potionDrop.wav");
//                QMessageBox msgBox;
//                msgBox.setWindowTitle("Item Drop");
//                msgBox.setText("Warrior dropped a potion");
//                msgBox.exec();
//                player_->addPotion(1);
//                ui->lblPotionAmount->setText(QString("Potions: %1").arg(player_->getPotion()));
//            }
//            if (upgradeChance == 25 || upgradeChance == 15)
//            {
//                QMessageBox msgBox;
//                msgBox.setWindowTitle("Health Upgrade");
//                msgBox.setText("Warrior dropped a health upgrade, adding 10 to your max health.");
//                msgBox.exec();
//                player_->addHealthUpgrade(10);
//            }
//            player_->checkXP();
//            checkSkillPoints();
//            ui->tabActionScreen->setEnabled(true);
//            ui->tabCInfoScreen->setEnabled(true);
//            ui->tabMenuScreen->setEnabled(true);
//            ui->tabQuestScreen->setEnabled(true);

//            ui->txtBattleInfo->setEnabled(false);
//            ui->btnAttack->setEnabled(false);
//            ui->pbarCHealth->setEnabled(false);
//            ui->pbarEHealth->setEnabled(false);
//            ui->btnBattle->setEnabled(true);
//            setPlayerInfo();
//            checkQuest();
//        }
//    }
//    else if (player_->getLevel() == 35)
//    {
//        if (warriorBoss_->isAlive() && player_->isAlive())
//        {
//            warriorBoss_->doHit(player_->doAttack(warriorBoss_->getName()));
//            message_ += player_->getMessage() + warriorBoss_->getMessage();
//            player_->doHit(warriorBoss_->doAttack(player_->getName()));
//            message_ += warriorBoss_->getMessage() + player_->getMessage();
//            ui->txtBattleInfo->setText(message_);
//            ui->pbarCHealth->setValue(player_->getHealth());
//            ui->pbarEHealth->setValue(warriorBoss_->getHealth());
//        }
//        if (!warriorBoss_->isAlive())
//        {
//            ui->pbarEHealth->setValue(0);
//            player_->addXP(warriorBoss_->getXPReward());

//            int potChance = rand() % 10 + 1;
//            int upgradeChance = rand() % 50 + 1;
//            player_->addGold(warriorBoss_->goldDrop());
//            ui->lblGoldAmount->setText(QString("Gold: %1").arg(player_->getGold()));
//            if (potChance == 3 || potChance == 7)
//            {
//                QSound::play("Sounds\\potionDrop.wav");
//                QMessageBox msgBox;
//                msgBox.setWindowTitle("Item Drop");
//                msgBox.setText("Warrior dropped a potion");
//                msgBox.exec();
//                player_->addPotion(1);
//                ui->lblPotionAmount->setText(QString("Potions: %1").arg(player_->getPotion()));
//            }
//            if (upgradeChance == 25 || upgradeChance == 15)
//            {
//                QMessageBox msgBox;
//                msgBox.setWindowTitle("Health Upgrade");
//                msgBox.setText("Warrior dropped a health upgrade, adding 10 to your max health.");
//                msgBox.exec();
//                player_->addHealthUpgrade(10);
//            }
//            player_->checkXP();
//            checkSkillPoints();
//            ui->tabActionScreen->setEnabled(true);
//            ui->tabCInfoScreen->setEnabled(true);
//            ui->tabMenuScreen->setEnabled(true);
//            ui->tabQuestScreen->setEnabled(true);

//            ui->txtBattleInfo->setEnabled(false);
//            ui->btnAttack->setEnabled(false);
//            ui->pbarCHealth->setEnabled(false);
//            ui->pbarEHealth->setEnabled(false);
//            ui->btnBattle->setEnabled(true);
//            ui->btnUsePotionBS->setEnabled(false);
//            setPlayerInfo();
//            checkQuest();
//        }
//    }

    if (!player_->isAlive())
    {
        ui->tabActionScreen->setEnabled(false);
        ui->tabCInfoScreen->setEnabled(false);
        ui->tabMenuScreen->setEnabled(true);
        ui->txtBattleInfo->setEnabled(false);
        ui->tabQuestScreen->setEnabled(false);
        ui->btnAttack->setEnabled(false);
        ui->btnSpecialAbility->setEnabled(false);
        ui->btnBattle->setEnabled(false);
        ui->btnUsePotionBS->setEnabled(false);
        ui->btnSave->setEnabled(false);
        ui->btnUsePotionBS->setEnabled(false);
        setPlayerHealth();
    }

//    if (!banditBoss_->isAlive())
//    {
//        QMessageBox msgBox;
//        msgBox.setWindowTitle("End Game");
//        msgBox.setText("You have defeated Thragg!\nYou're Winner!\nNow the game will close and you can start all over, scrub!\n");
//        msgBox.exec();
//        ui->tabActionScreen->setEnabled(false);
//        ui->tabCInfoScreen->setEnabled(false);
//        ui->tabMenuScreen->setEnabled(true);
//        ui->txtBattleInfo->setEnabled(false);
//        ui->btnAttack->setEnabled(false);
//        ui->pbarCHealth->setEnabled(false);
//        ui->pbarEHealth->setEnabled(false);
//        ui->btnBattle->setEnabled(false);
//        ui->btnUsePotionBS->setEnabled(false);
//        ui->btnSave->setEnabled(false);
//        ui->pbarCHealth->setValue(0);
//    }
}

void GameLogic::on_btnSpecialAbility_clicked()
{
    message_ = "";
    int playerLevel = 0;
    int enemyLevel = 0;
    int levelDiff = 0;

    if (player_->isAlive())
    {
        bandit_->doHit(player_->doSpecialAbility(bandit_->getName()), 20, player_->getName());
        message_ += player_->getMessage() + bandit_->getMessage();
    }

    if (bandit_->isAlive())
    {
        player_->doHit(bandit_->doAttack(player_->getName()), bandit_->doHitRoll(), bandit_->getName(), bandit_->isAlive());
        message_ += bandit_->getMessage() + player_->getMessage();
    }

    ui->txtBattleInfo->setText(message_);
    setEnemyHealth();
    setPlayerHealth();

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
            quest_->setAmountComplete(1);

        int potChance = rand() % 10 + 1;
        player_->addGold(bandit_->goldDrop());
        ui->lblGoldAmount->setText(QString("Gold: %1").arg(player_->getGold()));
        if (potChance == 3 || potChance == 7)
        {
            QSound::play("Sounds\\potionDrop.wav");
            QMessageBox msgBox;
            msgBox.setWindowTitle("Item Drop");
            msgBox.setText("Bandit dropped a potion");
            msgBox.exec();
            player_->addPotion(1);
            ui->lblPotionAmount->setText(QString("Potions: %1").arg(player_->getPotion()));
        }
        player_->checkXP();
        checkSkillPoints();
        ui->tabActionScreen->setEnabled(true);
        ui->tabCInfoScreen->setEnabled(true);
        ui->tabMenuScreen->setEnabled(true);
        ui->tabQuestScreen->setEnabled(true);

        ui->txtBattleInfo->setEnabled(false);
        ui->btnAttack->setEnabled(false);
        ui->btnSpecialAbility->setEnabled(false);
        ui->btnBattle->setEnabled(true);
        setPlayerInfo();
        checkQuest();
    }

    if (!player_->isAlive())
    {
        ui->tabActionScreen->setEnabled(false);
        ui->tabCInfoScreen->setEnabled(false);
        ui->tabMenuScreen->setEnabled(true);
        ui->txtBattleInfo->setEnabled(false);
        ui->tabQuestScreen->setEnabled(false);
        ui->btnAttack->setEnabled(false);
        ui->btnSpecialAbility->setEnabled(false);
        ui->btnBattle->setEnabled(false);
        ui->btnUsePotionBS->setEnabled(false);
        ui->btnSave->setEnabled(false);
        setPlayerHealth();
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

    ui->tabMenuScreen->setEnabled(false);
    ui->tabActionScreen->setEnabled(false);
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
        setEnemyHealth();
    }
    else if (bandit_->getEnemyType() == 6)
    {
        ui->txtBattleInfo->setText(QString("You saved an %1").arg(bandit_->getName()));
        quest_->setAmountComplete(1);
        ui->tabActionScreen->setEnabled(true);
        ui->tabCInfoScreen->setEnabled(true);
        ui->tabMenuScreen->setEnabled(true);
        ui->tabQuestScreen->setEnabled(true);

        ui->txtBattleInfo->setEnabled(false);
        ui->btnAttack->setEnabled(false);
        ui->btnSpecialAbility->setEnabled(false);
        ui->btnBattle->setEnabled(true);
        setPlayerInfo();
        checkQuest();
        bsBattleSC_->setEnabled(true);
    }
    else if (bandit_->getEnemyType() == 998)
    {
        ui->txtBattleInfo->setText(" ");
        ui->tabActionScreen->setEnabled(true);
        ui->tabCInfoScreen->setEnabled(true);
        ui->tabMenuScreen->setEnabled(true);
        ui->tabQuestScreen->setEnabled(true);

        ui->txtBattleInfo->setEnabled(false);
        ui->btnAttack->setEnabled(false);
        ui->btnBattle->setEnabled(true);
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
        ui->tabActionScreen->setEnabled(true);
        ui->tabCInfoScreen->setEnabled(true);
        ui->tabMenuScreen->setEnabled(true);
        ui->tabQuestScreen->setEnabled(true);

        ui->txtBattleInfo->setEnabled(false);
        ui->btnAttack->setEnabled(false);
        ui->btnSpecialAbility->setEnabled(false);
        ui->btnBattle->setEnabled(true);
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
        setEnemyHealth();
    }
//    else if (player_->getLevel() == 15)
//    {
//        ui->txtBattleInfo->setText("You were attacked by a bandit Leader");
//        ui->pbarEHealth->setMaximum(banditBoss_->getHealth());
//        ui->pbarEHealth->setValue(banditBoss_->getHealth());
//        ui->btnUsePotionBS->setEnabled(true);
//    }
//    else if (player_->getLevel() >= 16 && player_->getLevel() <= 34)
//    {
//        ui->txtBattleInfo->setText("You were attacked by a warrior");
//        ui->pbarEHealth->setMaximum(warrior_->getHealth());
//        ui->pbarEHealth->setValue(warrior_->getHealth());
//    }
//    else if (player_->getLevel() == 35)
//    {
//        ui->txtBattleInfo->setText("You were attacked by a bandit");
//        ui->pbarEHealth->setMaximum(warriorBoss_->getHealth());
//        ui->pbarEHealth->setValue(warriorBoss_->getHealth());
//        ui->btnUsePotionBS->setEnabled(true);
//    }
}

void GameLogic::checkLevel()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Choose A Bandit Camp To Attack");
    msgBox.setText("Where do you want to battle?");
    QPushButton *btnBanditBarracks = msgBox.addButton(tr("Bandit Barracks"), QMessageBox::ActionRole);
    QPushButton *btnDeepwoodForest = msgBox.addButton(tr("Deepwood Forest"), QMessageBox::ActionRole);
    QPushButton *btnRiverbane = msgBox.addButton(tr("Riverbane"), QMessageBox::ActionRole);
    QPushButton *btnAndorjaul = msgBox.addButton(tr("Andorjaul"), QMessageBox::ActionRole);
    //QPushButton *btnCutthroatCamp = msgBox.addButton(tr("Cutthroat Camp"), QMessageBox::ActionRole);
    //QPushButton *btnEliteCamp = msgBox.addButton(tr("Elite Camp"), QMessageBox::ActionRole);
    //QPushButton *btnFightTragg = msgBox.addButton(tr("Fight Thragg"), QMessageBox::ActionRole);

//    QPushButton *btnThugCamp     = msgBox.addButton(tr("Thug Camp"), QMessageBox::ActionRole);
//    QPushButton *btnBruiserCamp = msgBox.addButton(tr("Bruiser Camp"), QMessageBox::ActionRole);
//    QPushButton *btnCutthroatCamp = msgBox.addButton(tr("Cutthroat Camp"), QMessageBox::ActionRole);
//    QPushButton *btnEliteCamp = msgBox.addButton(tr("Elite Camp"), QMessageBox::ActionRole);
//    QPushButton *btnFightTragg = msgBox.addButton(tr("Fight Thragg"), QMessageBox::ActionRole);
    QPushButton *btnCancel = msgBox.addButton(QMessageBox::Cancel);
    msgBox.exec();

    if (msgBox.clickedButton() == btnBanditBarracks)
    {
        if (quest_->getQuestType() == 0)
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Bandit Barracks");
            msgBox.setText(QString("<b>Bandit Barracks</b><br>"
                                   "---------------------------------------------------------------------<br><br>"
                                   "The Bandit Barracks is where Thragg sends all of his new recruits<br>"
                                   "to train.<br><br>"
                                   "There is nothing for you to do here right now."));
            msgBox.exec();
            bandit_ = new Bandit("banditName", 0, 0, 0, 0, 0, 0, 999, 0);
        }
        else if (quest_->getQuestType() >= 4)
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Bandit Barracks");
            msgBox.setText(QString("<b>Bandit Barracks</b><br>"
                                   "---------------------------------------------------------------------<br><br>"
                                   "It is too dangerous to attack Thragg's Barracks right now."));
            msgBox.exec();
            bandit_ = new Bandit("banditName", 0, 0, 0, 0, 0, 0, 999, 0);
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

            if (quest_->getQuestType() == 2 && quest_->getIsQuestActive() == 1 && trainerChance >= 75)
            {
                banditName = "Bandit Trainer";
                banditHealth = 12;
                enemyMaxHP_ = 12;
                banditMaxAttackPower = 5;
                banditMinAttackPower = 1;
                banditCritChance = 50;
                banditXPReward = 12;
                banditType = 2;
                banditLevel = 2;
                banditAgility = 5;
            }
            else
            {
                banditHealth = rand() % ((9 + 1) - 5) + 5;
                enemyMaxHP_ = banditHealth;
                banditMaxAttackPower = 2;
                banditMinAttackPower = 1;
                banditCritChance = 100;
                banditXPReward = 6;
                banditType = 1;
            }

            bandit_ = new Bandit(banditName, banditHealth, banditMaxAttackPower, banditMinAttackPower,
                                 banditCritChance, banditXPReward, banditLevel, banditType, banditAgility);
        }
    }
    else if (msgBox.clickedButton() == btnDeepwoodForest)
    {
        if (quest_->getQuestType() < 3)
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Deepwood Forest");
            msgBox.setText(QString("<b>Deepwood Forest</b><br>"
                                   "---------------------------------------------------------------------<br><br>"
                                   "Deepwood Forest is usually a pretty quite place.<br>"
                                   "The Windlehelm City Guard built a trail that runs through the forest<br>"
                                   "that they use for trade convoys.<br>"
                                   "Bandits like to wander the forest every now and then in small numbers.<br>"
                                   "Nothing to be alarmed about, but always stay vigilant when travelling<br>"
                                   "through Deepwood.<br><br>"
                                   "There is nothing out of the ordinary going on in Deepwood right now."));
            msgBox.exec();
            bandit_ = new Bandit("banditName", 0, 0, 0, 0, 0, 0, 999, 0);
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

            if (quest_->getQuestType() == 3 && quest_->getIsQuestActive() == 1 && trainerChance >= 85)
            {
                banditName = "Trainer Gren";
                banditHealth = 15;
                enemyMaxHP_ = 15;
                banditMaxAttackPower = 6;
                banditMinAttackPower = 2;
                banditCritChance = 50;
                banditXPReward = 24;
                banditType = 3;
                banditLevel = 2;
                banditAgility = 6;
            }
            else if (quest_->getQuestType() == 5 && quest_->getIsQuestActive() == 1)
            {
                banditName = "Initiate Ambusher";
                banditHealth = rand() % ((9 + 1) - 5) + 5;
                enemyMaxHP_ = banditHealth;
                banditMaxAttackPower = 3;
                banditMinAttackPower = 1;
                banditCritChance = 50;
                banditXPReward = 6;
                banditType = 5;
            }
            else
            {
                banditHealth = rand() % ((9 + 1) - 5) + 5;
                enemyMaxHP_ = banditHealth;
                banditMaxAttackPower = 2;
                banditMinAttackPower = 1;
                banditCritChance = 100;
                banditXPReward = 6;
                banditType = 1;
            }

            bandit_ = new Bandit(banditName, banditHealth, banditMaxAttackPower, banditMinAttackPower,
                                 banditCritChance, banditXPReward, banditLevel, banditType, banditAgility);
        }
    }
    else if (msgBox.clickedButton() == btnRiverbane)
    {
        if (quest_->getQuestType() < 4 )
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Riverbane");
            msgBox.setText(QString("<b>The Riverbane Settlement</b><br>"
                                   "---------------------------------------------------------------------<br><br>"
                                   "Riverbane is one of the smaller settlements outside of Windlehelm<br>"
                                   "Most of the inhabitants there are miners that work at the<br>"
                                   "Riverbane Mine. They supply a huge amount of metals to Windlehelm,<br>"
                                   "which they use for crafting weapons and armour.<br><br>"
                                   "There is nothing happening is Riverbane right now."));
            msgBox.exec();
            bandit_ = new Bandit("banditName", 0, 0, 0, 0, 0, 0, 999, 0);
        }
        else if (quest_->getQuestType() > 4)
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Riverbane");
            msgBox.setText(QString("<b>The Riverbane Settlement</b><br>"
                                   "---------------------------------------------------------------------<br><br>"
                                   "Riverbane is currently under heavy protection from the<br>"
                                   "Windlehelm City Guard and is in no danger."));
            msgBox.exec();
            bandit_ = new Bandit("banditName", 0, 0, 0, 0, 0, 0, 999, 0);
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

            banditHealth = rand() % ((12 + 1) - 9) + 9;
            enemyMaxHP_ = banditHealth;
            banditMaxAttackPower = 3;
            banditMinAttackPower = 1;
            banditCritChance = 80;
            banditXPReward = 12;

            bandit_ = new Bandit(banditName, banditHealth, banditMaxAttackPower, banditMinAttackPower,
                                 banditCritChance, banditXPReward, banditLevel, banditType, banditAgility);
        }
    }
    else if (msgBox.clickedButton() == btnAndorjaul)
    {
        if (quest_->getQuestType() < 6)
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Andorjaul");
            msgBox.setText(QString("<b>The Andorjaul Settlement</b><br>"
                                   "---------------------------------------------------------------------<br><br>"
                                   "Andorjaul is one of the bigger settlements outside of Windlehelm<br>"
                                   "Many of the inhabitants here are just commoners, but there are also<br>"
                                   "medical professionals here. There are hospitals and medical shops<br>"
                                   "here that help out most of the travellers outside of Windlehelm.<br>"
                                   "Andorjaul also provides medicines and medical aid to the<br>"
                                   "Windlehelm City Guard.<br><br>"
                                   "There is nothing out of the ordinary happening in Andorjaul right now."));
            msgBox.exec();
            bandit_ = new Bandit("banditName", 0, 0, 0, 0, 0, 0, 999, 0);
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
            int banditType = 7;
            int banditAgility = 5;
            int andorjaulSettlerChance = rand() % ((100 + 1) - 1) + 1;

            if (quest_->getQuestType() == 6  && quest_->getIsQuestActive() == 1 && andorjaulSettlerChance >= 60)
            {
                banditName = "Andorjaul Settler";
                banditHealth = 2;
                enemyMaxHP_ = banditHealth;
                banditMaxAttackPower = 1;
                banditMinAttackPower = 1;
                banditCritChance = 80;
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
                banditCritChance = 80;
                banditXPReward = 12;
            }

            bandit_ = new Bandit(banditName, banditHealth, banditMaxAttackPower, banditMinAttackPower,
                                 banditCritChance, banditXPReward, banditLevel, banditType, banditAgility);
        }
    }
//    else if (msgBox.clickedButton() == btnCutthroatCamp)
//    {
//        bsAttackSC_->setEnabled(true);
//        bsBattleSC_->setEnabled(false);
//        QString banditName = "Bandit Cutthroat";
//        int banditHealth = 0;
//        int banditMaxAttackPower = 0;
//        int banditMinAttackPower = 0;
//        int banditCritChance = 0;
//        int banditXPReward = 0;
//        // attackDmg_ = rand() % ((maxAttackPower_ + 1) - minAttackPower_) + minAttackPower_;
//        int banditLevel = (rand() % ((12 + 1) - 10) + 10);
//        int banditType = 6;
//        int banditAgility = 6;

//        if (banditLevel == 10)
//        {
//            banditHealth = 600;
//            enemyMaxHP_ = 600;
//            banditMaxAttackPower = 34;
//            banditMinAttackPower = 20;
//            banditCritChance = 80;
//            banditXPReward = 504;
//        }
//        else if (banditLevel == 11)
//        {
//            banditHealth = 650;
//            enemyMaxHP_ = 650;
//            banditMaxAttackPower = 37;
//            banditMinAttackPower = 20;
//            banditCritChance = 80;
//            banditXPReward = 600;
//        }
//        else if (banditLevel == 12)
//        {
//            banditHealth = 700;
//            enemyMaxHP_ = 700;
//            banditMaxAttackPower = 40;
//            banditMinAttackPower = 25;
//            banditCritChance = 80;
//            banditXPReward = 702;
//        }

//        bandit_ = new Bandit(banditName, banditHealth, banditMaxAttackPower, banditMinAttackPower,
//                             banditCritChance, banditXPReward, banditLevel, banditType, banditAgility);
//    }
//    else if (msgBox.clickedButton() == btnEliteCamp)
//    {
//        bsAttackSC_->setEnabled(true);
//        bsBattleSC_->setEnabled(false);
//        QString banditName = "Bandit Elite";
//        int banditHealth = 0;
//        int banditMaxAttackPower = 0;
//        int banditMinAttackPower = 0;
//        int banditCritChance = 0;
//        int banditXPReward = 0;
//        // attackDmg_ = rand() % ((maxAttackPower_ + 1) - minAttackPower_) + minAttackPower_;
//        int banditLevel = (rand() % ((14 + 1) - 13) + 13);
//        int banditType = 7;
//        int banditAgility = 8;

//        if (banditLevel == 13)
//        {
//            banditHealth = 1000;
//            enemyMaxHP_ = 1000;
//            banditMaxAttackPower = 40;
//            banditMinAttackPower = 25;
//            banditCritChance = 60;
//            banditXPReward = 5004;
//        }
//        else if (banditLevel == 14)
//        {
//            banditHealth = 1100;
//            enemyMaxHP_ = 1100;
//            banditMaxAttackPower = 40;
//            banditMinAttackPower = 30;
//            banditCritChance = 60;
//            banditXPReward = 6000;
//        }

//        bandit_ = new Bandit(banditName, banditHealth, banditMaxAttackPower, banditMinAttackPower,
//                             banditCritChance, banditXPReward, banditLevel, banditType, banditAgility);
//    }
//    else if (msgBox.clickedButton() == btnFightTragg)
//    {
//        if (player_->getLevel() < 15)
//        {
//            QMessageBox msgBox;
//            msgBox.setWindowTitle("Choose A Bandit Camp To Attack");
//            msgBox.setText("You are not yet strong enough to face Thragg");
//            msgBox.exec();
//            ui->tabActionScreen->setEnabled(true);
//            ui->tabCInfoScreen->setEnabled(true);
//            ui->tabMenuScreen->setEnabled(true);
//            ui->tabQuestScreen->setEnabled(true);

//            ui->txtBattleInfo->setEnabled(false);
//            ui->btnAttack->setEnabled(false);
//            ui->btnSpecialAbility->setEnabled(false);
//            ui->btnBattle->setEnabled(true);
//            bsBattleSC_->setEnabled(true);
//        }
//        else
//        {
//            bsAttackSC_->setEnabled(true);
//            bsBattleSC_->setEnabled(false);
//            QString banditName = "Thragg";
//            int banditHealth = 0;
//            int banditMaxAttackPower = 0;
//            int banditMinAttackPower = 0;
//            int banditCritChance = 0;
//            int banditXPReward = 0;
//            // attackDmg_ = rand() % ((maxAttackPower_ + 1) - minAttackPower_) + minAttackPower_;
//            int banditLevel = 15;
//            int banditType = 20;
//            int banditAgility = 12;

//            banditHealth = 5000;
//            enemyMaxHP_ = 5000;
//            banditMaxAttackPower = 50;
//            banditMinAttackPower = 35;
//            banditCritChance = 40;
//            banditXPReward = 2000000;


//            bandit_ = new Bandit(banditName, banditHealth, banditMaxAttackPower, banditMinAttackPower,
//                                 banditCritChance, banditXPReward, banditLevel, banditType, banditAgility);
//        }
//    }
    else if (msgBox.clickedButton() == btnCancel)
    {
        bandit_ = new Bandit("banditName", 0, 0, 0, 0, 0, 0, 998, 0);
    }
    else
    {
        bandit_ = new Bandit("banditName", 0, 0, 0, 0, 0, 0, 998, 0);
    }

//    if (player_->getLevel() <= 3)
//        //name, health, maxAttackPower, minAttackPower, critChance, XPReward, level
//        bandit_ = new Bandit("Bandit", 50, 5, 1, 100, 5, 1);
//    else if (player_->getLevel() >=4 && player_->getLevel() <= 6)
//        bandit_ = new Bandit("Bandit", 100, 12, 7, 100, 10, 4);
//    else if (player_->getLevel() >=7 && player_->getLevel() <= 9)
//        bandit_ = new Bandit("Bandit", 200, 17, 12, 100, 15, 7);
//    else if (player_->getLevel() >= 10 && player_->getLevel() <= 14)
//        bandit_ = new Bandit("Bandit", 400, 25, 20, 100, 20, 10);
//    else if (player_->getLevel() == 15)
//        banditBoss_ = new Bandit("Bandit Leader", 1500, 50, 45, 50, 1000, 15);
//    else if (player_->getLevel() >= 16 && player_->getLevel() <= 18)
//        warrior_ = new Warrior("Warrior", 600, 25, 75, 75, 16);
//    else if (player_->getLevel() >= 19 && player_->getLevel() <= 21)
//        warrior_ = new Warrior("Warrior", 800, 35, 75, 110, 19);
//    else if (player_->getLevel() >= 22 && player_->getLevel() <= 24)
//        warrior_ = new Warrior("Warrior", 950, 45, 75, 150, 22);
//    else if (player_->getLevel() >= 25 && player_->getLevel() <= 27)
//        warrior_ = new Warrior("Warrior", 1100, 55, 75, 200, 25);
//    else if (player_->getLevel() >= 26 && player_->getLevel() <= 28)
//        warrior_ = new Warrior("Warrior", 1250, 65, 75, 300, 26);
//    else if (player_->getLevel() >= 29 && player_->getLevel() <= 31)
//        warrior_ = new Warrior("Warrior", 1300, 70, 75, 375, 29);
//    else if (player_->getLevel() >= 32 && player_->getLevel() <= 34)
//        warrior_ = new Warrior("Warrior", 1550, 80, 75, 450, 32);
//    else if (player_->getLevel() == 35)
//        warriorBoss_ = new Warrior("Warrior Leader", 5000, 145, 45, 450, 35);
}

void GameLogic::createCharacter()
{
    //health, maxHealth, maxAttackPower, minAttackPower, vitality, strength, agility, luck, intelligence, hit, agilityDefault, luckDefault
    player_ = new Player(20, 20, 5, 1, 10, 5, 0, 0, 0, 0, 6, 20);
    bool ok;
    name_ = QInputDialog::getText(this, tr("New Game"), tr("<p>Greetings traveler, welcome to <b>Windlehelm</b>.<br>"
                                                           "I am <b>Bormeir</b>, head of the <b>Windlehelm City Guard</b>.<br>"
                                                           "What might I call you?<br><br>"
                                                           "Enter a character name:</p>"), QLineEdit::Normal, "", &ok);

    if(ok)
    {
        player_->setName(name_);
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
            ui->tabActionScreen->setEnabled(true);
            ui->tabCInfoScreen->setEnabled(true);
            ui->tabQuestScreen->setEnabled(true);
            ui->btnBattle->setEnabled(true);
            msSaveGameSC_->setEnabled(true);
            ui->btnUsePotionBS->setEnabled(true);
            ui->lblEHealth->setFixedWidth(0);
            ui->lblEHealthAmount->setText("0");
            ui->lblELevel->setText("0");
            ui->lblEnemyName->setText(" ");
            ui->txtBattleInfo->setText(" ");

            if (quest_->getIsQuestActive() == 1 && quest_->getIsQuestComplete() == 0)
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

                ui->lblQTitle->setText("Quest Tite");
                ui->lblQProgress->setText("Progess:");
                ui->lblQReward->setText("Reward:");
            }

            setPlayerInfo();
            checkSkillPoints();
            ui->lblGoldAmount->setText(QString("Gold: %1").arg(player_->getGold()));
            ui->lblPotionAmount->setText(QString("Potions: %1").arg(player_->getPotion()));
            ui->txtBattleInfo->setText("");
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

void GameLogic::on_btnUsePotion_clicked()
{
    player_->usePotion();
    setPlayerInfo();
    ui->lblPotionAmount->setText(QString("Potions: %1").arg(player_->getPotion()));
}

void GameLogic::on_btnBuyPotion_clicked()
{
    player_->buyPotion();
    ui->lblGoldAmount->setText(QString("Gold: %1").arg(player_->getGold()));
    ui->lblPotionAmount->setText(QString("Potions: %1").arg(player_->getPotion()));
    setPlayerInfo();
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
    ui->lblPotionAmount->setText(QString("Potions: %1").arg(player_->getPotion()));
    ui->lblPLevel->setText(QString("%1").arg(player_->getLevel()));
    ui->lblCStrength->setText(QString("Strength: %1").arg(player_->getStrength()));
    ui->lblCAgility->setText(QString("Agility: %1").arg(player_->getAgility()));
    ui->lblCLuck->setText(QString("Luck: %1").arg(player_->getLuck()));
    ui->lblCVitality->setText(QString("Vitality: %1").arg(player_->getVitality()));
    ui->lblCHit->setText(QString("Hit: %1").arg(player_->getHit()));
    double xpPercent = (double(player_->getXP()) / double(player_->getXPTillLevel())) * 100;
    double xpPercent2 = (double(player_->getXP()) / double(player_->getXPTillLevel())) * 400;
    ui->lblXpPercent->setText(QString("%1%").arg(int(xpPercent)));
    ui->lblXpBar->setFixedWidth(int(xpPercent2));
    setPlayerHealth();
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
    quest_ = new quests(0, 0, 0, 0, 0, 0);
    ui->lblQTitle->setText("No Active Quest");
    ui->lblQProgress->setText("Progess:");
    ui->lblQReward->setText("Reward:");
    ui->btnBeginQuest->setEnabled(true);
    ui->btnCompleteQuest->setEnabled(false);
    ui->btnAbandonQuest->setEnabled(false);
}

void GameLogic::on_btnUsePotionBS_clicked()
{
    player_->usePotion();
    ui->lblPotionAmount->setText(QString("Potions: %1").arg(player_->getPotion()));
    setPlayerHealth();
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
    }

    if (player_->getVitality() == 20)
    {
        ui->btnIncreaseHP->setEnabled(false);
        ui->btnIncreaseHP->setVisible(false);
    }

    if (player_->getStrength() == 20)
    {
        ui->btnIncreaseAttack->setEnabled(false);
        ui->btnIncreaseAttack->setVisible(false);
    }

    if (player_->getAgility() == 20)
    {
        ui->btnIncreaseAgility->setEnabled(false);
        ui->btnIncreaseAgility->setVisible(false);
    }

    if (player_->getLuck() == 20)
    {
        ui->btnIncreaseCritChance->setEnabled(false);
        ui->btnIncreaseCritChance->setVisible(false);
    }

    if (player_->getHit() == 20)
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
    //player_->setMaxHealth(2);
    player_->addVitality(1);
    player_->setHealth(player_->getMaxHealth());
    ui->lblCHealth->setText(QString("Health: %1/%2").arg(player_->getHealth()).arg(player_->getMaxHealth()));
    ui->lblCVitality->setText(QString("Vitality: %1").arg(player_->getVitality()));
    player_->setSkillPoints(1);
    ui->lblCSkillPoints->setText(QString("Skill Points: %1").arg(player_->getSkillPoints()));
    checkSkillPoints();
    setPlayerHealth();
}

void GameLogic::on_btnIncreaseAttack_clicked()
{
    //player_->setMaxAttackPower(1);
    //player_->setMinAttackPower(10);
    player_->addStrength(1);
    ui->lblCAttack->setText(QString("Attack: %1-%2").arg(player_->getMinAttackPower()).arg(player_->getMaxAttackPower()));
    ui->lblCStrength->setText(QString("Strength: %1").arg(player_->getStrength()));
    player_->setSkillPoints(1);
    ui->lblCSkillPoints->setText(QString("Skill Points: %1").arg(player_->getSkillPoints()));
    checkSkillPoints();
}

void GameLogic::on_btnIncreaseAgility_clicked()
{
    player_->addAgility(1);
    ui->lblCAgility->setText(QString("Agility: %1").arg(player_->getAgility()));
    player_->setSkillPoints(1);
    ui->lblCSkillPoints->setText(QString("Skill Points: %1").arg(player_->getSkillPoints()));
    checkSkillPoints();
}

void GameLogic::on_btnIncreaseCritChance_clicked()
{
    player_->addLuck(1);
    ui->lblCLuck->setText(QString("Luck: %1").arg(player_->getLuck()));
    player_->setSkillPoints(1);
    ui->lblCSkillPoints->setText(QString("Skill Points: %1").arg(player_->getSkillPoints()));
    checkSkillPoints();
}

void GameLogic::on_btnIncreaseHitChance_clicked()
{
    player_->addHit(1);
    ui->lblCHit->setText(QString("Hit: %1").arg(player_->getHit()));
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
                               "10 Gold").arg(player_->getName()));
        QPushButton *btnAccept = msgBox.addButton(tr("Accept"), QMessageBox::ActionRole);
        QPushButton *btnDecline = msgBox.addButton(tr("Decline"), QMessageBox::ActionRole);
        msgBox.exec();

        if (msgBox.clickedButton() == btnAccept)
        {
            QSound::play("Sounds\\acceptQuest.wav");
            goldReward = 10;
            //xpReward, objective, amountComplete, isQuestComplete, isQuestActive, questType
            quest_ = new quests(50, 6, 0, 0, 1, 1);
            questTitle = QString("Kill %1 Bandit Initiates").arg(quest_->getObjective());
            questText = QString("Progress: %1/%2 Bandit Initiates killed.").arg(quest_->getAmountComplete()).arg(quest_->getObjective());
        }
        else if (msgBox.clickedButton() == btnDecline)
        {
            QSound::play("Sounds\\abondonQuest.wav");
            //xpReward, objective, amountComplete, isQuestComplete, isQuestActive, questType
            quest_ = new quests(0, 0, 0, 0, 0, 0);
        }
    }
    else if (player_->getQuestsCompleted() == 1)
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
            //xpReward, objective, amountComplete, isQuestComplete, isQuestActive, questType
            quest_ = new quests(100, 1, 0, 0, 1, 2);
            questTitle = QString("Fashionable New Clothes").arg(quest_->getObjective());
            questText = QString("Progress: Take an Initiate Trainer's Outfit.");
        }
        else if (msgBox.clickedButton() == btnDecline)
        {
            QSound::play("Sounds\\abondonQuest.wav");
            //xpReward, objective, amountComplete, isQuestComplete, isQuestActive, questType
            quest_ = new quests(0, 0, 0, 0, 0, 1);
        }
    }
    else if (player_->getQuestsCompleted() == 2)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Bormeir");
        msgBox.setText(QString("<b>An Opportunity Arises</b><br>"
                               "---------------------------------------------------------------------<br><br>"
                               "%1, I just heard word from one of my scouts in Deepwood Forest that<br>"
                               "a huge group of Bandit Initiates have set up camp inside the forest<br>"
                               "lead by a high value target. They're lead by Gren, one of Thragg's<br>"
                               "most trusted trainers.<br><br>"
                               "They've set up their camp just out of site of a main trail through<br>"
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
            //xpReward, objective, amountComplete, isQuestComplete, isQuestActive, questType
            quest_ = new quests(250, 1, 0, 0, 1, 3);
            questTitle = QString("An Oportunity Arises").arg(quest_->getObjective());
            questText = QString("Progress: Kill Gren and take his head.");
        }
        else if (msgBox.clickedButton() == btnDecline)
        {
            QSound::play("Sounds\\abondonQuest.wav");
            //xpReward, objective, amountComplete, isQuestComplete, isQuestActive, questType
            quest_ = new quests(0, 0, 0, 0, 0, 2);
        }
    }
    else if (player_->getQuestsCompleted() == 3)
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
            //xpReward, objective, amountComplete, isQuestComplete, isQuestActive, questType
            quest_ = new quests(150, 10, 0, 0, 1, 4);
            questTitle = QString("What's Mine is not Yours").arg(quest_->getObjective());
            questText = QString("Progress: %1/%2 Raiders killed.").arg(quest_->getAmountComplete()).arg(quest_->getObjective());
        }
        else if (msgBox.clickedButton() == btnDecline)
        {
            QSound::play("Sounds\\abondonQuest.wav");
            //xpReward, objective, amountComplete, isQuestComplete, isQuestActive, questType
            quest_ = new quests(0, 0, 0, 0, 0, 3);
        }
    }
    else if (player_->getQuestsCompleted() == 4)
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
            //xpReward, objective, amountComplete, isQuestComplete, isQuestActive, questType
            quest_ = new quests(75, 10, 0, 0, 1, 5);
            questTitle = QString("Deepwood Cleanup").arg(quest_->getObjective());
            questText = QString("Progress: %1/%2 Initiate Ambushers killed.").arg(quest_->getAmountComplete()).arg(quest_->getObjective());
        }
        else if (msgBox.clickedButton() == btnDecline)
        {
            QSound::play("Sounds\\abondonQuest.wav");
            //xpReward, objective, amountComplete, isQuestComplete, isQuestActive, questType
            quest_ = new quests(0, 0, 0, 0, 0, 4);
        }
    }
    else if (player_->getQuestsCompleted() == 5)
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
            //xpReward, objective, amountComplete, isQuestComplete, isQuestActive, questType
            quest_ = new quests(150, 7, 0, 0, 1, 6);
            questTitle = QString("Played The Fool").arg(quest_->getObjective());
            questText = QString("Progress: %1/%2 Andorjaul Settlers saved.").arg(quest_->getAmountComplete()).arg(quest_->getObjective());
        }
        else if (msgBox.clickedButton() == btnDecline)
        {
            QSound::play("Sounds\\abondonQuest.wav");
            //xpReward, objective, amountComplete, isQuestComplete, isQuestActive, questType
            quest_ = new quests(0, 0, 0, 0, 0, 5);
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

//    QMessageBox msgBox;
//    msgBox.setWindowTitle("Choose A Quest");
//    msgBox.setText("Choose a quest to embark on.");
//    QPushButton *btnInitiateKills = msgBox.addButton(tr("Initiate Kills"), QMessageBox::ActionRole);
//    QPushButton *btnThugKills     = msgBox.addButton(tr("Thug Kills"), QMessageBox::ActionRole);
//    QPushButton *btnBruiserKills = msgBox.addButton(tr("Bruiser Kills"), QMessageBox::ActionRole);
//    QPushButton *btnCutthroatKills = msgBox.addButton(tr("Cutthroat Kills"), QMessageBox::ActionRole);
//    QPushButton *btnEliteKills = msgBox.addButton(tr("Elite Kills"), QMessageBox::ActionRole);
//    QPushButton *btnThraggKill = msgBox.addButton(tr("Kill Thragg"), QMessageBox::ActionRole);
//    QPushButton *btnCancel = msgBox.addButton(QMessageBox::Cancel);
//    msgBox.exec();

//    if (msgBox.clickedButton() == btnInitiateKills)
//    {
//        QSound::play("Sounds\\acceptQuest.wav");
//        //xpReward, objective, amountComplete, isQuestComplete, isQuestActive, questType
//        quest_ = new quests(100, 10, 0, 0, 1, 1);
//        questTitle = QString("Kill %1 Bandit Initiates").arg(quest_->getObjective());
//        questText = QString("Progress: %1/%2 Bandit Initiates killed.").arg(quest_->getAmountComplete()).arg(quest_->getObjective());

//    }
//    else if (msgBox.clickedButton() == btnThugKills)
//    {
//        QSound::play("Sounds\\acceptQuest.wav");
//        //xpReward, objective, amountComplete, isQuestComplete, isQuestActive, questType
//        quest_ = new quests(250, 10, 0, 0, 1, 2);
//        questTitle = QString("Kill %1 Bandit Thugs").arg(quest_->getObjective());
//        questText = QString("Progress: %1/%2 Bandit Thugs killed.").arg(quest_->getAmountComplete()).arg(quest_->getObjective());

//    }
//    else if (msgBox.clickedButton() == btnBruiserKills)
//    {
//        QSound::play("Sounds\\acceptQuest.wav");
//        //xpReward, objective, amountComplete, isQuestComplete, isQuestActive, questType
//        quest_ = new quests(1500, 10, 0, 0, 1, 3);
//        questTitle = QString("Kill %1 Bandit Bruisers").arg(quest_->getObjective());
//        questText = QString("Progress: %1/%2 Bandit Bruisers killed.").arg(quest_->getAmountComplete()).arg(quest_->getObjective());

//    }
//    else if (msgBox.clickedButton() == btnCutthroatKills)
//    {
//        QSound::play("Sounds\\acceptQuest.wav");
//        //xpReward, objective, amountComplete, isQuestComplete, isQuestActive, questType
//        quest_ = new quests(9000, 6, 0, 0, 1, 4);
//        questTitle = QString("Kill %1 Bandit Cutthroats").arg(quest_->getObjective());
//        questText = QString("Progress: %1/%2 Bandit Cutthroats killed.").arg(quest_->getAmountComplete()).arg(quest_->getObjective());

//    }
//    else if (msgBox.clickedButton() == btnEliteKills)
//    {
//        QSound::play("Sounds\\acceptQuest.wav");
//        //xpReward, objective, amountComplete, isQuestComplete, isQuestActive, questType
//        quest_ = new quests(25000, 5, 0, 0, 1, 5);
//        questTitle = QString("Kill %1 Bandit Elites").arg(quest_->getObjective());
//        questText = QString("Progress: %1/%2 Bandit Elites killed.").arg(quest_->getAmountComplete()).arg(quest_->getObjective());

//    }
//    else if (msgBox.clickedButton() == btnThraggKill)
//    {
//        QSound::play("Sounds\\acceptQuest.wav");
//        //xpReward, objective, amountComplete, isQuestComplete, isQuestActive, questType
//        quest_ = new quests(3000000, 1, 0, 0, 1, 6);
//        questTitle = QString("Kill Thragg, the leader of the Bandits");
//        questText = QString("Progress: Kill Thragg");

//    }
//    else if (msgBox.clickedButton() == btnCancel)
//    {
//        QSound::play("Sounds\\abondonQuest.wav");
//        //xpReward, objective, amountComplete, isQuestComplete, isQuestActive, questType
//        quest_ = new quests(0, 0, 0, 0, 0, 0);
//    }
//    else
//    {
//        QSound::play("Sounds\\abondonQuest.wav");
//        //xpReward, objective, amountComplete, isQuestComplete, isQuestActive, questType
//        quest_ = new quests(0, 0, 0, 0, 0, 0);
//    }
}

void GameLogic::on_btnCompleteQuest_clicked()
{
    int isQuestComplete = 0;
    quest_->completeQuest();
    if (quest_->getAmountComplete() == quest_->getObjective())
    {
        player_->completeQuest();
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

void GameLogic::on_btnAbandonQuest_clicked()
{
    QSound::play("Sounds\\abondonQuest.wav");
    //xpReward, objective, amountComplete, isQuestComplete, isQuestActive
    quest_ = new quests(0, 0, 0, 0, 0, 0);

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
