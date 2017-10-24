#include "view.h"

#include <QtGlobal>
#include <QPainter>
#include <QDebug>

int rnd(int min = 0, int max = 255) {
    return qrand() % (max + 1 - min) + min;
}

View::View(QQuickItem *parent)
   : QQuickPaintedItem(parent)
{
}

qreal View::position() const
{
    return m_position;
}

void View::setPosition(qreal position)
{
    if (!qFuzzyCompare(m_position, position)) {
        m_position = position;
        emit positionChanged();

        update();
    }
}

int View::first() const
{
    return m_first;
}

void View::setFirst(int first)
{
    if (m_first != first) {
        m_first = first;
        emit firstChanged();
    }
}

int View::last() const
{
    return m_last;
}

void View::setLast(int last)
{
    if (m_last != last) {
        m_last = last;
        emit lastChanged();
    }
}

QList<View::Rect> View::getRects() const
{
    static const int min = 30;
    static const int max = 200;

    static QList<View::Rect> rects {
        { -1, QColor(Qt::black), 2 },
        {  0, QColor(rnd(), rnd(), rnd(), 200), rnd(min, max) * 1.0 },
        {  1, QColor(rnd(), rnd(), rnd(), 200), rnd(min, max) * 1.0 },
        {  2, QColor(rnd(), rnd(), rnd(), 200), rnd(min, max) * 1.0 },
        {  3, QColor(rnd(), rnd(), rnd(), 200), rnd(min, max) * 1.0 },
        {  4, QColor(rnd(), rnd(), rnd(), 200), rnd(min, max) * 1.0 },
        {  5, QColor(rnd(), rnd(), rnd(), 200), rnd(min, max) * 1.0 },
        {  6, QColor(rnd(), rnd(), rnd(), 200), rnd(min, max) * 1.0 },
        {  7, QColor(rnd(), rnd(), rnd(), 200), rnd(min, max) * 1.0 },
        {  8, QColor(rnd(), rnd(), rnd(), 200), rnd(min, max) * 1.0 },
        {  9, QColor(rnd(), rnd(), rnd(), 200), rnd(min, max) * 1.0 },
        { 10, QColor(rnd(), rnd(), rnd(), 200), rnd(min, max) * 1.0 },
        { 11, QColor(rnd(), rnd(), rnd(), 200), rnd(min, max) * 1.0 },
        { 12, QColor(rnd(), rnd(), rnd(), 200), rnd(min, max) * 1.0 },
        { 13, QColor(rnd(), rnd(), rnd(), 200), rnd(min, max) * 1.0 },
        { 14, QColor(rnd(), rnd(), rnd(), 200), rnd(min, max) * 1.0 },
        { 15, QColor(rnd(), rnd(), rnd(), 200), rnd(min, max) * 1.0 },
        { 16, QColor(rnd(), rnd(), rnd(), 200), rnd(min, max) * 1.0 },
        { 17, QColor(rnd(), rnd(), rnd(), 200), rnd(min, max) * 1.0 },
        { 18, QColor(rnd(), rnd(), rnd(), 200), rnd(min, max) * 1.0 },
        { 19, QColor(rnd(), rnd(), rnd(), 200), rnd(min, max) * 1.0 },
        { 20, QColor(rnd(), rnd(), rnd(), 200), rnd(min, max) * 1.0 },
        { 21, QColor(rnd(), rnd(), rnd(), 200), rnd(min, max) * 1.0 }
    };

    return rects;
}

QList<View::Rect> View::relativeRects(qreal &offset)
{
    QList<View::Rect> rects = getRects();
    if(getRects().isEmpty()) {
        offset = 0;
        return QList<Rect>();
    }

    offset = m_first == 0 ? m_position : 0;
    QList<Rect> head;

    QList<Rect> hoarded = getRects().mid(m_first);
    qreal p = offset;
    while(!hoarded.isEmpty() && (p + hoarded.first().width) < width()) {
        p += hoarded.first().width;
        head.append(hoarded.takeFirst());

        if(hoarded.isEmpty()) {
            hoarded = rects;
        }
    }

    setLast(m_first + head.size());
    return head;
}

void View::paint(QPainter *painter)
{
    painter->save();

    QFont font = painter->font();
    font.setBold(true);
    painter->setFont(font);

    qreal offset;
    const QList<Rect> items = relativeRects(offset);
    for(const Rect &it: items) {
        QRectF r(offset, 0, it.width, height());
        painter->fillRect(r, it.color);
        if(it.index >= 0) {
            painter->drawText(r, Qt::AlignCenter, QString::number(it.index));
            painter->drawText(r.adjusted(2,2,-2,-2), Qt::AlignTop | Qt::AlignRight, "+");
        }
        offset += it.width;
    }
    painter->restore();
}
