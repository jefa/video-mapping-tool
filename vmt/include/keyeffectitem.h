#ifndef KEYEFFECTITEM_H
#define KEYEFFECTITEM_H


#include <QList>
#include <QVariant>
#include <QVector>
#include <QTime>

using namespace std;

namespace gui {

//! [0]
class keyEffectItem
{
public:
    keyEffectItem(string idEffect = "", char key ='a');
    ~keyEffectItem();

    QVariant data(int column) /*const*/;
    bool setData(int column, const QVariant &value);
    char getItemData();
    string getIdEffect();

private:
    char key;
    string idEffect;
};
//! [0]

}
#endif
