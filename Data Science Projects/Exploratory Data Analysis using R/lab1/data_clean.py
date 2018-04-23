import json, pickle, sys

f = open("data_merged.pickle", "rb")
tweets = pickle.load(f)
f.close()

states = ["AL", "AK", "AZ", "AR", "CA", "CO", "CT", "DC", "DE", "FL", "GA", 
	"HI", "ID", "IL", "IN", "IA", "KS", "KY", "LA", "ME", "MD", 
	"MA", "MI", "MN", "MS", "MO", "MT", "NE", "NV", "NH", "NJ", 
	"NM", "NY", "NC", "ND", "OH", "OK", "OR", "PA", "RI", "SC", 
	"SD", "TN", "TX", "UT", "VT", "VA", "WA", "WV", "WI", "WY"
]

states = set([s.lower() for s in states])

states_map = {
	'AK': 'Alaska',
	'AL': 'Alabama',
	'AR': 'Arkansas',
	'AS': 'American Samoa',
	'AZ': 'Arizona',
	'CA': 'California',
	'CO': 'Colorado',
	'CT': 'Connecticut',
	'DC': 'District of Columbia',
	'DE': 'Delaware',
	'FL': 'Florida',
	'GA': 'Georgia',
	'GU': 'Guam',
	'HI': 'Hawaii',
	'IA': 'Iowa',
	'ID': 'Idaho',
	'IL': 'Illinois',
	'IN': 'Indiana',
	'KS': 'Kansas',
	'KY': 'Kentucky',
	'LA': 'Louisiana',
	'MA': 'Massachusetts',
	'MD': 'Maryland',
	'ME': 'Maine',
	'MI': 'Michigan',
	'MN': 'Minnesota',
	'MO': 'Missouri',
	'MP': 'Northern Mariana Islands',
	'MS': 'Mississippi',
	'MT': 'Montana',
	'NA': 'National',
	'NC': 'North Carolina',
	'ND': 'North Dakota',
	'NE': 'Nebraska',
	'NH': 'New Hampshire',
	'NJ': 'New Jersey',
	'NM': 'New Mexico',
	'NV': 'Nevada',
	'NY': 'New York',
	'OH': 'Ohio',
	'OK': 'Oklahoma',
	'OR': 'Oregon',
	'PA': 'Pennsylvania',
	'PR': 'Puerto Rico',
	'RI': 'Rhode Island',
	'SC': 'South Carolina',
	'SD': 'South Dakota',
	'TN': 'Tennessee',
	'TX': 'Texas',
	'UT': 'Utah',
	'VA': 'Virginia',
	'VI': 'Virgin Islands',
	'VT': 'Vermont',
	'WA': 'Washington',
	'WI': 'Wisconsin',
	'WV': 'West Virginia',
	'WY': 'Wyoming'
}

states_map = {name.lower() : states_map[name].lower() for name in states_map}

states_name = set(states_map.values())

for id in tweets:
	tweet = tweets[id]
	
	locs = tweet["location"].split(",")
	for elem in locs[:]:
		locs += elem.split(" ")

	found = False
	for loc in locs:		
		l = loc.strip().lower()

		if l in states:
			tweets[id]["state"] = states_map[l]
			found = True
			break
		elif l in states_name:
			tweets[id]["state"] = l
			found = True
			break
		
	if not found:
		tweets[id]["state"] = ""

tweets = list(tweets.values())

f = open("data_cleaned.json", "w")
json.dump(tweets, f, sort_keys = True, indent = 4, ensure_ascii = True)
f.close()

