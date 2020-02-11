# 精簡型eeprom讀寫工具
[ English ](https://github.com/EE990/HW_eeromWriter/blob/master/README.zh_TW.md) | 繁體中文
  - 使用MCU : ht32f1755
  - 腳位定義:
    * I2C_SCL - pb15
    * I2C_SDA - pc0
    * COM_TX  - pa4
    * COM_RX  - pa5
### USART 指令
Write:<br>

BYTES | byte0,1,2,3,4,5,6<br>(head) | byte7<br>(write Flag) | byte8,9,10,11<br>(page) | byte12 | byte13 | byte14 | byte15 | ... | byteXX | 
:---: | :---: | :---: | :---: |:---: |:---: |:---: |:---: |:---: |:---: 
Data | "+++Rom:"<br>(0x2b 0x2b 0x2b 0x52 0x6f 0x6d 0x3a) | 0x01 | 0xXX | Data0 | Data1 | Data2 | Data3 | ... | Data max1023 | 
<br>
Read:<br>

BYTES | byte0,1,2,3,4,5,6<br>(head) | byte7<br>(write Flag) | byte8,9,10,11<br>(start page) | byte12,13,14,15<br>(end page) | 
:---: | :---: | :---: | :---: |:---: |
Data | "+++Rom:"<br>(0x2b 0x2b 0x2b 0x52 0x6f 0x6d 0x3a) | 0x00 | 0xXX | 0xXX | 
