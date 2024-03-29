#ifndef ITEMCROSSREFERENCE_H
#define ITEMCROSSREFERENCE_H

#include <QString>



class itemCrossReference
{
private:
    //QString itemType_     [10] = {"", "", "",  "", "", "",  "",  "",  "",  ""};
    QString itemType_       [10] = {"Undefined", "Consumable", "Weapon",  "Armour", "Shield", "Quest",  "Ring",  "Trinket",  "random",  "Junk"};
    QString armourType_     [5]  = {"Undefined", "Cloth", "Leather", "Mail",  "Plate"};
    QString statType_       [8]  = {"Undefined", "Vitality", "Strength",  "Stamina", "Agility", "Luck",  "Precision",  "Block"};
    QString itemRarity_     [6]  = {"Undefined", "Common", "Uncommon",  "Rare", "Epic", "Legendary"};
    QString holdType_       [4]  = {"Undefined", "Main Hand", "1 Handed",  "2 Handed"};
    QString weaponType_     [15] = {"Undefined", "Dagger", "Short Sword", "Long Sword", "Mace", "Club", "Staff", "Scepter",
                                    "Greatclub", "Warhammer", "Maul", "Morningstar", "Greatsword", "Battleaxe", "Greataxe"};
    QString weaponEdgeType_ [4]  = {"Undefined", "Sharp", "Blunt", "Spiked"};
    QString classType_      [5]  = {"Undefined", "Wizard", "Rogue", "Warrior", "Knight"};

public:
    itemCrossReference();
    ~itemCrossReference(void);

    QString getItemType(int crossReference);
    QString getArmourType(int crossReference);
    QString getStatType(int crossReference);
    QString getItemRarity(int crossReference);
    QString getHoldType(int crossReference);
    QString getWeaponType(int crossReference);
    QString getWeaponEdgeType(int crossReference);
    QString getClassType(int crossReference);
};

#endif // ITEMCROSSREFERENCE_H
