
# Health Tracker Application

This Health Tracker Application is designed to simulate and display various health metrics, such as steps, calories burned, resting time, blood pressure, body temperature, heart rate, blood glucose, and blood oxygen levels. The application also provides the functionality to export the generated data to CSV format.

## Features

- Real-time simulation and display of various health metrics
- Dynamic charts for visualizing the data
- Ability to start and stop tracking
- Export data to CSV

## Requirements

- Qt 6.7.2 or later
- QtCharts module

## Installation

### Cloning the Repository

Clone this repository to your local machine using the following command:

```sh
git clone https://github.com/yourusername/health-tracker.git
```

## Usage

### Building the Project

1. Open the project in Qt Creator.
2. Configure the project with the appropriate Qt kit.
3. Build the project by clicking on the "Build" button or using the `Ctrl+B` shortcut.

### Running the Application

1. Run the application by clicking on the "Run" button or using the `Ctrl+R` shortcut.
2. The main window will display various health metrics being simulated in real-time.
3. Use the "Start Resting" button to switch between walking and resting modes.

### Exporting Data

1. To export the data to CSV, click on the "Export to CSV" button.
2. A file dialog will prompt you to choose the location and name of the file to save the data.

## Project Structure

- `mainwindow.h`: Header file for the main window class.
- `mainwindow.cpp`: Implementation file for the main window class.
- `mainwindow.ui`: UI file defining the layout of the main window.
- `main.cpp`: Entry point of the application.

## Dependencies

- Qt 6.7.2
- QtCharts module

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

## Contributing

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Commit your changes (`git commit -am 'Add new feature'`).
4. Push to the branch (`git push origin feature-branch`).
5. Create a new Pull Request.

For any questions or issues, please open an issue on the GitHub repository.
