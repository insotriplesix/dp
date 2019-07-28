# -*- coding: utf-8 -*-
import logging
import random
import sys
import telebot
import time

from spys import spys_parser, proxies_db, common_ports

token = "TOKEN"

# Create the bot object
bot = telebot.TeleBot(token)

# Chance to spit
chance = 100

# Default spit frequency
freq = 5

# --------------------------------------------------------------- #

aim_id = 224756173

aim_to_spit = [
    'ДИМА', 'Дима', 'дима', 'ДМИТРИЙ', 'Дмитрий', 'дмитрий',
    'ДИМУ', 'Диму', 'диму', 'ДМИТРИЮ', 'Дмитрию', 'дмитрию',
    'ДИМЕ', 'Диме', 'диме', 'ДИМЫ', 'Димы', 'димы',
    'DIMA', 'Dima', 'dima', 'DMITRY', 'Dmitry', 'dmitry'
]

phrases = [
    'чорту хорчок в чопу!',
    'придурь лови',
    'эу бомбо смари сюда',
    'стерва + ублюдок ахах'
]

open_mouth_e = u'\U0001f62e'
sweat_drops_e = u'\U0001f4a6'
thonk_e = u'\U0001f914'

# --------------------------------------------------------------- #

# Send few spits to Dima
def emoji_spit(m):
    for i in range(freq):
        if i > 0:
            r = random.randrange(0, len(phrases))
            bot.send_message(m.chat.id, phrases[r])

        r = random.randrange(1, 7)
        s = open_mouth_e + sweat_drops_e*r + thonk_e + "<-Дима"
        bot.send_message(m.chat.id, s)

def sticker_spit(m):
    thonkz = bot.get_sticker_set('ThonkHD')
    spit_thonk = thonkz.stickers[9]
    bot.send_sticker(m.chat.id, spit_thonk.file_id, reply_to_message_id=m.message_id)

# --------------------------------------------------------------- #

# Command 'chance' handler
@bot.message_handler(commands=['chance'])
def chance_message(m):
    val = m.text

    if val.isdigit() and val >= 1 and val <= 100:
        global chance
        chance = m.text
    else:
        print("Input correct value from range [1, 100]%")

# Command 'freq' handler
@bot.message_handler(commands=['freq'])
def freq_message(m):
    val = m.text

    if val.isdigit() and val >= 1 and val <= 5:
        global freq
        freq = m.text
    else:
        print("Input correct value from range [1, 5]")

# Command 'help' handler
@bot.message_handler(commands=['help'])
def help_message(m):
    h = '''
+++++++++++++++++++++++++
  {}{}  JOHN SPITTER [v0.2]
+++++++++++++++++++++++++
 
  Список команд:
    /chance - задать шанс на плевок [1-100]%
    /freq - задать частоту плевков [1-5]
    /help - вызов окна поддержки
    /start, /test - приветственное сообщение
    /spit - плюнуть в Диму

+++++++++++++++++++++++
'''.format(open_mouth_e, sweat_drops_e)
    bot.send_message(m.chat.id, h)

# Commands 'start' and 'test' handler
@bot.message_handler(commands=['start', 'test'])
def start_message(m):
    bot.send_message(m.chat.id, 'Готов харкать лошушке в рожу!')

# Command 'spit' handler
@bot.message_handler(commands=['spit'])
def spit_message(m):
    emoji_spit(m)

# Received message handler (sleep a little bit before reply)
@bot.message_handler(content_types=['text'])
def check_message(m):
    r = random.randrange(0, 100)
    if m.from_user.id == aim_id and r < chance:
        sticker_spit(m)
    for name in aim_to_spit:
        if name in m.text:
            time.sleep(random.randrange(3, 7))
            bot.reply_to(m, "Эх, вот бы сейчас харкнуть ему в рожу!")

# --------------------------------------------------------------- #

if __name__ == '__main__':
    while True:
        # Run with proxy
        spys_parser(0)
        for ip, lat in sorted(proxies_db.items(), key=lambda kv: kv[1]):
            try:
                for port in common_ports:
                    url = 'socks5://{}:{}'.format(ip, port)
                    print(url)
                    telebot.apihelper.proxy = {'https':url}
                    bot.polling(none_stop=True)
#               telebot.apihelper.proxy = {'https':'socks5://111.223.75.178:8888'}
#                bot.polling(none_stop=True)
            except:
                logging.error('error: {}'.format(sys.exc_info()[0]))
                time.sleep(5)
