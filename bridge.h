#ifndef BRIDGE_H
#define BRIDGE_H

#include <QObject>

class bridge : public QObject
{
    Q_OBJECT
public:
    explicit bridge(QObject *parent = 0);

    void connectAll();

signals:
public slots:

};

#endif // BRIDGE_H
