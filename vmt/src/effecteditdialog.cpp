#include <QtGui>

#include "effecteditdialog.h"

EffectEditDialog::EffectEditDialog(){
    this->positionPage = NULL;
    this->fadePage = NULL;
    this->texturePage = NULL;

    contentsWidget = new QListWidget;
    contentsWidget->setViewMode(QListView::IconMode);
    contentsWidget->setIconSize(QSize(96, 84));
    contentsWidget->setMovement(QListView::Static);
    contentsWidget->setMaximumWidth(128);
    contentsWidget->setSpacing(12);

    pagesWidget = new QStackedWidget;

    QPushButton *closeButton = new QPushButton(tr("Close"));
    QPushButton *saveButton = new QPushButton(tr("Save"));

    createIcons();

    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(save()));

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(contentsWidget);
    horizontalLayout->addWidget(pagesWidget, 1);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(saveButton);
    buttonsLayout->addWidget(closeButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(horizontalLayout);
    mainLayout->addStretch(1);
    mainLayout->addSpacing(12);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Effect Dialog"));
}

void EffectEditDialog::Init(VmtModel *vmtModel, Effect *ef)
{
    if (positionPage != NULL)
        pagesWidget->removeWidget(positionPage);
    if (fadePage != NULL)
        pagesWidget->removeWidget(fadePage);
    if (texturePage != NULL)
        pagesWidget->removeWidget(texturePage);

    this->positionPage = new PositionEffectPage(vmtModel, ef);
    this->fadePage = new FadeEffectPage(vmtModel, ef);
    this->texturePage = new TextureEffectPage(vmtModel, ef);
    pagesWidget->addWidget(positionPage);
    pagesWidget->addWidget(fadePage);
    pagesWidget->addWidget(texturePage);

    if (ef == NULL) {
        contentsWidget->setCurrentRow(0);
        positionButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        fadeButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        textureButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    } else {
        if (ef->getType() == POSITION_EFFECT) {
            positionButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            fadeButton->setFlags(Qt::ItemIsSelectable);
            textureButton->setFlags(Qt::ItemIsSelectable);
        } else if (ef->getType() == FADE_EFFECT){
            positionButton->setFlags(Qt::ItemIsSelectable);
            fadeButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            textureButton->setFlags(Qt::ItemIsSelectable);
        } else if (ef->getType() == TEXTURE_EFFECT) {
            positionButton->setFlags(Qt::ItemIsSelectable);
            fadeButton->setFlags(Qt::ItemIsSelectable);
            textureButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }
        contentsWidget->setCurrentRow(ef->getType());
    }
}

void EffectEditDialog::createIcons()
{
    positionButton = new QListWidgetItem(contentsWidget);
    positionButton->setIcon(QIcon(":/images/config.png"));
    positionButton->setText(tr("Position"));
    positionButton->setTextAlignment(Qt::AlignHCenter);
    positionButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    fadeButton = new QListWidgetItem(contentsWidget);
    fadeButton->setIcon(QIcon(":/images/update.png"));
    fadeButton->setText(tr("Fade"));
    fadeButton->setTextAlignment(Qt::AlignHCenter);
    fadeButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    textureButton = new QListWidgetItem(contentsWidget);
    textureButton->setIcon(QIcon(":/images/query.png"));
    textureButton->setText(tr("Texture"));
    textureButton->setTextAlignment(Qt::AlignHCenter);
    textureButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    connect(contentsWidget,
            SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));
}

void EffectEditDialog::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;

    pagesWidget->setCurrentIndex(contentsWidget->row(current));
}

void EffectEditDialog::save()
{
    if (contentsWidget->currentRow() == POSITION_EFFECT){
        this->positionPage->saveEffect();
    } else if (contentsWidget->currentRow() == FADE_EFFECT){
        this->fadePage->saveEffect();
    } else if (contentsWidget->currentRow() == TEXTURE_EFFECT){
        this->texturePage->saveEffect();
    }
    emit dataChanged();
    close();
}
