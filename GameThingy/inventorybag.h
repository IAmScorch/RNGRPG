#ifndef INVENTORYBAG_H
#define INVENTORYBAG_H

#include <QDialog>
#include <string>
#include <QString>
#include <QVector>
#include "item.h"

namespace Ui {
class InventoryBag;
}

class InventoryBag : public QDialog
{
    Q_OBJECT

public:
    explicit InventoryBag(QWidget *parent = nullptr);
    ~InventoryBag();

    void setInventory(QString items);
    void clearInventory();

public slots:
    void on_btnClose_clicked();

private:
    Ui::InventoryBag *ui;
    QVector<Item> inventory_;
    QVector<Item> equipment_;
};

#endif // INVENTORYBAG_H
