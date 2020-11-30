#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QElapsedTimer>
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

      static QVector<QPointF> ToQPointF(const QVector<HeatData>& h )
      {
          QVector<QPointF> d;
          for(auto& i:h) d.append(i.ToQPointF());
          return d;
      }

      static QRectF GetMax(const QVector<HeatData>& h ){
          qreal x=0, y=0;
          for(auto& i:h) {
              if(i.time>x) x=i.time;
              if(i.temperature>y) y=i.temperature;
          }
          return {0, 0, x ,y};
      };
    };

    struct ThermalPofile{
        QString name;
        QVector<HeatData> _heatdata;
        bool isCurrent;
    };

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    const QVector<MainWindow::HeatData> &heatdata();
protected:
    void Reset();
    void Stop();

private slots:
    void on_pushButton_clicked();
    void on_timer_timeout();

    void on_pushButton_2_clicked();
    void on_listWidget_currentRowChanged(int currentRow);

private:
    QTimer _timer;
    QElapsedTimer* _elapsed = nullptr;
    QVector<ThermalPofile> _thermal_profiles;
    int ix = 1;
    Ui::MainWindow *ui;
    RenderArea* _ra;

};
#endif // MAINWINDOW_H
