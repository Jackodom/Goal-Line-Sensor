# Goal Line Sensor

This project is an Arduino based program written in C++ that utilizes multiple Time of Flight sensors, multiple Arduino Nano workers, and an Arduino Uno Master. 

**Purpose:** In field Lacrosse many attempted goals can either partially cross the goal line or go too fast for the human eye to accurately tell whether the ball fully crossed the goal line. This project is meant to create an accurate and reliable system to detect when a ball fully crosses the goal line. 

# Features

- **Detects Interferences:** Uses multiple measurements across time intervals to classify objects that spend a significant amount of time in front of a sensor as an interference with the goal line.
- **Detects Goals:** Uses multiple mesurements and catergorizes motion as goal if not detected again over a certain time interval.
- **Generates Visual Output:** Creates a user friendly graph after a goal. Depicts the distance and sensor of last intereference detection and goal detection. Used to verify that the location the ball might have possible crossed is accurate.

   -
      **Visual Output Symbol meanings:**

     O = Last location of interference detection.

     X = Last location of goal detection.

# Future Improvements

- **Multi-step analysis:** Add additional methods of verifying if a detection is a goal or interference. 
- **Incorporate Bluetooth:** Enable the ability to use an Arduino HM-10 bluetooth module to allow wireless output to users.
- **Practice Mode:** Store all goals and locations of goal detections over a long period of time to output a post-practice analysis of shot placement and accuracy. 


# Acknowledgments
This project is a work in progress.




