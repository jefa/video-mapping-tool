#ifndef EFFECTSLISTMODEL_H
#define EFFECTSLISTMODEL_H

#include "vmtmodel.h"
#include "effectitem.h"

#include <vector>

namespace gui {

//! [0]
class EffectsListModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    EffectsListModel(VmtModel *vmtModel, QObject *parent = 0);
    ~EffectsListModel();

    QModelIndex index(int row, int column,
                              const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const ;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const ;

    EffectItem *getItem(const QModelIndex &index) const;
    VmtModel *getVmtModel();

    void setupModelData();

private:
    VmtModel *vmtModel;
    vector<EffectItem*> listItems;
};
//! [2]

}
#endif
