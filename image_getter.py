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


def saveImages(images):
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


def getData(words):
    service = getService()
    response = []
    images = []

    print(words)
    for word in words:
        print('Reading:', word)

        try:            
            response.append(service.cse().list(
                q= word,
                cx= config._CUSTOM_SEARCH_ENGINE,
                lr= 'lang_ja',
                num = 1,
                searchType = 'image'
                ).execute())

        except Exception as e:
            print(e)

    for r in response:
        if len(r['items']) > 0:
            for i in range(len(r['items'])):
                images.append(r['items'][i]['link'])

    return images


words = input('Which words do you want to search? > ').split()
saveImages(getData(words))
