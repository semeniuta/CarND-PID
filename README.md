# CarND PID Project

[![Udacity - Self-Driving Car NanoDegree](https://s3.amazonaws.com/udacity-sdc/github/shield-carnd.svg)](http://www.udacity.com/drive)

PID Project in Udacity's Self-Driving Car Nanodegree. The original project template can be found [here](https://github.com/udacity/CarND-PID-Control-Project).

## Basic build instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

## Tuning the controller

A PID controller is configured with three parameters: `(Kp, Ki,  Kd)`, corresponding to the gains of the proportional, integral, and differential components respectively. In this project they were initially tuned manually. 

At first, only `Kp` was tweaked so that the vehicle in the simulator drives relatively well. It is inherent property of a P-controller is that it leads to oscilation around the setpoint. In the case of the vehicle, it meant driving from side to side. By adding the differential component (tweaking both `Kp` and `Kd`), the oscilation was dumped.

The PD-controller after tweaking resulted in acceptable driving behavior. The `Ki` parameter showed negative effect on the system performance, and, hence, it was decided to keep `Ki=0`. As such, the following set of controller parameters was tweaked manually:

```
Kp=0.3, Ki=0., Kd=20.
```

To automatically tune the parameters using the simulator, the `OnlineTwiddle` class was developed. It uses the logic of the twiddle algorithm, and changes the parameters after the specified number of PID controller activations. It was counted that approximately 7000 activations happen during the whole cycle of the track iin the simulator, and the idea was to perform automatic tweaking of parameters using the twiddle logic after every 7000 activations. An example of calling `OnlineTwiddle` is the following:

```cpp
OnlineTwiddle controller{
    {0.9, 0., 40.}, // Starting values of the parameters 
    {0.5, 0, 20.},  // Starting values of the deltas
    7000,           // Number of activations in a cycle (full track is ~7000)
    {0, 2}          // indices (0-P, 1-I, 2-D) to tune
};
```
The best parameters obtained with `OnlineTwiddle` are the following: 

```
Kp=1.95, Ki=0., Kd=60.
```

## Misc

Another diagnostic tool is `PIDCounter`. It realizes PID controller and outputs the accummulated error per number of activations:

```cpp
PIDCounter controller{
    {1.95, 0., 60.}, // PID parameters
    7000             // Number of activations in a cycle
};
```
