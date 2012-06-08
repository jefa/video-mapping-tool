#include "objecteditdialog.h"
#include "uiutils.h"
#include <QtGui>

using namespace gui;

//! [0]
ObjectEditorDialog::ObjectEditorDialog(VmtModel *modelobj, string idobj)
{
    this->model = modelobj;
    this->idobj = idobj;
    Object3D *obj3d = this->model->getObject3D(idobj);
    object3d = obj3d;
    xCoordSpinBox = UiUtils::createCoordinateSpinBox();
    yCoordSpinBox = UiUtils::createCoordinateSpinBox();
    zCoordSpinBox = UiUtils::createCoordinateSpinBox();
    idLineEdit = new QLineEdit();
    idLineEdit->setMaximumWidth(80);

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

    setWindowTitle(tr("Object Properties"));

}
//! [5]

//! [12]
void ObjectEditorDialog::createFormGroupBox()
{
    formGroupBox = new QGroupBox(tr("Object properties"));
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(new QLabel(tr("Id/Name:")), 0, 0);
    layout->addWidget(idLineEdit, 0, 1, 1, 2);
    layout->addWidget(new QLabel(tr("Coord. :")), 1, 0);
    layout->addWidget(new QLabel(tr("X:")), 1, 1);
    layout->addWidget(xCoordSpinBox, 1, 2);
    layout->addWidget(new QLabel(tr("Y:")), 1, 3);
    layout->addWidget(yCoordSpinBox, 1, 4);
    layout->addWidget(new QLabel(tr("Z:")), 1, 5);
    layout->addWidget(zCoordSpinBox, 1, 6);
    formGroupBox->setLayout(layout);
}
//! [12]

void ObjectEditorDialog::loadData(){
    if (this->object3d != NULL) {
        previousId = this->object3d->getId();
        previousX = this->object3d->get(POS_X);
        previousY = this->object3d->get(POS_Y);
        previousZ = this->object3d->get(POS_Z);

        idLineEdit->setText(QString(previousId.c_str()));
        idLineEdit->setReadOnly(true);
        xCoordSpinBox->setValue(previousX);
        yCoordSpinBox->setValue(previousY);
        zCoordSpinBox->setValue(previousZ);

    }
}

void ObjectEditorDialog::xValueChanged(double newVal){
    if (this->model != NULL)
        this->model->setObject3D(idobj, POS_X, newVal);
}

void ObjectEditorDialog::yValueChanged(double newVal){
    if (this->model != NULL)
        this->model->setObject3D(idobj,POS_Y, newVal);
}

void ObjectEditorDialog::zValueChanged(double newVal){
    if (this->model != NULL)
        this->model->setObject3D(idobj,POS_Z, newVal);
}

void ObjectEditorDialog::acceptPressed(){
    hide();
}

void ObjectEditorDialog::rejectPressed(){
    undoChanges();
    hide();
}

void ObjectEditorDialog::undoChanges(){
    if (this->model != NULL) {
        this->model->setObject3D(idobj, POS_X, previousX);
        this->model->setObject3D(idobj, POS_Y, previousY);
        this->model->setObject3D(idobj, POS_Z, previousZ);
    }
}
