#ifndef EFFECTITEM_H
#define EFFECTITEM_H

#include "Effect.h"

#include <QList>
#include <QVariant>
#include <QVector>

using namespace std;

namespace gui {

//! [0]
class EffectItem
{
public:
    EffectItem(Effect *data = 0, string label = 0);
    ~EffectItem();

    QVariant data(int column) /*const*/;
    bool setData(int column, const QVariant &value);
    Effect* getItemData();

private:
    string itemLabel;
    Effect *itemData;
};
//! [0]

}
#endif
