## Storage configuration

Configure the SD card as follows:

- Create one or more FAT32 partitions.
- The main partition must be named **MK_SYSTEM**.
- A minimum size of **512 MB per partition** is required.
- Supported cluster sizes range from **512 to 65,536 bytes**.

### Example

Below is an example of a possible layout with the main partition and two optional partitions:

- Main partition (**mandatory**): **MK_SYSTEM**

> mk  
>> apps  
>> shell  
>> supervisor  
>> ...  

> ...

- User partition 1 (**optional**): **no name constraint**

> ...

- User partition 2 (**optional**): **no name constraint**

> ...
