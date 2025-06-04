# CelluleDobotMagician
Cellule d'assemblage basée sur le bras Dobot Magician et des communications ModbusTCP.

/Documentation : documentation générale sur les librairies et matériel utilisé
/Libs : Librairies utilisées
/Modbus-Serveur-Arduino : programme arduino permettant la commande de la cellule depuis un arduino. Recoit les commandes depuis modbus.
/Modbus-Client: Programme C permettant de generer les commandes modbus pour piloter la Cellule

Configuration réseau : 
Serveur-Arduino : @IP=169.254.36.66 (dans le .ino) ou ... @IP=169.254.250.222 - port modbus 502 (dans le .c). Verifier l'homogenité des adresses ... 
 
Modification du git : 

Declarer les clés et les ajouter au git : 
ssh-keygen -t ed25519 -C "myname@mydomain.fr"  
ssh-add --apple-use-keychain ~/.ssh/id_ed25519
cat ~/.ssh/id_ed25519.pub -> et coller la clé dans les settings du projet (deploy keys)     
test : ssh -T git@github.com 

A configurer après un clone:
git remote set-url origin git@github.com:pascalberthou/CelluleDobotMagician.git git branch -M main
git push -u origin main 

