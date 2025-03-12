#include "mainwindow.h"
#include <QMenuBar>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTimer>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();
    setupConnections();

    // Update current time every second in the status bar
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=](){
        currentTimeLabel->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    });
    timer->start(1000);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUi()
{
    // Create the central widget and main layout
    QWidget *central = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(central);

    // Video widget setup
    videoWidget = new QVideoWidget(this);
    videoWidget->setMinimumSize(640, 480);
    mainLayout->addWidget(videoWidget);

    // Control panel layout
    QHBoxLayout *controlLayout = new QHBoxLayout();

    playButton = new QPushButton("Play", this);
    pauseButton = new QPushButton("Pause", this);
    stopButton = new QPushButton("Stop", this);
    controlLayout->addWidget(playButton);
    controlLayout->addWidget(pauseButton);
    controlLayout->addWidget(stopButton);

    // Media position slider
    positionSlider = new QSlider(Qt::Horizontal, this);
    positionSlider->setRange(0, 100);
    controlLayout->addWidget(positionSlider);

    // URL entry for the media stream
    urlLineEdit = new QLineEdit(this);
    urlLineEdit->setPlaceholderText("Enter stream URL");
    controlLayout->addWidget(urlLineEdit);

    // Date/time edit widget to schedule stream start
    scheduleEdit = new QDateTimeEdit(QDateTime::currentDateTime(), this);
    scheduleEdit->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
    controlLayout->addWidget(scheduleEdit);

    mainLayout->addLayout(controlLayout);
    setCentralWidget(central);

    // Menu bar with an "Open Stream" action
    openAction = new QAction("Open Stream", this);
    menuBar()->addAction(openAction);

    // Status bar showing the current time
    currentTimeLabel = new QLabel(this);
    statusBar()->addPermanentWidget(currentTimeLabel);

    // Media player setup
    player = new QMediaPlayer(this);
    player->setVideoOutput(videoWidget);
}

void MainWindow::setupConnections()
{
    connect(openAction, &QAction::triggered, this, &MainWindow::openStream);
    connect(playButton, &QPushButton::clicked, this, &MainWindow::playStream);
    connect(pauseButton, &QPushButton::clicked, this, &MainWindow::pauseStream);
    connect(stopButton, &QPushButton::clicked, this, &MainWindow::stopStream);
    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::updatePosition);
    connect(positionSlider, &QSlider::sliderMoved, this, &MainWindow::sliderMoved);
    connect(player, &QMediaPlayer::mediaStatusChanged, this, &MainWindow::handleMediaStatusChanged);
}

void MainWindow::openStream()
{
    // Use the URL from the text field or let the user select a file if the field is empty
    QString url = urlLineEdit->text();
    if(url.isEmpty()) {
        url = QFileDialog::getOpenFileName(this, "Open Media", "", "Media Files (*.*)");
    }
    if(!url.isEmpty()){
        player->setMedia(QUrl(url));
    }
}

void MainWindow::playStream()
{
    // Check if the scheduled time is in the future; if so, delay the play
    QDateTime scheduledTime = scheduleEdit->dateTime();
    QDateTime now = QDateTime::currentDateTime();
    if(scheduledTime > now) {
        int delay = now.msecsTo(scheduledTime);
        QTimer::singleShot(delay, player, &QMediaPlayer::play);
    } else {
        player->play();
    }
}

void MainWindow::pauseStream()
{
    player->pause();
}

void MainWindow::stopStream()
{
    player->stop();
}

void MainWindow::updatePosition(qint64 position)
{
    if(player->duration() > 0) {
        int sliderPos = static_cast<int>((position * 100) / player->duration());
        positionSlider->setValue(sliderPos);
    }
}

void MainWindow::sliderMoved(int position)
{
    if(player->duration() > 0) {
        qint64 newPosition = (player->duration() * position) / 100;
        player->setPosition(newPosition);
    }
}

void MainWindow::handleMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    // Optional: handle media status changes (e.g., buffering or end of media)
    if(status == QMediaPlayer::EndOfMedia) {
        positionSlider->setValue(0);
    }
}
