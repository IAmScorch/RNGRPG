#ifndef ITEM_H
#define ITEM_H
#include <QString>
/*Item Types                        armourType	amourRating     statTypes
  1 = Consumable	6 = Ring		1 = Cloth	+6 agility      1 = Vitality	6 = Precision
  2 = Weapon		7 = Trinket		2 = Leather	+5 agility      2 = Strength	7 = Block
  3 = Armour		8 = random		3 = Mail	+4 agility      3 = Stamina
  4 = Shield		9 = Junk		4 = Plate	+3 agility      4 = Agility
  5 = Quest                                                     5 = Luck

  itemRarity          healType            Class Types                                       holdType
  1 = common          1 = Health          1 = Wizard 	(Cloth) 	Agility default = 8     1 = main hand
  2 = uncommon        2 = Stamina         2 = Rogue	(Leather)       Agility default = 7     2 = 1 handed
  3 = rare                                3 = Warrior	(Mail)		Agility default = 6     3 = 2 handed
  4 = epic  5 = legendary                 4 = Knight	(Plate)		Agility default = 5
  0 = consumable, junk or quest item

  ItemSlots 0 for empty 1 for full. Exception for main and off hand slots. They will have additional values for holdTypes
  Main Hand 1 = Main handed equipped, 2 = One handed equipped, 3 = Two handed equipped
  Off Hand 1 = One Handed equipped, 2 = Shield equipped, 3 = Two handed equipped
  Armour, Ring One, Ring Two, Trinket One, Trinket Two*/
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
      int numStats;
  };

#endif // ITEM_H
