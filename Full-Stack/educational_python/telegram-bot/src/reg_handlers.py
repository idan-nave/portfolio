from telegram import Update
from telegram.ext import CommandHandler, MessageHandler, filters, ContextTypes

# Import your functions from the messages module
from commands import start_command, help_command, echo_command, custom_command
from messages import handle_message

def register_handlers(app):
    """
    Register command and message handlers for the Telegram bot.

    Parameters:
    - app: The dispatcher object to register handlers.
    """
    try:
        # Register command handlers
        app.add_handler(CommandHandler('start', start_command))
        app.add_handler(CommandHandler('help', help_command))
        app.add_handler(CommandHandler('custom', custom_command))

        # Register message handler
        #app.add_handler(MessageHandler(filters.TEXT & (~filters.COMMAND), echo_command)) -- for echoing everything
        app.add_handler(MessageHandler(filters.TEXT, handle_message))

        print("Handlers registered successfully.")
    except Exception as e:
        print(f"Error registering handlers: {e}")
