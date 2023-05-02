import telebot
from telebot import types
import constants as keys

bot = telebot.TeleBot(keys.API_KEY)

@bot.message_handler(commands=['start'])
def start(message):
    markup = types.InlineKeyboardMarkup()
    orderB = types.InlineKeyboardButton(text='Сделать заказ', callback_data='order')

    markup.add(orderB)
    bot.send_message(message.chat.id, 'Привет! Я бот для доставки напитков.', reply_markup=markup)

@bot.message_handler(commands=['order', 'Сделать заказ'])
def order(message):
    markup = types.ReplyKeyboardMarkup(resize_keyboard=True, row_width=2)
    for num in range(3):
        drink = types.KeyboardButton(f'Напиток {num}')
        markup.add(drink)
    cancelB = types.KeyboardButton('Отмена')
    markup.add(cancelB)

    bot.send_message(message.chat.id, 'Выберите желаемый напиток.',  reply_markup=markup)

bot.polling(none_stop=True)
