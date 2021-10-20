This is a VHDL representation of a traffic light. The sequence goes as follows:

1.)  
  NORTH/SOUTH:Green
  EAST/WEST: Red
  
2.)  
  NORTH/SOUTH: Yellow
  EAST/WEST: Red
 
3.)  
  NORTH/SOUTH: Red
  EAST/WEST: Red
 
 4.)  
  NORTH/SOUTH:Red
  EAST/WEST: Green
  
5.)  
  NORTH/SOUTH:Red
  EAST/WEST: Yellow

6.)  
  NORTH/SOUTH:Red
  EAST/WEST: Red
  
  In order to achieve this, we used clock division to ensure that some instances stayed on for 5 seconds and others stayed on for 1 second. The DE1 board has an internal clock of 50mhz 
  so we divided it down to 6hz. 
  
  Light Bits:
  Bits[2-1] N/S : 10, Green; 01, Red; 11, Yellow
  Bits[1-0] E/W : 10, Green; 01, Red; 11, Yellow
  
  
  
