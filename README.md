# TimesheetAssistant
 An assistant that helps you fill out your timesheets by automatically calculating your working hours. (Windows only)

### What it looks like so far (could be better):
  ![mainwindow](https://github.com/alexmo16/TimesheetAssistant/blob/master/screenshots/mainwindow.PNG)

## Dependencies:
  - Qt 5.14.1
  - wevtapi.lib (Windows library for events logs)

## Development setup:
  - The current setup only works with visual studio, feel free to add a qt-creator setup.
  - Build step for deployment needs VCINSTALLDIR env variable, if it is not defined, please add it to your system environment variables.
  - You will need to activate some new local security policies to activate Logon/Logout events, see Help > TimesheetAssistant Help to know how to activate those.
  
## Release Installation:
  - In released zip folder, execute vc_redist.x64.exe before running TimesheetAssistant.
  - You will need to activate some new local security policies to activate Logon/Logout events, see Help > TimesheetAssistant Help to know how to activate those.