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
    QLabel *lblPotionCost;
    QLabel *lblRationCost;
    QPushButton *btnBuyRation;
    QPushButton *btnUseRation;
    QLabel *lblRationAmount;
    QWidget *tabBattleScreen;
    QTextEdit *txtBattleInfo;
    QPushButton *btnAttack;
    QLabel *lblEnemyName;
    QPushButton *btnBattle;
    QPushButton *btnUsePotionBS;
    QLabel *lblPLevel;
    QLabel *lblELevel;
    QPushButton *btnSpecialAbility;
    QLabel *lblBattleTabBG;
    QLabel *lblPHealth;
    QLabel *lblPHealthAmount;
    QLabel *lblPHealthBG;
    QLabel *lblEHealth;
    QLabel *lblEHealthAmount;
    QLabel *lblEHealthBG;
    QLabel *lblPStaminaAmount;
    QLabel *lblPStamina;
    QLabel *lblPStaminaBG;
    QPushButton *btnUseRationBS;
    QPushButton *btnTravel;
    QPushButton *btnRestBS;
    QWidget *tabCInfoScreen;
    QLabel *lblCName;
    QLabel *lblCHealth;
    QLabel *lblCAttack;
    QLabel *lblCLevel;
    QLabel *lblCXP;
    QLabel *lblCXPTillLvl;
    QPushButton *btnIncreaseHP;
    QPushButton *btnIncreaseAttack;
    QPushButton *btnIncreaseCritChance;
    QLabel *lblCSkillPoints;
    QLabel *lblCharTabBG;
    QLabel *lblCVitality;
    QLabel *lblCStrength;
    QLabel *lblCAgility;
    QLabel *lblCLuck;
    QPushButton *btnIncreaseAgility;
    QLabel *lblCHit;
    QPushButton *btnIncreaseHitChance;
    QLabel *lblCStamina;
    QPushButton *btnIncreaseStamina;
    QWidget *tabQuestScreen;
    QPushButton *btnBeginQuest;
    QPushButton *btnCompleteQuest;
    QLabel *lblQTitle;
    QLabel *lblQProgress;
    QLabel *lblQReward;
    QPushButton *btnAbandonQuest;
    QLabel *lblQuestTabBG;
    QLabel *lblXpBar;
    QLabel *lblXpPercent;
    QLabel *lblXpBarBG;
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
        btnUsePotion->setGeometry(QRect(10, 160, 91, 41));
        btnUsePotion->setFont(font1);
        lblGoldAmount = new QLabel(tabActionScreen);
        lblGoldAmount->setObjectName(QStringLiteral("lblGoldAmount"));
        lblGoldAmount->setGeometry(QRect(10, 10, 151, 41));
        lblGoldAmount->setFont(font1);
        lblGoldAmount->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        lblPotionAmount = new QLabel(tabActionScreen);
        lblPotionAmount->setObjectName(QStringLiteral("lblPotionAmount"));
        lblPotionAmount->setGeometry(QRect(110, 160, 151, 41));
        lblPotionAmount->setFont(font1);
        lblPotionAmount->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        lblActionTabBG = new QLabel(tabActionScreen);
        lblActionTabBG->setObjectName(QStringLiteral("lblActionTabBG"));
        lblActionTabBG->setGeometry(QRect(-60, -60, 1001, 665));
        lblPotionCost = new QLabel(tabActionScreen);
        lblPotionCost->setObjectName(QStringLiteral("lblPotionCost"));
        lblPotionCost->setGeometry(QRect(110, 60, 151, 41));
        lblPotionCost->setFont(font1);
        lblPotionCost->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        lblRationCost = new QLabel(tabActionScreen);
        lblRationCost->setObjectName(QStringLiteral("lblRationCost"));
        lblRationCost->setGeometry(QRect(110, 110, 151, 41));
        lblRationCost->setFont(font1);
        lblRationCost->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        btnBuyRation = new QPushButton(tabActionScreen);
        btnBuyRation->setObjectName(QStringLiteral("btnBuyRation"));
        btnBuyRation->setGeometry(QRect(10, 110, 91, 41));
        btnBuyRation->setFont(font1);
        btnUseRation = new QPushButton(tabActionScreen);
        btnUseRation->setObjectName(QStringLiteral("btnUseRation"));
        btnUseRation->setGeometry(QRect(10, 210, 91, 41));
        btnUseRation->setFont(font1);
        lblRationAmount = new QLabel(tabActionScreen);
        lblRationAmount->setObjectName(QStringLiteral("lblRationAmount"));
        lblRationAmount->setGeometry(QRect(110, 210, 151, 41));
        lblRationAmount->setFont(font1);
        lblRationAmount->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        tabGame->addTab(tabActionScreen, QString());
        lblActionTabBG->raise();
        btnBuyPotion->raise();
        btnUsePotion->raise();
        lblGoldAmount->raise();
        lblPotionAmount->raise();
        lblPotionCost->raise();
        lblRationCost->raise();
        btnBuyRation->raise();
        btnUseRation->raise();
        lblRationAmount->raise();
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
        btnBattle->setGeometry(QRect(150, 160, 91, 21));
        btnBattle->setFont(font1);
        btnUsePotionBS = new QPushButton(tabBattleScreen);
        btnUsePotionBS->setObjectName(QStringLiteral("btnUsePotionBS"));
        btnUsePotionBS->setGeometry(QRect(150, 213, 91, 21));
        btnUsePotionBS->setFont(font1);
        lblPLevel = new QLabel(tabBattleScreen);
        lblPLevel->setObjectName(QStringLiteral("lblPLevel"));
        lblPLevel->setGeometry(QRect(10, 215, 125, 21));
        QFont font4;
        font4.setPointSize(12);
        font4.setBold(true);
        font4.setWeight(75);
        lblPLevel->setFont(font4);
        lblPLevel->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        lblPLevel->setAlignment(Qt::AlignCenter);
        lblELevel = new QLabel(tabBattleScreen);
        lblELevel->setObjectName(QStringLiteral("lblELevel"));
        lblELevel->setGeometry(QRect(260, 215, 125, 23));
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
        lblPHealth = new QLabel(tabBattleScreen);
        lblPHealth->setObjectName(QStringLiteral("lblPHealth"));
        lblPHealth->setGeometry(QRect(10, 190, 125, 23));
        lblPHealth->setStyleSheet(QStringLiteral("background-color: rgb(0, 255, 0);"));
        lblPHealthAmount = new QLabel(tabBattleScreen);
        lblPHealthAmount->setObjectName(QStringLiteral("lblPHealthAmount"));
        lblPHealthAmount->setGeometry(QRect(10, 190, 125, 23));
        lblPHealthAmount->setStyleSheet(QStringLiteral("color: rgb(0, 0, 0);"));
        lblPHealthAmount->setAlignment(Qt::AlignCenter);
        lblPHealthBG = new QLabel(tabBattleScreen);
        lblPHealthBG->setObjectName(QStringLiteral("lblPHealthBG"));
        lblPHealthBG->setGeometry(QRect(10, 190, 125, 23));
        lblPHealthBG->setStyleSheet(QStringLiteral("background-color: rgb(179, 179, 179);"));
        lblEHealth = new QLabel(tabBattleScreen);
        lblEHealth->setObjectName(QStringLiteral("lblEHealth"));
        lblEHealth->setGeometry(QRect(260, 190, 125, 23));
        lblEHealth->setStyleSheet(QStringLiteral("background-color: rgb(0, 255, 0);"));
        lblEHealthAmount = new QLabel(tabBattleScreen);
        lblEHealthAmount->setObjectName(QStringLiteral("lblEHealthAmount"));
        lblEHealthAmount->setGeometry(QRect(260, 190, 125, 23));
        lblEHealthAmount->setStyleSheet(QStringLiteral("color: rgb(0, 0, 0);"));
        lblEHealthAmount->setAlignment(Qt::AlignCenter);
        lblEHealthBG = new QLabel(tabBattleScreen);
        lblEHealthBG->setObjectName(QStringLiteral("lblEHealthBG"));
        lblEHealthBG->setGeometry(QRect(260, 190, 125, 23));
        lblEHealthBG->setStyleSheet(QStringLiteral("background-color: rgb(179, 179, 179);"));
        lblPStaminaAmount = new QLabel(tabBattleScreen);
        lblPStaminaAmount->setObjectName(QStringLiteral("lblPStaminaAmount"));
        lblPStaminaAmount->setGeometry(QRect(10, 240, 125, 11));
        lblPStaminaAmount->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        lblPStaminaAmount->setAlignment(Qt::AlignCenter);
        lblPStamina = new QLabel(tabBattleScreen);
        lblPStamina->setObjectName(QStringLiteral("lblPStamina"));
        lblPStamina->setGeometry(QRect(10, 240, 125, 11));
        lblPStamina->setStyleSheet(QStringLiteral("background-color: rgb(0, 34, 224);"));
        lblPStamina->setAlignment(Qt::AlignCenter);
        lblPStaminaBG = new QLabel(tabBattleScreen);
        lblPStaminaBG->setObjectName(QStringLiteral("lblPStaminaBG"));
        lblPStaminaBG->setGeometry(QRect(10, 240, 125, 11));
        lblPStaminaBG->setStyleSheet(QStringLiteral("background-color: rgb(179, 179, 179);"));
        lblPStaminaBG->setAlignment(Qt::AlignCenter);
        btnUseRationBS = new QPushButton(tabBattleScreen);
        btnUseRationBS->setObjectName(QStringLiteral("btnUseRationBS"));
        btnUseRationBS->setGeometry(QRect(150, 233, 91, 21));
        btnUseRationBS->setFont(font1);
        btnTravel = new QPushButton(tabBattleScreen);
        btnTravel->setObjectName(QStringLiteral("btnTravel"));
        btnTravel->setGeometry(QRect(150, 140, 91, 21));
        btnTravel->setFont(font1);
        btnRestBS = new QPushButton(tabBattleScreen);
        btnRestBS->setObjectName(QStringLiteral("btnRestBS"));
        btnRestBS->setGeometry(QRect(150, 193, 91, 21));
        btnRestBS->setFont(font1);
        tabGame->addTab(tabBattleScreen, QString());
        lblBattleTabBG->raise();
        lblPStaminaBG->raise();
        lblEHealthBG->raise();
        lblPHealthBG->raise();
        btnSpecialAbility->raise();
        txtBattleInfo->raise();
        lblEnemyName->raise();
        btnBattle->raise();
        btnUsePotionBS->raise();
        lblPLevel->raise();
        lblELevel->raise();
        btnAttack->raise();
        lblPHealth->raise();
        lblPHealthAmount->raise();
        lblEHealth->raise();
        lblEHealthAmount->raise();
        lblPStamina->raise();
        btnUseRationBS->raise();
        btnTravel->raise();
        lblPStaminaAmount->raise();
        btnRestBS->raise();
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
        lblCXP = new QLabel(tabCInfoScreen);
        lblCXP->setObjectName(QStringLiteral("lblCXP"));
        lblCXP->setGeometry(QRect(10, 200, 251, 21));
        lblCXP->setFont(font1);
        lblCXP->setAutoFillBackground(false);
        lblCXP->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        lblCXPTillLvl = new QLabel(tabCInfoScreen);
        lblCXPTillLvl->setObjectName(QStringLiteral("lblCXPTillLvl"));
        lblCXPTillLvl->setGeometry(QRect(10, 230, 251, 21));
        lblCXPTillLvl->setFont(font1);
        lblCXPTillLvl->setAutoFillBackground(false);
        lblCXPTillLvl->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        btnIncreaseHP = new QPushButton(tabCInfoScreen);
        btnIncreaseHP->setObjectName(QStringLiteral("btnIncreaseHP"));
        btnIncreaseHP->setEnabled(false);
        btnIncreaseHP->setGeometry(QRect(370, 40, 23, 23));
        btnIncreaseHP->setFont(font1);
        btnIncreaseAttack = new QPushButton(tabCInfoScreen);
        btnIncreaseAttack->setObjectName(QStringLiteral("btnIncreaseAttack"));
        btnIncreaseAttack->setEnabled(false);
        btnIncreaseAttack->setGeometry(QRect(370, 70, 23, 23));
        btnIncreaseAttack->setFont(font1);
        btnIncreaseCritChance = new QPushButton(tabCInfoScreen);
        btnIncreaseCritChance->setObjectName(QStringLiteral("btnIncreaseCritChance"));
        btnIncreaseCritChance->setEnabled(false);
        btnIncreaseCritChance->setGeometry(QRect(370, 180, 23, 23));
        btnIncreaseCritChance->setFont(font1);
        lblCSkillPoints = new QLabel(tabCInfoScreen);
        lblCSkillPoints->setObjectName(QStringLiteral("lblCSkillPoints"));
        lblCSkillPoints->setGeometry(QRect(270, 10, 100, 21));
        lblCSkillPoints->setFont(font1);
        lblCSkillPoints->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        lblCharTabBG = new QLabel(tabCInfoScreen);
        lblCharTabBG->setObjectName(QStringLiteral("lblCharTabBG"));
        lblCharTabBG->setGeometry(QRect(-370, -10, 1001, 665));
        lblCharTabBG->setPixmap(QPixmap(QString::fromUtf8("../Img/tabCharacterBG.png")));
        lblCVitality = new QLabel(tabCInfoScreen);
        lblCVitality->setObjectName(QStringLiteral("lblCVitality"));
        lblCVitality->setGeometry(QRect(270, 40, 100, 21));
        lblCVitality->setFont(font1);
        lblCVitality->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        lblCStrength = new QLabel(tabCInfoScreen);
        lblCStrength->setObjectName(QStringLiteral("lblCStrength"));
        lblCStrength->setGeometry(QRect(270, 70, 100, 21));
        lblCStrength->setFont(font1);
        lblCStrength->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        lblCAgility = new QLabel(tabCInfoScreen);
        lblCAgility->setObjectName(QStringLiteral("lblCAgility"));
        lblCAgility->setGeometry(QRect(270, 150, 100, 21));
        lblCAgility->setFont(font1);
        lblCAgility->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        lblCLuck = new QLabel(tabCInfoScreen);
        lblCLuck->setObjectName(QStringLiteral("lblCLuck"));
        lblCLuck->setGeometry(QRect(270, 180, 100, 21));
        lblCLuck->setFont(font1);
        lblCLuck->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        btnIncreaseAgility = new QPushButton(tabCInfoScreen);
        btnIncreaseAgility->setObjectName(QStringLiteral("btnIncreaseAgility"));
        btnIncreaseAgility->setEnabled(false);
        btnIncreaseAgility->setGeometry(QRect(370, 150, 23, 23));
        btnIncreaseAgility->setFont(font1);
        lblCHit = new QLabel(tabCInfoScreen);
        lblCHit->setObjectName(QStringLiteral("lblCHit"));
        lblCHit->setGeometry(QRect(270, 210, 100, 21));
        lblCHit->setFont(font1);
        lblCHit->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        btnIncreaseHitChance = new QPushButton(tabCInfoScreen);
        btnIncreaseHitChance->setObjectName(QStringLiteral("btnIncreaseHitChance"));
        btnIncreaseHitChance->setEnabled(false);
        btnIncreaseHitChance->setGeometry(QRect(370, 210, 23, 23));
        btnIncreaseHitChance->setFont(font1);
        lblCStamina = new QLabel(tabCInfoScreen);
        lblCStamina->setObjectName(QStringLiteral("lblCStamina"));
        lblCStamina->setGeometry(QRect(270, 100, 100, 21));
        lblCStamina->setFont(font1);
        lblCStamina->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        btnIncreaseStamina = new QPushButton(tabCInfoScreen);
        btnIncreaseStamina->setObjectName(QStringLiteral("btnIncreaseStamina"));
        btnIncreaseStamina->setEnabled(false);
        btnIncreaseStamina->setGeometry(QRect(370, 100, 23, 23));
        btnIncreaseStamina->setFont(font1);
        tabGame->addTab(tabCInfoScreen, QString());
        lblCharTabBG->raise();
        lblCName->raise();
        lblCHealth->raise();
        lblCAttack->raise();
        lblCLevel->raise();
        lblCXP->raise();
        lblCXPTillLvl->raise();
        btnIncreaseHP->raise();
        btnIncreaseAttack->raise();
        btnIncreaseCritChance->raise();
        lblCSkillPoints->raise();
        lblCVitality->raise();
        lblCStrength->raise();
        lblCAgility->raise();
        lblCLuck->raise();
        btnIncreaseAgility->raise();
        lblCHit->raise();
        btnIncreaseHitChance->raise();
        lblCStamina->raise();
        btnIncreaseStamina->raise();
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
        lblQProgress->setGeometry(QRect(10, 90, 381, 41));
        lblQProgress->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"vertical-align: top;\n"
"text-align: left;"));
        lblQReward = new QLabel(tabQuestScreen);
        lblQReward->setObjectName(QStringLiteral("lblQReward"));
        lblQReward->setGeometry(QRect(10, 130, 381, 61));
        lblQReward->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"vertical-align: top;\n"
"text-align: left;"));
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
        lblXpBar = new QLabel(centralWidget);
        lblXpBar->setObjectName(QStringLiteral("lblXpBar"));
        lblXpBar->setGeometry(QRect(0, 280, 0, 23));
        lblXpBar->setStyleSheet(QStringLiteral("background-color: rgb(85, 0, 127);"));
        lblXpPercent = new QLabel(centralWidget);
        lblXpPercent->setObjectName(QStringLiteral("lblXpPercent"));
        lblXpPercent->setGeometry(QRect(0, 280, 400, 23));
        lblXpPercent->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        lblXpPercent->setAlignment(Qt::AlignCenter);
        lblXpBarBG = new QLabel(centralWidget);
        lblXpBarBG->setObjectName(QStringLiteral("lblXpBarBG"));
        lblXpBarBG->setGeometry(QRect(0, 280, 400, 23));
        lblXpBarBG->setStyleSheet(QStringLiteral("background-color: rgb(179, 179, 179);"));
        GameLogic->setCentralWidget(centralWidget);
        lblXpBarBG->raise();
        tabGame->raise();
        lblXpBar->raise();
        lblXpPercent->raise();
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
        btnUsePotion->setText(QApplication::translate("GameLogic", "Drink Potion", nullptr));
        lblGoldAmount->setText(QApplication::translate("GameLogic", "Gold: 0", nullptr));
        lblPotionAmount->setText(QApplication::translate("GameLogic", "Potions: 0", nullptr));
        lblActionTabBG->setText(QString());
        lblPotionCost->setText(QApplication::translate("GameLogic", "Cost: 20 Gold", nullptr));
        lblRationCost->setText(QApplication::translate("GameLogic", "Cost: 30 Gold", nullptr));
        btnBuyRation->setText(QApplication::translate("GameLogic", "Buy Ration", nullptr));
        btnUseRation->setText(QApplication::translate("GameLogic", "Eat Ration", nullptr));
        lblRationAmount->setText(QApplication::translate("GameLogic", "Rations: 0", nullptr));
        tabGame->setTabText(tabGame->indexOf(tabActionScreen), QApplication::translate("GameLogic", "Action", nullptr));
        btnAttack->setText(QApplication::translate("GameLogic", "Attack", nullptr));
        lblEnemyName->setText(QString());
        btnBattle->setText(QApplication::translate("GameLogic", "Start A Battle", nullptr));
        btnUsePotionBS->setText(QApplication::translate("GameLogic", "Drink Potion", nullptr));
        lblPLevel->setText(QApplication::translate("GameLogic", "0", nullptr));
        lblELevel->setText(QApplication::translate("GameLogic", "0", nullptr));
        btnSpecialAbility->setText(QApplication::translate("GameLogic", "Special Ability", nullptr));
        lblBattleTabBG->setText(QString());
        lblPHealth->setText(QString());
        lblPHealthAmount->setText(QApplication::translate("GameLogic", "100", nullptr));
        lblPHealthBG->setText(QString());
        lblEHealth->setText(QString());
        lblEHealthAmount->setText(QApplication::translate("GameLogic", "100", nullptr));
        lblEHealthBG->setText(QString());
        lblPStaminaAmount->setText(QApplication::translate("GameLogic", "10", nullptr));
        lblPStamina->setText(QString());
        lblPStaminaBG->setText(QString());
        btnUseRationBS->setText(QApplication::translate("GameLogic", "Eat Ration", nullptr));
        btnTravel->setText(QApplication::translate("GameLogic", "Travel", nullptr));
        btnRestBS->setText(QApplication::translate("GameLogic", "Rest", nullptr));
        tabGame->setTabText(tabGame->indexOf(tabBattleScreen), QApplication::translate("GameLogic", "Battles", nullptr));
        lblCName->setText(QApplication::translate("GameLogic", "Name:", nullptr));
        lblCHealth->setText(QApplication::translate("GameLogic", "Health:", nullptr));
        lblCAttack->setText(QApplication::translate("GameLogic", "Attack:", nullptr));
        lblCLevel->setText(QApplication::translate("GameLogic", "Level:", nullptr));
        lblCXP->setText(QApplication::translate("GameLogic", "Experience:", nullptr));
        lblCXPTillLvl->setText(QApplication::translate("GameLogic", "XP till next level:", nullptr));
        btnIncreaseHP->setText(QApplication::translate("GameLogic", "+", nullptr));
        btnIncreaseAttack->setText(QApplication::translate("GameLogic", "+", nullptr));
        btnIncreaseCritChance->setText(QApplication::translate("GameLogic", "+", nullptr));
        lblCSkillPoints->setText(QApplication::translate("GameLogic", "Skill Points: 0", nullptr));
        lblCharTabBG->setText(QString());
#ifndef QT_NO_TOOLTIP
        lblCVitality->setToolTip(QApplication::translate("GameLogic", "<html><head/><body><p><span style=\" color:#000000;\">Determines the amount of damage you can take from enemies</span></p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        lblCVitality->setText(QApplication::translate("GameLogic", "Vitality:", nullptr));
#ifndef QT_NO_TOOLTIP
        lblCStrength->setToolTip(QApplication::translate("GameLogic", "<html><head/><body><p><span style=\" color:#000000;\">Determines how much damage you can do to enemies</span></p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        lblCStrength->setText(QApplication::translate("GameLogic", "Strength:", nullptr));
#ifndef QT_NO_TOOLTIP
        lblCAgility->setToolTip(QApplication::translate("GameLogic", "<html><head/><body><p><span style=\" color:#000000;\">Determines the chance at which you can dodge an enemy's attack.</span></p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        lblCAgility->setText(QApplication::translate("GameLogic", "Agility:", nullptr));
#ifndef QT_NO_TOOLTIP
        lblCLuck->setToolTip(QApplication::translate("GameLogic", "<html><head/><body><p><span style=\" color:#000000;\">Determines the chance your attack can cause critical damage to an enemy.</span></p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        lblCLuck->setText(QApplication::translate("GameLogic", "Luck:", nullptr));
        btnIncreaseAgility->setText(QApplication::translate("GameLogic", "+", nullptr));
#ifndef QT_NO_TOOLTIP
        lblCHit->setToolTip(QApplication::translate("GameLogic", "<html><head/><body><p><span style=\" color:#000000;\">Determines the chance at which you can successfully strike an enemy.</span></p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        lblCHit->setText(QApplication::translate("GameLogic", "Precision:", nullptr));
        btnIncreaseHitChance->setText(QApplication::translate("GameLogic", "+", nullptr));
#ifndef QT_NO_TOOLTIP
        lblCStamina->setToolTip(QApplication::translate("GameLogic", "<html><head/><body><p><span style=\" color:#000000;\">Determines how many actions you can take per day. Fights cost 1 Stamina. Traveling costs 2 Stamina</span></p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        lblCStamina->setText(QApplication::translate("GameLogic", "Stamina:", nullptr));
        btnIncreaseStamina->setText(QApplication::translate("GameLogic", "+", nullptr));
        tabGame->setTabText(tabGame->indexOf(tabCInfoScreen), QApplication::translate("GameLogic", "Character Info", nullptr));
        btnBeginQuest->setText(QApplication::translate("GameLogic", "Begin Quest", nullptr));
        btnCompleteQuest->setText(QApplication::translate("GameLogic", "Hand In Quest", nullptr));
        lblQTitle->setText(QApplication::translate("GameLogic", "No Active Quest", nullptr));
        lblQProgress->setText(QApplication::translate("GameLogic", "Progress:", nullptr));
        lblQReward->setText(QApplication::translate("GameLogic", "Reward:", nullptr));
        btnAbandonQuest->setText(QApplication::translate("GameLogic", "Abandon Quest", nullptr));
        lblQuestTabBG->setText(QString());
        tabGame->setTabText(tabGame->indexOf(tabQuestScreen), QApplication::translate("GameLogic", "Quests", nullptr));
        lblXpBar->setText(QString());
        lblXpPercent->setText(QApplication::translate("GameLogic", "0%", nullptr));
        lblXpBarBG->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class GameLogic: public Ui_GameLogic {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTROMENU_H