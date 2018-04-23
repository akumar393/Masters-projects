import os
import json

def fetchJSONData(file_name):
	f = open(file_name)
	data = json.load(f)
	f.close()
	
	return data

def jsonDataToFile(data, file_name):
	f = open(file_name, 'w')
	f.write('\n'.join(data))
	f.close()

def readOutput(output_file_name):
	f = open(output_file_name, 'r')
	output = f.readlines()
	f.close()
	
	return output

def formatOutput(output):
	counts = list()

	for line in output:
		key, value = line.split('\t')
		key = key[1:-1]
		
		if not key:
			continue
		
		counts.append( (key, int(value)) )

	counts.sort(key=lambda x:x[1], reverse=True)

	return counts

def outputToFile(output_file_name, data):
	f =  open(output_file_name, 'w')
	f.write('\n'.join( [ "{}\t{}".format(obj[0], obj[1]) for obj in data ] ))
	f.close()

def outputToJSONFile(output_file_name, data):
	res = [ {'text': obj[0], 'size': int(obj[1])} for obj in data[:1000] ]
	
	f =  open(output_file_name, 'w')
	f.write(json.dumps(res, indent=4))
	f.close()

def analyseTweets():
	data = fetchJSONData('./TwitterData/tweets.json')

	tweets = [ tweet['text'] for tweet in data ]

	temp_file_name = "tweet_data.tmp"

	jsonDataToFile(tweets, temp_file_name)

	# Dispatch word count hadoop job
	os.system('python3 wc.py --hadoop-tmp-dir file:///home/ravi/Desktop/Sandbox/MapReduce/temp/ -r hadoop {} > output'.format(temp_file_name))
	#os.remove(temp_file_name)

	output = readOutput('output')
		
	counts = formatOutput(output)

	os.remove('output')

	outputToFile('output_tweets', counts)
	outputToJSONFile('output_tweets.json', counts)

	# Dispatch co-occurence hadoop job
	os.system('python3 wc_coocurence.py --hadoop-tmp-dir file:///home/ravi/Desktop/Sandbox/MapReduce/temp/ -r hadoop {} > output'.format(temp_file_name))
	#os.remove(temp_file_name)

	output = readOutput('output')
		
	counts = formatOutput(output)

	os.remove('output')

	outputToFile('output_coocurence_tweets', counts)
	outputToJSONFile('output_coocurence_tweets.json', counts)

def analyseNews():
	# Dispatch word count hadoop job
	os.system('python3 wc.py --hadoop-tmp-dir file:///home/ravi/Desktop/Sandbox/MapReduce/temp/ -r hadoop ./NewsData/news_data.txt > output')

	output = readOutput('output')
		
	counts = formatOutput(output)

	os.remove('output')

	outputToFile('output_news', counts)
	outputToJSONFile('output_news.json', counts)

	# Dispatch co-occurence hadoop job
	os.system('python3 wc_coocurence.py --hadoop-tmp-dir file:///home/ravi/Desktop/Sandbox/MapReduce/temp/ -r hadoop ./NewsData/news_data.txt > output')
	#os.remove(temp_file_name)

	output = readOutput('output')
		
	counts = formatOutput(output)

	os.remove('output')

	outputToFile('output_coocurence_news', counts)
	outputToJSONFile('output_coocurence_news.json', counts)



if __name__ == "__main__":
	analyseTweets()
	
	analyseNews()
