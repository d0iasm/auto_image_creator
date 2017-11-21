import config
import json

from requests_oauthlib import OAuth1Session

CK = config._CONSUMER_KEY
CS = config._CONSUMER_SECRET
AT = config._ACCESS_TOKEN
ATS = config._ACCESS_TOKEN_SECRET
twitter = OAuth1Session(CK, CS, AT, ATS)

def getData(count):
    req = twitter.get('https://api.twitter.com/1.1/search/tweets.json',
                      params = {'q' : 'to:imageapptest', 'count' : count})

    text = []
    if req.status_code == 200:
        print('----------------------------------------------------')
        search_timeline = json.loads(req.text)
        for tweet in search_timeline['statuses']:
            text.append(tweet['text'])
            print(tweet['user']['name'] + '::' + tweet['text'])
            print(tweet['created_at'])
            print('----------------------------------------------------')
    else:
        print('ERROR: %d' % req.status_code)

    return text

print(getData(1))
