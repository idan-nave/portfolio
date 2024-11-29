import logging
from telegram import Update
from telegram.ext import ApplicationBuilder, ContextTypes, CommandHandler

from config import TOKEN, API_ID, API_HASH
from reg_handlers import register_handlers

# logging.basicConfig(
#     format='%(asctime)s - %(name)s - %(levelname)s - %(message)s',
#     level=logging.INFO
# )-- used for echoing status to terminal

if __name__ == '__main__':
    print('Starting Bot...')
    application = ApplicationBuilder().token(TOKEN).build()
    
    register_handlers(application)
    
    #polling new messages
    print('Polling...')    
    application.run_polling()