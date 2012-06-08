#ifndef EVTEFFECTSLISTMODEL_H
#define EVTEFFECTSLISTMODEL_H

#include "evteffectitem.h"
#include "vmtmodel.h"

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include <vector>

namespace gui {

//! [0]
class evtEffectsListModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    evtEffectsListModel(VmtModel *vmtModel, QObject *parent = 0);
    ~evtEffectsListModel();

    QModelIndex index(int row, int column,
                              const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const ;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const ;
    void removeTimeEffect(float time, string effectId);

    evtEffectItem *getItem(const QModelIndex &index) const;
    VmtModel *getVmtModel();

    void setupModelData();

private:
    VmtModel *vmtModel;
    vector<evtEffectItem*> listItems;
};
//! [2]

}
#endif
