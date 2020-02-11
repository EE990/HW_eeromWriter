# Lite eeprom read/write tool
  English | [ 繁體中文 ](https://github.com/EE990/HW_eeromWriter/README.zh_TW.md)
  - MCU : ht32f1755
  - pin:
    * I2C_SCL - pb15
    * I2C_SDA - pc0
    * COM_TX  - pa4
    * COM_RX  - pa5
### usart command
Write:<br>

BYTES | byte0,1,2,3,4,5,6<br>(head) | byte7<br>(write Flag) | byte8,9,10,11<br>(page) | byte12 | byte13 | byte14 | byte15 | ... | byteXX | 
:---: | :---: | :---: | :---: |:---: |:---: |:---: |:---: |:---: |:---: 
Data | "+++Rom:"<br>(0x2b 0x2b 0x2b 0x52 0x6f 0x6d 0x3a) | 0x01 | 0xXX | Data0 | Data1 | Data2 | Data3 | ... | Data max1023 | 
<br>
Read:<br>

BYTES | byte0,1,2,3,4,5,6<br>(head) | byte7<br>(write Flag) | byte8,9,10,11<br>(start page) | byte12,13,14,15<br>(end page) | 
:---: | :---: | :---: | :---: |:---: |
Data | "+++Rom:"<br>(0x2b 0x2b 0x2b 0x52 0x6f 0x6d 0x3a) | 0x00 | 0xXX | 0xXX | 
