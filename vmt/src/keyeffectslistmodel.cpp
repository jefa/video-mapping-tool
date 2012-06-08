#include <QtGui>
#include <QVariant>
#include "keyeffectslistmodel.h"


using namespace gui;

//! [0]
keyEffectsListModel::keyEffectsListModel(VmtModel *vmtModel, QObject *parent)
    : QAbstractItemModel(parent)
{
    this->vmtModel = vmtModel;
    setupModelData();
}
//! [0]

//! [1]
keyEffectsListModel::~keyEffectsListModel()
{
    //delete rootItem;
}
//! [1]

//! [2]
void keyEffectsListModel::setupModelData()
{
    //beginInsertRows();
    this->listItems.clear();
    map<char, string>::iterator keyeffectsIt;
    map<char, string> keyeffectsMap = this->vmtModel->getKeyEffects();
    for(keyeffectsIt = keyeffectsMap.begin(); keyeffectsIt != keyeffectsMap.end(); keyeffectsIt++) {
        keyEffectItem *lItem = new keyEffectItem(keyeffectsIt->second, keyeffectsIt->first);
        this->listItems.push_back(lItem);
    }
    emit layoutChanged();
    //endInsertRows();
}

VmtModel * keyEffectsListModel::getVmtModel(){
    return this->vmtModel;
}

QModelIndex keyEffectsListModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();

    return createIndex(row, column);
}

QModelIndex keyEffectsListModel::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

QVariant keyEffectsListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    keyEffectItem *item = getItem(index);

    return item->data(index.column());
}

keyEffectItem *keyEffectsListModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        keyEffectItem *item = this->listItems[index.row()];
        if (item) return item;
    }
    return getItem(QModelIndex());
}

int keyEffectsListModel::rowCount(const QModelIndex &parent) const
{
    return this->vmtModel->getKeyEffects().size();
}

int keyEffectsListModel::columnCount(const QModelIndex & parent ) const
{
    return 1;
}
void keyEffectsListModel::removeKeyEffect(char key, string effectId){

    this->vmtModel->removeKeyEvent(key,effectId);
    setupModelData();
}
