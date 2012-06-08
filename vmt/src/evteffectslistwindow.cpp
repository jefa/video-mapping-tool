#include <QtGui>

#include "evteffectslistwindow.h"

using namespace gui;

evtEffectsListWindow::evtEffectsListWindow(VmtModel *vmtModel)
{
    this->selectedItem = NULL;
    this->evteffecteditdialog= new evtEffecteditdialog(vmtModel);

    evteffectsWindkey = new keyEffectsListWindow(vmtModel);
    midiEffectsWindkey = new midiEffectsListWindow(vmtModel);

    this->timeLine = new timeline(vmtModel);

    setupUi(this);

    evtEffectsListModel *model = new evtEffectsListModel(vmtModel, NULL);
    view->setModel(model);

    connect(view, SIGNAL(clicked(QModelIndex)), this, SLOT(clickedList(QModelIndex)));
	connect(view, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(doubleClickedList(QModelIndex)));

	connect(evteffecteditdialog, SIGNAL(dataChanged()), this, SLOT(effectsChanged()));

    connect(newEffectAction, SIGNAL(clicked()), this, SLOT(newEffect()));
    connect(removeEffectAction, SIGNAL(clicked()), this, SLOT(removeEffect()));

}

evtEffectsListWindow::~evtEffectsListWindow()
{
    delete(selectedItem);
    delete(evteffecteditdialog);
}

void evtEffectsListWindow::setupUi(QWidget *listWindow)
{
    if (listWindow->objectName().isEmpty())
        listWindow->setObjectName(QString::fromUtf8("listWindow2"));
    listWindow->resize(300, 430);
    listWindow->move(50, 500);
    QVBoxLayout *vboxLayout = new QVBoxLayout(listWindow);
    //vboxLayout->setSpacing(0);
    //vboxLayout->setContentsMargins(0, 0, 0, 0);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout2"));

    QGroupBox *teventsGroup = new QGroupBox(tr("Timed events"));
    QVBoxLayout *teventsLayout = new QVBoxLayout();

    view = new QListView(listWindow);
    view->setObjectName(QString::fromUtf8("view2"));
    view->setAlternatingRowColors(true);
    view->setSelectionBehavior(QAbstractItemView::SelectItems);
    view->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);

    newEffectAction = new QPushButton();
    newEffectAction->setObjectName(QString::fromUtf8("newEffectAction"));
    removeEffectAction = new QPushButton();
    removeEffectAction->setObjectName(QString::fromUtf8("removeEffectAction"));

    //vboxLayout->addWidget(view);
    teventsLayout->addWidget(view);
    teventsLayout->addWidget(newEffectAction);
    teventsLayout->addWidget(removeEffectAction);
    teventsGroup->setLayout(teventsLayout);

    QGroupBox *keventsGroup = new QGroupBox(tr("Key events"));
    QVBoxLayout *keventsLayout = new QVBoxLayout();
    keventsLayout->addWidget(evteffectsWindkey);
    keventsGroup->setLayout(keventsLayout);

    QGroupBox *meventsGroup = new QGroupBox(tr("Midi events"));
    QVBoxLayout *meventsLayout = new QVBoxLayout();
    meventsLayout->addWidget(midiEffectsWindkey);
    meventsGroup->setLayout(meventsLayout);

    QHBoxLayout *eventsLayout = new QHBoxLayout();
    eventsLayout->addWidget(teventsGroup);
    eventsLayout->addWidget(keventsGroup);
    eventsLayout->addWidget(meventsGroup);

    QGroupBox *timelineGroup = new QGroupBox(tr("Scene timeline"));
    QVBoxLayout *timelineLayout = new QVBoxLayout();
    timelineLayout->addWidget(timeLine);
    timelineGroup->setLayout(timelineLayout);

    //vboxLayout->addWidget(teventsGroup);
    vboxLayout->addLayout(eventsLayout);
    //vboxLayout->addWidget(newEffectAction);
    //vboxLayout->addWidget(removeEffectAction);
    vboxLayout->addWidget(timelineGroup);

    retranslateUi(listWindow);

} // setupUi

void evtEffectsListWindow::retranslateUi(QWidget *listWindow)
{
    listWindow->setWindowTitle(QApplication::translate("listWindow2", "Events-Effects", 0, QApplication::UnicodeUTF8));

    newEffectAction->setText(QApplication::translate("treeWindow", "New", 0, QApplication::UnicodeUTF8));
    removeEffectAction->setText(QApplication::translate("treeWindow", "Remove", 0, QApplication::UnicodeUTF8));


} // retranslateUi


void evtEffectsListWindow::clickedList(const QModelIndex &index)
{
    evtEffectsListModel *model = (evtEffectsListModel*) view->model();
    this->selectedItem = model->getItem(index);
}

void evtEffectsListWindow::doubleClickedList(const QModelIndex &index)
{

    evteffecteditdialog->show();
    evteffecteditdialog->Init(this->selectedItem->getItemData(),this->selectedItem->getIdEffect());
    effectsChanged();
}

void evtEffectsListWindow::newEffect(){

    evteffecteditdialog->show();
}

void evtEffectsListWindow::removeEffect(){
    if (this->selectedItem == NULL)
        return;
    evtEffectsListModel *model = (evtEffectsListModel*) view->model();
    model->removeTimeEffect(this->selectedItem->getItemData(),this->selectedItem->getIdEffect());

    view->update();
    this->repaint();
}


evtEffectsListModel* evtEffectsListWindow::getListViewModel(){
    return (evtEffectsListModel*) view->model();
}

void evtEffectsListWindow::effectsChanged(){
    evtEffectsListModel *model = (evtEffectsListModel*) view->model();
    model->setupModelData();
    view->update();
    this->repaint();
}
