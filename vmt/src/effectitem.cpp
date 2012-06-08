#include <QtGui>

#include "effectitem.h"

using namespace gui;

//! [0]
EffectItem::EffectItem(Effect *data, string label)
{
    itemData = data;
    itemLabel = label;
}
//! [0]

//! [1]
EffectItem::~EffectItem()
{
}
//! [1]

//! [6]
QVariant EffectItem::data(int column) //const
{
    if (itemData != NULL) { //is root
        if (column == 0)
            return QVariant(QString(itemData->toString()));
        if (column == 1)
            return QVariant(QString(""));
    }
    return QVariant(QString(itemLabel.c_str()));
}
//! [6]


//! [11]
bool EffectItem::setData(int column, const QVariant &value)
{
    //cout<< " set data: "<<column << &value ;
    if (column < 0 || column >= /*itemData.size()*/2)
        return false;

    if (itemData == NULL)
        return false;

    //itemData[column] = value;
    //itemData->setData(column, value);
    return true;
}
//! [11]

Effect* EffectItem::getItemData(){
    return this->itemData;
}
