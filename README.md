# Win11_24H2_KB5086672_Input_Regression

## Summary
A simple tool to diagnose input message issues found in Windows 11 (Build 26100.8117). 

It compares physical key states with OS keyboard hooks to identify potential regressions.

## Technical Detail
Method: Uses GetAsyncKeyState and WH_KEYBOARD_LL.

Goal: Detect discrepancies between hardware input and OS message delivery.

Status: Tested on Windows 11 Pro.

## Usage
Build in Visual Studio (x64).

Run the executable.

Check the console for sync status.

Press ESC to exit.

(Currently monitors Left Ctrl and A keys only)


## Result

KB5086672(26100.8117)


https://github.com/user-attachments/assets/6b537596-5303-4e15-aab8-7139919e1677


