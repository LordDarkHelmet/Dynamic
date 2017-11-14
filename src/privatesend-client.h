// Copyright (c) 2014-2017 The Dash Core developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef PRIVATESENDCLIENT_H
#define PRIVATESENDCLIENT_H

#include "dynode.h"
#include "privatesend.h"
#include "wallet/wallet.h"

class CPrivateSendClient;

static const int DENOMS_COUNT_MAX                   = 100;

static const int DEFAULT_PRIVATESEND_ROUNDS         = 2;
static const int DEFAULT_PRIVATESEND_AMOUNT         = 1000;
static const int DEFAULT_PRIVATESEND_LIQUIDITY      = 0;
static const bool DEFAULT_PRIVATESEND_MULTISESSION  = false;

// Warn user if mixing in gui or try to create backup if mixing in daemon mode
// when we have only this many keys left
static const int PRIVATESEND_KEYS_THRESHOLD_WARNING = 100;
// Stop mixing completely, it's too dangerous to continue when we have only this many keys left
static const int PRIVATESEND_KEYS_THRESHOLD_STOP    = 50;

// The main object for accessing mixing
extern CPrivateSendClient privateSendClient;

/** Used to keep track of current status of mixing pool
 */
class CPrivateSendClient : public CPrivateSendBase
{
private:
    mutable CCriticalSection cs_privatesend;

    // Keep track of the used Dynodes
    std::vector<CTxIn> vecDynodesUsed;

    std::vector<CAmount> vecDenominationsSkipped;
    std::vector<COutPoint> vecOutPointLocked;

    int nCachedLastSuccessBlock;
    int nMinBlockSpacing; //required blocks between mixes
    const CBlockIndex *pCurrentBlockIndex; // Keep track of current block index

    int nEntriesCount;
    bool fLastEntryAccepted;

    std::string strLastMessage;
    std::string strAutoDenomResult;

    CMutableTransaction txMyCollateral; // client side collateral

    /// Check for process
    void CheckPool();
    void CompletedTransaction(PoolMessage nMessageID);

    bool IsDenomSkipped(CAmount nDenomValue) {
        return std::find(vecDenominationsSkipped.begin(), vecDenominationsSkipped.end(), nDenomValue) != vecDenominationsSkipped.end();
    }

    // Make sure we have enough keys since last backup
    bool CheckAutomaticBackup();
    bool JoinExistingQueue(CAmount nBalanceNeedsAnonymized);
    bool StartNewQueue(CAmount nValueMin, CAmount nBalanceNeedsAnonymized);

    /// Create denominations
    bool CreateDenominated();
    bool CreateDenominated(const CompactTallyItem& tallyItem, bool fCreateMixingCollaterals);

    /// Split up large inputs or make fee sized inputs
    bool MakeCollateralAmounts();
    bool MakeCollateralAmounts(const CompactTallyItem& tallyItem, bool fTryDenominated);

    /// As a client, submit part of a future mixing transaction to a Dynode to start the process
    bool SubmitDenominate();
    /// step 1: prepare denominated inputs and outputs
    bool PrepareDenominate(int nMinRounds, int nMaxRounds, std::string& strErrorRet, std::vector<CTxIn>& vecTxInRet, std::vector<CTxOut>& vecTxOutRet);
    /// step 2: send denominated inputs and outputs prepared in step 1
    bool SendDenominate(const std::vector<CTxIn>& vecTxIn, const std::vector<CTxOut>& vecTxOut);

    /// Get Dynodes updates about the progress of mixing
    bool CheckPoolStateUpdate(PoolState nStateNew, int nEntriesCountNew, PoolStatusUpdate nStatusUpdate, PoolMessage nMessageID, int nSessionIDNew=0);
    // Set the 'state' value, with some logging and capturing when the state changed
    void SetState(PoolState nStateNew);

    /// As a client, check and sign the final transaction
    bool SignFinalTransaction(const CTransaction& finalTransactionNew, CNode* pnode);

    void RelayIn(const CPrivateSendEntry& entry);

    void SetNull();

public:
    int nPrivateSendRounds;
    int nPrivateSendAmount;
    int nLiquidityProvider;
    bool fEnablePrivateSend;
    bool fPrivateSendMultiSession;

    dynode_info_t infoMixingDynode;
    int nCachedNumBlocks; //used for the overview screen
    bool fCreateAutoBackups; //builtin support for automatic backups

    CPrivateSendClient() :
        nCachedLastSuccessBlock(0),
        nMinBlockSpacing(0),
        txMyCollateral(CMutableTransaction()),
        nPrivateSendRounds(DEFAULT_PRIVATESEND_ROUNDS),
        nPrivateSendAmount(DEFAULT_PRIVATESEND_AMOUNT),
        nLiquidityProvider(DEFAULT_PRIVATESEND_LIQUIDITY),
        fEnablePrivateSend(false),
        fPrivateSendMultiSession(DEFAULT_PRIVATESEND_MULTISESSION),
        nCachedNumBlocks(std::numeric_limits<int>::max()),
        fCreateAutoBackups(true) { SetNull(); }

    void ProcessMessage(CNode* pfrom, std::string& strCommand, CDataStream& vRecv);

    void ClearSkippedDenominations() { vecDenominationsSkipped.clear(); }

    void SetMinBlockSpacing(int nMinBlockSpacingIn) { nMinBlockSpacing = nMinBlockSpacingIn; }

    void ResetPool();

    void UnlockCoins();

    std::string GetStatus();

    /// Passively run mixing in the background according to the configuration in settings
    bool DoAutomaticDenominating(bool fDryRun=false);

    void CheckTimeout();

    /// Process a new block
    void NewBlock();

    void UpdatedBlockTip(const CBlockIndex *pindex);
};

void ThreadCheckPrivateSendClient();

#endif