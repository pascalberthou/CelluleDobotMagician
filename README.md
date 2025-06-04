# CelluleDobotMagician
Cellule d'assemblage basée sur le bras Dobot Magician et des communications ModbusTCP.

/Documentation : documentation générale sur les librairies et matériel utilisé
/Libs : Librairies utilisées
/Modbus-Serveur-Arduino : programme arduino permettant la commande de la cellule depuis un arduino. Recoit les commandes depuis modbus.
/Modbus-Client: Programme C permettant de generer les commandes modbus pour piloter la Cellule


Configuration réseau : 
Serveur-Arduino : @IP=169.254.36.66 (dans le .ino) ou ... @IP=169.254.250.222 - port modbus 502 (dans le .c). Verifier l'homogenité des adresses ... 
 
