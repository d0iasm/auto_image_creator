import config
import json

from requests_oauthlib import OAuth1Session

CK = config._CONSUMER_KEY
CS = config._CONSUMER_SECRET
AT = config._ACCESS_TOKEN
ATS = config._ACCESS_TOKEN_SECRET
twitter = OAuth1Session(CK, CS, AT, ATS)

url = "https://api.twitter.com/1.1/search/tweets.json"

print("Which words do you want to search?")
keyword = input('>> ')
print('----------------------------------------------------')

params = {'q' : keyword, 'count' : 5}

req = twitter.get(url, params = params)

if req.status_code == 200:
    search_timeline = json.loads(req.text)
    for tweet in search_timeline['statuses']:
        print(tweet['user']['name'] + '::' + tweet['text'])
        print(tweet['created_at'])
        print('----------------------------------------------------')
else:
    print("ERROR: %d" % req.status_code)
