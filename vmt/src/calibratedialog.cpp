#include <QtGui>

#include "calibratedialog.h"
#include "uiutils.h"
#include <limits>

using namespace gui;

//! [0]
CalibrateDialog::CalibrateDialog(VmtModel *modelobj)
{
    this->model = modelobj;
    layerEnabledBox = new  QCheckBox();
    idLineEdit = new QLineEdit();

    recalibrateBox = new QPushButton();
    recalibrateBox->setObjectName(QString::fromUtf8("recalibrateBox"));
    recalibrateBox->setEnabled(true);

    //Coordiantes panel
    QLabel *x0Label1 = new QLabel(tr("X0:"));
    QLabel *y0Label1 = new QLabel(tr("Y0:"));

    QLabel *x1Label1 = new QLabel(tr("X1:"));
    QLabel *y1Label1 = new QLabel(tr("Y1:"));

    QLabel *x2Label1 = new QLabel(tr("X2:"));
    QLabel *y2Label1 = new QLabel(tr("Y2:"));

    QLabel *x3Label1 = new QLabel(tr("X3:"));
    QLabel *y3Label1 = new QLabel(tr("Y3:"));

    QLabel *x0Label2 = new QLabel(tr("X0:"));
    QLabel *y0Label2 = new QLabel(tr("Y0:"));

    QLabel *x1Label2 = new QLabel(tr("X1:"));
    QLabel *y1Label2 = new QLabel(tr("Y1:"));

    QLabel *x2Label2 = new QLabel(tr("X2:"));
    QLabel *y2Label2 = new QLabel(tr("Y2:"));

    QLabel *x3Label2 = new QLabel(tr("X3:"));
    QLabel *y3Label2 = new QLabel(tr("Y3:"));

    QLabel *posIniLabel = new QLabel(tr("Ini:"));
    x0IniSpinBox = UiUtils::createCoordinateSpinBox();
    y0IniSpinBox = UiUtils::createCoordinateSpinBox();
    x1IniSpinBox = UiUtils::createCoordinateSpinBox();
    y1IniSpinBox = UiUtils::createCoordinateSpinBox();
    x2IniSpinBox = UiUtils::createCoordinateSpinBox();
    y2IniSpinBox = UiUtils::createCoordinateSpinBox();
    x3IniSpinBox = UiUtils::createCoordinateSpinBox();
    y3IniSpinBox = UiUtils::createCoordinateSpinBox();


    QLabel *posFinLabel = new QLabel(tr("Fin:"));
    x0FinSpinBox = UiUtils::createCoordinateSpinBox();
    y0FinSpinBox = UiUtils::createCoordinateSpinBox();
    x1FinSpinBox = UiUtils::createCoordinateSpinBox();
    y1FinSpinBox = UiUtils::createCoordinateSpinBox();
    x2FinSpinBox = UiUtils::createCoordinateSpinBox();
    y2FinSpinBox = UiUtils::createCoordinateSpinBox();
    x3FinSpinBox = UiUtils::createCoordinateSpinBox();
    y3FinSpinBox = UiUtils::createCoordinateSpinBox();

    QGroupBox *coordinatesGroup = new QGroupBox(tr("Points:"));
    QGridLayout *coordinatesLayout = new QGridLayout;
    coordinatesLayout->addWidget(posIniLabel, 0, 0);
    coordinatesLayout->addWidget(x0Label1, 0, 1);
    coordinatesLayout->addWidget(x0IniSpinBox, 0, 2);
    coordinatesLayout->addWidget(y0Label1, 0, 3);
    coordinatesLayout->addWidget(y0IniSpinBox, 0, 4);
    coordinatesLayout->addWidget(x1Label1, 0, 5);
    coordinatesLayout->addWidget(x1IniSpinBox, 0, 6);
    coordinatesLayout->addWidget(y1Label1, 0, 7);
    coordinatesLayout->addWidget(y1IniSpinBox, 0, 8);
    coordinatesLayout->addWidget(x2Label1, 0, 9);
    coordinatesLayout->addWidget(x2IniSpinBox, 0, 10);
    coordinatesLayout->addWidget(y2Label1, 0, 11);
    coordinatesLayout->addWidget(y2IniSpinBox, 0, 12);
    coordinatesLayout->addWidget(x3Label1, 0, 13);
    coordinatesLayout->addWidget(x3IniSpinBox, 0, 14);
    coordinatesLayout->addWidget(y3Label1, 0, 15);
    coordinatesLayout->addWidget(y3IniSpinBox, 0, 16);


    coordinatesLayout->addWidget(posFinLabel, 1, 0);
    coordinatesLayout->addWidget(x0Label2, 1, 1);
    coordinatesLayout->addWidget(x0FinSpinBox, 1, 2);
    coordinatesLayout->addWidget(y0Label2, 1, 3);
    coordinatesLayout->addWidget(y0FinSpinBox, 1, 4);
    coordinatesLayout->addWidget(x1Label2, 1, 5);
    coordinatesLayout->addWidget(x1FinSpinBox, 1, 6);
    coordinatesLayout->addWidget(y1Label2, 1, 7);
    coordinatesLayout->addWidget(y1FinSpinBox, 1, 8);
    coordinatesLayout->addWidget(x2Label2, 1, 9);
    coordinatesLayout->addWidget(x2FinSpinBox, 1, 10);
    coordinatesLayout->addWidget(y2Label2, 1, 11);
    coordinatesLayout->addWidget(y2FinSpinBox, 1, 12);
    coordinatesLayout->addWidget(x3Label2, 1, 13);
    coordinatesLayout->addWidget(x3FinSpinBox, 1, 14);
    coordinatesLayout->addWidget(y3Label2, 1, 15);
    coordinatesLayout->addWidget(y3FinSpinBox, 1, 16);

    coordinatesGroup->setLayout(coordinatesLayout);

    loadData();

    createFormGroupBox();

//! [0]

//! [1]
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(acceptPressed()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(rejectPressed()));
    connect(recalibrateBox, SIGNAL(clicked()), this, SLOT(reCalibration()));
    connect(layerEnabledBox, SIGNAL(clicked(bool)), this, SLOT(enabledChange(bool)));

    connect(x0IniSpinBox, SIGNAL(valueChanged(double)), this, SLOT(x0IniValueChanged(double)));
    connect(x1IniSpinBox, SIGNAL(valueChanged(double)), this, SLOT(x1IniValueChanged(double)));
    connect(x2IniSpinBox, SIGNAL(valueChanged(double)), this, SLOT(x2IniValueChanged(double)));
    connect(x3IniSpinBox, SIGNAL(valueChanged(double)), this, SLOT(x3IniValueChanged(double)));
    connect(y0IniSpinBox, SIGNAL(valueChanged(double)), this, SLOT(y0IniValueChanged(double)));
    connect(y1IniSpinBox, SIGNAL(valueChanged(double)), this, SLOT(y1IniValueChanged(double)));
    connect(y2IniSpinBox, SIGNAL(valueChanged(double)), this, SLOT(y2IniValueChanged(double)));
    connect(y3IniSpinBox, SIGNAL(valueChanged(double)), this, SLOT(y3IniValueChanged(double)));

    connect(x0FinSpinBox, SIGNAL(valueChanged(double)), this, SLOT(x0FinValueChanged(double)));
    connect(x1FinSpinBox, SIGNAL(valueChanged(double)), this, SLOT(x1FinValueChanged(double)));
    connect(x2FinSpinBox, SIGNAL(valueChanged(double)), this, SLOT(x2FinValueChanged(double)));
    connect(x3FinSpinBox, SIGNAL(valueChanged(double)), this, SLOT(x3FinValueChanged(double)));
    connect(y0FinSpinBox, SIGNAL(valueChanged(double)), this, SLOT(y0FinValueChanged(double)));
    connect(y1FinSpinBox, SIGNAL(valueChanged(double)), this, SLOT(y1FinValueChanged(double)));
    connect(y2FinSpinBox, SIGNAL(valueChanged(double)), this, SLOT(y2FinValueChanged(double)));
    connect(y3FinSpinBox, SIGNAL(valueChanged(double)), this, SLOT(y3FinValueChanged(double)));

//! [1]

//! [2]
    QVBoxLayout *mainLayout = new QVBoxLayout;
//! [2] //! [3]
    //mainLayout->setMenuBar(menuBar);
//! [3] //! [4]
    layoutbut = new QGridLayout;
    layoutbut->setColumnStretch(1, 1);
    layoutbut->setColumnMinimumWidth(0,200);
    layoutbut->setColumnMinimumWidth(1, 200);
    layoutbut->addWidget(recalibrateBox, 0, 0);

    //mainLayout->addWidget(formGroupBox);
    mainLayout->addWidget(coordinatesGroup);
    mainLayout->addLayout(layoutbut);
    mainLayout->addWidget(buttonBox);


//! [4] //! [5]
    setLayout(mainLayout);

    setWindowTitle(tr("Calibrate"));

    recalibrateBox->setText(QApplication::translate("Calibrate", "ReCalibrate", 0, QApplication::UnicodeUTF8));
    recalibrateBox->setShortcut(QApplication::translate("Calibrate", "Ctrl+L", 0, QApplication::UnicodeUTF8));

}
//! [5]

//! [12]
void CalibrateDialog::createFormGroupBox()
{
    formGroupBox = new QGroupBox(tr("Calibrate"));
    QFormLayout *layout = new QFormLayout;
    //layout->addRow(new QLabel(tr("Id/Name:")), idLineEdit);
    //layout->addRow(new QLabel(tr("Is Enabled:")), layerEnabledBox);
    formGroupBox->setLayout(layout);
}
//! [12]

void CalibrateDialog::loadData(){
    if (this->model != NULL){
        this->model->setActiveCamDisplayHelpers(true);
         ofVec2f coord = this->model->getActiveCamHelperCoord(true,0);
         x0IniSpinBox->setValue(coord.x);
         y0IniSpinBox->setValue(coord.y);
        coord = this->model->getActiveCamHelperCoord(true,1);
         x1IniSpinBox->setValue(coord.x);
         y1IniSpinBox->setValue(coord.y);
        coord = this->model->getActiveCamHelperCoord(true,2);
         x2IniSpinBox->setValue(coord.x);
         y2IniSpinBox->setValue(coord.y);
        coord = this->model->getActiveCamHelperCoord(true,3);
         x3IniSpinBox->setValue(coord.x);
         y3IniSpinBox->setValue(coord.y);

        coord = this->model->getActiveCamHelperCoord(false,0);
         x0FinSpinBox->setValue(coord.x);
         y0FinSpinBox->setValue(coord.y);
        coord = this->model->getActiveCamHelperCoord(false,1);
         x1FinSpinBox->setValue(coord.x);
         y1FinSpinBox->setValue(coord.y);
        coord = this->model->getActiveCamHelperCoord(false,2);
         x2FinSpinBox->setValue(coord.x);
         y2FinSpinBox->setValue(coord.y);
        coord = this->model->getActiveCamHelperCoord(false,3);
         x3FinSpinBox->setValue(coord.x);
         y3FinSpinBox->setValue(coord.y);
    }
}
void CalibrateDialog::x0IniValueChanged(double newVal){
    ofVec2f coord;
    ofVec2f coordAux = this->model->getActiveCamHelperCoord(true,0);
    coord.set( newVal, coordAux.y);
    if (this->model != NULL){
        this->model->setActiveCamHelperCoord(true, 0, coord);
    }
}
void CalibrateDialog::x1IniValueChanged(double newVal){
    ofVec2f coord;
    ofVec2f coordAux = this->model->getActiveCamHelperCoord(true,1);
    coord.set( newVal, coordAux.y);
    if (this->model != NULL){
        this->model->setActiveCamHelperCoord(true, 1, coord);
    }
}
void CalibrateDialog::x2IniValueChanged(double newVal){
    ofVec2f coord;
    ofVec2f coordAux = this->model->getActiveCamHelperCoord(true,2);
    coord.set( newVal, coordAux.y);
    if (this->model != NULL){
        this->model->setActiveCamHelperCoord(true, 2, coord);
    }
}
void CalibrateDialog::x3IniValueChanged(double newVal){
    ofVec2f coord;
    ofVec2f coordAux = this->model->getActiveCamHelperCoord(true,3);
    coord.set( newVal, coordAux.y);
    if (this->model != NULL){
        this->model->setActiveCamHelperCoord(true, 3, coord);
    }
}
void CalibrateDialog::y0IniValueChanged(double newVal){
    ofVec2f coord;
    ofVec2f coordAux = this->model->getActiveCamHelperCoord(true,0);
    coord.set( coordAux.x, newVal);
    if (this->model != NULL){
        this->model->setActiveCamHelperCoord(true, 0, coord);
    }
}
void CalibrateDialog::y1IniValueChanged(double newVal){
    ofVec2f coord;
    ofVec2f coordAux = this->model->getActiveCamHelperCoord(true,1);
    coord.set( coordAux.x, newVal);
    if (this->model != NULL){
        this->model->setActiveCamHelperCoord(true, 1, coord);
    }
}
void CalibrateDialog::y2IniValueChanged(double newVal){
    ofVec2f coord;
    ofVec2f coordAux = this->model->getActiveCamHelperCoord(true,2);
    coord.set( coordAux.x, newVal);
    if (this->model != NULL){
        this->model->setActiveCamHelperCoord(true, 2, coord);
    }
}
void CalibrateDialog::y3IniValueChanged(double newVal){
    ofVec2f coord;
    ofVec2f coordAux = this->model->getActiveCamHelperCoord(true,3);
    coord.set( coordAux.x, newVal);
    if (this->model != NULL){
        this->model->setActiveCamHelperCoord(true, 3, coord);
    }
}

void CalibrateDialog::x0FinValueChanged(double newVal){
    ofVec2f coord;
    ofVec2f coordAux = this->model->getActiveCamHelperCoord(false,0);
    coord.set( newVal, coordAux.y);
    if (this->model != NULL){
        this->model->setActiveCamHelperCoord(false, 0, coord);
    }
}
void CalibrateDialog::x1FinValueChanged(double newVal){
    ofVec2f coord;
    ofVec2f coordAux = this->model->getActiveCamHelperCoord(false,1);
    coord.set( newVal, coordAux.y);
    if (this->model != NULL){
        this->model->setActiveCamHelperCoord(false, 1, coord);
    }
}
void CalibrateDialog::x2FinValueChanged(double newVal){
    ofVec2f coord;
    ofVec2f coordAux = this->model->getActiveCamHelperCoord(false,2);
    coord.set( newVal, coordAux.y);
    if (this->model != NULL){
        this->model->setActiveCamHelperCoord(false, 2, coord);
    }
}
void CalibrateDialog::x3FinValueChanged(double newVal){
    ofVec2f coord;
    ofVec2f coordAux = this->model->getActiveCamHelperCoord(false,3);
    coord.set( newVal, coordAux.y);
    if (this->model != NULL){
        this->model->setActiveCamHelperCoord(false, 3, coord);
    }
}
void CalibrateDialog::y0FinValueChanged(double newVal){
    ofVec2f coord;
    ofVec2f coordAux = this->model->getActiveCamHelperCoord(false,0);
    coord.set( coordAux.x, newVal);
    if (this->model != NULL){
        this->model->setActiveCamHelperCoord(false, 0, coord);
    }
}
void CalibrateDialog::y1FinValueChanged(double newVal){
    ofVec2f coord;
    ofVec2f coordAux = this->model->getActiveCamHelperCoord(false,1);
    coord.set( coordAux.x, newVal);
    if (this->model != NULL){
        this->model->setActiveCamHelperCoord(false, 1, coord);
    }
}
void CalibrateDialog::y2FinValueChanged(double newVal){
    ofVec2f coord;
    ofVec2f coordAux = this->model->getActiveCamHelperCoord(false,2);
    coord.set( coordAux.x, newVal);
    if (this->model != NULL){
        this->model->setActiveCamHelperCoord(false, 2, coord);
    }
}
void CalibrateDialog::y3FinValueChanged(double newVal){
    ofVec2f coord;
    ofVec2f coordAux = this->model->getActiveCamHelperCoord(false,3);
    coord.set( coordAux.x, newVal);
    if (this->model != NULL){
        this->model->setActiveCamHelperCoord(false, 3, coord);
    }
}

void CalibrateDialog::enabledChange(bool newVal){

}
void CalibrateDialog::reCalibration(){
    if (this->model != NULL){
        this->model->resetActiveCamCalibraton();
    }
}

void CalibrateDialog::acceptPressed(){
    if (this->model != NULL){
        this->model->setActiveCamDisplayHelpers(false);
        this->model->calibrateActiveCam();
    }
    hide();
}

void CalibrateDialog::rejectPressed(){
    if (this->model != NULL){
        this->model->setActiveCamDisplayHelpers(false);
    }
    undoChanges();
    hide();
}

void CalibrateDialog::undoChanges(){

}
