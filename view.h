#ifndef VIEW_H
#define VIEW_H

#include <QList>
#include <QSize>
#include <QTimer>
#include <QQuickPaintedItem>

class View : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(qreal position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(int first READ first WRITE setFirst NOTIFY firstChanged)
    Q_PROPERTY(int last READ last WRITE setLast NOTIFY lastChanged)

public:
    struct Rect {
        int index;
        QColor color;
        qreal width;
    };

    explicit View(QQuickItem *parent = nullptr);

    void paint(QPainter *painter) override;

    qreal position() const;
    void setPosition(qreal position);

    int first() const;
    void setFirst(int first);

    int last() const;
    void setLast(int last);

signals:
    void positionChanged();
    void firstChanged();
    void lastChanged();

private:
    QList<View::Rect> getRects() const;
    QList<View::Rect> relativeRects(qreal &offset);

private:
    qreal m_position = 0.0;
    int m_first = 0;
    int m_last = 0;
};


#endif
