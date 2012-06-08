#include <QtGui>

#include "nodeeditdialog.h"
#include <limits>

using namespace gui;

//! [0]
NodeEditorDialog::NodeEditorDialog(VmtModel *modelobj, string idNode)
{
    this->model = modelobj;
    this->idNode = idNode;
    //cout<< " id nodo al crear el objeto "<<idNode;

    isActiveBox = new  QCheckBox();
    idLineEdit = new QLineEdit();
    addressEdit = new QLineEdit();
    cameraIdEdit =  new QLineEdit();
    portEdit =  new QLineEdit();

    loadData();

    createFormGroupBox();
//! [0]

//! [1]
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(acceptPressed()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(rejectPressed()));

    connect(isActiveBox, SIGNAL(clicked(bool)), this, SLOT(isActive(bool)));


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

    setWindowTitle(tr("Node Properties"));

}

//! [5]

//! [12]
void NodeEditorDialog::createFormGroupBox()
{
    formGroupBox = new QGroupBox(tr("Node properties"));
    QFormLayout *layout = new QFormLayout;
    layout->addRow(new QLabel(tr("Id/Name:")), idLineEdit);
    layout->addRow(new QLabel(tr("Is Active:")), isActiveBox);
    layout->addRow(new QLabel(tr("Address:")), addressEdit);
    layout->addRow(new QLabel(tr("CameraId:")), cameraIdEdit);
    layout->addRow(new QLabel(tr("Port:")), portEdit);

    formGroupBox->setLayout(layout);
}
//! [12]

void NodeEditorDialog::loadData(){
    //cout << "id node  "<<idNode;
    Node *node = this->model->getNode(idNode);
    previousAddress = node->address;
    previousCameraId = node->cameraId;
    previousPort = node->port;
    previousIsActive = node->isActive;
    idLineEdit->setText(QString(idNode.c_str()));
    idLineEdit->setReadOnly(true);
    isActiveBox->setChecked(node->isActive);
    addressEdit->setText(QString((node->address).c_str()));
    cameraIdEdit->setText(QString((node->cameraId).c_str()));
    portEdit->setText(QString(node->port));
}

void NodeEditorDialog::isActive(bool newVal){
    this->model->getNode(idNode)->isActive = newVal;
}

void NodeEditorDialog::acceptPressed(){
    this->model->setNodeAtributes(idNode,addressEdit->text().toStdString(), portEdit->text().toInt(), isActiveBox->isChecked(),cameraIdEdit->text().toStdString());
    hide();
}

void NodeEditorDialog::rejectPressed(){
    undoChanges();
    hide();
}

void NodeEditorDialog::undoChanges(){
        this->model->setNodeAtributes(idNode, previousAddress , previousPort, previousIsActive, previousCameraId);

}
