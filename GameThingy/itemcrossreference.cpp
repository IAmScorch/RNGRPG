#include "itemcrossreference.h"

itemCrossReference::itemCrossReference()
{

}

QString itemCrossReference::getItemType(int crossReference)
{
    return itemType_[crossReference];
}

QString itemCrossReference::getArmourType(int crossReference)
{
    return armourType_[crossReference];
}

QString itemCrossReference::getStatType(int crossReference)
{
    return statType_[crossReference];
}

QString itemCrossReference::getItemRarity(int crossReference)
{
    return itemRarity_[crossReference];
}

QString itemCrossReference::getHoldType(int crossReference)
{
    return  holdType_[crossReference];
}
