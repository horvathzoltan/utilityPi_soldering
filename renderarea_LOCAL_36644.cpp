#include "renderarea.h"
#include <QPainter>

RenderArea::RenderArea(QWidget *parent) : QWidget(parent)
{
    pen = QPen(Qt::red);
    brush = QBrush(Qt::blue);
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize RenderArea::sizeHint() const
{
    return QSize(400, 200);
}

void RenderArea::paintEvent(QPaintEvent * /* event */)
{
     auto r = this->parent()
     //QRect rect(10, 20, 80, 60);
     QRect rect(0, 0, r.width(), r.height());

     QPainter painter(this);
     painter.setPen(pen);
     painter.setBrush(brush);
     //if (antialiased)
     painter.setRenderHint(QPainter::Antialiasing, true);
     painter.drawLine(rect.bottomLeft(), rect.topRight());
}
