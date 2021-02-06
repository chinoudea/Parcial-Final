#ifndef CUERPO_H
#define CUERPO_H

#include <QGraphicsItem>



class cuerpo : public QGraphicsItem
{
public:
    int r;
    int posx, posy;
    QString tipoCuerpo;
    cuerpo();
    cuerpo(int r_, int x_, int y_, QString tipo);

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // CUERPO_H
