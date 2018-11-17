#include <iostream>
#include <QString>
#include <random>
#include <ctime>
#include <QTime>
#include <QMessageBox>
#include <QInputDialog>
#include <QSound>
#include <QShortcut>
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
    ui->pbarCHealth->setEnabled(false);
    ui->pbarEHealth->setEnabled(false);
    ui->btnBattle->setEnabled(false);
    ui->btnUsePotionBS->setEnabled(false);
    ui->btnBeginQuest->setEnabled(false);
    ui->btnCompleteQuest->setEnabled(false);
    ui->btnAbandonQuest->setEnabled(false);
    ui->btnSpecialAbility->setEnabled(false);
    ui->lblQuestTabBG->setPixmap(QPixmap("../Img/tabQuestBG.png"));
    ui->lblMenuTabBG->setPixmap(QPixmap("../Img/tabMenuBG.png"));
    ui->lblBattleTabBG->setPixmap(QPixmap("../Img/tabBattleBG.png"));
    ui->lblCharTabBG->setPixmap(QPixmap("../Img/tabCharacterBG.png"));
    ui->lblActionTabBG->setPixmap(QPixmap("../Img/tabActionBG.png"));

    ui->btnNewGame->setStyleSheet("background-color: rgb(225, 225, 225, 200)");
    ui->btnLoad->setStyleSheet("background-color: rgb(225, 225, 225, 200)");
    ui->btnSave->setStyleSheet("background-color: rgb(225, 225, 225, 200)");
    ui->btnQuit->setStyleSheet("background-color: rgb(225, 225, 225, 200)");
    bandit_ = new Bandit("", 0, 0, 0, 0, 0, 0, 0);
    banditBoss_ = new Bandit("", 0, 0, 0, 0, 0, 0, 0);
    warrior_ = new Warrior("", 0, 0, 0, 0, 0);
    warriorBoss_ = new Warrior("", 0, 0, 0, 0, 0);
    player_ = new Player(0, 0, 0, 0, 0);
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
    createCharacter();
    setPlayerInfo();
}

void GameLogic::on_btnAttack_clicked()
{
    //QSound::play("../Sounds/doHit.wav");
    message_ = "";
    int playerLevel = 0;
    int enemyLevel = 0;
    int levelDiff = 0;

   // if (player_->getLevel() >= 1 && player_->getLevel() <= 15)
   // {
        if (bandit_->isAlive() && player_->isAlive())
        {
            bandit_->doHit(player_->doAttack(bandit_->getName()));
            player_->addSpecialAbilityCharge(1);
            message_ += player_->getMessage() + bandit_->getMessage();
            player_->doHit(bandit_->doAttack(player_->getName()));
            message_ += bandit_->getMessage() + player_->getMessage();
            ui->txtBattleInfo->setText(message_);
            ui->pbarCHealth->setValue(player_->getHealth());
            ui->pbarEHealth->setValue(bandit_->getHealth());

            if (player_->IsSpecialReady())
            {
                ui->btnSpecialAbility->setEnabled(true);
                bsSpecialSC_->setEnabled(true);
            }
        }
        if (!bandit_->isAlive())
        {
            bsAttackSC_->setEnabled(false);
            ui->pbarEHealth->setValue(0);

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
                QSound::play("../Sounds/potionDrop.wav");
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
            ui->pbarCHealth->setEnabled(false);
            ui->pbarEHealth->setEnabled(false);
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
//                QSound::play("../Sounds/potionDrop.wav");
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
//                QSound::play("../Sounds/potionDrop.wav");
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
//                QSound::play("../Sounds/potionDrop.wav");
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
        ui->pbarCHealth->setEnabled(false);
        ui->pbarEHealth->setEnabled(false);
        ui->btnBattle->setEnabled(false);
        ui->btnUsePotionBS->setEnabled(false);
        ui->btnSave->setEnabled(false);
        ui->pbarCHealth->setValue(0);
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

    if (bandit_->isAlive() && player_->isAlive())
    {
        bandit_->doHit(player_->doSpecialAbility(bandit_->getName()));
        message_ += player_->getMessage() + bandit_->getMessage();
        player_->doHit(bandit_->doAttack(player_->getName()));
        message_ += bandit_->getMessage() + player_->getMessage();
        ui->txtBattleInfo->setText(message_);
        ui->pbarCHealth->setValue(player_->getHealth());
        ui->pbarEHealth->setValue(bandit_->getHealth());
    }
    if (!bandit_->isAlive())
    {
        ui->pbarEHealth->setValue(0);

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
            QSound::play("../Sounds/potionDrop.wav");
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
        ui->pbarCHealth->setEnabled(false);
        ui->pbarEHealth->setEnabled(false);
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
        ui->pbarCHealth->setEnabled(false);
        ui->pbarEHealth->setEnabled(false);
        ui->btnBattle->setEnabled(false);
        ui->btnUsePotionBS->setEnabled(false);
        ui->btnSave->setEnabled(false);
        ui->pbarCHealth->setValue(0);
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
    ui->pbarCHealth->setEnabled(true);
    ui->pbarEHealth->setEnabled(true);
    ui->btnBattle->setEnabled(false);

    ui->tabMenuScreen->setEnabled(false);
    ui->tabActionScreen->setEnabled(false);
    ui->tabCInfoScreen->setEnabled(false);
    ui->tabQuestScreen->setEnabled(false);
    ui->pbarCHealth->setMaximum(player_->getMaxHealth());
    ui->pbarCHealth->setValue(player_->getHealth());
    checkLevel();

    if (bandit_->getEnemyType() == 6)
    {
        ui->txtBattleInfo->setText("You were attacked by Thragg!");
        ui->pbarEHealth->setMaximum(bandit_->getHealth());
        ui->pbarEHealth->setValue(bandit_->getHealth());
        //ui->lblQReward->setText(QString("Reward: %1 XP").arg(quest_->getXPReward()));
        ui->lblPLevel->setText(QString("%1").arg(player_->getLevel()));
        ui->lblELevel->setText(QString("%1").arg(bandit_->getLevel()));
        ui->lblEnemyName->setText(bandit_->getName());
        ui->btnUsePotionBS->setEnabled(true);
    }
    else
    {
        ui->txtBattleInfo->setText("You were attacked by a bandit");
        ui->pbarEHealth->setMaximum(bandit_->getHealth());
        ui->pbarEHealth->setValue(bandit_->getHealth());
        //ui->lblQReward->setText(QString("Reward: %1 XP").arg(quest_->getXPReward()));
        ui->lblPLevel->setText(QString("%1").arg(player_->getLevel()));
        ui->lblELevel->setText(QString("%1").arg(bandit_->getLevel()));
        ui->lblEnemyName->setText(bandit_->getName());
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
    QPushButton *btnInitiateCamp = msgBox.addButton(tr("Initiate Camp"), QMessageBox::ActionRole);
    QPushButton *btnThugCamp     = msgBox.addButton(tr("Thug Camp"), QMessageBox::ActionRole);
    QPushButton *btnBruiserCamp = msgBox.addButton(tr("Bruiser Camp"), QMessageBox::ActionRole);
    QPushButton *btnCutthroatCamp = msgBox.addButton(tr("Cutthroat Camp"), QMessageBox::ActionRole);
    QPushButton *btnEliteCamp = msgBox.addButton(tr("Elite Camp"), QMessageBox::ActionRole);
    QPushButton *btnFightTragg = msgBox.addButton(tr("Fight Thragg"), QMessageBox::ActionRole);
    QPushButton *btnCancel = msgBox.addButton(QMessageBox::Cancel);
    msgBox.exec();

    if (msgBox.clickedButton() == btnInitiateCamp)
    {
        bsAttackSC_->setEnabled(true);
        bsBattleSC_->setEnabled(false);
        QString banditName = "Bandit Initiate";
        int banditHealth = 0;
        int banditMaxAttackPower = 0;
        int banditMinAttackPower = 0;
        int banditCritChance = 0;
        int banditXPReward = 0;
        int banditLevel = (rand() % 3 + 1);
        int banditType = 1;

        if (banditLevel == 1)
        {
            banditHealth = 25;
            banditMaxAttackPower = 5;
            banditMinAttackPower = 1;
            banditCritChance = 100;
            banditXPReward = 6;
        }
        else if (banditLevel == 2)
        {
            banditHealth = 35;
            banditMaxAttackPower = 8;
            banditMinAttackPower = 1;
            banditCritChance = 100;
            banditXPReward = 12;
        }
        else if (banditLevel == 3)
        {
            banditHealth = 50;
            banditMaxAttackPower = 10;
            banditMinAttackPower = 1;
            banditCritChance = 100;
            banditXPReward = 24;
        }

        bandit_ = new Bandit(banditName, banditHealth, banditMaxAttackPower, banditMinAttackPower, banditCritChance, banditXPReward, banditLevel, banditType);
    }
    else if (msgBox.clickedButton() == btnThugCamp)
    {
        bsAttackSC_->setEnabled(true);
        bsBattleSC_->setEnabled(false);
        QString banditName = "Bandit Thug";
        int banditHealth = 0;
        int banditMaxAttackPower = 0;
        int banditMinAttackPower = 0;
        int banditCritChance = 0;
        int banditXPReward = 0;
        // attackDmg_ = rand() % ((maxAttackPower_ + 1) - minAttackPower_) + minAttackPower_;
        int banditLevel = (rand() % ((6 + 1) - 4) + 4);
        int banditType = 2;

        if (banditLevel == 4)
        {
            banditHealth = 100;
            banditMaxAttackPower = 14;
            banditMinAttackPower = 9;
            banditCritChance = 90;
            banditXPReward = 48;
        }
        else if (banditLevel == 5)
        {
            banditHealth = 150;
            banditMaxAttackPower = 17;
            banditMinAttackPower = 9;
            banditCritChance = 90;
            banditXPReward = 60;
        }
        else if (banditLevel == 6)
        {
            banditHealth = 200;
            banditMaxAttackPower = 20;
            banditMinAttackPower = 10;
            banditCritChance = 90;
            banditXPReward = 72;
        }

        bandit_ = new Bandit(banditName, banditHealth, banditMaxAttackPower, banditMinAttackPower, banditCritChance, banditXPReward, banditLevel, banditType);
    }
    else if (msgBox.clickedButton() == btnBruiserCamp)
    {
        bsAttackSC_->setEnabled(true);
        bsBattleSC_->setEnabled(false);
        QString banditName = "Bandit Bruiser";
        int banditHealth = 0;
        int banditMaxAttackPower = 0;
        int banditMinAttackPower = 0;
        int banditCritChance = 0;
        int banditXPReward = 0;
        // attackDmg_ = rand() % ((maxAttackPower_ + 1) - minAttackPower_) + minAttackPower_;
        int banditLevel = (rand() % ((9 + 1) - 7) + 7);
        int banditType = 3;

        if (banditLevel == 7)
        {
            banditHealth = 300;
            banditMaxAttackPower = 24;
            banditMinAttackPower = 12;
            banditCritChance = 90;
            banditXPReward = 204;
        }
        else if (banditLevel == 8)
        {
            banditHealth = 350;
            banditMaxAttackPower = 27;
            banditMinAttackPower = 12;
            banditCritChance = 90;
            banditXPReward = 252;
        }
        else if (banditLevel == 9)
        {
            banditHealth = 400;
            banditMaxAttackPower = 30;
            banditMinAttackPower = 15;
            banditCritChance = 90;
            banditXPReward = 300;
        }

        bandit_ = new Bandit(banditName, banditHealth, banditMaxAttackPower, banditMinAttackPower, banditCritChance, banditXPReward, banditLevel, banditType);
    }
    else if (msgBox.clickedButton() == btnCutthroatCamp)
    {
        bsAttackSC_->setEnabled(true);
        bsBattleSC_->setEnabled(false);
        QString banditName = "Bandit Cutthroat";
        int banditHealth = 0;
        int banditMaxAttackPower = 0;
        int banditMinAttackPower = 0;
        int banditCritChance = 0;
        int banditXPReward = 0;
        // attackDmg_ = rand() % ((maxAttackPower_ + 1) - minAttackPower_) + minAttackPower_;
        int banditLevel = (rand() % ((12 + 1) - 10) + 10);
        int banditType = 4;

        if (banditLevel == 10)
        {
            banditHealth = 600;
            banditMaxAttackPower = 34;
            banditMinAttackPower = 20;
            banditCritChance = 80;
            banditXPReward = 504;
        }
        else if (banditLevel == 11)
        {
            banditHealth = 650;
            banditMaxAttackPower = 37;
            banditMinAttackPower = 20;
            banditCritChance = 80;
            banditXPReward = 600;
        }
        else if (banditLevel == 12)
        {
            banditHealth = 700;
            banditMaxAttackPower = 40;
            banditMinAttackPower = 25;
            banditCritChance = 80;
            banditXPReward = 702;
        }

        bandit_ = new Bandit(banditName, banditHealth, banditMaxAttackPower, banditMinAttackPower, banditCritChance, banditXPReward, banditLevel, banditType);
    }
    else if (msgBox.clickedButton() == btnEliteCamp)
    {
        bsAttackSC_->setEnabled(true);
        bsBattleSC_->setEnabled(false);
        QString banditName = "Bandit Elite";
        int banditHealth = 0;
        int banditMaxAttackPower = 0;
        int banditMinAttackPower = 0;
        int banditCritChance = 0;
        int banditXPReward = 0;
        // attackDmg_ = rand() % ((maxAttackPower_ + 1) - minAttackPower_) + minAttackPower_;
        int banditLevel = (rand() % ((14 + 1) - 13) + 13);
        int banditType = 5;

        if (banditLevel == 13)
        {
            banditHealth = 1000;
            banditMaxAttackPower = 40;
            banditMinAttackPower = 25;
            banditCritChance = 60;
            banditXPReward = 5000;
        }
        else if (banditLevel == 14)
        {
            banditHealth = 1100;
            banditMaxAttackPower = 40;
            banditMinAttackPower = 30;
            banditCritChance = 60;
            banditXPReward = 6000;
        }

        bandit_ = new Bandit(banditName, banditHealth, banditMaxAttackPower, banditMinAttackPower, banditCritChance, banditXPReward, banditLevel, banditType);
    }
    else if (msgBox.clickedButton() == btnFightTragg)
    {
        if (player_->getLevel() < 15)
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Choose A Bandit Camp To Attack");
            msgBox.setText("You are not yet strong enough to face Thragg");
            msgBox.exec();
            ui->tabActionScreen->setEnabled(true);
            ui->tabCInfoScreen->setEnabled(true);
            ui->tabMenuScreen->setEnabled(true);
            ui->tabQuestScreen->setEnabled(true);

            ui->txtBattleInfo->setEnabled(false);
            ui->btnAttack->setEnabled(false);
            ui->btnSpecialAbility->setEnabled(false);
            ui->pbarCHealth->setEnabled(false);
            ui->pbarEHealth->setEnabled(false);
            ui->btnBattle->setEnabled(true);
            bsBattleSC_->setEnabled(true);
        }
        else
        {
            bsAttackSC_->setEnabled(true);
            bsBattleSC_->setEnabled(false);
            QString banditName = "Thragg";
            int banditHealth = 0;
            int banditMaxAttackPower = 0;
            int banditMinAttackPower = 0;
            int banditCritChance = 0;
            int banditXPReward = 0;
            // attackDmg_ = rand() % ((maxAttackPower_ + 1) - minAttackPower_) + minAttackPower_;
            int banditLevel = 15;
            int banditType = 6;

            banditHealth = 5000;
            banditMaxAttackPower = 50;
            banditMinAttackPower = 35;
            banditCritChance = 40;
            banditXPReward = 2000000;


            bandit_ = new Bandit(banditName, banditHealth, banditMaxAttackPower, banditMinAttackPower, banditCritChance, banditXPReward, banditLevel, banditType);
        }
    }
    else if (msgBox.clickedButton() == btnCancel)
    {
        ui->tabActionScreen->setEnabled(true);
        ui->tabCInfoScreen->setEnabled(true);
        ui->tabMenuScreen->setEnabled(true);
        ui->tabQuestScreen->setEnabled(true);

        ui->txtBattleInfo->setEnabled(false);
        ui->btnAttack->setEnabled(false);
        ui->pbarCHealth->setEnabled(false);
        ui->pbarEHealth->setEnabled(false);
        ui->btnBattle->setEnabled(true);
        ui->pbarEHealth->setMaximum(1);
        ui->pbarEHealth->setValue(0);
        ui->lblELevel->setText(" ");
        ui->lblEnemyName->setText(" ");
    }
    else
    {
        ui->tabActionScreen->setEnabled(true);
        ui->tabCInfoScreen->setEnabled(true);
        ui->tabMenuScreen->setEnabled(true);
        ui->tabQuestScreen->setEnabled(true);

        ui->txtBattleInfo->setEnabled(false);
        ui->btnAttack->setEnabled(false);
        ui->pbarCHealth->setEnabled(false);
        ui->pbarEHealth->setEnabled(false);
        ui->btnBattle->setEnabled(true);
        ui->pbarEHealth->setMaximum(1);
        ui->pbarEHealth->setValue(0);
        ui->lblELevel->setText(" ");
        ui->lblEnemyName->setText(" ");
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
    //health, maxHealth, maxAttackPower, minAttackPower, critChance
    player_ = new Player(100, 100, 10, 1, 50);
    bool ok;
    name_ = QInputDialog::getText(this, tr("Character Creation"), tr("Enter a character name:"), QLineEdit::Normal, "", &ok);

    if(ok)
        player_->setName(name_);
}

void GameLogic::on_btnSave_clicked()
{
    player_->save();
    quest_->save();
    QMessageBox msgBox;
    msgBox.setWindowTitle("Save Game");
    msgBox.setText("      Game Saved.            ");
    msgBox.exec();
}

void GameLogic::on_btnLoad_clicked()
{
    player_->load();
    quest_->load();
    ui->btnSave->setEnabled(true);
    ui->tabActionScreen->setEnabled(true);
    ui->tabCInfoScreen->setEnabled(true);
    ui->tabQuestScreen->setEnabled(true);
    ui->btnBattle->setEnabled(true);
    msSaveGameSC_->setEnabled(true);

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
    ui->pbarCHealth->setValue(0);
    ui->pbarEHealth->setValue(0);
    ui->txtBattleInfo->setText("");

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

    QMessageBox msgBox;
    msgBox.setWindowTitle("Load Game");
    msgBox.setText("      Game Loaded.            ");
    msgBox.exec();
}

void GameLogic::on_btnUsePotion_clicked()
{
    player_->usePotion();
    setPlayerInfo();
    ui->lblPotionAmount->setText(QString("Potions: %1").arg(player_->getPotion()));
    ui->pbarCHealth->setMaximum(player_->getMaxHealth());
    ui->pbarCHealth->setValue(player_->getHealth());
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
    ui->lblCCritChance->setText(QString("Critical Hit Chance: %1").arg(player_->getCritChance()));
    ui->lblCXP->setText(QString("Experience: %1/%2").arg(player_->getXP()).arg(player_->getXPTillLevel()));
    ui->lblCXPTillLvl->setText(QString("XP till next level: %1").arg(player_->getXPTillLevel() - player_->getXP()));
    ui->lblCSkillPoints->setText(QString("Skill Points: %1").arg(player_->getSkillPoints()));
    ui->lblGoldAmount->setText(QString("Gold: %1").arg(player_->getGold()));
    ui->lblPotionAmount->setText(QString("Potions: %1").arg(player_->getPotion()));
    double xpPercent = (double(player_->getXP()) / double(player_->getXPTillLevel())) * 100;
    ui->pbarXP->setValue(int(xpPercent));
}

void GameLogic::on_btnUsePotionBS_clicked()
{
    player_->usePotion();
    ui->pbarCHealth->setValue(player_->getHealth());
    ui->lblPotionAmount->setText(QString("Potions: %1").arg(player_->getPotion()));
}

void GameLogic::checkSkillPoints()
{
    if (player_->getSkillPoints() >= 1)
    {
        ui->btnIncreaseAttack->setEnabled(true);
        ui->btnIncreaseHP->setEnabled(true);
        ui->btnIncreaseCritChance->setEnabled(true);
    }
    else if (player_->getSkillPoints() == 0)
    {
        ui->btnIncreaseAttack->setEnabled(false);
        ui->btnIncreaseHP->setEnabled(false);
        ui->btnIncreaseCritChance->setEnabled(false);
        csAddHPSC_->setEnabled(false);
        csAddAPSC_->setEnabled(false);
        csAddCCSC_->setEnabled(false);
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
            ui->lblQReward->setText(QString("Reward: %1 XP").arg(quest_->getXPReward()));

            quest_->setObjectiveProgress(questText);
        }
        else if (quest_->getIsQuestActive() == 1 && quest_->getAmountComplete() == quest_->getObjective())
        {
            ui->lblQTitle->setText(QString("Kill %1 Bandit Initiates").arg(quest_->getObjective()));
            ui->lblQProgress->setText(QString("Progress: %1/%2 Bandit Initiates killed.").arg(quest_->getAmountComplete()).arg(quest_->getObjective()));
            ui->lblQReward->setText(QString("Reward: %1 XP").arg(quest_->getXPReward()));
            QSound::play("../Sounds/questComplete.wav");
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
            QString questText = QString("Progress: %1/%2 Bandit Thugs killed.").arg(quest_->getAmountComplete()).arg(quest_->getObjective());
            ui->lblQTitle->setText(QString("Kill %1 Bandit Thugs").arg(quest_->getObjective()));
            ui->lblQProgress->setText(questText);
            ui->lblQReward->setText(QString("Reward: %1 XP").arg(quest_->getXPReward()));

            quest_->setObjectiveProgress(questText);
        }
        else if (quest_->getIsQuestActive() == 1 && quest_->getAmountComplete() == quest_->getObjective())
        {
            ui->lblQTitle->setText(QString("Kill %1 Bandit Thugs").arg(quest_->getObjective()));
            ui->lblQProgress->setText(QString("Progress: %1/%2 Bandit Thugs killed.").arg(quest_->getAmountComplete()).arg(quest_->getObjective()));
            ui->lblQReward->setText(QString("Reward: %1 XP").arg(quest_->getXPReward()));
            QSound::play("../Sounds/questComplete.wav");
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
            QString questText = QString("Progress: %1/%2 Bandit Bruisers killed.").arg(quest_->getAmountComplete()).arg(quest_->getObjective());
            ui->lblQTitle->setText(QString("Kill %1 Bandit Bruisers").arg(quest_->getObjective()));
            ui->lblQProgress->setText(questText);
            ui->lblQReward->setText(QString("Reward: %1 XP").arg(quest_->getXPReward()));

            quest_->setObjectiveProgress(questText);
        }
        else if (quest_->getIsQuestActive() == 1 && quest_->getAmountComplete() == quest_->getObjective())
        {
            ui->lblQTitle->setText(QString("Kill %1 Bandit Bruisers").arg(quest_->getObjective()));
            ui->lblQProgress->setText(QString("Progress: %1/%2 Bandit Bruisers killed.").arg(quest_->getAmountComplete()).arg(quest_->getObjective()));
            ui->lblQReward->setText(QString("Reward: %1 XP").arg(quest_->getXPReward()));
            QSound::play("../Sounds/questComplete.wav");
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
            QString questText = QString("Progress: %1/%2 Bandit Cutthroats killed.").arg(quest_->getAmountComplete()).arg(quest_->getObjective());
            ui->lblQTitle->setText(QString("Kill %1 Bandit Cutthroats").arg(quest_->getObjective()));
            ui->lblQProgress->setText(questText);
            ui->lblQReward->setText(QString("Reward: %1 XP").arg(quest_->getXPReward()));

            quest_->setObjectiveProgress(questText);
        }
        else if (quest_->getIsQuestActive() == 1 && quest_->getAmountComplete() == quest_->getObjective())
        {
            ui->lblQTitle->setText(QString("Kill %1 Bandit Cutthroats").arg(quest_->getObjective()));
            ui->lblQProgress->setText(QString("Progress: %1/%2 Bandit Cutthroats killed.").arg(quest_->getAmountComplete()).arg(quest_->getObjective()));
            ui->lblQReward->setText(QString("Reward: %1 XP").arg(quest_->getXPReward()));
            QSound::play("../Sounds/questComplete.wav");
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
            QString questText = QString("Progress: %1/%2 Bandit Elites killed.").arg(quest_->getAmountComplete()).arg(quest_->getObjective());
            ui->lblQTitle->setText(QString("Kill %1 Bandit Elites").arg(quest_->getObjective()));
            ui->lblQProgress->setText(questText);
            ui->lblQReward->setText(QString("Reward: %1 XP").arg(quest_->getXPReward()));

            quest_->setObjectiveProgress(questText);
        }
        else if (quest_->getIsQuestActive() == 1 && quest_->getAmountComplete() == quest_->getObjective())
        {
            ui->lblQTitle->setText(QString("Kill %1 Bandit Elites").arg(quest_->getObjective()));
            ui->lblQProgress->setText(QString("Progress: %1/%2 Bandit Elites killed.").arg(quest_->getAmountComplete()).arg(quest_->getObjective()));
            ui->lblQReward->setText(QString("Reward: %1 XP").arg(quest_->getXPReward()));
            QSound::play("../Sounds/questComplete.wav");
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
            //QString questText = QString("Progress: Kill Thragg.");
            ui->lblQTitle->setText(quest_->getQuestTitle());
            ui->lblQProgress->setText(quest_->getObjectiveProgress());
            ui->lblQReward->setText(QString("Reward: %1 XP").arg(quest_->getXPReward()));
        }
        else if (quest_->getIsQuestActive() == 1 && quest_->getAmountComplete() == quest_->getObjective())
        {
            ui->lblQTitle->setText(quest_->getQuestTitle());
            ui->lblQProgress->setText(QString("Progress: Thragg Killed."));
            ui->lblQReward->setText(QString("Reward: %1 XP").arg(quest_->getXPReward()));
            QSound::play("../Sounds/questComplete.wav");
            QMessageBox msgBox;
            msgBox.setWindowTitle("Quest");
            msgBox.setText("Quest Completed!");
            msgBox.exec();
            quest_->setIsQuestActive(0);
        }
    }
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
    player_->setMaxHealth(10);
    player_->setHealth(player_->getMaxHealth());
    ui->lblCHealth->setText(QString("Health: %1/%2").arg(player_->getHealth()).arg(player_->getMaxHealth()));
    player_->setSkillPoints(1);
    ui->lblCSkillPoints->setText(QString("Skill Points: %1").arg(player_->getSkillPoints()));
    checkSkillPoints();
}

void GameLogic::on_btnIncreaseAttack_clicked()
{
    player_->setMaxAttackPower(5);
    player_->setMinAttackPower(10);
    ui->lblCAttack->setText(QString("Attack: %1-%2").arg(player_->getMinAttackPower()).arg(player_->getMaxAttackPower()));
    player_->setSkillPoints(1);
    ui->lblCSkillPoints->setText(QString("Skill Points: %1").arg(player_->getSkillPoints()));
    checkSkillPoints();
}

void GameLogic::on_btnIncreaseCritChance_clicked()
{
    if (player_->getCritChance() > 5)
    {
        player_->setCritChance(5);
        ui->lblCCritChance->setText(QString("Critical Hit Chance: %1").arg(player_->getCritChance()));
        player_->setSkillPoints(1);
        ui->lblCSkillPoints->setText(QString("Skill Points: %1").arg(player_->getSkillPoints()));
    }
    checkSkillPoints();
}

void GameLogic::on_btnBeginQuest_clicked()
{
    QString questTitle = "";
    QString questText = "";

    QMessageBox msgBox;
    msgBox.setWindowTitle("Choose A Quest");
    msgBox.setText("Choose a quest to embark on.");
    QPushButton *btnInitiateKills = msgBox.addButton(tr("Initiate Kills"), QMessageBox::ActionRole);
    QPushButton *btnThugKills     = msgBox.addButton(tr("Thug Kills"), QMessageBox::ActionRole);
    QPushButton *btnBruiserKills = msgBox.addButton(tr("Bruiser Kills"), QMessageBox::ActionRole);
    QPushButton *btnCutthroatKills = msgBox.addButton(tr("Cutthroat Kills"), QMessageBox::ActionRole);
    QPushButton *btnEliteKills = msgBox.addButton(tr("Elite Kills"), QMessageBox::ActionRole);
    QPushButton *btnThraggKill = msgBox.addButton(tr("Kill Thragg"), QMessageBox::ActionRole);
    QPushButton *btnCancel = msgBox.addButton(QMessageBox::Cancel);
    msgBox.exec();

    if (msgBox.clickedButton() == btnInitiateKills)
    {
        QSound::play("../Sounds/acceptQuest.wav");
        //xpReward, objective, amountComplete, isQuestComplete, isQuestActive, questType
        quest_ = new quests(100, 10, 0, 0, 1, 1);
        questTitle = QString("Kill %1 Bandit Initiates").arg(quest_->getObjective());
        questText = QString("Progress: %1/%2 Bandit Initiates killed.").arg(quest_->getAmountComplete()).arg(quest_->getObjective());

    }
    else if (msgBox.clickedButton() == btnThugKills)
    {
        QSound::play("../Sounds/acceptQuest.wav");
        //xpReward, objective, amountComplete, isQuestComplete, isQuestActive, questType
        quest_ = new quests(250, 10, 0, 0, 1, 2);
        questTitle = QString("Kill %1 Bandit Thugs").arg(quest_->getObjective());
        questText = QString("Progress: %1/%2 Bandit Thugs killed.").arg(quest_->getAmountComplete()).arg(quest_->getObjective());

    }
    else if (msgBox.clickedButton() == btnBruiserKills)
    {
        QSound::play("../Sounds/acceptQuest.wav");
        //xpReward, objective, amountComplete, isQuestComplete, isQuestActive, questType
        quest_ = new quests(1500, 10, 0, 0, 1, 3);
        questTitle = QString("Kill %1 Bandit Bruisers").arg(quest_->getObjective());
        questText = QString("Progress: %1/%2 Bandit Bruisers killed.").arg(quest_->getAmountComplete()).arg(quest_->getObjective());

    }
    else if (msgBox.clickedButton() == btnCutthroatKills)
    {
        QSound::play("../Sounds/acceptQuest.wav");
        //xpReward, objective, amountComplete, isQuestComplete, isQuestActive, questType
        quest_ = new quests(9000, 6, 0, 0, 1, 4);
        questTitle = QString("Kill %1 Bandit Cutthroats").arg(quest_->getObjective());
        questText = QString("Progress: %1/%2 Bandit Cutthroats killed.").arg(quest_->getAmountComplete()).arg(quest_->getObjective());

    }
    else if (msgBox.clickedButton() == btnEliteKills)
    {
        QSound::play("../Sounds/acceptQuest.wav");
        //xpReward, objective, amountComplete, isQuestComplete, isQuestActive, questType
        quest_ = new quests(25000, 5, 0, 0, 1, 5);
        questTitle = QString("Kill %1 Bandit Elites").arg(quest_->getObjective());
        questText = QString("Progress: %1/%2 Bandit Elites killed.").arg(quest_->getAmountComplete()).arg(quest_->getObjective());

    }
    else if (msgBox.clickedButton() == btnThraggKill)
    {
        QSound::play("../Sounds/acceptQuest.wav");
        //xpReward, objective, amountComplete, isQuestComplete, isQuestActive, questType
        quest_ = new quests(3000000, 1, 0, 0, 1, 6);
        questTitle = QString("Kill Thragg, the leader of the Bandits");
        questText = QString("Progress: Kill Thragg");

    }
    else if (msgBox.clickedButton() == btnCancel)
    {
        QSound::play("../Sounds/abondonQuest.wav");
        //xpReward, objective, amountComplete, isQuestComplete, isQuestActive, questType
        quest_ = new quests(0, 0, 0, 0, 0, 0);
    }
    else
    {
        QSound::play("../Sounds/abondonQuest.wav");
        //xpReward, objective, amountComplete, isQuestComplete, isQuestActive, questType
        quest_ = new quests(0, 0, 0, 0, 0, 0);
    }

    if (quest_->getIsQuestActive() == 1)
    {
        quest_->setQuestTitle(questTitle);
        quest_->setObjectiveProgress(questText);
        ui->lblQTitle->setText(quest_->getQuestTitle());
        ui->lblQProgress->setText(quest_->getObjectiveProgress());
        ui->lblQReward->setText(QString("Reward: %1 XP").arg(quest_->getXPReward()));
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
    int isQuestComplete = 0;
    quest_->completeQuest();
    isQuestComplete = quest_->getIsQuestComplete();

    if (isQuestComplete == 1)
    {
        if (quest_->getQuestTitle().toLower().contains("thragg"))
        {
            QSound::play("../Sounds/deathOfThragg.wav");
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
            QSound::play("../Sounds/questComplete.wav");
            QMessageBox msgBox;
            msgBox.setWindowTitle("Quest Progress");
            msgBox.setText("<b>" + quest_->getQuestTitle() + "</b>");
            msgBox.setInformativeText(QString("Quest complete!\nYou are rewarded %1 XP!").arg(quest_->getXPReward()));
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
    QSound::play("../Sounds/abondonQuest.wav");
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
