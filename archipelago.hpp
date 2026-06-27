#ifndef ARCHIPELAGO_HPP
#define ARCHIPELAGO_HPP
#include "hyper.h"
#include <apclient.hpp>
using namespace hr;
using namespace nlohmann;

namespace ap{

enum class progressCheck {
  notingame=-1,
  locked=0,
  unlocked=1,
  orbunlocked=2,
  orbunlockedglobal=3,
  completed=4,
  orbunlocked_extra=5,
  orbunlockedglobal_extra=6,
  completed_extra=7
};

#define HYPERROGUE_BASE_ID 0XCBA000
eItem itemByID[0X60]={eItem::itNone};
eItem orbByID[0X60]={eItem::itNone};


// Check array setup
progressCheck landChecksReceived[eItem::ittypes]={progressCheck::locked};
int orbsReceived[eItem::ittypes] = {0};
/* Locations are numbered like their offsets in IDs +1, matching progressCheck:
    1: Unlock
    2: 10 Treasures
    3: 25 Treasures
    4: 50 Treasures
    5: 10 Treasures Extra
    6: 25 Treasures Extra
    7: 50 Treasures Extra
*/
bool landProgressChecksSent[eItem::ittypes][8] = {false};
bool victoryAchieved = false;
bool victoryPackageSent = false;
double deathtime = -1;
bool deathLinkPending = false;

// Utility functions
int getNumberOfProgressedLands(progressCheck prog);
bool isTreasure(eItem item);
bool isOrb(eItem item);
int getVirtualTreasureCount(progressCheck prog, eItem i);
eItem getItemByName(std::string name);
int getLocationID(eItem treas, progressCheck prog);

// Initialization
namespace init {
  bool initialRestartDone = false;
  void initRando();
  eLand getFirstLand();
  void initItemByID();
  void initOrbByID();
}

// Check management
namespace checks{
  progressCheck sendingProgress(eItem it);
  void hintLand(eLand land);
  bool checkWinCon();
  int alreadyHandledChecks = -1;
  void resetInventory();
  void receiveCheck(APClient::NetworkItem item);
  void collectCheck(eItem treasure, progressCheck progress);
  void updateChecks();
  void doFullSync();
}

void sendDeathLink(std::string msg);
namespace settings{
  enum goalCondition{
    hyperstones10=0,
    hyperstones50=1,
    orbofyendor=2
  };
  goalCondition goal=goalCondition::orbofyendor;
  bool easierHyperstones = true;
  bool deathLink = false;
  int requiredTreasures = 25;
  bool hintOrb = false;
  void readSettings(json settings);
  int startLandID=-1;
  bool extra_location_10 = false;
  bool extra_location_25 = false;
  bool extra_location_50 = false;
}

namespace saves{
  void writeApState(std::string fileName);
  void readApState(std::string fileName);
}
}
#endif