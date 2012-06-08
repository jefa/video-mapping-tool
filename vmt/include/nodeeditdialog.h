#ifndef NODEEDITORDIALOG_H
#define NODEEDITORDIALOG_H


#include "vmtmodel.h"

#include <QDialog>
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

namespace gui {

//! [0]
class NodeEditorDialog : public QWidget
{
    Q_OBJECT

public:
    NodeEditorDialog(VmtModel* modelobj, string idNode);

private slots:
    void acceptPressed();
    void rejectPressed();
    void isActive(bool state);

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

    QCheckBox *isActiveBox;
    QLineEdit *idLineEdit;
    QLineEdit *addressEdit;
    QLineEdit *cameraIdEdit;
    QLineEdit *portEdit;

    string previousAddress, previousCameraId;
    int previousPort;
    bool previousIsActive;

    VmtModel *model;
    string idNode;



};
//! [0]

}

#endif
