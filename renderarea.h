#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPen>
#include <QPainter>
#include <QList>

class RenderArea : public QWidget
{
    Q_OBJECT

public:

    explicit RenderArea(QWidget *parent = nullptr);
    //~RenderArea() {delete _painter;}

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    void setPolyLine(const QVector<QPointF>& pl){_pl = pl;}
    void setPen(const QPen& p){_pen = p;}
    void setBrush(const QBrush& b){_brush = b;}
    void setMarker(qreal x){_mx = x;}
    void setMtext(const QString& x){_mtxt = x;}
    void setRect(const QRectF& x){_r = x;}

protected:
    void paintEvent(QPaintEvent *event) override;

    QRectF _r;
    QPen _pen;
    qreal _mx =0;
    QString _mtxt;
    QBrush _brush;
    QVector<QPointF> _pl;
};

#endif // RENDERAREA_H
