#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&_timer, SIGNAL(timeout()), this, SLOT(on_timer_timeout()));
    connect(ui->frame, SIGNAL(paint()), this, SLOT(on_paint()));
    //SNPB
    _heatdata.append({0, 25}); //start
    _heatdata.append({70, 100}); //
    _heatdata.append({175, 140});
    _heatdata.append({239, 220});
    _heatdata.append({300, 25}); //end
    //SN
//    _heatdata.append({0, 25}); //start
//    _heatdata.append({120, 100}); //
//    _heatdata.append({310, 180});
//    _heatdata.append({375, 260});
//    _heatdata.append({600, 25}); //end

}

MainWindow::~MainWindow()
{
    delete _elapsed;
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    if(_elapsed) return;
    ui->label->setText("0");
    _elapsed = new QElapsedTimer();
    _elapsed->start();
    _timer.start(1000);
}

void MainWindow::on_timer_timeout()
{
    if(!_elapsed) return;
    QString e = QString::number(_elapsed->elapsed()/1000);
    ui->label->setText(e);
}

void MainWindow::on_pushButton_2_clicked()
{
    if(!_elapsed) return;
    _timer.stop();
    delete _elapsed; _elapsed = nullptr;
}

void MyFrame::paintEvent(QPaintEvent *e) {
    QPainter paint(this);
    paint.setPen(Qt::red);
    paint.drawEllipse(10,10,100,100);

    paint.end();
    QFrame::paintEvent(e);
}

