#ifndef EVTEFFECTEDITDIALOG_H
#define EVTEFFECTEDITDIALOG_H

#include <vmtmodel.h>

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
class evtEffecteditdialog : public QWidget
{
    Q_OBJECT

public:
    evtEffecteditdialog(VmtModel *vmtModel);
    void Init(float time, string effectId);

private slots:
    void acceptPressed();
    void rejectPressed();

Q_SIGNALS:
    void dataChanged();

private:
    void createFormGroupBox();
    void loadData();
    void undoChanges();


    enum { NumGridRows = 2, NumButtons = 2 };

    QGroupBox *formGroupBox;
    QLabel *labels[NumGridRows];
    QLineEdit *lineEdits[NumGridRows];
    QPushButton *buttons[NumButtons];
    QDialogButtonBox *buttonBox;

    VmtModel *vmtModel;
    QDoubleSpinBox *TimeBox;
    QComboBox *idLineEdit;


};
//! [0]

}

#endif
