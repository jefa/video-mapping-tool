#ifndef MIDIEFFECTITEM_H
#define MIDIEFFECTITEM_H


#include <QList>
#include <QVariant>
#include <QVector>
#include <QTime>

using namespace std;

namespace gui {

//! [0]
class midiEffectItem {
public:
    midiEffectItem(string idEffect = "", int id=0, int value=0);
    ~midiEffectItem();

    QVariant data(int column) /*const*/;
    bool setData(int column, const QVariant &value);
    int getItemData();
    string getIdEffect();
    int getValueData();


private:
    int id, value;
    string idEffect;

};
//! [0]

}
#endif
