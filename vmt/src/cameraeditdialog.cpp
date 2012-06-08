#include <QtGui>

#include "cameraeditdialog.h"
#include "uiutils.h"

using namespace gui;

//! [0]
CameraEditorDialog::CameraEditorDialog(VmtModel *modelobj, string id)
{
    this->model = modelobj;
    cameraId = id;
    xCoordSpinBox = UiUtils::createCoordinateSpinBox();
    yCoordSpinBox = UiUtils::createCoordinateSpinBox();
    zCoordSpinBox = UiUtils::createCoordinateSpinBox();

    xCoordSpinEyeBox = UiUtils::createCoordinateSpinBox();
    yCoordSpinEyeBox = UiUtils::createCoordinateSpinBox();
    zCoordSpinEyeBox = UiUtils::createCoordinateSpinBox();

    xCoordSpinUpBox = UiUtils::createCoordinateSpinBox();
    yCoordSpinUpBox = UiUtils::createCoordinateSpinBox();
    zCoordSpinUpBox = UiUtils::createCoordinateSpinBox();

    fieldOfView = UiUtils::createDoubleSpinBox();
    fieldOfView->setMaximumWidth(100);
    aspectRatio = UiUtils::createDoubleSpinBox();
    aspectRatio->setMaximumWidth(100);
    zNear = UiUtils::createDoubleSpinBox();
    zNear->setMaximumWidth(100);
    zFar = UiUtils::createDoubleSpinBox();
    zFar->setMaximumWidth(100);

    projector = new  QCheckBox();
    idLineEdit = new QLineEdit();

    loadData();

    createFormGroupBox();
//! [0]

//! [1]
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(acceptPressed()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(rejectPressed()));

    connect(xCoordSpinBox, SIGNAL(valueChanged(double)), this, SLOT(xValueChanged(double)));
    connect(yCoordSpinBox, SIGNAL(valueChanged(double)), this, SLOT(yValueChanged(double)));
    connect(zCoordSpinBox, SIGNAL(valueChanged(double)), this, SLOT(zValueChanged(double)));

    connect(xCoordSpinEyeBox, SIGNAL(valueChanged(double)), this, SLOT(xValueChangedEye(double)));
    connect(yCoordSpinEyeBox, SIGNAL(valueChanged(double)), this, SLOT(yValueChangedEye(double)));
    connect(zCoordSpinEyeBox, SIGNAL(valueChanged(double)), this, SLOT(zValueChangedEye(double)));

    connect(xCoordSpinUpBox, SIGNAL(valueChanged(double)), this, SLOT(xValueChangedUp(double)));
    connect(yCoordSpinUpBox, SIGNAL(valueChanged(double)), this, SLOT(yValueChangedUp(double)));
    connect(zCoordSpinUpBox, SIGNAL(valueChanged(double)), this, SLOT(zValueChangedUp(double)));

    connect(fieldOfView, SIGNAL(valueChanged(double)), this, SLOT(fieldOfViewValueChanged(double)));
    connect(aspectRatio, SIGNAL(valueChanged(double)), this, SLOT(aspectRatioValueChanged(double)));
    connect(zNear, SIGNAL(valueChanged(double)), this, SLOT(zNearValueChanged(double)));
    connect(zFar, SIGNAL(valueChanged(double)), this, SLOT(zFarValueChanged(double)));

    connect(projector, SIGNAL(clicked(bool)), this, SLOT(proyectorChange(bool)));


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

    setWindowTitle(tr("Camera Properties"));

}
//! [5]

//! [12]
void CameraEditorDialog::createFormGroupBox()
{
    formGroupBox = new QGroupBox(tr("Camera properties"));

    QGridLayout *coordinatesLayout = new QGridLayout;
    coordinatesLayout->addWidget(new QLabel(tr("Id/Name:")), 0, 0);
    coordinatesLayout->addWidget(idLineEdit, 0, 1, 1, 4);
    coordinatesLayout->addWidget(new QLabel(tr("Position:")), 1, 0);
    coordinatesLayout->addWidget(new QLabel(tr("X:")), 1, 1);
    coordinatesLayout->addWidget(xCoordSpinBox, 1, 2);
    coordinatesLayout->addWidget(new QLabel(tr("Y:")), 1, 3);
    coordinatesLayout->addWidget(yCoordSpinBox, 1, 4);
    coordinatesLayout->addWidget(new QLabel(tr("Z:")), 1, 5);
    coordinatesLayout->addWidget(zCoordSpinBox, 1, 6);
    coordinatesLayout->addWidget(new QLabel(tr("Eye:")), 2, 0);
    coordinatesLayout->addWidget(new QLabel(tr("X:")), 2, 1);
    coordinatesLayout->addWidget(xCoordSpinEyeBox, 2, 2);
    coordinatesLayout->addWidget(new QLabel(tr("Y:")), 2, 3);
    coordinatesLayout->addWidget(yCoordSpinEyeBox, 2, 4);
    coordinatesLayout->addWidget(new QLabel(tr("Z:")), 2, 5);
    coordinatesLayout->addWidget(zCoordSpinEyeBox, 2, 6);
    coordinatesLayout->addWidget(new QLabel(tr("Up:")), 3, 0);
    coordinatesLayout->addWidget(new QLabel(tr("X:")), 3, 1);
    coordinatesLayout->addWidget(xCoordSpinUpBox, 3, 2);
    coordinatesLayout->addWidget(new QLabel(tr("Y:")), 3, 3);
    coordinatesLayout->addWidget(yCoordSpinUpBox, 3, 4);
    coordinatesLayout->addWidget(new QLabel(tr("Z:")), 3, 5);
    coordinatesLayout->addWidget(zCoordSpinUpBox, 3, 6);

    coordinatesLayout->addWidget(new QLabel(tr("fieldOfView :")), 4, 0);
    coordinatesLayout->addWidget(fieldOfView, 4, 1, 1, 6);

    coordinatesLayout->addWidget(new QLabel(tr("aspectRatio :")), 5, 0);
    coordinatesLayout->addWidget(aspectRatio, 5, 1, 1, 6);

    coordinatesLayout->addWidget(new QLabel(tr("zNear :")), 6, 0);
    coordinatesLayout->addWidget(zNear, 6, 1, 1, 6);

    coordinatesLayout->addWidget(new QLabel(tr("zFar :")), 7, 0);
    coordinatesLayout->addWidget(zFar, 7, 1, 1, 6);

    coordinatesLayout->addWidget(new QLabel(tr("Is Proyector:")), 8, 0);
    coordinatesLayout->addWidget(projector, 8, 1, 1, 6);

    formGroupBox->setLayout(coordinatesLayout);
}
//! [12]

void CameraEditorDialog::loadData(){
    if (this->model != NULL) {
        Qt::CheckState state;
        state= Qt::Unchecked;
        ofxCamera *camera = this->model->getCameras()[cameraId];

        idLineEdit->setText(QString(cameraId.c_str()));
        idLineEdit->setReadOnly(true);

        previousprojector = camera->isProjector();
        if (previousprojector) {  state=Qt::Checked;}
        projector->setCheckState(state);

        previousX = camera->getPosition().x;
        previousY = camera->getPosition().y;
        previousZ = camera->getPosition().z;

        xCoordSpinBox->setValue(previousX);
        yCoordSpinBox->setValue(previousY);
        zCoordSpinBox->setValue(previousZ);

        previousEyeX = camera->getEye().x;
        previousEyeY = camera->getEye().y;
        previousEyeZ = camera->getEye().z;

        xCoordSpinEyeBox->setValue(previousEyeX);
        yCoordSpinEyeBox->setValue(previousEyeY);
        zCoordSpinEyeBox->setValue(previousEyeZ);

        previousUpX = camera->getUp().x;
        previousUpY = camera->getUp().y;
        previousUpZ = camera->getUp().z;

        xCoordSpinUpBox->setValue(previousUpX);
        yCoordSpinUpBox->setValue(previousUpY);
        zCoordSpinUpBox->setValue(previousUpZ);

        previousaspectRatio = camera->getaspectRatio();
        aspectRatio->setValue(previousaspectRatio);

        previousfieldOfView = camera->getfieldOfView();
        fieldOfView->setValue(previousfieldOfView);

        previouszFar = camera->getzFar();
        zFar->setValue(previouszFar);

        previouszNear = camera->getzNear();
        zNear->setValue(previouszNear);

        }

}

void CameraEditorDialog::xValueChanged(double newVal){
     if(this->model != NULL)
        this->model->setCameraPos(cameraId,newVal, previousY, previousZ);
}

void CameraEditorDialog::yValueChanged(double newVal){
     if(this->model != NULL)
        this->model->setCameraPos(cameraId,previousX, newVal, previousZ);
}

void CameraEditorDialog::zValueChanged(double newVal){
     if(this->model != NULL)
        this->model->setCameraPos(cameraId,previousX, previousY, newVal);
}

void CameraEditorDialog::xValueChangedEye(double newVal){
     if(this->model != NULL)
        this->model->setCameraEye(cameraId,newVal, previousEyeY, previousEyeZ);
}
void CameraEditorDialog::yValueChangedEye(double newVal){
     if(this->model != NULL)
        this->model->setCameraEye(cameraId,previousEyeX, newVal, previousEyeZ);
}
void CameraEditorDialog::zValueChangedEye(double newVal){
     if(this->model != NULL)
        this->model->setCameraEye(cameraId,previousEyeX, previousEyeY, newVal);
}
void CameraEditorDialog::xValueChangedUp(double newVal){
     if(this->model != NULL)
        this->model->setCameraUp(cameraId,newVal, previousUpY, previousUpZ);
}
void CameraEditorDialog::yValueChangedUp(double newVal){
     if(this->model != NULL)
        this->model->setCameraUp(cameraId,previousUpX, newVal, previousUpZ);
}
void CameraEditorDialog::zValueChangedUp(double newVal){
     if(this->model != NULL)
        this->model->setCameraUp(cameraId,previousUpX, previousUpY, newVal);
}

void CameraEditorDialog::fieldOfViewValueChanged(double newVal){
        if(this->model != NULL)
        this->model->setPerspective(cameraId, newVal, previousaspectRatio, previouszNear,previouszFar);
}
void CameraEditorDialog::aspectRatioValueChanged(double newVal){
        if(this->model != NULL)
        this->model->setPerspective(cameraId, previousfieldOfView, newVal, previouszNear,previouszFar);
}
void CameraEditorDialog::zNearValueChanged(double newVal){
        if(this->model != NULL)
        this->model->setPerspective(cameraId, previousfieldOfView, previousaspectRatio, newVal,previouszFar);
}
void CameraEditorDialog::zFarValueChanged(double newVal){
        if(this->model != NULL)
        this->model->setPerspective(cameraId, previousfieldOfView, previousaspectRatio, previouszNear,newVal);
}
void CameraEditorDialog::proyectorChange(bool newVal){
        if(this->model != NULL)
        this->model->setIsProjector(cameraId,newVal);
}


void CameraEditorDialog::acceptPressed(){
    if (this->model != NULL)
    this->model->setIsProjector(cameraId, projector->isChecked());
    hide();
}

void CameraEditorDialog::rejectPressed(){
    undoChanges();
    hide();
}

void CameraEditorDialog::undoChanges(){
    if (this->model != NULL) {
        this->model->setIsProjector(cameraId, previousprojector);
        this->model->setPerspective(cameraId, previousfieldOfView, previousaspectRatio, previouszNear,previouszFar);
        this->model->setCameraUp(cameraId,previousUpX, previousUpY, previousUpZ);
        this->model->setCameraEye(cameraId,previousEyeX, previousEyeY, previousEyeZ);
        this->model->setCameraPos(cameraId,previousX, previousY, previousZ);

    }
}
