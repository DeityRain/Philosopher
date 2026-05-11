# Philosophers

The **Philosophers** project (from School 42) introduces students to the concepts of **multithreading**, **mutexes**, and protecting shared resources.  
The goal is to simulate the famous **Dining Philosophers Problem** while avoiding **deadlocks**, **race conditions**, and **starvation**.

---

## Overview

Each philosopher cycles through three states:

- **Thinking**
- **Eating**
- **Sleeping**

To eat, a philosopher must take **two forks**, which are shared with neighbors.  
The difficulty lies in coordinating philosophers so the simulation remains accurate and consistent.

---

## Usage

Your program must be executed as:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

Parameters
Argument	Description
number_of_philosophers	Total philosophers (and forks)
time_to_die	Time (ms) before a philosopher dies if they do not eat
time_to_eat	Time (ms) a philosopher spends eating
time_to_sleep	Time (ms) a philosopher sleeps
number_of_times_each_philosopher_must_eat	(optional) Simulation stops when all have eaten this many times

How It Works
Threads

Each philosopher is represented by a thread running its routine:

Take forks

Eat

Sleep

Think

Forks

Forks are implemented as mutexes, one between each philosopher.
Mutexes

Common mutex usage:

    One mutex per fork

    A print mutex (to prevent mixed output)

    A shared state mutex to detect deaths safely

Timing

Accurate timestamps are crucial.
All logs follow the format:

[timestamp] [philosopher id] [action]

Example:

200 3 is eating

Death Detection

A monitoring system checks if any philosopher exceeds time_to_die without eating.
If one dies:

    The simulation stops immediately

    "X died" is printed once

Running Examples

make
./philo 5 800 200 200

With eating requirement:

./philo 5 800 200 200 7

Example Output

0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
...
520 2 died

Makefile

make — Build program

make clean — Remove object files

make fclean — Remove objects + binary

make re — Rebuild everything

---

## Author

**DeityRain**    
🧭 [github.com/DeityRain](https://github.com/DeityRain)
