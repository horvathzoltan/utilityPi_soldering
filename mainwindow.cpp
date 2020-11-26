#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&_timer, SIGNAL(timeout()), this, SLOT(on_timer_timeout()));    
    //SNPB
    _heatdata.append({0, 25, "preheat"}); //start
    _heatdata.append({70, 100, "soak"}); //
    _heatdata.append({175, 140, "reflow"});
    _heatdata.append({240, 220, "cooling"});
    _heatdata.append({300, 25, "end"}); //end
    //SN
//    _heatdata.append({0, 25}); //start
//    _heatdata.append({120, 100}); //
//    _heatdata.append({310, 180});
//    _heatdata.append({375, 260});
//    _heatdata.append({600, 25}); //end

    _ra = new RenderArea(ui->frame);
    _ra->setPen(QPen(Qt::blue));
    _ra->setBrush(QBrush(Qt::lightGray));
    _ra->setPolyLine(HeatData::ToQPointF(_heatdata));
    _ra->setRect({0,0, 300,220});
}

MainWindow::~MainWindow()
{
    delete _elapsed;
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    if(_elapsed) return;

    Reset();

    _ra->setMtext("");
    _ra->repaint();

    _elapsed = new QElapsedTimer();
    _elapsed->start();
    _timer.start(50);
}

void MainWindow::on_timer_timeout()
{
    if(!_elapsed) return;    
    qreal mx = _elapsed->elapsed()/50;
    if(mx>_heatdata.last().time) Stop();
    QString e = QString::number(mx);
    ui->label->setText(e);
    _ra->setMarker(mx);
    QString* txt=nullptr;
    for(auto& i:_heatdata){if(mx<i.time) break; txt=&(i.desc); }
    if(txt) _ra->setMtext(*txt);
    _ra->repaint();
}

void MainWindow::on_pushButton_2_clicked()
{
    if(!_elapsed) { Reset(); return;}
    Stop();
}

void MainWindow::Stop(){
    _timer.stop();
    delete _elapsed; _elapsed = nullptr;
}

void MainWindow::Reset(){
    ui->label->setText("");
    _ra->setMarker(0);
    _ra->setMtext("");
    _ra->repaint();
}
