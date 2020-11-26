#include "renderarea.h"
#include <QPainter>

RenderArea::RenderArea(QWidget *parent) : QWidget(parent){}

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

    qreal rx = (qreal)rect.width()/_r.width();
    qreal ry = (qreal)rect.height()/_r.height();

    QPainter p(this);

    QPen dashpen(_pen);
    QVector<qreal> dashes;
    qreal space = 4;
    dashes << 4 << space;
    qreal my;
    dashpen.setDashPattern(dashes);
    p.setPen(dashpen);
    for(auto& i:_pl){
        auto v = i.y();
        auto y = rect.height() - v*ry;
        QString txt = QString::number(v)+"°C";
        QRect br = p.boundingRect(0, 0, 0, 0, 0, txt);
        p.drawLine(0, y, rect.width(), y);
        y-=2;
        if(y<br.height())y=br.height();
        p.drawText(2, y, txt);
        if(_mx>i.x()) my=v;
    }

    p.setPen(_pen);
    p.setBrush(_brush);
    p.setRenderHint(QPainter::Antialiasing, true);

    QFont font = p.font();
    font.setPixelSize(48);
    p.setFont(font);

    if(!_mtxt.isEmpty()){
        QRect br = p.boundingRect(0, 0, 0, 0, 0, _mtxt);

        auto x = rx*_mx;
        if(x>rect.width()/2){
            if(x>rect.width()) x = rect.width();
            x-=br.width();
        }

        auto y = rect.height()-br.height()-ry*my;
        if(y<0) y=0;

        br.translate(x, y);
        p.drawText(br, _mtxt);
    }


    p.translate(0, rect.height());
    p.scale(rx, -ry);

    p.drawPolyline(_pl.begin(), _pl.count());

    p.setPen(QPen(Qt::red));
    p.drawLine(_mx, 0, _mx, rect.height()-1);
}
