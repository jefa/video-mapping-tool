#ifndef EFFECTSLISTWINDOW_H
#define EFFECTSLISTWINDOW_H

#include "vmtmodel.h"
#include "effectitem.h"
#include "effectslistmodel.h"
#include "effecteditdialog.h"

#include <QModelIndex>
#include <QWidget>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QPushButton>
#include <QString>
#include <QCoreApplication>

class QAction;
class QListView;

namespace gui {

class EffectsListWindow : public QWidget
{
    Q_OBJECT

public:
    EffectsListWindow(VmtModel *vmtModel);
    ~EffectsListWindow();

public slots:
    void effectsChanged();
    void clickedList(const QModelIndex &index);
    void doubleClickedList(const QModelIndex &index);
    void newEffect();
    void editEffect();
    void removeEffect();
    void testEffect();

private slots:

private:
    void setupUi(QWidget *);
    void retranslateUi(QWidget *);
    EffectsListModel* getListViewModel();

public:
    QVBoxLayout *vboxLayout;
    QGridLayout *layout;

    QPushButton *newEffectAction;
    QPushButton *editEffectAction;
    QPushButton *removeEffectAction;
    QPushButton *testEffectAction;

    QListView *view;


    EffectEditDialog *effectEditDialog;

    EffectItem *selectedItem;
};

}

#endif
