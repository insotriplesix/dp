# -*- coding: utf-8 -*-
import datetime
import random
import telebot
import time

from bs4 import BeautifulSoup
from config import TOKEN
from urllib import request

# Create an object of a bot
bot = telebot.TeleBot(TOKEN)

''' ---------------------------------------------------------------------------------------------------------------- '''

bot_names = ['Вася', 'вася', 'Васёк', 'васёк', 'Васек', 'васек', 'Васька', 'васька', 'Василий', 'василий', 'Васе',
             'васе', 'Васю', 'васю', 'Васи', 'васи', 'Вась', 'вась', 'Ваське', 'ваське', 'Ваську', 'ваську', 'Василию',
             'василию', 'Vasek', 'vasek', 'VASEK', 'ВАСИЛИЮ', 'ВАСЯ', 'ВАСЁК', 'ВАСЕК', 'ВАСЬКА', 'ВАСИЛИЙ', 'ВАСЕ',
             'ВАСЮ', 'ВАСИ', 'ВАСЬ', 'ВАСЬКЕ', 'ВАСЬКУ']

activity_words = ['Что делаешь', 'что делаешь', 'Чё делаешь', 'чё делаешь', 'Че делаешь', 'че делаешь', 'Чо делаешь',
                  'чо делаешь', 'Шо делаешь', 'шо делаешь', 'Што делаешь', 'што делаешь', 'Чем занят', 'чем занят',
                  'Чё мутишь', 'чё мутишь', 'Че мутишь', 'че мутишь', 'Шо мутишь', 'шо мутишь', 'как ты там',
                  'как ты там', 'там у тебя', 'ЧЕМ ЗАНЯТ', 'ЧТО ДЕЛАЕШЬ', 'ЧЕ ДЕЛАЕШЬ', 'ЧО ДЕЛАЕШЬ', 'ШО ДЕЛАЕШЬ',
                  'ШТО ДЕЛАЕШЬ', 'ШО МУТИШЬ']

goodbye_words = ['Пока', 'пока', 'Споки', 'споки', 'Спочки', 'спочки', 'Спокойной ночи', 'спокойной ночи', 'ПОКА']

hello_words = ['Привет', 'привет', 'Здарова', 'здарова', 'Хай', 'хай', 'Салют', 'салют', 'ПРИВЕТ', 'ЗДАРОВА', 'ХАЙ']

mood_words = ['Как дела', 'как дела', 'Как настроение', 'как настроение', 'Как у тебя дела', 'как у тебя дела',
              'Как у тебя настроение', 'как у тебя настроение', 'Че как', 'че как', 'Че каво', 'че каво', 'Как ты',
              'как ты', 'Как поживаешь', 'как поживаешь', 'КАК ПОЖИВАЕШЬ', 'КАК ДЕЛА', 'КАК НАСТРОЕНИЕ', 'ЧО КАК']

random_words = ['Скажи', 'скажи', 'скажешь', 'Что ещё', 'что ещё', 'Шо ещё', 'шо ещё', 'Чё ещё', 'чё ещё', 'Чо ещё',
                'чо ещё', 'Что-нибудь', 'что-нибудь', 'Шо недь', 'шо недь', 'Што-нибудь', 'што-нибудь', 'Че-недь',
                'че-недь', 'Чё недь', 'чё недь', 'Чо недь', 'чо недь', 'Шо нибудь', 'шо нибудь', 'Што-недь', 'што-недь',
                'ЧО НЕДЬ', 'ШО НИБУДЬ']

rude_words = ['Хуй', 'хуй', 'Соси', 'соси', 'Пид', 'пид', 'Лох', 'лох', 'Тупой', 'тупой', 'Тупица', 'тупица', 'Уёб',
              'уёб', 'Уеб', 'уеб', 'Даун', 'даун', 'Сука', 'сука', 'Пизд', 'пизд', 'Сосать', 'сосать', 'Придурок',
              'придурок', 'Идиот', 'идиот', 'Чмо', 'чмо', 'Чёрт', 'чёрт', 'Черт', 'черт', 'Долбо', 'долбо', 'Ублюдок',
              'ублюдок', 'Суч', 'суч', 'Гнида', 'гнида', 'Шлю', 'шлю', 'Гондон', 'гондон']

why_words = ['Почему', 'почему', 'А что так', 'а что так', 'А чё так', 'а чё так', 'А шо так', 'а шо так', 'Зачем',
             'зачем', 'Нахуя', 'нахуя', 'Нахрен', 'нахрен']

petrovich_answers = {0: 'сука хачу питровича!', 1: 'хочу бухать суки', 2: 'дай мне питровича падла)))', 3: 'хочу суку',
                     4: 'дайти водяры суки', 5: 'пошли бухать питровича детка))))'}

artem_words = ['Артём', 'артём', 'Артем', 'артем', 'Тёма', 'тёма']
ilya_words = ['Илья', 'илья', 'Илюша', 'илюша', 'Илье', 'илье', 'Илью', 'илью']
lera_words = ['Лера', 'лера', 'Лерк', 'лерк', 'Леру', 'леру', 'Лере', 'лере']
roman_words = ['Рома', 'рома', 'Ромо', 'ромо']
sonya_words = ['Соня', 'соня', 'Соньк', 'соньк', 'Соню', 'соню', 'Соне', 'соне']

''' ---------------------------------------------------------------------------------------------------------------- '''

activity_answers = {0: 'сижу общаюсь с тобой че не видеш', 1: 'сую хуй тебе в рот))))', 2: 'играю в гта крмпэшку',
                    3: 'тараню твой рот балтом', 4: 'общаюсь с соской кокойто', 5: 'пирданул в нос тебе а что????',
                    6: 'слушай мне не до тебя говори чё хочеш', 7: 'ща подожди одаааа сука пёрнул в тебя', 8: 'хаваю',
                    9: 'ем огурец а чё', 10: 'пишу тебе в телеграме идиотина', 11: 'бухаю пивас', 12: 'смотрю телик',
                    13: 'дрочу и ща кончю на тебя оооо дааааа суааааааа'}

goodbye_answers = {0: 'аливидерчи)))', 1: 'ага', 2: 'гудбай лошара)', 3: 'пиздуй))', 4: 'адиос амигос сука подсасывай',
                   5: 'пака и подпишись на канал сучка)))', 6: 'прощай', 7: 'вали подальше', 8: 'вот и идика ты нахуй',
                   9: 'пока но наа даче будет жара када ебать тя буду', 10: '66', 11: 'смари не падавись моим шлангом',
                   12: 'пока машка))))', 13: 'до встречи с моим членам'}

hello_answers = {0: 'здарово', 1: 'ну привет', 2: 'хай сука))', 3: 'ага', 4: 'гутэнтак)))', 5: 'банжур епта', 6: 'хай',
                 7: 'салют сучька!)', 8: 'здраствуйте', 9: 'привет соска', 10: 'привет бот)))', 11: 'хай и саси сразу',
                 12: 'хочеш общаца? давай сука', 13: 'базарь'}

mood_answers = {0: 'нормальна. а че те?', 1: 'хуёва', 2: 'зоебись))', 3: 'так се', 4: 'норма', 5: 'тя не ебать должно',
                6: 'нормас хочу трахаца в троём я лерка сонька)))))', 7: 'а вот так что у тебя весь рот в моей сперми',
                8: 'как ты думаеш когда у меня хуй большой те в рот не влезет??', 9: 'по жопе бы те надавать сучбка))',
                10: 'ща покажу те свой хуй узнаеш', 11: 'отсоси узнаеш', 12: 'а щто хочешь от меня?', 13: 'хз бля чёте',
                14: 'неебу дальше што', 15: 'вс отлично вчера леру трахнул хорошо было стонала сука)))'}

random_answers = {0: 'я люблю лерку но эта сучка меня не любет', 1: 'соню выдрать хочеца очень))',
                  2: 'рома пидафил ебаный бородатый черт саси хуй', 3: 'артем питух соси', 4: 'илья лох я те ёбну',
                  5: 'хз чё расказать. го на сервак я тя админом сделаю))))))', 6: 'када бухать суки на дачю', 7: 'пнх',
                  8: 'ниче не хочу говорить иди нахуй', 9: 'если никитос еще раз будет пиздить я ево ушатаю суку',
                  10: 'подпишись https://www.youtube.com/channel/UCV0XK4xmltqmn5tY6by4NbA', 11: 'соси болт сучка)))',
                  12: 'яне насрать под губу с насваем пусть сасет дальше', 13: 'кто хочет сасать давай иди сюда сука',
                  14: 'нах ваш ебаный телеграмм'}

rude_answers = {0: 'иди нахуй сука', 1: 'саси', 2: 'ты шлюшка тупая отсаси мой хуй', 3: 'ты сука отсоси мой болт',
                4: 'отсоси мне', 5: 'сучка я тя ушатаю', 6: 'завали ебала сука', 7: 'заткнись', 8: 'прососи хуй дура',
                9: 'я тя уебу падлюка', 10: 'ты сука тупая пошла нахуй тварь', 11: 'я твой хуй разработаю лох',
                12: 'соска рот закрой', 13: 'понюхай очко моё сучара', 14: 'смотри сюда --------> соси', 15: 'ди на',
                16: 'чё срака красная? иди проспись', 17: 'пошла нахуй', 18: 'давай едь на дачу я тебя ебать буду',
                19: 'иди сюда я те пасасать дам', 20: 'ехай нахуй'}

what_answers = {0: 'че?', 1: 'хули надо', 2: 'ну?', 3: 'че те блять', 4: '?', 5: 'чо сука', 6: 'саси ево 3====э',
                7: 'што хотела сучька?', 8: 'ты мне бля', 9: 'да', 10: 'што', 11: 'ну пизди тока хуй высунь изо рта',
                12: 'говори дальше сука', 13: 'жду', 14: 'я тут есличё'}

why_answers = {0: 'хуй ево знает я занет атвали)))', 1: 'незнаю', 2: 'не ебу', 3: 'я не в настраении отвачать',
               4: 'потомучьто ты прососка)', 5: 'шоб ты спросила', 6: 'я уебок наверна', 7: 'просто', 8: 'хз иди нах',
               9: 'хз', 10: 'понятья неимею', 11: 'какая тибе разница', 12: 'тя не ибёт', 13: 'саси а не спрашивай))',
               14: 'давай саси не останавливайся'}

# rude_answers5 = {0: '', 1: '', 2: '', 3: '', 4: '', 5: '', 6: '', 7: '', 8: '', 9: '', 10: '', 11: '', 12: '', 13: ''}

''' ---------------------------------------------------------------------------------------------------------------- '''
# гей дон гондон протаранить рот ну сучька давай давай сделай это


# Bot hello messages
def say_hello(message):
    for word in hello_words:
        if word in message.text:
            bot.send_message(message.chat.id, hello_answers[random.randrange(0, len(hello_answers))])
            return 0


# Bot mood messages
def say_mood(message):
    for word in mood_words:
        if word in message.text:
            bot.send_message(message.chat.id, mood_answers[random.randrange(0, len(mood_answers))])
            return 0


# Bot activity messages
def say_activity(message):
    for word in activity_words:
        if word in message.text:
            bot.send_message(message.chat.id, activity_answers[random.randrange(0, len(activity_answers))])
            return 0


# Bot goodbye messages
def say_goodbye(message):
    for word in goodbye_words:
        if word in message.text:
            bot.send_message(message.chat.id, goodbye_answers[random.randrange(0, len(goodbye_answers))])
            return 0


# Bot why messages
def say_why(message):
    for word in why_words:
        if word in message.text:
            bot.send_message(message.chat.id, why_answers[random.randrange(0, len(why_answers))])
            return 0


# Bot respond messages
def say_what(message):
    bot.send_message(message.chat.id, what_answers[random.randrange(0, len(what_answers))])
    return 0


# Bot rude messages
def say_swearword(message):
    for word in rude_words:
        if word in message.text:
            bot.send_message(message.chat.id, rude_answers[random.randrange(0, len(rude_answers))])
            return 0


# Bot tells his thoughts
def say_something(message):
    for word in random_words:
        if word in message.text:
            bot.send_message(message.chat.id, random_answers[random.randrange(0, len(random_answers))])
            return 0


''' ---------------------------------------------------------------------------------------------------------------- '''


# Command 'help' handling
@bot.message_handler(commands=['help'])
def help_message(message):
    msg = '''
*************************
****** Vasek Bot v1.2 ******
*************************
 
 Список команд:
 /help - вызов окна поддержки
 /start, /test - приветственное сообщение
 /time - информация о времени
 /tits - отправить сиськи

 Заметки:
 > Vasek является аппроксимированной копией блогера и геймера Василия Придатченко из клана SKK
 
 > Vasek не реагирует на сообщения, в которых не упоминается его имя (почти)

 > Vasek не всегда адекватен, поэтому не стоит на него злиться... но и злить его тоже не стоит :)

 > Vasek может стать лучше благодаря вам, так что предлагайте свои идеи по его усовершенствованию

 (с) Eugen Crack
'''
    bot.send_message(message.chat.id, msg)


# Command 'start' and 'test' handling
@bot.message_handler(commands=['start', 'test'])
def start_message(message):
    bot.send_message(message.chat.id, 'я тут')


# Command 'time' handling
@bot.message_handler(commands=['time'])
def time_message(message):
    summer_days = 92
    today = datetime.date.today()
    next_year = today.year + 1

    last_summer_day = datetime.date(today.year, 9, 1)
    new_year_day = datetime.date(next_year, 1, 1)
    boys_day = datetime.date(next_year, 2, 23)
    girls_day = datetime.date(next_year, 3, 8)
    win_day = datetime.date(next_year, 5, 9)
    rus_day = datetime.date(next_year, 6, 12)
    artem_day = datetime.date(next_year, 1, 5)
    ilya_day = datetime.date(next_year, 2, 23)
    lera_day = datetime.date(next_year, 3, 5)
    nikita_day = datetime.date(next_year, 6, 17)
    roman_day = datetime.date(next_year, 3, 8)
#    sonya_day = datetime.date(next_year, 1, 1)  # ?????
    vasya_day = datetime.date(next_year, 1, 3)
    yana_day = datetime.date(next_year, 5, 15)

    diff_summer = last_summer_day - today
    diff_new_year = new_year_day - today
    diff_boys = boys_day - today
    diff_girls = girls_day - today
    diff_win = win_day - today
    diff_rus = rus_day - today
    diff_artem = artem_day - today
    diff_ilya = ilya_day - today
    diff_lera = lera_day - today
    diff_nikita = nikita_day - today
    diff_roman = roman_day - today
    diff_sonya = today - today
    diff_vasya = vasya_day - today
    diff_yana = yana_day - today

    msg = '''
Сегодня {}
Проёбано {} дней лета... осталось {}
----------------------------------------------------------
 > Новый год через {}д
 > День пацанов через {}д
 > День тёлок через {}д
 > Деды победят через {}д
 > День России через {}д
----------------------------------------------------------
 > День рождения Артёма через {}д
 > День рождения Васи через {}д
 > День рождения Ильи через {}д
 > День рождения Леры через {}д
 > День рождения Никиты через {}д
 > День рождения Романа через {}д
 > День рождения Сони через {}д
 > День рождения Яны через {}д
'''.format(today.strftime('%d.%m.%Y'), summer_days - diff_summer.days, diff_summer.days, diff_new_year.days,
           diff_boys.days, diff_girls.days, diff_win.days, diff_rus.days, diff_artem.days, diff_vasya.days,
           diff_ilya.days, diff_lera.days, diff_nikita.days, diff_roman.days, diff_sonya.days, diff_yana.days)
    bot.send_message(message.chat.id, msg)


# Command 'tits' handling
@bot.message_handler(commands=['tits'])
def tits_message(message):
    url = 'http://boobs-selfshots.tumblr.com/random'
    resp = request.urlopen(url)
    html = resp.read()
    parser = BeautifulSoup(html, 'html.parser')
    tag = parser.find_all('div', {'class': 'photo_post'})[0].a

    if tag is not None:
        img = tag.img
    else:
        img = parser.find_all('div', {'class': 'photo_post'})[0].img

    link = img['src']
    bot.send_message(message.chat.id, link)


# Received message handling, 'sleep' for a little delay before answering
@bot.message_handler(content_types=['text'])
def check_message(message):
    if 'петрович' in message.text or 'питрович' in message.text:
        time.sleep(random.randrange(3, 7))
        bot.send_message(message.chat.id, petrovich_answers[random.randrange(0, len(petrovich_answers))])
        return

    # ~10% chance to do that block
    if random.randrange(0, 10) == 5:
        for artem in artem_words:
            if artem in message.text:
                time.sleep(random.randrange(3, 7))
                bot.send_message(message.chat.id, 'артем питух)))')
                return

        for ilya in ilya_words:
            if ilya in message.text:
                time.sleep(random.randrange(3, 7))
                bot.send_message(message.chat.id, 'илья олкаш ебаный)')
                return

        for lera in lera_words:
            if lera in message.text:
                time.sleep(random.randrange(3, 7))
                bot.send_message(message.chat.id, 'я люблю и хочю лерку')
                return

        for roman in roman_words:
            if roman in message.text:
                time.sleep(random.randrange(3, 7))
                bot.send_message(message.chat.id, 'рома это пидар)))')
                return

        for sonya in sonya_words:
            if sonya in message.text:
                time.sleep(random.randrange(3, 7))
                bot.send_message(message.chat.id, 'я хочю потрахаца с соней)))')
                return

    for name in bot_names:
        if name in message.text:
            time.sleep(random.randrange(3, 7))

            # Greetings!
            if say_hello(message) == 0:
                break

            # How r u?
            if say_mood(message) == 0:
                break

            # Why?
            if say_why(message) == 0:
                break

            # Wut r u doing?
            if say_activity(message) == 0:
                break

            # Say something!
            if say_something(message) == 0:
                break

            # Rude words
            if say_swearword(message) == 0:
                break

            # Good bye
            if say_goodbye(message) == 0:
                break

            # Bot responds
            if say_what(message) == 0:
                break


if __name__ == '__main__':
    bot.polling(none_stop=True)
