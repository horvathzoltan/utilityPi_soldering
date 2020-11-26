#include "renderarea.h"
#include <QPainter>

RenderArea::RenderArea(QWidget *parent) : QWidget(parent)
{
    //_pen = QPen(Qt::red);
    //_brush = QBrush(Qt::blue);
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize RenderArea::sizeHint() const
{
    return QSize(400, 200);
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    auto rect = this->parentWidget()->size();
    this->resize(rect);

    QPainter p(this);
    p.setPen(_pen);
    p.setBrush(_brush);
    p.setRenderHint(QPainter::Antialiasing, true);

    QFont font = p.font();
    font.setPixelSize(48);
    p.setFont(font);

    //QTextOption o(Qt::AlignmentFlag::AlignCenter|Qt::AlignmentFlag::AlignHCenter, );
    if(!_mtxt.isEmpty()) p.drawText(QPointF{100,(qreal)rect.height()/2}, _mtxt);

//    const QRect rectangle = QRect(0, 0, 100, 50);
//    QRect boundingRect;
//    p.drawText(rectangle, 0, tr("Hello"), &boundingRect);

    qreal rx = rect.width()/_r.width();
    qreal ry = rect.height()/_r.height();
    p.translate(0, rect.height());
    p.scale(rx, -ry);


    p.drawPolyline(_pl.begin(), _pl.count());
    p.setPen(QPen(Qt::red));
    p.drawLine(_mx, 0, _mx, rect.height()-1);

//    QLine r2 = {-10, -10, 10, 10};
//    QLine r3 = {-10, 10, 10, -10};
//    p.drawLine(r2);
//    p.drawLine(r3);
}
