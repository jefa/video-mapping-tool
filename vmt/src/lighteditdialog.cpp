#include <QtGui>

#include "lighteditdialog.h"
#include <limits>

using namespace gui;

//! [0]
LightEditorDialog::LightEditorDialog(VmtModel *modelobj, string id)
{
    this->model = modelobj;
    idlight = id;

    onBox = new  QCheckBox();
    idLineEdit = new QLineEdit();

    loadData();

    createFormGroupBox();
//! [0]

//! [1]
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(acceptPressed()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(rejectPressed()));

    connect(onBox, SIGNAL(clicked(bool)), this, SLOT(enabledChange(bool)));


//! [1]

//! [2]
    QVBoxLayout *mainLayout = new QVBoxLayout;
//! [2] //! [3]

//! [3] //! [4]
    mainLayout->addWidget(formGroupBox);
    mainLayout->addWidget(buttonBox);

//! [4] //! [5]
    setLayout(mainLayout);

    setWindowTitle(tr("Light Properties"));

}
//! [5]

//! [12]
void LightEditorDialog::createFormGroupBox()
{
    formGroupBox = new QGroupBox(tr("Light properties"));
    QFormLayout *layout = new QFormLayout;
    layout->addRow(new QLabel(tr("Id/Name:")), idLineEdit);
    layout->addRow(new QLabel(tr("ON:")), onBox);
    formGroupBox->setLayout(layout);
}
//! [12]

void LightEditorDialog::loadData(){
    Qt::CheckState state;
    state= Qt::Unchecked;
    if (this->model != NULL) {
        previousValueON =  (this->model->getLight(idlight))->ison();
        if (previousValueON) {  state=Qt::Checked;}

        idLineEdit->setText(QString(( (this->model->getLight(idlight))->getId() ).c_str()));
        idLineEdit->setReadOnly(true);
        onBox->setCheckState(state);

    }
}

void LightEditorDialog::enabledChange(bool newVal){
    if (this->model != NULL)
        if (newVal)   this->model->setLightOn( (this->model->getLight(idlight))->getId() );
        else this->model->setLightOff((this->model->getLight(idlight))->getId());

}

void LightEditorDialog::acceptPressed(){
    hide();
}

void LightEditorDialog::rejectPressed(){
    undoChanges();
    hide();
}

void LightEditorDialog::undoChanges(){
    if (this->model != NULL) {

        if (previousValueON)    this->model->getScene()->setLightOn((this->model->getLight(idlight))->getId());
        else this->model->getScene()->setLightOff((this->model->getLight(idlight))->getId());


    }
}
