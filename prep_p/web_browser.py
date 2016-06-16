import requests, webbrowser, sys
from urllib.request import urlopen
from bs4 import BeautifulSoup
from pprint import pprint
import pyowm

def map_city(city):
	webbrowser.open('https://www.google.com/maps/place/' + city)
	
def get_weather(city):
	owm = pyowm.OWM()
	wthr = owm.weather_at_place(city)
	w = wthr.get_weather()
	print(w.get_wind())
#map_city('bangalore')
get_weather('bangalore')

