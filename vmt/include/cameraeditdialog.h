#ifndef CAMERAEDITORDIALOG_H
#define CAMERAEDITORDIALOG_H

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
#include <QDoubleSpinBox>
#include <QTextEdit>
#include <QCheckBox>

#include "ofxCamera.h"

namespace gui {

//! [0]
class CameraEditorDialog : public QWidget
{
    Q_OBJECT

public:
    CameraEditorDialog(VmtModel *modelobj, string id);

private slots:
    void acceptPressed();
    void rejectPressed();
    void xValueChanged(double);
    void yValueChanged(double);
    void zValueChanged(double);

    void xValueChangedEye(double);
    void yValueChangedEye(double);
    void zValueChangedEye(double);

    void xValueChangedUp(double);
    void yValueChangedUp(double);
    void zValueChangedUp(double);

    void fieldOfViewValueChanged(double);
    void aspectRatioValueChanged(double);
    void zNearValueChanged(double);
    void zFarValueChanged(double);

    void proyectorChange(bool state);

private:
    void createFormGroupBox();
    void loadData();
    void undoChanges();

    enum { NumGridRows = 3, NumButtons = 15 };

    QGroupBox *formGroupBox;
    QLabel *labels[NumGridRows];
    QLineEdit *lineEdits[NumGridRows];
    QPushButton *buttons[NumButtons];
    QDialogButtonBox *buttonBox;

    QDoubleSpinBox *xCoordSpinBox;
    QDoubleSpinBox *yCoordSpinBox;
    QDoubleSpinBox *zCoordSpinBox;

    QDoubleSpinBox *xCoordSpinEyeBox;
    QDoubleSpinBox *yCoordSpinEyeBox;
    QDoubleSpinBox *zCoordSpinEyeBox;

    QDoubleSpinBox *xCoordSpinUpBox;
    QDoubleSpinBox *yCoordSpinUpBox;
    QDoubleSpinBox *zCoordSpinUpBox;

    QDoubleSpinBox *fieldOfView;
    QDoubleSpinBox *aspectRatio;
    QDoubleSpinBox *zNear;
    QDoubleSpinBox *zFar;

    QCheckBox *projector;

    QLineEdit *idLineEdit;

    VmtModel *model;
    string cameraId;

    float previousX, previousY, previousZ,previousEyeX, previousEyeY, previousEyeZ,previousUpX, previousUpY, previousUpZ;
	float previousfieldOfView, previousaspectRatio, previouszNear, previouszFar;
	bool previousprojector;

};
//! [0]

}

#endif
