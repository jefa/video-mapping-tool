#include <QtGui>

#include "backgraundeditdialog.h"
#include <limits>

using namespace gui;

//! [0]
BackgraundEditorDialog::BackgraundEditorDialog(VmtModel *modelobj)
{
    model = modelobj;
    colorBox = new QColorDialog();

    loadData();

    createFormGroupBox();
//! [0]


    connect(colorBox, SIGNAL(accepted()), this, SLOT(acceptPressed()));
    connect(colorBox, SIGNAL(rejected()), this, SLOT(rejectPressed()));

    connect(colorBox, SIGNAL(colorSelected(QColor)), this, SLOT(enabledChange(QColor)));


//! [1]

//! [2]
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(formGroupBox);


//! [4] //! [5]
    setLayout(mainLayout);

    setWindowTitle(tr("Backgraund Properties"));

}
//! [5]

//! [12]
void BackgraundEditorDialog::createFormGroupBox()
{
    formGroupBox = new QGroupBox(tr("Backgraund properties"));
    QFormLayout *layout = new QFormLayout;
    layout->addRow(new QLabel(tr("backgraund:")), colorBox);

    formGroupBox->setLayout(layout);
}
//! [12]

void BackgraundEditorDialog::loadData(){
}

void BackgraundEditorDialog::enabledChange(QColor newVal){
    this->model->setBackground(newVal.red(),newVal.green(),newVal.blue());
}

void BackgraundEditorDialog::acceptPressed(){
    hide();
}

void BackgraundEditorDialog::rejectPressed(){
    undoChanges();
    hide();
}

void BackgraundEditorDialog::undoChanges(){

}
