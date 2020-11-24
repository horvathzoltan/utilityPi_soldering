#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPen>

class RenderArea : public QWidget
{
    Q_OBJECT

public:

    explicit RenderArea(QWidget *parent = nullptr);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;


//public slots:
    //void setData();

protected:
    void paintEvent(QPaintEvent *event) override;

    QPen pen;
    QBrush brush;

    //QPixmap pixmap;
};

#endif // RENDERAREA_H
