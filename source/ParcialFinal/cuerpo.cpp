#include "cuerpo.h"

#include <QPainter>

cuerpo::cuerpo()
{

}

cuerpo::cuerpo(int r_, int x_, int y_, QString tipo)
{
    r=r_;
    posx = x_;
    posy = y_;
    setPos(posx,posy);
    tipoCuerpo = tipo;
}

QRectF cuerpo::boundingRect() const
{
    return QRectF(-r,-r,2*r,2*r);
}
void cuerpo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if (tipoCuerpo=="morteroO") {
        painter->setBrush(Qt::blue);
    } else if (tipoCuerpo=="morteroD") {
        painter->setBrush(Qt::red);
    } else if (tipoCuerpo=="balaO") {
        painter->setBrush(Qt::green);
    } else if (tipoCuerpo=="balaD") {
        painter->setBrush(Qt::yellow);
    }
    painter->drawEllipse(boundingRect());
}
