#include <QtGui>

#include "keyeffectslistwindow.h"

using namespace gui;

keyEffectsListWindow::keyEffectsListWindow(VmtModel *vmtModel)
{
    this->selectedItem = NULL;
    this->keyeffecteditdialog= new keyEffecteditdialog(vmtModel);

    setupUi(this);

    keyEffectsListModel *model = new keyEffectsListModel(vmtModel, NULL);
    view->setModel(model);

    connect(view, SIGNAL(clicked(QModelIndex)), this, SLOT(clickedList(QModelIndex)));
	connect(view, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(doubleClickedList(QModelIndex)));

	connect(keyeffecteditdialog, SIGNAL(dataChanged()), this, SLOT(effectsChanged()));

    connect(newEffectAction, SIGNAL(clicked()), this, SLOT(newEffect()));
    connect(removeEffectAction, SIGNAL(clicked()), this, SLOT(removeEffect()));

}

keyEffectsListWindow::~keyEffectsListWindow()
{
    delete(selectedItem);
    delete(keyeffecteditdialog);
}

void keyEffectsListWindow::setupUi(QWidget *listWindow)
{
    if (listWindow->objectName().isEmpty())
        listWindow->setObjectName(QString::fromUtf8("listWindow3"));
    //listWindow->resize(200, 450);
    //listWindow->move(ofGetScreenWidth()-800,40);
    QVBoxLayout *vboxLayout = new QVBoxLayout(listWindow);
    //vboxLayout->setSpacing(0);
    //vboxLayout->setContentsMargins(0, 0, 0, 0);
    //vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    view = new QListView(listWindow);
    view->setObjectName(QString::fromUtf8("view"));
    view->setAlternatingRowColors(true);
    view->setSelectionBehavior(QAbstractItemView::SelectItems);
    view->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);

    vboxLayout->addWidget(view);

    newEffectAction = new QPushButton();
    newEffectAction->setObjectName(QString::fromUtf8("newEffectAction"));
    removeEffectAction = new QPushButton();
    removeEffectAction->setObjectName(QString::fromUtf8("removeEffectAction"));

    vboxLayout->addWidget(newEffectAction);
    vboxLayout->addWidget(removeEffectAction);

    retranslateUi(listWindow);

} // setupUi

void keyEffectsListWindow::retranslateUi(QWidget *listWindow)
{
    listWindow->setWindowTitle(QApplication::translate("listWindow3", "KeyEvents-Effects", 0, QApplication::UnicodeUTF8));

    newEffectAction->setText(QApplication::translate("treeWindow", "New", 0, QApplication::UnicodeUTF8));
    removeEffectAction->setText(QApplication::translate("treeWindow", "Remove", 0, QApplication::UnicodeUTF8));


} // retranslateUi


void keyEffectsListWindow::clickedList(const QModelIndex &index)
{
    keyEffectsListModel *model = (keyEffectsListModel*) view->model();
    this->selectedItem = model->getItem(index);
}

void keyEffectsListWindow::doubleClickedList(const QModelIndex &index)
{
    keyeffecteditdialog->show();
    keyeffecteditdialog->Init(this->selectedItem->getItemData(),this->selectedItem->getIdEffect());
    effectsChanged();

}

void keyEffectsListWindow::newEffect(){

    keyeffecteditdialog->show();
    effectsChanged();
}

void keyEffectsListWindow::removeEffect(){
    if (this->selectedItem == NULL)
        return;
    keyEffectsListModel *model = (keyEffectsListModel*) view->model();
    model->removeKeyEffect(this->selectedItem->getItemData(),this->selectedItem->getIdEffect());

    view->update();
    this->repaint();

}


keyEffectsListModel* keyEffectsListWindow::getListViewModel(){
    return (keyEffectsListModel*) view->model();
}

void keyEffectsListWindow::effectsChanged(){
    keyEffectsListModel *model = (keyEffectsListModel*) view->model();
    model->setupModelData();
    view->update();
    this->repaint();
}
