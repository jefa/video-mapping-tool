#ifndef TREEMODEL_H
#define TREEMODEL_H

#include "vmtmodel.h"

namespace gui {

class TreeItem;

//! [0]
class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    TreeModel(VmtModel *vmtModel, QObject *parent = 0);
    ~TreeModel();
//! [0] //! [1]

    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
//! [1]

//! [2]
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole);
    bool setHeaderData(int section, Qt::Orientation orientation,
                       const QVariant &value, int role = Qt::EditRole);

    bool insertColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex());
    bool removeColumns(int position, int columns,
                      const QModelIndex &parent = QModelIndex());
    //bool addElement(int position, int rows,
    //                const QModelIndex &parent = QModelIndex());
    string ObtType(const QModelIndex &parent);
    QString inputText(string defaultValue);
    bool insertRows(int position, int rows,
                    const QModelIndex &index = QModelIndex(), string Name = "");
    bool removeRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex());

    TreeItem *getItem(const QModelIndex &index) const;
    bool addObject3D(int position, int rows, const QModelIndex &index, string name, string path);
    VmtModel *getVmtModel();

private:
    void setupSceneModelData();
    void setupLayersModelData(TreeItem *parent);
    void setupObjectsModelData(TreeItem *parent);
    void setupLightsModelData(TreeItem *parent);
    void setupNodesModelData(TreeItem *parent);

    TreeItem *rootItem;
    VmtModel *vmtModel;
};
//! [2]

}
#endif
