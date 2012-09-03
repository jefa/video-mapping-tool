#include <QtGui>
#include <QString>

#include "treewindow.h"
#include "treemodel.h"
#include "treeitem.h"
#include "colorlisteditor.h"
#include "objecteditdialog.h"
#include "layereditdialog.h"
#include "cameraeditdialog.h"
#include "quadeditdialog.h"
#include "backgraundeditdialog.h"
#include "lighteditdialog.h"
#include "calibratedialog.h"
#include "nodeeditdialog.h"
#include "evteffecteditdialog.h"

using namespace gui;


TreeWindow::TreeWindow(VmtModel *vmtModel)
{
    setupUi(this);

    TreeModel *model = new TreeModel(vmtModel, NULL);
    view->setModel(model);
    //for (int column = 0; column < model->columnCount(); ++column)
    //    view->resizeColumnToContents(column);
    view->setColumnWidth(0, 150);

    connect(exitAction, SIGNAL(clicked()), this, SLOT(quit()));
/*
    connect(view->selectionModel(),
            SIGNAL(selectionChanged(const QItemSelection &,
                                    const QItemSelection &)),
            this, SLOT(updateActions()));
*/
    //connect(actionsMenu, SIGNAL(aboutToShow()), this, SLOT(updateActions()));
    connect(insertRowAction, SIGNAL(clicked()), this, SLOT(insertRow()));
    connect(insertColumnAction, SIGNAL(clicked()), this, SLOT(insertColumn()));
    connect(removeRowAction, SIGNAL(clicked()), this, SLOT(removeRow()));
    connect(removeColumnAction, SIGNAL(clicked()), this, SLOT(removeColumn()));
    connect(insertChildAction, SIGNAL(clicked()), this, SLOT(insertChild()));
    connect(editObjectAction, SIGNAL(clicked()), this, SLOT(editObject()));
    connect(saveShowAction, SIGNAL(clicked()), this, SLOT(saveShow()));
    connect(loadShowAction, SIGNAL(clicked()), this, SLOT(loadShow()));
    connect(modeOrbitAction, SIGNAL(clicked()), this, SLOT(setOrbitmode()));
    connect(modeRollAction, SIGNAL(clicked()), this, SLOT(setRollmode()));
    connect(modeDollyAction, SIGNAL(clicked()), this, SLOT(setDollymode()));
    connect(modePanyAction, SIGNAL(clicked()), this, SLOT(setPanymode()));
    connect(calibrateAction, SIGNAL(clicked()), this, SLOT(setCalibration()));

    connect(view, SIGNAL(clicked(QModelIndex)), this, SLOT(clickedTree(QModelIndex)));

//    updateActions();
}
TreeWindow::~TreeWindow()
{
   // this->quit();
}
void TreeWindow::insertChild()
{
     QModelIndex index = view->selectionModel()->currentIndex();
     QAbstractItemModel *model = view->model();

     if (model->columnCount(index) == 0) {
         if (!model->insertColumn(0, index))
             return;
     }

     if (!model->insertRow(0, index))
         return;

     for (int column = 0; column < model->columnCount(index); ++column) {
         QModelIndex child = model->index(0, column, index);
         model->setData(child, QVariant("[No data]"), Qt::EditRole);
         if (!model->headerData(column, Qt::Horizontal).isValid())
             model->setHeaderData(column, Qt::Horizontal, QVariant("[No header]"),
                                  Qt::EditRole);
     }

     view->selectionModel()->setCurrentIndex(model->index(0, 0, index),
                                             QItemSelectionModel::ClearAndSelect);

     updateActions();


}

bool TreeWindow::insertColumn(const QModelIndex &parent)
{
    QAbstractItemModel *model = view->model();
    int column = view->selectionModel()->currentIndex().column();

    // Insert a column in the parent item.
    bool changed = model->insertColumn(column + 1, parent);
    if (changed)
        model->setHeaderData(column + 1, Qt::Horizontal, QVariant("[No header]"),
                             Qt::EditRole);

//    updateActions();

    return changed;
}

void TreeWindow::insertRow()
{

     QModelIndex index = view->selectionModel()->currentIndex();
    // TreeModel *model = view->model();
     TreeModel *model = (TreeModel*) view->model();
     string TypeNodo;
     string Name, path;
     TypeNodo =ObtType(index);
     if (TypeNodo == "OBJECTS" || TypeNodo == "OBJECT"){
         Name= (inputText("New")).toStdString();
         path= (inputTextPath("")).toStdString();
         int pos = model->getVmtModel()->getObjects3D().size();
         model->addObject3D(/*pos*/0, index.row()+1, index, Name, path);
     } else {
         Name = (inputText("New")).toStdString();
         model->insertRows(0,index.row()+1, index, Name);
     }

     updateActions(index);

    /*

     for (int column = 0; column < model->columnCount(index); ++column) {
         QModelIndex child = model->index(index.row()+1, column, index.parent());
         model->setData(child, name /*QVariant("[No data]")*//*, Qt::EditRole);
     }
*/
}

bool TreeWindow::removeColumn(const QModelIndex &parent)
{
    QAbstractItemModel *model = view->model();
    int column = view->selectionModel()->currentIndex().column();

    // Insert columns in each child of the parent item.
    bool changed = model->removeColumn(column, parent);

 //   if (!parent.isValid() && changed)
//        updateActions();

    return changed;
}

void TreeWindow::removeRow()
{
     QModelIndex index = view->selectionModel()->currentIndex();
     QAbstractItemModel *model = view->model();
     if (model->removeRow(index.row(), index.parent()))
         updateActions(index);

}
string TreeWindow::ObtType(const QModelIndex &index)
{
    string TypeNodo;

    TreeModel *model = (TreeModel*) view->model();
    TreeItemData *itemData = model->getItem(index)->getItemData();
    if (itemData == NULL) {
           //cout<< "child number: "<<model->getItem(index)->childNumber();
           //0 CAMERAS  1 OBJECTS   2  Backgraund
           	switch(model->getItem(index)->childNumber())
                {
                case 0:TypeNodo = "CAMERAS";		 break;
                case 1:TypeNodo = "OBJECTS";		 break;
                case 2:TypeNodo = "GROUPS";		     break;
                case 3:TypeNodo = "NODES";		     break;
                case 4:TypeNodo = "BACKGRAUND";		 break;

                }
    }
    else{
      //  "CAMERA","LAYER", "QUAD","OBJECT"

           	switch(itemData->itemId)
                {
                case 0:TypeNodo = "CAMERA";		 break;
                case 1:TypeNodo = "LAYER";		 break;
                case 2:TypeNodo = "QUAD";		 break;
                case 3:TypeNodo = "OBJECT";		 break;
                case 4:TypeNodo = "GROUPS";		 break;
                case 5:TypeNodo = "NODE";		 break;

                }
        }
    return TypeNodo;
}


void TreeWindow::updateActions(const QModelIndex &index)
{
//"CAMERAS", "OBJECTS","BACKGRAUND", "CAMERA","LAYER", "QUAD","OBJECT"
string TypeNodo;
    //printf("===== UPDATEACTIONS!!!\n");

        TypeNodo = ObtType(index);
        //cout  << " TypeNodo : "<< TypeNodo;

        if (TypeNodo == "CAMERAS")
        {
            editObjectAction->setEnabled(false);
            insertRowAction->setEnabled(true);
            removeRowAction->setEnabled(false);
        }
        if (TypeNodo == "CAMERA")
        {
            editObjectAction->setEnabled(true);
            insertRowAction->setEnabled(true);
            removeRowAction->setEnabled(true);
        }
        if (TypeNodo == "OBJECTS")
        {
            editObjectAction->setEnabled(false);
            insertRowAction->setEnabled(true);
            removeRowAction->setEnabled(false);
        }
        if (TypeNodo == "OBJECT")
        {
            editObjectAction->setEnabled(true);
            insertRowAction->setEnabled(true);
            removeRowAction->setEnabled(true);
        }
        if (TypeNodo == "BACKGRAUND" )
        {
            editObjectAction->setEnabled(true);
            insertRowAction->setEnabled(false);
            removeRowAction->setEnabled(false);
        }
        if (TypeNodo == "GROUPS" )
        {
            editObjectAction->setEnabled(false);
            insertRowAction->setEnabled(true);
            removeRowAction->setEnabled(false);
        }
        if (TypeNodo == "LIGHT")
        {
            editObjectAction->setEnabled(true);
            insertRowAction->setEnabled(true);
            removeRowAction->setEnabled(true);
        }
        if (TypeNodo == "NODES" )
        {
            editObjectAction->setEnabled(false);
            insertRowAction->setEnabled(true);
            removeRowAction->setEnabled(false);
        }
        if (TypeNodo == "NODE")
        {
            editObjectAction->setEnabled(true);
            insertRowAction->setEnabled(true);
            removeRowAction->setEnabled(true);
        }
        if (TypeNodo == "LAYER" )
        {
            editObjectAction->setEnabled(true);
            insertRowAction->setEnabled(true);
            removeRowAction->setEnabled(true);
        }
        if (TypeNodo == "QUAD" )
        {
            editObjectAction->setEnabled(true);
            insertRowAction->setEnabled(true);
            removeRowAction->setEnabled(true);
        }





}

void TreeWindow::setupUi(QWidget *treeWindow)
{
    if (treeWindow->objectName().isEmpty())
        treeWindow->setObjectName(QString::fromUtf8("treeWindow"));
    treeWindow->resize(400, 400);
    treeWindow->move(20,20);
    exitAction = new QPushButton();
    exitAction->setObjectName(QString::fromUtf8("exitAction"));
    insertRowAction = new QPushButton();
    insertRowAction->setObjectName(QString::fromUtf8("insertRowAction"));
    insertRowAction->setEnabled(false);
    removeRowAction = new QPushButton();
    removeRowAction->setObjectName(QString::fromUtf8("removeRowAction"));
    removeRowAction->setEnabled(false);
    insertColumnAction = new QPushButton();
    insertColumnAction->setObjectName(QString::fromUtf8("insertColumnAction"));
    insertColumnAction->setEnabled(false);
    removeColumnAction = new QPushButton();
    removeColumnAction->setObjectName(QString::fromUtf8("removeColumnAction"));
    removeColumnAction->setEnabled(false);
    insertChildAction = new QPushButton();
    insertChildAction->setObjectName(QString::fromUtf8("insertChildAction"));
    insertChildAction->setEnabled(false);
    editObjectAction = new QPushButton();
    editObjectAction->setObjectName(QString::fromUtf8("editObjectAction"));
    editObjectAction->setEnabled(false);
    saveShowAction = new QPushButton();
    saveShowAction->setObjectName(QString::fromUtf8("saveShowAction"));
    saveShowAction->setEnabled(true);
    loadShowAction = new QPushButton();
    loadShowAction->setObjectName(QString::fromUtf8("loadShowAction"));
    loadShowAction->setEnabled(true);

    modeOrbitAction = new QPushButton();
    modeOrbitAction->setObjectName(QString::fromUtf8("modeOrbitAction"));
    modeOrbitAction->setEnabled(true);
    modeRollAction = new QPushButton();
    modeRollAction->setObjectName(QString::fromUtf8("modeRollAction"));
    modeRollAction->setEnabled(true);
    modeDollyAction = new QPushButton();
    modeDollyAction->setObjectName(QString::fromUtf8("modeDollyAction"));
    modeDollyAction->setEnabled(true);
    modePanyAction = new QPushButton();
    modePanyAction->setObjectName(QString::fromUtf8("modePanyAction"));
    modePanyAction->setEnabled(true);

    calibrateAction = new QPushButton();
    calibrateAction->setObjectName(QString::fromUtf8("calibrateAction"));
    calibrateAction->setEnabled(true);


    treeWindow->setObjectName(QString::fromUtf8("centralwidget"));
    vboxLayout = new QVBoxLayout(treeWindow);
    vboxLayout->setSpacing(0);
    vboxLayout->setContentsMargins(0, 0, 0, 0);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    view = new QTreeView(treeWindow);
    view->setObjectName(QString::fromUtf8("view"));
    view->setAlternatingRowColors(true);
    view->setSelectionBehavior(QAbstractItemView::SelectItems);
    view->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    view->setAnimated(false);
    view->setAllColumnsShowFocus(true);

    vboxLayout->addWidget(view);

    layout = new QGridLayout;
    layout->setColumnStretch(1, 1);
    layout->setColumnMinimumWidth(0,200);
    layout->setColumnMinimumWidth(1, 200);
    layout->addWidget(editObjectAction, 0, 0);
    layout->addWidget(insertRowAction, 0, 1);
    layout->addWidget(removeRowAction, 1, 1);
    layout->addWidget(saveShowAction, 1, 0);
    layout->addWidget(loadShowAction, 2, 0);

    layout->addWidget(modeOrbitAction, 3,1);
    layout->addWidget(modeRollAction,  3,0);
    layout->addWidget(modeDollyAction, 4,1);
    layout->addWidget(modePanyAction,4,0);
    layout->addWidget(calibrateAction,5,0);

    //layout->addWidget(insertChildAction, 0, 1);


    vboxLayout->addLayout(layout);
    vboxLayout->addWidget(exitAction);

    //treeWindow->setCentralWidget(centralwidget);
    //menubar = new QMenuBar(treeWindow);
    //menubar->setObjectName(QString::fromUtf8("menubar"));
    //menubar->setGeometry(QRect(0, 0, 573, 31));
    //fileMenu = new QMenu(menubar);
    //fileMenu->setObjectName(QString::fromUtf8("fileMenu"));
    //actionsMenu = new QMenu(menubar);
    //actionsMenu->setObjectName(QString::fromUtf8("actionsMenu"));
    //treeWindow->setMenuBar(menubar);
    //statusbar = new QStatusBar(treeWindow);
    //statusbar->setObjectName(QString::fromUtf8("statusbar"));
    //treeWindow->setStatusBar(statusbar);

    //menubar->addAction(fileMenu->menuAction());
    //menubar->addAction(actionsMenu->menuAction());
    //fileMenu->addAction(exitAction);
    //actionsMenu->addAction(insertRowAction);
    //actionsMenu->addAction(insertColumnAction);
    //actionsMenu->addSeparator();
    //actionsMenu->addAction(removeRowAction);
    //actionsMenu->addAction(removeColumnAction);
    //actionsMenu->addSeparator();
    //actionsMenu->addAction(insertChildAction);

    retranslateUi(treeWindow);

    //QMetaObject::connectSlotsByName(treeWindow);
} // setupUi

void TreeWindow::retranslateUi(QWidget *treeWindow)
{
    treeWindow->setWindowTitle(QApplication::translate("treeWindow", "Scene", 0, QApplication::UnicodeUTF8));
    exitAction->setText(QApplication::translate("treeWindow", "E&xit", 0, QApplication::UnicodeUTF8));
    exitAction->setShortcut(QApplication::translate("treeWindow", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
    insertRowAction->setText(QApplication::translate("treeWindow", "Add", 0, QApplication::UnicodeUTF8));
    insertRowAction->setShortcut(QApplication::translate("treeWindow", "Ctrl+I, R", 0, QApplication::UnicodeUTF8));
    removeRowAction->setText(QApplication::translate("treeWindow", "Remove", 0, QApplication::UnicodeUTF8));
    removeRowAction->setShortcut(QApplication::translate("treeWindow", "Ctrl+R, R", 0, QApplication::UnicodeUTF8));
    insertColumnAction->setText(QApplication::translate("treeWindow", "Insert Column", 0, QApplication::UnicodeUTF8));
    insertColumnAction->setShortcut(QApplication::translate("treeWindow", "Ctrl+I, C", 0, QApplication::UnicodeUTF8));
    removeColumnAction->setText(QApplication::translate("treeWindow", "Remove Column", 0, QApplication::UnicodeUTF8));
    removeColumnAction->setShortcut(QApplication::translate("treeWindow", "Ctrl+R, C", 0, QApplication::UnicodeUTF8));
    insertChildAction->setText(QApplication::translate("treeWindow", "Add", 0, QApplication::UnicodeUTF8));
    insertChildAction->setShortcut(QApplication::translate("treeWindow", "Ctrl+N", 0, QApplication::UnicodeUTF8));

    editObjectAction->setText(QApplication::translate("treeWindow", "Edit", 0, QApplication::UnicodeUTF8));
    editObjectAction->setShortcut(QApplication::translate("treeWindow", "Ctrl+O", 0, QApplication::UnicodeUTF8));
    saveShowAction->setText(QApplication::translate("treeWindow", "Save", 0, QApplication::UnicodeUTF8));
    saveShowAction->setShortcut(QApplication::translate("treeWindow", "Ctrl+S", 0, QApplication::UnicodeUTF8));
    loadShowAction->setText(QApplication::translate("treeWindow", "Load", 0, QApplication::UnicodeUTF8));
    loadShowAction->setShortcut(QApplication::translate("treeWindow", "Ctrl+L", 0, QApplication::UnicodeUTF8));

    modeOrbitAction->setText(QApplication::translate("treeWindow", "ORBIT Mode", 0, QApplication::UnicodeUTF8));
    modeOrbitAction->setShortcut(QApplication::translate("treeWindow", "Ctrl+L", 0, QApplication::UnicodeUTF8));

    modeRollAction->setText(QApplication::translate("treeWindow", "ROLL Mode", 0, QApplication::UnicodeUTF8));
    modeRollAction->setShortcut(QApplication::translate("treeWindow", "Ctrl+L", 0, QApplication::UnicodeUTF8));

    modeDollyAction->setText(QApplication::translate("treeWindow", "DOLLY Mode", 0, QApplication::UnicodeUTF8));
    modeDollyAction->setShortcut(QApplication::translate("treeWindow", "Ctrl+L", 0, QApplication::UnicodeUTF8));

    modePanyAction->setText(QApplication::translate("treeWindow", "PAN Mode", 0, QApplication::UnicodeUTF8));
    modePanyAction->setShortcut(QApplication::translate("treeWindow", "Ctrl+L", 0, QApplication::UnicodeUTF8));


    calibrateAction->setText(QApplication::translate("treeWindow", "Calibrate", 0, QApplication::UnicodeUTF8));
    calibrateAction->setShortcut(QApplication::translate("treeWindow", "Ctrl+L", 0, QApplication::UnicodeUTF8));



    //fileMenu->setTitle(QApplication::translate("treeWindow", "&File", 0, QApplication::UnicodeUTF8));
    //actionsMenu->setTitle(QApplication::translate("treeWindow", "&Actions", 0, QApplication::UnicodeUTF8));
} // retranslateUi

QString TreeWindow::inputText(string defaultValue)
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                         tr("Name:"), QLineEdit::Normal,
                                         QString(defaultValue.c_str()), &ok);
    if (ok && !text.isEmpty())
        return text;

    throw exception();
}

QString TreeWindow::inputTextPath(string defaultValue)
{
    QFileDialog::Options options;
    QString selectedFilter;
    QString path = QFileDialog::getOpenFileName(this,
                         "Select one or more files to open",
                         "/home",
                         "files (*.3ds)",&selectedFilter
                         /*this,
                                tr("Path"),
                                QString("NewSquirrel.3ds"),
                                tr("All Files (*);;(*.3DS)"),
                                &selectedFilter,options*/);
    if (!path.isEmpty())
        return path;

    int ret = QMessageBox::warning(this, tr("VMT"),
                                tr("Error opening file.\n"
                                   "Either file or path are invalid."),
                                /*QMessageBox::Save | QMessageBox::Discard*/QMessageBox::Ok,
                                QMessageBox::Ok);

    return "";
}

void TreeWindow::clickedTree(const QModelIndex &index)
{

    updateActions(index);
    TreeModel *model = (TreeModel*) view->model();
    TreeItemData *itemData = model->getItem(index)->getItemData();
    if (itemData != NULL) {
        //cout<<"index "<< itemData->itemId;
        if (itemData->itemId == 0){ //es camara
            CameraItemData *cid = (CameraItemData*)itemData;
            string str = cid->getData(0).toString().toStdString();
            //cout<<" activa camera " << str;
            model->getVmtModel()->activateCamera(str);
            cout<<"\tcamaraID "<< str;

        }
    }
}

void TreeWindow::editObject()
{
    TreeModel *model = (TreeModel*) view->model();
    QModelIndex index = view->selectionModel()->currentIndex();
    TreeItemData *itemData = model->getItem(index)->getItemData();
    TreeItemData *parentitemData = model->getItem(index.parent())->getItemData();
    TreeItemData *parentitemData0;
    if (index.parent().parent().isValid()) {
        parentitemData0 = model->getItem(index.parent().parent())->getItemData();
    }

    string TypeNodo;
    TypeNodo =ObtType(index);
    if (TypeNodo == "NODE"){
        cout << "nodo  "<<itemData->getData(0).toString().toStdString();
        //cout <<  "id camera del node"<< (model->getVmtModel()->getNode(itemData->getData(0).toString().toStdString()))->cameraId;
       //model->getVmtModel()->activateCamera((model->getVmtModel()->getNodes()[itemData->getData(0).toString().toStdString()]).cameraId);
       NodeEditorDialog *d = new NodeEditorDialog(model->getVmtModel(),itemData->getData(0).toString().toStdString());
        d->show();
    }
    if (TypeNodo == "LIGHT"){

       LightEditorDialog *d = new LightEditorDialog(model->getVmtModel(),(itemData->getData(0).toString().toStdString()) );
        d->show();
    }
    if (TypeNodo == "CAMERA"){
        CameraEditorDialog *d = new CameraEditorDialog(model->getVmtModel(),itemData->getData(0).toString().toStdString());
        d->show();
    }

    if (TypeNodo == "OBJECT"){
        ObjectEditorDialog *d = new ObjectEditorDialog(model->getVmtModel(),itemData->getData(0).toString().toStdString());
        d->show();
    }
    if (TypeNodo == "LAYER"){
        model->getVmtModel()->activateCamera(parentitemData->getData(0).toString().toStdString());
        LayerEditorDialog *d = new LayerEditorDialog(model->getVmtModel(), parentitemData->getData(0).toString().toStdString() , itemData->getData(0).toString().toStdString() );
        d->show();
    }
    if (TypeNodo == "QUAD"){

        model->getVmtModel()->activateCamera(parentitemData0->getData(0).toString().toStdString());
        QuadEditorDialog *d = new QuadEditorDialog(model->getVmtModel(), parentitemData0->getData(0).toString().toStdString(),  parentitemData->getData(0).toString().toStdString(), itemData->getData(0).toString().toStdString());
        d->show();
    }
    if (TypeNodo == "BACKGRAUND" )
    {
        BackgraundEditorDialog *d = new BackgraundEditorDialog(model->getVmtModel());
        d->show();
    }

}

void TreeWindow::quit()
{


}

void TreeWindow::loadShow()
{
    QFileDialog::Options options;
    //if (!native->isChecked())
    //    options |= QFileDialog::DontUseNativeDialog;
    QString selectedFilter;
    QString fileName = QFileDialog::getOpenFileName(this,
                                tr("Load show..."),
                                QString("show1.xml"),
                                tr("All Files (*);;Text Files (*.txt)"),
                                &selectedFilter,
                                options);
    if (!fileName.isEmpty()) {
        TreeModel *model = (TreeModel*) view->model();
        model->getVmtModel()->loadShow(fileName.toStdString());
    }
}

void TreeWindow::setOrbitmode(){
    TreeModel *model = (TreeModel*) view->model();
    model->getVmtModel()->setControlMode(ORBIT_MODE);

}

void TreeWindow::setRollmode(){
    TreeModel *model = (TreeModel*) view->model();
    model->getVmtModel()->setControlMode(ROLL_MODE);
}

void TreeWindow::setDollymode(){
    TreeModel *model = (TreeModel*) view->model();
    model->getVmtModel()->setControlMode(DOLLY_MODE);
}

void TreeWindow::setPanymode(){
    TreeModel *model = (TreeModel*) view->model();
    model->getVmtModel()->setControlMode(PAN_MODE);
}
void TreeWindow::setCalibration(){
    TreeModel *model = (TreeModel*) view->model();
    CalibrateDialog *d = new CalibrateDialog(model->getVmtModel());
    d->show();
}

void TreeWindow::saveShow()
{
    QString fileName = inputText("show2.xml");
    TreeModel *model = (TreeModel*) view->model();
    model->getVmtModel()->saveShow(fileName.toStdString());
}

void registerColorItemEditorFactory(){
    QItemEditorFactory *factory = new QItemEditorFactory;

    QItemEditorCreatorBase *colorListCreator =
        new QStandardItemEditorCreator<ColorListEditor>();

    factory->registerEditor(QVariant::Color, colorListCreator);

    QItemEditorFactory::setDefaultFactory(factory);
}
