#ifndef KEYEFFECTSLISTMODEL_H
#define KEYEFFECTSLISTMODEL_H

#include "keyeffectitem.h"
#include "vmtmodel.h"

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include <vector>

namespace gui {

//! [0]
class keyEffectsListModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    keyEffectsListModel(VmtModel *vmtModel, QObject *parent = 0);
    ~keyEffectsListModel();

    QModelIndex index(int row, int column,
                              const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const ;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const ;

    keyEffectItem *getItem(const QModelIndex &index) const;
    VmtModel *getVmtModel();

    void setupModelData();
    void removeKeyEffect(char key, string effectId);

private:
    VmtModel *vmtModel;
    vector<keyEffectItem*> listItems;
};
//! [2]

}
#endif
