# TimesheetAssistant
 An assistant that helps you fill out your timesheets by automatically calculating your working hours. (Windows only)

## Dependencies:
  - Qt 5.14.1
  - wevtapi.lib (Windows library for events logs)

## Development setup:
  - The current setup only works with visual studio, feel free to add a qt-creator setup.
  - Build step for deployment needs VCINSTALLDIR env variable, if it is not defined, please add it to your system environment variables.

## Installation:
  - In released zip folder, execute vc_redist.x64.exe before running TimesheetAssistant.