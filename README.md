# Typing Trainer

**A real-time typing habit correction tool** built with C++/CLI and WinForms.

---

## Table of Contents

* [Overview](#overview)
* [Features](#features)
* [Getting Started](#getting-started)

  * [Prerequisites](#prerequisites)
  * [Building](#building)
  * [Running](#running)
* [Usage](#usage)
* [Project Structure](#project-structure)
* [Extensibility](#extensibility)
* [License](#license)

---

## Overview

Typing Trainer is a desktop application that captures your keystrokes in real time, analyzes typing speed, accuracy, and backspace patterns, and provides personalized feedback and practice sentences to improve your typing habits. It supports a library of 100+ English proverbs selected randomly to keep practice engaging.

## Features

* **Real-time data collection**: Records each keypress, timestamp, and backspace usage.
* **Accuracy and speed analysis**: Displays accuracy as a pie chart and speed over time in a line chart.
* **Error heatmap**: Visualizes error frequency across the sentence.
* **Dynamic training mode**: Extracts mis‐typed words, prompts you to practice them, then requires you to type the full sentence correctly before moving on.
* **Proverb library**: Randomly selects from 100+ English proverbs.
* **Save & Load**: Persist and restore typing sessions (autosave on exit).

## Getting Started

### Prerequisites

* Windows 10/11
* Visual Studio 2022 with C++/CLI and .NET desktop development workloads
* .NET Framework 4.8 or later

### Building

1. Clone this repository.
2. Open `TypingTrainer.sln` in Visual Studio.
3. Restore NuGet packages if prompted.
4. Build the solution (Release or Debug).

### Running

* Locate `TypingTrainer.exe` under `bin\Debug` (or `bin\Release`).
* Double-click to launch.

## Usage

1. **Practice**: A random proverb appears at the top. Type the full sentence into the textbox.
2. **Analyze**: Click **Analyze** to see charts and heatmap.
3. **Train**: If mistakes occurred, a list of mis‐typed words appears. Type each word correctly to clear them.
4. **Next**: After mastering the full sentence, the app automatically selects a new proverb.
5. **Save/Load**: Use **Save** and **Load** to persist session data.

## Project Structure

```
/src
  ├─ Form1.h        # UI definitions and event declarations
  ├─ Form1.cpp      # Logic for analysis, training mode, navigation
  ├─ TypingSession.h/.cpp  # Keystroke event storage
  ├─ Analyzer.h/.cpp       # Accuracy, speed, backspace analysis
  ├─ Trainer.h/.cpp        # Generate practice segments
  └─ FileManager.h/.cpp    # Session serialization

/README.md         # This file
/TypingTrainer.sln # Visual Studio solution
```

## Extensibility

* **Phrase List**: Replace or extend the `references` array in `Form1.cpp` to customize practice sentences.
* **Analysis Metrics**: Add new metrics (e.g. WPM, consistency) in `Analyzer.cpp` and hook into the UI.
* **Themes**: Swap WinForms controls or integrate other charting libraries.

## License

This project is released under the [MIT License](LICENSE).
