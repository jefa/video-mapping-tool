#ifndef UIUTILS_H
#define UIUTILS_H

#include <QtGui>

using namespace std;

class UiUtils
{

    public:
        static QDoubleSpinBox* createCoordinateSpinBox();
        static QDoubleSpinBox* createDoubleSpinBox();
        static void setComboIndexForText(QComboBox *combo, string txt);
        static void clearCombo(QComboBox *combo);
};

#endif
