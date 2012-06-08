#include <QtGui>

#include "midieffectslistwindow.h"

using namespace gui;

midiEffectsListWindow::midiEffectsListWindow(VmtModel *vmtModel)
{
    this->selectedItem = NULL;
    this->midieffecteditdialog= new midiEffecteditdialog(vmtModel);

    setupUi(this);

    midiEffectsListModel *model = new midiEffectsListModel(vmtModel, NULL);
    view->setModel(model);

    connect(view, SIGNAL(clicked(QModelIndex)), this, SLOT(clickedList(QModelIndex)));
	connect(view, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(doubleClickedList(QModelIndex)));

	connect(midieffecteditdialog, SIGNAL(dataChanged()), this, SLOT(effectsChanged()));

    connect(newEffectAction, SIGNAL(clicked()), this, SLOT(newEffect()));
    connect(removeEffectAction, SIGNAL(clicked()), this, SLOT(removeEffect()));

    midiIn.listPorts();
    cout<<"midiEffectsListWindow::abrir puerto";
    midiIn.openPort(1);

    addMidiListener(this);
    midiIn.setVerbose(true);


}

midiEffectsListWindow::~midiEffectsListWindow()
{
    delete(selectedItem);
    delete(midieffecteditdialog);
}

void midiEffectsListWindow::setupUi(QWidget *listWindow)
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

void midiEffectsListWindow::retranslateUi(QWidget *listWindow)
{
    listWindow->setWindowTitle(QApplication::translate("listWindow3", "MIDI-Effects", 0, QApplication::UnicodeUTF8));

    newEffectAction->setText(QApplication::translate("treeWindow", "New", 0, QApplication::UnicodeUTF8));
    removeEffectAction->setText(QApplication::translate("treeWindow", "Remove", 0, QApplication::UnicodeUTF8));


} // retranslateUi


void midiEffectsListWindow::clickedList(const QModelIndex &index)
{
    midiEffectsListModel *model = (midiEffectsListModel*) view->model();
    this->selectedItem = model->getItem(index);
}

void midiEffectsListWindow::doubleClickedList(const QModelIndex &index)
{
    ofxMidiEventArgs* Msg = new ofxMidiEventArgs();
    Msg->id = this->selectedItem->getItemData();
    Msg->value = this->selectedItem->getValueData();

    midieffecteditdialog->show();
    midieffecteditdialog->Init(Msg,this->selectedItem->getIdEffect());
    effectsChanged();
}

void midiEffectsListWindow::newEffect(){

    midieffecteditdialog->show();
    effectsChanged();
}

void midiEffectsListWindow::removeEffect(){
    if (this->selectedItem == NULL)
        return;
    ofxMidiEventArgs* Msg = new ofxMidiEventArgs();
    Msg->id = this->selectedItem->getItemData();
    Msg->value = this->selectedItem->getValueData();

    midiEffectsListModel *model = (midiEffectsListModel*) view->model();
    model->removeMidiEffect(Msg,this->selectedItem->getIdEffect());

    view->update();
    this->repaint();
}


midiEffectsListModel* midiEffectsListWindow::getListViewModel(){
    return (midiEffectsListModel*) view->model();
}

void midiEffectsListWindow::effectsChanged(){
    midiEffectsListModel *model = (midiEffectsListModel*) view->model();
    model->setupModelData();
    view->update();
    this->repaint();
}
void midiEffectsListWindow::newMidiMessage(ofxMidiEventArgs& eventArgs){
    cout<<"midiEffectsListWindow::newMidiMessage"<<eventArgs.id <<" "<< eventArgs.value  << '\n';
    midieffecteditdialog->newMidiMessage(eventArgs);

}
void midiEffectsListWindow::addMidiListener(ofxMidiListener *listener){
    midiIn.addListener(listener);
}
