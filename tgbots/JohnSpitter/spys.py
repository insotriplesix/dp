import logging
import re
import sys
import requests

# TODO: used proxies flag?

# the most common ports
common_ports = (1080, 6667, 8888, 9999)

# ips database {ip: latency}
proxies_db = {}

# print proxies db just 4 debug stuff
def dump_info():
    print('+' + '-'*17 + '+' + '-'*8 + '+')
    print('| {:15} | {:6} |'.format("IP", "LAT"))
    print('+' + '-'*17 + '+' + '-'*8 + '+')

    for k, v in sorted(proxies_db.items(), key=lambda kv: kv[1]):
        print('| {:15} | {:6} |'.format(k, v))

    print('+' + '-'*17 + '+' + '-'*8 + '+')

# +++ PARSER +++
def spys_parser(x):
    url = "http://spys.one/en/socks-proxy-list/"
    headers = {'User-Agent': 'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:67.0) Gecko/20100101 Firefox/67.0'}
    req = requests.post(url, {"xpp":x}, headers=headers)
    webpage = req.content.decode("utf8")

    seen = set()

    raw_ips = re.findall(r"\b\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}\b", webpage)
    raw_delays = re.findall(r"\>\d{1,3}\.\d{1,3}\<", webpage)

    # get rid of brackets
    delays = [raw_delays[i][1:len(raw_delays[i])-1] for i in range(0, len(raw_delays))]

    # sometimes 'hostname/org' section can contain the duplicates
    # of already parsed ips, we aint need 'em
    cnt = min(len(raw_ips), len(delays))
    d = 0
    for i in range(cnt):
        ip = raw_ips[i]
        if ip not in seen:
            seen.add(ip)
            proxies_db[ip] = float(delays[d])
            d += 1

#if __name__ == "__main__":
#    spys_parser(0) # opt selection, from 0 to 5
#    dump_info()
