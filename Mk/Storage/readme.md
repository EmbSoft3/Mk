## Storage configuration

Configure the SD card as follows:

 - Create one or more FAT32 partitions. 
 - The name of the main partition must be **MK_SYSTEM**.
 - A minimum of 512MB for each partition is required. Supported cluster sizes range from 512 to 65536 bytes.

### Example

Below is an example of a possible organization with the main partition and two optional partitions :

- Main partition (**mandatory**) : **MK_SYSTEM**

>- mk

>>- apps
>>- shell
>>- supervisor
>>- ...

>- ...

- User partition 1 (**optional**) : **NO NAME CONSTRAINT**

> ...

- User partition 2 (**optional**) : **NO NAME CONSTRAINT**

> ...

