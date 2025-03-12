#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QSlider>
#include <QPushButton>
#include <QDateTimeEdit>
#include <QLabel>
#include <QAction>
#include <QLineEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openStream();
    void playStream();
    void pauseStream();
    void stopStream();
    void updatePosition(qint64 position);
    void sliderMoved(int position);
    void handleMediaStatusChanged(QMediaPlayer::MediaStatus status);

private:
    void setupUi();
    void setupConnections();

    QMediaPlayer *player;
    QVideoWidget *videoWidget;
    QSlider *positionSlider;
    QPushButton *playButton;
    QPushButton *pauseButton;
    QPushButton *stopButton;
    QDateTimeEdit *scheduleEdit;
    QLabel *currentTimeLabel;
    QLineEdit *urlLineEdit;
    QAction *openAction;
};

#endif // MAINWINDOW_H
