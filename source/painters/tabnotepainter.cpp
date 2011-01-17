#include "tabnotepainter.h"

#include <QPainter>
#include <QMessageBox>
#include <QFontMetricsF>

#include <powertabdocument/note.h>

QFont TabNotePainter::tabFont = QFont("Liberation Sans");

TabNotePainter::TabNotePainter(Note* notePtr)
{
    note = notePtr;
    tabFont.setPixelSize(10); // needed for cross-platform consistency in font size
    tabFont.setStyleStrategy(QFont::PreferAntialias);

    setText();
}

void TabNotePainter::mousePressEvent(QGraphicsSceneMouseEvent *)
{
}

void TabNotePainter::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    QMessageBox message;
    message.setText("Fret: " + QString().setNum(note->GetFretNumber()) + " String: " + QString().setNum(note->GetString()));
    message.exec();
}

void TabNotePainter::mouseMoveEvent(QGraphicsSceneMouseEvent *)
{
}

QRectF TabNotePainter::boundingRect() const
{
    return QFontMetricsF(tabFont).boundingRect(noteText);
}

void TabNotePainter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setFont(tabFont);

    if(note->IsTied())
    {
        painter->setPen(Qt::lightGray);
    }
    else
    {
        painter->setPen(Qt::black);
    }

    setText();

    // offset height by 1 pixel for clarity
    painter->drawText(0, -1, noteText);
}

inline void TabNotePainter::setText()
{
    noteText = QString().fromStdString(note->GetText());
}
