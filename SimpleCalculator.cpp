
#define FLOATING_POINT
//#undef  FLOATING_POINT

#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#ifdef FLOATING_POINT
#include <QtWidgets/QDoubleSpinBox>
#else
#include <QtWidgets/QLineEdit>
#endif
#include <QtWidgets/QLabel>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QtWidgets/QMessageBox>

class SimpleCalculator : public QWidget {
public:
    SimpleCalculator(QWidget *parent = nullptr) : QWidget(parent) {
        // Create the input boxes and button
#ifdef FLOATING_POINT
        m_input1 = new QDoubleSpinBox(this);
        m_input2 = new QDoubleSpinBox(this);
#else
        m_input1 = new QLineEdit(this);
        m_input2 = new QLineEdit(this);
#endif
        m_buttonAdd = new QPushButton("+", this);
        m_buttonSubtract = new QPushButton("-", this);
        m_buttonMultiply = new QPushButton("*", this);
        m_buttonDivide = new QPushButton("/", this);
        m_buttonEquals = new QPushButton("=", this);

        // Create the layout
        auto *hLayout1 = new QHBoxLayout;
        hLayout1->addWidget(new QLabel("Input 1:", this));
        hLayout1->addWidget(m_input1);

        auto *hLayout2 = new QHBoxLayout;
        hLayout2->addWidget(new QLabel("Input 2:", this));
        hLayout2->addWidget(m_input2);

        auto *hLayout3 = new QHBoxLayout;
        hLayout3->addWidget(m_buttonAdd);
        hLayout3->addWidget(m_buttonSubtract);
        hLayout3->addWidget(m_buttonMultiply);
        hLayout3->addWidget(m_buttonDivide);
        hLayout3->addWidget(m_buttonEquals);

        auto *vLayout = new QVBoxLayout;
        vLayout->addLayout(hLayout1);
        vLayout->addLayout(hLayout2);
        vLayout->addLayout(hLayout3);

        // Set the layout
        setLayout(vLayout);

        // Connect the button to the slot
        connect(m_buttonAdd, &QPushButton::clicked, this, &SimpleCalculator::performAddition);
        connect(m_buttonSubtract, &QPushButton::clicked, this, &SimpleCalculator::performSubtraction);
        connect(m_buttonMultiply, &QPushButton::clicked, this, &SimpleCalculator::performMultiplication);
        connect(m_buttonDivide, &QPushButton::clicked, this, &SimpleCalculator::performDivision);
        connect(m_buttonEquals, &QPushButton::clicked, this, &SimpleCalculator::displayResult);
    }

private slots:
    /*
    Qt-specific keyword that indicates that the following member functions are slots, which are functions that can be connected to signals.

    In Qt, signals and slots are used for communication between objects. 
    A signal is emitted by an object when something happens, and a slot is a function that gets called in response to a signal. 
    When a signal is emitted, all the slots connected to it are called.

    In this code, we have several slots that are connected to the buttons' clicked() signals. 
    For example, the performAddition() slot is connected to the clicked() signal of the m_buttonAdd button using the connect() function.

    By default, all slots are declared as private in a QObject subclass, which is the base class of the SimpleCalculator class. 
    Therefore, we need to use the private slots keyword to declare our slots as private in the SimpleCalculator class. 
    This is not a standard C++ keyword, but a Qt-specific one.
    */
    void performAddition() {
#ifdef FLOATING_POINT
        m_result = m_input1->value() + m_input2->value();
#else
        m_result = m_input1->text().toInt() + m_input2->text().toInt();
#endif
    }

    void performSubtraction() {
#ifdef FLOATING_POINT
        m_result = m_input1->value() - m_input2->value();
#else
        m_result = m_input1->text().toInt() - m_input2->text().toInt();
#endif
    }

    void performMultiplication() {
#ifdef FLOATING_POINT
        m_result = m_input1->value() * m_input2->value();
#else
        m_result = m_input1->text().toInt() * m_input2->text().toInt();
#endif
    }

    void performDivision() {
#ifdef FLOATING_POINT
        if (m_input2->value() == 0) {
#else
        if (m_input2->text().toInt() == 0) {
#endif
            QMessageBox::warning(this, "Error", "Division by zero is not allowed.");
            return;
        }
#ifdef FLOATING_POINT
        m_result = m_input1->value() / m_input2->value();
#else
        m_result = m_input1->text().toInt() / m_input2->text().toInt();
#endif
    }

    void displayResult() {
        QMessageBox::information(this, "Result", QString("The result is %1").arg(m_result));
    }

private:
#ifdef FLOATING_POINT
    QDoubleSpinBox *m_input1;
    QDoubleSpinBox *m_input2;
#else
    QLineEdit *m_input1;
    QLineEdit *m_input2;
#endif
    QPushButton *m_buttonAdd;
    QPushButton *m_buttonSubtract;
    QPushButton *m_buttonMultiply;
    QPushButton *m_buttonDivide;
    QPushButton *m_buttonEquals;
#ifdef FLOATING_POINT
    double m_result = 0.;
#else
    int m_result = 0;
#endif
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    SimpleCalculator ui;
    ui.show();

    return app.exec();
}
 