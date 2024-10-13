# Event system

The event system handles all events, both user defined and builtin. This is also how units interface.

## Event items

An event is stored as an `Evt*`. The `Evt` struct contains the following fields:

| Name           | Type            | Description                                                                                       |
|----------------|-----------------|---------------------------------------------------------------------------------------------------|
| `listener`     | `uint8_t`       | The type of receiver the event should be detected by.                                             |
| `evt_type`     | `uint8_t`       | The type of an event. Enum used depends on context.                                               |
| `data`         | `void*`         | The data to send. The type before casting is defined by the type of function and what it needs.   |
| `retdata`      | `void*`         | The data to return. The type of data return is defined by the type of function and what it needs. |
| `return_ready` | `volatile bool` | Whether the return data is ready to be used. This is important for multithreading.                |

The event consumer must set `return_ready`, even if it's not multithreading.

## Event listener block arrangement

| Range     | Description                                                                                                                                             |
|-----------|---------------------------------------------------------------------------------------------------------------------------------------------------------|
| 0x01-0x07 | `Hardware_query` `Capabilities_query`                                                                                                                   |
| 0x08-0x0F | `Drawer_required_A` `Drawer_required_B` `Drawer_optional_A` `Drawer_optional_B` `Drawer_optional_C`                                                     |
| 0x10-0x39 | These may be used by system requests in the future, **DO NOT** use                                                                                      |
| 0x40-0x7E | Internal driver communication, if required. Be careful this, and it's a good idea to provide offsetability, to prevent conflicts. Be frugal with these. |
| 0x7F-0xFF | User defined queries                                                                                                                                    |