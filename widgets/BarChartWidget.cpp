#include "BarChartWidget.h"
#include <QPainter>
#include <QDate>
#include <vector>
#include <string>

BarChartWidget::BarChartWidget(const std::vector<int>& eventsPerMonth, QWidget* parent)
    : QWidget(parent), data(eventsPerMonth) {}

void BarChartWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int w = width();
    int h = height();

    int marginLeft = 50;
    int marginRight = 20;
    int marginTop = 20;
    int marginBottom = 40;

    int availableHeight = h - marginTop - marginBottom;
    int availableWidth = w - marginLeft - marginRight;

    int maxVal = *std::max_element(data.begin(), data.end());
    if (maxVal == 0) maxVal = 1;

    int barWidth = availableWidth / data.size();

    QFont font2 = painter.font();
    font2.setPointSize(10);
    painter.setFont(font2);

    painter.save();

    painter.translate(10, marginTop + availableHeight / 2);
    painter.rotate(-90);
    painter.drawText(0, 0, "Number of events");

    painter.restore();

    // Y-Axis ticks
    int numTicks = 5;
    QFont font = painter.font();
    font.setPointSize(8);
    painter.setFont(font);

    for (int i = 0; i <= numTicks; ++i) {
        int y = marginTop + i * (availableHeight / numTicks);
        int value = maxVal - i * (maxVal / numTicks);
        QString label = QString::number(value);
        painter.drawText(0, y + 5, marginLeft - 5, 15, Qt::AlignRight, label);
        painter.setPen(Qt::lightGray);
        painter.drawLine(marginLeft, y, w - marginRight, y);
        painter.setPen(Qt::black);
    }

    // Draw bars
    for (int i = 0; i < data.size(); ++i) {
        int barHeight = static_cast<int>((static_cast<double>(data[i]) / maxVal) * availableHeight);
        QRect barRect(
            marginLeft + i * barWidth + 5,
            h - marginBottom - barHeight,
            barWidth - 10,
            barHeight
        );
        painter.fillRect(barRect, QColor("#87CEFA"));
        painter.drawRect(barRect);

        // Month label
        std::vector<std::string> months = { "January","February","March","April","May","June","July","August","September","October","November","December" };
        QString monthLabel = QString(months[i].c_str());
        painter.drawText(barRect.x(), h - marginBottom + 15, barWidth - 10, 15, Qt::AlignCenter, monthLabel);
    }
}

