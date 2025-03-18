# Window Streaming App

Window Streaming App is a C++ Qt-based application that streams video and audio while offering an enhanced user interface with media controls, scheduling capabilities, and real-time updates. This project serves as a starting point for developing multimedia streaming applications with a modular design and clear separation between UI and logic.

## Features

- **Video & Audio Streaming:** Play media streams from a URL or local file.
- **User Controls:** Play, pause, and stop buttons to manage playback.
- **Media Slider:** Track and adjust the current playback position.
- **URL Input:** Easily specify or change the media stream source.
- **Scheduling:** Use a date-time widget to schedule the start of streaming.
- **Real-Time Clock:** A status bar displays the current date and time, updating every second.
- **Modular Design:** Clear separation between UI setup and media handling logic.

## Requirements

- **Qt Framework:** This project is built using Qt (version 5 or 6 recommended).
- **C++ Compiler:** A C++ compiler that supports C++11 or later.
- **Operating System:** Windows (the code is designed as a Windows application but can be adapted for other OS with minor modifications).

## Installation and Build Instructions

1. **Install Qt:**
   - Download and install the latest version of [Qt](https://www.qt.io/download).

2. **Clone or Download the Repository:**
   ```bash
   git clone https://github.com/yourusername/ComplexStreamApp.git
   cd ComplexStreamApp
   ```
Open the Project:

Open ComplexStreamApp.pro in Qt Creator.
Build the Project:

Click on the Build button or run:

```bash
qmake
make
```


On Windows, you might use:


```bash
qmake
nmake
```
or simply build through Qt Creator.
Run the Application:

After building, run the executable from Qt Creator or via your file explorer.
Usage
Launching the App:

When you run the application, the main window will appear with a video area, media control buttons, a playback slider, a URL input field, and a date/time widget for scheduling.
Streaming Media:

Enter a valid media URL in the URL input field or use the "Open Stream" menu option to load a media file.
Click Play. If a future date/time is specified in the scheduler, playback will start at that time; otherwise, it will begin immediately.
Use the Pause and Stop buttons to control playback.
Adjust the slider to seek to a different position in the stream.
