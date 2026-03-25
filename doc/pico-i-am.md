# Pico isolated analogue measurement

## State machine

```plantuml
@startuml
[*] --> Disconnected
Disconnected --> Connected : net_state_next == NetConnOk
Connected --> Disconnected : net_state_next == NetConnLoss
@enduml
```