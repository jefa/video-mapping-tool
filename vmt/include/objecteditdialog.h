#ifndef OBJECTEDITORDIALOG_H
#define OBJECTEDITORDIALOG_H

#include "vmtmodel.h"
#include "Object3D.h"

namespace gui {

//! [0]
class ObjectEditorDialog : public QWidget
{
    Q_OBJECT

public:
    ObjectEditorDialog(VmtModel *modelobj, string idobj);

private slots:
    void acceptPressed();
    void rejectPressed();
    void xValueChanged(double);
    void yValueChanged(double);
    void zValueChanged(double);

private:
    void createFormGroupBox();
    void loadData();
    void undoChanges();

    enum { NumGridRows = 3, NumButtons = 4 };

    QGroupBox *formGroupBox;
    QLabel *labels[NumGridRows];
    QLineEdit *lineEdits[NumGridRows];
    QPushButton *buttons[NumButtons];
    QDialogButtonBox *buttonBox;

    QDoubleSpinBox *xCoordSpinBox;
    QDoubleSpinBox *yCoordSpinBox;
    QDoubleSpinBox *zCoordSpinBox;
    QLineEdit *idLineEdit;

    string idobj;
    VmtModel *model;
    Object3D *object3d;
    string previousId;
    float previousX, previousY, previousZ;

};
//! [0]

}

#endif
