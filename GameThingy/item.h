#ifndef ITEM_H
#define ITEM_H
#include <QString>
/*Item Types                      armourType	amourRating     statTypes
  1 = Consumable	6 = Ring		1 = Cloth	+4 dodge        1 = Vitality	6 = Precision
  2 = Weapon		7 = Trinket		2 = Leather	+3 dodge        2 = Strength	7 = Dodge
  3 = Armour		8 = random		3 = Mail	+2 dodge        3 = Stamina     8 = Block
  4 = Shield		9 = Junk		4 = Plate	+1 dodge        4 = Agility		9 = Hit
  5 = Quest                                                     5 = Luck

  itemRarity          healType            Class Types                                       holdType
  1 = common          1 = Health          1 = Wizard 	(Cloth) 	Agility default = 8     1 = main hand
  2 = uncommon        2 = Stamina         2 = Rogue	(Leather)       Agility default = 7     2 = 1 handed
  3 = rare                                3 = Warrior	(Mail)		Agility default = 6     3 = 2 handed
  4 = epic  5 = legendary                 4 = Knight	(Plate)		Agility default = 5
  0 = consumable, junk or quest item*/
  struct Item{
      QString name;
      int itemRarity;
      int itemType;
      int armourRating;
      int armourType;
      int healType;
      int healAmount;
      bool isEquippable;
      int sellPrice;
      bool isUsable;
      int weight;
      int minAtk;
      int maxAtk;
      int block;
      int holdType;
      int stat1;
      int statType1;
      int stat2;
      int statType2;
      int stat3;
      int statType3;
      int amount;
  };

#endif // ITEM_H
