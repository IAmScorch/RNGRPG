/********************************************************************************
** Form generated from reading UI file 'inventorybag.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INVENTORYBAG_H
#define UI_INVENTORYBAG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_InventoryBag
{
public:
    QListWidget *lstEquipment;
    QListWidget *lstInventory;
    QLabel *lblInventory;
    QLabel *lblEquipment;
    QPushButton *btnClose;

    void setupUi(QDialog *InventoryBag)
    {
        if (InventoryBag->objectName().isEmpty())
            InventoryBag->setObjectName(QStringLiteral("InventoryBag"));
        InventoryBag->resize(400, 300);
        InventoryBag->setContextMenuPolicy(Qt::DefaultContextMenu);
        lstEquipment = new QListWidget(InventoryBag);
        lstEquipment->setObjectName(QStringLiteral("lstEquipment"));
        lstEquipment->setGeometry(QRect(10, 35, 185, 110));
        lstInventory = new QListWidget(InventoryBag);
        lstInventory->setObjectName(QStringLiteral("lstInventory"));
        lstInventory->setGeometry(QRect(205, 35, 185, 210));
        lblInventory = new QLabel(InventoryBag);
        lblInventory->setObjectName(QStringLiteral("lblInventory"));
        lblInventory->setGeometry(QRect(205, 10, 150, 21));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        lblInventory->setFont(font);
        lblInventory->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        lblEquipment = new QLabel(InventoryBag);
        lblEquipment->setObjectName(QStringLiteral("lblEquipment"));
        lblEquipment->setGeometry(QRect(10, 10, 150, 21));
        lblEquipment->setFont(font);
        lblEquipment->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        btnClose = new QPushButton(InventoryBag);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        btnClose->setGeometry(QRect(80, 210, 80, 21));

        retranslateUi(InventoryBag);

        QMetaObject::connectSlotsByName(InventoryBag);
    } // setupUi

    void retranslateUi(QDialog *InventoryBag)
    {
        InventoryBag->setWindowTitle(QApplication::translate("InventoryBag", "Inventory", nullptr));
        lblInventory->setText(QApplication::translate("InventoryBag", "Inventory", nullptr));
        lblEquipment->setText(QApplication::translate("InventoryBag", "Equipment", nullptr));
        btnClose->setText(QApplication::translate("InventoryBag", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InventoryBag: public Ui_InventoryBag {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INVENTORYBAG_H
