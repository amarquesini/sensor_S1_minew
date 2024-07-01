
## IDENTIFICACION DE DISPOSITIVOS BLE

* 00 = Sensor 1
* 01 = Sensor 2

## COMANDOS

### FORMATO PARA SETEO DE MAC ADDRESS

$[BB]MA[XX:XX:XX:XX:XX:XX]#

Donde:  
BB = Dispositivo BLE apuntado,  
XX:XX:XX:XX:XX:XX = MAC Address a configurar

Ej: $00MAAC:23:3F:AE:02:3F# Setea la mac address del sensor 1

### FORMATO GENERAL

$[BB][CC][VV]#

donde:   
BB = dispositivo ble apuntado,  
CC = comando  
VV = valor a configurar (cuando corresponda)

En algunos comandos el valor de BB o de VV puede ser indistinto.  
En los siguientes ejemplos "XX" singnifica que este valor es indistinto. Se recomienda dejarlo en "00".

* ENABLE (EN)
    * Permite habilitar o deshabilitar el sensor correspondiente.
    * Ej: ?01EN01# (habilita sensor 2), ?01EN00# (deshabilita sensor 2)
* SHOW PARAMS (SP) 
    * Permite ver las configuraciones actuales.
    * Ej: ?01SPXX#
* SET DEFAULT (SD)
    * Permite configurar valores por defecto en todos los parametros.
    * Ej: ?XXSDXX#
