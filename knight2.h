#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG
enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL};
enum ItemType { ANTIDOTE = 0, PHOENIXDOWNI, PHOENIXDOWNII, PHOENIXDOWNIII, PHOENIXDOWNIV};
enum Treasure { PALADINSHIELD = 0, LANCELOTSPEAR, GUINEVEREHAIR, EXCALIBUR , NOPE};

class BaseItem; //Forward declaration
class BaseKnight;
class ArmyKnights;

class BaseBag {
protected:
//public:*
    int currentSize = 0;
    BaseItem* itemListHead = nullptr;

public:
    int capacity = 0;

    virtual ~BaseBag();

    virtual int count() const;

    void print();

    virtual bool insertFirst(BaseItem* item);
    virtual BaseItem* get(ItemType itemType);
    virtual BaseItem* getPhoenixDown(BaseKnight* knight);
    virtual string toString() const;

    virtual bool swap(BaseItem* item1, BaseItem* item2);
    virtual void erase(BaseItem* item);

    virtual bool canHold(ItemType itemType);
    virtual void dropItem();
};
/// <Custom bags>
class PaladinBag : public BaseBag {
public:
    PaladinBag() {
        capacity = -1;
    }
};
class LancelotBag : public BaseBag {
public:
    LancelotBag() {
        capacity = 16;
    }
};
class DragonBag : public BaseBag {
public:
    DragonBag() {
        capacity = 14;
    }

    bool canHold(ItemType itemType) override;
};
class NormalBag : public BaseBag {
public:
    NormalBag() {
        capacity = 19;
    }
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
    virtual ~BaseKnight();

    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
};

/// <Custom knights
class PaladinKnight : public BaseKnight {
public:
    PaladinKnight() {
        knightBaseDamage = 0.06;
    }
};
class LancelotKnight : public BaseKnight {
public:
    LancelotKnight() {
        knightBaseDamage = 0.05;
    }
};
class DragonKnight : public BaseKnight {
public:
    DragonKnight() {
        knightBaseDamage = 0.075;
    }
};
class NormalKnight : public BaseKnight {
public:
    NormalKnight() {
        knightBaseDamage = 0;
    }
};
/// </Custom knights>

class BaseItem {
public:
    BaseItem* next = nullptr;
    ItemType itemType = ANTIDOTE;

    int id = 0;

    virtual bool canUse(BaseKnight* knight) = 0;
    virtual void use(BaseKnight* knight) = 0;
};

//ANTIDOTE , PHOENIXDOWNI, PHOENIXDOWNII, PHOENIXDOWNIII, PHOENIXDOWNIV
class Antidote : public BaseItem {
public:
    Antidote() {
        itemType = ANTIDOTE;
    }

    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
};
class PhoenixdownI : public BaseItem {
public:
    PhoenixdownI() {
        itemType = PHOENIXDOWNI;
    }

    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
};
class PhoenixdownII : public BaseItem {
public:
    PhoenixdownII() {
        itemType = PHOENIXDOWNII;
    }

    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
};
class PhoenixdownIII : public BaseItem {
public:
    PhoenixdownIII() {
        itemType = PHOENIXDOWNIII;
    }

    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
};
class PhoenixdownIV : public BaseItem {
public:
    PhoenixdownIV() {
        itemType = PHOENIXDOWNIV;
    }

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
    virtual ~BaseOpponent();

    int baseDamage = 0;

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
    MadBear() {
        eventId = 1;
        rewardGil = 100;
        baseDamage = 10;
    }
};
class Bandit : public BaseOpponent {
public:
    Bandit() {
        eventId = 2;
        rewardGil = 150;
        baseDamage = 15;
    }
};
class LordLupin : public BaseOpponent {
public:
    LordLupin() {
        eventId = 3;
        rewardGil = 450;
        baseDamage = 45;
    }
};
class Elf : public BaseOpponent {
public:
    Elf() {
        eventId = 4;
        rewardGil = 750;
        baseDamage = 75;
    }
};
class Troll : public BaseOpponent {
public:
    Troll() {
        eventId = 5;
        rewardGil = 800;
        baseDamage = 95;
    }
};

//Event opponents
class Tornbery : public BaseOpponent {
    void specialPunish(ArmyKnights* armyknight) override;
public:
    Tornbery() {
        eventId = 6;
        rewardLevel = 1;
    } 
};
class QueenOfCards : public BaseOpponent {
    void specialReward(ArmyKnights* armyknight) override;
    void specialPunish(ArmyKnights* armyknight) override;
public:
    QueenOfCards() {
        eventId = 7;
    }
};
class NinaDeRings : public BaseOpponent {
    void specialReward(ArmyKnights* armyknight) override;
public:
    NinaDeRings() {
        eventId = 8;
        evil = 0;
    }
};
class DurianGarden : public BaseOpponent {
    void specialReward(ArmyKnights* armyknight) override;
public:
    DurianGarden() {
        eventId = 9;
        evil = 0;
    }
};
class OmegaWeapon : public BaseOpponent {
    void specialReward(ArmyKnights* armyknight) override;
    void specialPunish(ArmyKnights* armyknight) override;

    static int ignore;
    void ignoreNextTime() override;
public:
    OmegaWeapon() {
        eventId = 10;
    }
};
class Hades : public BaseOpponent {
    void specialReward(ArmyKnights* armyknight) override;
    void specialPunish(ArmyKnights* armyknight) override;

    static int ignore;
    void ignoreNextTime() override;
public:
    Hades() {
        eventId = 11;
    }
};
class PickPhoenixDown : public BaseOpponent {
    void specialReward(ArmyKnights* armyknight) override;
public:
    PickPhoenixDown() {
        evil = 0;
    }

    PickPhoenixDown(int eventId);
};
class PickTreasure : public BaseOpponent {
    void specialReward(ArmyKnights* armyknight) override;
public:
    PickTreasure() {
        evil = 0;
    }

    PickTreasure(int eventId);
};

class Events {
private:
    int size = 0;
    int current = 0;
    int* eventList = nullptr;

public:
    Events(const string& file_events);
    virtual ~Events();

    int count() const;
    int get(int i) const;

    void print() const;
};

class ArmyKnights {
private:
    int size = 0;
    int current = 0;
    BaseKnight** knights = nullptr;

    bool printingResult = 0;
    int skippedKnight = 0;
    BaseKnight* UltimeciaLastKnight = nullptr;

public:
    int TreasureChecklist[5];

    ArmyKnights(const string& file_armyknights);
    virtual ~ArmyKnights();
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
    ArmyKnights * armyKnights = nullptr;
    Events * events = nullptr;

public:
    KnightAdventure();
    virtual ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string& file_armyknights);
    void loadEvents(const string& file_events);
    void run();

    void printEvents();
};



#endif // __KNIGHT2_H__