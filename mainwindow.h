#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include <QTimer>
#include <QLabel>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onStartWalkButtonClicked();

private:
    Ui::MainWindow *ui;
    QTimer *dataGenerationTimer;
    QLineSeries *seriesSteps;
    QLineSeries *seriesCalories;
    QLineSeries *seriesSleep;
    QLineSeries *seriesBloodPressure;
    QLineSeries *seriesTemperature;
    QLineSeries *seriesHeartRate;
    QLineSeries *seriesBloodGlucose;
    QLineSeries *seriesBloodOxygen;

    QChart *chartSteps;
    QChart *chartCalories;
    QChart *chartSleep;
    QChart *chartBloodPressure;
    QChart *chartTemperature;
    QChart *chartHeartRate;
    QChart *chartBloodGlucose;
    QChart *chartBloodOxygen;

    int timeCounter;
    bool isWalking;

    // Adicionar membros QLabel
    QLabel *labelSteps;
    QLabel *labelCalories;
    QLabel *labelSleep;
    QLabel *labelBloodPressure;
    QLabel *labelTemperature;
    QLabel *labelHeartRate;
    QLabel *labelBloodGlucose;
    QLabel *labelBloodOxygen;

    QLabel *labelAverageSteps;
    QLabel *labelAverageCalories;
    QLabel *labelAverageSleep;
    QLabel *labelAverageBloodPressure;
    QLabel *labelAverageTemperature;
    QLabel *labelAverageHeartRate;
    QLabel *labelAverageBloodGlucose;
    QLabel *labelAverageBloodOxygen;

    QPushButton *startWalkButton;

    // Declarar a função setupChart
    void setupChart(QChartView *chartView, QChart *chart, QLineSeries *series, const QString &title, int yMin, int yMax);
    void updateYAxisRange(QChart *chart, QLineSeries *series); // Adicionar a declaração da função
    void setFixedYAxisRange(QChart *chart, double minY, double maxY);
    void updateAverageLabel(QLineSeries *series, QLabel *label, const QString &prefix, const QString &suffix);
    void generateSimulatedData();
};

#endif // MAINWINDOW_H
