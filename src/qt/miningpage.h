// Copyright (c) 2016-2019 Duality Blockchain Solutions Developers
// Copyright (c) 2014-2019 The Dash Core Developers
// Copyright (c) 2009-2019 The Bitcoin Developers
// Copyright (c) 2009-2019 Satoshi Nakamoto
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef MININGPAGE_H
#define MININGPAGE_H

#include "platformstyle.h"

#include "walletmodel.h"

#include <QWidget>
#include <memory>

namespace Ui
{
class MiningPage;
}

class MiningPage : public QWidget
{
    Q_OBJECT

public:
    explicit MiningPage(const PlatformStyle* platformStyle, QWidget* parent = 0);
    ~MiningPage();

    void setModel(WalletModel* model);

private:
    Ui::MiningPage* ui;
    WalletModel* model;
    std::unique_ptr<WalletModel::UnlockContext> unlockContext;
    bool hasMiningprivkey;
    bool fGPUMinerOn;
    bool fCPUMinerOn;
    void timerEvent(QTimerEvent* event);
    void updateUI();
    void StartMiner(bool fGPU);
    void StopMiner(bool fGPU);
    void showHashMeterControls(bool show, bool fGPU);
    void updatePushSwitch(bool fGPU);

private Q_SLOTS:

    void startMining();
    void switchMining(bool fGPU);
    void showHashRate(int i, bool fGPU);
    void changeSampleTime(int i, bool fGPU);

    void changeNumberOfCPUThreads(int i);
    void switchCPUMining();
    void showCPUHashRate(int i);
    void changeCPUSampleTime(int i);
    void clearCPUHashRateData();


#ifdef ENABLE_GPU
    void changeNumberOfGPUThreads(int i);
    void switchGPUMining();
    void showGPUHashRate(int i);
    void changeGPUSampleTime(int i);
    void clearGPUHashRateData();
#endif
};

#endif // MININGPAGE_H
