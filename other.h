#ifndef OTHER_H
#define OTHER_H

#include <QGraphicsItem>

class Other : public QGraphicsItem
{
public:
    Other();
    enum {Type = UserType+3};
    int type() const override;
};

#endif // OTHER_H
