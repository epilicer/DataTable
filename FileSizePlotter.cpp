#include <QApplication>

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QDebug>
#include <QtCore/QDate>

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>

QT_CHARTS_USE_NAMESPACE

class FileSizePlotter : public QWidget {
public:
    FileSizePlotter(QWidget *parent = nullptr) : QWidget(parent) {
        QGridLayout *layout = new QGridLayout(this);
        m_chartView = new QChartView(this);
        layout->addWidget(m_chartView);
        m_chart = new QChart();
        m_chartView->setChart(m_chart);
        m_chartView->setRenderHint(QPainter::Antialiasing);

        QValueAxis *xAxis = new QValueAxis();
        xAxis->setTickCount(12);
        xAxis->setLabelFormat("%d/%m/%y");
        //m_chart->setAxisX(xAxis);
        m_chart->addAxis(xAxis, Qt::AlignBottom);

        QValueAxis *yAxis = new QValueAxis();
        yAxis->setLabelFormat("%d GB");
        //m_chart->setAxisY(yAxis);
        m_chart->addAxis(yAxis, Qt::AlignLeft);

        // Set up the "Browse" button
        QPushButton *browseButton = new QPushButton("Browse");
        connect(browseButton, &QPushButton::clicked, this, &FileSizePlotter::browse);
        layout->addWidget(browseButton);
    }

private:
    QChartView *m_chartView;
    QChart *m_chart;

    void browse() {
        QString fileName = QFileDialog::getOpenFileName(this, "Open CSV File", "", "CSV Files (*.csv)");
        if (fileName.isEmpty()) {
            return;
        }

        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Failed to open file:" << fileName;
            return;
        }

        m_chart->removeAllSeries();
        QLineSeries *series = new QLineSeries();
        series->setName("File Size");

        QTextStream in(&file);
        int i = 0;
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(",");
            if (fields.size() < 2) {
                qDebug() << "Invalid line:" << line;
                continue;
            }
            double fileSize = fields.at(0).toDouble();
            QString dateString = fields.at(1);
            QDate date = QDate::fromString(dateString, "yyyy/MM");
            if (!date.isValid()) {
                qDebug() << "Invalid date:" << dateString;
                continue;
            }
            series->append(date.toJulianDay(), fileSize);
            ++i;
        }
        file.close();
        m_chart->addSeries(series);
        m_chart->setTitle("Monthly File Size");
        m_chart->createDefaultAxes();
    }

};

//#include <QApplication>
//#include "FileSizePlotter.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    FileSizePlotter plotter;
    plotter.show();

    return app.exec();
}
