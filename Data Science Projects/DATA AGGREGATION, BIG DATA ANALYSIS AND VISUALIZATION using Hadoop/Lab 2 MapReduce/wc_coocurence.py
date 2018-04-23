from mrjob.job import MRJob
from mrjob.step import MRStep
from nltk.corpus import stopwords
import re

stopwords = set(stopwords.words('english'))
stopwords.add('https')
stopwords.add('//t')
stopwords.add('&amp')
stopwords.add('&amp;')

class WordCount(MRJob):
	def steps(self):
		return [
			MRStep(mapper=self.mapper_get_words,
				reducer=self.reducer_count_words
			)
		]
		
	def mapper_get_words(self, _, line):
		line = self.replace_urls(line)
	
		words = re.split(r'[- :!.,?#@]', line)
		
		words = self.remove_stop_words(words)
		
		for i in range(len(words)):
			for j in range(i, len(words)):
				word1 = words[i]
				word2 = words[j]
				
				if word1 == word2:
					continue
					
				yield "{}_{}".format(word1, word2), 1
				
		
		#for word1 in words:
		#	for word2 in words:
		#		if word1 == word2:
		#			continue
		#	
		#		yield "{}_{}".format(word1, word2), 1
		
	def reducer_count_words(self, key, values):
		yield key, sum(values)
		
	def clean(self, word):
		word = word.strip()
		word = word.lower()
		
		return word
		
	def remove_stop_words(self, words):
		res = list()
		
		for word in words:
			word = self.clean(word)
		
			if word in stopwords:
				continue
				
			if not word:
				continue
			
			if word.isnumeric():
				continue
				
			res.append(word)
			
		return res
		
	def replace_urls(self, line):
		urlpattern = re.compile(r"""(?i)\b((?:https?://|www\d{0,3}[.]|[a-z0-9.\-]+[.][a-z]{2,4}/)(?:[^\s()<>]+|\(([^\s()<>]+|(\([^\s()<>]+\)))*\))+(?:\(([^\s()<>]+|(\([^\s()<>]+\)))*\)|[^\s`!()\[\]{};:'".,<>?«»“”‘’]))""")    
		line = urlpattern.sub(r'', line)
		
		return line
		
if __name__ == '__main__':
	WordCount.run()
