#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QElapsedTimer>
#include <QVarLengthArray>
//#include <QtCharts>
#include <renderarea.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    struct HeatData{
      qreal time;
      qreal temperature;
      QString desc;

      QPointF ToQPointF() const {return {time, temperature};}

      static QVarLengthArray<QPointF> ToQPointF(const QVarLengthArray<HeatData>& h )
      {
          QVarLengthArray<QPointF> d;
          for(auto& i:h) d.append(i.ToQPointF());
          return d;
      }
    };

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void Reset();
private slots:
    void on_pushButton_clicked();
    void on_timer_timeout();

    void on_pushButton_2_clicked();
private:
    QTimer _timer;
    QElapsedTimer* _elapsed = nullptr;
    QVarLengthArray<HeatData> _heatdata;
    //QChart *_chart;
    Ui::MainWindow *ui;
    RenderArea* _ra;

};
#endif // MAINWINDOW_H
