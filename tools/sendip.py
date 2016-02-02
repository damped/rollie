#!/usr/bin/env python
#
#
#       Sends an email with the ip addresses
#
#
###############################################

import urllib2



import time
import commands
import re
import smtplib
 
####--[COFIGURATION]
server = 'smtp.gmail.com' #smtp server address
server_port = '587' #port for smtp erver
 
username = 'rolliepi69@gmail.com' #gmail account
password = 'raspiserver' #password for that gmail account
 
fromaddr = 'rolliepi69@gmail.com' #address to send from
toaddr = 'rolliepi69@gmail.com' #address to send IP to
message = "ssh -p 22 pi@"

#message that is sent
####--[/COFIGURATION]
 
#the interface may be wifi and it needs time to initialize
#so wait a little bit before parsing ifconifg
time.sleep(10)
 
#extract the ip address (or addresses) from ifconfig
found_ips = [urllib2.urlopen('http://ip.42.pl/raw').read()]
ips = re.findall( r'[0-9]+(?:\.[0-9]+){3}', commands.getoutput("/sbin/ifconfig"))
for ip in ips:
  if ip.startswith("255") or ip.startswith("127") or ip.endswith("255"):
    continue
  found_ips.append(ip)


message += "   | Local: ".join(found_ips)

headers = ["From: " + fromaddr,
           "To: " + toaddr,
           "MIME-Version: 1.0",
           "Content-Type: text/html"]
headers = "\r\n".join(headers)
 
server = smtplib.SMTP(server + ':' + server_port)  
server.ehlo()
server.starttls()  
server.ehlo()
server.login(username, password)  
server.sendmail(fromaddr, toaddr, headers + "\r\n\r\n" +  message)  
server.quit()
