#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdlib> // Para std::rand() e std::srand()
#include <ctime>   // Para std::time
#include <QDateTime>
#include <cmath>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dataGenerationTimer(new QTimer(this)),
    seriesSteps(new QLineSeries(this)),
    seriesCalories(new QLineSeries(this)),
    seriesSleep(new QLineSeries(this)),
    seriesBloodPressure(new QLineSeries(this)),
    seriesTemperature(new QLineSeries(this)),
    seriesHeartRate(new QLineSeries(this)),
    seriesBloodGlucose(new QLineSeries(this)),
    seriesBloodOxygen(new QLineSeries(this)),
    chartSteps(new QChart()),
    chartCalories(new QChart()),
    chartSleep(new QChart()),
    chartBloodPressure(new QChart()),
    chartTemperature(new QChart()),
    chartHeartRate(new QChart()),
    chartBloodGlucose(new QChart()),
    chartBloodOxygen(new QChart()),
    timeCounter(0)
{
    ui->setupUi(this);

    // Inicialize a semente para o gerador de números aleatórios
    std::srand(std::time(0));

    // Inicializar labels
    labelSteps = ui->labelSteps;
    labelCalories = ui->labelCalories;
    labelSleep = ui->labelSleep;
    labelBloodPressure = ui->labelBloodPressure;
    labelTemperature = ui->labelTemperature;
    labelHeartRate = ui->labelHeartRate;
    labelBloodGlucose = ui->labelBloodGlucose;
    labelBloodOxygen = ui->labelBloodOxygen;

    labelAverageSteps = ui->labelAverageSteps;
    labelAverageCalories = ui->labelAverageCalories;
    labelAverageSleep = ui->labelAverageSleep;
    labelAverageBloodPressure = ui->labelAverageBloodPressure;
    labelAverageTemperature = ui->labelAverageTemperature;
    labelAverageHeartRate = ui->labelAverageHeartRate;
    labelAverageBloodGlucose = ui->labelAverageBloodGlucose;
    labelAverageBloodOxygen = ui->labelAverageBloodOxygen;

    // Configurar os gráficos
    setupChart(ui->chartViewSteps, chartSteps, seriesSteps, "Steps", 0, 30000);
    setupChart(ui->chartViewCalories, chartCalories, seriesCalories, "Calories", 0, 5000);
    setupChart(ui->chartViewSleep, chartSleep, seriesSleep, "Sleep Hours", 0, 12);
    setupChart(ui->chartViewBloodPressure, chartBloodPressure, seriesBloodPressure, "Blood Pressure", 50, 200);
    setupChart(ui->chartViewTemperature, chartTemperature, seriesTemperature, "Body Temperature", 35, 42);
    setupChart(ui->chartViewHeartRate, chartHeartRate, seriesHeartRate, "Heart Rate", 40, 180);
    setupChart(ui->chartViewBloodGlucose, chartBloodGlucose, seriesBloodGlucose, "Blood Glucose", 70, 180);
    setupChart(ui->chartViewBloodOxygen, chartBloodOxygen, seriesBloodOxygen, "Blood Oxygen", 90, 100);

    // Configurar altura mínima dos gráficos
    ui->chartViewSteps->setMinimumHeight(400);
    ui->chartViewCalories->setMinimumHeight(400);
    ui->chartViewSleep->setMinimumHeight(400);
    ui->chartViewBloodPressure->setMinimumHeight(400);
    ui->chartViewTemperature->setMinimumHeight(400);
    ui->chartViewHeartRate->setMinimumHeight(400);
    ui->chartViewBloodGlucose->setMinimumHeight(400);
    ui->chartViewBloodOxygen->setMinimumHeight(400);

    connect(dataGenerationTimer, &QTimer::timeout, this, &MainWindow::generateSimulatedData);
    dataGenerationTimer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupChart(QChartView *chartView, QChart *chart, QLineSeries *series, const QString &title, int yMin, int yMax)
{
    QDateTimeAxis *axisX = new QDateTimeAxis;
    QValueAxis *axisY = new QValueAxis;

    axisX->setTickCount(10);
    axisX->setFormat("hh:mm:ss");
    axisX->setTitleText("Time");
    axisX->setRange(QDateTime::currentDateTime().addSecs(-100), QDateTime::currentDateTime());

    axisY->setRange(yMin, yMax);
    axisY->setTitleText(title);

    chart->addSeries(series);
    chart->setAxisX(axisX, series);
    chart->setAxisY(axisY, series);
    chart->setTitle(title);
    chart->legend()->setVisible(false);

    chartView->setChart(chart);
}

void MainWindow::generateSimulatedData()
{
    static int timeCounter = 0;
    static double steps = 0;
    static double calories = 0;
    static double sleep = 8;
    static double bloodPressure = 120;
    static double temperature = 37;
    static double heartRate = 75;
    static double bloodGlucose = 100;
    static double bloodOxygen = 98;

    QDateTime currentTime = QDateTime::currentDateTime();

    // Append the current data points to the series
    seriesSteps->append(currentTime.toMSecsSinceEpoch(), steps);
    seriesCalories->append(currentTime.toMSecsSinceEpoch(), calories);
    seriesSleep->append(currentTime.toMSecsSinceEpoch(), sleep);
    seriesBloodPressure->append(currentTime.toMSecsSinceEpoch(), bloodPressure);
    seriesTemperature->append(currentTime.toMSecsSinceEpoch(), temperature);
    seriesHeartRate->append(currentTime.toMSecsSinceEpoch(), heartRate);
    seriesBloodGlucose->append(currentTime.toMSecsSinceEpoch(), bloodGlucose);
    seriesBloodOxygen->append(currentTime.toMSecsSinceEpoch(), bloodOxygen);

    // Update labels with the generated data
    labelSteps->setText(QString("Steps: %1").arg(static_cast<int>(steps)));
    labelCalories->setText(QString("Calories: %1").arg(static_cast<int>(calories)));
    labelSleep->setText(QString("Sleep Hours: %1h %2min").arg(static_cast<int>(sleep)).arg(static_cast<int>((sleep - static_cast<int>(sleep)) * 60)));
    labelBloodPressure->setText(QString("Blood Pressure: %1 mmHg").arg(QString::number(bloodPressure, 'f', 1)));
    labelTemperature->setText(QString("Body Temperature: %1 °C").arg(QString::number(temperature, 'f', 1)));
    labelHeartRate->setText(QString("Heart Rate: %1 bpm").arg(static_cast<int>(heartRate)));
    labelBloodGlucose->setText(QString("Blood Glucose: %1 mg/dL").arg(QString::number(bloodGlucose, 'f', 1)));
    labelBloodOxygen->setText(QString("Blood Oxygen: %1%").arg(QString::number(bloodOxygen, 'f', 1)));

    // Update the average labels
    updateAverageLabel(seriesSteps, labelAverageSteps, "Average Steps: ", " steps");
    updateAverageLabel(seriesCalories, labelAverageCalories, "Average Calories: ", " kcal");
    updateAverageLabel(seriesSleep, labelAverageSleep, "Average Sleep Hours: ", "h %2min");
    updateAverageLabel(seriesBloodPressure, labelAverageBloodPressure, "Average Blood Pressure: ", " mmHg");
    updateAverageLabel(seriesTemperature, labelAverageTemperature, "Average Body Temperature: ", " °C");
    updateAverageLabel(seriesHeartRate, labelAverageHeartRate, "Average Heart Rate: ", " bpm");
    updateAverageLabel(seriesBloodGlucose, labelAverageBloodGlucose, "Average Blood Glucose: ", " mg/dL");
    updateAverageLabel(seriesBloodOxygen, labelAverageBloodOxygen, "Average Blood Oxygen: ", "%");

    // Generate more realistic variations for the next data points
    steps += std::max(0.0, QRandomGenerator::global()->bounded(500.0) * std::sin(timeCounter * M_PI / 180.0));
    calories += std::max(0.0, QRandomGenerator::global()->bounded(200.0) * std::sin(timeCounter * M_PI / 180.0));
    sleep = 7 + QRandomGenerator::global()->bounded(3) * std::cos(timeCounter * M_PI / 360.0);
    bloodPressure = 110 + QRandomGenerator::global()->bounded(30) + 10 * std::sin(timeCounter * M_PI / 360.0);
    temperature = 36.5 + QRandomGenerator::global()->bounded(1.0) + 0.5 * std::cos(timeCounter * M_PI / 720.0);
    heartRate = 60 + QRandomGenerator::global()->bounded(40) * std::sin(timeCounter * M_PI / 180.0);
    bloodGlucose = 90 + QRandomGenerator::global()->bounded(30) * std::cos(timeCounter * M_PI / 180.0);
    bloodOxygen = 95 + QRandomGenerator::global()->bounded(5) * std::sin(timeCounter * M_PI / 720.0);

    // Update the time counter
    timeCounter++;

    // Update the X axis range to shift the time window
    QDateTime currentTimeMinus100Secs = currentTime.addSecs(-100);
    QDateTimeAxis *axisX;

    axisX = qobject_cast<QDateTimeAxis *>(chartSteps->axisX());
    if (axisX) {
        axisX->setRange(currentTimeMinus100Secs, currentTime);
    }

    axisX = qobject_cast<QDateTimeAxis *>(chartCalories->axisX());
    if (axisX) {
        axisX->setRange(currentTimeMinus100Secs, currentTime);
    }

    axisX = qobject_cast<QDateTimeAxis *>(chartSleep->axisX());
    if (axisX) {
        axisX->setRange(currentTimeMinus100Secs, currentTime);
    }

    axisX = qobject_cast<QDateTimeAxis *>(chartBloodPressure->axisX());
    if (axisX) {
        axisX->setRange(currentTimeMinus100Secs, currentTime);
    }

    axisX = qobject_cast<QDateTimeAxis *>(chartTemperature->axisX());
    if (axisX) {
        axisX->setRange(currentTimeMinus100Secs, currentTime);
    }

    axisX = qobject_cast<QDateTimeAxis *>(chartHeartRate->axisX());
    if (axisX) {
        axisX->setRange(currentTimeMinus100Secs, currentTime);
    }

    axisX = qobject_cast<QDateTimeAxis *>(chartBloodGlucose->axisX());
    if (axisX) {
        axisX->setRange(currentTimeMinus100Secs, currentTime);
    }

    axisX = qobject_cast<QDateTimeAxis *>(chartBloodOxygen->axisX());
    if (axisX) {
        axisX->setRange(currentTimeMinus100Secs, currentTime);
    }

    // Update the Y axis range to fit the data dynamically
    updateYAxisRange(chartSteps, seriesSteps);
    updateYAxisRange(chartCalories, seriesCalories);

    // Set fixed Y axis range for other charts
    setFixedYAxisRange(chartSleep, 0, 12);
    setFixedYAxisRange(chartBloodPressure, 50, 200);
    setFixedYAxisRange(chartTemperature, 35, 42);
    setFixedYAxisRange(chartHeartRate, 40, 180);
    setFixedYAxisRange(chartBloodGlucose, 70, 180);
    setFixedYAxisRange(chartBloodOxygen, 90, 100);
}

void MainWindow::updateYAxisRange(QChart *chart, QLineSeries *series)
{
    if (!chart || !series) return;

    const auto points = series->points();
    if (points.isEmpty()) return;

    double minY = points.first().y();
    double maxY = minY;

    for (const QPointF &point : points)
    {
        if (point.y() < minY) minY = point.y();
        if (point.y() > maxY) maxY = point.y();
    }

    // Add a margin to the Y axis range
    double margin = (maxY - minY) * 0.1;
    if (margin == 0) margin = 1.0; // Garantir que haja uma margem mínima

    QValueAxis *axisY = qobject_cast<QValueAxis *>(chart->axisY());
    if (axisY)
    {
        axisY->setRange(minY - margin, maxY + margin);
    }
}

void MainWindow::setFixedYAxisRange(QChart *chart, double minY, double maxY)
{
    QValueAxis *axisY = qobject_cast<QValueAxis *>(chart->axisY());
    if (axisY)
    {
        axisY->setRange(minY, maxY);
    }
}

void MainWindow::updateAverageLabel(QLineSeries *series, QLabel *label, const QString &prefix, const QString &suffix)
{
    if (!series || !label) return;

    const auto points = series->points();
    if (points.isEmpty()) return;

    double sum = 0;
    for (const QPointF &point : points)
    {
        sum += point.y();
    }

    double average = sum / points.size();

    QString formattedAverage;
    if (prefix.contains("Sleep")) {
        int hours = static_cast<int>(average);
        int minutes = static_cast<int>((average - hours) * 60);
        formattedAverage = QString("%1h %2min").arg(hours).arg(minutes);
    } else {
        formattedAverage = QString::number(average, 'f', 1) + suffix;
    }

    label->setText(QString("%1%2").arg(prefix).arg(formattedAverage));
}
