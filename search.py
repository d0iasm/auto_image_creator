import config
import json
import os
import urllib.request

from googleapiclient.discovery import build


_IMAGES_PATH = './images/'


def getService():
    service = build('customsearch', 'v1',
                    developerKey=config._IMAGE_API_KEY)

    return service


def getImage(images):
    if not os.path.isdir(_IMAGES_PATH):
        os.mkdir(_IMAGES_PATH)

    opener = urllib.request.build_opener()
    count = 1

    for image in images:
        try:
            f = open(_IMAGES_PATH + str(count) + '.jpg', 'wb')
            f.write(urllib.request.urlopen(image).read())
            f.close()
            count = count + 1

        except Exception as e:
            print(e)
            continue


def getData():

    pageLimit = 5
    service = getService()
    startIndex = 1
    response = []
    images = []

    for nPage in range(pageLimit):
        print('Reading page number:', nPage+1)

        try:
            
            response.append(service.cse().list(
                q= '猫',
                cx= config._CUSTOM_SEARCH_ENGINE,
                lr= 'lang_ja',
                num = 1,
                start=startIndex,
                searchType = 'image'
                ).execute())

            startIndex = response[nPage].get('queries').get('nextPage')[0].get('startIndex')

        except Exception as e:
            print(e)

    with open('data.json', 'w') as outfile:
        json.dump(response, outfile)

    for r in response:
        if len(r['items']) > 0:
            for i in range(len(r['items'])):
                images.append(r['items'][i]['link'])

    return images

            
getImage(getData())
