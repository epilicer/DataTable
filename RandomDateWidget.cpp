#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
//#include <QDateEdit>

#include "RandomDatesGenerator.h"
//#include <memory>

class RandomDateWidget : public QWidget {
public:
    RandomDateWidget(QWidget* parent = nullptr) : QWidget(parent) {
        // Create a new instance of the RandomDatesGenerator class with default dates
        std::unique_ptr<RandomDatesGenerator> m_dateGenerator(new RandomDatesGenerator("2022-01-01", "2022-12-31"));
        //m_dateGenerator = std::make_unique<RandomDatesGenerator>("2022-01-01", "2022-12-31");
        //m_dateGenerator = new RandomDatesGenerator("2022-01-01", "2022-12-31");

        // Create the layout for the widget
        QVBoxLayout* layout = new QVBoxLayout(this);

        // Create a horizontal layout for the start and end date inputs
        QHBoxLayout* dateInputLayout = new QHBoxLayout();
        layout->addLayout(dateInputLayout);

        // Create a label for the start date input
        QLabel* startDateLabel = new QLabel("Start Date:", this);
        dateInputLayout->addWidget(startDateLabel);

        // Create a line edit for the start date input
        m_startDateEdit = new QLineEdit("2022-01-01", this);
        dateInputLayout->addWidget(m_startDateEdit);

        // Create a label for the end date input
        QLabel* endDateLabel = new QLabel("End Date:", this);
        dateInputLayout->addWidget(endDateLabel);

        // Create a line edit for the end date input
        m_endDateEdit = new QLineEdit("2022-12-31", this);
        dateInputLayout->addWidget(m_endDateEdit);

        // Create a button to generate the random dates
        QPushButton* button = new QPushButton("Generate Random Dates", this);
        layout->addWidget(button);

        // Connect the button to the slot that generates the random dates
        connect(button, &QPushButton::clicked, this, &RandomDateWidget::generateRandomDates);

        // Create a label to display the title
        m_titleLabel = new QLabel("Random Dates", this);
        layout->addWidget(m_titleLabel);

        // Create a layout for the date labels
        m_dateLabelsLayout = new QVBoxLayout();
        layout->addLayout(m_dateLabelsLayout);

        // Generate the initial random dates
        generateRandomDates();
    }

private:
    QLineEdit *m_startDateEdit;
    QLineEdit *m_endDateEdit;
    QLabel* m_titleLabel;
    QVBoxLayout* m_dateLabelsLayout;
    RandomDatesGenerator* m_dateGenerator;

    void generateRandomDates() {
        // Get the start and end dates from the line edits
        std::string startDate = m_startDateEdit->text().toStdString();
        std::string endDate = m_endDateEdit->text().toStdString();

        // Create a new instance of the RandomDatesGenerator class with the user input dates
        std::unique_ptr<RandomDatesGenerator> m_dateGenerator(new RandomDatesGenerator(startDate, endDate));
        //m_dateGenerator = std::make_unique<RandomDatesGenerator>(startDate, endDate);
        //m_dateGenerator = new RandomDatesGenerator(startDate, endDate);
        
        // Generate a vector of 10 random dates
        std::vector<std::string> randomDates = m_dateGenerator->generateDates(10);

        // Update the title label
        m_titleLabel->setText("Random Dates (" + QString::fromStdString(startDate) + " to " + QString::fromStdString(endDate) + ")");

        // Remove the existing date labels
        QLayoutItem* child;
        while ((child = m_dateLabelsLayout->takeAt(0)) != nullptr) {
            delete child->widget();
            delete child;
        }

        // Loop through the random dates and add a label for each one
        for (const auto& date : randomDates) {
            QLabel* label = new QLabel(QString::fromStdString(date), this);
            m_dateLabelsLayout->addWidget(label);
        }
    }
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Create a new instance of the RandomDateWidget class
    RandomDateWidget widget;
    widget.show();

    return app.exec();
}
