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
      +hasIntermediaryFloor(int)
    }

    class ElevatorState{
      +String direction
      +int targetFloor
      +int nextFloor
      +setState(int, int)
      +getState()
    }
```

## Sequence diagram

```mermaid
sequenceDiagram
    User->>+Elevator: Go to floor 4
    User->>+Elevator: Stop at floor 2
    Elevator-->>-User: Stopping at floor 2
    Elevator-->>-User: Stopping at floor 4
```
