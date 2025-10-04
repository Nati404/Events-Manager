#pragma once
#include <QWidget>
#include <vector>

class BarChartWidget : public QWidget {
    Q_OBJECT
public:
    explicit BarChartWidget(const std::vector<int>& eventsPerMonth, QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    std::vector<int> data;
};