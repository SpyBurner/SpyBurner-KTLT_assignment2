#include "knight2.h"

#define fto(i,a,b) for (int i = a; i<=b; ++i)
#define fdto(i,a,b) for (int i = a; i >= b; --i)

#define log(st) cout << st << endl

//STATICS HERE
int OmegaWeapon::ignore = 0;
int Hades::ignore = 0;
//

//NO CLASS FUNCTIONS
int isPrime(int s) {
	if (s <= 1) return 0;
	if (s == 2) return 1;
	fto(i, 2, sqrt(s)) {
		if (s % i == 0) return 0;
	}
	return 1;
}
int PythagorasTriple(int maxhp) {
	if (maxhp < 100) return 0;
	int a = maxhp % 10;
	int b = (maxhp / 10) % 10;
	int c = (maxhp / 100) % 10;

	if (a * b * c == 0) return 0;

	if (a * a + b * b == c * c || b * b + c * c == a * a || c * c + a * a == b * b)
		return 1;
	return 0;
}
KnightType DetermineKnightType(int maxhp){
	if (isPrime(maxhp)) return PALADIN;
	if (maxhp == 888) return LANCELOT;
	if (PythagorasTriple(maxhp)) return DRAGON;
	return NORMAL;
}
//

/* * * BEGIN implementation of class BaseBag * * */

BaseBag::~BaseBag() {
	BaseItem* ptr = itemListHead;
	while (ptr != nullptr)
	{
		BaseItem* current = ptr;
		ptr = ptr->next;

		delete current;
	}
}

void BaseBag::print() {
	BaseItem* ptr = itemListHead->next;
	while (ptr != nullptr) {
		cout << ptr->itemType << " ";
		ptr = ptr->next;
	}
	cout << endl;
}

int BaseBag::count() const{
	//return currentSize;
	if (currentSize == 0) return 0;
	BaseItem* ptr = itemListHead->next;
	int cnt = 0;
	while (ptr != nullptr) {
		cnt++;
		ptr = ptr->next;
	}
	return cnt;
}

bool BaseBag::insertFirst(BaseItem* item) {
	//log("Bag size:");
	//log(currentSize);
	if (currentSize == capacity || !canHold(item->itemType)) return 0;
	if (currentSize == 0) {
		itemListHead = new Antidote;
		itemListHead->next = item;
	}
	else {
		item->next = itemListHead->next;
		itemListHead->next = item;
	}
	currentSize++;
	return 1;
}
BaseItem* BaseBag::get(ItemType itemType) {
	if (count() <= 0) return nullptr;
	BaseItem* item = itemListHead->next;
	while (item != nullptr) {
		if (item->itemType == itemType) break;
		item = item->next;
	}
	return item;
}
BaseItem* BaseBag::getPhoenixDown(BaseKnight* knight) {
	if (count() <= 0) return nullptr;
	BaseItem* item = itemListHead->next;
	while (item != nullptr) {
		if (PHOENIXDOWNI <= item->itemType && item->itemType <= PHOENIXDOWNIV && item->canUse(knight)) {
			break;
		}
		item = item->next;
	}
	return item; //Return nullptr if not found
}

bool BaseBag::swap(BaseItem* item1, BaseItem* item2) {
	if (itemListHead == nullptr) return 0;

	BaseItem* pre1 = itemListHead;
	BaseItem* pre2 = itemListHead;
	BaseItem* itemPtr1 = itemListHead->next;
	BaseItem* itemPtr2 = itemListHead->next;

	while (itemPtr1 != nullptr && itemPtr1 != item1) {
		pre1 = itemPtr1;
		itemPtr1 = itemPtr1->next;
	}
	while (itemPtr2 != nullptr && itemPtr2 != item2) {
		pre2 = itemPtr2;
		itemPtr2 = itemPtr2->next;
	}

	if (itemPtr1 == nullptr || itemPtr2 == nullptr) return 0;

	if (pre1 != itemListHead) {
		pre1->next = itemPtr2;
	}
	else {
		itemListHead->next = itemPtr2;
	}

	if (pre2 != itemListHead) {
		pre2->next = itemPtr1;
	}
	else {
		itemListHead->next = itemPtr1;
	}

	BaseItem* temp = itemPtr1->next;
	itemPtr1->next = itemPtr2->next;
	itemPtr2->next = temp;

	return 1;
}

void BaseBag::erase(BaseItem* item) {
	bool erasible = swap(itemListHead->next, item);
	if (!erasible) return;

	itemListHead->next = itemListHead->next->next;
	delete item;
	item = nullptr;

	currentSize--;
}

string BaseBag::toString() const {
	string typeString[] = { "Antidote", "PhoenixI", "PhoenixII", "PhoenixIII", "PhoenixIV" };

	string s = "";
	s += "Bag[count=" + to_string(count()) + ";";

	if (currentSize != 0) {
		BaseItem* ptr = itemListHead->next;
		while (ptr != nullptr) {
			s += typeString[int(ptr->itemType)];
			ptr = ptr->next;
			if (ptr != nullptr) s += ",";
		}
	}

	s += "]";
	return s;
}
bool BaseBag::canHold(ItemType itemType) {
	return 1;
}

//DragonBag cant hold antidote
bool DragonBag::canHold(ItemType itemType) {
	if (itemType == ANTIDOTE) return 0;
	return 1;
}
//

void BaseBag::dropItem() {
	if (count() > 0) {
		erase(itemListHead->next);
	}
}

/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseItem * * */


bool Antidote::canUse(BaseKnight* knight) {
	return 1;
}
void Antidote::use(BaseKnight* knight) {
	knight->hp = knight->maxhp;

	knight->hp = min(knight->hp, knight->maxhp);
}

bool PhoenixdownI::canUse(BaseKnight* knight) {
	return knight->hp <= 0;
}
void PhoenixdownI::use(BaseKnight* knight) {
	knight->hp = knight->maxhp;
}

bool PhoenixdownII::canUse(BaseKnight* knight) {
	return knight->hp < int(knight->maxhp / 4);
}
void PhoenixdownII::use(BaseKnight* knight) {
	knight->hp = knight->maxhp;

	knight->hp = min(knight->hp, knight->maxhp);
}

bool PhoenixdownIII::canUse(BaseKnight* knight) {
	return knight->hp < int(knight->maxhp / 3);
}
void PhoenixdownIII::use(BaseKnight* knight) {
	if (knight->hp <= 0) knight->hp = knight->maxhp / 3;
	else {
		knight->hp += knight->maxhp / 4;
	}

	knight->hp = min(knight->hp, knight->maxhp);
}

bool PhoenixdownIV::canUse(BaseKnight* knight) {
	return knight->hp < int(knight->maxhp / 2);
}
void PhoenixdownIV::use(BaseKnight* knight) {
	if (knight->hp <= 0) knight->hp = knight->maxhp / 2;
	else {
		knight->hp += knight->maxhp / 5;
	}

	knight->hp = min(knight->hp, knight->maxhp);
}

/* * * END implementation of class BaseItem * * */

/* * * BEGIN implementation of class BaseKnight * * */
BaseKnight::~BaseKnight() {
	delete bag;
}

string BaseKnight::toString() const {
	string typeString[4] = { "PALADIN", "LANCELOT", "DRAGON", "NORMAL" };
	// inefficient version, students can change these code
	//      but the format output must be the same
	string s("");
	s += "[Knight:id:" + to_string(id)
		+ ",hp:" + to_string(hp)
		+ ",maxhp:" + to_string(maxhp)
		+ ",level:" + to_string(level)
		+ ",gil:" + to_string(gil)
		+ "," + bag->toString()
		+ ",knight_type:" + typeString[knightType]
		+ "]";
	return s;
}
BaseKnight* BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI) {
	KnightType typeOfKnight = DetermineKnightType(maxhp);
	BaseKnight* res = nullptr;


	switch (typeOfKnight)
	{
	case PALADIN:
		res = new PaladinKnight;
		res->bag = new PaladinBag;
		break;
	case LANCELOT:
		res = new LancelotKnight;
		res->bag = new LancelotBag;
		break;
	case DRAGON:
		res = new DragonKnight;
		res->bag = new DragonBag;
		break;
	default:
		res = new NormalKnight;
		res->bag = new NormalBag;
		break;
	}

	res->id = id;
	res->hp = res->maxhp = maxhp;
	res->level = level;
	res->gil = gil;

	fto(i, 1, phoenixdownI) {
		PhoenixdownI* phoenixdownI = new PhoenixdownI;
		res->bag->insertFirst(phoenixdownI);
	}

	fto(i, 1, antidote) {
		Antidote* antidote = new Antidote;
		res->bag->insertFirst(antidote);
	}

	res->knightType = typeOfKnight;

	return res;
}

/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */
//Constructor & destructor
ArmyKnights::ArmyKnights(const string& file_armyknights) {
	ifstream inFile(file_armyknights);
	int n; inFile >> n;
	current = size = n;
	knights = new BaseKnight * [n + 1];

	knights[0] = nullptr;

	fto(id, 1, n) {
		int maxhp, level, phoenixdownI, gil, antidote;
		inFile >> maxhp >> level >> phoenixdownI >> gil >> antidote;

		knights[id] = BaseKnight::create(id, maxhp, level, gil, antidote, phoenixdownI);
	}

	fto(i, 0, 3) {
		TreasureChecklist[i] = 0;
	}

	//fto(id, 1, n) {
	//    cout << knights[id]->toString() << endl;
	//}
}

ArmyKnights::~ArmyKnights() {
	fto(i, 0, size-1) {
		delete knights[i];
	}
	delete[] knights;
}
//

bool ArmyKnights::hasPaladinShield() const {
	return TreasureChecklist[0];
}
bool ArmyKnights::hasLancelotSpear() const {
	return TreasureChecklist[1];
}
bool ArmyKnights::hasGuinevereHair() const {
	return TreasureChecklist[2];
}
bool ArmyKnights::hasExcaliburSword() const {
	return TreasureChecklist[3];
}

void ArmyKnights::printInfo() const {
	cout << "No. knights: " << this->count();
	if (this->current > 0) {
		BaseKnight* lknight = lastKnight(); // last knight
		cout << ";" << lknight->toString();
	}
	cout << ";PaladinShield:" << this->hasPaladinShield()
		<< ";LancelotSpear:" << this->hasLancelotSpear()
		<< ";GuinevereHair:" << this->hasGuinevereHair()
		<< ";ExcaliburSword:" << this->hasExcaliburSword()
		<< endl
		<< string(50, '-') << endl;
}
void ArmyKnights::printResult(bool win) const {
	cout << (win ? "WIN" : "LOSE") << endl;
}

int ArmyKnights::count() const {
	return current + ((printingResult)? skippedKnight : 0);
}
BaseKnight* ArmyKnights::lastKnight() const {
	//log(current);
	if (current <= 0) return nullptr;
	if (UltimeciaLastKnight != nullptr && printingResult) return UltimeciaLastKnight;
	return knights[current];
}

bool ArmyKnights::DetermineWinner(ArmyKnights* armyknight, BaseOpponent* opponent) {
	BaseKnight* knight = lastKnight();	if (knight->knightType == PALADIN || knight->knightType == LANCELOT) {
		
		if (1 <= opponent->eventId && opponent->eventId <= 5) {
			return 1;
		}
	}
	if (opponent->eventId == 10) {
		if (knight->knightType == DRAGON || (knight->hp == knight->maxhp && knight->level == 10))
			return 1;
		return 0;
	}
	if (opponent->eventId == 11) {
		if (knight->level == 10 || (knight->level >= 8 && knight->knightType == PALADIN))
			return 1;
		return 0;
	}	return knight->level >= opponent->levelO();
}

void ArmyKnights::itemOverflow(BaseItem* item, int index) {
	BaseKnight* knight = knights[index];
	if (index == -1) return;

	bool inserted = knight->bag->insertFirst(item);
	//log("Picked");
	//log(inserted);
	if (inserted) {
		return;
	}
	itemOverflow(item, index - 1);
}

void ArmyKnights::gilOverflow(int amount, int index) {
	if (amount <= 0 || index == 0) return;
	BaseKnight* knight = knights[index];
	knight->gil += amount;
	amount = knight->gil - 999;
	knight->gil = min(knight->gil, 999);
	gilOverflow(amount, index - 1);
}

void ArmyKnights::reward(ArmyKnights* armyknight, BaseOpponent* opponent) {
	
	int eventid = opponent->eventId;
	BaseKnight* knight = armyknight->lastKnight();

	knight->gil += opponent->rewardGil;
	knight->level += opponent->rewardLevel;

	knight->gil = min(knight->gil, 999);
	knight->level = min(knight->level, 10);

	opponent->specialReward(armyknight);
}
void ArmyKnights::punish(ArmyKnights* armyknight, BaseOpponent* opponent) {
	int eventid = opponent->eventId;
	BaseKnight* knight = armyknight->lastKnight();

	int damage = opponent->baseDamage * (opponent->levelO() - knight->level);
	knight->hp -= damage;

	opponent->specialPunish(armyknight);
}

void ArmyKnights::heal() {
	BaseKnight* knight = lastKnight();
	BaseItem* item = knight->bag->getPhoenixDown(lastKnight());
	if (item != nullptr) {
		item->use(lastKnight());
		lastKnight()->bag->erase(item);
		return;
	}

	if (knight->hp > 0) return;

	if (knight->gil >= 100) {
		knight->gil -= 100;
		knight->hp = knight->maxhp / 2;
	}

	return;
}
void ArmyKnights::pop() {
	if (current > 0) {
		current--;
	}
}

/* * * END implementation of class ArmyKnights * * */


/* * * BEGIN implementation of class BaseOpponent * * */
//BaseOpponent::BaseOpponent() {
//
//}
BaseOpponent::~BaseOpponent() {
}

PickPhoenixDown::PickPhoenixDown(int eventId) {
	evil = 0;
	this->eventId = eventId;
}
PickTreasure::PickTreasure(int eventId) {
	evil = 0;
	this->eventId = eventId;
}

int BaseOpponent::levelO() {
	return evil * ((index + eventId) % 10 + 1);
}
BaseOpponent* BaseOpponent::create(int eventId, int index) {
	BaseOpponent* result = nullptr;
	switch (eventId) {
	case 1:
		result = new MadBear;
		break;
	case 2:
		result = new Bandit;
		break;
	case 3:
		result = new LordLupin;
		break;
	case 4:
		result = new Elf;
		break;
	case 5:
		result = new Troll;
		break;
	case 6:
		result = new Tornbery;
		break;
	case 7:
		result = new QueenOfCards;
		break;
	case 8:
		result = new NinaDeRings;
		break;
	case 9:
		result = new DurianGarden;
		break;
	case 10:
		result = new OmegaWeapon;
		break;
	case 11:
		result = new Hades;
		break;
	case 112:
	case 113:
	case 114:
		result = new PickPhoenixDown(eventId);
		break;
	case 95:
	case 96:
	case 97:
	case 98:
		result = new PickTreasure(eventId);
		break;
	default:
		result = new BaseOpponent;
		break;
	}

	result->index = index;

	return result;
}
void BaseOpponent::specialReward(ArmyKnights* armyknight) {

}
void BaseOpponent::specialPunish(ArmyKnights* armyknight) {

}
void BaseOpponent::ignoreNextTime() {

}

void Tornbery::specialPunish(ArmyKnights* armyknight) {
	BaseKnight* knight = armyknight->lastKnight();

	if (knight->knightType == DRAGON) return;

	BaseItem* antidote = knight->bag->get(ANTIDOTE);
	if (antidote != nullptr) {
		knight->bag->erase(antidote);
		return;
	}

	knight->hp -= 10;
	knight->bag->dropItem();
	knight->bag->dropItem();
	knight->bag->dropItem();
}

void QueenOfCards::specialReward(ArmyKnights* armyknight) {
	BaseKnight* knight = armyknight->lastKnight();

	armyknight->gilOverflow(knight->gil, armyknight->count());
}
void QueenOfCards::specialPunish(ArmyKnights* armyknight) {
	BaseKnight* knight = armyknight->lastKnight();

	if (knight->knightType == PALADIN) return;

	knight->gil = knight->gil / 2;
}

void NinaDeRings::specialReward(ArmyKnights* armyknight) {
	BaseKnight* knight = armyknight->lastKnight();

	if ((knight->gil >= 50 && knight->hp < knight->maxhp / 3) || knight->knightType == PALADIN) {
		knight->gil -= 50;
		knight->hp += knight->maxhp / 5;
		if (knight->knightType == PALADIN)
			knight->gil += 50;
	}
	knight->hp = min(knight->hp, knight->maxhp);
}

void DurianGarden::specialReward(ArmyKnights* armyknight) {
	BaseKnight* knight = armyknight->lastKnight();
	knight->hp = knight->maxhp;
}

void OmegaWeapon::specialReward(ArmyKnights* armyknight) {
	BaseKnight* knight = armyknight->lastKnight();

	knight->level = 10;
	knight->gil = 999;
}
void OmegaWeapon::specialPunish(ArmyKnights* armyknight) {
	BaseKnight* knight = armyknight->lastKnight();

	knight->hp = 0;
}
void OmegaWeapon::ignoreNextTime() {
	OmegaWeapon::ignore = 1;
}

void Hades::specialReward(ArmyKnights* armyknight) {
	BaseKnight* knight = armyknight->lastKnight();

	armyknight->TreasureChecklist[PALADINSHIELD] = 1;
}
void Hades::specialPunish(ArmyKnights* armyknight) {
	BaseKnight* knight = armyknight->lastKnight();

	knight->hp = 0;
}
void Hades::ignoreNextTime() {
	Hades::ignore = 1;
}

void PickPhoenixDown::specialReward(ArmyKnights* armyknight) {
	BaseItem* item = nullptr;
	switch (eventId){
	case 112:
		item = new PhoenixdownII;
		break;
	case 113:
		item = new PhoenixdownIII;
		break;
	case 114:
		item = new PhoenixdownIV;
		break;
	default:
		item = new PhoenixdownII;
		break;
	}
	armyknight->itemOverflow(item, armyknight->count());
}
void PickTreasure::specialReward(ArmyKnights* armyknight) {
	BaseItem* item = nullptr;
	switch (eventId) {
	case 95:
		armyknight->TreasureChecklist[PALADINSHIELD] = 1;
		break;
	case 96:
		armyknight->TreasureChecklist[LANCELOTSPEAR] = 1;
		break;
	case 97:
		armyknight->TreasureChecklist[GUINEVEREHAIR] = 1;
		break;
	case 98:
		if (armyknight->hasPaladinShield() && armyknight->hasLancelotSpear()
			&& armyknight->hasGuinevereHair())
		armyknight->TreasureChecklist[EXCALIBUR] = 1;
		break;
	}
}
/* * * END implementation of class BaseOpponent * * */

/* * * BEGIN implementation of class Events * * */
Events::Events(const string& file_events) {
	ifstream inFile(file_events);
	int e; inFile >> e;
	current = size = e;

	eventList = new int[e];
	fto(i, 0, e - 1) {
		inFile >> eventList[i];
	}
}
Events::~Events() {
	delete[] eventList;
}

int Events::count() const {
	return current;
}
int Events::get(int i) const {
	return eventList[i];
}
void Events::print() const {
	fto(i, 0, size - 1) {
		cout << eventList[i] << " ";
	}
	cout << endl;
}
/* * * END implementation of class Events * * */

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() {
	armyKnights = nullptr;
	events = nullptr;
}

void KnightAdventure::loadArmyKnights(const string& file_armyknights) {
	armyKnights = new ArmyKnights(file_armyknights);
}
void KnightAdventure::loadEvents(const string& file_events) {
	events = new Events(file_events);
}
void KnightAdventure::printEvents() {
	events->print();
}
KnightAdventure::~KnightAdventure() {
	delete armyKnights;
	delete events;
}

//Main stuffs
void KnightAdventure::run() {
	bool result = armyKnights->adventure(events);
	armyKnights->printInfo();
	armyKnights->printResult(result);
}

bool ArmyKnights::adventure(Events* events) {
	fto(i, 0, events->count() - 1) {
		int eventId = events->get(i);
		//log(eventId);
		//log(lastKnight()->bag->capacity);

		BaseOpponent* opponent = BaseOpponent::create(eventId, i);

		if (eventId == 99) {
			return fightUltimecia();
		}

		if (opponent != nullptr) {
			bool win = fight(opponent);
		}

		printInfo();
		delete opponent;
	}

	return 0;//DECOY
}

bool ArmyKnights::fight(BaseOpponent* opponent) {
	int eventid = opponent->eventId;
	BaseKnight* knight = lastKnight();

	if (opponent->ignore) return 1;
	//log(eventid);
	//log("win = " + to_string(DetermineWinner(this, opponent)));
	if (DetermineWinner(this, opponent)) {
		reward(this, opponent);

		opponent->ignoreNextTime();
	}
	else {
		punish(this, opponent);
		if (knight->hp < knight->maxhp) {
			heal();
		}
		if (knight->hp <= 0) {
			pop();
			return fight(opponent);	
		}
	}

	return 1;
}

bool ArmyKnights::fightUltimecia() {
	int boss_hp = 5000;
	if (hasExcaliburSword()) {
		printingResult = 1;
		return 1;
	}
	if (!hasPaladinShield() || !hasLancelotSpear() && !hasGuinevereHair()) {
		current = 0;
		return 0;
	}
		

	while (current > 0 && boss_hp > 0) {
		BaseKnight* knight = lastKnight();

		int damage = knight->knightBaseDamage * knight->level * knight->hp;

		boss_hp -= damage;

		if (boss_hp > 0) {
			pop();
			//log(knight->knightType);
			
			//lazy hack
			if (knight->knightType == NORMAL) {
				//log(knight->knightType);
				//log(string(10, '-'));
				skippedKnight++;
				if (UltimeciaLastKnight == nullptr) {
					UltimeciaLastKnight = knight;
				}
				continue;
			}
			//

			knight->hp = 0;
		}
	}
	if (boss_hp <= 0) {
		printingResult = 1;
		return 1;
	}
	else return 0;
}
/* * * END implementation of class KnightAdventure * * */