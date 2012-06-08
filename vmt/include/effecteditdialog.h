#ifndef EFFECTEDITDIALOG_H
#define EFFECTEDITDIALOG_H

#include "vmtmodel.h"
#include "Effect.h"
#include "effectpages.h"

QT_BEGIN_NAMESPACE
class QListWidget;
class QListWidgetItem;
class QStackedWidget;
QT_END_NAMESPACE

class EffectEditDialog : public QDialog
{
    Q_OBJECT

public:
    EffectEditDialog();
    void Init(VmtModel *vmtModel, Effect *ef);

public slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);
    void save();

Q_SIGNALS:
    void dataChanged();

private:
    void createIcons();

    QListWidget *contentsWidget;
    QStackedWidget *pagesWidget;

    QListWidgetItem *positionButton;
    QListWidgetItem *fadeButton;
    QListWidgetItem *textureButton;

    PositionEffectPage* positionPage;
    FadeEffectPage* fadePage;
    TextureEffectPage* texturePage;

};

#endif
