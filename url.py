from urllib.request import urlopen
response = urlopen('http://www.espncricinfo.com/')
html = response.read()

#print(html)