#include "enemylootdrops.h"
#include "item.h"
#include <qmessagebox.h>

enemyLootDrops::enemyLootDrops()
{

}

QVector<Item> enemyLootDrops::doLootDrop(QString enemyName, QVector<Item> enemyLoot,
                                         int itemDropChance, int itemDropChanceModifier)
{
    int dropChance;
    QString itemChance;
    int itemsToDropped;
    QString lootMessage;
    QMessageBox msgBox;
    QVector<Item> droppedItems_;
    QVector<Item> tempItems;
    Item item;

    dropChance = rand()% 100 + 1;
    dropChance+= itemDropChanceModifier;
    lootMessage = enemyName + " dropped no loot";
    itemChance = "";

    if (dropChance >= itemDropChance)
    {
        lootMessage = enemyName + " dropped:\n";
        itemsToDropped = rand()% 3 + 1;

        for (int i = 0; i < itemsToDropped; i++)
        {
            CalculateTotalDropWeight(enemyLoot);
            int roll = rand() % totalDropWeight_;

            for (int x = 0; x < enemyLoot.length(); x++)
            {
                roll -= enemyLoot.value(x).dropWeight;

                if (roll < 0)
                {
                    item = enemyLoot.value(x);

                    if (item.itemRarity > 1)
                    {
                        int itemStatTypes[7] = {1,2,3,4,5,6};
                        int itemStatType1 = 0;
                        int itemStatType2 = 0;
                        int itemStatType3 = 0;
                        int numStats = 0;

                        if (item.itemType == 4)
                        {
                            itemStatType1 = rand()% 7 + 1;
                            itemStatType2 = rand()% 7 + 1;
                            itemStatType3 = rand()% 7 + 1;
                        }
                        else
                        {
                            itemStatType1 = itemStatTypes[rand()% 6];
                            itemStatType2 = itemStatTypes[rand()% 6];
                            itemStatType3 = itemStatTypes[rand()% 6];
                        }

                        if (item.itemType != 8)
                        {
                            switch (item.itemRarity)
                            {
                                case 2: //uncommon
                                    item.statType1 = itemStatType1;
                                    item.stat1 = 1;
                                    item.numStats = 1;
                                    numStats = 1;
                                    break;
                                case 3: //rare
                                    item.statType1 = itemStatType1;
                                    item.statType2 = itemStatType2;
                                    item.stat1 = 1;
                                    item.stat2 = 1;
                                    item.numStats = 2;
                                    numStats = 2;
                                    break;
                                case 4: //epic
                                    item.statType1 = itemStatType1;
                                    item.statType2 = itemStatType2;
                                    item.statType3 = itemStatType3;
                                    item.stat1 = 1;
                                    item.stat2 = 1;
                                    item.stat3 = 1;
                                    item.numStats = 3;
                                    numStats = 3;
                                    break;
                                case 5: //legendary
                                    item.statType1 = itemStatType1;
                                    item.statType2 = itemStatType2;
                                    item.statType3 = itemStatType3;
                                    item.stat1 = rand()% 2 + 1;
                                    item.stat2 = rand()% 2 + 1;
                                    item.stat3 = rand()% 2 + 1;
                                    item.numStats = 3;
                                    numStats = 3;
                                    break;
                            }
                        }
                        else if (item.itemType == 8)
                        {
                            int itemTypes[5] = {2,3,4,6,7};
                            int itemType = rand()% 5;
                            QString statName1 = "";
                            QString statName2 = "";
                            QString statName3 = "";
                            item.itemType = itemTypes[itemType];

                            if (item.itemType == 4)
                            {
                                itemStatType1 = rand()% 7 + 1;
                                itemStatType2 = rand()% 7 + 1;
                                itemStatType3 = rand()% 7 + 1;
                            }
                            else
                            {
                                itemStatType1 = itemStatTypes[rand()% 6];
                                itemStatType2 = itemStatTypes[rand()% 6];
                                itemStatType3 = itemStatTypes[rand()% 6];
                            }

                            switch (item.itemRarity)
                            {
                                case 2: //uncommon
                                    item.statType1 = itemStatType1;
                                    item.stat1 = 1;
                                    item.numStats = 1;
                                    statName1 = itemStatNames[itemStatType1 - 1];
                                    numStats = 1;
                                    break;
                                case 3: //rare
                                    item.statType1 = itemStatType1;
                                    item.statType2 = itemStatType2;
                                    item.stat1 = 1;
                                    item.stat2 = 1;
                                    item.numStats = 2;
                                    statName1 = itemStatNames[itemStatType1 - 1];
                                    statName2 = itemStatNames[itemStatType2 - 1];
                                    numStats = 2;
                                    break;
                                case 4: //epic
                                    item.statType1 = itemStatType1;
                                    item.statType2 = itemStatType2;
                                    item.statType3 = itemStatType3;
                                    item.stat1 = 1;
                                    item.stat2 = 1;
                                    item.stat3 = 1;
                                    item.numStats = 3;
                                    statName1 = itemStatNames[itemStatType1 - 1];
                                    statName2 = itemStatNames[itemStatType2 - 1];
                                    statName3 = itemStatNames[itemStatType3 - 1];
                                    numStats = 3;
                                    break;
                                case 5: //legendary
                                    item.statType1 = itemStatType1;
                                    item.statType2 = itemStatType2;
                                    item.statType3 = itemStatType3;
                                    item.stat1 = rand()% 2 + 1;
                                    item.stat2 = rand()% 2 + 1;
                                    item.stat3 = rand()% 2 + 1;
                                    item.numStats = 3;
                                    statName1 = itemStatNames[itemStatType1 - 1];
                                    statName2 = itemStatNames[itemStatType2 - 1];
                                    statName3 = itemStatNames[itemStatType3 - 1];
                                    numStats = 3;
                                    break;
                            }

                            switch (item.itemType)
                            {
                                case 2: //weapons
                                    item.name = weaponPrefixes[rand()%20];
                                    item.name +=  " " + weaponTypes[rand()% 14];
                                    if (item.name.contains("Dagger"))
                                    {
                                        item.sellPrice = (20 * item.itemRarity);
                                        item.minAtk = (1 + item.itemRarity) - 1;
                                        item.maxAtk = (4 + item.itemRarity) - 1;
                                        item.holdType = 2;
                                        item.weaponType = 1;
                                        item.weaponEdgeType = 1;
                                        item.dotType_ = 1;
                                    }
                                    else if (item.name.contains("Short Sword"))
                                    {
                                        item.sellPrice = (25 * item.itemRarity);
                                        item.minAtk = (1 + item.itemRarity) - 1;
                                        item.maxAtk = (6 + item.itemRarity) - 1;
                                        item.holdType = rand()%2 + 1;
                                        item.weaponType = 2;
                                        item.weaponEdgeType = 1;
                                        item.dotType_ = 1;
                                    }
                                    else if (item.name.contains("Long Sword"))
                                    {
                                        item.sellPrice = (30 * item.itemRarity);
                                        item.minAtk = (1 + item.itemRarity) - 1;
                                        item.maxAtk = (10 + item.itemRarity) - 1;
                                        item.holdType = 3;
                                        item.weaponType = 3;
                                        item.weaponEdgeType = 1;
                                        item.dotType_ = 1;
                                    }
                                    else if (item.name.contains("Club"))
                                    {
                                        item.sellPrice = (20 * item.itemRarity);
                                        item.minAtk = (1 + item.itemRarity) - 1;
                                        item.maxAtk = (4 + item.itemRarity) - 1;
                                        item.holdType = 2;
                                        item.weaponType = 5;
                                        item.weaponEdgeType = 2;
                                        item.dotType_ = 2;
                                    }
                                    else if (item.name.contains("Greatclub"))
                                    {
                                        item.sellPrice = (25 * item.itemRarity);
                                        item.minAtk = (1 + item.itemRarity) - 1;
                                        item.maxAtk = (8 + item.itemRarity) - 1;
                                        item.holdType = 3;
                                        item.weaponType = 8;
                                        item.weaponEdgeType = 2;
                                        item.dotType_ = 2;
                                    }
                                    else if (item.name.contains("Mace"))
                                    {
                                        item.sellPrice = (25 * item.itemRarity);
                                        item.minAtk = (1 + item.itemRarity) - 1;
                                        item.maxAtk = (6 + item.itemRarity) - 1;
                                        item.holdType = rand()%2 + 1;
                                        item.weaponType = 4;
                                        item.weaponEdgeType = 2;
                                        item.dotType_ = 2;
                                    }
                                    else if (item.name.contains("Warhammer"))
                                    {
                                        item.sellPrice = (30 * item.itemRarity);
                                        item.minAtk = (1 + item.itemRarity) - 1;
                                        item.maxAtk = (10 + item.itemRarity) - 1;
                                        item.holdType = 3;
                                        item.weaponType = 3;
                                        item.weaponEdgeType = 2;
                                        item.dotType_ = 2;
                                    }
                                    else if (item.name.contains("Maul"))
                                    {
                                        item.sellPrice = (35 * item.itemRarity);
                                        item.minAtk = (2 + item.itemRarity) - 1;
                                        item.maxAtk = (12 + item.itemRarity) - 1;
                                        item.holdType = 3;
                                        item.weaponType = 12;
                                        item.weaponEdgeType = 1;
                                        item.dotType_ = 1;
                                    }
                                    else if (item.name.contains("Greatsword"))
                                    {
                                        item.sellPrice = (35 * item.itemRarity);
                                        item.minAtk = (2 + item.itemRarity) - 1;
                                        item.maxAtk = (12 + item.itemRarity) - 1;
                                        item.holdType = 3;
                                        item.weaponType = 10;
                                        item.weaponEdgeType = 2;
                                        item.dotType_ = 2;
                                    }
                                    else if (item.name.contains("Morningstar"))
                                    {
                                        item.sellPrice = (25 * item.itemRarity);
                                        item.minAtk = (1 + item.itemRarity) - 1;
                                        item.maxAtk = (8 + item.itemRarity) - 1;
                                        item.holdType = 2;
                                        item.weaponType = 11;
                                        item.weaponEdgeType = 1;
                                        item.dotType_ = 1;
                                    }
                                    else if (item.name.contains("Battleaxe"))
                                    {
                                        item.sellPrice = (30 * item.itemRarity);
                                        item.minAtk = (1 + item.itemRarity) - 1;
                                        item.maxAtk = (10 + item.itemRarity) - 1;
                                        item.holdType = 3;
                                        item.weaponType = 13;
                                        item.weaponEdgeType = 1;
                                        item.dotType_ = 1;
                                    }
                                    else if (item.name.contains("Greataxe"))
                                    {
                                        item.sellPrice = (35 * item.itemRarity);
                                        item.minAtk = (1 + item.itemRarity) - 1;
                                        item.maxAtk = (12 + item.itemRarity) - 1;
                                        item.holdType = 3;
                                        item.weaponType = 14;
                                        item.weaponEdgeType = 1;
                                        item.dotType_ = 1;
                                    }
                                    break;
                                case 3: //armour
                                    item.name = armourPrefixes[rand()%7];
                                    item.name +=  " " + armourTypes[rand()% 4];
                                    if (item.name.contains("Cloth"))
                                    {
                                        item.sellPrice = (15 * item.itemRarity);
                                        item.armourType = 1;
                                        item.armourRating = (5 + item.itemRarity) - 1;
                                    }
                                    else if (item.name.contains("Leather"))
                                    {
                                        item.sellPrice = (20 * item.itemRarity);
                                        item.armourType = 2;
                                        item.armourRating = (4 + item.itemRarity) - 1;
                                    }
                                    else if (item.name.contains("Mail"))
                                    {
                                        item.sellPrice = (25 * item.itemRarity);
                                        item.armourType = 3;
                                        item.armourRating = (3 + item.itemRarity) - 1;
                                    }
                                    else if (item.name.contains("Plate"))
                                    {
                                        item.sellPrice = (30 * item.itemRarity);
                                        item.armourType = 4;
                                        item.armourRating = (2 + item.itemRarity) - 1;
                                    }
                                    break;
                                case 4: //Shield
                                    item.name = ShieldPrefixes[rand()%7] + " Shield";
                                    item.sellPrice = (30 * item.itemRarity) - 5;
                                    item.block = (7 + item.itemRarity) - 1;
                                    break;
                                case 6: //ring
                                    item.name = ringPrefixes[rand()%2] + " Ring";
                                    item.sellPrice = (15 + item.itemRarity);
                                    break;
                                case 7: //trinket
                                    item.name = trinketPrefixes[rand()%3] + " Trinket";
                                    item.sellPrice = (15 + item.itemRarity);
                                    break;
                            }

                            switch(numStats)
                            {
                                case 1:
                                    item.name += " of " + statName1;
                                    break;
                                case 2:
                                    if (itemStatType1 == itemStatType2)
                                    {
                                        item.name += " of Major " + statName1;
                                    }
                                    else
                                    {
                                        item.name += " of " + statName1 + " and " + statName2;
                                    }
                                    break;
                                case 3:
                                    if (itemStatType1 == itemStatType2)
                                    {
                                        item.name += " of Major " + statName1 + " and " + statName3;
                                    }
                                    else if (itemStatType1 == itemStatType3)
                                    {
                                        item.name += " of Major " + statName1 + " and " + statName2;
                                    }
                                    else if (itemStatType2 == itemStatType3)
                                    {
                                        item.name += " of Major " + statName2 + " and " + statName1;
                                    }
                                    else if (itemStatType1 == itemStatType2 && itemStatType1 == itemStatType3)
                                    {
                                        item.name += " of Maximum " + statName1;
                                    }
                                    else
                                    {
                                        item.name += " of " + statName1 + " and " + statName2 + " and " +statName3;
                                    }
                                    break;
                            }

                        }
                    }
                    droppedItems_.push_back(item);
                    enemyLoot.remove(x);
                    break;
                }
            }
        }
    }
    for (int i = 0; i < droppedItems_.length(); i++)
    {
        lootMessage += droppedItems_.value(i).name + "\n";
    }
    msgBox.setWindowTitle("Loot Drop");
    msgBox.setText(QString(lootMessage));
    msgBox.exec();

    return droppedItems_;
}

void enemyLootDrops::setLoot(int enemyType, QString enemyName, int bigLootModifier)
{
    Item item;
    int dRows;
    defaultLoot_.clear();
    enemySpecificLoot_.clear();

    if (enemyType >= 1 && enemyType <= 5)
    {
        dRows =  sizeof banditDefaultItemDrops_ / sizeof banditDefaultItemDrops_[0];

        for (int x = 0; x < dRows; x++)
        {
            item.name =             banditDefaultItemDrops_[x][0];
            item.itemRarity =       banditDefaultItemDrops_[x][1].toInt();
            item.itemType =         banditDefaultItemDrops_[x][2].toInt();
            item.armourRating =     banditDefaultItemDrops_[x][3].toInt();
            item.armourType =       banditDefaultItemDrops_[x][4].toInt();
            item.healType =         banditDefaultItemDrops_[x][5].toInt();
            item.healAmount =       banditDefaultItemDrops_[x][6].toInt();
            item.isEquippable =     banditDefaultItemDrops_[x][7].toInt();
            item.sellPrice =        banditDefaultItemDrops_[x][8].toInt();
            item.isUsable =         banditDefaultItemDrops_[x][9].toInt();
            item.minAtk =           banditDefaultItemDrops_[x][10].toInt();
            item.maxAtk =           banditDefaultItemDrops_[x][11].toInt();
            item.block =            banditDefaultItemDrops_[x][12].toInt();
            item.holdType =         banditDefaultItemDrops_[x][13].toInt();
            item.weaponType =       banditDefaultItemDrops_[x][14].toInt();
            item.weaponEdgeType =   banditDefaultItemDrops_[x][15].toInt();
            item.dotType_ =         banditDefaultItemDrops_[x][16].toInt();
            item.dropWeight =       banditDefaultItemDrops_[x][17].toInt();

            if (item.itemRarity == 2 || item.itemRarity == 3 || item.itemRarity == 4 || item.itemRarity == 5)
                item.dropWeight += bigLootModifier;

            defaultLoot_.push_back(item);
        }

        if (enemyType == 1)
        {
            dRows =  sizeof banditInitiateItemDrops_ / sizeof banditInitiateItemDrops_[0];

            for (int x = 0; x < dRows; x++)
            {
                item.name =             banditInitiateItemDrops_[x][0];
                item.itemRarity =       banditInitiateItemDrops_[x][1].toInt();
                item.itemType =         banditInitiateItemDrops_[x][2].toInt();
                item.armourRating =     banditInitiateItemDrops_[x][3].toInt();
                item.armourType =       banditInitiateItemDrops_[x][4].toInt();
                item.healType =         banditInitiateItemDrops_[x][5].toInt();
                item.healAmount =       banditInitiateItemDrops_[x][6].toInt();
                item.isEquippable =     banditInitiateItemDrops_[x][7].toInt();
                item.sellPrice =        banditInitiateItemDrops_[x][8].toInt();
                item.isUsable =         banditInitiateItemDrops_[x][9].toInt();
                item.minAtk =           banditInitiateItemDrops_[x][10].toInt();
                item.maxAtk =           banditInitiateItemDrops_[x][11].toInt();
                item.block =            banditInitiateItemDrops_[x][12].toInt();
                item.holdType =         banditInitiateItemDrops_[x][13].toInt();
                item.weaponType =       banditInitiateItemDrops_[x][14].toInt();
                item.weaponEdgeType =   banditInitiateItemDrops_[x][15].toInt();
                item.dotType_ =         banditInitiateItemDrops_[x][16].toInt();
                item.dropWeight =       banditInitiateItemDrops_[x][17].toInt();

                if (item.itemRarity == 2 || item.itemRarity == 3 || item.itemRarity == 4 || item.itemRarity == 5)
                    item.dropWeight += bigLootModifier;

                enemySpecificLoot_.push_back(item);
            }
        }
        else if (enemyType == 2)
        {
            dRows =  sizeof banditTrainerItemDrops_ / sizeof banditTrainerItemDrops_[0];

            for (int x = 0; x < dRows; x++)
            {
                item.name =             banditTrainerItemDrops_[x][0];
                item.itemRarity =       banditTrainerItemDrops_[x][1].toInt();
                item.itemType =         banditTrainerItemDrops_[x][2].toInt();
                item.armourRating =     banditTrainerItemDrops_[x][3].toInt();
                item.armourType =       banditTrainerItemDrops_[x][4].toInt();
                item.healType =         banditTrainerItemDrops_[x][5].toInt();
                item.healAmount =       banditTrainerItemDrops_[x][6].toInt();
                item.isEquippable =     banditTrainerItemDrops_[x][7].toInt();
                item.sellPrice =        banditTrainerItemDrops_[x][8].toInt();
                item.isUsable =         banditTrainerItemDrops_[x][9].toInt();
                item.minAtk =           banditTrainerItemDrops_[x][10].toInt();
                item.maxAtk =           banditTrainerItemDrops_[x][11].toInt();
                item.block =            banditTrainerItemDrops_[x][12].toInt();
                item.holdType =         banditTrainerItemDrops_[x][13].toInt();
                item.weaponType =       banditTrainerItemDrops_[x][14].toInt();
                item.weaponEdgeType =   banditTrainerItemDrops_[x][15].toInt();
                item.dotType_ =         banditTrainerItemDrops_[x][16].toInt();
                item.dropWeight =       banditTrainerItemDrops_[x][17].toInt();

                if (item.itemRarity == 2 || item.itemRarity == 3 || item.itemRarity == 4 || item.itemRarity == 5)
                    item.dropWeight += bigLootModifier;

                enemySpecificLoot_.push_back(item);
            }
        }
        else if (enemyType == 3)
        {
            dRows =  sizeof banditGrenItemDrops_ / sizeof banditGrenItemDrops_[0];

            for (int x = 0; x < dRows; x++)
            {
                item.name =             banditGrenItemDrops_[x][0];
                item.itemRarity =       banditGrenItemDrops_[x][1].toInt();
                item.itemType =         banditGrenItemDrops_[x][2].toInt();
                item.armourRating =     banditGrenItemDrops_[x][3].toInt();
                item.armourType =       banditGrenItemDrops_[x][4].toInt();
                item.healType =         banditGrenItemDrops_[x][5].toInt();
                item.healAmount =       banditGrenItemDrops_[x][6].toInt();
                item.isEquippable =     banditGrenItemDrops_[x][7].toInt();
                item.sellPrice =        banditGrenItemDrops_[x][8].toInt();
                item.isUsable =         banditGrenItemDrops_[x][9].toInt();
                item.minAtk =           banditGrenItemDrops_[x][10].toInt();
                item.maxAtk =           banditGrenItemDrops_[x][11].toInt();
                item.block =            banditGrenItemDrops_[x][12].toInt();
                item.holdType =         banditGrenItemDrops_[x][13].toInt();
                item.weaponType =       banditGrenItemDrops_[x][14].toInt();
                item.weaponEdgeType =   banditGrenItemDrops_[x][15].toInt();
                item.dotType_ =         banditGrenItemDrops_[x][16].toInt();
                item.dropWeight =       banditGrenItemDrops_[x][17].toInt();

                if (item.itemRarity == 2 || item.itemRarity == 3 || item.itemRarity == 4 || item.itemRarity == 5)
                    item.dropWeight += bigLootModifier;

                enemySpecificLoot_.push_back(item);
            }
        }
        else if (enemyType == 4)
        {
            dRows =  sizeof banditRaiderItemDrops_ / sizeof banditRaiderItemDrops_[0];

            for (int x = 0; x < dRows; x++)
            {
                item.name =             banditRaiderItemDrops_[x][0];
                item.itemRarity =       banditRaiderItemDrops_[x][1].toInt();
                item.itemType =         banditRaiderItemDrops_[x][2].toInt();
                item.armourRating =     banditRaiderItemDrops_[x][3].toInt();
                item.armourType =       banditRaiderItemDrops_[x][4].toInt();
                item.healType =         banditRaiderItemDrops_[x][5].toInt();
                item.healAmount =       banditRaiderItemDrops_[x][6].toInt();
                item.isEquippable =     banditRaiderItemDrops_[x][7].toInt();
                item.sellPrice =        banditRaiderItemDrops_[x][8].toInt();
                item.isUsable =         banditRaiderItemDrops_[x][9].toInt();
                item.minAtk =           banditRaiderItemDrops_[x][10].toInt();
                item.maxAtk =           banditRaiderItemDrops_[x][11].toInt();
                item.block =            banditRaiderItemDrops_[x][12].toInt();
                item.holdType =         banditRaiderItemDrops_[x][13].toInt();
                item.weaponType =       banditRaiderItemDrops_[x][14].toInt();
                item.weaponEdgeType =   banditRaiderItemDrops_[x][15].toInt();
                item.dotType_ =         banditRaiderItemDrops_[x][16].toInt();
                item.dropWeight =       banditRaiderItemDrops_[x][17].toInt();

                if (item.itemRarity == 2 || item.itemRarity == 3 || item.itemRarity == 4 || item.itemRarity == 5)
                    item.dropWeight += bigLootModifier;

                enemySpecificLoot_.push_back(item);
            }
        }
        else if (enemyType == 5)
        {
            dRows =  sizeof banditAmbusherItemDrops_ / sizeof banditAmbusherItemDrops_[0];

            for (int x = 0; x < dRows; x++)
            {
                item.name =             banditAmbusherItemDrops_[x][0];
                item.itemRarity =       banditAmbusherItemDrops_[x][1].toInt();
                item.itemType =         banditAmbusherItemDrops_[x][2].toInt();
                item.armourRating =     banditAmbusherItemDrops_[x][3].toInt();
                item.armourType =       banditAmbusherItemDrops_[x][4].toInt();
                item.healType =         banditAmbusherItemDrops_[x][5].toInt();
                item.healAmount =       banditAmbusherItemDrops_[x][6].toInt();
                item.isEquippable =     banditAmbusherItemDrops_[x][7].toInt();
                item.sellPrice =        banditAmbusherItemDrops_[x][8].toInt();
                item.isUsable =         banditAmbusherItemDrops_[x][9].toInt();
                item.minAtk =           banditAmbusherItemDrops_[x][10].toInt();
                item.maxAtk =           banditAmbusherItemDrops_[x][11].toInt();
                item.block =            banditAmbusherItemDrops_[x][12].toInt();
                item.holdType =         banditAmbusherItemDrops_[x][13].toInt();
                item.weaponType =       banditAmbusherItemDrops_[x][14].toInt();
                item.weaponEdgeType =   banditAmbusherItemDrops_[x][15].toInt();
                item.dotType_ =         banditAmbusherItemDrops_[x][16].toInt();
                item.dropWeight =       banditAmbusherItemDrops_[x][17].toInt();

                if (item.itemRarity == 2 || item.itemRarity == 3 || item.itemRarity == 4 || item.itemRarity == 5)
                    item.dropWeight += bigLootModifier;

                enemySpecificLoot_.push_back(item);
            }
        }
    }
    else if (enemyType >= 7 && enemyType <= 8)
    {
        dRows =  sizeof koboldDefaultItemDrops_ / sizeof koboldDefaultItemDrops_[0];

        for (int x = 0; x < dRows; x++)
        {
            item.name =             koboldDefaultItemDrops_[x][0];
            item.itemRarity =       koboldDefaultItemDrops_[x][1].toInt();
            item.itemType =         koboldDefaultItemDrops_[x][2].toInt();
            item.armourRating =     koboldDefaultItemDrops_[x][3].toInt();
            item.armourType =       koboldDefaultItemDrops_[x][4].toInt();
            item.healType =         koboldDefaultItemDrops_[x][5].toInt();
            item.healAmount =       koboldDefaultItemDrops_[x][6].toInt();
            item.isEquippable =     koboldDefaultItemDrops_[x][7].toInt();
            item.sellPrice =        koboldDefaultItemDrops_[x][8].toInt();
            item.isUsable =         koboldDefaultItemDrops_[x][9].toInt();
            item.minAtk =           koboldDefaultItemDrops_[x][10].toInt();
            item.maxAtk =           koboldDefaultItemDrops_[x][11].toInt();
            item.block =            koboldDefaultItemDrops_[x][12].toInt();
            item.holdType =         koboldDefaultItemDrops_[x][13].toInt();
            item.weaponType =       koboldDefaultItemDrops_[x][14].toInt();
            item.weaponEdgeType =   koboldDefaultItemDrops_[x][15].toInt();
            item.dotType_ =         koboldDefaultItemDrops_[x][16].toInt();
            item.dropWeight =       koboldDefaultItemDrops_[x][17].toInt();

            if (item.itemRarity == 2 || item.itemRarity == 3 || item.itemRarity == 4 || item.itemRarity == 5)
                item.dropWeight += bigLootModifier;

            defaultLoot_.push_back(item);
        }

        if (enemyName == "Menzid")
        {
            dRows =  sizeof menzidItemDrops_ / sizeof menzidItemDrops_[0];

            for (int x = 0; x < dRows; x++)
            {
                item.name =             menzidItemDrops_[x][0];
                item.itemRarity =       menzidItemDrops_[x][1].toInt();
                item.itemType =         menzidItemDrops_[x][2].toInt();
                item.armourRating =     menzidItemDrops_[x][3].toInt();
                item.armourType =       menzidItemDrops_[x][4].toInt();
                item.healType =         menzidItemDrops_[x][5].toInt();
                item.healAmount =       menzidItemDrops_[x][6].toInt();
                item.isEquippable =     menzidItemDrops_[x][7].toInt();
                item.sellPrice =        menzidItemDrops_[x][8].toInt();
                item.isUsable =         menzidItemDrops_[x][9].toInt();
                item.minAtk =           menzidItemDrops_[x][10].toInt();
                item.maxAtk =           menzidItemDrops_[x][11].toInt();
                item.block =            menzidItemDrops_[x][12].toInt();
                item.holdType =         menzidItemDrops_[x][13].toInt();
                item.weaponType =       menzidItemDrops_[x][14].toInt();
                item.weaponEdgeType =   menzidItemDrops_[x][15].toInt();
                item.dotType_ =         menzidItemDrops_[x][16].toInt();
                item.dropWeight =       menzidItemDrops_[x][17].toInt();

                if (item.itemRarity == 2 || item.itemRarity == 3 || item.itemRarity == 4 || item.itemRarity == 5)
                    item.dropWeight += bigLootModifier;

                enemySpecificLoot_.push_back(item);
            }
        }
    }
}

QVector<Item> enemyLootDrops::getDefaultLoot()
{
    return defaultLoot_;
}

QVector<Item> enemyLootDrops::getEnemySpecificLoot()
{
    return enemySpecificLoot_;
}

void enemyLootDrops::CalculateTotalDropWeight(QVector<Item> loot)
{
    totalDropWeight_ = 0;

    for (int i = 0; i < loot.length(); i++)
    {
        totalDropWeight_ += loot.value(i).dropWeight;
    }
}
