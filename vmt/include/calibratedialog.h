#ifndef CALIBRATEDIALOG_H
#define CALIBRATEDIALOG_H

#include "vmtmodel.h"

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
#include <QtGui>

namespace gui {

//! [0]
class CalibrateDialog : public QWidget
{
    Q_OBJECT

public:
    CalibrateDialog(VmtModel* modelobj);


private slots:
    void acceptPressed();
    void rejectPressed();
    void enabledChange(bool state);
    void reCalibration();

    void x0IniValueChanged(double newval);
    void x1IniValueChanged(double newval);
    void x2IniValueChanged(double newval);
    void x3IniValueChanged(double newval);
    void y0IniValueChanged(double newval);
    void y1IniValueChanged(double newval);
    void y2IniValueChanged(double newval);
    void y3IniValueChanged(double newval);

    void x0FinValueChanged(double newval);
    void x1FinValueChanged(double newval);
    void x2FinValueChanged(double newval);
    void x3FinValueChanged(double newval);
    void y0FinValueChanged(double newval);
    void y1FinValueChanged(double newval);
    void y2FinValueChanged(double newval);
    void y3FinValueChanged(double newval);


private:
    void createFormGroupBox();
    void loadData();
    void undoChanges();

    enum { NumGridRows = 4, NumButtons = 3 };

    QGroupBox *formGroupBox;
    QLabel *labels[NumGridRows];
    QLineEdit *lineEdits[NumGridRows];
    QPushButton *buttons[NumButtons];
    QDialogButtonBox *buttonBox;

    QDoubleSpinBox *x0IniSpinBox;
    QDoubleSpinBox *y0IniSpinBox;

    QDoubleSpinBox *x1IniSpinBox;
    QDoubleSpinBox *y1IniSpinBox;

    QDoubleSpinBox *x2IniSpinBox;
    QDoubleSpinBox *y2IniSpinBox;

    QDoubleSpinBox *x3IniSpinBox;
    QDoubleSpinBox *y3IniSpinBox;

    QDoubleSpinBox *x0FinSpinBox;
    QDoubleSpinBox *y0FinSpinBox;

    QDoubleSpinBox *x1FinSpinBox;
    QDoubleSpinBox *y1FinSpinBox;

    QDoubleSpinBox *x2FinSpinBox;
    QDoubleSpinBox *y2FinSpinBox;

    QDoubleSpinBox *x3FinSpinBox;
    QDoubleSpinBox *y3FinSpinBox;

    QPushButton *recalibrateBox;

    QCheckBox *layerEnabledBox;
    QLineEdit *idLineEdit;

    QGridLayout *layoutbut;
    QVBoxLayout *mainLayout;

    VmtModel *model;



};
//! [0]

}

#endif
