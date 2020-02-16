# LIBS Autofocus

Laser-Induced Breakdown Spectroscopy (LIBS) can be used to analyse the composition of materials. However, to improve the accuracy, multiple measurements at different angles are necessary. As the surface of samples is not even, a lens needs to be manually adjusted to let the laser focus on the surface. So, my supervisor asked to develop an autofocus system for this spectroscopy.

## Hardware

* Kinesis TCube DC Servo Motor

* Microvision Industrial Camera

## Library

* Microsoft Foundation Class Library 

* OpenCV

* Kinesis SDK

* Microvision SDK

# Strategy

* Acquire pictures at different points
* Use a no reference image quality evaluation algorithm to assign a score for each picture
* Use *Least Squares Regression* to find the optimal position.
