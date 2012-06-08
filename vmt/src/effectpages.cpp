#include <QtGui>

#include "effectpages.h"
#include "Object3D.h"
#include "uiutils.h"
#include <map>

PositionEffectPage::PositionEffectPage(VmtModel *vmtModel, Effect *ef, QWidget *parent)
    : QWidget(parent)
{
    QGroupBox *configGroup = new QGroupBox(tr("Configuration"));
    QLabel *effectIdLabel = new QLabel(tr("Effect Id:"));
    effectIdTxt = new QLineEdit;
    QLabel *objectIdLabel = new QLabel(tr("Object Id:"));
    objectCombo = new QComboBox;

    loadObjectsCombo(objectCombo, vmtModel);

    //Coordiantes panel
    QLabel *xLabel1 = new QLabel(tr("X:"));
    QLabel *xLabel2 = new QLabel(tr("X:"));
    QLabel *yLabel1 = new QLabel(tr("Y:"));
    QLabel *yLabel2 = new QLabel(tr("Y:"));
    QLabel *zLabel1 = new QLabel(tr("Z:"));
    QLabel *zLabel2 = new QLabel(tr("Z:"));
    QLabel *posIniLabel = new QLabel(tr("Ini:"));
    xIniSpinBox = UiUtils::createCoordinateSpinBox();
    yIniSpinBox = UiUtils::createCoordinateSpinBox();
    zIniSpinBox = UiUtils::createCoordinateSpinBox();
    QLabel *posFinLabel = new QLabel(tr("Fin:"));
    xFinSpinBox = UiUtils::createCoordinateSpinBox();
    yFinSpinBox = UiUtils::createCoordinateSpinBox();
    zFinSpinBox = UiUtils::createCoordinateSpinBox();

    QGroupBox *coordinatesGroup = new QGroupBox(tr("Coordinates"));
    QGridLayout *coordinatesLayout = new QGridLayout;
    coordinatesLayout->addWidget(posIniLabel, 0, 0);
    coordinatesLayout->addWidget(xLabel1, 0, 1);
    coordinatesLayout->addWidget(xIniSpinBox, 0, 2);
    coordinatesLayout->addWidget(yLabel1, 0, 3);
    coordinatesLayout->addWidget(yIniSpinBox, 0, 4);
    coordinatesLayout->addWidget(zLabel1, 0, 5);
    coordinatesLayout->addWidget(zIniSpinBox, 0, 6);
    coordinatesLayout->addWidget(posFinLabel, 1, 0);
    coordinatesLayout->addWidget(xLabel2, 1, 1);
    coordinatesLayout->addWidget(xFinSpinBox, 1, 2);
    coordinatesLayout->addWidget(yLabel2, 1, 3);
    coordinatesLayout->addWidget(yFinSpinBox, 1, 4);
    coordinatesLayout->addWidget(zLabel2, 1, 5);
    coordinatesLayout->addWidget(zFinSpinBox, 1, 6);

    coordinatesGroup->setLayout(coordinatesLayout);

    //Delay panel
    QGroupBox *delayGroup = new QGroupBox(tr("Delay"));
    delaySpinBox = new QDoubleSpinBox;
    //delaySpinBox->setPrefix(tr("Start after "));
    //delaySpinBox->setSuffix(tr(" milliseconds"));
    //delaySpinBox->setSpecialValueText(tr("Start immediatelly"));
    delaySpinBox->setSingleStep(.5);

    QVBoxLayout *delayLayout = new QVBoxLayout;
    delayLayout->addWidget(delaySpinBox);
    delayGroup->setLayout(delayLayout);

    QHBoxLayout *effectLayout = new QHBoxLayout;
    effectLayout->addWidget(effectIdLabel);
    effectLayout->addWidget(effectIdTxt);

    QHBoxLayout *objectLayout = new QHBoxLayout;
    objectLayout->addWidget(objectIdLabel);
    objectLayout->addWidget(objectCombo);

    QVBoxLayout *configLayout = new QVBoxLayout;
    configLayout->addLayout(effectLayout);
    configLayout->addLayout(objectLayout);
    configGroup->setLayout(configLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(configGroup);
    mainLayout->addWidget(coordinatesGroup);
    mainLayout->addWidget(delayGroup);
    mainLayout->addStretch(1);
    setLayout(mainLayout);

    this->vmtModel = vmtModel;
    if (ef != NULL && ef->getType() == POSITION_EFFECT)
        this->effect = (PositionEffect*) ef;
    else
        this->effect = NULL;

    loadEffect();
}

void PositionEffectPage::loadEffect(){
    if (this->effect != NULL){
        effectIdTxt->setText(QString(effect->getId().c_str()));
        UiUtils::setComboIndexForText(objectCombo, effect->getObject3D()->getId());
        xIniSpinBox->setValue(effect->getPosIni()[0]);
        yIniSpinBox->setValue(effect->getPosIni()[1]);
        zIniSpinBox->setValue(effect->getPosIni()[2]);
        xFinSpinBox->setValue(effect->getPosFin()[0]);
        yFinSpinBox->setValue(effect->getPosFin()[1]);
        zFinSpinBox->setValue(effect->getPosFin()[2]);

        delaySpinBox->setValue(effect->getDelay());
    } else {
        effectIdTxt->setText(QString(""));
        objectCombo->setCurrentIndex(-1);
        xIniSpinBox->setValue(0);
        yIniSpinBox->setValue(0);
        zIniSpinBox->setValue(0);
        xFinSpinBox->setValue(0);
        yFinSpinBox->setValue(0);
        zFinSpinBox->setValue(0);
        delaySpinBox->setValue(0);
    }
}

void PositionEffectPage::saveEffect(){
    QString objId = objectCombo->currentText();
    if (this->effect == NULL){
        this->vmtModel->addPositionEffect(effectIdTxt->text().toStdString(), objId.toStdString(),
                                          ofVec3f(xIniSpinBox->value(), yIniSpinBox->value(), zIniSpinBox->value()),
                                          ofVec3f(xFinSpinBox->value(), yFinSpinBox->value(), zFinSpinBox->value()),
                                          delaySpinBox->value());
    } else {
        this->effect->setId(effectIdTxt->text().toStdString());
        this->effect->setObject3D(this->vmtModel->getObject3D(objId.toStdString()));
        this->effect->setPosIni(ofVec3f(xIniSpinBox->value(), yIniSpinBox->value(), zIniSpinBox->value()));
        this->effect->setPosFin(ofVec3f(xFinSpinBox->value(), yFinSpinBox->value(), zFinSpinBox->value()));
        this->effect->setDelay(delaySpinBox->value());
    }
}

FadeEffectPage::FadeEffectPage(VmtModel *vmtModel, Effect *ef, QWidget *parent)
    : QWidget(parent)
{
    QGroupBox *configGroup = new QGroupBox(tr("Configuration"));
    QLabel *effectIdLabel = new QLabel(tr("Effect Id:"));
    effectIdTxt = new QLineEdit;
    QLabel *groupIdLabel = new QLabel(tr("Group Id:"));
    groupsCombo = new QComboBox;

    loadGroupsCombo(groupsCombo, vmtModel);

    //Colors panel
    QLabel *rLabel1 = new QLabel(tr("R:"));
    QLabel *rLabel2 = new QLabel(tr("R:"));
    QLabel *gLabel1 = new QLabel(tr("G:"));
    QLabel *gLabel2 = new QLabel(tr("G:"));
    QLabel *bLabel1 = new QLabel(tr("B:"));
    QLabel *bLabel2 = new QLabel(tr("B:"));
    QLabel *colorIniLabel = new QLabel(tr("Ini:"));
    rIniSpinBox = new QSpinBox();
    rIniSpinBox->setMaximum(255);
    gIniSpinBox = new QSpinBox();
    gIniSpinBox->setMaximum(255);
    bIniSpinBox = new QSpinBox();
    bIniSpinBox->setMaximum(255);
    QLabel *colorFinLabel = new QLabel(tr("Fin:"));
    rFinSpinBox = new QSpinBox();
    rFinSpinBox->setMaximum(255);
    gFinSpinBox = new QSpinBox();
    gFinSpinBox->setMaximum(255);
    bFinSpinBox = new QSpinBox();
    bFinSpinBox->setMaximum(255);

    QGroupBox *colorsGroup = new QGroupBox(tr("Colors"));
    QGridLayout *colorsLayout = new QGridLayout;
    colorIniButton = new QPushButton(tr("get&Color()"));
    colorFinButton = new QPushButton(tr("get&Color()"));
    colorsLayout->addWidget(colorIniLabel, 0, 0);
    colorsLayout->addWidget(rLabel1, 0, 1);
    colorsLayout->addWidget(rIniSpinBox, 0, 2);
    colorsLayout->addWidget(gLabel1, 0, 3);
    colorsLayout->addWidget(gIniSpinBox, 0, 4);
    colorsLayout->addWidget(bLabel1, 0, 5);
    colorsLayout->addWidget(bIniSpinBox, 0, 6);
    colorsLayout->addWidget(colorIniButton, 0, 7);
    colorsLayout->addWidget(colorFinLabel, 1, 0);
    colorsLayout->addWidget(rLabel2, 1, 1);
    colorsLayout->addWidget(rFinSpinBox, 1, 2);
    colorsLayout->addWidget(gLabel2, 1, 3);
    colorsLayout->addWidget(gFinSpinBox, 1, 4);
    colorsLayout->addWidget(bLabel2, 1, 5);
    colorsLayout->addWidget(bFinSpinBox, 1, 6);
    colorsLayout->addWidget(colorFinButton, 1, 7);

    colorsGroup->setLayout(colorsLayout);

    //Delay panel
    QGroupBox *delayGroup = new QGroupBox(tr("Delay"));
    delaySpinBox = new QDoubleSpinBox;
    //delaySpinBox->setPrefix(tr("Start after "));
    //delaySpinBox->setSuffix(tr(" milliseconds"));
    //delaySpinBox->setSpecialValueText(tr("Start immediatelly"));
    delaySpinBox->setSingleStep(.5);

    QVBoxLayout *delayLayout = new QVBoxLayout;
    delayLayout->addWidget(delaySpinBox);
    delayGroup->setLayout(delayLayout);

    QHBoxLayout *effectLayout = new QHBoxLayout;
    effectLayout->addWidget(effectIdLabel);
    effectLayout->addWidget(effectIdTxt);

    QHBoxLayout *objectLayout = new QHBoxLayout;
    objectLayout->addWidget(groupIdLabel);
    objectLayout->addWidget(groupsCombo);

    QVBoxLayout *configLayout = new QVBoxLayout;
    configLayout->addLayout(effectLayout);
    configLayout->addLayout(objectLayout);
    configGroup->setLayout(configLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(configGroup);
    mainLayout->addWidget(colorsGroup);
    mainLayout->addWidget(delayGroup);
    mainLayout->addStretch(1);
    setLayout(mainLayout);

    connect(colorIniButton, SIGNAL(clicked()), this, SLOT(setColorIni()));
    connect(colorFinButton, SIGNAL(clicked()), this, SLOT(setColorFin()));

    this->vmtModel = vmtModel;
    if (ef != NULL && ef->getType() == FADE_EFFECT)
        this->effect = (FadeEffect*) ef;
    else
        this->effect = NULL;

    loadEffect();
}

void FadeEffectPage::setColorIni()
{
    QColor color;
    QColor color2 = QColor(rIniSpinBox->value(),
                   gIniSpinBox->value(),
                   bIniSpinBox->value());
    //if (native->isChecked())
        color = QColorDialog::getColor(Qt::green, this);
        //color = QColorDialog::getColor(color2, this);
    //else
        //color = QColorDialog::getColor(Qt::green, this, "Select Color", QColorDialog::DontUseNativeDialog);

    if (color.isValid()) {
        rIniSpinBox->setValue(color.red());
        gIniSpinBox->setValue(color.green());
        bIniSpinBox->setValue(color.blue());
    }
}

void FadeEffectPage::setColorFin()
{
    QColor color;
    QColor color2 = QColor(rFinSpinBox->value(),
                   gFinSpinBox->value(),
                   bFinSpinBox->value());
    //if (native->isChecked())
        color = QColorDialog::getColor(Qt::green, this);
        //color = QColorDialog::getColor(color2, this);
    //else
        //color = QColorDialog::getColor(Qt::green, this, "Select Color", QColorDialog::DontUseNativeDialog);

    if (color.isValid()) {
        rFinSpinBox->setValue(color.red());
        gFinSpinBox->setValue(color.green());
        bFinSpinBox->setValue(color.blue());
    }
}


void FadeEffectPage::loadEffect(){
    if (this->effect != NULL){
        effectIdTxt->setText(QString(effect->getId().c_str()));
        UiUtils::setComboIndexForText(groupsCombo, effect->getQuadGroup()->getName());
        rIniSpinBox->setValue(effect->getColorIni()[0]);
        gIniSpinBox->setValue(effect->getColorIni()[1]);
        bIniSpinBox->setValue(effect->getColorIni()[2]);
        rFinSpinBox->setValue(effect->getColorFin()[0]);
        gFinSpinBox->setValue(effect->getColorFin()[1]);
        bFinSpinBox->setValue(effect->getColorFin()[2]);
        delaySpinBox->setValue(effect->getDelay());
    } else {
        effectIdTxt->setText(QString(""));
        groupsCombo->setCurrentIndex(-1);
        rIniSpinBox->setValue(0);
        gIniSpinBox->setValue(0);
        bIniSpinBox->setValue(0);
        rFinSpinBox->setValue(0);
        gFinSpinBox->setValue(0);
        bFinSpinBox->setValue(0);
        delaySpinBox->setValue(0);
    }
}

void FadeEffectPage::saveEffect(){
    QString grpId = groupsCombo->currentText();
    if (this->effect == NULL){
        this->vmtModel->addFadeEffect(effectIdTxt->text().toStdString(), grpId.toStdString(),
                                          ofVec4f(rIniSpinBox->value()/255.0f, gIniSpinBox->value()/255.0f, bIniSpinBox->value()/255.0f, 0),
                                          ofVec4f(rFinSpinBox->value()/255.0f, gFinSpinBox->value()/255.0f, bFinSpinBox->value()/255.0f, 1),
                                          delaySpinBox->value());
    } else {
        this->effect->setId(effectIdTxt->text().toStdString());
        this->effect->setQuadGroup(this->vmtModel->getGroup(grpId.toStdString()));
        this->effect->setColorIni(ofVec4f(rIniSpinBox->value()/255.0f, gIniSpinBox->value()/255.0f, bIniSpinBox->value()/255.0f, 0));
        this->effect->setColorFin(ofVec4f(rFinSpinBox->value()/255.0f, gFinSpinBox->value()/255.0f, bFinSpinBox->value()/255.0f, 1));
        this->effect->setDelay(delaySpinBox->value());
    }
}

TextureEffectPage::TextureEffectPage(VmtModel *vmtModel, Effect *ef, QWidget *parent)
    : QWidget(parent)
{
    QGroupBox *configGroup = new QGroupBox(tr("Configuration"));
    QLabel *effectIdLabel = new QLabel(tr("Effect Id:"));
    effectIdTxt = new QLineEdit;

    QLabel *groupIdLabel = new QLabel(tr("Group Id:"));
    groupsCombo = new QComboBox;
    loadGroupsCombo(groupsCombo, vmtModel);

    QLabel *objectIdLabel = new QLabel(tr("Object Id:"));
    objectCombo = new QComboBox;
    loadObjectsCombo(objectCombo, vmtModel);

    isGroupCheckBox = new QCheckBox(tr("Use Group?"));
    isVideoCheckBox = new QCheckBox(tr("Is Video?"));

    //Texture panel
    QLabel *keyLabel = new QLabel(tr("Texture key"));
    keyEdit = new QLineEdit();

    QGroupBox *textureGroup = new QGroupBox(tr("Texture"));
    QGridLayout *textureLayout = new QGridLayout;
    searchButton = new QPushButton(tr("Browse"));
    textureLayout->addWidget(keyLabel, 0, 0);
    textureLayout->addWidget(keyEdit, 0, 1);
    textureLayout->addWidget(searchButton, 0, 2);
    textureLayout->addWidget(isVideoCheckBox, 1, 0);

    textureGroup->setLayout(textureLayout);

    //Faces panel
    QGroupBox *facesGroup = new QGroupBox(tr("Faces"));
    facesCombo = new QComboBox;

    QVBoxLayout *facesLayout = new QVBoxLayout;
    facesLayout->addWidget(facesCombo);
    facesGroup->setLayout(facesLayout);

    QHBoxLayout *effectLayout = new QHBoxLayout;
    effectLayout->addWidget(effectIdLabel);
    effectLayout->addWidget(effectIdTxt);

    QHBoxLayout *objectLayout = new QHBoxLayout;
    objectLayout->addWidget(objectIdLabel);
    objectLayout->addWidget(objectCombo);

    QHBoxLayout *groupLayout = new QHBoxLayout;
    groupLayout->addWidget(groupIdLabel);
    groupLayout->addWidget(groupsCombo);

    QVBoxLayout *configLayout = new QVBoxLayout;
    configLayout->addLayout(effectLayout);
    configLayout->addWidget(isGroupCheckBox);
    configLayout->addLayout(objectLayout);
    configLayout->addLayout(groupLayout);
    configGroup->setLayout(configLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(configGroup);
    mainLayout->addWidget(textureGroup);
    mainLayout->addWidget(facesGroup);
    mainLayout->addStretch(1);
    setLayout(mainLayout);

    connect(searchButton, SIGNAL(clicked()), this, SLOT(setOpenFileName()));
    connect(objectCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(comboObjectsChanged(int)));
    connect(isGroupCheckBox, SIGNAL(stateChanged(int)), this, SLOT(checkboxGroupStateChanged(int)));
    connect(isVideoCheckBox, SIGNAL(stateChanged(int)), this, SLOT(checkboxVideoStateChanged(int)));

    this->vmtModel = vmtModel;
    if (ef != NULL && ef->getType() == TEXTURE_EFFECT)
        this->effect = (TextureEffect*) ef;
    else
        this->effect = NULL;

    loadEffect();
}

void TextureEffectPage::loadEffect(){
    if (this->effect != NULL){

        effectIdTxt->setText(QString(effect->getId().c_str()));

        isGroupCheckBox->setChecked(effect->getIsGroup());
        if (effect->getIsGroup()){
            UiUtils::setComboIndexForText(groupsCombo, effect->getGroup()->getName());
        } else {
            UiUtils::setComboIndexForText(objectCombo, effect->getObject3D()->getId());
            //facesEdit->setText(QString(effect->getFacesID().c_str()));
            UiUtils::setComboIndexForText(facesCombo, effect->getFacesID());
        }
        keyEdit->setText(QString(effect->getTextureKey().c_str()));

        if (effect->getTextureType() == VIDEO_TEXTURE){
            isVideoCheckBox->setChecked(true);
        } else { //tType = IMAGE_TEXTURE;
            isVideoCheckBox->setChecked(false);
        }
    } else {
        effectIdTxt->setText(QString(""));
        isGroupCheckBox->setChecked(false);
        checkboxGroupStateChanged(Qt::Unchecked);
        groupsCombo->setCurrentIndex(-1);
        objectCombo->setCurrentIndex(-1);
        facesCombo->setCurrentIndex(-1);
        keyEdit->setText(QString(""));
        isVideoCheckBox->setChecked(false);
    }
}

void TextureEffectPage::saveEffect(){
    QString objId = objectCombo->currentText();
    QString grpId = groupsCombo->currentText();

    bool isGroup = isGroupCheckBox->isChecked();
    bool isVideoTexture = isVideoCheckBox->isChecked();

    textureType tType;
    if (isVideoTexture){
        tType = VIDEO_TEXTURE;
    } else {
        tType = IMAGE_TEXTURE;
    }

    if (this->effect == NULL){

        if (isGroup){
            this->vmtModel->addTextureGroupEffect(effectIdTxt->text().toStdString(), grpId.toStdString(),
                                                  keyEdit->text().toStdString(),
                                                  tType);
        } else {
            QString facesId = facesCombo->currentText();
            this->vmtModel->addTextureObjectEffect(effectIdTxt->text().toStdString(), objId.toStdString(),
                                                  facesId.toStdString(), keyEdit->text().toStdString(),
                                                   tType);
        }

    } else {
        this->effect->setId(effectIdTxt->text().toStdString());
        if (isGroup){
            this->effect->setGroup(this->vmtModel->getGroup(grpId.toStdString()));
        } else {
            QString facesId = facesCombo->currentText();
            this->effect->setObject3D(this->vmtModel->getObject3D(objId.toStdString()));
            this->effect->setFacesID(facesId.toStdString());
        }
        this->effect->setTextureKey(keyEdit->text().toStdString());
        this->effect->setTextureType(tType);
    }
}

void TextureEffectPage::setOpenFileName()
{
    QFileDialog::Options options;
    //if (!native->isChecked())
    //    options |= QFileDialog::DontUseNativeDialog;
    QString selectedFilter;
    QString fileName = QFileDialog::getOpenFileName(this,
                                tr("QFileDialog::getOpenFileName()"),
                                keyEdit->text(),
                                tr("All Files (*);;Text Files (*.txt)"),
                                &selectedFilter,
                                options);
    if (!fileName.isEmpty())
        keyEdit->setText(fileName);
}

void TextureEffectPage::checkboxGroupStateChanged(int changeState){
    if (changeState == Qt::Unchecked) { //Qt::Unchecked	0
        groupsCombo->setCurrentIndex(-1);
        objectCombo->setDisabled(false);
        facesCombo->setDisabled(false);
        groupsCombo->setDisabled(true);
    //} else if (changeState == Qt::PartiallyChecked) { //Qt::PartiallyChecked	1
    } else if (changeState == Qt::Checked) { //Qt::Checked	2
        objectCombo->setCurrentIndex(-1);
        objectCombo->setDisabled(true);
        facesCombo->setDisabled(true);
        groupsCombo->setDisabled(false);
    }
}

void TextureEffectPage::checkboxVideoStateChanged(int changeState){
}

void TextureEffectPage::comboObjectsChanged(int index){
    UiUtils::clearCombo(facesCombo);
    if (index != -1){
        QString objId = objectCombo->currentText();
        vector<string> mats = this->vmtModel->getObject3D(objId.toStdString())->getMaterialNames();
        vector<string>::iterator matsIt;
        for(matsIt = mats.begin(); matsIt != mats.end(); matsIt++) {
            facesCombo->addItem((*matsIt).c_str());
        }
    }
}

void loadGroupsCombo(QComboBox *combo, VmtModel *vmtModel){
    map<string, QuadGroup*>::iterator it;
    map<string, QuadGroup*> qMap = vmtModel->getGroups();
    for(it = qMap.begin(); it != qMap.end(); it++) {
        QuadGroup* gr = (QuadGroup*) it->second;
        combo->addItem(gr->getName().c_str());
    }
}

void loadObjectsCombo(QComboBox *combo, VmtModel *vmtModel){
    map<string, Object3D*>::iterator objects3DIt;
    map<string, Object3D*> objsMap = vmtModel->getObjects3D();
    for(objects3DIt = objsMap.begin(); objects3DIt != objsMap.end(); objects3DIt++) {
        Object3D *obj = (Object3D*) objects3DIt->second;
        combo->addItem(obj->getId().c_str());
    }
}
