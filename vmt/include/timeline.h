#ifndef TIMELINE_H
#define TIMELINE_H

#include "vmtmodel.h"

#include <QtGui/QWidget>
#include <QVBoxLayout>
#include <QTimeLine>
#include <QProgressBar>
#include <QSlider>
#include <QPushButton>
#include <QLabel>
#include <QStyle>

class timeline : public QWidget
{
    Q_OBJECT

public:
	timeline(VmtModel *, QWidget *parent = 0);
    ~timeline();

public slots:
    void valueChanged(qreal x);
    void frameChangedTimeline(int);
    void stateChanged(QTimeLine::State newState);
    void finished();
    void start();

    void changePositionSlider(int);

private:
    VmtModel *vmtModel;

	QPushButton *pushButton;
	QTimeLine *timeLine;
	QProgressBar *progressBar;
	QSlider *slider;
    QVBoxLayout *layout;
    QLabel *timerLabel;
};

#endif // TIMELINE_H
