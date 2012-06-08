#ifndef TREEITEM_H
#define TREEITEM_H

#include "Scene.h"
#include "Layer2D.h"
#include "Quad2D.h"
#include "ofxCamera.h"
#include "ofxLight.h"
#include "OscManager.h"


#include <QList>
#include <QVariant>
#include <QVector>

using namespace std;


namespace gui {

class TreeItemData;

//! [0]
class TreeItem
{
public:
    TreeItem(TreeItemData *data = 0, TreeItem *parent = 0,
            string label = 0);
    ~TreeItem();

    TreeItem *child(int number);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) /*const*/;
    bool insertChildren(int position, int count, /*int columns*/ TreeItemData *itemData, string label = 0 );
    bool insertColumns(int position, int columns);
    TreeItem *parent();
    bool removeChildren(int position, int count);
    bool removeColumns(int position, int columns);
    int childNumber() const;
    bool setData(int column, const QVariant &value);
    bool setSeleted(Scene *scene);
    TreeItemData* getItemData();

private:
    string itemLabel;
    QList<TreeItem*> childItems;
    TreeItemData *itemData;
    TreeItem *parentItem;
};
//! [0]

class TreeItemData {
    public:
    virtual QVariant getData(int column)=0;
    virtual void setData(int column, QVariant colValue)=0;
    virtual bool setSeleted(Scene *scene)=0;

    //int getItemID();

    //protected:
    int itemId;

};

class CameraItemData : public TreeItemData {

    public:
    CameraItemData(ofxCamera *camera);
    ~CameraItemData();

    QVariant getData(int column);
    void setData(int column, QVariant colValue);
    bool setSeleted(Scene *scene);

    private:
    ofxCamera *camera;
};
class LightItemData : public TreeItemData {

    public:
    LightItemData(ofxLight *light);
    ~LightItemData();

    QVariant getData(int column);
    void setData(int column, QVariant colValue);
    bool setSeleted(Scene *scene);

    private:
    ofxLight *light;
};

class LayerItemData : public TreeItemData {

    public:
    LayerItemData(Layer2D *layer2D);
    ~LayerItemData();

    QVariant getData(int column);
    void setData(int column, QVariant colValue);
    bool setSeleted(Scene *scene);

    private:
    Layer2D *layer;
};

class QuadItemData : public TreeItemData {

    public:
    QuadItemData(Quad2D *quad2D);
    ~QuadItemData();

    QVariant getData(int column);
    void setData(int column, QVariant colValue);
    bool setSeleted(Scene *scene);

    private:
    Quad2D *quad2d;
};


class ObjectItemData : public TreeItemData {

    public:
    ObjectItemData(Object3D *object3d);
    ~ObjectItemData();

    QVariant getData(int column);
    void setData(int column, QVariant colValue);
    bool setSeleted(Scene *scene);

    private:
    Object3D *object3d;
};


class NodeItemData : public TreeItemData {

    public:
    NodeItemData(Node *nodeobj);
    ~NodeItemData();

    QVariant getData(int column);
    void setData(int column, QVariant colValue);
    bool setSeleted(Scene *scene);

    private:
    Node *node;

};

}
#endif
