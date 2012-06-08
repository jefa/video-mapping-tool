#ifndef MIDIEFFECTEDITDIALOG_H
#define MIDIEFFECTEDITDIALOG_H

#include <vmtmodel.h>
#include "..\addons\ofxMidiIn\events\ofxMidiEvents.h"

#include <QDoubleSpinBox>
#include <QAction>
#include <QDialogButtonBox>
#include <QGroupBox>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QCheckBox>
#include <QTextEdit>
#include <QTimeEdit>
#include <string>
#include <QModelIndex>

using namespace std;

namespace gui {

//! [0]
class midiEffecteditdialog : public QWidget, ofxMidiListener
{
    Q_OBJECT

public:
    midiEffecteditdialog(VmtModel *vmtModel);
    void newMidiMessage(ofxMidiEventArgs& eventArgs);
    void Init(ofxMidiEventArgs* Msg, string IdEffect);

private slots:
    void acceptPressed();
    void rejectPressed();


Q_SIGNALS:
    void dataChanged();

private:
    void createFormGroupBox();
    void loadData();
    void undoChanges();

    enum { NumGridRows = 3, NumButtons = 2 };

    QGroupBox *formGroupBox;
    QLabel *labels[NumGridRows];
    QLineEdit *lineEdits[NumGridRows];
    QPushButton *buttons[NumButtons];
    QDialogButtonBox *buttonBox;

    VmtModel *vmtModel;

    QComboBox *idEffectEdit;
    QDoubleSpinBox *idMidiEdit;
    QDoubleSpinBox *valueMidiEdit;

    ofxMidiEventArgs * MidiMsg;

};
//! [0]

}

#endif
