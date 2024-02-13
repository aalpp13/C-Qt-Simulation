#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QVector>
#include <QDateTime>
#include "qcustomplot.h"
#include "blocks/gain/gain.h"
#include "blocks/Integrator/integrator.h"
#include "blocks/generator/generator.h"
#include "blocks/continuous/continuous.h"
#include "blocks/generator/gendis.h"
#include "blocks/discrete/dis_system.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void update();

private:
    Ui::Widget *ui;
    QGridLayout *mainlayout;
    QCustomPlot *inputPlot;
    QCustomPlot *outputPlot;
	QPushButton* startButton;
	QPushButton* saveButton;

	qint64 startTime = 0;
	qint64 relativeTime = 0;
	qint64 dt;

    QTimer * timer;

    // --------------------------
    // Add pointer to the object here
    // --------------------------
    gain *object;   // <=
    Integrator *m_integrator;

    generator* m_generator;
    continuous* m_continuous;
    gendis* m_gendis;
    dis_system* DSystem;
    // --------------------------
    // Add pointer to the object here
    // --------------------------
};

#endif // WIDGET_H
