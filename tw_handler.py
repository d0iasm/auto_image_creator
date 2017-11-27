import config
import json

from requests_oauthlib import OAuth1Session


CK = config._CONSUMER_KEY
CS = config._CONSUMER_SECRET
AT = config._ACCESS_TOKEN
ATS = config._ACCESS_TOKEN_SECRET
twitter = OAuth1Session(CK, CS, AT, ATS)


def checkStatus(req):
    if req.status_code == 200:
        return True
    else:
        print('ERROR: %d' % req.status_code)


def getData():
    req = twitter.get('https://api.twitter.com/1.1/search/tweets.json',
                      params = {'q' : 'to:imageapptest', 'count' : 1})

    text = []
    if checkStatus(req):
        search_timeline = json.loads(req.text)
        for tweet in search_timeline['statuses']:
            text.append(tweet['text'])
            print(tweet['text'].split()[1])

    return text


def uploadImage():
    with open('dest/result.jpg', 'rb') as file:
        raw_binary = file.read()
        
    req = twitter.post('https://upload.twitter.com/1.1/media/upload.json',
                       files = {'media': open('dest/result.jpg', 'rb')})

    if checkStatus(req):
        return json.loads(req._content)['media_id']

    
def sendImage():
    req = twitter.post('https://api.twitter.com/1.1/statuses/update.json',
                       params = {'status': 'Hello, World!',
                                 'media_ids': uploadImage()})

    if checkStatus(req):
        print('Successed')
