#ifndef EFFECTPAGES_H
#define EFFECTPAGES_H

#include "vmtmodel.h"
#include "Effect.h"
#include "PositionEffect.h"
#include "FadeEffect.h"
#include "TextureEffect.h"

//#include <QtGui>

void setComboIndexForText(QComboBox *combo, string txt);
void loadGroupsCombo(QComboBox *combo, VmtModel *vmtModel);
void loadObjectsCombo(QComboBox *combo, VmtModel *vmtModel);

class PositionEffectPage : public QWidget
{
public:
    PositionEffectPage(VmtModel *vmtModel, Effect *ef, QWidget *parent = 0);
    void saveEffect();

private:
    void loadEffect();

    PositionEffect *effect;
    VmtModel *vmtModel;

    QLineEdit *effectIdTxt;
    QComboBox *objectCombo;
    QDoubleSpinBox *xIniSpinBox;
    QDoubleSpinBox *yIniSpinBox;
    QDoubleSpinBox *zIniSpinBox;
    QDoubleSpinBox *xFinSpinBox;
    QDoubleSpinBox *yFinSpinBox;
    QDoubleSpinBox *zFinSpinBox;
    QDoubleSpinBox *delaySpinBox;

};

class FadeEffectPage : public QWidget
{
    Q_OBJECT

public:
    FadeEffectPage(VmtModel *vmtModel, Effect *ef, QWidget *parent = 0);
    void saveEffect();

public slots:
    void setColorIni();
    void setColorFin();

private:
    void loadEffect();

    FadeEffect *effect;
    VmtModel *vmtModel;

    QPushButton *colorIniButton;
    QPushButton *colorFinButton;
    QLineEdit *effectIdTxt;
    QComboBox *groupsCombo;
    QSpinBox *rIniSpinBox;
    QSpinBox *gIniSpinBox;
    QSpinBox *bIniSpinBox;
    QSpinBox *rFinSpinBox;
    QSpinBox *gFinSpinBox;
    QSpinBox *bFinSpinBox;
    QDoubleSpinBox *delaySpinBox;
};

class TextureEffectPage : public QWidget
{
    Q_OBJECT

public:
    TextureEffectPage(VmtModel *vmtModel, Effect *ef, QWidget *parent = 0);
    void saveEffect();

public slots:
    void setOpenFileName();
    void checkboxGroupStateChanged(int);
    void checkboxVideoStateChanged(int);
    void comboObjectsChanged(int);

private:
    void loadEffect();

    TextureEffect *effect;
    VmtModel *vmtModel;

    QPushButton *searchButton;
    QLineEdit *effectIdTxt;
    QComboBox *objectCombo;
    QComboBox *groupsCombo;
    QCheckBox *isGroupCheckBox;
    QCheckBox *isVideoCheckBox;
    QLineEdit *keyEdit;
    QComboBox *facesCombo;
};

#endif
