#include <QtGui>

#include "quadeditdialog.h"
#include "uiutils.h"
#include <limits>

using namespace gui;

//! [0]
QuadEditorDialog::QuadEditorDialog(VmtModel *model, string Camera, string Layer, string Quad)
{

    this->model = model;
    object2d = model->getLayer2D(Layer)->getQuad2D(Quad);
    idCamera= Camera;
    idLayer = Layer;
    idQuad = Quad;
    //cout<< idCamera <<"  "<< idLayer <<"  "<< idQuad ;
    x0CoordSpinBox = UiUtils::createCoordinateSpinBox();
    y0CoordSpinBox = UiUtils::createCoordinateSpinBox();
    x1CoordSpinBox = UiUtils::createCoordinateSpinBox();
    y1CoordSpinBox = UiUtils::createCoordinateSpinBox();
    x2CoordSpinBox = UiUtils::createCoordinateSpinBox();
    y2CoordSpinBox = UiUtils::createCoordinateSpinBox();
    x3CoordSpinBox = UiUtils::createCoordinateSpinBox();
    y3CoordSpinBox = UiUtils::createCoordinateSpinBox();

    enabledBox = new  QCheckBox();
    idLineEdit = new QLineEdit();

    loadData();

    createFormGroupBox();
//! [0]

//! [1]
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(acceptPressed()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(rejectPressed()));

    connect(x0CoordSpinBox, SIGNAL(valueChanged(double)), this, SLOT(x0ValueChanged(double)));
    connect(y0CoordSpinBox, SIGNAL(valueChanged(double)), this, SLOT(y0ValueChanged(double)));

    connect(x1CoordSpinBox, SIGNAL(valueChanged(double)), this, SLOT(x1ValueChanged(double)));
    connect(y1CoordSpinBox, SIGNAL(valueChanged(double)), this, SLOT(y1ValueChanged(double)));

    connect(x2CoordSpinBox, SIGNAL(valueChanged(double)), this, SLOT(x2ValueChanged(double)));
    connect(y2CoordSpinBox, SIGNAL(valueChanged(double)), this, SLOT(y2ValueChanged(double)));

    connect(x3CoordSpinBox, SIGNAL(valueChanged(double)), this, SLOT(x3ValueChanged(double)));
    connect(y3CoordSpinBox, SIGNAL(valueChanged(double)), this, SLOT(y3ValueChanged(double)));

    connect(enabledBox, SIGNAL(clicked(bool)), this, SLOT(enabledChanged(bool)));


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

    setWindowTitle(tr("Quad Properties"));

}
//! [5]

//! [12]
void QuadEditorDialog::createFormGroupBox()
{
    formGroupBox = new QGroupBox(tr("Quad properties"));
    QGridLayout *gridLayout = new QGridLayout;

    gridLayout->addWidget(new QLabel(tr("Id/Name:")), 0, 0);
    gridLayout->addWidget(idLineEdit, 0, 1, 1, 6);

    gridLayout->addWidget(new QLabel(tr("Is Enabled:")), 1, 0);
    gridLayout->addWidget(enabledBox, 1, 1, 1, 6);

    gridLayout->addWidget(new QLabel(tr("Point 0:")), 2, 0);
    gridLayout->addWidget(new QLabel(tr("X:")), 2, 1);
    gridLayout->addWidget(x0CoordSpinBox, 2, 2);
    gridLayout->addWidget(new QLabel(tr("Y:")), 2, 3);
    gridLayout->addWidget(y0CoordSpinBox, 2, 4);

    gridLayout->addWidget(new QLabel(tr("Point 1:")), 3, 0);
    gridLayout->addWidget(new QLabel(tr("X:")), 3, 1);
    gridLayout->addWidget(x1CoordSpinBox, 3, 2);
    gridLayout->addWidget(new QLabel(tr("Y:")), 3, 3);
    gridLayout->addWidget(y1CoordSpinBox, 3, 4);

    gridLayout->addWidget(new QLabel(tr("Point 2:")), 4, 0);
    gridLayout->addWidget(new QLabel(tr("X:")), 4, 1);
    gridLayout->addWidget(x2CoordSpinBox, 4, 2);
    gridLayout->addWidget(new QLabel(tr("Y:")), 4, 3);
    gridLayout->addWidget(y2CoordSpinBox, 4, 4);

    gridLayout->addWidget(new QLabel(tr("Point 3:")), 5, 0);
    gridLayout->addWidget(new QLabel(tr("X:")), 5, 1);
    gridLayout->addWidget(x3CoordSpinBox, 5, 2);
    gridLayout->addWidget(new QLabel(tr("Y:")), 5, 3);
    gridLayout->addWidget(y3CoordSpinBox, 5, 4);

    formGroupBox->setLayout(gridLayout);
}
//! [12]

void QuadEditorDialog::loadData(){
    Qt::CheckState state;
    state= Qt::Unchecked;
    if (this->object2d != NULL) {
        previousId = this->object2d->getId();
        idLineEdit->setText(QString(previousId.c_str()));
        idLineEdit->setReadOnly(true);

        previousEnabled = this->object2d->isEnabled();
        if (previousEnabled) {  state=Qt::Checked;}
        enabledBox->setCheckState(state);


        previous0X = this->object2d->getPoint(0).x;
        aux0X = previous0X;
        previous0Y = this->object2d->getPoint(0).y;
        aux0Y = previous0Y;

        x0CoordSpinBox->setValue(previous0X);
        y0CoordSpinBox->setValue(previous0Y);

        previous1X = this->object2d->getPoint(1).x;
        aux1X = previous1X;
        previous1Y = this->object2d->getPoint(1).y;
        aux1Y = previous1Y;

        x1CoordSpinBox->setValue(previous1X);
        y1CoordSpinBox->setValue(previous1Y);

        previous2X = this->object2d->getPoint(2).x;
        aux2X = previous2X;
        previous2Y = this->object2d->getPoint(2).y;
        aux2Y = previous2Y;

        x2CoordSpinBox->setValue(previous2X);
        y2CoordSpinBox->setValue(previous2Y);

        previous3X = this->object2d->getPoint(3).x;
        aux3X = previous3X;
        previous3Y = this->object2d->getPoint(3).y;
        aux3Y = previous3Y;

        x3CoordSpinBox->setValue(previous3X);
        y3CoordSpinBox->setValue(previous3Y);

    }
}
void QuadEditorDialog::enabledChanged(bool newVal){
    if (this->model != NULL)
        this ->model->enableQuad(idCamera, idLayer, idQuad, newVal);
}

void QuadEditorDialog::x0ValueChanged(double newVal){
    float value;
    value = newVal;
    if (this->model != NULL){
            this->model->setQuadPoint(idCamera, idLayer,idQuad,0, value, aux0Y);
            aux0X=newVal;
    }
}

void QuadEditorDialog::y0ValueChanged(double newVal){
    if (this->model != NULL){
        this->model->setQuadPoint(idCamera, idLayer, idQuad,0, aux0X, newVal);
        aux0Y=newVal;
    }

}
void QuadEditorDialog::x1ValueChanged(double newVal){
    if (this->model != NULL){
            this->model->setQuadPoint(idCamera, idLayer, idQuad,1, newVal, aux1Y);
            aux1X=newVal;
    }
}

void QuadEditorDialog::y1ValueChanged(double newVal){
    if (this->model != NULL){
        this->model->setQuadPoint(idCamera, idLayer, idQuad,1, aux1X, newVal);
        aux1Y=newVal;
    }
}
void QuadEditorDialog::x2ValueChanged(double newVal){
    if (this->model != NULL){
            this->model->setQuadPoint(idCamera, idLayer, idQuad,2, newVal, aux2Y);
            aux2X=newVal;
    }
}

void QuadEditorDialog::y2ValueChanged(double newVal){
    if (this->model != NULL){
        this->model->setQuadPoint(idCamera, idLayer, idQuad,2, aux2X, newVal);
        aux2Y=newVal;
    }
}
void QuadEditorDialog::x3ValueChanged(double newVal){
    float value;
    value = newVal;
    if (this->model != NULL){
            this->model->setQuadPoint(idCamera, idLayer, idQuad,3, value, aux3Y);
            aux3X=newVal;
    }
}

void QuadEditorDialog::y3ValueChanged(double newVal){
    float value;
    value = newVal;
    if (this->model != NULL){
        this->model->setQuadPoint(this->idCamera,this->idLayer, this->idQuad,3, aux3X, value);
        aux3Y=newVal;
    }
}
void QuadEditorDialog::acceptPressed(){
    this ->model->enableQuad(idCamera, idLayer, idQuad, enabledBox->isChecked());
    hide();
}

void QuadEditorDialog::rejectPressed(){
    undoChanges();
    hide();
}

void QuadEditorDialog::undoChanges(){
    if (this->model != NULL) {
        this ->model->enableQuad(idCamera, idLayer, idQuad, previousEnabled);
        this->model->setQuadPoint(idCamera, idLayer, idQuad,0, previous0X, previous0Y);
        this->model->setQuadPoint(idCamera, idLayer, idQuad,1, previous1X, previous1Y);
        this->model->setQuadPoint(idCamera, idLayer, idQuad,2, previous2X, previous2Y);
        this->model->setQuadPoint(idCamera, idLayer, idQuad,3, previous3X, previous3Y);
    }
}
