#include "keyeffectitem.h"

#include <QColor>

using namespace gui;

//! [0]
keyEffectItem::keyEffectItem(string idEffect , char keyid)
{
    this->key = keyid;
    this->idEffect = idEffect;

}
//! [0]

//! [1]
keyEffectItem::~keyEffectItem()
{
}
//! [1]

//! [6]
QVariant keyEffectItem::data(int column) //const
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
bool keyEffectItem::setData(int column, const QVariant &value)
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

char keyEffectItem::getItemData(){
    return this->key;
}

string keyEffectItem::getIdEffect(){
    return this->idEffect;
}
