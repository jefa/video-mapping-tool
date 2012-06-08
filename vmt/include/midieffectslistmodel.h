#ifndef MIDIEFFECTSLISTMODEL_H
#define MIDIEFFECTSLISTMODEL_H

#include "midieffectitem.h"
#include "vmtmodel.h"

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include <vector>

namespace gui {

//! [0]
class midiEffectsListModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    midiEffectsListModel(VmtModel *vmtModel, QObject *parent = 0);
    ~midiEffectsListModel();

    QModelIndex index(int row, int column,
                              const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const ;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const ;
    void removeMidiEffect(ofxMidiEventArgs * MidiMsg, string effectId);

    midiEffectItem *getItem(const QModelIndex &index) const;
    VmtModel *getVmtModel();

    void setupModelData();

private:
    VmtModel *vmtModel;
    vector<midiEffectItem*> listItems;
};
//! [2]

}
#endif
