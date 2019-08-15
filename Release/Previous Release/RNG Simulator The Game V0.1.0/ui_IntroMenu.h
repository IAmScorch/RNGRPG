/********************************************************************************
** Form generated from reading UI file 'IntroMenu.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTROMENU_H
#define UI_INTROMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameLogic
{
public:
    QWidget *centralWidget;
    QTabWidget *tabGame;
    QWidget *tabMenuScreen;
    QPushButton *btnNewGame;
    QPushButton *btnQuit;
    QPushButton *btnSave;
    QPushButton *btnLoad;
    QLabel *lblMenuTabBG;
    QWidget *tabActionScreen;
    QPushButton *btnBuyPotion;
    QPushButton *btnUsePotion;
    QLabel *lblGoldAmount;
    QLabel *lblPotionAmount;
    QLabel *lblActionTabBG;
    QWidget *tabBattleScreen;
    QTextEdit *txtBattleInfo;
    QPushButton *btnAttack;
    QProgressBar *pbarCHealth;
    QProgressBar *pbarEHealth;
    QLabel *lblEnemyName;
    QPushButton *btnBattle;
    QPushButton *btnUsePotionBS;
    QLabel *lblPLevel;
    QLabel *lblELevel;
    QPushButton *btnSpecialAbility;
    QLabel *lblBattleTabBG;
    QWidget *tabCInfoScreen;
    QLabel *lblCName;
    QLabel *lblCHealth;
    QLabel *lblCAttack;
    QLabel *lblCLevel;
    QLabel *lblCCritChance;
    QLabel *lblCXP;
    QLabel *lblCXPTillLvl;
    QPushButton *btnIncreaseHP;
    QPushButton *btnIncreaseAttack;
    QPushButton *btnIncreaseCritChance;
    QLabel *lblCSkillPoints;
    QLabel *lblCharTabBG;
    QWidget *tabQuestScreen;
    QPushButton *btnBeginQuest;
    QPushButton *btnCompleteQuest;
    QLabel *lblQTitle;
    QLabel *lblQProgress;
    QLabel *lblQReward;
    QPushButton *btnAbandonQuest;
    QLabel *lblQuestTabBG;
    QProgressBar *pbarXP;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *GameLogic)
    {
        if (GameLogic->objectName().isEmpty())
            GameLogic->setObjectName(QStringLiteral("GameLogic"));
        GameLogic->resize(400, 306);
        centralWidget = new QWidget(GameLogic);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabGame = new QTabWidget(centralWidget);
        tabGame->setObjectName(QStringLiteral("tabGame"));
        tabGame->setEnabled(true);
        tabGame->setGeometry(QRect(0, -1, 401, 281));
        tabMenuScreen = new QWidget();
        tabMenuScreen->setObjectName(QStringLiteral("tabMenuScreen"));
        btnNewGame = new QPushButton(tabMenuScreen);
        btnNewGame->setObjectName(QStringLiteral("btnNewGame"));
        btnNewGame->setGeometry(QRect(220, 10, 151, 61));
        QFont font;
        font.setPointSize(16);
        btnNewGame->setFont(font);
        btnNewGame->setStyleSheet(QStringLiteral(""));
        btnNewGame->setFlat(false);
        btnQuit = new QPushButton(tabMenuScreen);
        btnQuit->setObjectName(QStringLiteral("btnQuit"));
        btnQuit->setGeometry(QRect(220, 190, 151, 61));
        btnQuit->setFont(font);
        btnQuit->setFlat(false);
        btnSave = new QPushButton(tabMenuScreen);
        btnSave->setObjectName(QStringLiteral("btnSave"));
        btnSave->setEnabled(false);
        btnSave->setGeometry(QRect(220, 70, 151, 61));
        btnSave->setFont(font);
        btnSave->setFlat(false);
        btnLoad = new QPushButton(tabMenuScreen);
        btnLoad->setObjectName(QStringLiteral("btnLoad"));
        btnLoad->setGeometry(QRect(220, 130, 151, 61));
        btnLoad->setFont(font);
        btnLoad->setFlat(false);
        lblMenuTabBG = new QLabel(tabMenuScreen);
        lblMenuTabBG->setObjectName(QStringLiteral("lblMenuTabBG"));
        lblMenuTabBG->setGeometry(QRect(-60, -60, 501, 333));
        tabGame->addTab(tabMenuScreen, QString());
        lblMenuTabBG->raise();
        btnNewGame->raise();
        btnQuit->raise();
        btnSave->raise();
        btnLoad->raise();
        tabActionScreen = new QWidget();
        tabActionScreen->setObjectName(QStringLiteral("tabActionScreen"));
        btnBuyPotion = new QPushButton(tabActionScreen);
        btnBuyPotion->setObjectName(QStringLiteral("btnBuyPotion"));
        btnBuyPotion->setGeometry(QRect(10, 60, 91, 41));
        QFont font1;
        font1.setPointSize(10);
        btnBuyPotion->setFont(font1);
        btnUsePotion = new QPushButton(tabActionScreen);
        btnUsePotion->setObjectName(QStringLiteral("btnUsePotion"));
        btnUsePotion->setGeometry(QRect(10, 110, 91, 41));
        btnUsePotion->setFont(font1);
        lblGoldAmount = new QLabel(tabActionScreen);
        lblGoldAmount->setObjectName(QStringLiteral("lblGoldAmount"));
        lblGoldAmount->setGeometry(QRect(110, 60, 151, 41));
        lblGoldAmount->setFont(font1);
        lblGoldAmount->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        lblPotionAmount = new QLabel(tabActionScreen);
        lblPotionAmount->setObjectName(QStringLiteral("lblPotionAmount"));
        lblPotionAmount->setGeometry(QRect(110, 110, 151, 41));
        lblPotionAmount->setFont(font1);
        lblPotionAmount->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        lblActionTabBG = new QLabel(tabActionScreen);
        lblActionTabBG->setObjectName(QStringLiteral("lblActionTabBG"));
        lblActionTabBG->setGeometry(QRect(-60, -60, 1001, 665));
        tabGame->addTab(tabActionScreen, QString());
        lblActionTabBG->raise();
        btnBuyPotion->raise();
        btnUsePotion->raise();
        lblGoldAmount->raise();
        lblPotionAmount->raise();
        tabBattleScreen = new QWidget();
        tabBattleScreen->setObjectName(QStringLiteral("tabBattleScreen"));
        txtBattleInfo = new QTextEdit(tabBattleScreen);
        txtBattleInfo->setObjectName(QStringLiteral("txtBattleInfo"));
        txtBattleInfo->setGeometry(QRect(10, 0, 371, 131));
        QFont font2;
        font2.setFamily(QStringLiteral("Kalinga"));
        font2.setBold(true);
        font2.setWeight(75);
        txtBattleInfo->setFont(font2);
        txtBattleInfo->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255, 100);"));
        txtBattleInfo->setReadOnly(true);
        btnAttack = new QPushButton(tabBattleScreen);
        btnAttack->setObjectName(QStringLiteral("btnAttack"));
        btnAttack->setGeometry(QRect(10, 140, 125, 21));
        btnAttack->setFont(font1);
        pbarCHealth = new QProgressBar(tabBattleScreen);
        pbarCHealth->setObjectName(QStringLiteral("pbarCHealth"));
        pbarCHealth->setGeometry(QRect(10, 190, 125, 23));
        pbarCHealth->setStyleSheet(QStringLiteral(""));
        pbarCHealth->setMaximum(100);
        pbarCHealth->setValue(0);
        pbarCHealth->setAlignment(Qt::AlignCenter);
        pbarCHealth->setTextVisible(true);
        pbarCHealth->setInvertedAppearance(false);
        pbarEHealth = new QProgressBar(tabBattleScreen);
        pbarEHealth->setObjectName(QStringLiteral("pbarEHealth"));
        pbarEHealth->setGeometry(QRect(260, 190, 125, 23));
        pbarEHealth->setValue(0);
        pbarEHealth->setAlignment(Qt::AlignCenter);
        lblEnemyName = new QLabel(tabBattleScreen);
        lblEnemyName->setObjectName(QStringLiteral("lblEnemyName"));
        lblEnemyName->setGeometry(QRect(260, 140, 125, 41));
        QFont font3;
        font3.setPointSize(10);
        font3.setBold(true);
        font3.setWeight(75);
        font3.setStrikeOut(false);
        lblEnemyName->setFont(font3);
        lblEnemyName->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        lblEnemyName->setAlignment(Qt::AlignCenter);
        btnBattle = new QPushButton(tabBattleScreen);
        btnBattle->setObjectName(QStringLiteral("btnBattle"));
        btnBattle->setGeometry(QRect(150, 140, 91, 41));
        btnBattle->setFont(font1);
        btnUsePotionBS = new QPushButton(tabBattleScreen);
        btnUsePotionBS->setObjectName(QStringLiteral("btnUsePotionBS"));
        btnUsePotionBS->setGeometry(QRect(150, 190, 91, 41));
        btnUsePotionBS->setFont(font1);
        lblPLevel = new QLabel(tabBattleScreen);
        lblPLevel->setObjectName(QStringLiteral("lblPLevel"));
        lblPLevel->setGeometry(QRect(10, 222, 125, 21));
        QFont font4;
        font4.setPointSize(12);
        font4.setBold(true);
        font4.setWeight(75);
        lblPLevel->setFont(font4);
        lblPLevel->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        lblPLevel->setAlignment(Qt::AlignCenter);
        lblELevel = new QLabel(tabBattleScreen);
        lblELevel->setObjectName(QStringLiteral("lblELevel"));
        lblELevel->setGeometry(QRect(260, 220, 125, 23));
        lblELevel->setFont(font4);
        lblELevel->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        lblELevel->setAlignment(Qt::AlignCenter);
        btnSpecialAbility = new QPushButton(tabBattleScreen);
        btnSpecialAbility->setObjectName(QStringLiteral("btnSpecialAbility"));
        btnSpecialAbility->setGeometry(QRect(10, 160, 125, 21));
        btnSpecialAbility->setFont(font1);
        lblBattleTabBG = new QLabel(tabBattleScreen);
        lblBattleTabBG->setObjectName(QStringLiteral("lblBattleTabBG"));
        lblBattleTabBG->setGeometry(QRect(-90, -70, 601, 335));
        tabGame->addTab(tabBattleScreen, QString());
        lblBattleTabBG->raise();
        btnSpecialAbility->raise();
        txtBattleInfo->raise();
        pbarCHealth->raise();
        pbarEHealth->raise();
        lblEnemyName->raise();
        btnBattle->raise();
        btnUsePotionBS->raise();
        lblPLevel->raise();
        lblELevel->raise();
        btnAttack->raise();
        tabCInfoScreen = new QWidget();
        tabCInfoScreen->setObjectName(QStringLiteral("tabCInfoScreen"));
        lblCName = new QLabel(tabCInfoScreen);
        lblCName->setObjectName(QStringLiteral("lblCName"));
        lblCName->setGeometry(QRect(10, 10, 251, 21));
        lblCName->setFont(font1);
        lblCName->setAutoFillBackground(false);
        lblCName->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        lblCHealth = new QLabel(tabCInfoScreen);
        lblCHealth->setObjectName(QStringLiteral("lblCHealth"));
        lblCHealth->setGeometry(QRect(10, 40, 251, 21));
        lblCHealth->setFont(font1);
        lblCHealth->setAutoFillBackground(false);
        lblCHealth->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        lblCAttack = new QLabel(tabCInfoScreen);
        lblCAttack->setObjectName(QStringLiteral("lblCAttack"));
        lblCAttack->setGeometry(QRect(10, 70, 251, 21));
        lblCAttack->setFont(font1);
        lblCAttack->setAutoFillBackground(false);
        lblCAttack->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        lblCLevel = new QLabel(tabCInfoScreen);
        lblCLevel->setObjectName(QStringLiteral("lblCLevel"));
        lblCLevel->setGeometry(QRect(10, 100, 251, 21));
        lblCLevel->setFont(font1);
        lblCLevel->setAutoFillBackground(false);
        lblCLevel->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        lblCCritChance = new QLabel(tabCInfoScreen);
        lblCCritChance->setObjectName(QStringLiteral("lblCCritChance"));
        lblCCritChance->setGeometry(QRect(10, 150, 251, 21));
        lblCCritChance->setFont(font1);
        lblCCritChance->setAutoFillBackground(false);
        lblCCritChance->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        lblCXP = new QLabel(tabCInfoScreen);
        lblCXP->setObjectName(QStringLiteral("lblCXP"));
        lblCXP->setGeometry(QRect(10, 180, 251, 21));
        lblCXP->setFont(font1);
        lblCXP->setAutoFillBackground(false);
        lblCXP->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        lblCXPTillLvl = new QLabel(tabCInfoScreen);
        lblCXPTillLvl->setObjectName(QStringLiteral("lblCXPTillLvl"));
        lblCXPTillLvl->setGeometry(QRect(10, 210, 251, 21));
        lblCXPTillLvl->setFont(font1);
        lblCXPTillLvl->setAutoFillBackground(false);
        lblCXPTillLvl->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        btnIncreaseHP = new QPushButton(tabCInfoScreen);
        btnIncreaseHP->setObjectName(QStringLiteral("btnIncreaseHP"));
        btnIncreaseHP->setEnabled(false);
        btnIncreaseHP->setGeometry(QRect(270, 40, 23, 23));
        btnIncreaseHP->setFont(font1);
        btnIncreaseAttack = new QPushButton(tabCInfoScreen);
        btnIncreaseAttack->setObjectName(QStringLiteral("btnIncreaseAttack"));
        btnIncreaseAttack->setEnabled(false);
        btnIncreaseAttack->setGeometry(QRect(270, 70, 23, 23));
        btnIncreaseAttack->setFont(font1);
        btnIncreaseCritChance = new QPushButton(tabCInfoScreen);
        btnIncreaseCritChance->setObjectName(QStringLiteral("btnIncreaseCritChance"));
        btnIncreaseCritChance->setEnabled(false);
        btnIncreaseCritChance->setGeometry(QRect(270, 150, 23, 23));
        btnIncreaseCritChance->setFont(font1);
        lblCSkillPoints = new QLabel(tabCInfoScreen);
        lblCSkillPoints->setObjectName(QStringLiteral("lblCSkillPoints"));
        lblCSkillPoints->setGeometry(QRect(270, 10, 100, 21));
        lblCSkillPoints->setFont(font1);
        lblCSkillPoints->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        lblCharTabBG = new QLabel(tabCInfoScreen);
        lblCharTabBG->setObjectName(QStringLiteral("lblCharTabBG"));
        lblCharTabBG->setGeometry(QRect(-370, -10, 1001, 665));
        tabGame->addTab(tabCInfoScreen, QString());
        lblCharTabBG->raise();
        lblCName->raise();
        lblCHealth->raise();
        lblCAttack->raise();
        lblCLevel->raise();
        lblCCritChance->raise();
        lblCXP->raise();
        lblCXPTillLvl->raise();
        btnIncreaseHP->raise();
        btnIncreaseAttack->raise();
        btnIncreaseCritChance->raise();
        lblCSkillPoints->raise();
        tabQuestScreen = new QWidget();
        tabQuestScreen->setObjectName(QStringLiteral("tabQuestScreen"));
        btnBeginQuest = new QPushButton(tabQuestScreen);
        btnBeginQuest->setObjectName(QStringLiteral("btnBeginQuest"));
        btnBeginQuest->setGeometry(QRect(10, 200, 125, 41));
        btnBeginQuest->setAutoFillBackground(false);
        btnBeginQuest->setStyleSheet(QStringLiteral(""));
        btnBeginQuest->setCheckable(false);
        btnBeginQuest->setAutoDefault(false);
        btnBeginQuest->setFlat(false);
        btnCompleteQuest = new QPushButton(tabQuestScreen);
        btnCompleteQuest->setObjectName(QStringLiteral("btnCompleteQuest"));
        btnCompleteQuest->setGeometry(QRect(266, 200, 125, 41));
        lblQTitle = new QLabel(tabQuestScreen);
        lblQTitle->setObjectName(QStringLiteral("lblQTitle"));
        lblQTitle->setGeometry(QRect(10, 40, 381, 21));
        lblQTitle->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        lblQTitle->setAlignment(Qt::AlignCenter);
        lblQProgress = new QLabel(tabQuestScreen);
        lblQProgress->setObjectName(QStringLiteral("lblQProgress"));
        lblQProgress->setGeometry(QRect(10, 90, 381, 21));
        lblQProgress->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        lblQReward = new QLabel(tabQuestScreen);
        lblQReward->setObjectName(QStringLiteral("lblQReward"));
        lblQReward->setGeometry(QRect(10, 130, 381, 21));
        lblQReward->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        btnAbandonQuest = new QPushButton(tabQuestScreen);
        btnAbandonQuest->setObjectName(QStringLiteral("btnAbandonQuest"));
        btnAbandonQuest->setGeometry(QRect(140, 200, 121, 41));
        lblQuestTabBG = new QLabel(tabQuestScreen);
        lblQuestTabBG->setObjectName(QStringLiteral("lblQuestTabBG"));
        lblQuestTabBG->setGeometry(QRect(-150, -30, 650, 450));
        tabGame->addTab(tabQuestScreen, QString());
        lblQuestTabBG->raise();
        btnBeginQuest->raise();
        btnCompleteQuest->raise();
        lblQTitle->raise();
        lblQProgress->raise();
        lblQReward->raise();
        btnAbandonQuest->raise();
        pbarXP = new QProgressBar(centralWidget);
        pbarXP->setObjectName(QStringLiteral("pbarXP"));
        pbarXP->setGeometry(QRect(0, 280, 401, 23));
        pbarXP->setAutoFillBackground(false);
        pbarXP->setMaximum(100);
        pbarXP->setValue(0);
        pbarXP->setAlignment(Qt::AlignCenter);
        pbarXP->setTextVisible(true);
        pbarXP->setInvertedAppearance(false);
        GameLogic->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GameLogic);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 20));
        GameLogic->setMenuBar(menuBar);

        retranslateUi(GameLogic);

        tabGame->setCurrentIndex(0);
        btnBeginQuest->setDefault(false);


        QMetaObject::connectSlotsByName(GameLogic);
    } // setupUi

    void retranslateUi(QMainWindow *GameLogic)
    {
        GameLogic->setWindowTitle(QApplication::translate("GameLogic", "RNG Simulator The Game", nullptr));
        btnNewGame->setText(QApplication::translate("GameLogic", "New Game", nullptr));
        btnQuit->setText(QApplication::translate("GameLogic", "Quit", nullptr));
        btnSave->setText(QApplication::translate("GameLogic", "Save", nullptr));
        btnLoad->setText(QApplication::translate("GameLogic", "Load", nullptr));
        lblMenuTabBG->setText(QString());
        tabGame->setTabText(tabGame->indexOf(tabMenuScreen), QApplication::translate("GameLogic", "Menu", nullptr));
        btnBuyPotion->setText(QApplication::translate("GameLogic", "Buy Potion", nullptr));
        btnUsePotion->setText(QApplication::translate("GameLogic", "Use Potion", nullptr));
        lblGoldAmount->setText(QApplication::translate("GameLogic", "Gold: 0", nullptr));
        lblPotionAmount->setText(QApplication::translate("GameLogic", "Potions: 0", nullptr));
        lblActionTabBG->setText(QString());
        tabGame->setTabText(tabGame->indexOf(tabActionScreen), QApplication::translate("GameLogic", "Action", nullptr));
        btnAttack->setText(QApplication::translate("GameLogic", "Attack", nullptr));
        pbarCHealth->setFormat(QApplication::translate("GameLogic", "%v", nullptr));
        pbarEHealth->setFormat(QApplication::translate("GameLogic", "%v", nullptr));
        lblEnemyName->setText(QString());
        btnBattle->setText(QApplication::translate("GameLogic", "Start A Battle", nullptr));
        btnUsePotionBS->setText(QApplication::translate("GameLogic", "Use Potion", nullptr));
        lblPLevel->setText(QApplication::translate("GameLogic", "0", nullptr));
        lblELevel->setText(QApplication::translate("GameLogic", "0", nullptr));
        btnSpecialAbility->setText(QApplication::translate("GameLogic", "Special Ability", nullptr));
        lblBattleTabBG->setText(QString());
        tabGame->setTabText(tabGame->indexOf(tabBattleScreen), QApplication::translate("GameLogic", "Battles", nullptr));
        lblCName->setText(QApplication::translate("GameLogic", "Name:", nullptr));
        lblCHealth->setText(QApplication::translate("GameLogic", "Health:", nullptr));
        lblCAttack->setText(QApplication::translate("GameLogic", "Attack:", nullptr));
        lblCLevel->setText(QApplication::translate("GameLogic", "Level:", nullptr));
        lblCCritChance->setText(QApplication::translate("GameLogic", "Critical Hit Chance:", nullptr));
        lblCXP->setText(QApplication::translate("GameLogic", "Experience:", nullptr));
        lblCXPTillLvl->setText(QApplication::translate("GameLogic", "XP till next level:", nullptr));
        btnIncreaseHP->setText(QApplication::translate("GameLogic", "+", nullptr));
        btnIncreaseAttack->setText(QApplication::translate("GameLogic", "+", nullptr));
        btnIncreaseCritChance->setText(QApplication::translate("GameLogic", "+", nullptr));
        lblCSkillPoints->setText(QApplication::translate("GameLogic", "Skill Points: 0", nullptr));
        lblCharTabBG->setText(QString());
        tabGame->setTabText(tabGame->indexOf(tabCInfoScreen), QApplication::translate("GameLogic", "Character Info", nullptr));
        btnBeginQuest->setText(QApplication::translate("GameLogic", "Begin Quest", nullptr));
        btnCompleteQuest->setText(QApplication::translate("GameLogic", "Hand In Quest", nullptr));
        lblQTitle->setText(QApplication::translate("GameLogic", "No Active Quest", nullptr));
        lblQProgress->setText(QApplication::translate("GameLogic", "Progress:", nullptr));
        lblQReward->setText(QApplication::translate("GameLogic", "Reward:", nullptr));
        btnAbandonQuest->setText(QApplication::translate("GameLogic", "Abandon Quest", nullptr));
        lblQuestTabBG->setText(QString());
        tabGame->setTabText(tabGame->indexOf(tabQuestScreen), QApplication::translate("GameLogic", "Quests", nullptr));
        pbarXP->setFormat(QApplication::translate("GameLogic", "%v%", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameLogic: public Ui_GameLogic {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTROMENU_H
