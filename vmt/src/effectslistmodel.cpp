#include <QtGui>
#include <QVariant>
#include "effectslistmodel.h"

using namespace gui;

//! [0]
EffectsListModel::EffectsListModel(VmtModel *vmtModel, QObject *parent)
    : QAbstractItemModel(parent)
{
    this->vmtModel = vmtModel;
    setupModelData();
}
//! [0]

//! [1]
EffectsListModel::~EffectsListModel()
{
    //delete rootItem;
}
//! [1]

//! [2]
void EffectsListModel::setupModelData()
{
    //beginInsertRows();

    this->listItems.clear();
    map<string, Effect*>::iterator effectsIt;
    map<string, Effect*> effectsMap = this->vmtModel->getEffects();
    for(effectsIt = effectsMap.begin(); effectsIt != effectsMap.end(); effectsIt++) {
        EffectItem *lItem = new EffectItem(effectsIt->second, effectsIt->first);
        this->listItems.push_back(lItem);
    }

    emit layoutChanged();
    //endInsertRows();
}

VmtModel * EffectsListModel::getVmtModel(){
    return this->vmtModel;
}

QModelIndex EffectsListModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();

    return createIndex(row, column);
}

QModelIndex EffectsListModel::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

QVariant EffectsListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    EffectItem *item = getItem(index);

    return item->data(index.column());
}

EffectItem *EffectsListModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        //ListItem *item = static_cast<ListItem*>(index.internalPointer());
        EffectItem *item = this->listItems[index.row()];
        if (item) return item;
    }
    return getItem(QModelIndex());
}

int EffectsListModel::rowCount(const QModelIndex &parent) const
{
    return this->vmtModel->getEffects().size();
}

int EffectsListModel::columnCount(const QModelIndex & parent ) const
{
    return 1;
}
