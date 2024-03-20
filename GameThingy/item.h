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
  1 = common          1 = Health          1 = Wizard 	(Cloth) 	Agility default = 6     1 = main hand
  2 = uncommon        2 = Stamina         2 = Rogue	(Leather)       Agility default = 5     2 = 1 handed
  3 = rare                                3 = Warrior	(Mail)		Agility default = 4     3 = 2 handed
  4 = epic  5 = legendary                 4 = Knight	(Plate)		Agility default = 3
  0 = consumable, junk or quest item

  Weapon Types                                          Weapon Edge Type    DoT Type
  1 = Dagger          6 = Staff     11 = Morningstar    1 = Sharp           1 = Bleeding
  2 = Short Sword     7 = Scepter   12 = Greatsword     2 = Blunt           2 = Blunt Trauma
  3 = Long Sword      8 = Greatclub 13 = Battleaxe      3 = Spiked          3 = Poison
  4 = Mace            9 = Warhammer 14 = Greataxe
  5 = Club           10 = Maul

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
      int stat1 = 0;
      int statType1 = 0;
      int stat2 = 0;
      int statType2 = 0;
      int stat3 = 0;
      int statType3 = 0;
      int amount = 1;
      int numStats = 0;
      int weaponType = 0;
      int weaponEdgeType = 0;
      int dotType_ = 0;
      int dropWeight = 0;
  };

#endif // ITEM_H
