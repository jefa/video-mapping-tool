#include <QtGui>

#include "evteffecteditdialog.h"
#include "uiutils.h"
#include <limits>


using namespace gui;

//! [0]
evtEffecteditdialog::evtEffecteditdialog(VmtModel *vmtModel)
{
    this->vmtModel = vmtModel;
    TimeBox = new QDoubleSpinBox();
    TimeBox->setMouseTracking(true);
    TimeBox->setMaximum(numeric_limits<double>::max());
    TimeBox->setMinimum((numeric_limits<double>::max())*(0));
    TimeBox->setSingleStep(1);
    TimeBox->setMaximumWidth(70);

    idLineEdit = new QComboBox();



    loadData();

    createFormGroupBox();
//! [0]

//! [1]
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(acceptPressed()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(rejectPressed()));



//! [1]

//! [2]
    QVBoxLayout *mainLayout = new QVBoxLayout;
//! [2] //! [3]
    //mainLayout->setMenuBar(menuBar);
//! [3] //! [4]
    mainLayout->addWidget(formGroupBox);
    mainLayout->addWidget(buttonBox);

//! [4] //! [5]
    setLayout(mainLayout);

    setWindowTitle(tr("Add"));

}
//! [5]

//! [12]
void evtEffecteditdialog::createFormGroupBox()
{
    formGroupBox = new QGroupBox(tr("Add"));
    QFormLayout *layout = new QFormLayout;
    layout->addRow(new QLabel(tr("Id/Efect:")), idLineEdit);
    layout->addRow(new QLabel(tr("Time:")), TimeBox);

    formGroupBox->setLayout(layout);
}
//! [12]

void evtEffecteditdialog::loadData(){
    map<string, Effect*>::iterator effectsIt;
    map<string, Effect*> effectsMap = this->vmtModel->getEffects();
    for(effectsIt = effectsMap.begin(); effectsIt != effectsMap.end(); effectsIt++) {
        idLineEdit->addItem(QString(effectsIt->second->getId().c_str()),QString(effectsIt->second->getId().c_str()));
    }

}


void evtEffecteditdialog::acceptPressed(){
    float timeShedule;
    timeShedule = TimeBox->value();
    this->vmtModel->scheduleEvent(timeShedule, (idLineEdit->currentText()).toStdString());

    emit dataChanged();

    hide();
}

void evtEffecteditdialog::rejectPressed(){
    undoChanges();
    hide();
}

void evtEffecteditdialog::undoChanges(){
}
void evtEffecteditdialog::Init(float time, string effectId){

    TimeBox->setValue(time);
    idLineEdit->setCurrentIndex(idLineEdit->findText(QString(effectId.c_str()),0) );
}
