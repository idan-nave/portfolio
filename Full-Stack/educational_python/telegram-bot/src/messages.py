from telegram import Update
from telegram.ext import MessageHandler, filters, ContextTypes

# Import your functions & Constants
from responses import handle_response
from config import BOT_USERNAME

async def handle_message(update: Update, context: ContextTypes.DEFAULT_TYPE):
    message_type: str = update.message.chat.type
    text: str = update.message.text_html

    # debug traffic
    print(f'User ({update.message.chat.id}) in {message_type}: "{text}"')

    # within a group only respond, if asked explicitly
    if message_type == 'group':
        if BOT_USERNAME in text:
            new_text: str = text.replace(BOT_USERNAME, '').strip()
            response: str = handle_response(new_text)
        else:
            return  # do not respond if not asked
    else:
        response: str = handle_response(text)

    # debug send traffic
    print('Bot:', response)

    await update.message.reply_text(response)

async def error(update: Update, context: ContextTypes.DEFAULT_TYPE):
    print(f'Update {update} caused error {context.error}')