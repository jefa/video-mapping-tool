#ifndef EFFECTPAGES_H
#define EFFECTPAGES_H

#include <string>
#include <QtGui>

using namespace std;

class ProcessDialog : public QWidget
{
    Q_OBJECT

public:
    ProcessDialog(QWidget *parent = 0);
    void saveEffect();

public slots:
    void acceptPressed();
    void rejectPressed();
    void setOpenFileName();

private:
    void init();
    void informationMessage(string , string );
    void criticalMessage(string , string );

    QErrorMessage *errorMessageDialog;

    QDialogButtonBox *buttonBox;

    QLineEdit *filePathEdit;
    QLineEdit *outputNameEdit;

    QPushButton *searchButton;
    QSpinBox *sampleNumSpinBox;
    QDoubleSpinBox *radiusSpinBox;
    QCheckBox *subsampleCheckBox;

    QSpinBox *neigborsSpinBox;
    QCheckBox *flipFlagCheckBox;

    QSpinBox *octdepthSpinBox;
    QSpinBox *solverdivideSpinBox;
    QDoubleSpinBox *samplespernodeSpinBox;
    QDoubleSpinBox *offsetSpinBox;

};

#endif
