#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPen>
#include <QPainter>

class RenderArea : public QWidget
{
    Q_OBJECT

public:

    explicit RenderArea(QWidget *parent = nullptr);
    //~RenderArea() {delete _painter;}

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    void setPolyLine(const QVarLengthArray<QPointF>& pl){_pl = pl;}
    void setPen(const QPen& p){_pen = p;}
    void setBrush(const QBrush& b){_brush = b;}
    void setMarker(qreal x){_mx = x;}
    void setMtext(const QString& x){_mtxt = x;}
    //public slots:
//public slots:
    //void setData();    

protected:
    void paintEvent(QPaintEvent *event) override;

    //QPainter* _painter=nullptr;
    QPen _pen;
    qreal _mx =0;
    QString _mtxt;
    QBrush _brush;
    QVarLengthArray<QPointF> _pl;

    //QPixmap pixmap;
};

#endif // RENDERAREA_H
