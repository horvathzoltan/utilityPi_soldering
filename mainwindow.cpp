#include "mainwindow.h"
#include "ui_mainwindow.h"

/*
http://www.bristolwatch.com/ele/thermalcouple_amplifier.htm
https://www.aboutcircuit.com/thermocouple-instrument/
*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&_timer, SIGNAL(timeout()), this, SLOT(on_timer_timeout()));    
    //SNPB

    _thermal_profiles.append({"SnPb", {
                                       {0, 25, "preheat"},
                                       {70, 100, "soak"},
                                       {175, 140, "reflow"},
                                       {240, 220, "cooling"},
                                       {300, 25, "end"}
                                   }, false});

    _thermal_profiles.append({"Sn", {
                                       {0, 25, "preheat"},
                                       {120, 100, "soak"},
                                       {310, 180, "reflow"},
                                       {375, 260, "cooling"},
                                       {600, 25, "end"}
                                   }, true});




    _ra = new RenderArea(ui->frame);
    _ra->setPen(QPen(Qt::blue));
    _ra->setBrush(QBrush(Qt::lightGray));
//    _ra->setPolyLine(HeatData::ToQPointF(heatdata()));
//    _ra->setRect(HeatData::GetMax(heatdata()));

    for(auto&i:_thermal_profiles){

        ui->listWidget->addItem(i.name);
        if(i.isCurrent) ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
    }

}

const QVector<MainWindow::HeatData>& MainWindow::heatdata(){
    return _thermal_profiles[ix]._heatdata;
}

MainWindow::~MainWindow()
{
    delete _elapsed;
    delete ui;
}


//start
void MainWindow::on_pushButton_clicked()
{
    if(_elapsed) return;

    ui->listWidget->setEnabled(false);
    Reset();

    _ra->setMtext("");
    _ra->repaint();

    _elapsed = new QElapsedTimer();
    _elapsed->start();
    _timer.start(1000);
}

void MainWindow::on_timer_timeout()
{
    if(!_elapsed) return;    
    qreal mx = _elapsed->elapsed()/1000;
    if(mx>heatdata().last().time) Stop();
    QString e = QString::number(mx);
    ui->label->setText(e);
    _ra->setMarker(mx);
    const QString* txt=nullptr;
    for(auto&i:heatdata()){if(mx<i.time) break; txt=&(i.desc); }
    if(txt) _ra->setMtext(*txt);
    _ra->repaint();
}

//stop
void MainWindow::on_pushButton_2_clicked()
{
    if(!_elapsed) { Reset(); return;}
    Stop();
    ui->listWidget->setEnabled(true);
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

void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
    ix = currentRow;

    _ra->setPolyLine(HeatData::ToQPointF(heatdata()));
    _ra->setRect(HeatData::GetMax(heatdata()));

    _ra->repaint();
}
