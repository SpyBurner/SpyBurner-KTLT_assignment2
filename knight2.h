#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG
enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
enum ItemType { ANTIDOTE = 0, PHOENIXDOWNI, PHOENIXDOWNII, PHOENIXDOWNIII, PHOENIXDOWNIV };
enum Treasure { PALADINSHIELD = 0, LANCELOTSPEAR, GUINEVEREHAIR, EXCALIBUR , NOPE};

class BaseItem; //Forward declaration
class BaseKnight;
class ArmyKnights;

class BaseBag {
protected:
//public:
    int capacity = 0;
    int currentSize = 0;
    BaseItem* itemListHead = nullptr;

public:
    ~BaseBag();

    virtual bool insertFirst(BaseItem* item);
    virtual BaseItem* get(ItemType itemType);
    virtual BaseItem* getPhoenixDown(BaseKnight* knight);
    virtual string toString() const;

    virtual void swap(BaseItem* item1, BaseItem* item2);
    virtual void erase(BaseItem* item);

    virtual bool canHold(ItemType itemType);
    void dropItem();
};
/// <Custom bags>
class PaladinBag : public BaseBag {
public:
    int capacity = -1;
};
class LancelotBag : public BaseBag {
public:
    int capacity = 16;
};
class DragonBag : public BaseBag {
public:
    int capacity = 14;

    bool canHold(ItemType itemType);
};
class NormalBag : public BaseBag {
public:
    int capacity = 19;
};
/// </Custom bags>

class BaseOpponent;

class BaseKnight {
//protected:
public:
    int id = 0;
    int hp = 0;
    int maxhp = 0;
    double knightBaseDamage = 0;
    int level = 0;
    int gil = 0;
    int antidote = 0;
    int phoenixdownI = 0;
    BaseBag * bag = nullptr;
    KnightType knightType = NORMAL;

public:
    ~BaseKnight();

    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
};

/// <Custom knights
class PaladinKnight : public BaseKnight {
public:
    double knightBaseDamage = 0.06;
};
class LancelotKnight : public BaseKnight {
public:
    double knightBaseDamage = 0.05;
};
class DragonKnight : public BaseKnight {
public:
    double knightBaseDamage = 0.075;
};
class NormalKnight : public BaseKnight {
public:
    double knightBaseDamage = 0;
};
/// </Custom knights>

class BaseItem {
public:
    BaseItem* next = nullptr;
    ItemType itemType = ANTIDOTE;

    ~BaseItem();

    virtual bool canUse(BaseKnight* knight) = 0;
    virtual void use(BaseKnight* knight) = 0;
};

//ANTIDOTE , PHOENIXDOWNI, PHOENIXDOWNII, PHOENIXDOWNIII, PHOENIXDOWNIV
class Antidote : public BaseItem {
public:
    ItemType itemType = ANTIDOTE;

    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
};
class PhoenixdownI : public BaseItem {
public:
    ItemType itemType = PHOENIXDOWNI;

    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
};
class PhoenixdownII : public BaseItem {
public:
    ItemType itemType = PHOENIXDOWNII;

    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
};
class PhoenixdownIII : public BaseItem {
public:
    ItemType itemType = PHOENIXDOWNIII;

    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
};
class PhoenixdownIV : public BaseItem {
public:
    ItemType itemType = PHOENIXDOWNIV;

    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
};


//class PaladinShield : public BaseItem{
//    ItemType itemType = PALADINSHIELD;
//};
//class LancelotSpear : public BaseItem{
//    ItemType itemType = LANCELOTSPEAR;
//};
//class GuinevereHair : public BaseItem{
//    ItemType itemType = GUINEVEREHAIR;
//};
//class Excalibur : public BaseItem{
//    ItemType itemType = EXCALIBUR;
//};

class BaseOpponent {
public: 
    ~BaseOpponent();

    int baseDamage = 0;
    int forceDamage = 0;

    int evil = 1;

    int ignore = 0;//CHANGE TO STATIC IN SOME CLASSES
    int eventId = 0;
    int index = 0;
    int levelO();

    int rewardGil = 0;
    int rewardLevel = 0;

    static BaseOpponent* create(int eventId, int index);
    virtual void specialReward(ArmyKnights* armyknight);
    virtual void specialPunish(ArmyKnights* armyknight);
    virtual void ignoreNextTime();
};

class MadBear : public BaseOpponent {
public:
    int eventId = 1;
    int rewardGil = 100;
    int baseDamage = 10;
};
class Bandit : public BaseOpponent {
public:
    int eventId = 2;
    int rewardGil = 150;
    int baseDamage = 15;
};
class LordLupin : public BaseOpponent {
public:
    int eventId = 3;
    int rewardGil = 450;
    int baseDamage = 45;
};
class Elf : public BaseOpponent {
public:
    int eventId = 4;
    int rewardGil = 750;
    int baseDamage = 75;
};
class Troll : public BaseOpponent {
public:
    int eventId = 5;
    int rewardGil = 800;
    int baseDamage = 95;
};

//Event opponents
class Tornbery : public BaseOpponent {
    int rewardLevel = 1;
    int forceDamage = 10;

    void specialPunish(ArmyKnights* armyknight);
};
class QueenOfCards : public BaseOpponent {
    void specialReward(ArmyKnights* armyknight);
    void specialPunish(ArmyKnights* armyknight);
};
class NinaDeRings : public BaseOpponent {
    int evil = 0;
    void specialReward(ArmyKnights* armyknight);
};
class DurianGarden : public BaseOpponent {
    int evil = 0;
    void specialReward(ArmyKnights* armyknight);
};
class OmegaWeapon : public BaseOpponent {
    void specialReward(ArmyKnights* armyknight);
    void specialPunish(ArmyKnights* armyknight);

    static int ignore;
    void ignoreNextTime();
};
class Hades : public BaseOpponent {
    void specialReward(ArmyKnights* armyknight);
    void specialPunish(ArmyKnights* armyknight);

    static int ignore;
    void ignoreNextTime();
};
class PickPhoenixDown : public BaseOpponent {
public:
    int evil = 0;
    PickPhoenixDown(int eventId);
    void specialReward(ArmyKnights* armyknight);
};
class PickTreasure : public BaseOpponent {
public:
    int evil = 0;
    PickTreasure(int eventId);
    void specialReward(ArmyKnights* armyknight);
};

class Events {
private:
    int size;
    int current;
    int* eventList;

public:
    Events(const string& file_events);
    ~Events();

    int count() const;
    int get(int i) const;

    void print() const;
};

class ArmyKnights {
private:
    int size;
    int current;
    BaseKnight** knights;
    

public:
    int TreasureChecklist[5];

    ArmyKnights(const string& file_armyknights);
    ~ArmyKnights();
    bool adventure(Events* events);
    int count() const;
    BaseKnight* lastKnight() const;

    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;

    void printInfo() const;
    void printResult(bool win) const;

    bool DetermineWinner(ArmyKnights* armyknight, BaseOpponent* opponent);
    void itemOverflow(BaseItem* item, int index);
    void gilOverflow(int amount, int index);
    void reward(ArmyKnights* armyknight, BaseOpponent* opponent);
    void punish(ArmyKnights* armyknight, BaseOpponent* opponent);

    void heal();
    void pop();

    bool fight(BaseOpponent* opponent);
    bool fightUltimecia();
    
};

class KnightAdventure {
private:
    ArmyKnights * armyKnights;
    Events * events;

public:
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string& file_armyknights);
    void loadEvents(const string& file_events);
    void run();

    void printEvents();
};



#endif // __KNIGHT2_H__