/*
This code creates a Qt main window that displays a scatter plot of 100 random data points. 
The x-axis shows the time since the Unix epoch (in seconds), and the y-axis shows a random 
number between 0 and 100. The start and end dates for the data points are generated randomly, 
and the data points themselves are also generated randomly. The chart is created using the 
QChart and QScatterSeries classes from the Qt Charts module, and is displayed using a QChartView widget.	
*/
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QScatterSeries>

#include <random>
#include <chrono>

#include "RandomDateGenerator.h"

QT_CHARTS_USE_NAMESPACE

class RandomDateWidget : public QMainWindow
{
public:
    RandomDateWidget(QWidget *parent = nullptr) : QMainWindow(parent)
    {
        // Set up the chart
        QChart *chart = new QChart();
        chart->setTitle("Random Scatter Plot");
        chart->legend()->hide();

        m_dateGenerator = new RandomDateGenerator("2022-01-01", "2022-12-31");
        
        // Create a random number generator
        std::uniform_real_distribution<> number_dist(0.0, 100.0);

        // Create a scatter series and populate it with random data
        QScatterSeries *series = new QScatterSeries();
        series->setName("Random Data");
        for (int i = 0; i < 100; i++) {
            auto date = m_dateGenerator->generate_date();
            qreal x = date.time_since_epoch().count();
            qreal y = number_dist(gen);
            *series << QPointF(x, y);
        }

        // Add the series to the chart and create a chart view to display it
        chart->addSeries(series);
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        // Set the central widget of the main window to be the chart view
        setCentralWidget(chartView);
    }

private:
    RandomDateGenerator* m_dateGenerator;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RandomDateWidget w;
    w.show();
    return a.exec();
}
