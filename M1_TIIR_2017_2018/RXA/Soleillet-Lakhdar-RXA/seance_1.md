
serveur : smb://smbhost/M1-RXA

1- Connexion au switch : cables droits  

2- Configuration telnet :  
  >enable  
  #configure terminal  
  activation des liaisons séries virtuelles (vty) :  
  (config)# line vty 0  
  (config-line)# password bonjour  
  (config-line)# transport input telnet  
  (config-line)# end  
  #configure terminale  
  (config)# interface vlan1  
  (config-if)# ip address 192.168.1.254 255.255.255.0  
  (config-if)# exit  
  (config)# end  


  3- Configuration ssh :  
    >enable  
    #configure terminal  
    #hostname SB4  
    #ip domaine-name lille  
    #crypto key generate rsa  
    (config)# line vty 0  
    (config-line)# login local  
    (config-line)# transport input ssh  
    (config-line)# end  
    #configure terminale  
    (config)# interface vlan1  
    (config-if)# ip address 192.168.1.254 255.255.255.0  
    (config-if)# exit  
    (config)# end  

4- tftp  
  ssh root@192.168.1.254  
  copy system:running-config tftp  
