# 🍝 Philosophers

## 🎯 About
A solution to the classic dining philosophers problem using threads and mutexes. This project demonstrates process synchronization and deadlock avoidance.

## 🔧 Prerequisites
- GCC compiler
- Make
- POSIX threads library
- Unix-based OS

## 🛠️ Installation
```bash
cd Philosophers
make
```

## 💻 Usage
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Parameters:
- `number_of_philosophers`: Number of philosophers at the table (1-250)
- `time_to_die`: Time in milliseconds before a philosopher dies from starvation
- `time_to_eat`: Time in milliseconds it takes to eat
- `time_to_sleep`: Time in milliseconds to sleep
- `number_of_times_each_philosopher_must_eat`: (Optional) Number of times each philosopher must eat

### Example:
```bash
./philo 4 410 200 200
```

## 🎮 Program Behavior
- Each philosopher is a thread
- Forks are represented by mutexes
- Philosophers alternate between eating, sleeping, and thinking
- Each philosopher needs two forks to eat
- If a philosopher doesn't start eating within `time_to_die` milliseconds, they die
- Program stops when a philosopher dies or all philosophers have eaten enough times

## 🚫 Death Conditions
- A philosopher dies if they haven't eaten for `time_to_die` milliseconds
- The simulation stops when a philosopher dies
- Death message must be displayed within 10ms of actual death

## ✨ Features
- No data races
- No deadlocks
- Memory leak free
- Proper thread synchronization

## 🔍 Status Messages
- `X has taken a fork` 🍴
- `X is eating` 🍝
- `X is sleeping` 😴
- `X is thinking` 🤔
- `X died` 💀

Where X is the philosopher number.

## 📚 Learning Outcomes
- Thread management
- Mutex usage
- Race condition prevention
- Deadlock avoidance
- Process synchronization

## 📝 License
This project is part of 42 school's curriculum. Unauthorized use or distribution is prohibited.