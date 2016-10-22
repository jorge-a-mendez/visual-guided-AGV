# visual-guided-AGV
AGV controlled jointly by a wire-guidance system and a visual system

The project consists of two parts:

1. The first part is a low-level controller, which is implemented as a PID controller on a DEMOQE128 board. The input signal is the current read by two coils. Constraints are added to avoid collisions (using a SHARP distance sensor) and to stop on the road intersections, which are marked with black tape (using IR sensors). Lastly, the controller determines the direction to take on every intersection based on commands received from the high-level controller (part 2). So far only this part has been committed.

2. The second part is a hig-level controller, which takes user input to determine the goal location of the AGV, plans the shortest path to the goal, and sends commands via an IR transmitter to the AGV indicating the desired location.
