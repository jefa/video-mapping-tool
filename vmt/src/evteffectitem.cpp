#include "evteffectitem.h"

#include <QColor>

using namespace gui;

//! [0]
evtEffectItem::evtEffectItem(string idEffect , float Time )
{
    this->evtTime = Time;
    this->idEffect = idEffect;

}
//! [0]

//! [1]
evtEffectItem::~evtEffectItem()
{
}
//! [1]

//! [6]
QVariant evtEffectItem::data(int column) //const
{
    if (idEffect != "") { //is root
        if (column == 0)
            return QVariant(QString(idEffect.c_str()));
        if (column == 1)
            return QVariant(QString(""));
    }
    return QVariant(QString(""));
}
//! [6]


//! [11]
bool evtEffectItem::setData(int column, const QVariant &value)
{
    //cout<< " set data: "<<column << &value ;
    if (column < 0 || column >= /*itemData.size()*/2)
        return false;

    if (idEffect == "")
        return false;

    idEffect = value.toString().toStdString();

    return true;
}
//! [11]

float evtEffectItem::getItemData(){
    return this->evtTime;
}
string evtEffectItem::getIdEffect(){
    return this->idEffect;
}
