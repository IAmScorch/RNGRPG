#include "inventorybag.h"
#include "ui_inventorybag.h"

InventoryBag::InventoryBag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InventoryBag)
{
    ui->setupUi(this);
}

InventoryBag::~InventoryBag()
{
    delete ui;
}

void InventoryBag::setInventory(QString items)
{
    ui->lstInventory->addItem(items);
}

void InventoryBag::clearInventory()
{
    ui->lstInventory->clear();
}

void InventoryBag::on_btnClose_clicked()
{

}
