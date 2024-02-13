    #include "widget.h"
    #include "ui_widget.h"
    #include <iostream>
    #include <math.h>

    // --------------------------
    // Set stop time here
    // --------------------------
    #define ENDOFTIME 25
    #define SAMPLINGTIMEMSEC 200
    // --------------------------
    // Set stop time here
    // --------------------------

    Widget::Widget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::Widget)
    {
        ui->setupUi(this);

        // Create dir for logs
        if (!QDir("logs").exists()) {
            QDir().mkdir("logs");
        }

        // Set window size
        this->setMinimumSize(640, 480);

        // Add main layout with two plots
        mainlayout = new QGridLayout(this);
        inputPlot = new QCustomPlot(this);
        outputPlot = new QCustomPlot(this);
        mainlayout->addWidget(inputPlot, 0, 0);
        mainlayout->addWidget(outputPlot, 0, 1);
        inputPlot->addGraph();
        outputPlot->addGraph();

        startButton = new QPushButton("Start");
        connect(startButton, &QPushButton::clicked, this, [=](){
            startTime = 0;
            relativeTime = 0;
            inputPlot->graph(0)->data()->clear();
            outputPlot->graph(0)->data()->clear();
            timer->start();
        });
        mainlayout->addWidget(startButton, 1, 0);

        saveButton = new QPushButton("Save");
        connect(saveButton, &QPushButton::clicked, this, [=](){
            QString timestamp = QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss");
            inputPlot->savePng(QString("./logs/%1_input.png").arg(timestamp));
            outputPlot->savePng(QString("./logs/%1_output.png").arg(timestamp));
        });
        mainlayout->addWidget(saveButton, 1, 1);

        // Give the axes some labels:
        inputPlot->xAxis->setLabel("t");
        inputPlot->yAxis->setLabel("input");
        outputPlot->xAxis->setLabel("t");
        outputPlot->yAxis->setLabel("output");

        // --------------------------
        // Change ranges if you need
        // --------------------------
        // Set axes ranges so see all data:
        inputPlot->xAxis->setRange(0, ENDOFTIME);
        inputPlot->yAxis->setRange(-3, 3);
        outputPlot->xAxis->setRange(0, ENDOFTIME);
        outputPlot->yAxis->setRange(-2.0, 2);

        // --------------------------
        // Create the object here
        // --------------------------
        object = new gain(2.0);
        m_integrator = new Integrator(-1);
        m_generator = new generator(0.24740395925452294, 0.24223);
        m_continuous = new continuous(0.0,0.0,0.0);
        m_gendis = new gendis(5.0);
        DSystem = new dis_system(5.0);
        // --------------------------
        // Create the object here
        // --------------------------

        timer = new QTimer(this);
        timer->setTimerType(Qt::TimerType::PreciseTimer);
        connect(timer, SIGNAL(timeout()), this, SLOT(update()));

        // --------------------------
        // Set sampling time here
        // --------------------------
        timer->setInterval(SAMPLINGTIMEMSEC);
        // --------------------------
        // Set sampling time here
        // --------------------------
    }

    Widget::~Widget()
    {
        delete ui;
        delete inputPlot;
        delete outputPlot;
        delete timer;
        delete mainlayout;

        // --------------------------
        // Delete the object here
        // --------------------------
        delete object;
        delete m_integrator;
        // --------------------------
        // Delete the object here
        // --------------------------
    }

    void Widget::update() {

        // --------------------------
        // Replace input signal with ours
        // --------------------------
        double signal = std::sin(relativeTime / 1000.0 * 0.25 + 0.25) + 0.55;
        // --------------------------
        // Replace input signal with ours
        // --------------------------

        // --------------------------
        // Plot initial values here
        // --------------------------
        if (startTime == 0) {
            // First step only plot initial values
            startTime = QDateTime::currentMSecsSinceEpoch();

            inputPlot->graph(0)->addData(0.0, 0);
            outputPlot->graph(0)->addData(0.0, 0);
            return;
        } else {
            dt = relativeTime;
            relativeTime = QDateTime::currentMSecsSinceEpoch() - startTime;
            dt = relativeTime - dt;
        }

        //inputPlot->graph(0)->addData(relativeTime / 1000.0, signal);
        //outputPlot->graph(0)->addData(relativeTime / 1000.0, m_generator->update(dt/1000.0));
        //outputPlot->graph(0)->addData(relativeTime / 1000.0, m_continuous->update(1.0, dt/1000.0));

        inputPlot->graph(0)->addData(relativeTime / 1000.0, m_generator->update(dt/1000.0));
        outputPlot->graph(0)->addData(relativeTime / 1000.0, DSystem ->getValue());
        //DSystem -> update(m_generator->update(dt/1000.0));
        DSystem -> update(m_generator->update(dt/1000.0));

/*
        inputPlot->graph(0)->addData(relativeTime / 1000.0, m_gendis->getValue());
        outputPlot->graph(0)->addData(relativeTime / 1000.0, DSystem ->getValue());

        m_gendis-> update();
        DSystem -> update(m_gendis->getValue());

        inputPlot->graph(0)->addData(relativeTime / 1000.0, m_gendis->getValue());
        outputPlot->graph(0)->addData(relativeTime / 1000.0, DSystem ->getValue());
*/

        inputPlot->replot();
        outputPlot->replot();

        // --------------------------
        // Update the object here
        // --------------------------
        object->update(signal);
        // --------------------------
        // Update the object here
        // --------------------------

        if (relativeTime / 1000.0 > ENDOFTIME) {
            timer->blockSignals(true);
            timer->stop();
            timer->blockSignals(false);
        }
    }
