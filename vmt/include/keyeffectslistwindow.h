#ifndef KEYEFFECTSLISTWINDOW_H
#define KEYEFFECTSLISTWINDOW_H

#include "vmtmodel.h"
#include "keyeffectitem.h"
#include "keyeffectslistmodel.h"
#include "keyeffecteditdialog.h"

#include <QModelIndex>
#include <QWidget>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QPushButton>
#include <QString>
#include <QTime>
#include <QCoreApplication>

class QAction;
class QListView;

namespace gui {

class keyEffectsListWindow : public QWidget
{
    Q_OBJECT

public:
    keyEffectsListWindow(VmtModel *vmtModel);
    ~keyEffectsListWindow();

public slots:
    void effectsChanged();
    void clickedList(const QModelIndex &index);
    void doubleClickedList(const QModelIndex &index);
    void newEffect();
    void removeEffect();

private slots:

private:
    void setupUi(QWidget *);
    void retranslateUi(QWidget *);
    keyEffectsListModel* getListViewModel();

public:
    //QVBoxLayout *vboxLayout;

    QPushButton *newEffectAction;
    QPushButton *removeEffectAction;

    QListView *view;

    keyEffecteditdialog *keyeffecteditdialog;

    keyEffectItem *selectedItem;
};

}

#endif
