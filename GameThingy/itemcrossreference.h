#ifndef ITEMCROSSREFERENCE_H
#define ITEMCROSSREFERENCE_H

#include <QString>



class itemCrossReference
{
private:
    //QString itemType_ [10] = {"", "", "",  "", "", "",  "",  "",  "",  ""};
    QString itemType_   [10] = {"Default", "Consumable", "Weapon",  "Armour", "Shield", "Quest",  "Ring",  "Trinket",  "random",  "Junk"};
    QString armourType_ [5]  = {"Default", "Cloth", "Leather", "Mail",  "Plate"};
    QString statType_   [10] = {"Default", "Vitality", "Strength",  "Stamina", "Agility", "Luck",  "Precision",  "Dodge",  "Block",  "Hit"};
    QString itemRarity_ [6]  = {"Default", "Common", "Uncommon",  "Rare", "Epic", "Legendary"};
    QString holdType_   [4]  = {"Default", "Main Hand", "1 Handed",  "2 Handed"};

public:
    itemCrossReference();
    ~itemCrossReference(void);

    QString getItemType(int crossReference);
    QString getArmourType(int crossReference);
    QString getStatType(int crossReference);
    QString getItemRarity(int crossReference);
    QString getHoldType(int crossReference);
};

#endif // ITEMCROSSREFERENCE_H
