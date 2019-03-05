# Remote_OptomaZU660e

# Sony VPL FHZ66 (VKB WorldChanges)
# Check status:
wsl curl -v 'http://192.168.0.101/cgi-bin/web.cgi' -H 'Origin: http://192.168.0.101' -H 'Accept-Encoding: gzip, deflate' -H 'Accept-Language: hu-HU,hu;q=0.9,en-US;q=0.8,en;q=0.7' -H 'User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/72.0.3626.119 Safari/537.36' -H 'Content-Type: application/json' -H 'Accept: */*' -H 'Referer: http://192.168.0.101/control_main.htm' -H 'X-Requested-With: XMLHttpRequest' -H 'Connection: keep-alive' --data-binary '{"req":{"type":"get","category":"control"},"param":{"category":"4054"}}' --compressed

# Send 

wsl curl 'http://192.168.0.101/cgi-bin/web.cgi' -H 'Origin: http://192.168.0.101' -H 'Accept-Encoding: gzip, deflate' -H 'Accept-Language: hu-HU,hu;q=0.9,en-US;q=0.8,en;q=0.7' -H 'User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/72.0.3626.119 Safari/537.36' -H 'Content-Type: application/json' -H 'Accept: */*' -H 'Referer: http://192.168.0.101/control_main.htm' -H 'X-Requested-With: XMLHttpRequest' -H 'Connection: keep-alive' --data-binary '{"req":{"type":"send","category":"control"},"param":{"category":"4054","code":"15"}}' --compressed