// Copyright (c) 2016-2019 Duality Blockchain Solutions Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "bdaplinkdetaildialog.h"
#include "ui_bdaplinkdetaildialog.h"

#include "guiutil.h"
#include "rpcregister.h"
#include "rpcserver.h"
#include "rpcclient.h"
#include "util.h"

#include <stdio.h>

#include <boost/algorithm/string.hpp>



BdapLinkDetailDialog::BdapLinkDetailDialog(QWidget *parent, LinkActions actionType, const std::string& requestor, const std::string& recipient, const UniValue& resultinput, bool displayInfo) : QDialog(parent),
                                                        ui(new Ui::BdapLinkDetailDialog)
{
    ui->setupUi(this);

    ui->labelinfoHeader->setVisible(displayInfo);
    ui->labelinfoHeader->setText(QObject::tr(LINK_TRANSACTION_MESSAGE.c_str()));

    connect(ui->pushButtonOK, SIGNAL(clicked()), this, SLOT(goClose()));

    populateValues(actionType,requestor,recipient,resultinput);

}

BdapLinkDetailDialog::~BdapLinkDetailDialog()
{
    delete ui;
}


void BdapLinkDetailDialog::populateValues(LinkActions accountType, const std::string& requestor, const std::string& recipient, const UniValue& resultinput)
{
    std::vector<std::string> results;
    std::string keyName = "";
    std::string getRequestor = "";
    std::string getRecipient = "";
    std::string linkPublicKey = "N/A";
    std::string linkRequestorPublicKey = "N/A";
    std::string linkRecipientPublicKey = "N/A";
    std::string requstorLinkAddress = "N/A";
    std::string recipientLinkAddress = "N/A";
    std::string signatureProof = "N/A";
    std::string linkMessage = "N/A";
    std::string txId = "";
    std::string expirationDate = "";
    std::string expired = "";
    std::string timeValue = "";
    std::string outputmessage = "";
    std::string sharedRequestPubKey = "N/A";
    std::string sharedAcceptPubKey = "N/A";
    std::string acceptTXID = "N/A";
    std::string acceptTime = "N/A";
    std::string acceptExpirationDate = "N/A";
    std::string acceptexpired = "N/A";

    UniValue result = UniValue(UniValue::VOBJ);
 
    if (resultinput.size() == 0) {
        return; //do not use for now
    } //if resultinput.size() = 0
    else {
        result = resultinput;
    }



    for (size_t i {0} ; i < result.size() ; ++i) {
        keyName = "";
        keyName = result.getKeys()[i];
        if (keyName == "requestor_fqdn") getRequestor = result.getValues()[i].get_str();
        if (keyName == "recipient_fqdn") getRecipient = result.getValues()[i].get_str();
        if (keyName == "requestor_link_pubkey") linkRequestorPublicKey = result.getValues()[i].get_str();
        if (keyName == "recipient_link_pubkey") linkRecipientPublicKey = result.getValues()[i].get_str();
        if (keyName == "requestor_link_address") requstorLinkAddress = result.getValues()[i].get_str();
        if (keyName == "recipient_link_address") recipientLinkAddress = result.getValues()[i].get_str();
        if (keyName == "signature_proof") signatureProof = result.getValues()[i].get_str();
        if (keyName == "link_message") linkMessage = result.getValues()[i].get_str();

        if (keyName == "shared_request_pubkey") sharedRequestPubKey = result.getValues()[i].get_str();
        if (keyName == "shared_accept_pubkey") sharedAcceptPubKey = result.getValues()[i].get_str();



        if (keyName == "txid") txId = result.getValues()[i].get_str();
        if (keyName == "accept_txid") acceptTXID = result.getValues()[i].get_str();


        if (keyName == "expires_on") expirationDate = DateTimeStrFormat("%Y-%m-%d", result.getValues()[i].get_int64());
        if (keyName == "accept_expires_on") acceptExpirationDate = DateTimeStrFormat("%Y-%m-%d", result.getValues()[i].get_int64());

        if (keyName == "expired") expired = ((result.getValues()[i].get_bool())?"true":"false");
        if (keyName == "accept_expired") acceptexpired = ((result.getValues()[i].get_bool())?"true":"false");

        if (keyName == "time") timeValue = DateTimeStrFormat("%Y-%m-%d %H:%M", result.getValues()[i].get_int64());
        if (keyName == "accept_time") acceptTime = DateTimeStrFormat("%Y-%m-%d %H:%M", result.getValues()[i].get_int64());

    } //for i

    ui->lineEditRequestor->setText(QString::fromStdString(getRequestor));
    ui->lineEditRecipient->setText(QString::fromStdString(getRecipient));

    ui->lineEditRequestorPublicKey->setText(QString::fromStdString(linkRequestorPublicKey));
    ui->lineEditRecipientPublicKey->setText(QString::fromStdString(linkRecipientPublicKey));

    ui->lineEditRequestorLinkAddress->setText(QString::fromStdString(requstorLinkAddress));
    ui->lineEditRecipientLinkAddress->setText(QString::fromStdString(recipientLinkAddress));
    ui->lineEditSignatureProof->setText(QString::fromStdString(signatureProof));
    ui->lineEditLinkMessage->setText(QString::fromStdString(linkMessage));

    ui->lineEditTXID->setText(QString::fromStdString(txId));
    ui->lineEditAcceptTXID->setText(QString::fromStdString(acceptTXID));


    ui->lineEditExpirationDate->setText(QString::fromStdString(expirationDate));
    ui->lineEditAcceptExpirationDate->setText(QString::fromStdString(acceptExpirationDate));


    ui->lineEditExpired->setText(QString::fromStdString(expired));
    ui->lineEditAcceptExpired->setText(QString::fromStdString(acceptexpired));

    ui->lineEditTime->setText(QString::fromStdString(timeValue));
    ui->lineEditAcceptTime->setText(QString::fromStdString(acceptTime));

    ui->lineEditSharedRequestPubKey->setText(QString::fromStdString(sharedRequestPubKey));
    ui->lineEditSharedAcceptPubKey->setText(QString::fromStdString(sharedAcceptPubKey));




} //populateValues


void BdapLinkDetailDialog::goClose()
{
    QDialog::accept(); //accepted
} //goClose




















