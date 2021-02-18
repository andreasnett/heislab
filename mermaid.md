# Diagram illustrations using mermaid

## Class diagram

```mermaid
classDiagram
    Elevator <|-- Queue
    Elevator <|-- ElevatorState
    class Elevator{
      -Queue queue
      -ElevatorState state
      -boolean EmergencyStop
      +init()
      +activate()
    }

    class Queue{
      -Map map
      +getNext()
      +addToQueue(int)
      +popFromQueue(int)
      +checkStop(int)
    }

    class ElevatorState{
      +String direction
      +int targetFloor
      +int currentFloor
      +setState(int, int)
      +getState()
    }
```

## Sequence diagram

```mermaid
sequenceDiagram
    participant User
    participant Elevator
    participant Queue
    participant State
    User->>Elevator: Go to floor 1
    activate Elevator
    Elevator->>Queue: Add floor 1
    activate Queue
    Elevator->>+State: Get direction, current, target
    State-->>-Elevator: Move down, floor 2, floor 1
    Elevator-->>User: Stop floor 1
    Elevator->>Queue: Pop floor 1
    deactivate Queue
    Elevator->>+Queue: Get next stop
    Queue-->>-Elevator: N/A

    deactivate Elevator
    User->>Elevator: Go to floor 4
    activate Elevator
    Elevator->>Queue: Add floor 4
    activate Queue
    Elevator->>+State: Get direction, current, target
    State-->>-Elevator: Move up, floor 1, floor 4
    Elevator->>+Queue: Check stop floor 2
    Queue-->>-Elevator: false
    Elevator->>+Queue: Check stop floor 3
    Queue-->>-Elevator: false
    Elevator-->>User: Stop floor 4
    Elevator->>Queue: Pop floor 4
    deactivate Queue
    Elevator->>+Queue: Get next stop
    Queue-->>-Elevator: N/A
    deactivate Elevator

```

## Finite State Machine

```mermaid
stateDiagram
   [*]--> A
   A-->C: 0/0
   A-->B: 1/0

   B-->C: 0/0
   B-->A: 1/0

   C-->C: 0/0
   C-->DF: 1/0

   DF-->E:0/0
   DF-->A:1/0

   E-->C: 0/0
   E-->DF: 1/1
   E-->[*]

```
