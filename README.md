# CarND PID Project

[![Udacity - Self-Driving Car NanoDegree](https://s3.amazonaws.com/udacity-sdc/github/shield-carnd.svg)](http://www.udacity.com/drive)

PID Project in Udacity's Self-Driving Car Nanodegree. The original project template can be found [here](https://github.com/udacity/CarND-PID-Control-Project).

## Basic build instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

## Tuning the controller

The first set of manually tuned parameters `(Kp, Ki,  Kd)` is `(0.3, 0., 20.)`. It was decided to keep `Ki=0` for the vehicle in the simulator. 

To automatically tune the parameters using the simulator, the `OnlineTwiddle` class is developed. It uses the logic of the twiddle algorithm, and changes the parameters after the specified number of PID controller activations. An example of calling `OnlineTwiddle` is the following:

```cpp
OnlineTwiddle controller{
    {0.9, 0., 40.}, // Starting values of the parameters 
    {0.5, 0, 20.},  // Starting values of the deltas
    7000,           // Number of activations in a cycle (full track is ~7000)
    {0, 2}          // indices (0-P, 1-I, 2-D) to tune
};
```
The best parameters obtained with `OnlineTwiddle` are `(1.95, 0., 60.)`. 

Another diagnostic tool is `PIDCounter`. It realizes PID controller and outputs the accummulated error per number of activations:

```cpp
PIDCounter controller{
    {1.95, 0., 60.}, // PID parameters
    7000             // Number of activations in a cycle
};
```
