#include "uiutils.h"

#include <limits>

QDoubleSpinBox* UiUtils::createCoordinateSpinBox(){
    QDoubleSpinBox *coordSpinBox = createDoubleSpinBox();
    coordSpinBox->setMaximumWidth(70);
    return coordSpinBox;
}

QDoubleSpinBox* UiUtils::createDoubleSpinBox(){
    QDoubleSpinBox *coordSpinBox = new QDoubleSpinBox();
    coordSpinBox->setMouseTracking(true);
    coordSpinBox->setMaximum(numeric_limits<double>::max());
    coordSpinBox->setMinimum((numeric_limits<double>::max())*(-1));
    coordSpinBox->setSingleStep(.5);
    return coordSpinBox;
}

void UiUtils::setComboIndexForText(QComboBox *combo, string txt){
    for (int i=0; i < combo->count(); i++){
        if (combo->itemText(i).toStdString().compare(txt) == 0){
            combo->setCurrentIndex(i);
            break;
        }
    }
}

void UiUtils::clearCombo(QComboBox *combo){
    int count = combo->count();
    for (int i=(count-1); i >= 0; i--){
        combo->removeItem(i);
    }
}
