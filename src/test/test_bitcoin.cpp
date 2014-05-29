#define BOOST_TEST_MODULE Bitcoin Test Suite
#include <boost/test/unit_test.hpp>

#include "db.h"
#include "main.h"
#include "wallet.h"
#include "checkpoints.h"

CWallet* pwalletMain;
CClientUIInterface uiInterface;

extern bool fPrintToConsole;
extern void noui_connect();

unsigned int nMinerSleep;
bool fEnforceCanonical;
unsigned int nNodeLifespan;
bool fConfChange;
bool fUseFastIndex;
unsigned int nDerivationMethodIndex;
enum Checkpoints::CPMode CheckpointsMode;

struct TestingSetup {
    TestingSetup() {
        fPrintToDebugger = true; // don't want to write to debug.log file
	fPrintToConsole = true; // Get make to output all of the information
        noui_connect();
        bitdb.MakeMock();
        LoadBlockIndex(true);
        bool fFirstRun;
        pwalletMain = new CWallet("wallet.dat");
        pwalletMain->LoadWallet(fFirstRun);
        RegisterWallet(pwalletMain);
	nMinerSleep = 500;
	fEnforceCanonical = true;
	nNodeLifespan = 7;
	fConfChange = false;
	fUseFastIndex = true;
        nDerivationMethodIndex = 0;
        CheckpointsMode = Checkpoints::PERMISSIVE;

		// We need to make a key to test blocks
        CPubKey newDefaultKey;
        assert(pwalletMain->GetKeyFromPool(newDefaultKey, false));
        pwalletMain->SetDefaultKey(newDefaultKey);
    }
    ~TestingSetup()
    {
        delete pwalletMain;
        pwalletMain = NULL;
        bitdb.Flush(true);
    }
};

BOOST_GLOBAL_FIXTURE(TestingSetup);

void Shutdown(void* parg)
{
  exit(0);
}

void StartShutdown()
{
  exit(0);
}

