#ifndef EVTEFFECTITEM_H
#define EVTEFFECTITEM_H


#include <QList>
#include <QVariant>
#include <QVector>
#include <QTime>

using namespace std;

namespace gui {

//! [0]
class evtEffectItem
{
public:
    evtEffectItem(string idEffect = "", float Time = 0 );
    ~evtEffectItem();

    QVariant data(int column) /*const*/;
    bool setData(int column, const QVariant &value);
    float getItemData();
    string getIdEffect();

private:
    float evtTime;
    string idEffect;
};
//! [0]

}
#endif
