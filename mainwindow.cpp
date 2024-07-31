#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <cstdlib>
#include <ctime>
#include <QDateTime>
#include <cmath>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dataGenerationTimer(new QTimer(this)),
    modeSwitchTimer(new QTimer(this)),
    seriesSteps(new QLineSeries(this)),
    seriesCalories(new QLineSeries(this)),
    seriesRestingTime(new QLineSeries(this)),
    seriesBloodPressure(new QLineSeries(this)),
    seriesTemperature(new QLineSeries(this)),
    seriesHeartRate(new QLineSeries(this)),
    seriesBloodGlucose(new QLineSeries(this)),
    seriesBloodOxygen(new QLineSeries(this)),
    chartSteps(new QChart()),
    chartCalories(new QChart()),
    chartRestingTime(new QChart()),
    chartBloodPressure(new QChart()),
    chartTemperature(new QChart()),
    chartHeartRate(new QChart()),
    chartBloodGlucose(new QChart()),
    chartBloodOxygen(new QChart()),
    timeCounter(0),
    isResting(false),
    totalRestingTime(0)
{
    ui->setupUi(this);

    std::srand(std::time(0));

    labelSteps = ui->labelSteps;
    labelCalories = ui->labelCalories;
    labelRestingTime = ui->labelRestingTime;
    labelBloodPressure = ui->labelBloodPressure;
    labelTemperature = ui->labelTemperature;
    labelHeartRate = ui->labelHeartRate;
    labelBloodGlucose = ui->labelBloodGlucose;
    labelBloodOxygen = ui->labelBloodOxygen;

    labelAverageSteps = ui->labelAverageSteps;
    labelAverageCalories = ui->labelAverageCalories;
    labelAverageRestingTime = ui->labelAverageRestingTime;
    labelAverageBloodPressure = ui->labelAverageBloodPressure;
    labelAverageTemperature = ui->labelAverageTemperature;
    labelAverageHeartRate = ui->labelAverageHeartRate;
    labelAverageBloodGlucose = ui->labelAverageBloodGlucose;
    labelAverageBloodOxygen = ui->labelAverageBloodOxygen;

    labelTotalRestingTime = ui->labelTotalRestingTime;

    startWalkButton = ui->startWalkButton;
    exportCsvButton = ui->exportCsvButton;

    connect(startWalkButton, &QPushButton::clicked, this, &MainWindow::onStartWalkButtonClicked);
    connect(exportCsvButton, &QPushButton::clicked, this, &MainWindow::onExportCsvButtonClicked);

    setupChart(ui->chartViewSteps, chartSteps, seriesSteps, "Steps", 0, 30000);
    setupChart(ui->chartViewCalories, chartCalories, seriesCalories, "Calories", 0, 5000);
    setupChart(ui->chartViewRestingTime, chartRestingTime, seriesRestingTime, "Resting Time", 0, 120);
    setupChart(ui->chartViewBloodPressure, chartBloodPressure, seriesBloodPressure, "Blood Pressure", 50, 200);
    setupChart(ui->chartViewTemperature, chartTemperature, seriesTemperature, "Body Temperature", 35, 42);
    setupChart(ui->chartViewHeartRate, chartHeartRate, seriesHeartRate, "Heart Rate", 40, 180);
    setupChart(ui->chartViewBloodGlucose, chartBloodGlucose, seriesBloodGlucose, "Blood Glucose", 70, 180);
    setupChart(ui->chartViewBloodOxygen, chartBloodOxygen, seriesBloodOxygen, "Blood Oxygen", 90, 100);

    ui->chartViewSteps->setMinimumHeight(400);
    ui->chartViewCalories->setMinimumHeight(400);
    ui->chartViewRestingTime->setMinimumHeight(400);
    ui->chartViewBloodPressure->setMinimumHeight(400);
    ui->chartViewTemperature->setMinimumHeight(400);
    ui->chartViewHeartRate->setMinimumHeight(400);
    ui->chartViewBloodGlucose->setMinimumHeight(400);
    ui->chartViewBloodOxygen->setMinimumHeight(400);

    connect(dataGenerationTimer, &QTimer::timeout, this, &MainWindow::generateSimulatedData);
    dataGenerationTimer->start(1000);

    connect(modeSwitchTimer, &QTimer::timeout, this, &MainWindow::switchMode);
    switchMode();
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
    static int steps = 0;
    static double calories = 0;
    static double restingTime = 0;
    static double totalRestingTime = 0;
    static double bloodPressure = 120;
    static double temperature = 37;
    static double heartRate = 75;
    static double bloodGlucose = 100;
    static double bloodOxygen = 98;

    QDateTime currentTime = QDateTime::currentDateTime();

    if (!isResting) {
        steps += 1;
        calories += 1 * (0.2 + QRandomGenerator::global()->bounded(0.4) * std::cos(timeCounter * M_PI / 360.0));
        heartRate = 100 + QRandomGenerator::global()->bounded(40) * std::sin(timeCounter * M_PI / 180.0);
        temperature = 37 + QRandomGenerator::global()->bounded(1.0) * std::cos(timeCounter * M_PI / 360.0);
        bloodPressure = 130 + QRandomGenerator::global()->bounded(20) + 10 * std::sin(timeCounter * M_PI / 360.0);
        bloodGlucose = 110 + QRandomGenerator::global()->bounded(20) * std::cos(timeCounter * M_PI / 360.0);
        bloodOxygen = 95 + QRandomGenerator::global()->bounded(5) * std::sin(timeCounter * M_PI / 720.0);
        restingTime = 0;
    } else {
        heartRate = 75 + QRandomGenerator::global()->bounded(10) * std::sin(timeCounter * M_PI / 180.0);
        temperature = 37 + QRandomGenerator::global()->bounded(0.5) * std::cos(timeCounter * M_PI / 720.0);
        bloodPressure = 120 + QRandomGenerator::global()->bounded(10) * std::sin(timeCounter * M_PI / 360.0);
        bloodGlucose = 100 + QRandomGenerator::global()->bounded(10) * std::cos(timeCounter * M_PI / 720.0);
        bloodOxygen = 98 + QRandomGenerator::global()->bounded(2) * std::sin(timeCounter * M_PI / 720.0);

        restingTime += 1.0 / 60.0;
        totalRestingTime += 1.0 / 60.0;
    }

    seriesSteps->append(currentTime.toMSecsSinceEpoch(), steps);
    seriesCalories->append(currentTime.toMSecsSinceEpoch(), calories);
    seriesRestingTime->append(currentTime.toMSecsSinceEpoch(), restingTime * 60);
    seriesBloodPressure->append(currentTime.toMSecsSinceEpoch(), bloodPressure);
    seriesTemperature->append(currentTime.toMSecsSinceEpoch(), temperature);
    seriesHeartRate->append(currentTime.toMSecsSinceEpoch(), heartRate);
    seriesBloodGlucose->append(currentTime.toMSecsSinceEpoch(), bloodGlucose);
    seriesBloodOxygen->append(currentTime.toMSecsSinceEpoch(), bloodOxygen);

    labelSteps->setText(QString("Steps: %1").arg(static_cast<int>(steps)));
    labelCalories->setText(QString("Calories: %1 kcal").arg(static_cast<int>(calories)));
    labelRestingTime->setText(QString("Resting Time: %1 s").arg(static_cast<int>(restingTime * 60)));
    labelTotalRestingTime->setText(QString("Total Resting Time: %1 s").arg(static_cast<int>(totalRestingTime * 60)));
    labelBloodPressure->setText(QString("Blood Pressure: %1 mmHg").arg(QString::number(bloodPressure, 'f', 1)));
    labelTemperature->setText(QString("Body Temperature: %1 °C").arg(QString::number(temperature, 'f', 1)));
    labelHeartRate->setText(QString("Heart Rate: %1 bpm").arg(static_cast<int>(heartRate)));
    labelBloodGlucose->setText(QString("Blood Glucose: %1 mg/dL").arg(QString::number(bloodGlucose, 'f', 1)));
    labelBloodOxygen->setText(QString("Blood Oxygen: %1%").arg(QString::number(bloodOxygen, 'f', 1)));

    updateAverageLabel(seriesSteps, labelAverageSteps, "Average Steps: ", " steps");
    updateAverageLabel(seriesCalories, labelAverageCalories, "Average Calories: ", " kcal");
    updateAverageLabel(seriesRestingTime, labelAverageRestingTime, "Average Resting Time: ", " s");
    updateAverageLabel(seriesBloodPressure, labelAverageBloodPressure, "Average Blood Pressure: ", " mmHg");
    updateAverageLabel(seriesTemperature, labelAverageTemperature, "Average Body Temperature: ", " °C");
    updateAverageLabel(seriesHeartRate, labelAverageHeartRate, "Average Heart Rate: ", " bpm");
    updateAverageLabel(seriesBloodGlucose, labelAverageBloodGlucose, "Average Blood Glucose: ", " mg/dL");
    updateAverageLabel(seriesBloodOxygen, labelAverageBloodOxygen, "Average Blood Oxygen: ", "%");

    timeCounter++;

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

    axisX = qobject_cast<QDateTimeAxis *>(chartRestingTime->axisX());
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

    updateYAxisRange(chartSteps, seriesSteps);
    updateYAxisRange(chartCalories, seriesCalories);

    setFixedYAxisRange(chartRestingTime, 0, 120);
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

    int pointCount = points.size();
    int startIndex = pointCount > 100 ? pointCount - 100 : 0;

    double minY = std::numeric_limits<double>::max();
    double maxY = std::numeric_limits<double>::lowest();

    for (int i = startIndex; i < pointCount; ++i)
    {
        const QPointF &point = points[i];
        if (point.y() < minY) minY = point.y();
        if (point.y() > maxY) maxY = point.y();
    }

    double margin = (maxY - minY) * 0.1;
    if (margin == 0) {
        margin = 1.0;
    }

    if (minY < 0) {
        minY = 0;
    }

    QValueAxis *axisY = qobject_cast<QValueAxis *>(chart->axisY());
    if (axisY)
    {
        axisY->setRange(minY, maxY + margin);
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
    if (prefix.contains("Resting Time")) {
        formattedAverage = QString::number(average, 'f', 1) + " s";
    } else {
        formattedAverage = QString::number(average, 'f', 1) + suffix;
    }

    label->setText(QString("%1%2").arg(prefix).arg(formattedAverage));
}

void MainWindow::onStartWalkButtonClicked()
{
    switchMode();
}

void MainWindow::switchMode()
{
    isResting = !isResting;
    if (isResting) {
        startWalkButton->setText("Stop resting");
        startWalkButton->setStyleSheet("background-color: red; color: white; font-size: 18px;");
        int restDuration = 20 + QRandomGenerator::global()->bounded(20);  // 20s ~ 40s
        modeSwitchTimer->start(restDuration * 1000);
    } else {
        startWalkButton->setText("Start resting");
        startWalkButton->setStyleSheet("background-color: green; color: white; font-size: 18px;");
        int walkDuration = 40 + QRandomGenerator::global()->bounded(50);  // 40s ~ 1m 30s
        modeSwitchTimer->start(walkDuration * 1000);
    }
}

void MainWindow::onExportCsvButtonClicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save CSV", "", "CSV Files (*.csv)");
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, "Error", "Could not open file for writing");
        return;
    }

    QTextStream stream(&file);
    stream << "Time,Steps,Calories,Resting Time,Blood Pressure,Body Temperature,Heart Rate,Blood Glucose,Blood Oxygen\n";

    const int pointCount = seriesSteps->points().size();
    for (int i = 0; i < pointCount; ++i) {
        QDateTime timestamp = QDateTime::fromMSecsSinceEpoch(seriesSteps->at(i).x());
        QString timeStr = timestamp.toString("yyyy-MM-dd hh:mm:ss");

        QString steps = QString::number(seriesSteps->at(i).y());
        QString calories = QString::number(seriesCalories->at(i).y(), 'f', 1);
        QString restingTime = QString::number(seriesRestingTime->at(i).y(), 'f', 1);
        QString bloodPressure = QString::number(seriesBloodPressure->at(i).y(), 'f', 1);
        QString bodyTemperature = QString::number(seriesTemperature->at(i).y(), 'f', 1);
        QString heartRate = QString::number(seriesHeartRate->at(i).y(), 'f', 1);
        QString bloodGlucose = QString::number(seriesBloodGlucose->at(i).y(), 'f', 1);
        QString bloodOxygen = QString::number(seriesBloodOxygen->at(i).y(), 'f', 1);

        stream << timeStr << "," << steps << "," << calories << "," << restingTime << "," << bloodPressure << ","
               << bodyTemperature << "," << heartRate << "," << bloodGlucose << "," << bloodOxygen << "\n";
    }

    file.close();
    QMessageBox::information(this, "Success", "Data exported successfully");
}
