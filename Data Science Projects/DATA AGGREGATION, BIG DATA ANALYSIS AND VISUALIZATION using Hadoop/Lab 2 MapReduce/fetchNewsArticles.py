# -*- coding: utf-8 -*-
"""
Created on Sun Apr  1 00:42:58 2018

@author: abina
"""

from nytimesarticle import articleAPI
import requests, time, json
from bs4 import BeautifulSoup

def parse_articles(articles):
	'''
	This function takes in a response to the NYT ap
	
	35i and parses
	the articles into a list of dictionaries
	'''
	news = []
	article=[]
	for i in articles['response']['docs']:
		req = requests.get(i['web_url'])
		soup = BeautifulSoup(req.content, "lxml")
		paragraphs = soup.find_all('p', class_='story-body-text story-content')

		for i in paragraphs:
			article.append(i.get_text())
			
	return (news, article)

		
api = articleAPI('1f222871b0b240779173878f2a6308f2')

raw_response = dict()
articles_list = list()

p = 1
data_available = True
while data_available and p <= 200:
	print ("Page: {}".format(p))

	articles = api.search( q = 'immigration', begin_date = 20180323,
		end_date = 20180330, page = p)
	
	raw_response[p] = articles
		
	if len(articles['response']['docs']) <= 0:
		data_available = False
		break
	
	news, articles = parse_articles(articles)

	articles_list.extend(articles)

	p += 1

with open('news_data.txt', 'w') as f:
	f.write('\n\n'.join(articles_list))
	
with open('news_data_raw.txt', 'w') as f:
	f.write(json.dumps(raw_response, indent=4))
	
	
