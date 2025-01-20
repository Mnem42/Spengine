# Event system

## Event quenes

```mermaid
---
  config:
    class:
      hideEmptyMembersBox: true
---

classDiagram
	class EVT["Event"]
		EVT: #volatile State write_lock
		EVT: #any contained

		EVT: +Event~T~(T in) Event
		EVT: +Event(void* in) Event

	class EQ["EventQuene"] 
		<<Abstract>> EQ
		EQ: #vector~Event~ itemsS
		EQ: +add_event()

	class EQT["EventQuene"] 
		<<Interface>> EQT
		EQT: #vector~Event~ items
		EQT: +add_event()
		note for EQT "Technically a concept, so this can only work for C++ 20 and above"
    class SEQ["SimpleEventQuene"]
		SEQ: +filter_events(type) vector~Event~

	class DEQ["DelegatingEventQuene"]
		DEQ: +DelegatingEventQuene(vector~idk~ table)

	EQ ..|> SEQ
	EQ ..|> DEQ
	EQT ..|> SEQ
	EQT ..|> DEQ
```

## Event handlers

### Calling

There are multiple different ways to call an event. The applicability of each
depends on the type of event and how it's triggered. For example, calling convention
B makes more sense for things like IO input events, because it isn't a problem if 
anything is unhandled. 

However, calling convention A makes more sense for events 
that have to be responded to, or for long running background processes like downloading
a file.

#### Calling convention A

In this option, the handler is instructed by the quene to handle an event sent
by the caller. The handler directly notifies the caller if it succeeds.

```mermaid
sequenceDiagram
participant C   as Caller
participant H   as Handler
participant MT  as Quene
participant ERR as Error handler

C-)MT:    Do something
MT->>H:   Do what the caller said
H-->>ERR: Error details
H-->>C:   Notify caller if error occurs
H-->>C:   Send return data <br/> if required
```

#### Calling convention B

In this option, the handler polls the quene to check if there's something it has
to respond to, and calls it. It directly notifies 
the caller if there's an error and also directly 
provides any return data

```mermaid
sequenceDiagram
participant C   as Caller
participant H   as Handler
participant MT  as Quene
participant ERR as Error handler

C-)MT:    Do something
loop
H->>MT:   Do I have to do anything?
H-->>ERR: Error details
H-->>C:   Notify caller if error occurs
H-->>C:   Send return data <br/> if required
end
```