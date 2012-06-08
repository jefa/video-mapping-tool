#include "midieffectitem.h"

#include <QColor>

using namespace gui;

//! [0]
midiEffectItem::midiEffectItem(string idEffect , int id, int value)
{
    this->id = id;
    this->value = value;
    this->idEffect = idEffect;

}
//! [0]

//! [1]
midiEffectItem::~midiEffectItem()
{
}
//! [1]

//! [6]
QVariant midiEffectItem::data(int column) //const
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
bool midiEffectItem::setData(int column, const QVariant &value)
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

int midiEffectItem::getItemData(){
    return this->id;
}
string midiEffectItem::getIdEffect(){
    return this->idEffect;
}
int midiEffectItem::getValueData(){
    return this->value;
}
