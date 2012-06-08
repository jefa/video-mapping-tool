#include <QtGui>

#include "midieffecteditdialog.h"
#include "uiutils.h"
#include <limits>


using namespace gui;

//! [0]
midiEffecteditdialog::midiEffecteditdialog(VmtModel *vmtModel)
{
    this->vmtModel = vmtModel;

    idEffectEdit = new QComboBox();

    idMidiEdit = new QDoubleSpinBox();
    idMidiEdit->setDecimals(0);
    idMidiEdit->setMaximum(9999999999);

    valueMidiEdit = new QDoubleSpinBox();
    valueMidiEdit->setDecimals(0);
    valueMidiEdit->setMaximum(9999999999);
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
void midiEffecteditdialog::createFormGroupBox()
{
    formGroupBox = new QGroupBox(tr("Add"));
    QFormLayout *layout = new QFormLayout;
    layout->addRow(new QLabel(tr("Id/Efect:")), idEffectEdit);
    layout->addRow(new QLabel(tr("Id MIDI:")), idMidiEdit);
    layout->addRow(new QLabel(tr("Value MIDI:")), valueMidiEdit);

    formGroupBox->setLayout(layout);
}
//! [12]

void midiEffecteditdialog::loadData(){

    map<string, Effect*>::iterator effectsIt;
    map<string, Effect*> effectsMap = this->vmtModel->getEffects();
    for(effectsIt = effectsMap.begin(); effectsIt != effectsMap.end(); effectsIt++) {
        idEffectEdit->addItem(QString(effectsIt->second->getId().c_str()),QString(effectsIt->second->getId().c_str()));
    }

}


void midiEffecteditdialog::acceptPressed(){
    ofxMidiEventArgs * MidiMsg = new ofxMidiEventArgs();
    MidiMsg->channel = 0;
    MidiMsg->id = idMidiEdit->text().toInt();
    MidiMsg->msgType = 0;
    MidiMsg->port = 0 ;
    MidiMsg->timestamp = 0;
    MidiMsg->value = valueMidiEdit->text().toInt();

    this->vmtModel->addMidiEvent(MidiMsg,(idEffectEdit->currentText()).toStdString());
    emit dataChanged();
    hide();
}

void midiEffecteditdialog::rejectPressed(){
    undoChanges();
    hide();
}

void midiEffecteditdialog::undoChanges(){
}

void midiEffecteditdialog::newMidiMessage(ofxMidiEventArgs& eventArgs){
    cout<<"midiEffecteditdialog::newMidiMessage"<<eventArgs.id <<" "<< eventArgs.value  << '\n';
    idMidiEdit->setValue(eventArgs.id);
    valueMidiEdit->setValue(eventArgs.value);

    cout<<"midiEffecteditdialog::datos"<<idMidiEdit->text().toInt()<<" "<< valueMidiEdit->text().toInt()  << '\n';
}
 void midiEffecteditdialog::Init(ofxMidiEventArgs* Msg, string IdEffect){

     idEffectEdit->setCurrentIndex(idEffectEdit->findText(QString(IdEffect.c_str()),0) );
     idMidiEdit->setValue(Msg->id);
     valueMidiEdit->setValue(Msg->value);
 }
